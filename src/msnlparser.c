#include "msnlparser.h"
#include "functiontable.h"
// Declared extern in .h
// Array of all components in circuit
Line_t *g_Lines = NULL;
Component_t *g_ComponentList = NULL;
Node_t *g_NodeList = NULL;
int g_NumNodesMax = 0;
int g_NumNodesUnique = 0;
int g_NodeIndex = 0;
int g_NumLines = 0;
int g_LineIndex = 0;

void debug() {
    return;
}
// Open file and read it, return ptr to Lines array
void MSNL_ReadFile(const char *file_name_string) {
    // Open the file in read mode
    FILE *fptr = fopen(file_name_string, "r");
    // Error if file opening failed
    if (fptr == NULL) {
        printf("Error: failed to open file %s. Program terminated.\n", file_name_string);
        exit(EXIT_FAILURE);
    }
    // Count lines in file
    char c;
    int count = 0;
    for (c = fgetc(fptr); c != EOF; c = fgetc(fptr)) if (c == '\n') count++;
    // Assign number of lines counted to global num lines
    g_NumLines = count;
    // Allocate Lines array
    g_Lines = (Line_t *) calloc(g_NumLines, sizeof(Line_t));
    // Reset read ptr
    rewind(fptr);
    for (count = 0; count < g_NumLines; ++count) {
        // Access the array at index [count], then the .Data member
        fgets(g_Lines[count].Data, MAX_LINE_LENGTH, fptr);
    }
    // Close the file
    fclose(fptr);
}
// Make list of all components in circuit
void MSNL_MakeComponentList() { 
    g_ComponentList = (Component_t *) calloc(g_NumLines, sizeof(Component_t));
}

// Make list of all nodes in circuit
void MSNL_MakeNodeList() {
    // Temporary solution, 2x nodes per component should be more than enough
    g_NodeList = (Node_t *) calloc(g_NumNodesMax, sizeof(Node_t));
}
// Check if parsed node name already found or not
int MSNL_IsRepeatNode(char * node_label_string) {
    int i;
    // Iterate until a repeat is found
    for (i = 0; i < g_NumNodesMax; i++) {
        // Compare argument string to Label at current index
        if (!strncmp(g_NodeList[i].Label, node_label_string, (MAX_LABEL_LENGTH))) {
            // If repeat is found, return 1
            return 1;
        }
    }
    // If no repeat, increment NumNodesUnique and return 1
    g_NumNodesUnique++;
    return 0;
}

void MSNL_GetCircuitFromFile(const char *file_name_string) {
    // Consolidate previous functions
    MSNL_ReadFile(file_name_string);
    MSNL_MakeComponentList();
    g_NumNodesMax = g_NumLines * 2;
    MSNL_MakeNodeList();
    // Guarantee that this gets reset
    for (g_LineIndex = 0; g_LineIndex < g_NumLines; g_LineIndex++) {
        MSNL_ParseLine(g_Lines[g_LineIndex].Data);
    }
}

// Parse lines
void MSNL_ParseLine(char *target_line) {
    char *token;
    // Delimiters specified by MSNL format
    const char *delimiters = " \t\n"; 
    // Get Label (Example: "V1")
    token = strtok(target_line, delimiters);
    if (!token) {
        printf("Error: Parser was called to interpret line %d, which is empty.\n", g_LineIndex);
        exit(EXIT_FAILURE);   
    }
    if (strlen(target_line) > MAX_LABEL_LENGTH) {
         printf("Error: Invalid component label on line %d.\n", g_LineIndex);
         exit(EXIT_FAILURE);
    }

    strncpy(g_ComponentList[g_LineIndex].Label, token, sizeof(g_ComponentList[g_LineIndex].Label) - 1);
    // Get Type ("ACTIVE", "RESISTOR", ...)
    token = strtok(NULL, delimiters);
    if (!token) {
        printf("Failed to parse component type, terminating program.\n");
        exit(EXIT_FAILURE);
    }
    if (strcmp(token, "ACTIVE") == 0)         g_ComponentList[g_LineIndex].Type = ACTIVE;
    else if (strcmp(token, "RESISTOR") == 0)  g_ComponentList[g_LineIndex].Type = RESISTOR;
    else if (strcmp(token, "CAPACITOR") == 0) g_ComponentList[g_LineIndex].Type = CAPACITOR;
    else if (strcmp(token, "INDUCTOR") == 0)  g_ComponentList[g_LineIndex].Type = INDUCTOR;
    else {
        printf("Error: Unknown component type '%s'\n", token);
        exit(EXIT_FAILURE);
    }

    // Get Value (function ptr for active, else float literal)
    token = strtok(NULL, delimiters); // Contains "SIN(5,100)" or "100.0f"
    if (!token) {
        printf("Failed to parse component value, terminating program.\n");
        exit(EXIT_FAILURE);
    }
    if (g_ComponentList[g_LineIndex].Type == ACTIVE) {
        // Separate function from parameters (Ex: "SIN" from "(5,100)")
        char *open_parentheses = strchr(token, '(');
        if (!open_parentheses) {
            printf("Error: Active component missing parameters '('\n");
            exit(EXIT_FAILURE);
        }

        // Isolate the function name
        *open_parentheses = '\0';
        char *FuncNameStr = token; // Now "SIN" is just a C string
        char *FuncParamStr = open_parentheses + 1; // Now "5,100)"

        // Find parsed function name in lookup table
        g_ComponentList[g_LineIndex].Value.ActiveFunction.ptr = NULL;
        int i = 0;
        for (i = 0; g_FunctionTable[i].FuncPtr != NULL; i++) {
            if (strcmp(g_FunctionTable[i].Name, FuncNameStr) == 0) {
                g_ComponentList[g_LineIndex].Value.ActiveFunction.ptr = g_FunctionTable[i].FuncPtr;
                break;
            }
        }
        if (g_ComponentList[g_LineIndex].Value.ActiveFunction.ptr == NULL) {
            printf("Error: Unknown active function '%s' on line %d.\n", FuncNameStr, g_LineIndex);
            exit(EXIT_FAILURE);
        }
        g_ComponentList[g_LineIndex].Value.ActiveFunction.ParamsCount = 0;
        char *cursor = FuncParamStr; // Use a cursor to walk the string
        char *endptr = NULL;

        // Loop until closing parentheses or end of string
        while (*cursor != '\0' && *cursor != ')') {
    
            if (g_ComponentList[g_LineIndex].Value.ActiveFunction.ParamsCount >= MAX_NUM_PARAMS) {
                printf("Error: Too many parameters for function %s\n.", FuncNameStr);
            exit(EXIT_FAILURE);
            }

            // strtof parses the float and sets endptr to the character immediately following the number
            g_ComponentList[g_LineIndex].Value.ActiveFunction.Params[g_ComponentList[g_LineIndex].Value.ActiveFunction.ParamsCount] = strtof(cursor, &endptr);
            // If no conversion, prevent infinite loop
            if (cursor == endptr) {
                break; 
            }
            g_ComponentList[g_LineIndex].Value.ActiveFunction.ParamsCount++;
            // Advance cursor to the end of the number we just parsed
            cursor = endptr;
            // Skip the comma if the next character is one
            if (*cursor == ',') {
                cursor++;
            }
        }
    } 
    else {
        // Parse float for RESISTOR, CAPACITOR, INDUCTOR
        char *endptr;
        // Give float literal to component nominal value
        g_ComponentList[g_LineIndex].Value.Nominal = strtof(token, &endptr);     
        // Fail if no number found (token == endptr)
        // Fail if characters remain that aren't just 'f'
        if (token == endptr || (*endptr != '\0' && (*endptr != 'f' || *(endptr + 1) != '\0'))) {
            printf("Error: Invalid value '%s'. Units are not allowed.\n", token);
            exit(EXIT_FAILURE);
        }
    }
    // Parse Positive Node
    token = strtok(NULL, delimiters);
    if (!token) {
        printf("Failed to parse positive node, terminating program.\n");
        exit(EXIT_FAILURE);
    }
    strncpy(g_ComponentList[g_LineIndex].PosNode, token, sizeof(g_ComponentList[g_LineIndex].PosNode) - 1);
    // If node isn't a repeat, add it to the NodeList
    if (!MSNL_IsRepeatNode(token)) {
        // Add to list
        strncpy(g_NodeList[g_NodeIndex].Label, token, sizeof(g_ComponentList[g_NodeIndex].PosNode) - 1);
        // Increment index
        g_NodeIndex++;
    }
    // Parse Negative Node
    token = strtok(NULL, delimiters);

    if (!token) {
        printf("Failed to parse negative node, terminating program.\n");
        exit(EXIT_FAILURE);
    }    
    strncpy(g_ComponentList[g_LineIndex].NegNode, token, sizeof(g_ComponentList[g_LineIndex].NegNode) - 1);
    if (!MSNL_IsRepeatNode(token)) {
        // Add to list
        strncpy(g_NodeList[g_NodeIndex].Label, token, sizeof(g_ComponentList[g_NodeIndex].NegNode) - 1);
        // Increment index
        g_NodeIndex++;
    }
}

#include "msnlparser.h"
#include "functiontable.h"
// Array of all components in circuit
Component_t *ComponentList;
// Declared extern in .h
unsigned int g_LineIndex;
// Open file and read it, return ptr to Lines array
Line_t *MSNL_ReadFile(const char *file_name_string) {
    // Open the file in read mode
    FILE *fptr = fopen(file_name_string, "r");
    // Error if file opening failed
    if (fptr == NULL) {
        printf("Error: failed to open file %s. Program terminated.\n", file_name_string);
        exit(EXIT_FAILURE);
    }
    // Count lines in file
    char c;
    unsigned int count = 0;
    for (c = fgetc(fptr); c != EOF; c = fgetc(fptr)) if (c == '\n') count++;
    // Assign number of lines counted to global line index
    g_LineIndex = count;
    // Allocate Lines array
    Line_t *result = (Line_t *) malloc(sizeof(Line_t) * g_LineIndex);
    // Reset read ptr
    rewind(fptr);
    for (count = 0; count < g_LineIndex; ++count) {
        // Access the array at index [count], then the .Data member
        fgets(result[count].Data, MAX_LINE_LENGTH, fptr);
    }
    // Close the file
    fclose(fptr);
    return result;
}
// Make list of all components in circuit
Component_t *MSNL_MakeComponentList() {
    Component_t *result = (Component_t *) malloc(sizeof(Component_t) * g_LineIndex);
    return result;
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

    strncpy(ComponentList[g_LineIndex].Label, token, sizeof(ComponentList[g_LineIndex].Label) - 1);
    // Get Type ("ACTIVE", "RESISTOR", ...)
    token = strtok(NULL, delimiters);
    if (!token) {
        printf("Failure, terminating program.\n");
        exit(EXIT_FAILURE);
    }
    if (strcmp(token, "ACTIVE") == 0)         ComponentList[g_LineIndex].Type = ACTIVE;
    else if (strcmp(token, "RESISTOR") == 0)  ComponentList[g_LineIndex].Type = RESISTOR;
    else if (strcmp(token, "CAPACITOR") == 0) ComponentList[g_LineIndex].Type = CAPACITOR;
    else if (strcmp(token, "INDUCTOR") == 0)  ComponentList[g_LineIndex].Type = INDUCTOR;
    else {
        printf("Error: Unknown component type '%s'\n", token);
        exit(EXIT_FAILURE);
    }

    // Get Value (function ptr for active, else float literal)
    token = strtok(NULL, delimiters); // Contains "SIN(5,100)" or "100.0f"
    if (!token) {
        printf("Failure, terminating program.\n");
        exit(EXIT_FAILURE);
    }
    if (ComponentList[g_LineIndex].Type == ACTIVE) {
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
        ComponentList[g_LineIndex].Value.ActiveFunction.ptr = NULL;
        int i = 0;
        for (i = 0; g_FunctionTable[i].FuncPtr != NULL; i++) {
            if (strcmp(g_FunctionTable[i].Name, FuncNameStr) == 0) {
                ComponentList[g_LineIndex].Value.ActiveFunction.ptr = g_FunctionTable[i].FuncPtr;
                break;
            }
        }
        if (ComponentList[g_LineIndex].Value.ActiveFunction.ptr == NULL) {
            printf("Error: Unknown active function '%s' on line %d.\n", FuncNameStr, g_LineIndex);
            exit(EXIT_FAILURE);
        }
        ComponentList[g_LineIndex].Value.ActiveFunction.ParamsCount = 0;
        char *param_token = strtok(FuncParamStr, ",)"); // Delimit by comma or closing paren
        while (param_token != NULL) {
            if (ComponentList[g_LineIndex].Value.ActiveFunction.ParamsCount >= MAX_NUM_PARAMS) {
                printf("Error: Too many parameters for function %s\n.", FuncNameStr);
                exit(EXIT_FAILURE);
            }
            ComponentList[g_LineIndex].Value.ActiveFunction.Params[ComponentList[g_LineIndex].Value.ActiveFunction.ParamsCount] = strtof(param_token, NULL);
            ComponentList[g_LineIndex].Value.ActiveFunction.ParamsCount++;
            param_token = strtok(NULL, ",)");
        }
        } 
    else {
        // Parse float for RESISTOR, CAPACITOR, INDUCTOR
        char *endptr;
        // Give float literal to component nominal value
        ComponentList[g_LineIndex].Value.Nominal = strtof(token, &endptr);     
        // Fail if no number found (token == endptr)
        // Fail if characters remain that aren't just 'f' (e.g., "10Ohm" fails)
        if (token == endptr || (*endptr != '\0' && (*endptr != 'f' || *(endptr + 1) != '\0'))) {
            printf("Error: Invalid value '%s'. Units are not allowed.\n", token);
            exit(EXIT_FAILURE);
        }
    }
/*
    // Parse Positive Node
    token = strtok(NULL, delimiters);
    if (!token) return -1;
    strncpy(ComponentList[g_LineIndex].NodePos, token, sizeof(ComponentList[g_LineIndex].NodePos) - 1);

    // 5. Parse Negative Node
    token = strtok(NULL, delimiters);
    if (!token) return -1;
    strncpy(ComponentList[g_LineIndex].NodeNeg, token, sizeof(ComponentList[g_LineIndex].NodeNeg) - 1);
*/
}


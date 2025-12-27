#include "nodelut.h" // For size macros
/*
// Function table declaration
FunctionMapping_t g_FunctionTable[] = {
    { "SIN",    func_SIN },
    { "SQUARE", func_SQUARE },
    { "PULSE",  func_PULSE },
    { "DC",     func_DC },
    { "",       NULL }
};
*/
LabelMapEntry_t *g_NodeTable = NULL;
// Allocate memory for NodeTable and populate entries
void NODELUT_MakeNodeTable() {
    // Allocate an entry for each node
    g_NodeTable = (LabelMapEntry_t *) calloc(g_NumNodesUnique, sizeof(LabelMapEntry_t));
    // Build map alphabetically
    int i = 0;
    char c = 'A';
    // If c is in acceptable range
    while ((c >= 'A') && (c <= 'Z')) {
        for (i = 0; i < g_NumNodesUnique; i++) {
            // Copy node label string
            strcpy(g_NodeTable[i].Name, g_NodeList[i].Label);
            // Map to current capital letter
            g_NodeTable[i].Letter = c;
            c++;
        }
        // Avoid infite loop
        break;
    }
}
// FOR TESTING: PRINT ALL PAIRS IN NODE TABLE
void NODELUT_PrintNodeTable() {
    int i = 0;
    for (i = 0; i < g_NumNodesUnique; i++) {
        printf("Node Table:\n");
        printf("\t%s  |   %c\n", g_NodeTable[i].Name, g_NodeTable[i].Letter);
    }
}

#ifndef NODESOLVE_H
#define NODESOLVE_H
// This is the top level file of the circuit solving hierarchy
#include "msnlparser.h"
#include "imaginarymath.h"
extern Branch_t *g_BranchList;
extern int g_BranchIndex;

void NODESOLVE_MapNodeConnections();
void NODESOLVE_PrintNodeConnections(Node_t *target);
void NODESOLVE_MakeBranchList();
void NODESOLVE_ComputeBranchImpedances();
void NODESOLVE_PrintAllBranchImpedances();
void NODESOLVE_PrintAllBranchNodes();
void NODESOLVE_MakeNodeMatrix();
void NODESOLVE_PopulateNodeMatrix();
void NODESOLVE_PrintNodeMatrix();

typedef struct {
    // Real and imaginary parts (Z = a + jb)
    float a, b;
} ZNum_t;

typedef struct {
    // Row (array) of ZNums
    ZNum_t *Element;
} ZNumRow_t;
// This points to an element of the row
extern ZNum_t *g_NodeMatrixCol;
// This points to an array (row)
extern ZNumRow_t *g_NodeMatrixRow;













#endif // Header define

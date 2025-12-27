#ifndef NODESOLVE_H
#define NODESOLVE_H
// This is the top level file of the circuit solving hierarchy
#include "msnlparser.h"

extern Branch_t *g_BranchList;
extern int g_BranchIndex;

void NODESOLVE_MapNodeConnections();
void NODESOLVE_PrintNodeConnections(Node_t *target);
void NODESOLVE_MakeBranchList();
void NODESOLVE_ComputeBranchImpedances();
void NODESOLVE_PrintAllBranchImpedances();
void NODESOLVE_PrintAllBranchNodes();















#endif // Header define

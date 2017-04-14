#pragma once
char** GraphToMatrix(Graph<DijVertex> &g);
void ClearMatrix(char*** m, int n);
void PrintMatrix(char** m, int n, FILE*out = NULL);
void MatrixToTransitiveClosure(char **a, int n);

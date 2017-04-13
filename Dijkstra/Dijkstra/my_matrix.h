#pragma once
bool** GraphToMatrix(Graph<DijVertex> g);
void ClearMatrix(bool** m, int n);
void PrintMatrix(bool** m, int n);
void MatrixToTransitiveClosure(bool **a, int n);

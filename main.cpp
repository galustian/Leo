#include <iostream>
#include "core.h"

using namespace std;
using namespace Leo;

int main() {
    Matrix<float, Dynamic, Dynamic> dynMat(4, 3);
    cout << dynMat.kRowsAtCompileTime << endl;

    Matrix<float, 3, 7> mat;
    cout << mat.kColsAtCompileTime << endl;

    return 0;
}
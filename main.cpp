#include <iostream>
#include "core.h"

using namespace std;
using namespace Leo;

int main() {
    Matrix<float, Dynamic, Dynamic> dynMat(4, 3);
    cout << dynMat.kRowsAtCompileTime << endl;

    Matrix<float, 3, 7> mat;
    cout << mat.kColsAtCompileTime << endl;

    auto& val = dynMat(2, 2);
    cout << val << endl;
    
    dynMat(2, 2) = 45;

    cout << dynMat(2, 2) << endl;
    cout << val << endl;

    return 0;
}
#include <iostream>
#include "core.h"

using namespace std;
using namespace Leo;

int main() {
    auto randMat = Matrix<double, 4, 6>::Random();

    cout << randMat << endl;

    Matrix<double, 2, 3> myMat;

    auto list = {
        2.0, 4.5, 454566.8,
        4.4, 45.0, 45.45
    };
    myMat << list;

    cout << myMat << endl;

    return 0;
}
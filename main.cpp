#include <iostream>
#include "core.h"

using namespace std;
using namespace Leo;

int main() {
    auto randMat = Matrix<float, 18, 18>::Random();

    cout << randMat << endl;

    Matrix<double, 3, 4> myMat;

    auto list = {
        2., 6., 4., 8.,
        4., 44., 48., 24.,
        8., 4., 40., 22.
    };
    myMat << list;

    cout << myMat << endl;

    myMat.EchelonForm();
    randMat.EchelonForm();

    cout << myMat << endl;
    cout << randMat << endl;

    return 0;
}
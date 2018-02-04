#include <iostream>
#include "core.h"

using namespace std;
using namespace Leo;

int main() {
    auto randMat = Matrix<float, 10, 8>::Random();

    cout << randMat << endl;

    Matrix<double, 3, 4> myMat;

    auto list = {
        0., 6., 4., 8.,
        4., 0., 48., 24.,
        8., 4., 40., 22.
    };
    myMat << list;

    cout << myMat << endl;

    
    

    cout << myMat.EchelonForm() << endl;
    cout << randMat.EchelonForm() << endl;

    return 0;
}
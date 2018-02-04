#include <iostream>
#include "core.h"

using namespace std;
using namespace Leo;

int main() {
    auto randMat = Matrix<float, 10, 8>::Random();

    Matrix<double, 3, 4> myMat;

    auto list = {
        10., 6., 4., 8.,
        4., 0., 48., 24.,
        8., 4., 40., 22.
    };
    myMat << list;

    cout << myMat.EchelonForm() << endl;

    double val = myMat.EchelonForm()(2, 3);
    cout << val << endl;
    
    //cout << myMat.EchelonForm()(2, 0) << endl << endl;

    cout << myMat.ReducedEchelonForm() << endl;
    
    return 0;
}
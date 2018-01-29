#include <iostream>
#include "core.h"

using namespace std;
using namespace Leo;

int main() {
    auto randMat = Matrix<double, 4, 6>::Random();

    cout << randMat << endl;

    return 0;
}
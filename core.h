#ifndef CORE_H
#define CORE_H

//#include <type_traits>
#include <array>
#include <vector>

using namespace std;

namespace Leo {

    static constexpr long Dynamic = -1;
    
    template<typename T, long Rows, long Cols>
    class Matrix {
        private:
            enum {
                kIsDynamicStorage = Rows == Dynamic || Cols == Dynamic
            };

            //conditional<is_dynamic_storage, vector<vector<T>>, T[Rows][Cols]>::type storage;
            //T storage[kIsDynamicStorage ? 0: Rows][kIsDynamicStorage ? 0: Cols];
            array<array<T, kIsDynamicStorage ? 0: Cols>, kIsDynamicStorage ? 0: Rows> storage;

            vector<vector<T>> dynamic_storage;

        public:
            enum {
                kRowsAtCompileTime = Rows,
                kColsAtCompileTime = Cols
            };
            

            Matrix();
            // Matrix(long dims);
            Matrix(size_t rows, size_t cols);
            // TODO ~Matrix();
            // void T();
            // auto coef_type();

    };
}

#include "core.cpp"

#endif
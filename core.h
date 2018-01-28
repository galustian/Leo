#ifndef CORE_H
#define CORE_H

#include <array>
#include <vector>
#include <type_traits>

using namespace std;

namespace Leo {

    static const long Dynamic = -1;
    
    template<typename T, long Rows, long Cols>
    class Matrix {
        private:
            enum {
                kIsDynamicStorage = Rows == Dynamic || Cols == Dynamic
            };

            typename conditional<kIsDynamicStorage, 
                                vector<vector<T>>, 
                                array<array<T, Cols>, Rows>>::type storage;

        public:
            enum {
                kRowsAtCompileTime = Rows,
                kColsAtCompileTime = Cols
            };

            Matrix();
            Matrix(size_t rows, size_t cols);
            
            //template <bool DS = kIsDynamicStorage>
            T& operator() (long row_i, long col_i);
            //enable_if_t<!kIsDynamicStorage, array<array<T, Cols>, Rows>> operator() (long row_i, long col_i);
            //auto operator() (long row_i, long col_i);

            // TODO
            // operator<<
            // Random(4, 3)
            // RandomNormal(4, 3)
            // Matrix(long dims);
            // TODO ~Matrix();
            // void T();
    };
}

#include "core.cpp"

#endif
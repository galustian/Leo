#pragma once

#include <array>
#include <vector>
#include <initializer_list>
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
            Matrix(long rows, long cols);
            
            T& operator() (long row_i, long col_i);
            void operator<< (initializer_list<T>& coefficients);
            
            template <typename T1, long Rows1, long Cols1>
            friend ostream& operator<< (ostream& os, const Matrix<T1, Rows1, Cols1>& mat) ;


            static Matrix<T, Rows, Cols> Random();
 
            
            // TODO
            // RandomNormal(4, 3)
            // Matrix(long dims);
            // TODO ~Matrix();
            // void T();
    };
}

#include "core.cpp"
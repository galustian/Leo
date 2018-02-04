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
            
            // HELPERS
            void RowReduce(long reduced_row_i, long row_i, long pivot_col_i);
            bool OnlyZerosBelow(long row_i, long col_i) const;
            void ReorderRowsIfZeroAtTop(long top_row_i, long col_i);

        public:
            enum {
                kRowsAtCompileTime = Rows,
                kColsAtCompileTime = Cols
            };

            Matrix();
            Matrix(long rows, long cols);

            auto EchelonForm();
            auto ReducedEchelonForm();
            T GetPivotRowValue(long row_i);
            long GetPivotColumnPosition(long row_i);
            
            T& operator() (long row_i, long col_i);
            void operator<< (initializer_list<T>& coefficients);
            
            static auto Random();
            
            template <typename T1, long Rows1, long Cols1>
            friend ostream& operator<< (ostream& os, const Matrix<T1, Rows1, Cols1>& mat);
 
            
            // TODO
            //Matrix operator* (Matrix mat);
            // Matrix Inverse
            // Slicing wiht initializer_list [{1, 2}, {0, -1}]
            // Multithreading Support
            // auto T();
            // RandomNormal(4, 3)
            // Matrix(long dims);
    };
}

#include "core.cpp"
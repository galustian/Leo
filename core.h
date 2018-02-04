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
            
            bool is_zero_column(long col_i) const;
            void reorder_rows_if_zero_at_top(long top_row_i, long col_i);
            template <typename V>
            void element_wise_reduction(V& below_row, V& top_row, double row_multiplier);

        public:
            enum {
                kRowsAtCompileTime = Rows,
                kColsAtCompileTime = Cols
            };

            Matrix();
            Matrix(long rows, long cols);

            void EchelonForm();
            
            T& operator() (long row_i, long col_i);
            void operator<< (initializer_list<T>& coefficients);
            
            static Matrix<T, Rows, Cols> Random();
            
            template <typename T1, long Rows1, long Cols1>
            friend ostream& operator<< (ostream& os, const Matrix<T1, Rows1, Cols1>& mat);
 
            
            // TODO
            // RandomNormal(4, 3)
            // Matrix(long dims);
            // TODO ~Matrix();
            // void T();
    };
}

#include "core.cpp"
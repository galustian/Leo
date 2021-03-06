#include <algorithm>
#include <random>
#include <cmath>
#include "core.h"

#define IS_DYNAMIC_ASSERT(is_dynamic) static_assert(kIsDynamicStorage, "This method is intended for dynamic storage");
#define NOT_DYNAMIC_ASSERT(is_dynamic) static_assert(!kIsDynamicStorage, "This method is intended for fixed storage");

using namespace std;

namespace Leo {
    #include "core_helpers.cpp"

    template <typename T, long Rows, long Cols>
    Matrix<T, Rows, Cols>::Matrix() {}
    
    template <typename T, long Rows, long Cols>
    Matrix<T, Rows, Cols>::Matrix(long rows, long cols) {
        IS_DYNAMIC_ASSERT(kIsDynamicStorage)
        
        storage.resize(rows);
        for(auto& row: storage) row.resize(cols);
    }

    template <typename T, long Rows, long Cols>
    auto Matrix<T, Rows, Cols>::EchelonForm() {
        auto mat = *this;
        
        long top_row_i {0};

        for (long col_i = 0; col_i < Cols; col_i++) {            
            if (top_row_i == Rows-1) break;
            if (mat.OnlyZerosBelow(top_row_i, col_i)) continue;

            mat.ReorderRowsIfZeroAtTop(top_row_i, col_i);
            
            // REDUCE ROWS BELOW top_row
            const auto& top_row = mat.storage[top_row_i];
            for (long row_i = top_row_i+1; row_i < Rows; row_i++) {               
                mat.RowReduce(row_i, top_row_i, col_i);
            }

            top_row_i++;
        }
        return mat;
    }

    template <typename T, long Rows, long Cols>
    auto Matrix<T, Rows, Cols>::ReducedEchelonForm() {
        auto mat = this->EchelonForm();

        for (long bottom_row_i = Rows-1; bottom_row_i != -1; bottom_row_i--) {
            auto& bottom_row = mat.storage[bottom_row_i];
            
            if (IsZeroRow(bottom_row)) continue;

            long pivot_col_i = mat.GetPivotColumnPosition(bottom_row_i);
            T pivot_value = mat.GetPivotRowValue(bottom_row_i);
            cout << pivot_col_i << endl;
            cout << "Val." << pivot_value << endl;

            // UNIT SCALE bottom_row
            for (T& coeff: bottom_row) {
                coeff /= pivot_value;
            }

            // REDUCE ROWS ABOVE bottom_row
            for (long row_i = bottom_row_i-1; row_i != -1; row_i--) {
                mat.RowReduce(row_i, bottom_row_i, pivot_col_i);
            }
        }

        return mat;
    }

    
    template <typename T, long Rows, long Cols>
    T& Matrix<T, Rows, Cols>::operator() (long row_i, long col_i) {
        return storage[row_i][col_i];
    }

    template <typename T, long Rows, long Cols>
    auto Matrix<T, Rows, Cols>::Random() {
        NOT_DYNAMIC_ASSERT(kIsDynamicStorage)

        Matrix<T, Rows, Cols> randomMat;

        random_device seed;
        mt19937 rand_gen(seed());
        uniform_real_distribution<T> rand_uniform(0, 1);

        for (auto& arr: randomMat.storage) {
            for (long i = 0; i < arr.size(); i++) {
                arr[i] = rand_uniform(rand_gen);
            }
        }

        return randomMat;
    }

    template <typename T1, long Rows1, long Cols1>
    ostream& operator<< (ostream& os, const Matrix<T1, Rows1, Cols1>& mat) {
        for (auto& stor: mat.storage) {
            for (long i = 0; i < stor.size(); i++) {
                T1 val = (int)(stor[i] * 100 + .5);
                os << (T1)val / 100;
                
                if (i + 1 != stor.size()) {
                    os << ", ";
                }
            }
            os << "\n";
        }
        return os;
    }

    template <typename T, long Rows, long Cols>
    void Matrix<T, Rows, Cols>::operator<< (initializer_list<T>& coefficients) {
        long i {0};

        for (auto const& coeff: coefficients) {
            long row_i = i / Cols;
            long col_i = i % Cols;

            storage[row_i][col_i] = coeff;
            i++;
        }
    }

} // end namespace Leo
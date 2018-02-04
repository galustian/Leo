#include <algorithm>
#include <cmath>
#include <random>
#include "core.h"

#define IS_DYNAMIC_ASSERT(is_dynamic) static_assert(kIsDynamicStorage, "This method is intended for dynamic storage");
#define NOT_DYNAMIC_ASSERT(is_dynamic) static_assert(!kIsDynamicStorage, "This method is intended for fixed storage");

using namespace std;

namespace Leo {
    template <typename T, long Rows, long Cols>
    Matrix<T, Rows, Cols>::Matrix() {}
    
    template <typename T, long Rows, long Cols>
    Matrix<T, Rows, Cols>::Matrix(long rows, long cols) {
        IS_DYNAMIC_ASSERT(kIsDynamicStorage)
        
        storage.resize(rows);
        for(auto& row: storage) row.resize(cols);
    }

    template <typename T, long Rows, long Cols>
    void Matrix<T, Rows, Cols>::EchelonForm() {
        long top_row_i = 0;

        for (long col_i = 0; col_i < storage[0].size(); col_i++) {            
            if (top_row_i == Rows-1) break;
            if (is_zero_column(col_i)) continue;

            reorder_rows_if_zero_at_top(top_row_i, col_i);
            
            // REDUCE ROWS BELOW top_row
            auto top_row = storage[top_row_i];
            for (long row_i = top_row_i+1; row_i < Rows; row_i++) {
                auto& below_row = storage[row_i];
                
                double row_multiplier = below_row[col_i] / top_row[col_i]; 
                element_wise_reduction(below_row, top_row, row_multiplier);
            }

            ++top_row_i;
        }
    }
    // TODO create header-file for helpers
    /*-------------------------------------------- HELPERS START --------------------------------------------*/
    template <typename T, long Rows, long Cols>
    bool Matrix<T, Rows, Cols>::is_zero_column(long col_i) const {
        for (auto& row: storage) {
            if (row[col_i] != 0) return false;
        } 
        return true;
    }


    template <typename T, long Rows, long Cols>
    void Matrix<T, Rows, Cols>::reorder_rows_if_zero_at_top(long top_row_i, long col_i) {
        if (storage[top_row_i][col_i] != 0) return;
        
        // CHOOSE ROW WITH LARGEST ABSOLUTE COEFFICIENT TO REDUCE ROUNDOFF ERRORS
        long abs_largest_coeff {0};
        long i_row_largest_coeff {0};

        for (long row_i = top_row_i+1; row_i < storage.size(); row_i++) {
            const T coeff = storage[row_i][col_i];
            if (coeff != 0 && abs(coeff) > abs_largest_coeff) {
                abs_largest_coeff = coeff;
                i_row_largest_coeff = row_i;
            }
        }
        swap(storage[top_row_i], storage[i_row_largest_coeff]);
    }

    template <typename T, long Rows, long Cols>
    template <typename V>
    void Matrix<T, Rows, Cols>::element_wise_reduction(V& below_row, V& top_row, double row_multiplier) {
        for (long i = 0; i < below_row.size(); i++) 
            below_row[i] -= row_multiplier * top_row[i];
    }

    /*-------------------------------------------- HELPERS END --------------------------------------------*/



    template <typename T, long Rows, long Cols>
    T& Matrix<T, Rows, Cols>::operator() (long row_i, long col_i) {
        return storage[row_i][col_i];
    }

    template <typename T, long Rows, long Cols>
    Matrix<T, Rows, Cols> Matrix<T, Rows, Cols>::Random() {
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
        long row_i;
        long col_i;
        long i {0};

        for (auto const& coeff: coefficients) {
            row_i = i / Cols;
            col_i = i % Cols;

            storage[row_i][col_i] = coeff;
            ++i;
        }
    }
}
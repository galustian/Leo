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
        for(auto& vec: storage) vec.resize(cols);
    }

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
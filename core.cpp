#include <type_traits>
#include "core.h"

using namespace std;

namespace Leo {
    template <typename T, long Rows, long Cols>
    Matrix<T, Rows, Cols>::Matrix() {}
    
    template <typename T, long Rows, long Cols>
    Matrix<T, Rows, Cols>::Matrix(size_t rows, size_t cols) {
        static_assert(kIsDynamicStorage, "This constructor is intended for dynamic storage initialization");
        
        storage.resize(rows);
        for (auto& vec: storage) vec.resize(cols);
    }

    template <typename T, long Rows, long Cols>
    T& Matrix<T, Rows, Cols>::operator() (long row_i, long col_i) {
        return storage[row_i][col_i];
    }
}
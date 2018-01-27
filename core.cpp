#include "core.h"

namespace Leo {
    template<typename T, long Rows, long Cols>
    Matrix<T, Rows, Cols>::Matrix() {}
    
    template<typename T, long Rows, long Cols>
    Matrix<T, Rows, Cols>::Matrix(size_t rows, size_t cols) {
        static_assert(kIsDynamicStorage, "This constructor is intended for dynamic storage initialization");
        
        dynamic_storage.reserve(rows);
        for (auto& vec: dynamic_storage) vec.reserve(cols);
    }

    /*auto MatirxBase::get_type() {
        return typeid()
    }*/
}
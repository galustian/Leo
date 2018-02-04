template <typename V>
bool IsZeroRow(const V& row) {
    for (auto coeff: row)
        if (coeff != 0) return false;
    
    return true;
}

template <typename T, long Rows, long Cols>
bool Matrix<T, Rows, Cols>::OnlyZerosBelow(long top_row_i, long col_i) const {
    for (long i = top_row_i+1; i < storage.size(); i++) {
        if (storage[i][col_i] != 0) return false;
    }
    return true;
}

template <typename T, long Rows, long Cols>
void Matrix<T, Rows, Cols>::ReorderRowsIfZeroAtTop(long top_row_i, long col_i) {
    if (storage[top_row_i][col_i] != 0) return;
    
    // Partial Pivoting => CHOOSE ROW WITH LARGEST ABSOLUTE COEFFICIENT TO REDUCE ROUNDOFF ERRORS
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
void Matrix<T, Rows, Cols>::RowReduce(long reduced_row_i, long row_i, long pivot_col_i) {
    auto& reduced_row = storage[reduced_row_i];
    const auto& row = storage[row_i];
    
    double row_multiplier = reduced_row[pivot_col_i] / row[pivot_col_i];  
    
    for (long i = 0; i < Cols; i++) 
        reduced_row[i] -= row_multiplier * row[i];    
}

template <typename T, long Rows, long Cols>
T Matrix<T, Rows, Cols>::GetPivotRowValue(long row_i) {
    for (T coeff: storage[row_i]) {
        if (coeff != 0.0) return coeff;
    }
    throw "Row has no Pivot";
}

template <typename T, long Rows, long Cols>
long Matrix<T, Rows, Cols>::GetPivotColumnPosition(long row_i) {
    for (long col_i = 0; col_i < Cols; col_i++) {
        if (storage[row_i][col_i] != 0.0) return col_i;
    }
    throw "Row has no Pivot";
}
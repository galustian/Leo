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

#ifndef math_library
#define math_library

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

struct matrix;
void free_matrix (struct matrix *target);
struct matrix *create_matrix (int row_count, int col_count, double *contents, int element_count);
struct matrix *change_matrix_dimensions (struct matrix *target, int new_row_count, int new_col_count);
struct matrix *matrix_addition (struct matrix *target1, struct matrix *target2);
struct matrix *matrix_multiplication (struct matrix *target1, struct matrix *target2);
char *matrix_to_string (struct matrix *target);
bool compare_matrices (struct matrix *target1, struct matrix *target2);

#endif
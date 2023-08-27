#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


struct matrix {
    int row_count;
    int col_count;
    double **contents;
};


void free_matrix (struct matrix *target) {
    /***************************
    Frees the dynamically allocated matrix, and all of its contents.

    Make sure that the contents are set to NULL if they have already
    been freed before calling this function.
    ****************************/

    if (target == NULL) {
        return;
    }
    else if (target->contents == NULL) {
        free(target);
        return;
    }
    
    for (int i = 0; i < target->row_count; i++) {
        free(target->contents[i]);
    }
    free(target->contents);
    free(target);
}


struct matrix *create_matrix (int row_count, int col_count, double *contents, int element_count) {
    /********************************************************************************
    Creates a non-empty matrix of Real-Valued numbers. Must be freed.

    element_count should be given as sizeof contents / sizeof contents[0]

    Input parameters:
        - row amount
        - column amount
        - array of the elements
        - size of the array
    Return value:
        - If successfull: struct matrix *
        - Malloc error: NULL
        - Parameter error: NULL
    *********************************************************************************/

    if (!(row_count > 0 && col_count > 0)) {
        fprintf(
            stderr,
            "ERROR create_matrix(): Dimensions %d %d unacceptable\n",
            row_count, col_count
        );
        return NULL;
    }

    if (element_count != (row_count * col_count)) {
        fprintf(
            stderr,
            "ERROR create_matrix(): Size of contents %d unacceptable with dimensions %d %d\n",
            element_count, row_count, col_count
        );
        return NULL;
    }

    if (contents == NULL) {
        fprintf(
            stderr,
            "ERROR create_matrix(): contents cannot be NULL"
        );
        return NULL;
    }

    // Defining the struct and rows of the matrix
    struct matrix *result = (struct matrix *) malloc(sizeof(struct matrix));
    if (result == NULL) {
        return NULL;
    }
    result->row_count = row_count;
    result->col_count = col_count;

    double **result_contents = (double **) malloc(sizeof(double *) * row_count);
    if (result_contents == NULL) {
        free(result);
        return NULL;
    }
    result->contents = result_contents;

    // Defining the columns of the matrix
    bool malloc_fail = false;
    for (int i = 0; i < row_count; i++) {
        if (!malloc_fail) {
            result->contents[i] = (double *) malloc(sizeof(double) * col_count);
            if (result->contents[i] == NULL) {
                malloc_fail = true;
            }
        }
        else {
            result->contents[i] = NULL;
        }
    }
    if (malloc_fail) {
        free_matrix(result);
        return NULL;
    }

    // Filling in the contents and returning successfully
    for (int i = 0; i < row_count; i++) {
        for (int j = 0; j < col_count; j++) {
            int correct_index = j;
            correct_index += i * col_count;
            result->contents[i][j] = contents[correct_index];
        }
    }
    return result;
}


struct matrix *change_matrix_dimensions (struct matrix *target, int new_row_count, int new_col_count) {
    /********************************************************************************
    Changes the dimensions of a matrix to the newly specified dimensions. Must be freed.

    The new dimensions must match the old dimensions.
    This function does not free the old matrix.

    Input parameters:
        - the target matrix
        - new row amount
        - new column amount
    Return value:
        - If successfull: new and updated struct matrix *
        - Malloc error: NULL
        - Parameter error: NULL
    *********************************************************************************/

    if (target == NULL) {
        fprintf(
            stderr,
            "ERROR change_matrix_dimensions(): target cannot be NULL"
        );
        return NULL;
    }

    int old_row_count = target->row_count;
    int old_col_count = target->col_count;

    if (old_row_count * old_col_count != new_row_count * new_col_count) {
        fprintf(
            stderr,
            "ERROR change_matrix_dimensions(): new dimensions (%d %d) do not match old dimensions (%d %d)",
            new_row_count, new_col_count, old_row_count, old_col_count
        );
        return NULL;
    }

    // Creating a one dimensional array representation of the contents
    int size = target->row_count * target->col_count;
    double contents[size];

    for (int i = 0; i < target->row_count; i++) {
        for (int j = 0; j < target->col_count; j++) {
            contents[j + (i * target->col_count)] = target->contents[i][j];
        }
    }
    return create_matrix(new_row_count, new_col_count, contents, size);
}


struct matrix *matrix_addition (struct matrix *target1, struct matrix *target2) {
    /********************************************************************************
    Performs addition between two matrices of the same dimensions. Result must be freed.

    Input parameters:
        - the first matrix
        - the second matrix
    Return value:
        - If successfull: new struct matrix *
        - Malloc error: NULL
        - Parameter error: NULL
    *********************************************************************************/

    if (target1 == NULL || target2 == NULL) {
        fprintf(
            stderr,
            "ERROR matrix_addition(): targets cannot be NULL"
        );
        return NULL;
    }

    int row1 = target1->row_count;
    int col1 = target1->col_count;
    int row2 = target2->row_count;
    int col2 = target2->col_count;

    if (row1 != row2 || col1 != col2) {
        fprintf(
            stderr,
            "ERROR matrix_addition(): target1 dim: %d %d not compatible with target2 dim: %d %d\n",
            row1, col1, row2, col2
        );
        return NULL;
    }

    // Performing addition
    int size = row1 * col1;
    double result_contents[size];

    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < col1; j++) {
            result_contents[(i * col1) + j] = target1->contents[i][j] + target2->contents[i][j];
        }
    }
    return create_matrix(row1, col1, result_contents, size);
}


struct matrix *matrix_multiplication (struct matrix *target1, struct matrix *target2) {
    /********************************************************************************
    Performs multiplication between two matrices. Result must be freed.

    The row amount of the first matrix must match the column amount
    of the second matrix. The multiplication is performed as shown below,
    with target1 as x, target2 as y, and the result as z.

                                    | y y y y y y y
                                    | y y y y y y y
                                    | y y y y y y y
                    ---------------------------------
                              x x x | z z z z z z z
                              x x x | z z z z z z z

    Input parameters:
        - the first matrix
        - the second matrix
    Return value:
        - If successfull: new struct matrix *
        - Malloc error: NULL
        - Parameter error: NULL
    *********************************************************************************/

    if (target1 == NULL || target2 == NULL) {
        fprintf(
            stderr,
            "ERROR matrix_multiplication(): targets cannot be NULL"
        );
        return NULL;
    }

    int row1 = target1->row_count;
    int col1 = target1->col_count;
    int row2 = target2->row_count;
    int col2 = target2->col_count;

    if (col1 != row2) {
        fprintf(
            stderr,
            "ERROR matrix_multiplication(): target1 row_count (%d) must equal target2 col_count (%d)\n",
            row1, col2
        );
        return NULL;
    }

    // Performing matrix multiplication
    int size = row1 * col2;
    double result_contents[size];

    for (int a = 0; a < row1; a++) {  // Row vector
        for (int b = 0; b < col2; b++) {  // Column vector

            // Vector multiplication
            double sum = 0;
            for (int c = 0; c < col1; c++) {
                sum += target1->contents[a][c] * target2->contents[c][b];
            }
            result_contents[(a * col2) + b] = sum;
        }
    }
    return create_matrix(row1, col2, result_contents, size);
}


char *matrix_to_string (struct matrix *target) {
    /**************************************************************
    Creates a printable string version of a matrix. The string must be freed.

    The string will have this form:

    |0.000  0.000  0.000  0.000  |\n
    |0.000  0.000  0.000  0.000  |\n
    |0.000  0.000  0.000  0.000  |\n\0

    Input parameters:
        - the target matrix
    Return value:
        - If successfull: string of the matrix
        - Malloc error: NULL
        - Parameter error: NULL
    ***************************************************************/

    if (target == NULL) {
        fprintf(
            stderr,
            "ERROR matrix_to_string: target cannot be NULL\n"
        );
        return NULL;
    }

    // Converts all matrix elements to strings
    int size = target->row_count * target->col_count;
    char *contents_to_strings[size];

    bool malloc_fail = false;
    int max_string_size = 0;  // excluding nullbyte
    for (int i = 0; i < target->row_count; i++) {
        for (int j = 0; j < target->col_count; j++) {
            int correct_index = j;
            correct_index += i * target->col_count;

            if (!malloc_fail) {
                // Allocates space for string, and inserts a string version of the double
                contents_to_strings[correct_index] = (char *) malloc(sizeof(char) * 100);
                if (contents_to_strings[correct_index] == NULL) {
                    malloc_fail = true;
                }
                else {
                    int str_len = sprintf(
                        contents_to_strings[correct_index],
                        "%0.3f",
                        target->contents[i][j]
                    );
                    if (str_len > max_string_size) {
                        max_string_size = str_len;
                    }
                }
            }
            else {
                // Sets all pointers to NULL, thus allowing free() on every element
                contents_to_strings[correct_index] = NULL;
            }
        }
    }
    if (malloc_fail) {
        for (int i = 0; i < size; i++) {
            free(contents_to_strings[i]);
        }
        return NULL;
    }

    // Makes all of those strings equal in length
    int new_string_size = max_string_size + 2;  // add 2 whitespaces before the nullbyte

    for (int i = 0; i < size; i++) {
        char *old_string = contents_to_strings[i];

        if (!malloc_fail) {
            // Prepares adequate space for updated string
            char *new_string = (char *) malloc(sizeof(char) * (new_string_size + 1));  // remember nullbyte
            if (new_string == NULL) {
                malloc_fail = true;
            }
            else {
                new_string = strcpy(new_string, old_string);

                // Fills in whitespaces between the string and the final nullbyte
                bool nullbyte_reached = false;
                for (int j = 0; j <= new_string_size; j++) {
                    if (!nullbyte_reached && new_string[j] == '\0' && (j < new_string_size)) {
                        nullbyte_reached = true;
                    }
                    if (nullbyte_reached && (j < new_string_size)) {
                        new_string[j] = ' ';
                    }
                    else if (j == new_string_size) {
                        new_string[j] = '\0';
                    }
                }
            }
            // Updates the string directly and frees the old string
            contents_to_strings[i] = new_string;
            free(old_string);
        }
        else {
            // Sets all pointers to NULL, thus allowing free() on every element
            free(old_string);
            contents_to_strings[i] = NULL;
        }
    }
    if (malloc_fail) {
        for (int i = 0; i < size; i++) {
            free(contents_to_strings[i]);
        }
        return NULL;
    }

    // Inserts all of the strings into one huge string
    int result_size = target->row_count * target->col_count * new_string_size;
    result_size += target->row_count * 3 + 1;  // | \n and \0
    char result[result_size];

    result[result_size - 1] = '\0';

    for (int i = 0; i < target->row_count; i++) {
        for (int j = 0; j < target->col_count; j++) {
            // Index for contents_to_strings
            int correct_index1 = j + (i * target->col_count);

            // Index for result
            int correct_index2 = j * new_string_size + 1;  // starts at 1
            correct_index2 += i * (target->col_count * new_string_size);  // row offset
            correct_index2 += i * 3;  // row offset considering brackets and newlines

            // Inserts the string into result
            char *string_to_insert = contents_to_strings[correct_index1];
            for (int k = 0; k < new_string_size; k++) {
                result[k + correct_index2] = string_to_insert[k]; 
            }
        }

        // Inserts brackets
        int bracket_index1 = i * (target->col_count * new_string_size);  // row offset
        bracket_index1 += i * 3;  // row offset considering brackets and newlines
        int bracket_index2 = bracket_index1 + (target->col_count * new_string_size) + 1;
        result[bracket_index1] = '|';
        result[bracket_index2] = '|';

        // Inserts newlines
        int newline_index = i * (target->col_count * new_string_size);  // row offset
        newline_index += i * 3;  // row offset considering brackets and newlines
        newline_index += (target->col_count * new_string_size) + 2;
        result[newline_index] = '\n';
    }

    // Remember to free the array of dynamically allocated strings
    for (int i = 0; i < size; i++) {
        free(contents_to_strings[i]);
    }
    
    return strdup(result);  // returns NULL if malloc error
}


bool compare_matrices (struct matrix *target1, struct matrix *target2) {
    /*************************************************
    Check whether or not the two matrices are equal.

    They are only considered equal if their contents and dimensions match.

    Input parameters:
        - the first matrix
        - the second matrix
    Return value:
        - If equal: true
        - If inequal: false
        - Parameter error: NULL
    ***************************************************/

    if (target1 == NULL || target2 == NULL) {
        fprintf(
            stderr,
            "ERROR compare_matrices(): targets cannot be NULL"
        );
        return NULL; // might have to change this one
    }

    // Compares dimensions
    int row1 = target1->row_count;
    int col1 = target1->col_count;
    int row2 = target2->row_count;
    int col2 = target2->col_count;

    if (row1 != row2 || col1 != col2) {
        return false;
    }

    // Compares elements
    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < col1; j++) {
            double element1 = target1->contents[i][j];
            double element2 = target2->contents[i][j];
            double difference = element1 - element2;
            
            char str_difference[100];
            sprintf(str_difference, "%0.6f", difference);
            char str_zero[] = "0.000000";
            bool equal_check = true;

            if (str_difference[0] == '-') {
                char current = str_difference[1];
                for (int i = 1; current != '\0'; i++) {
                    if (str_difference[i] != str_zero[i - 1]) {
                        equal_check = false;
                    }
                    current = str_difference[i + 1];
                }
            }
            else {
                char current = str_difference[0];
                for (int i = 0; current != '\0'; i++) {
                    if (str_difference[i] != str_zero[i]) {
                        equal_check = false;
                    }
                    current = str_difference[i + 1];
                }
            }

            if (!equal_check) {
                //printf("\n%lf --- string: %s\n", difference, str_difference);
                //printf("target1: element %lf --- target2: element %lf\n\n", target1->contents[i][j], target2->contents[i][j]);
                return false;
            }
        }
    }
    return true;
}

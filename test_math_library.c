#include <stdio.h>
#include "math_library.h"

int test_create_matrix ();
int test_compare_matrices ();
int test_matrix_addition ();
int test_matrix_multiplication ();
int test_scalar_addition ();
int test_scalar_multiplication ();

int main (int argc, char *argv[]) {

    if (test_create_matrix()) {
        return 1;
    }

    if (test_compare_matrices()) {
        return 1;
    }

    if (test_matrix_addition()) {
        return 1;
    }

    if (test_matrix_multiplication()) {
        return 1;
    }

    return 0;
}

int test_create_matrix () {

    printf("\nTesting create_matrix()\n\n");

    // TEST 1: All positive matrix with 20 elements, dim: 4 5
    printf("TEST 1: all positive --- ");
    double test1_contents[] = {
        1, 3, 5.45, 7, 9, 11, 13, 15.221, 17, 19, 21.232,
        23, 25.2342, 27, 29.33, 31, 33.987, 35.11, 37, 39
    };
    int test1_contents_size = sizeof test1_contents / sizeof test1_contents[0];

    struct matrix *test1 = create_matrix(4, 5, test1_contents, test1_contents_size);
    if (test1 == NULL) {
        printf("FAILURE\n");
        return 1;
    }
    char *str_test1 = matrix_to_string(test1);
    if (str_test1 == NULL) {
        free_matrix(test1);
        return 1;
    }
    printf("SUCCESS\n%s\n", str_test1);
    free_matrix(test1);
    free(str_test1);

    // TEST 2: All negative matrix with 20 elements, dim: 4 5
    printf("TEST 2: all negative --- ");
    double test2_contents[] = {
        -1, -3, -5.45, -7, -9, -11, -13, -15.221, -17, -19, -21.232,
        -23, -25.2342, -27, -29.33, -31, -33.987, -35.11, -37, -39
    };
    int test2_contents_size = sizeof test2_contents / sizeof test2_contents[0];

    struct matrix *test2 = create_matrix(4, 5, test2_contents, test2_contents_size);
    if (test2 == NULL) {
        printf("FAILURE\n");
        return 1;
    }
    char *str_test2 = matrix_to_string(test2);
    if (str_test2 == NULL) {
        free_matrix(test2);
        return 1;
    }
    printf("SUCCESS\n%s\n", str_test2);
    free_matrix(test2);
    free(str_test2);

    // TEST 3: Mixed matrix with 20 elements, dim: 5 4
    printf("TEST 3: mixed --- ");
    double test3_contents[] = {
        1, -3, -5.45, 7, 9, 11, -13, -15.221, 17, -19, 21.232,
        -23, -25.2342, 27, 29.33, -31, -33.987, 35.11, 37, 39
    };
    int test3_contents_size = sizeof test3_contents / sizeof test3_contents[0];

    struct matrix *test3 = create_matrix(5, 4, test3_contents, test3_contents_size);
    if (test3 == NULL) {
        printf("FAILURE\n");
        return 1;
    }
    char *str_test3 = matrix_to_string(test3);
    if (str_test3 == NULL) {
        free_matrix(test3);
        return 1;
    }
    printf("SUCCESS\n%s\n", str_test3);
    free_matrix(test3);
    free(str_test3);

    // TEST 4: Matrix with 1 element
    printf("TEST 4: one element --- ");
    double test4_contents[] = {100.652098};
    int test4_contents_size = sizeof test4_contents / sizeof test4_contents[0];

    struct matrix *test4 = create_matrix(1, 1, test4_contents, test4_contents_size);
    if (test4 == NULL) {
        printf("FAILURE\n");
        return 1;
    }
    char *str_test4 = matrix_to_string(test4);
    if (str_test4 == NULL) {
        free_matrix(test4);
        return 1;
    }
    printf("SUCCESS\n%s\n", str_test4);
    free_matrix(test4);
    free(str_test4);

    // TEST 5: Empty matrix - Should fail
    printf("TEST 5: empty ");
    double test5_contents[] = {};
    int test5_contents_size = 0;

    struct matrix *test5 = create_matrix(0, 0, test5_contents, test5_contents_size);
    if (test5 != NULL) {
        printf("--- FAILURE\n");
        free_matrix(test5);
        return 1;
    }
    printf("--- SUCCESS\n\n");

    // TEST 6: Negative dimensions - Should fail
    printf("TEST 6: negative dimensions ");
    double test6_contents[] = {
        1, -3, -5.45, 7, 9, 11, -13, -15.221, 17, -19, 21.232,
        -23, -25.2342, 27, 29.33, -31, -33.987, 35.11, 37, 39
    };
    int test6_contents_size = sizeof test6_contents / sizeof test6_contents[0];

    struct matrix *test6 = create_matrix(-5, -4, test6_contents, test6_contents_size);
    if (test6 != NULL) {
        printf("--- FAILURE\n");
        free_matrix(test6);
        return 1;
    }
    printf("--- SUCCESS\n\n");

    // TEST 7: Invalid size - Should fail
    printf("TEST 7: invalid size");
    double test7_contents[] = {1, 0, 2, 0, 3, 0, 4, 0, 5, 0};
    int test7_contents_size = sizeof test7_contents / sizeof test7_contents[0];

    struct matrix *test7 = create_matrix(3, 3, test7_contents, test7_contents_size);
    if (test7 != NULL) {
        printf(" --- FAILURE\n");
        free_matrix(test7);
        return 1;
    }
    printf(" --- SUCCESS\n\n");

    return 0;
}

int test_compare_matrices () {

    printf("\nTesting compare_matrices()\n\n");

    // TEST 1: Matrix with itself
    printf("TEST 1: matrix with itself --- ");
    double test1_contents[] = {
        1, 3, 5.45, 7, 9, 11, 13, 15.221, 17, 19, 21.232,
        23, 25.2342, 27, 29.33, 31, 33.987, 35.11, 37, 39
    };
    int test1_contents_size = sizeof test1_contents / sizeof test1_contents[0];

    struct matrix *test1 = create_matrix(4, 5, test1_contents, test1_contents_size);
    if (test1 == NULL) {
        return 1;
    }
    bool test1_result = compare_matrices(test1, test1);
    if ((test1_result) == false) {
        printf("FAILURE\n");
        return 1;
    }
    printf("SUCCESS\n");
    free_matrix(test1);

    // TEST 2: Mixed matrices, di: 3 4
    printf("TEST 2: mixed matrices --- ");
    double test2_contents[] = {2, 0, -7.342135, 6.34, -1000.1232, 20.0, 400.34566, 1, 2, -111.0, 99.999999, -0.123456};
    int test2_contents_size = sizeof test2_contents / sizeof test2_contents[0];

    struct matrix *test2_1 = create_matrix(3, 4, test2_contents, test2_contents_size);
    struct matrix *test2_2 = create_matrix(3, 4, test2_contents, test2_contents_size);
    if (test2_1 == NULL || test2_2 == NULL) {
        free_matrix(test2_1);
        free_matrix(test2_2);
        return 1;
    }
    bool test2_result = compare_matrices(test2_1, test2_2);
    if (test2_result == false) {
        printf("FAILURE\n");
        return 1;
    }
    printf("SUCCESS\n");
    free_matrix(test2_1);
    free_matrix(test2_2);

    // TEST 3: Same contents with dimensions flipped
    printf("TEST 3: same contents with dimensions flipped --- ");
    double test3_contents[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int test3_contents_size = sizeof test3_contents / sizeof test3_contents[0];

    struct matrix *test3_1 = create_matrix(2, 5, test3_contents, test3_contents_size);
    struct matrix *test3_2 = create_matrix(5, 2, test3_contents, test3_contents_size);
    if (test3_1 == NULL || test3_2 == NULL) {
        free_matrix(test3_1);
        free_matrix(test3_2);
        return 1;
    }
    bool test3_result = compare_matrices(test3_1, test3_2);
    if (test3_result == true) {
        printf("FAILURE\n");
        return 1;
    }
    printf("SUCCESS\n");
    free_matrix(test3_1);
    free_matrix(test3_2);

    // TEST 4: Same dimensions with different contents
    printf("TEST 4: same dimensions with different contents --- ");
    double test4_contents_1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int test4_contents_1_size = sizeof test4_contents_1 / sizeof test4_contents_1[0];
    double test4_contents_2[] = {1, 2, 5, 3, 4, 6, 7, 10, 9};
    int test4_contents_2_size = sizeof test4_contents_2 / sizeof test4_contents_2[0];

    struct matrix *test4_1 = create_matrix(3, 3, test4_contents_1, test4_contents_1_size);
    struct matrix *test4_2 = create_matrix(3, 3, test4_contents_2, test4_contents_2_size);
    if (test4_1 == NULL || test4_2 == NULL) {
        free_matrix(test4_1);
        free_matrix(test4_2);
        return 1;
    }
    bool test4_result = compare_matrices(test4_1, test4_2);
    if (test4_result == true) {
        printf("FAILURE\n");
        return 1;
    }
    printf("SUCCESS\n\n");
    free_matrix(test4_1);
    free_matrix(test4_2);

    return 0;
}

int test_matrix_addition () {

    printf("\nTesting matrix_addition()\n\n");

    // TEST matrix_addition(): test 1 all positive, dim: 4 5
    printf("TEST 1: all positive --- ");
    double test1_contents_1[] = {
        1, 2, 3, 4, 5,
        6, 7, 8, 9, 10,
        11, 12, 13, 14, 15,
        16, 17, 18, 19, 20
    };
    double test1_contents_2[] = {
        20, 19, 18, 17, 16,
        15, 14, 13, 12, 11,
        10, 9, 8, 7, 6,
        5, 4, 3, 2, 1
    };
    double test1_contents_expected[20];
    for (int i = 0; i < 20; i++) {
        test1_contents_expected[i] = 21;
    }
    int test1_contents_1_size = sizeof test1_contents_1 / sizeof test1_contents_1[0];
    int test1_contents_2_size = sizeof test1_contents_2 / sizeof test1_contents_2[0];
    int test1_contents_expected_size = sizeof test1_contents_expected / sizeof test1_contents_expected[0];

    struct matrix *test1_1 = create_matrix(4, 5, test1_contents_1, test1_contents_1_size);
    struct matrix *test1_2 = create_matrix(4, 5, test1_contents_2, test1_contents_2_size);
    struct matrix *test1_expected = create_matrix(4, 5, test1_contents_expected, test1_contents_expected_size);
    if (test1_1 == NULL || test1_2 == NULL || test1_expected == NULL) {
        free_matrix(test1_1);
        free_matrix(test1_2);
        free_matrix(test1_expected);
        return 1;
    }

    struct matrix *test1_result_matrix = matrix_addition(test1_1, test1_2);
    if (test1_result_matrix == NULL) {
        free_matrix(test1_1);
        free_matrix(test1_2);
        free_matrix(test1_expected);
        free_matrix(test1_result_matrix);
        return 1;
    }
    bool test1_result = compare_matrices(test1_expected, test1_result_matrix);
    free_matrix(test1_1);
    free_matrix(test1_2);
    free_matrix(test1_expected);
    free_matrix(test1_result_matrix);

    if (test1_result == false) {
        printf("FAILURE\n");
        return 1;
    }
    printf("SUCCESS\n");

    // TEST matrix_addition(): test 2 all negative, dim: 4 5
    printf("TEST 2: all negative --- ");
    double test2_contents_1[] = {
        -1, -2, -3, -4, -5, -6, -7, -8, -9, -10,
        -11, -12, -13, -14, -15, -16, -17, -18, -19, -20
    };
    double test2_contents_2[] = {
        -20, -19, -18, -17, -16, -15, -14, -13, -12, -11,
        -10, -9, -8, -7, -6, -5, -4, -3, -2, -1
    };
    double test2_contents_expected[20];
    for (int i = 0; i < 20; i++) {
        test2_contents_expected[i] = -21;
    }
    int test2_contents_1_size = sizeof test2_contents_1 / sizeof test2_contents_1[0];
    int test2_contents_2_size = sizeof test2_contents_2 / sizeof test2_contents_2[0];
    int test2_contents_expected_size = sizeof test2_contents_expected / sizeof test2_contents_expected[0];

    struct matrix *test2_1 = create_matrix(4, 5, test2_contents_1, test2_contents_1_size);
    struct matrix *test2_2 = create_matrix(4, 5, test2_contents_2, test2_contents_2_size);
    struct matrix *test2_expected = create_matrix(4, 5, test2_contents_expected, test2_contents_expected_size);
    if (test2_1 == NULL || test2_2 == NULL || test2_expected == NULL) {
        free_matrix(test2_1);
        free_matrix(test2_2);
        free_matrix(test2_expected);
        return 1;
    }

    struct matrix *test2_result_matrix = matrix_addition(test2_1, test2_2);
    if (test2_result_matrix == NULL) {
        free_matrix(test2_1);
        free_matrix(test2_2);
        free_matrix(test2_expected);
        free_matrix(test2_result_matrix);
        return 1;
    }

    bool test2_result = compare_matrices(test2_expected, test2_result_matrix);
    free_matrix(test2_1);
    free_matrix(test2_2);
    free_matrix(test2_expected);
    free_matrix(test2_result_matrix);
    
    if (test2_result == false) {
        printf("FAILURE\n");
        return 1;
    }
    printf("SUCCESS\n");

    // TEST matrix_addition(): test 3 mixed, dim: 2 3
    printf("TEST 3: mixed --- ");
    double test3_contents_1[] = {7, 5.7, -3, 81.4, 10, -72};
    double test3_contents_2[] = {-5, 34.3, 7, 9.2, 1, 3};
    double test3_contents_expected[] = {2, 40, 4, 90.6, 11, -69};
    int test3_contents_1_size = sizeof test3_contents_1 / sizeof test3_contents_1[0];
    int test3_contents_2_size = sizeof test3_contents_2 / sizeof test3_contents_2[0];
    int test3_contents_expected_size = sizeof test3_contents_expected / sizeof test3_contents_expected[0];

    struct matrix *test3_1 = create_matrix(2, 3, test3_contents_1, test3_contents_1_size);
    struct matrix *test3_2 = create_matrix(2, 3, test3_contents_2, test3_contents_2_size);
    struct matrix *test3_expected = create_matrix(2, 3, test3_contents_expected, test3_contents_expected_size);
    if (test3_1 == NULL || test3_2 == NULL || test3_expected == NULL) {
        free_matrix(test3_1);
        free_matrix(test3_2);
        free_matrix(test3_expected);
        return 1;
    }

    struct matrix *test3_result_matrix = matrix_addition(test3_1, test3_2);
    if (test3_result_matrix == NULL) {
        free_matrix(test3_1);
        free_matrix(test3_2);
        free_matrix(test3_expected);
        free_matrix(test3_result_matrix);
        return 1;
    }

    bool test3_result = compare_matrices(test3_expected, test3_result_matrix);
    free_matrix(test3_1);
    free_matrix(test3_2);
    free_matrix(test3_expected);
    free_matrix(test3_result_matrix);
    
    if (test3_result == false) {
        printf("FAILURE\n");
        return 1;
    }
    printf("SUCCESS\n");

    // TEST 4: not equal dimensions
    printf("TEST 4: not equal dimensions --- ");
    double test4_contents_1[] = {
        1, 2, 3, 4,
        -1, -2, -3, -4,
    };
    double test4_contents_2[] = {
        4, 3, 2,
        1, 4, 2,
        6, 3, 2
    };

    int test4_contents_1_size = sizeof test4_contents_1 / sizeof test4_contents_1[0];
    int test4_contents_2_size = sizeof test4_contents_2 / sizeof test4_contents_2[0];

    struct matrix *test4_1 = create_matrix(2, 4, test4_contents_1, test4_contents_1_size);
    struct matrix *test4_2 = create_matrix(3, 3, test4_contents_2, test4_contents_2_size);
    if (test4_1 == NULL || test4_2 == NULL) {
        free_matrix(test4_1);
        free_matrix(test4_2);
        return 1;
    }

    struct matrix *test4_result_matrix = matrix_addition(test4_1, test4_2);
    free_matrix(test4_1);
    free_matrix(test4_2);
    if (test4_result_matrix != NULL) {
        printf("FAILURE\n");
        free_matrix(test4_result_matrix);
        return 1;
    }
    printf("SUCCESS\n\n");

    return 0;
}

int test_matrix_multiplication () {

    printf("\nTesting matrix_multiplication()\n\n");

    // TEST 1: all positive. target1 dim: 2 3. target2 dim: 3 5
    printf("TEST 1: all positive --- ");
    double test1_contents_1[] = {
        2, 4, 1,
        3, 7, 6
    };
    double test1_contents_2[] = {
        6, 3, 9, 3, 1,
        5, 9, 6, 2, 2,
        7, 7, 23, 9, 10
    };
    double test1_contents_expected[] = {
        39, 49, 65, 23, 20,
        95, 114, 207, 77, 77
    };
    int test1_contents_1_size = sizeof test1_contents_1 / sizeof test1_contents_1[0];
    int test1_contents_2_size = sizeof test1_contents_2 / sizeof test1_contents_2[0];
    int test1_contents_expected_size = sizeof test1_contents_expected / sizeof test1_contents_expected[0];

    struct matrix *test1_1 = create_matrix(2, 3, test1_contents_1, test1_contents_1_size);
    struct matrix *test1_2 = create_matrix(3, 5, test1_contents_2, test1_contents_2_size);
    struct matrix *test1_expected = create_matrix(2, 5, test1_contents_expected, test1_contents_expected_size);
    if (test1_1 == NULL || test1_2 == NULL || test1_expected == NULL) {
        free_matrix(test1_1);
        free_matrix(test1_2);
        free_matrix(test1_expected);
        return 1;
    }

    struct matrix *test1_result_matrix = matrix_multiplication(test1_1, test1_2);
    if (test1_result_matrix == NULL) {
        free_matrix(test1_1);
        free_matrix(test1_2);
        free_matrix(test1_expected);
        free_matrix(test1_result_matrix);
        return 1;
    }

    bool test1_result = compare_matrices(test1_expected, test1_result_matrix);

    free_matrix(test1_1);
    free_matrix(test1_2);
    free_matrix(test1_expected);
    free_matrix(test1_result_matrix);
    
    if (test1_result == false) {
        printf("FAILURE\n");
        return 1;
    }
    printf("SUCCESS\n");

    // TEST 2: all negative. target1 dim: 2 3. target2 dim: 3 5
    printf("TEST 2: all negative --- ");
    double test2_contents_1[] = {
        -2, -4, -1,
        -3, -7, -6
    };
    double test2_contents_2[] = {
        -6, -3, -9, -3, -1,
        -5, -9, -6, -2, -2,
        -7, -7, -23, -9, -10
    };
    double test2_contents_expected[] = {
        39, 49, 65, 23, 20,
        95, 114, 207, 77, 77
    };
    int test2_contents_1_size = sizeof test2_contents_1 / sizeof test2_contents_1[0];
    int test2_contents_2_size = sizeof test2_contents_2 / sizeof test2_contents_2[0];
    int test2_contents_expected_size = sizeof test2_contents_expected / sizeof test2_contents_expected[0];

    struct matrix *test2_1 = create_matrix(2, 3, test2_contents_1, test2_contents_1_size);
    struct matrix *test2_2 = create_matrix(3, 5, test2_contents_2, test2_contents_2_size);
    struct matrix *test2_expected = create_matrix(2, 5, test2_contents_expected, test2_contents_expected_size);
    if (test2_1 == NULL || test2_2 == NULL || test2_expected == NULL) {
        free_matrix(test2_1);
        free_matrix(test2_2);
        free_matrix(test2_expected);
        return 1;
    }

    struct matrix *test2_result_matrix = matrix_multiplication(test2_1, test2_2);
    if (test2_result_matrix == NULL) {
        free_matrix(test2_1);
        free_matrix(test2_2);
        free_matrix(test2_expected);
        free_matrix(test2_result_matrix);
        return 1;
    }

    bool test2_result = compare_matrices(test2_expected, test2_result_matrix);

    free_matrix(test2_1);
    free_matrix(test2_2);
    free_matrix(test2_expected);
    free_matrix(test2_result_matrix);
    
    if (test2_result == false) {
        printf("FAILURE\n");
        return 1;
    }
    printf("SUCCESS\n");

    // TEST 3: one negative. target1 dim: 2 3. target2 dim: 3 5
    printf("TEST 3: one negative --- ");
    double test3_contents_1[] = {
        2, 4, 1,
        3, 7, 6
    };
    double test3_contents_2[] = {
        -6, -3, -9, -3, -1,
        -5, -9, -6, -2, -2,
        -7, -7, -23, -9, -10
    };
    double test3_contents_expected[] = {
        -39, -49, -65, -23, -20,
        -95, -114, -207, -77, -77
    };
    int test3_contents_1_size = sizeof test3_contents_1 / sizeof test3_contents_1[0];
    int test3_contents_2_size = sizeof test3_contents_2 / sizeof test3_contents_2[0];
    int test3_contents_expected_size = sizeof test3_contents_expected / sizeof test3_contents_expected[0];

    struct matrix *test3_1 = create_matrix(2, 3, test3_contents_1, test3_contents_1_size);
    struct matrix *test3_2 = create_matrix(3, 5, test3_contents_2, test3_contents_2_size);
    struct matrix *test3_expected = create_matrix(2, 5, test3_contents_expected, test3_contents_expected_size);
    if (test3_1 == NULL || test3_2 == NULL || test3_expected == NULL) {
        free_matrix(test3_1);
        free_matrix(test3_2);
        free_matrix(test3_expected);
        return 1;
    }

    struct matrix *test3_result_matrix = matrix_multiplication(test3_1, test3_2);
    if (test3_result_matrix == NULL) {
        free_matrix(test3_1);
        free_matrix(test3_2);
        free_matrix(test3_expected);
        free_matrix(test3_result_matrix);
        return 1;
    }

    bool test3_result = compare_matrices(test3_expected, test3_result_matrix);

    free_matrix(test3_1);
    free_matrix(test3_2);
    free_matrix(test3_expected);
    free_matrix(test3_result_matrix);
    
    if (test3_result == false) {
        printf("FAILURE\n");
        return 1;
    }
    printf("SUCCESS\n");

    // TEST 4: not equal dimensions
    printf("TEST 4: incompatible dimensions --- ");
    double test4_contents_1[] = {
        1, 2, 3, 4,
        -1, -2, -3, -4,
    };
    double test4_contents_2[] = {
        4, 3, 2,
        1, 4, 2,
        6, 3, 2
    };

    int test4_contents_1_size = sizeof test4_contents_1 / sizeof test4_contents_1[0];
    int test4_contents_2_size = sizeof test4_contents_2 / sizeof test4_contents_2[0];

    struct matrix *test4_1 = create_matrix(2, 4, test4_contents_1, test4_contents_1_size);
    struct matrix *test4_2 = create_matrix(3, 3, test4_contents_2, test4_contents_2_size);
    if (test4_1 == NULL || test4_2 == NULL) {
        free_matrix(test4_1);
        free_matrix(test4_2);
        return 1;
    }

    struct matrix *test4_result_matrix = matrix_multiplication(test4_1, test4_2);
    free_matrix(test4_1);
    free_matrix(test4_2);
    if (test4_result_matrix != NULL) {
        printf("FAILURE\n");
        free_matrix(test4_result_matrix);
        return 1;
    }
    printf("SUCCESS\n\n");

    return 1;
}

int test_scalar_addition () {
    return 1;
}

int test_scalar_multiplication () {
    return 1;
}

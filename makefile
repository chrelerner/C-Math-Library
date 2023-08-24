CFLAGS = -g -Wall -Wextra -std=gnu11

test: math_library.c test_math_library.c
	gcc $(CFLAGS) test_math_library.c math_library.c -o test
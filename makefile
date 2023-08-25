CFLAGS = -g -Wall -Wextra -std=gnu11
VFLAGS = --track-origins=yes --malloc-fill=0x40 --free-fill=0x23 --leak-check=full --show-leak-kinds=all

test: math_library.c test_math_library.c
	gcc $(CFLAGS) test_math_library.c math_library.c -o test

valgrind_test:
	valgrind $(VFLAGS) ./test

clean:
	rm -f test

compile:
	gcc -g -Wall -Werror -c Allocation.c
	gcc -g -Wall -Werror -c Allocator.c
	gcc -g -Wall -Werror -o prog4 prog4.o Allocation.o Allocator.o
	gcc -g -Wall -Werror -o tester tester.c Allocation.o Allocator.o

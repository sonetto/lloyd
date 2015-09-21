GCC_OPTIONS=-std=gnu11 -lopenal -lm

all: sine_test

sine_test: sine_test.c
	gcc sine_test.c $(GCC_OPTIONS) -o build/sine_test

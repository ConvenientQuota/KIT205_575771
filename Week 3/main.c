#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <time.h>



//Practical Analysis: Step 3
long f1(long n) {
    long k = 0;
    for (long i = 0; i < n; i++) {
        for (long j = 0; j < n; j++) {
            k++;
        }
    }
    return k;
}

void f2(long n) {
    long k = 0;
    for (long i = 0; i < n; i++) {
        for (long j = 0; j < i; j++) {
            k++;
        }
        for (long t = 0; t < 10000; t++) {
            k++;
        }
    }
}

void f3(long n) {
    if (n > 0) {
        f3(n / 2);
        f3(n / 2);
    }
}

void f4(long n) {
    if (n > 0) {
        f4(n / 2);
        f4(n / 2);
        f2(n);
    }
}

void f5(long n) {
    long k = 0;
    for (long i = 0; i < 10; i++) {
        long j = n;
        while (j > 0) {
            f1(1000);
            k++;
            j = j / 2;
        }
    }
}

void f6(long n) {
    f2(n);
    f3(n);
    f5(n);
}

void f7(long n) {
    long k = 0;
    for (long i = 0; i < f1(n); i++) {
        k++;
    }
    for (long j = 0; j < n; j++) {
        k++;
    }
}

// Moved this from list.c
void list_adhoc_test(List* self) {
	List newList = new_list();
	int quit = 0;

	while (!quit) {
		int value;
		printf("\nMenu\n");
		printf("0. Exit\n");
		printf("1. f1\n");
		printf("2. f2\n");
		printf("3. f3\n");
        printf("4. f4\n");
        printf("5. f5\n");
        printf("6. f6\n");
        printf("7. f7\n");
		printf("\nEnter choice\n");
		scanf("%d", &value);

        if (value != 0) {
            long a;
            printf("Please enter value for n\n");
            scanf("%d", &a);

            clock_t start = clock();
            
            switch (value) {
            case 1:
                f1(a);
                break;
            case 2:
                f2(a);
                break;
            case 3:
                f3(a);
                break;
            case 4:
                f4(a);
                break;
            case 5:
                f5(a);
                break;
            case 6:
                f6(a);
                break;
            case 7:
                f7(a);
                break;
            default:
                printf("Please enter another number.\n");
            }
            //calculating time difference and converting to milliseconds
            clock_t difference = clock() - start;
            long msec = diff * 1000 / CLOCKS_PER_SEC;
            printf("Time taken: %d milliseconds\n", msec);
        }
        else {
            quit = 1;
        }
	}
}

int main() {
	test_list();
    list_adhoc_test();
	return 0;
}
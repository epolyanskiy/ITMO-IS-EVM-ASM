#include <stdio.h>
#include <stdlib.h>

void sort(int *arr, int n);

int main() {
    FILE *inputFile = fopen("/Users/epolyanskiy/CLionProjects/untitled/INPUT.txt", "r");
    if (inputFile == NULL) {
        perror("Unable to open input file");
        return 1;
    }

    int n;
    fscanf(inputFile, "%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        perror("Unable to allocate memory");
        fclose(inputFile);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        fscanf(inputFile, "%d", &arr[i]);
    }

    fclose(inputFile);

    sort(arr, n);

    FILE *outputFile = fopen("/Users/epolyanskiy/CLionProjects/untitled/OUTPUT.txt", "w");
    if (outputFile == NULL) {
        perror("Unable to open output file");
        free(arr);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        fprintf(outputFile, "%d\n", arr[i]);
    }

    fclose(outputFile);
    free(arr);

    return 0;
}

void sort(int *arr, int n) {
    __asm__ volatile (
            "mov w8, %w[n]         \n" // w8 = n
            "sub w8, w8, #1        \n" // w8 = n - 1
            "1:                    \n"
            "mov w9, #0            \n" // w9 = 0 (flag: swapped)
            "mov w10, #0           \n" // w10 = 0 (index i)
            "2:                    \n"
            "ldr w11, [%[arr], w10, uxtw #2] \n" // w11 = arr[i]
            "add w12, w10, #1      \n" // w12 = i + 1
            "ldr w13, [%[arr], w12, uxtw #2] \n" // w13 = arr[i + 1]
            "cmp w11, w13          \n"
            "ble 3f                \n" // if arr[i] <= arr[i + 1], skip swapping
            "str w13, [%[arr], w10, uxtw #2] \n" // arr[i] = arr[i + 1]
            "str w11, [%[arr], w12, uxtw #2] \n" // arr[i + 1] = arr[i]
            "mov w9, #1            \n" // swapped = 1
            "3:                    \n"
            "add w10, w10, #1      \n" // i++
            "cmp w10, w8           \n"
            "blt 2b                \n" // if i < n - 1, repeat inner loop
            "sub w8, w8, #1        \n" // n--
            "cbnz w9, 1b           \n" // if swapped, repeat outer loop
            :
            : [arr] "r" (arr), [n] "r" (n)
    : "w8", "w9", "w10", "w11", "w12", "w13"
    );
}

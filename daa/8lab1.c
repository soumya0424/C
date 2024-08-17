#include <stdio.h>
#include <limits.h>

void printOptimalParens(int **S, int i, int j) {
    if (i == j)
        printf("A%d", i);
    else {
        printf("(");
        printOptimalParens(S, i, S[i][j]);
        printOptimalParens(S, S[i][j] + 1, j);
        printf(")");
    }
}

void matrixChainOrder(int p[], int n) {
    int **M = (int **)malloc(n * sizeof(int *));
    int **S = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        M[i] = (int *)malloc(n * sizeof(int));
        S[i] = (int *)malloc(n * sizeof(int));
    }

    for (int i = 1; i < n; i++)
        M[i][i] = 0;

    for (int length = 2; length < n; length++) {
        for (int i = 1; i < n - length + 1; i++) {
            int j = i + length - 1;
            M[i][j] = INT_MAX;
            for (int k = i; k <= j - 1; k++) {
                int q = M[i][k] + M[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < M[i][j]) {
                    M[i][j] = q;
                    S[i][j] = k;
                }
            }
        }
    }

    printf("Minimum number of scalar multiplications: %d\n", M[1][n - 1]);
    printf("Optimal Parenthesization: ");
    printOptimalParens(S, 1, n - 1);
    printf("\n");

    for (int i = 0; i < n; i++) {
        free(M[i]);
        free(S[i]);
    }
    free(M);
    free(S);
}

int main() {
    int n;
    printf("Enter the number of matrices: ");
    scanf("%d", &n);

    int p[n + 1];
    printf("Enter the dimensions of the matrices (in the form of array p):\n");
    for (int i = 0; i <= n; i++) {
        printf("p[%d]: ", i);
        scanf("%d", &p[i]);
    }

    matrixChainOrder(p, n + 1);

    return 0;
}

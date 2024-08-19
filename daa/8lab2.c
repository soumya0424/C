#include <stdio.h>
#include <string.h>

void printLCS(int **L, char *X, char *Y, int m, int n) {
    int i = m, j = n;
    int index = L[m][n];
    char lcs[index + 1];
    lcs[index] = '\0';

    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs[index - 1] = X[i - 1];
            i--;
            j--;
            index--;
        }
        else if (L[i - 1][j] > L[i][j - 1])
            i--;
        else
            j--;
    }

    printf("LCS: %s\n", lcs);
}

int lcs(char *X, char *Y, int m, int n) {
    int **L = (int **)malloc((m + 1) * sizeof(int *));
    for (int i = 0; i <= m; i++)
        L[i] = (int *)malloc((n + 1) * sizeof(int));

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;
            else
                L[i][j] = L[i - 1][j] > L[i][j - 1] ? L[i - 1][j] : L[i][j - 1];
        }
    }

    printf("Length of LCS: %d\n", L[m][n]);
    printLCS(L, X, Y, m, n);

    for (int i = 0; i <= m; i++)
        free(L[i]);
    free(L);

    return L[m][n];
}

int main() {
    char X[100], Y[100];
    printf("Enter first string: ");
    scanf("%s", X);
    printf("Enter second string: ");
    scanf("%s", Y);

    int m = strlen(X);
    int n = strlen(Y);

    lcs(X, Y, m, n);

    return 0;
}

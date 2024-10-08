#include <stdio.h>

void fastTranspose(int sparse[][3], int transposed[][3], int nonZero) {
    int totalArray[sparse[0][1]], startingPos[sparse[0][1]];
    int i, j;

    for (i = 0; i < sparse[0][1]; i++) {
        totalArray[i] = 0;
    }

    for (i = 1; i <= nonZero; i++) {
        totalArray[sparse[i][1]]++;
    }

    startingPos[0] = 1;
    for (i = 1; i < sparse[0][1]; i++) {
        startingPos[i] = startingPos[i - 1] + totalArray[i - 1];
    }

    for (i = 1; i <= nonZero; i++) {
        j = startingPos[sparse[i][1]]++;
        transposed[j][0] = sparse[i][1];
        transposed[j][1] = sparse[i][0];
        transposed[j][2] = sparse[i][2];
    }

    transposed[0][0] = sparse[0][1];
    transposed[0][1] = sparse[0][0];
    transposed[0][2] = sparse[0][2];
}

int main() {
    int n, m, nonZero;

    printf("Enter the number of rows: ");
    scanf("%d", &n);
    printf("Enter the number of columns: ");
    scanf("%d", &m);
    printf("Enter the number of non-zero elements: ");
    scanf("%d", &nonZero);
    int arr[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("Enter the element at (%d, %d): ", i, j);
            scanf("%d", &arr[i][j]);
        }
    }
    int sparse[nonZero + 1][3];
    sparse[0][0] = n;
    sparse[0][1] = m;
    sparse[0][2] = nonZero;
    int k = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (arr[i][j] != 0) {
                sparse[k][0] = i;
                sparse[k][1] = j;
                sparse[k][2] = arr[i][j];
                k++;
            }
        }
    }
    printf("Triplet form of the sparse matrix:\n");
    printf("Row Column Value\n");
    for (int i = 0; i < nonZero + 1; i++) {
        printf("%d    %d    %d\n", sparse[i][0], sparse[i][1], sparse[i][2]);
    }

    int transposed[nonZero + 1][3];
    fastTranspose(sparse, transposed, nonZero);

    printf("Triplet form of the transposed sparse matrix:\n");
    printf("Row Column Value\n");
    for (int i = 0; i < nonZero + 1; i++) {
        printf("%d    %d    %d\n", transposed[i][0], transposed[i][1], transposed[i][2]);
    }

    return 0;
}
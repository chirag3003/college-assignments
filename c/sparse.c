#include <stdio.h>

int main()
{
    int n, m, nonZero;

    printf("Enter the number of rows: ");
    scanf("%d", &n);
    printf("Enter the number of columns: ");
    scanf("%d", &m);
    printf(
        "Enter the number of non-zero elements: ");
    scanf("%d", &nonZero);
    int arr[n][m];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("Enter the element at (%d, %d): ", i, j);
            scanf("%d", &arr[i][j]);
        }
    }
    int sparse[nonZero + 1][3];
    sparse[0][0] = n;
    sparse[0][1] = m;
    sparse[0][2] = nonZero;
    int k = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (arr[i][j] != 0)
            {
                sparse[k][0] = i;
                sparse[k][1] = j;
                sparse[k][2] = arr[i][j];
                k++;
            }
        }
    }
    printf("Triplet form of the sparse matrix:\n");
    printf("Row Column Value\n");
    for (int i = 0; i < nonZero + 1; i++)
    {
        printf("%d    %d    %d\n", sparse[i][0], sparse[i][1], sparse[i][2]);
    }
    return 0;
}
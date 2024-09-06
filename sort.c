#include <stdio.h>
#include <string.h>

struct student
{
    char name[50];
    char prn[10];
    char mobile[10];
    char email[50];
};

void main()
{
    int n;
    printf("Enter the number of students: ");
    scanf("%d", &n);

    struct student students[n];

    for (int i = 0; i < n; i++) 
    {
        printf("Enter the name of student %d: ", i + 1);
        scanf("%s", students[i].name);
        printf("Enter the PRN of student %d: ", i + 1);
        scanf("%s", students[i].prn);
        printf("Enter the mobile number of student %d: ", i + 1);
        scanf("%s", students[i].mobile);
        printf("Enter the email of student %d: ", i + 1);
        scanf("%s", students[i].email);
    }

    int choice;
    printf("Enter the sorting algorithm to use: \n1. Bubble Sort\n2. Selection Sort\n3. Insertion Sort\n");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        // bubble sort
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
            {
                if (strcmp(students[j].name, students[j + 1].name) > 0)
                {
                    struct student temp = students[j];
                    students[j] = students[j + 1];
                    students[j + 1] = temp;
                }
            }
        }

        break;
    case 2:
        // selection sort
        for (int i = 0; i < n - 1; i++)
        {
            int min = i;
            for (int j = i + 1; j < n; j++)
            {
                if (strcmp(students[j].name, students[min].name) < 0)
                {
                    min = j;
                }
            }
            struct student temp = students[i];
            students[i] = students[min];
            students[min] = temp;
        }
        break;

    case 3:
        // insertion sort
        for (int i = 1; i < n; i++)
        {
            struct student key = students[i];
            int j = i - 1;
            while (j >= 0 && strcmp(students[j].name, key.name) > 0)
            {
                students[j + 1] = students[j];
                j = j - 1;
            }
            students[j + 1] = key;
        }
        break;
    }

    for (int i = 0; i < n; i++)
    {
        printf("Student %d\n", i + 1);
        printf("Name: %s\n", students[i].name);
        printf("PRN: %s\n", students[i].prn);
        printf("Mobile: %s\n", students[i].mobile);
        printf("Email: %s\n", students[i].email);
    }
}
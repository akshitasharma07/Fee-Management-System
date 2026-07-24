#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student
{
    int rollNo;
    char name[50];
    char course[30];
    float totalFee;
    float paidFee;
    float balance;
};

void addRecord();
void viewRecords();
void searchRecord();
void generateReceipt();

int main()
{
    int choice;

    while (1)
    {
        printf("\n===============================");
        printf("\n   FEE MANAGEMENT SYSTEM");
        printf("\n===============================\n");

        printf("1. Add Student Fee Record\n");
        printf("2. View All Records\n");
        printf("3. Search Student Record\n");
        printf("4. Generate Payment Receipt\n");
        printf("5. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addRecord();
            break;
        case 2:
            viewRecords();
            break;
        case 3:
            searchRecord();
            break;
        case 4:
            generateReceipt();
            break;
        case 5:
            printf("Thank You!\n");
            exit(0);
        default:
            printf("Invalid Choice!\n");
        }
    }

    return 0;
}

void addRecord()
{
    FILE *fp;
    struct Student s;

    fp = fopen("fees.dat", "ab");

    if (fp == NULL)
    {
        printf("File Error!\n");
        return;
    }

    printf("\nEnter Roll Number: ");
    scanf("%d", &s.rollNo);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Course: ");
    scanf(" %[^\n]", s.course);

    printf("Enter Total Fee: ");
    scanf("%f", &s.totalFee);

    printf("Enter Paid Fee: ");
    scanf("%f", &s.paidFee);

    s.balance = s.totalFee - s.paidFee;

    fwrite(&s, sizeof(s), 1, fp);

    fclose(fp);

    printf("\nRecord Added Successfully!\n");
}

void viewRecords()
{
    FILE *fp;
    struct Student s;

    fp = fopen("fees.dat", "rb");

    if (fp == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    printf("\n-------------------------------\n");

    while (fread(&s, sizeof(s), 1, fp))
    {
        printf("\nRoll No : %d", s.rollNo);
        printf("\nName    : %s", s.name);
        printf("\nCourse  : %s", s.course);
        printf("\nTotal Fee : %.2f", s.totalFee);
        printf("\nPaid Fee  : %.2f", s.paidFee);
        printf("\nBalance   : %.2f", s.balance);
        printf("\n-------------------------------\n");
    }

    fclose(fp);
}

void searchRecord()
{
    FILE *fp;
    struct Student s;
    int roll, found = 0;

    fp = fopen("fees.dat", "rb");

    if (fp == NULL)
    {
        printf("No Records Found!\n");
        return;
    }

    printf("Enter Roll Number: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp))
    {
        if (s.rollNo == roll)
        {
            found = 1;

            printf("\nStudent Found\n");
            printf("-----------------------\n");
            printf("Roll No : %d\n", s.rollNo);
            printf("Name : %s\n", s.name);
            printf("Course : %s\n", s.course);
            printf("Total Fee : %.2f\n", s.totalFee);
            printf("Paid Fee : %.2f\n", s.paidFee);
            printf("Balance : %.2f\n", s.balance);
        }
    }

    if (!found)
        printf("Record Not Found!\n");

    fclose(fp);
}

void generateReceipt()
{
    FILE *fp, *receipt;
    struct Student s;
    int roll, found = 0;

    fp = fopen("fees.dat", "rb");

    if (fp == NULL)
    {
        printf("No Records Found!\n");
        return;
    }

    printf("Enter Roll Number: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp))
    {
        if (s.rollNo == roll)
        {
            found = 1;

            receipt = fopen("receipt.txt", "w");

            fprintf(receipt, "=================================\n");
            fprintf(receipt, "        PAYMENT RECEIPT\n");
            fprintf(receipt, "=================================\n");
            fprintf(receipt, "Roll Number : %d\n", s.rollNo);
            fprintf(receipt, "Student Name: %s\n", s.name);
            fprintf(receipt, "Course      : %s\n", s.course);
            fprintf(receipt, "---------------------------------\n");
            fprintf(receipt, "Total Fee   : %.2f\n", s.totalFee);
            fprintf(receipt, "Paid Fee    : %.2f\n", s.paidFee);
            fprintf(receipt, "Balance Fee : %.2f\n", s.balance);
            fprintf(receipt, "=================================\n");
            fprintf(receipt, "      Payment Successful\n");
            fprintf(receipt, "=================================\n");

            fclose(receipt);

            printf("\nReceipt Generated Successfully!");
            printf("\nCheck 'receipt.txt' file.\n");
        }
    }

    if (!found)
        printf("Student Record Not Found!\n");

    fclose(fp);
}
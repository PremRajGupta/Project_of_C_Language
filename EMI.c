// Loan EMI Calculator Porject from C language
#include <stdio.h>
#include <conio.h>
#include <math.h>

float calculateEMI(float principal, float annualRate, int tenureYears)
{
    float monthlyRate = annualRate / (12 * 100); // convert annual rate to mothly
    int totalMonths = tenureYears * 12;          // calculate number of months of the loan

    return (principal * monthlyRate * pow(1 + monthlyRate, totalMonths)) / (pow(1 + monthlyRate, totalMonths) - 1);
}

void generateLoanChart(FILE *file, float loanAmount, float annualRate, int tenureYears)
{
    int month;
    float emi = calculateEMI(loanAmount, annualRate, tenureYears);
    float balance = loanAmount;
    float interestPaid, principalPaid;
    int totalMonths = tenureYears * 12;

    fprintf(file, "\nLoan Repayment Chart\n");
    fprintf(file, "Month\tEMI\t\tInterest Paid\tPrincipal Paid\tOutstanding balance\n");

    for (month = 1; month <= totalMonths; month++)
    {
        interestPaid = balance * (annualRate / (12 * 100));
        principalPaid = emi - interestPaid;
        balance -= principalPaid;
        if (balance < 0)
        {
            balance = 0;
        }
        fprintf(file, "%d\t%.2f\t\t%.2f\t\t%.2f\t\t%.2f\n", month, emi, interestPaid, principalPaid, balance);
    }
    printf("Loan chart has been saved to 'loan_details.txt'.\n");
}

void displayLoanChart()
{
    char ch;
    FILE *file = fopen("Loan_details.txt", "r");
    if (file == NULL)
    {
        printf("Error: No loan chart found. Generate a loan cahrt filrst.\n");
        return;
    }
    while ((ch = fgetc(file)) != EOF)
    {
        putchar(ch);
    }
    fclose(file);
}

int main()
{
    FILE *file;
    int choice;
    float loanAmount, annualRate;
    int tenureYears;

    while (1)
    {
        printf("\nLoan Application System\n");
        printf("1. Enter Loan Details and Generate Chart\n");
        printf("2. Display Loan Chart\n");
        printf("3. Exit\n");
        printf("Enter Your Choice:");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            file = fopen("loan_details.txt", "w");
            if (file == NULL)
            {
                printf("Error: unable to open file.\n");
                return 1;
            }
            printf("Enter Loan Amount: ");
            scanf("%f", &loanAmount);

            printf("Enter Annual Interest Rate: ");
            scanf("%f", &annualRate);

            printf("Enter Loan Tenure (in years): ");
            scanf("%d", &tenureYears);

            fprintf(file, "Loan Amount: %.2f\n", loanAmount);
            fprintf(file, "Annual Interset Rate: %.2f%%\n", annualRate);
            fprintf(file, "Loan Tenure: %d years\n", tenureYears);

            generateLoanChart(file, loanAmount, annualRate, tenureYears);

            fclose(file);
            break;

        case 2:
            displayLoanChart();
            break;

        case 3:
            printf("Exiting....\n");
            return 0;

        default:
            printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}
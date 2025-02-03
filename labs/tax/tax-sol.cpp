/* Take Home Pay Calculator */
// Social Security tax = 6.2% of gross wages (FICA)
// Medicare tax = 1.45% of gross wages (FICA)

// To learn more:
// https://www.ssa.gov/thirdparty/materials/pdfs/educators/What-is-FICA-Infographic-EN-05-10297.pdf

// Tax Rates 2022 for filing single
// 10%               Up to $10,275
// 12%               $10,276-$41,775
// 22%               $41,776-$89,075
// 24%               $89,076-$170,050
// 32%               $170,051-$215,950
// 35%               $215,951-$539,900
// 37%               $539,901 and over

const double SOCIAL_SECURITY_TAX_RATE = 0.062;
const double MEDICARE_TAX_RATE = 0.0145;

const double MINIMUM_WAGE = 15080;

const double BRACKET1 = 0;
const double BRACKET2 = 11600;
const double BRACKET3 = 47150;
const double BRACKET4 = 100525;
const double BRACKET5 = 191950;
const double BRACKET6 = 243725;
const double BRACKET7 = 609350;

const double TAX_RATE1 = 0.1;
const double TAX_RATE2 = 0.12;
const double TAX_RATE3 = 0.22;
const double TAX_RATE4 = 0.24;
const double TAX_RATE5 = 0.32;
const double TAX_RATE6 = 0.35;
const double TAX_RATE7 = 0.37;

#include <iomanip>
#include <iostream>

using namespace std;

int main() {
    double salary;
    double salaryInput;

    cout << "Enter a salary: $";
    cin >> salaryInput;
    salary = salaryInput;

    if (salary < MINIMUM_WAGE) {
        cerr << "This is less than minimum wage for a yearly salary." << endl;
        return 1;
    }

    const double ssTax = salary * SOCIAL_SECURITY_TAX_RATE;
    const double medicareTax = salary * MEDICARE_TAX_RATE;

    double incomeTax = 0;
    if (salary > BRACKET7) {
        incomeTax += (salary - BRACKET7) * TAX_RATE7;
        salary = BRACKET7;
    }
    if (salary > BRACKET6) {
        incomeTax += (salary - BRACKET6) * TAX_RATE6;
        salary = BRACKET6;
    }
    if (salary > BRACKET5) {
        incomeTax += (salary - BRACKET5) * TAX_RATE5;
        salary = BRACKET5;
    }
    if (salary > BRACKET4) {
        incomeTax += (salary - BRACKET4) * TAX_RATE4;
        salary = BRACKET4;
    }
    if (salary > BRACKET3) {
        incomeTax += (salary - BRACKET3) * TAX_RATE3;
        salary = BRACKET3;
    }
    if (salary > BRACKET2) {
        incomeTax += (salary - BRACKET2) * TAX_RATE2;
        salary = BRACKET2;
    }

    incomeTax += salary * TAX_RATE1;

    const double takeHomeSalary = salaryInput - ssTax - medicareTax - incomeTax;
    const double monthlyPay = takeHomeSalary / 12;

    cout << fixed << setprecision(2);
    cout << string(35, '-') << endl; // 35 dashes
    cout << setw(25) << left << "Yearly Salary: "
         << "$" << setw(9) << right << salaryInput << endl;
    cout << setw(25) << left << "Social Security Tax: "
         << "$" << setw(9) << right << ssTax << endl;
    cout << setw(25) << left << "Medicare Tax: "
         << "$" << setw(9) << right << medicareTax << endl;
    cout << setw(25) << left << "Income Tax: "
         << "$" << setw(9) << right << incomeTax << endl;
    cout << string(35, '-') << endl;
    cout << setw(25) << left << "Take Home Salary: "
         << "$" << setw(9) << right << takeHomeSalary << endl;
    cout << setw(25) << left << "Monthly Take Home Pay: "
         << "$" << setw(9) << right << monthlyPay << endl;
}

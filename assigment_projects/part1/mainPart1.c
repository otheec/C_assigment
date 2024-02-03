#include <stdio.h>
#include <math.h>

#define MAX_DEGREE 5
#define MAX_ITER 10
#define EPSILON 1e-4

double function(const int coefficients[], double x) {
    double ret = 0;
    for (int i = 0; i < MAX_DEGREE; ++i) {
        ret = ret + ((double)coefficients[i] * pow(x, i));
    }
    return ret;
}

double secantMethod(int coefficients[], double x0, double x1) {
    double x2, f0, f1, f2;
    int step = 1;

    do {
        f0 = function(coefficients, x0);
        f1 = function(coefficients, x1);

        x2 = x1 - f1 * (x1 - x0) / (f1 - f0);
        f2 = function(coefficients, x2);

        x0 = x1;
        f0 = f1;
        x1 = x2;
        f1 = f2;

        step++;

        if (step > MAX_ITER) {
            printf("Max iterations reached.");
            return -1;
        }
    } while (fabs(f2) > EPSILON && fabs(x1 - x0) > EPSILON);

    printf("\nRoot is: %f\n", x2);

    return x2;
}

double derivative(int coefficients[], double x) {
    double ret = 0;
    for (int i = 1; i < MAX_DEGREE; ++i) {
        ret += i * (double)coefficients[i] * pow(x, i - 1);
    }
    return ret;
}

double newtonRaphsonMethod(int coefficients[], double x0) {
    double x1, f0, f1, x0_old;
    int step = 1;

    do {
        f0 = function(coefficients, x0);

        x1 = x0 - f0 / derivative(coefficients, x0);
        f1 = function(coefficients, x1);

        x0_old = x0;
        x0 = x1;
        f0 = f1;

        step++;

        if (step > MAX_ITER) {
            printf("Max iterations reached.");
            return -1;
        }
    } while (fabs(f1) > EPSILON && fabs(x1 - x0_old) > EPSILON);

    printf("\nRoot is: %f\n", x1);

    return x1;
}

int getIntNumber() {
    int ret;
    int scanfResult;
    do {
        scanfResult = scanf("%d", &ret);
        if (scanfResult != 1) {
            while ((getchar()) != '\n');
            printf("Not a N number.\n");
        }
    } while (scanfResult != 1);
    return ret;
}

void getCoeficients(int coefficients[]) {
    for (int i = 0; i < MAX_DEGREE; i++) {
        printf("Enter coefficient %d: ", i);
        coefficients[i] = getIntNumber();
    }
}

void menu() {
    while (1) {
        double x0, x1;
        int coefficients[MAX_DEGREE], choice = 0;
        do {
            printf("Choose a method:\n");
            printf("1. Secant Method 1\n");
            printf("2. Newton-Raphson method 2\n");
            printf("3. Exit 3\n");
            choice = getIntNumber();
        } while (choice != 1 && choice != 2 && choice != 3);


        if (choice == 3) {
            break;
        }

        switch(choice) {
            case 1:
                getCoeficients(coefficients);
                printf("Enter the value of x0: ");
                scanf("%lf", &x0);
                printf("Enter the value of x1: ");
                scanf("%lf", &x1);
                secantMethod(coefficients, x0, x1);
                break;
            case 2:
                getCoeficients(coefficients);
                printf("Enter the value of x0: ");
                scanf("%lf", &x0);
                newtonRaphsonMethod(coefficients, x0);
                break;
        }
    }
}

int main() {
    menu();
    return 0;
}
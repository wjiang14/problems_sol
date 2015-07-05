//
//  main.c
//  shordinger_eq
//
//  Created by wei on 15/5/2.
//  Copyright (c) 2015年 wei. All rights reserved.
//

#include <stdio.h>
#include "math.h"

double x, x_left = 0, x_right;
int E, n, i = 1;

double potential(double x, double E){
    double pot = (x*x - E);
    return pot;
}


double differential2nd(double (*func)(double x), double x, double h){
    double diff2nd = (func(x + h) + func(x - h) - 2*func(x))/pow(h, 2);
    return diff2nd;
}


FILE *fp;

double psi[3];

double solve_odd(double h, double x_right, double E){
    fp = fopen( "output.txt", "w" );
    /* boundary condition */
    
    x = x_left;
    psi[0] = 0;
    psi[1] = h + pow(h, 3)*potential(x_left, E)/6.0;
    printf( "%f %f\n%f %f\n ", x_left, psi[0], x_left + h, psi[1] );
    fprintf(fp, "%e %e\n%e %e\n ", x_left, psi[0], x_left + h, psi[1] );
    
    /* recursion */
    while (x <= x_right) {
        x += h;
        psi[2] = ((2 + 5 * pow(h, 2) * potential(x, E)/6.0)*psi[1] - (1.0 - pow(h, 2) * potential(x - h, E)/12.0)*psi[0])/(1 - pow(h, 2) * potential(x + h, E)/12.0);
        printf("%f %f\n ", x + h, psi[2]);
        fprintf(fp, "%e %e\n ", x + h, psi[2]);
        psi[0] = psi[1];
        psi[1] = psi[2];
    }
    fclose( fp );
    return 0;
}


double solve_even(double h, double x_right, double E){
    fp = fopen( "output.txt", "w" );
    /* boundary condition */
   
    x = x_left;
    psi[0] = 1;
    psi[1] = 1 + pow(h, 2)/2*potential(x_left, E) + pow(h, 4)/24*(2 + pow(potential(x_left, E), 2));
    printf( "%f %f\n%f %f\n ", x_left, psi[0], x_left + h, psi[1] );
    fprintf(fp, "%e %e\n%e %e\n ", x_left, psi[0], x_left + h, psi[1]);
   
    /* recursion */
    while (x <= x_right) {
        x += h;
        psi[2] = ((2 + 5 * pow(h, 2) * potential(x, E)/6.0)*psi[1] - (1.0 - pow(h, 2) * potential(x - h, E)/12.0)*psi[0])/(1 - pow(h, 2) * potential(x + h, E)/12.0);
        printf("%f %f\n ", x + h, psi[2]);
        fprintf(fp, "%e %e\n ", x+h, psi[2]);
        psi[0] = psi[1];
        psi[1] = psi[2];
    }
    fclose( fp );
    return 0;
}

int main(int argc, const char * argv[]) {
    double x_right = 5;
    double h = 0.05;
    int n = 0;
    double E = 1;
    
    if (n%2 == 1) {
        solve_odd(h, x_right, E);
    }
    else
        solve_even(h, x_right, E);
    return 0;
}

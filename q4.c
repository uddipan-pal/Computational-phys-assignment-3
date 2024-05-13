#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <fftw3.h>



double gauss(double x) {
    
        return exp(-x*x);
    
}

int main() {
	int num=200;
	double xmax=50;
	
    fftw_complex in[num], out[num];
    fftw_plan plan;
    double h =  2 * xmax / (num - 1);

    for (int i=0; i < num; i++) {
        in[i] = gauss(-xmax + i * h) + I * 0.0;
    }

    plan = fftw_plan_dft_1d(num, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    fftw_execute(plan);

    FILE *file = fopen("q4_data.csv","w");
    if (file == NULL) {
        printf("Error Opening File!\n");
        return 1;
    }

    for (int i = 0; i < num; i++) {
        fprintf(file, "%g, %g\n", creal(out[i]), cimag(out[i]));
    }

    fclose(file);

    fftw_destroy_plan(plan);
    fftw_cleanup();

    printf("Fourier transform data written to 'q4_data.csv'.\n");

    return 0;
}
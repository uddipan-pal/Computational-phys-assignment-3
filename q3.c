
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_fft_complex.h>

#define REAL(z,i) ((z)[2*(i)])
#define IMAG(z,i) ((z)[2*(i)+1])


double sinc(double x) {
    if (x == 0.0){
        return 1.0;
    } else {
        return sin(x)/x;
    }
}

int main() {
	int num= 200;
	double xmax=50;
    double h= 2 * xmax / (num- 1);
    double data[2*num];

    gsl_fft_complex_wavetable * wavetable;
    gsl_fft_complex_workspace * workspace;

    for (int i=0; i < num; i++) {
        double x = -xmax + i * h;
        REAL(data,i) = sinc(x);
        IMAG(data,i) = 0.0;
    }

    wavetable = gsl_fft_complex_wavetable_alloc(num);
    workspace = gsl_fft_complex_workspace_alloc(num);

    gsl_fft_complex_forward(data, 1, num, wavetable, workspace);

    FILE *file = fopen("q3_data.csv","w");
   

    for (int i = 0; i < num; i++) {
        fprintf(file, "%g, %g\n", REAL(data,i), IMAG(data,i));
    }

    gsl_fft_complex_wavetable_free (wavetable);
    gsl_fft_complex_workspace_free (workspace);
    fclose(file);

    printf("Fourier transform data to 'q3_data.csv'.\n");

    return 0;
}

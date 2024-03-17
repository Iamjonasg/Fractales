// Jonas Gabirot

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main()
{

    int width = 512;
    int height = 512;
    double x_min = -1.5;
    double x_max = 0.5;
    double y_min = -1;
    double y_max = 1;
    int max_iterations = 200;

    int image3[512][512] = {0};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            double x = 2 * (j - 512 / 1.35) / 511;
            double y = 2 * (i - 512 / 2.0) / 511;
            double *z_real_list = malloc(max_iterations * sizeof(double));
            double *z_imag_list = malloc(max_iterations * sizeof(double));
            int count = 0;

            double z_real = 0;
            double z_imag = 0;
            int iterations = 0;
            while (z_real * z_real + z_imag * z_imag < 4 && iterations < max_iterations)
            {
                double z_real_new = z_real * z_real - z_imag * z_imag + x;
                double z_imag_new = 2 * z_real * z_imag + y;
                z_real = z_real_new;
                z_imag = z_imag_new;
                z_real_list[count] = z_real;
                z_imag_list[count] = z_imag;

                count++;
                iterations++;
            }

            if (iterations == max_iterations)
            {

                for (int i = 0; i <= count; i++)
                {
                    if (z_real_list[i] >= -1.5 && z_real_list[i] <= 0.5 && z_imag_list[i] >= -1.0 && z_imag_list[i] <= 1.0)
                    {
                        int k = (511 / 2) * z_real_list[i] + (512 / 1.35);
                        int l = (511 / 2) * z_imag_list[i] + (512 / 2.0);

                        image3[k][l] += 1;
                    }
                }
            }
        }
    }
    FILE *outfile3 = fopen("FractalMandelbrot_QII.3.pgm", "wb");
    fprintf(outfile3, "P2\n%d %d %d\n", 512, 512, 255);

    for (int i = 0; i < 512; i++)
    {
        for (int j = 0; j < 512; j++)
        {
            int temp = image3[i][j];

            // Writing the gray values in the 2D array to the file
            fprintf(outfile3, "%d ", temp);
        }
        fprintf(outfile3, "\n");
    }

    fclose(outfile3);

    return 0;
}
// Jonas Gabirot

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main()
{
    unsigned char *image = (unsigned char *)malloc(512 * 512 * sizeof(unsigned char) * 3);

    int width = 512;
    int height = 512;
    double x_min = -1.5;
    double x_max = 0.5;
    double y_min = -1;
    double y_max = 1;
    int max_iterations = 200;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            double x = 2 * (i - 512 / 1.35) / 511;
            double y = 2 * (j - 512 / 2.0) / 511;

            double z_real = 0;
            double z_imag = 0;
            int iterations = 0;
            while (z_real * z_real + z_imag * z_imag < 4 && iterations < max_iterations)
            {
                double z_real_new = z_real * z_real - z_imag * z_imag + x;
                double z_imag_new = 2 * z_real * z_imag + y;
                z_real = z_real_new;
                z_imag = z_imag_new;
                iterations++;
            }

            int index = (j * 512 + i) * 3;
            if (iterations == max_iterations)
            {
                image[index] = 0;
                image[index + 1] = 0;
                image[index + 2] = 0;
            }
            else
            {

                image[index] = 255;
                image[index + 1] = 255;
                image[index + 2] = 255;
            }
        }
    }
    FILE *outfile = fopen("FractalMandelbrot_QII.1.pgm", "wb");
    fprintf(outfile, "P6\n%d %d\n%d\n", 512, 512, 255);
    fwrite(image, sizeof(unsigned char) * 3, 512 * 512, outfile);
    fclose(outfile);

    // Free the memory used by the image
    free(image);

    return 0;
}
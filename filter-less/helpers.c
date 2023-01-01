#include "helpers.h"
#include <math.h>

// Convert image to grayscale
// should take an image and turn it into a black-and-white version of the same image.
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // find average value
            float average = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.00;
            int resultaverage = (int)round(average);

            // assign average value to the current pixel
            image[i][j].rgbtRed = resultaverage;
            image[i][j].rgbtGreen = resultaverage;
            image[i][j].rgbtBlue = resultaverage;
        }
    }
    return;
}

// Convert image to sepia
// should take an image and turn it into a sepia version of the same image.
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // rgbtRed:50,rgbtGreen:190,rgbtBlue:90 --> rgbtRed:183, rgbtGreen:163, rgbtBlue:127
    // sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue;
    // sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue;
    // sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;

            // calculate sepia
            float newRed = .393 * red + .769 * green + .189 * blue;
            float newgreen = .349 * red + .686 * green + .168 * blue;
            float newblue = .272 * red + .534 * green + .131 * blue;
            // round to int
            int intnewRed = (int)round(newRed);
            int intnewgreen = (int)round(newgreen);
            int intnewblue = (int)round(newblue);
            // assure numbers > 255 are set to 255
            if (intnewRed > 255)
            {
                intnewRed = 255;
            }
            if (intnewgreen > 255)
            {
                intnewgreen = 255;
            }
            if (intnewblue > 255)
            {
                intnewblue = 255;
            }
            // assign sepia values to the current pixel
            image[i][j].rgbtRed = intnewRed;
            image[i][j].rgbtGreen = intnewgreen;
            image[i][j].rgbtBlue = intnewblue;
        }
    }
    return;
}

// Reflect image horizontally
// should take an image and reflect it horizontally.
// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int temp[3];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            temp[0] = image[i][j].rgbtBlue;
            temp[1] = image[i][j].rgbtGreen;
            temp[2] = image[i][j].rgbtRed;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][width - j - 1].rgbtBlue = temp[0];
            image[i][width - j - 1].rgbtGreen = temp[1];
            image[i][width - j - 1].rgbtRed = temp[2];
        }
    }
    return;
}

int filterBlur(int i, int j, int height, int width, RGBTRIPLE image[height][width], int col_pos)
{
    float co = 0;
    int result = 0;

    /** Start from 1 row before it and end at 1 row after it- total of 3rows */
    for (int w = i - 1; w < (i + 2); w++)
    {
        /** Start from 1 blocw before it and end at 1 blocw after it- total of 3blocws */
        for (int n = j - 1; n < (j + 2); n ++)
        {
            if (n < 0 || w < 0 || n >= width || w >= height)
            {
                continue;
            }
            if (col_pos == 0)
            {
                result = result + image[w][n].rgbtRed;
            }
            else if (col_pos == 1)
            {
                result = result + image[w][n].rgbtGreen;
            }
            else
            {
                result = result + image[w][n].rgbtBlue;
            }
            co++;

        }
    }
    return round(result / co);
}
// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE aux[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            aux[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = filterBlur(i, j, height, width, aux, 0);
            image[i][j].rgbtGreen = filterBlur(i, j, height, width, aux, 1);
            image[i][j].rgbtBlue = filterBlur(i, j, height, width, aux, 2);
        }
    }
    return;
}
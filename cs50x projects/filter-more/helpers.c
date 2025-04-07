#include "helpers.h"
#include "math.h"

void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int rgbt;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            rgbt = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = rgbt;
            image[i][j].rgbtGreen = rgbt;
            image[i][j].rgbtRed = rgbt;
        }
    }

    return;
}


// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        if (width % 2 == 0)
        {
            for (int j = 0; j < width / 2; j++)
            {
                RGBTRIPLE temp[height][width];
                temp[i][j] = image[i][j];
                image[i][j] = image[i][width - (j + 1)];
                image[i][width - (j + 1)] = temp[i][j];
            }
        }
        else
        {
            for (int j = 0; j < (width - 1) / 2; j++)
            {
                RGBTRIPLE temp[height][width];
                temp[i][j] = image[i][j];
                image[i][j] = image[i][width - (j + 1)];
                image[i][width - (j + 1)] = temp[i][j];
            }
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]) {
  // Create a temporary array to store the blurred image.
  RGBTRIPLE temp[height][width];

  // Iterate over the original image, blurring each pixel.
  for (int i = 0; i < height; i++)
   {
    for (int j = 0; j < width; j++)
     {
      // Calculate the sum of the surrounding pixels.
      float sumBlue = 0;
      float sumGreen = 0;
      float sumRed = 0;
      float counter = 0;

      for (int r = -1; r < 2; r++)
       {
        for (int c = -1; c < 2; c++)
         {
          // Check if the pixel is within the bounds of the image.
          if (i + r < 0 || i + r > height - 1)
          {
            continue;
          }

          if (j + c < 0 || j + c > width - 1)
          {
            continue;
          }

          // Add the pixel's value to the sum.
          sumBlue += image[i + r][j + c].rgbtBlue;
          sumGreen += image[i + r][j + c].rgbtGreen;
          sumRed += image[i + r][j + c].rgbtRed;
          counter++;
        }
      }

      // Set the blurred pixel's value.
      temp[i][j].rgbtBlue = round(sumBlue / counter);
      temp[i][j].rgbtGreen = round(sumGreen / counter);
      temp[i][j].rgbtRed = round(sumRed / counter);
    }
  }

  // Copy the blurred image back to the original image.
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
      image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
      image[i][j].rgbtRed = temp[i][j].rgbtRed;
    }
  }

  return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Iterate over all pixels in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate the Gx and Gy values for the current pixel
            int gxBlue = 0, gyBlue = 0, gxGreen = 0, gyGreen = 0, gxRed = 0, gyRed = 0;
            for (int r = -1; r < 2; r++)
            {
                for (int c = -1; c < 2; c++)
                {
                    // Check if the current pixel is within the image boundaries
                    if (i + r < 0 || i + r > height - 1 || j + c < 0 || j + c > width - 1)
                    {
                        continue;
                    }

                    // Add the product of the current pixel's RGB value and the Gx/Gy kernel value
                    gxBlue += image[i + r][j + c].rgbtBlue * gx[r + 1][c + 1];
                    gyBlue += image[i + r][j + c].rgbtBlue * gy[r + 1][c + 1];
                    gxGreen += image[i + r][j + c].rgbtGreen * gx[r + 1][c + 1];
                    gyGreen += image[i + r][j + c].rgbtGreen * gy[r + 1][c + 1];
                    gxRed += image[i + r][j + c].rgbtRed * gx[r + 1][c + 1];
                    gyRed += image[i + r][j + c].rgbtRed * gy[r + 1][c + 1];
                }
            }

            // Calculate the magnitude of the gradient for each color channel
            int blue = round(sqrt(gxBlue * gxBlue + gyBlue * gyBlue));
            int green = round(sqrt(gxGreen * gxGreen + gyGreen * gyGreen));
            int red = round(sqrt(gxRed * gxRed + gyRed * gyRed));

            // Clamp the magnitude to 255
            temp[i][j].rgbtBlue = (blue > 255) ? 255 : blue;
            temp[i][j].rgbtGreen = (green > 255) ? 255 : green;
            temp[i][j].rgbtRed = (red > 255) ? 255 : red;
        }
    }

    // Copy the temporary image back to the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }

    return;
}






































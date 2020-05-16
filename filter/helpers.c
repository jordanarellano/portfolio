#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{   
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            //get average of original RGB values
            int av = round((image[h][w].rgbtRed + image[h][w].rgbtGreen + image[h][w].rgbtBlue) / 3.0);
            image[h][w].rgbtRed = av;
            image[h][w].rgbtGreen = av;
            image[h][w].rgbtBlue = av;
        }
    }
    
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            //get original RGB values
            int OGR = image[h][w].rgbtRed;
            int OGG = image[h][w].rgbtGreen;
            int OGB = image[h][w].rgbtBlue;
            
            //cap R at 255
            if (round(.393 * OGR + .769 * OGG + .189 * OGB) > 255)
            {
                image[h][w].rgbtRed = 255;
            }
            
            //set new R
            else 
            {
                image[h][w].rgbtRed = round(.393 * OGR + .769 * OGG + .189 * OGB);
            }
            
            //cap G at 255
            if (round(.349 * OGR + .686 * OGG + .168 * OGB) > 255)
            {
                image[h][w].rgbtGreen = 255;
            }
            
            //set new G
            else
            {
                image[h][w].rgbtGreen = round(.349 * OGR + .686 * OGG + .168 * OGB);
            }
            
            //cap blue at 255
            if (round(.272 * OGR + .534 * OGG + .131 * OGB) > 255)
            {
                image[h][w].rgbtBlue = 255;
            }
            
            //set new B
            else
            {
                image[h][w].rgbtBlue = round(.272 * OGR + .534 * OGG + .131 * OGB);
            }
        }
        
    }
    
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        
        for (int w = 0; w < width / 2 ; w++)
        {
            
            int OGR = image[h][w].rgbtRed;
            int OGG = image[h][w].rgbtGreen;
            int OGB = image[h][w].rgbtBlue;
            
            
            image[h][w].rgbtRed = image[h][width - 1 - w].rgbtRed;
            image[h][w].rgbtGreen = image[h][width - 1 - w].rgbtGreen;
            image[h][w].rgbtBlue =  image[h][width - 1 - w].rgbtBlue;
                
            image[h][width - 1 - w].rgbtRed = OGR;
            image[h][width - 1 - w].rgbtGreen = OGG;
            image[h][width - 1 - w].rgbtBlue = OGB;
            
        }  
    
    }    
    
    
    
    
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int red[height][width];
    int green[height][width];
    int blue[height][width];
     
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width ; w++)
        {
            //Special casec top left corner [0,0]
            if (h == 0 && w == 0)
            {
                
                //AVG RGB 
                int r1 = image[h][w].rgbtRed; 
                int g1 = image[h][w].rgbtGreen;
                int b1 = image[h][w].rgbtBlue;
                
                int r2 = image[h][w + 1].rgbtRed; 
                int g2 = image[h][w + 1].rgbtGreen;
                int b2 = image[h][w + 1].rgbtBlue;
                
                int r3 = image[h + 1][w].rgbtRed; 
                int g3 = image[h + 1][w].rgbtGreen;
                int b3 = image[h + 1][w].rgbtBlue;
                
                int r4 = image[h + 1][w + 1].rgbtRed; 
                int g4 = image[h + 1][w + 1].rgbtGreen;
                int b4 = image[h + 1][w + 1].rgbtBlue;
                
                //Assign avgs to current pixel to create blur
                red[h][w] = round((r1 + r2 + r3 + r4) / 4.00);
                green[h][w] = round((g1 + g2 + g3 + g4) / 4.00);
                blue[h][w] = round((b1 + b2 + b3 + b4) / 4.00);
            }
            
            //Special case top right corner  [0,width-1]
            else if (h == 0 && w == (width - 1))
            {
                
                //AVG RGB 
                int r1 = image[h][w - 1].rgbtRed; 
                int g1 = image[h][w - 1].rgbtGreen;
                int b1 = image[h][w - 1].rgbtBlue;
                
                int r2 = image[h][w].rgbtRed; 
                int g2 = image[h][w].rgbtGreen;
                int b2 = image[h][w].rgbtBlue;
                
                int r3 = image[h + 1][w - 1].rgbtRed; 
                int g3 = image[h + 1][w - 1].rgbtGreen;
                int b3 = image[h + 1][w - 1].rgbtBlue;
                
                int r4 = image[h + 1][w].rgbtRed; 
                int g4 = image[h + 1][w].rgbtGreen;
                int b4 = image[h + 1][w].rgbtBlue;
                
                //Assign avgs to current pixel to create blur
                red[h][w] = round((r1 + r2 + r3 + r4) / 4.00);
                blue[h][w] = round((g1 + g2 + g3 + g4) / 4.00);
                green[h][w] = round((b1 + b2 + b3 + b4) / 4.00);
            }
            
            //special case bottom left corner [height-1, 0]
            else if (h == (height - 1) && w == 0)
            {
                
                //AVG RGB 
                int r1 = image[h - 1][w].rgbtRed; 
                int g1 = image[h - 1][w].rgbtGreen;
                int b1 = image[h - 1][w].rgbtBlue;
                
                int r2 = image[h - 1][w + 1].rgbtRed; 
                int g2 = image[h - 1][w + 1].rgbtGreen;
                int b2 = image[h - 1][w + 1].rgbtBlue;
                
                int r3 = image[h][w].rgbtRed; 
                int g3 = image[h][w].rgbtGreen;
                int b3 = image[h][w].rgbtBlue;
                
                int r4 = image[h][w + 1].rgbtRed; 
                int g4 = image[h][w + 1].rgbtGreen;
                int b4 = image[h][w + 1].rgbtBlue;

                //Assign avgs to current pixel to create blur
                red[h][w] = round((r1 + r2 + r3 + r4) / 4.00);
                green[h][w] = round((g1 + g2 + g3 + g4) / 4.00);
                blue[h][w] = round((b1 + b2 + b3 + b4) / 4.00);
            }
            
            //special case bottom right corner [height-1,width-1]
            else if (h == (height - 1) && w == (width - 1))
            {
                
                //AVG RGB 
                int r1 = image[h - 1][w - 1].rgbtRed; 
                int g1 = image[h - 1][w - 1].rgbtGreen;
                int b1 = image[h - 1][w - 1].rgbtBlue;
                
                int r2 = image[h - 1][w].rgbtRed; 
                int g2 = image[h - 1][w].rgbtGreen;
                int b2 = image[h - 1][w].rgbtBlue;
                
                int r3 = image[h][w - 1].rgbtRed; 
                int g3 = image[h][w - 1].rgbtGreen;
                int b3 = image[h][w - 1].rgbtBlue;
                
                int r4 = image[h][w].rgbtRed; 
                int g4 = image[h][w].rgbtGreen;
                int b4 = image[h][w].rgbtBlue;
  
                //Assign avgs to current pixel to create blur
                red[h][w] = round((r1 + r2 + r3 + r4) / 4.00);
                green[h][w] = round((g1 + g2 + g3 + g4) / 4.00);
                blue[h][w] = round((b1 + b2 + b3 + b4) / 4.00);
            }
            
            //special case top row [0,w]
            else if (h == 0 && (w != 0 && w != (width - 1)))
            {

                //AVG RGB for surrounding pixels
                int r1 = image[h][w - 1].rgbtRed; 
                int g1 = image[h][w - 1].rgbtGreen;
                int b1 = image[h][w - 1].rgbtBlue;
                
                int r2 = image[h][w].rgbtRed; 
                int g2 = image[h][w].rgbtGreen;
                int b2 = image[h][w].rgbtBlue;
                
                int r3 = image[h][w + 1].rgbtRed; 
                int g3 = image[h][w + 1].rgbtGreen;
                int b3 = image[h][w + 1].rgbtBlue;
                
                int r4 = image[h + 1][w - 1].rgbtRed; 
                int g4 = image[h + 1][w - 1].rgbtGreen;
                int b4 = image[h + 1][w - 1].rgbtBlue;
                
                int r5 = image[h + 1][w].rgbtRed; 
                int g5 = image[h + 1][w].rgbtGreen;
                int b5 = image[h + 1][w].rgbtBlue;
                
                int r6 = image[h + 1][w + 1].rgbtRed; 
                int g6 = image[h + 1][w + 1].rgbtGreen;
                int b6 = image[h + 1][w + 1].rgbtBlue;
                
                //Assign avgs to current pixel to create blur
                red[h][w] = round((r1 + r2 + r3 + r4 + r5 + r6) / 6.00);
                green[h][w] = round((g1 + g2 + g3 + g4 + g5 + g6) / 6.00);
                blue[h][w] = round((b1 + b2 + b3 + b4 + b5 + b6) / 6.00);
   
            }
            
            //special case bottow row [height - 1 , w]
            else if (h == (height - 1) && (w != 0 && w != (width - 0)))
            {
                
                //AVG RGB for surrounding pixels
                int r1 = image[h - 1][w - 1].rgbtRed; 
                int g1 = image[h - 1][w - 1].rgbtGreen;
                int b1 = image[h - 1][w - 1].rgbtBlue;
                
                int r2 = image[h - 1][w].rgbtRed; 
                int g2 = image[h - 1][w].rgbtGreen;
                int b2 = image[h - 1][w].rgbtBlue;
                
                int r3 = image[h - 1][w + 1].rgbtRed; 
                int g3 = image[h - 1][w + 1].rgbtGreen;
                int b3 = image[h - 1][w + 1].rgbtBlue;
                
                int r4 = image[h][w - 1].rgbtRed; 
                int g4 = image[h][w - 1].rgbtGreen;
                int b4 = image[h][w - 1].rgbtBlue;
                
                int r5 = image[h][w].rgbtRed; 
                int g5 = image[h][w].rgbtGreen;
                int b5 = image[h][w].rgbtBlue;
                
                int r6 = image[h][w + 1].rgbtRed; 
                int g6 = image[h][w + 1].rgbtGreen;
                int b6 = image[h][w + 1].rgbtBlue;

                //Assign avgs to current pixel to create blur
                red[h][w] = round((r1 + r2 + r3 + r4 + r5 + r6) / 6.00);
                green[h][w] = round((g1 + g2 + g3 + g4 + g5 + g6) / 6.00);
                blue[h][w] = round((b1 + b2 + b3 + b4 + b5 + b6) / 6.00);
                
            }
            
            //special case left column [h,0]
            else if (w == 0 && (h != 0 && h != (height - 1)))
            {
                
                //AVG RGB for surrounding pixels
                int r1 = image[h - 1][w].rgbtRed; 
                int g1 = image[h - 1][w].rgbtGreen;
                int b1 = image[h - 1][w].rgbtBlue;
                
                int r2 = image[h - 1][w + 1].rgbtRed; 
                int g2 = image[h - 1][w + 1].rgbtGreen;
                int b2 = image[h - 1][w + 1].rgbtBlue;
                
                int r3 = image[h][w].rgbtRed; 
                int g3 = image[h][w].rgbtGreen;
                int b3 = image[h][w].rgbtBlue;
                
                int r4 = image[h][w + 1].rgbtRed; 
                int g4 = image[h][w + 1].rgbtGreen;
                int b4 = image[h][w + 1].rgbtBlue;
                
                int r5 = image[h + 1][w].rgbtRed; 
                int g5 = image[h + 1][w].rgbtGreen;
                int b5 = image[h + 1][w].rgbtBlue;
                
                int r6 = image[h + 1][w + 1].rgbtRed; 
                int g6 = image[h + 1][w + 1].rgbtGreen;
                int b6 = image[h + 1][w + 1].rgbtBlue;

                //Assign avgs to current pixel to create blur
                red[h][w] = round((r1 + r2 + r3 + r4 + r5 + r6) / 6.00);
                green[h][w] = round((g1 + g2 + g3 + g4 + g5 + g6) / 6.00);
                blue[h][w] = round((b1 + b2 + b3 + b4 + b5 + b6) / 6.00);
               
            }
            
            //special case right column [h,width - 1]
            else if (w == (width - 1) && (h != 0 && h != (height - 1)))
            {
                
                //AVG RGB for surrounding pixels
                int r1 = image[h - 1][w - 1].rgbtRed; 
                int g1 = image[h - 1][w - 1].rgbtGreen;
                int b1 = image[h - 1][w - 1].rgbtBlue;
                
                int r2 = image[h - 1][w].rgbtRed; 
                int g2 = image[h - 1][w].rgbtGreen;
                int b2 = image[h - 1][w].rgbtBlue;
                
                int r3 = image[h][w - 1].rgbtRed; 
                int g3 = image[h][w - 1].rgbtGreen;
                int b3 = image[h][w - 1].rgbtBlue;
                
                int r4 = image[h][w].rgbtRed; 
                int g4 = image[h][w].rgbtGreen;
                int b4 = image[h][w].rgbtBlue;
                
                int r5 = image[h + 1][w - 1].rgbtRed; 
                int g5 = image[h + 1][w - 1].rgbtGreen;
                int b5 = image[h + 1][w - 1].rgbtBlue;
                
                int r6 = image[h + 1][w].rgbtRed; 
                int g6 = image[h + 1][w].rgbtGreen;
                int b6 = image[h + 1][w].rgbtBlue;
 
               
                //Assign avgs to current pixel to create blur
                red[h][w] = round((r1 + r2 + r3 + r4 + r5 + r6) / 6.00);
                green[h][w] = round((g1 + g2 + g3 + g4 + g5 + g6) / 6.00);
                blue[h][w] = round((b1 + b2 + b3 + b4 + b5 + b6) / 6.00);
                
            }
            
            //anything not in 4 corners, or along 4 edges
            else
            {
            
                //AVG RGB for surrounding pixels
                int r1 = image[h - 1][w - 1].rgbtRed; 
                int g1 = image[h - 1][w - 1].rgbtGreen;
                int b1 = image[h - 1][w - 1].rgbtBlue;
                
                int r2 = image[h - 1][w].rgbtRed; 
                int g2 = image[h - 1][w].rgbtGreen;
                int b2 = image[h - 1][w].rgbtBlue;
                
                int r3 = image[h - 1][w + 1].rgbtRed; 
                int g3 = image[h - 1][w + 1].rgbtGreen;
                int b3 = image[h - 1][w + 1].rgbtBlue;
                
                int r4 = image[h][w - 1].rgbtRed; 
                int g4 = image[h][w - 1].rgbtGreen;
                int b4 = image[h][w - 1].rgbtBlue;
                
                int r5 = image[h][w].rgbtRed; 
                int g5 = image[h][w].rgbtGreen;
                int b5 = image[h][w].rgbtBlue;
                
                int r6 = image[h][w + 1].rgbtRed; 
                int g6 = image[h][w + 1].rgbtGreen;
                int b6 = image[h][w + 1].rgbtBlue;
                
                int r7 = image[h + 1][w - 1].rgbtRed; 
                int g7 = image[h + 1][w - 1].rgbtGreen;
                int b7 = image[h + 1][w - 1].rgbtBlue;
                
                int r8 = image[h + 1][w].rgbtRed; 
                int g8 = image[h + 1][w].rgbtGreen;
                int b8 = image[h + 1][w].rgbtBlue;
                
                int r9 = image[h + 1][w + 1].rgbtRed; 
                int g9 = image[h + 1][w + 1].rgbtGreen;
                int b9 = image[h + 1][w + 1].rgbtBlue;
                
               
                //Assign avgs to current pixel to create blur
                red[h][w] = round((r1 + r2 + r3 + r4 + r5 + r6 + r7 + r8 + r9) / 9.00);
                green[h][w] = round((g1 + g2 + g3 + g4 + g5 + g6 + g7 + g8 + g9) / 9.00);
                blue[h][w] = round((b1 + b2 + b3 + b4 + b5 + b6 + b7 + b8 + b9) / 9.00);
            }
        }
    }
    
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width ; w++)
        {
            image[h][w].rgbtRed = red[h][w];
            image[h][w].rgbtGreen = green[h][w];
            image[h][w].rgbtBlue = blue[h][w];
            
        }
        
    }
    
    
    
    return;
}

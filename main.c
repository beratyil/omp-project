#include <stdio.h>
#include <stdlib.h>

#define GRAYSCALE (65536 / 4) - 1

int main(int argc, char* argv[])
{
    int rowImg, colImg;

    if(argc < 2)
    {
        rowImg = colImg = 6;
    }

    rowImg = atoi(argv[1]);
    colImg = atoi(argv[2]);

    unsigned short** image = (unsigned short**)malloc(rowImg * sizeof(unsigned short*));
    unsigned short** resultImage = (unsigned short**)malloc(rowImg * sizeof(unsigned short*));

    for(int i = 0; i < rowImg; i++)
    {
        image[i] = (unsigned short*)malloc(colImg * sizeof(unsigned short));
        resultImage[i] = (unsigned short*)malloc(colImg * sizeof(unsigned short));
    }

    for(int i = 0; i < rowImg; i++)
    {
        for(int j = 0; j < colImg; j++)
        {
            image[i][j] = rand() % GRAYSCALE;
        }
    }
    
    /* Print Original Image */
    //
    for(int i = 0; i < rowImg; i++)
    {
        for(int j = 0; j < colImg; j++)
        {
            printf("%d ", image[i][j]);
        }
        printf("\n");
    }

    for(int imgRowIndx = 0; imgRowIndx < rowImg; imgRowIndx++)
    {
        for(int imgColIndx = 0; imgColIndx < rowImg; imgColIndx++)
        {
            
            unsigned int A[5][5];
            unsigned int B[5][5];

            for(int kernelRowIndx = imgRowIndx; kernelRowIndx < imgRowIndx + 5; kernelRowIndx++)
            {
                for(int kernelColIndx = imgColIndx; kernelColIndx < imgRowIndx + 5; kernelColIndx++)
                {
                    

                }


            }

        }

    }

    return 0;
}
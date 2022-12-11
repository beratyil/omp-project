#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GRAYSCALE (65536 / 1024) - 1

void matrixMultiplication(unsigned short matrix1[5][5], unsigned short matrix2[5][5], unsigned short result[][5]);

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

    for(int i = 0; i < rowImg; i++)
    {
        for(int j = 0; j < colImg; j++)
        {
            printf("%d ", image[i][j]);
        }
        printf("\n");
    }

    for(int imgRowIndx = 0; imgRowIndx + 5 <= rowImg; imgRowIndx++)
    {
        for(int imgColIndx = 0; imgColIndx <= imgRowIndx; imgColIndx++)
        {
            
            unsigned short A[5][5];
            unsigned short B[5][5];

            /* Prepare A and B matrices */
            for(int kernelRowIndx = 0; kernelRowIndx < 5; kernelRowIndx++)
            {
                for(int kernelColIndx = 0; kernelColIndx < 5; kernelColIndx++)
                {
                    A[kernelRowIndx][kernelColIndx] = image[imgRowIndx + kernelRowIndx][imgColIndx + kernelColIndx];
                    B[kernelRowIndx][kernelColIndx] = image[imgColIndx + kernelColIndx][imgRowIndx + kernelRowIndx];
                }
            }

            unsigned short C[5][5];
            memset(C, 0, sizeof(C));

            matrixMultiplication(A, B, C);
            
            printf("\nKernel Matrix\n");

            for(int i = 0; i < 5; i++)
            {
                for(int j = 0; j < 5; j++)
                {
                    printf("%d ", C[i][j]);
                }
                printf("\n");
            }

            for(int kernelRowIndx = 0; kernelRowIndx < 5; kernelRowIndx++)
            {
                for(int kernelColIndx = 0; kernelColIndx < 5; kernelColIndx++)
                {
                    resultImage[imgRowIndx + kernelRowIndx][imgColIndx + kernelColIndx] += C[kernelRowIndx][kernelColIndx];
                }
            }
        }

    }

    FILE* originalImageFile, * resultImageFile;

    if((originalImageFile = fopen("./originalImage.txt", "wb")) == NULL)
    {
        printf("Error!The Original Image File cannot be Openned");
    }

    if(fwrite(image, sizeof(unsigned short), rowImg*colImg, originalImageFile) != rowImg*colImg)
    {
        printf("File write error.");
    }

    fclose(originalImageFile);

    if((resultImageFile = fopen("./resultImage.txt", "wb")) == NULL)
    {
        printf("Error!The Original Image File cannot be Openned");
    }

    if(fwrite(image, sizeof(unsigned short), rowImg*colImg, resultImageFile) != rowImg*colImg)
    {
        printf("File write error.");
    }

    fclose(resultImageFile);

    return 0;
}

void matrixMultiplication(unsigned short matrix1[5][5], unsigned short matrix2[5][5], unsigned short result[][5])
{
    for(int row = 0; row < 5; row++)
    {
        for(int col = 0; col < 5; col++)
        {
            for(int colRow = 0; colRow < 5; colRow++)
            {
                result[row][col] += matrix1[row][colRow] * matrix2[colRow][col];
            }
        }
    }
    return;    
}

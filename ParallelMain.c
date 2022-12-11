#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>

#define GRAYSCALE (65536 / 1024) - 1

void matrixMultiplication(unsigned short matrix1[5][5], unsigned short matrix2[5][5], unsigned short result[][5]);

int main(int argc, char* argv[])
{
    time_t startTime = clock();

    int rowImg, colImg;

    if(argc < 2)
    {
        rowImg = colImg = 6;
    }
    else
    {
        rowImg = atoi(argv[1]);
        colImg = atoi(argv[2]);
    }

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
            resultImage[i][j] = 0;
        }
    }

    #pragma omp parallel for collapsable(2)
    {
        for(int imgRowIndx = 0; imgRowIndx <= rowImg - 5; imgRowIndx++)
        {
            for(int imgColIndx = 0; imgColIndx <= imgRowIndx; imgColIndx++)
            {
                unsigned short A[5][5];
                unsigned short B[5][5];

                /* Prepare A and B matrices */
                #pragma omp parallel num_threads(5)
                {
                    int kernelRowIndx = omp_get_thread_num();

                    for(int kernelColIndx = 0; kernelColIndx < 5; kernelColIndx++){
                        A[kernelRowIndx][kernelColIndx] = image[imgRowIndx + kernelRowIndx][imgColIndx + kernelColIndx];
                        B[kernelRowIndx][kernelColIndx] = image[imgColIndx + kernelColIndx][imgRowIndx + kernelRowIndx];
                    }
                }

                unsigned short C[5][5];
                memset(C, 0, sizeof(C));

                matrixMultiplication(A, B, C);

                #pragma omp parallel num_threads(5)
                {
                    int kernelRowIndx = omp_get_thread_num();

                    for(int kernelColIndx = 0; kernelColIndx < 5; kernelColIndx++){
                        #pragma omp critical
                        resultImage[imgRowIndx + kernelRowIndx][imgColIndx + kernelColIndx] += C[kernelRowIndx][kernelColIndx];
                    }
                }
            }
        }

        
    }
    

    time_t imageProcessingTime = clock();

    FILE* originalImageFile, * resultImageFile;

    if((originalImageFile = fopen("./originalImageOpenMP.txt", "wb")) == NULL)
    {
        printf("Error!The Original Image File cannot be Openned");
    }

    for(int i=0;i<rowImg;i++)
    {
        for(int j=0;j<colImg;j++)
        {
            fprintf(originalImageFile,"%d ",image[i][j]);
        }
        fprintf(originalImageFile,"\n");
    }

    fclose(originalImageFile);

    if((resultImageFile = fopen("./resultImageOpenMP.txt", "wb")) == NULL)
    {
        printf("Error!The Original Image File cannot be Openned");
    }

    for(int i=0;i<rowImg;i++)
    {
        for(int j=0;j<colImg;j++)
        {
            fprintf(resultImageFile,"%d ",resultImage[i][j]);
        }
        fprintf(resultImageFile, "\n");
    }

    fclose(resultImageFile);

    time_t loggingTime = clock();

    printf("\nImage processing time: %f", (double)(imageProcessingTime - startTime) / CLOCKS_PER_SEC );
    printf("\nLogging data to txt processing time: %f", (double)(loggingTime - startTime) / CLOCKS_PER_SEC );

    return 0;
}

void matrixMultiplication(unsigned short matrix1[5][5], unsigned short matrix2[5][5], unsigned short result[][5])
{
    int row, col, colRow;
    unsigned short temp;

    #pragma omp parallel for private(col, colRow, temp)
    for(row = 0; row < 5; row++)
    {
        for(col = 0; col < 5; col++)
        {
            temp = 0;
            for(colRow = 0; colRow < 5; colRow++)
            {
                temp += matrix1[row][colRow] * matrix2[colRow][col];
            }
            result[row][col] = temp;
        }
    }
    return;    
}

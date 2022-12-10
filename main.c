#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    int rowImg, colImg;

    if(argc < 2)
    {
        rowImg = colImg = 6;
    }

    rowImg = atoi(argv[1]);
    colImg = atoi(argv[2]);

    int** image = (int**)malloc(rowImg * sizeof(int*));

    for(int i = 0; i < rowImg; i++)
    {
        image[i] = (int*)malloc(colImg * sizeof(int));
    }


    return 0;
}
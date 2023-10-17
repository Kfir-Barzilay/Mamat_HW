/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


/*=========================================================================
  Constants and definitions:
==========================================================================*/

/* put your #defines and typedefs here*/
#define SCORE_MAX 100
#define SCORE_MIN 0


/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/

void mean(FILE *f)//print the mean value of all the grades in the file
{
    int sum = 0;
    int stud_num = 0;
    int grade;
    int line = 0;
    while(fscanf(f, "%d", &grade) != EOF)
    {
        if (grade > SCORE_MAX || grade < SCORE_MIN)
        {
            fprintf(stderr, "Grade value is not valid in line %d\n", line);
        }
        else
        {
            sum += grade;//summing all the grades in the file
            stud_num++;//counting all the students number
        }
        line++;
    }

    double mean = (((double)sum) / stud_num);//calculating the mean 
    fprintf(stdout, "%.2f", mean);
    return;
}

int main(int argc, char **argv)
{
    FILE *f;
    if(argc == 1 || !strcmp("-",argv[1]))
    {
        f = stdin;
    }
    else
    {
        f = fopen(argv[1], "r");
    }
    //checking for errors
    if(!f)
    {
        fprintf(stderr, "File not found: \"%s\"\n",argv[1]);
        return 1;
    }
    mean(f);
    fclose(f);
  return 0;
}


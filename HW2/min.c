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
void min(FILE *f)//extract the minimum value from grades
{
    int grade;
    int line = 0;
    int min = SCORE_MAX;
    while(fscanf(f,"%d",&grade)!= EOF)
    {
        if (grade > SCORE_MAX || grade < SCORE_MIN) {
            fprintf(stderr, "Value not valid in line %d\n", line);
        }
        else {
            min = (grade < min) ? grade : min;
        }
        line++;
    }
    fprintf(stdout,"%d", min);
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
        f = fopen(argv[1],"r");
    }
    //checking for errors
    if(!f)
    {
        fprintf(stderr, "File not found: \"%s\"\n",argv[1]);
        return 1;
    }
    min(f);
    fclose(f);
  return 0;
}

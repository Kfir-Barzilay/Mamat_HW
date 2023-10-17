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
 -------------------------------------------------------------------------
*/
int hist_build(FILE *f, int hist[SCORE_MAX+1])//function that bulid histogram of grades
{
    int grade;
    int line = 0;
    int stud_num = 0;
    while(fscanf(f, "%d", &grade)!= EOF) {
        if (grade > SCORE_MAX || grade < SCORE_MIN) {//check if the grade value is valid
            fprintf(stderr, "Grade value is not valid in line - %d", line);
        }
        else {
            hist[grade]++;
            stud_num++;
        }
        line++;
    }
    return stud_num;
}


void median(FILE *f)//function that extract the meadian from the histogram
{
    int hist[SCORE_MAX + 1]={0};
    int stud_num = hist_build(f ,hist); //filling the hist + find stud_num
    int med_num = (stud_num + 1)/2; //median place
    for(int i= SCORE_MIN; i <= SCORE_MAX; i++) {
        med_num -= hist[i];
        if(med_num <= 0) {
            fprintf(stdout, "%d",i);
            return;
        }
    }
    return;
}


int main(int argc, char **argv)
{
    FILE *f;
    if(argc == 1 || !strcmp("-",argv[1])) {
        f = stdin;
    }
    else {
        f = fopen(argv[1],"r");
    }
    //checking for errors
    if(!f) {
        fprintf(stderr, "File not found: \"%s\"\n",argv[1]);
        return 1;
    }
    median(f);
    fclose(f);
  return 0;
}

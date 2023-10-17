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
#define N_BINS_DEFAULT 10

static FILE *f;
static int nbins = 10;

/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/

 void extract_arg(int argc, char **argv)//getting the grades file and number of bins
 {
    f = stdin;
    for(int i=1; i<argc; i++) {
        if (!strcmp(argv[i],"-")) {
            f = stdin;
        } else if (!strcmp(argv[i], "-n_bins")) {
            nbins = (i<argc-1) ? atoi(argv[i+1]) : 10;
            i++;
        } else {
            f = fopen(argv[i], "r");
        }
    }
 }

 void fill_hist(int *hist)//filling the histogram with grades
 {
     int grade, bin, line=0;
     while(fscanf(f,"%d", &grade) != EOF) {
        if (grade > SCORE_MAX || grade < SCORE_MIN) {
            fprintf(stderr, "Grade value is not valid in line %d\n", line);
        }
        else {
            bin =(grade == SCORE_MAX)? nbins-1 : grade * nbins / SCORE_MAX;
            hist[bin]++;
        }
        line++;
     }
 }

 void print_hist(int *hist)//printing the histogram of grades
 {
   int portion = SCORE_MAX / nbins;
     for(int i=0; i <nbins-1; i++) {
        fprintf(stdout,"%d-%d\t%d\n",i*portion, (i+1)*portion -1 , *(hist +i));
     }
     fprintf(stdout,"%d-%d\t%d\n",SCORE_MAX-portion,SCORE_MAX,*(hist +nbins-1));
 }

int main(int argc, char **argv)
{
    extract_arg(argc, argv);
    //checking for errors
    if(!f) {
        fprintf(stderr, "File not found: \"%s\"\n",argv[1]);
        return 1;
    }
    int *hist = (int*)calloc(nbins,sizeof(int));
    fill_hist(hist);
    print_hist(hist);
    free(hist);
    fclose(f);
    return 0;
}

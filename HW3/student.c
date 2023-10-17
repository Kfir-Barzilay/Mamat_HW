#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*---------------------------------------------------------------------------*/
/* Create a new student struct and copy the data from the given student */
elem_t student_clone(elem_t element) {
    if(element == NULL)
        return NULL;
    pstudent_t orig_student = (pstudent_t)element;
    pstudent_t new_student = malloc(sizeof(student_t));
    int size = 0;
    if (new_student == NULL) {
        return NULL;
    }
    size = strlen(orig_student->name)+1;
    new_student->name = (char*)(malloc(size*sizeof(char)));
    if (new_student->name == NULL)
	return NULL;
    strcpy(new_student->name , orig_student->name);
    if (new_student->name == NULL) {
        free(new_student);
        return NULL;
    }
    new_student->age = orig_student->age;
    new_student->id = orig_student->id;
    return (elem_t)new_student;
}

/* Free the memory allocated for a student struct */
void student_destroy(elem_t element) {
    if(element == NULL)
        return;
    pstudent_t student = (pstudent_t)element;
    free(student->name);
    free(student);
}

/* Print the data of a student struct */
void student_print(elem_t element) {
    if(element == NULL)
        return;
    pstudent_t student = (pstudent_t)element;
    printf("student name: %s, age: %d, id: %d.\n",
           student->name, student->age, student->id);
}

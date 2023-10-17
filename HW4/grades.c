#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grades.h" //we need to check which include we can remove
#include "linked-list.h"

#define SUCCESS 0
#define FAILED -1

typedef struct course {
    char *name;
    int grade;
} *pcourse_t,course_t;

typedef struct student {  
    char *name;
    int id;
    struct list *list_of_courses;
} *pstudent_t, student_t;

typedef struct grades {
    struct list *list_of_students;
} grades;


int clone_student(void *element, void **output);
int clone_course(void* element, void** output);
void destroy_student(void *element);
void destroy_course(void* element);

struct grades* grades_init() { //good
    struct grades *grade = (struct grades*)malloc(sizeof(grades));
    if(grade == NULL)
        return NULL;
    grade->list_of_students = list_init((void*)clone_student,
                                		(void*) destroy_student);
    if (grade->list_of_students == NULL) {
        free(grade);
        return NULL;
	}
    return grade;
}

void grades_destroy(grades *g_arr) {
    if (g_arr==NULL)
        return; 
    list_destroy(g_arr->list_of_students);
    free(g_arr);
}

/*-------------------clones_and_destroys--------------------------------*/

int clone_student(void *element, void **output) {   //good
    if (element == NULL || output == NULL) {
    	return FAILED;
	}
	pstudent_t source = (pstudent_t)element;
    pstudent_t dest = malloc(sizeof(student_t));
     if (dest == NULL) 
        return FAILED;
    int name_size = (strlen(source->name) + 1)*sizeof(char);
    dest->name = malloc(name_size);
    if(dest->name == NULL) {
        free(dest);
        return FAILED;
    }
    strcpy(dest->name, source->name);
    dest->id = source->id;
    dest->list_of_courses = list_init((void*)clone_course,
                                     (void*)destroy_course);
    if(dest->list_of_courses == NULL) {
        free(dest->name);
        free(dest);
        return FAILED;
    }
    *output = dest;
    return SUCCESS;
}

void destroy_student(void *element) {  //good
    if (element == NULL)
        return;
    pstudent_t stud = (pstudent_t) element;
    free(stud->name);
    list_destroy(stud->list_of_courses);
    free(stud);
}

int clone_course(void* element, void** output){
    if (element == NULL || output == NULL)
        return FAILED;
    pcourse_t source = (pcourse_t)element;
    pcourse_t dest = malloc(sizeof(course_t));
	if(dest == NULL){
		return FAILED;
	}
	int name_size = sizeof(char)*(strlen(source->name) + 1);
	dest->name = (char*)malloc(name_size);
	if((dest->name) == NULL) {
        free(dest);
		return FAILED;
    }
	strcpy(dest->name ,source->name);
    dest->grade = source-> grade;
	*output = dest;
	return SUCCESS;
}

void destroy_course(void* element){
    if (element == NULL)
        return;
    pcourse_t course = (pcourse_t)element;
    free(course->name);
    free(course);
}

/*---------------------creates------------------------------*/

pstudent_t create_student(const char *name, int id) {
    if(name == NULL)
        return NULL;
    pstudent_t student = malloc(sizeof(student_t));
    if (student == NULL)
        return NULL;
    int name_size = (strlen(name) + 1)*sizeof(char);
    student->name = malloc(name_size);
    if(student->name == NULL) {
        free(student);
        return NULL;
    }
    strcpy(student->name,name);
    student->id = id;

    student->list_of_courses = list_init(clone_course, destroy_course);
    if (student->list_of_courses == NULL) {
        free(student->name);
        free(student);
        return NULL;
    }
    return student;
}

pcourse_t create_course(const char *name, int grade){
    if(name == NULL)
        return NULL;
    if(grade > 100 || grade < 0)
        return NULL;
    pcourse_t course = malloc(sizeof(course_t));
    if (course == NULL)
        return NULL;
    int name_size = (strlen(name) + 1)*sizeof(char);
    course->name = (char*)malloc(name_size);
    if(course->name == NULL) {
        free(course);
        return NULL;
    }
    strcpy(course->name,name);
    course->grade = grade;
    return course;
}

/*--------------------helpers---------------------------*/

pstudent_t get_stud(grades* grade, int id) {
    if (grade == NULL)
        return NULL;
    struct iterator *temp = list_begin(grade->list_of_students);
    while(temp != NULL)
    {
        pstudent_t stud = (pstudent_t)list_get(temp);
        stud = list_get(temp);
        if(stud == NULL)
            return NULL;
        if(stud->id == id)
            return stud;
        temp = list_next(temp);
    }
    return NULL;
}

int student_exist(grades *grade, int id) {
    pstudent_t student = get_stud(grade, id);
    if (student == NULL)
        return FAILED;
    return SUCCESS;
}

int course_exist(pstudent_t stud, const char* course_name) {
    struct iterator *temp = list_begin(stud->list_of_courses);
    while(temp != NULL) {
        pcourse_t course = (pcourse_t)list_get(temp);
        if(course == NULL)
            return FAILED;
        if(strcmp(course_name, course->name)==0) //course exist
            return SUCCESS;
        temp = list_next(temp);
    }
    return FAILED;
}

int print_course(pcourse_t course) {
	if(course == NULL){
   		return FAILED;
	}
    printf(" %s %d", course->name, course->grade);
	return SUCCESS;
}

int print_all_courses(pstudent_t student) {
	if (student == NULL){
		return FAILED;
	}
	struct iterator *temp = list_begin(student->list_of_courses);
    while(temp != NULL)
    {
        pcourse_t course = (pcourse_t)list_get(temp);
        if (print_course(course) == FAILED){
			return FAILED;
		}
		temp = list_next(temp);
		if(temp != NULL)
			printf(",");
    }
	printf("\n");
	return SUCCESS;
}
/*-------------------------------------------------------------------*/

int grades_add_student(struct grades *grades, const char *name, int id) {
    if(grades == NULL || name == NULL)
        return FAILED;
    // Check if student with the given ID already exists
    if(student_exist(grades, id) == SUCCESS) 
        return FAILED;
    pstudent_t student = create_student(name, id);
    if (student == NULL){
        return FAILED;
	}
    int result = list_push_back(grades->list_of_students,student);
    destroy_student(student);
    return result;
}

int grades_add_grade(struct grades *grades,
                     const char *name,
                     int id,
                     int grade) {
    //code protections
    if (grades == NULL || name == NULL)//
        return FAILED;
    if(grade < 0 || grade > 100)
        return FAILED;

    pstudent_t student = get_stud(grades, id);   //get relevant student
    if(student == NULL)
        return FAILED;
    if(course_exist(student, name) == SUCCESS)
        return FAILED;
    pcourse_t new_course = create_course(name, grade);
	if (new_course == NULL) {
		return FAILED;
	}
    int result = list_push_back(student->list_of_courses, new_course);
    destroy_course(new_course);
    return result;
}


float grades_calc_avg(struct grades *grades, int id, char **out) {
    if(grades == NULL || out == NULL)
        return FAILED;
    pstudent_t student = get_stud(grades, id);
    if(student == NULL) //doesnot exist
        return FAILED;
    float sum = 0;
    float course_num = 0;
    struct iterator *temp = list_begin(student->list_of_courses);
    while(temp != NULL)
    {
        pcourse_t course = (pcourse_t)list_get(temp);
        if(course == NULL)
            return FAILED;
        course_num++;
        sum+= course->grade;
        temp = list_next(temp);
    }
	int name_size = sizeof(char) * (strlen(student->name )+1);
	*out = malloc(sizeof(name_size));
	strcpy(*out,student->name);
    if(course_num == 0.0){
        return 0.0;
	}
    return sum/course_num;
}

int grades_print_student(struct grades *grades, int id) {
    if(grades == NULL)
        return FAILED;
    pstudent_t student = get_stud(grades, id);
    if(student == NULL)
        return FAILED;
    printf("%s %d:", student->name, student->id);
    if (print_all_courses(student)== FAILED)
		return FAILED;
    return SUCCESS;
}

int grades_print_all(struct grades *grades) {
    if(grades == NULL)
        return FAILED;
    struct iterator *temp =list_begin(grades->list_of_students);
    while(temp != NULL)
    {
        pstudent_t student = (pstudent_t)list_get(temp);
        if(student == NULL)
            return FAILED;
        if (grades_print_student(grades, student->id) == FAILED)
			return FAILED;
        temp = list_next(temp);
    }
    return SUCCESS;
}
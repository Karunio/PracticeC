#ifndef __STUDENT_H__
#define __STUDENT_H__

#define _MAX_NAME_SIZE	20

typedef struct student Student;

struct student {
	int age;
	char name[_MAX_NAME_SIZE];
};

#endif

#include <stdio.h>

struct dob {
    int day;
    int month;
    int year;
};

struct student_info {
    int roll_no;
    char name[50];
    float CGPA;
    struct dob age;
};

void print_student_by_value(struct student_info s) {
    printf("Roll No: %d\nName: %s\nCGPA: %.2f\nDOB: %d-%d-%d\n", s.roll_no, s.name, s.CGPA, s.age.day, s.age.month, s.age.year);
}

void print_student_by_address(struct student_info *s) {
    printf("Roll No: %d\nName: %s\nCGPA: %.2f\nDOB: %d-%d-%d\n", s->roll_no, s->name, s->CGPA, s->age.day, s->age.month, s->age.year);
}

int main() {
    struct student_info student = {1, "John Doe", 3.5, {15, 8, 2000}};
    
    printf("Using call-by-value:\n");
    print_student_by_value(student);
    
    printf("\nUsing call-by-address:\n");
    print_student_by_address(&student);
    
    return 0;
}

#include <stdio.h>
#include <malloc.h>

typedef struct Student {
    char name[20];
    int sex;
    int birthTime;
    float height;
    int c_language;
    int Calculus;
} Student;

Student *initStudent(int count, Student *students);

void C_average(int count, Student *students);

void C_max(int count, Student *students);

void C_min(int count, Student *students);

void Calculus_average(int count, Student *students);

void Calculus_max(int count, Student *students);

void Calculus_min(int count, Student *students);

void student_info(Student *student);


int main() {
    int count;
    scanf("%d", &count);
    Student *students = (Student *) malloc(count * sizeof(Student));

    students = initStudent(count, students);

    C_average(count, students);
    C_max(count, students);
    C_min(count, students);
    Calculus_average(count, students);
    Calculus_max(count, students);
    Calculus_min(count, students);

    return 0;
}

Student *initStudent(int count, Student *students) {
    for (int i = 0; i < count; i++) {
        scanf("%s", students[i].name);
        scanf("%d", &students[i].sex);
        scanf("%d", &students[i].birthTime);
        scanf("%f", &students[i].height);
        scanf("%d", &students[i].c_language);
        scanf("%d", &students[i].Calculus);
    }
    return students;
}


void C_average(int count, Student *students) {
    int sum = 0;
    for (int i = 0; i < count; i++) {
        sum += students[i].c_language;
    }
    printf("C_average:%d\n", sum / count);
}


void Calculus_average(int count, Student *students) {
    int sum = 0;
    for (int i = 0; i < count; i++) {
        sum += students[i].Calculus;
    }
    printf("Calculus_average:%d\n", sum / count);
}


void C_max(int count, Student *students) {
    int max = 0, i = 0;
    max = students[i].c_language;
    if (count!=1){
        for (i = 0; i < count - 1; i++) {
            if (max< students[i + 1].c_language) {
                max = students[i + 1].c_language;
            }
        }
    }
    printf("C_max:%d\n", max);
    for (int j = 0; j < count; j++) {
        if (students[j].c_language == max) {
            student_info(students + j);
        }
    }
}

void Calculus_max(int count, Student *students) {
    int max = 0, i = 0;
        max = students[i].Calculus;
    if (count!=1){
        for (i = 0; i < count - 1; i++) {
            if (max < students[i + 1].Calculus) {
                max = students[i + 1].Calculus;
                printf("now max is %d\n",max);
            }
        }
    }

    printf("Calculus_max:%d\n", max);
    for (int j = 0; j < count; j++) {
        if (students[j].Calculus == max) {
            student_info(students + j);
        }
    }
}

void C_min(int count, Student *students) {
    int min = 0, i = 0;
    if (count == 1) {
        min = students[i].c_language;
    } else {
        for (i = 0; i < count - 1; i++) {
            if (students[i].c_language > students[i + 1].c_language) {
                min = students[i + 1].c_language;
            } else if (students[i].c_language < students[i + 1].c_language) {
                min = students[i].c_language;
            }

        }
    }
    printf("C_min:%d\n", min);
}

void Calculus_min(int count, Student *students) {
    int min = 0, i = 0;
    if (count == 1) {
        min = students[i].Calculus;
    } else {
        for (i = 0; i < count - 1; i++) {
            if (students[i].Calculus > students[i + 1].Calculus) {
                min = students[i + 1].Calculus;
            } else if (students[i].Calculus < students[i + 1].Calculus) {
                min = students[i].Calculus;
            }
        }
    }
    printf("Calculus_min:%d\n", min);
}


void student_info(Student *student) {
    printf("%s ", student->name);
    printf("%d ", student->sex);
    printf("%d ", student->birthTime);
    printf("%.2f ", student->height);
    printf("%d ", student->c_language);
    printf("%d\n", student->Calculus);
}
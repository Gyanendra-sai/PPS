// #include<stdio.h>

// struct employee 
// {
//     int id;
//     char name[30];
//     float salary;
//     char department[20];
// };

// int main(){
//     struct employee e1;

//     printf("Enter employee ID : \n");
//     scanf("%d", &e1.id);
//     printf("Enter employee name : \n");
//     scanf("%s", &e1.name);
//     printf("Enter employee salary : \n");
//     scanf("%f", &e1.salary);
//     printf("Enter department : \n");
//     fgets(e1.department, 20, stdin);
//     printf("\n========= Employee Detaiks =========\n");
//     printf("ID : %d\n", e1.id);
//     fgets(e1.name, 30, stdin);
//     printf("Salary : %f\n", e1.salary);
//     printf("Department : %s\n", e1.department);

//     return 0;
// }


#include<stdio.h>

struct student{
    char name[50];
    int age;
    float marks;
};

int main(){
    struct student s1[3];
    int i;

    for (int i = 0; i < 3; i++){
        printf("Enter details for student %d : \n", i + 1);
        printf("Name : ");
        scanf("%s", s1[i].name);
        printf("Age : ");
        scanf("%d", &s1[i].age);
        printf("Marks : ");
        scanf("%f", &s1[i].marks);
    }

    printf("\n========== List of Students ==========");

    for (int i = 0; i < 3; i++) {
        printf("\nStudent %d:\n", i + 1);
        printf("Name: %s\n", s1[i].name);
        printf("Age: %d\n", s1[i].age);
        printf("Marks: %.2f\n", s1[i].marks);
    }
    
    return 0; }

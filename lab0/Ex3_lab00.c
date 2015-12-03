#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define STUDENTMAX 20

typedef struct {
  float GPA;
  char name[50];
} Student;

void sortByGPA(Student* students,int first,int last){
    int pivot,j,i;
    Student temp;

     if(first<last){
         pivot=first;
         i=first+1;
         j=last-1;

         while(i<j){
             while(students[i].GPA<=students[pivot].GPA&&i<last)
                 i++;
             while(students[j].GPA>students[pivot].GPA)
                 j--;
             if(i<j){
                 temp=students[i];
                  students[i]=students[j];
                  students[j]=temp;
             }
         }

         temp=students[pivot];
         students[pivot]=students[j];
         students[j]=temp;
         sortByGPA(students,first,j-1);
         sortByGPA(students,j+1,last);

    }
}

int main(){
  Student students[STUDENTMAX];
  int totalStudents = 0;

  printf("Please enter the amount of students:");
  scanf("%d", &totalStudents);
  while(totalStudents>STUDENTMAX){
      printf("The maximum amount of students is %d\n", STUDENTMAX);
      printf("Please, try again:\n");
      scanf("%d", &totalStudents);
  }

  for(int i=0; i<totalStudents; i++){
          printf("Please enter the name:");
          scanf("%s",students[i].name);
          printf("Please enter the GPA:");
          scanf("%f",&students[i].GPA);        
  }

  sortByGPA(students,0,totalStudents);

  for(int i=0;i<totalStudents;i++){
    printf("Name: %s GPA:%.2f\n",students[i].name,students[i].GPA);
  }

  return 0;
}
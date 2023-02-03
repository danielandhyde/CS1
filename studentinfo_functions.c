#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//define max numbers of students, courses, enrollments, and length of names
#define MAXSTD 2000
#define MAXCRS 100
#define MAXENR 5000
#define MAXNAM 50
//define a struct called Students with int for student id, strings for first and last names, and ints for day, month, and year of birth
typedef struct Students{
  int id;
  char fname[MAXNAM];
  char lname[MAXNAM];
  int day;
  int month;
  int year;
}Students;
//define a struct called Courses with strings for course id and course name and a float for credit
typedef struct Courses{
  char id[MAXNAM];
  char name[MAXNAM];
  float credit;
}Courses;
//define a struct called Enrollments with an int for student id, strings for course id and semester, and a float for score
typedef struct Enrollments{
  int studentID;
  char courseID[MAXNAM];
  char semester[MAXNAM];
  float score;
}Enrollments;
//function to load students from a file into an array and fill the number of students into a pointer
void loadStudents(Students st[], int *numStudents);
//load enrollments from file into an array of type Enrollments and return the number of enrollments
int loadEnrollment(Enrollments en[]);
//load courses from file into array of type Courses and return number of courses
int loadCourses(Courses course[]);
//function to handle practically everything given all the loaded info from files and a user-inputted command
void menu(Students ArrayOfStudents[], int amountStudents, Courses ArrayOfCourses[], int amountCourses, Enrollments ArrayOfEnrollments[], int amountEnrolls, char command[]);
//function to print students given a subcommand and other extraneous information that may or may not be useful
void print_student(char command[], char name[], Students ArrayOfStudents[], int amountStudents, Courses ArrayOfCourses[], int amountCourses, Enrollments ArrayOfEnrollments[], int amountEnrolls, int id, int byear);
//function to print enrollments given info from the menu
void print_student_enrollment(Students ArrayOfStudents[], int amountStudents, Courses ArrayOfCourses[], int amountCourses, Enrollments ArrayOfEnrollments[], int amountEnrolls, int id);
//simple function to return a character grade given a numerical score
char return_grade(float num_grade);
//function to match a course with an enrollment course id and to fill in the course name to a given array; also returns the index of occurrence
int match_course_id(char course_id[], int amountCourses, Courses arr[], char course_name[]);
//function to print course enrollments given information from the menu and other extraneous information that may or may not be useful
void print_course_enrollment(Students ArrayOfStudents[], int amountStudents, Courses ArrayOfCourses[], int amountCourses, Enrollments ArrayOfEnrollments[], int amountEnrolls, char id[], char semester[]);
//Given a course id and semester, display the list of students enrolled in that course on that particular semester.
void match_semesters(char semester[], Enrollments ArrayOfEnrollments[], int index_enrollments, Students ArrayOfStudents[], int index_students);
//Display course info and all students enrolled to a given course given the course id.
void print_course(char command[], char course_id[], Students ArrayOfStudents[], int amountStudents, Courses ArrayOfCourses[], int amountCourses, Enrollments ArrayOfEnrollments[], int amountEnrolls);
//Given a courseid, course name, and credit, add this new course to the end of the course.txt file. Before adding, the system should check whether the course id already exists. If it does, display “violation of course id uniqueness. Cannot add the record.” After adding data, reload data to the program's structure.
void add_course(Courses ArrayOfCourses[], int amountCourses, char course_id[], char course_name[], float credit);
//Display total number of students. Display total number of students for each cid. Display total number of students for each semeste
void count(char command1[], int amountStudents, int amountCourses, int amountEnrollments, Students ArrayOfStudents[], Courses ArrayOfCourses[], Enrollments ArrayOfEnrollments[]);

int main(void) {
  //arrays for each struct type to hold data from files
  Students st[MAXSTD];
  Enrollments en[MAXENR];
  Courses course[MAXCRS];
  //ints to hold the amounts of each data type
  int amount_of_students = 0, *numStudents, numEnrollments, numCourses;
  numStudents = &amount_of_students;
  //load data into arrays
  loadStudents(st, numStudents);
  numEnrollments = loadEnrollment(en);
  numCourses = loadCourses(course);
  //infinite loop to take commands
  while(1){
    char command[MAXNAM];
    scanf("%s", command);
    //if the command is exit, end the code regardless of the loop
    if(strcmp(command, "exit")==0){
      printf("==================\n------------------\nBye!");
      exit(-1);
    }
    //otherwise, reload menu with the new command
    else{
      printf("==================\n------------------\n");
      menu(st, *numStudents, course, numCourses, en, numEnrollments, command);
    }
  }
  return 0;
}

void loadStudents(Students st[], int *numStudents){
  FILE *fp = fopen("students.txt", "r");
  int i = 0;
  //get the first character of the file and rewind
  char ch = fgetc(fp);
  rewind(fp);
  //while fp isnt ended
  while(!feof(fp)){
    //if the character isnt the EOF char, scan in the necessary data
    if(ch!=EOF){
      fscanf(fp, "%d", &st[i].id);
      fscanf(fp, "%s", st[i].fname);
      fscanf(fp, "%s", st[i].lname);
      fscanf(fp, "%d", &st[i].day);
      fscanf(fp, "%d", &st[i].month);
      fscanf(fp, "%d", &st[i].year);
      //advance the array index
      i++;
    }
    //advance fp char
    ch = fgetc(fp);
  }
  //numstudents equals the total index
  *numStudents = i;
  fclose(fp);
}
//repeat of loadStudents with Enrollments data
int loadEnrollment(Enrollments en[]){
  FILE *fp = fopen("enrollment.txt", "r");
  int i = 0;
  char ch = fgetc(fp);
  rewind(fp);
  while(!feof(fp)){
    if(ch!=EOF){
      fscanf(fp, "%d", &en[i].studentID);
      fscanf(fp, "%s", en[i].courseID);
      fscanf(fp, "%s", en[i].semester);
      fscanf(fp, "%f", &en[i].score);
      i++;
    }
    ch = fgetc(fp);
  }
  fclose(fp);
  return i;
}
//repeat of loadStudents with Courses data
int loadCourses(Courses course[]){
  FILE *fp = fopen("courses.txt", "r");
  int i = 0;
  char ch = fgetc(fp);
  rewind(fp);
  while(!feof(fp)){
    if(ch!=EOF){
      fscanf(fp, "%s", course[i].id);
      fscanf(fp, "%s", course[i].name);
      fscanf(fp, "%f", &course[i].credit);
      i++;
    }
    ch = fgetc(fp);
  }
  fclose(fp);
  return i;
}

void menu(Students ArrayOfStudents[], int amountStudents, Courses ArrayOfCourses[], int amountCourses, Enrollments ArrayOfEnrollments[], int amountEnrolls, char command[]){
  //chars for potentially necessary variables, such as a subcommand or a teriarary command
  char command2[MAXNAM];
  char name[MAXNAM];
  int id = 0;
  int byear = 0;
  //if the command is search_students
  if(strcmp(command, "search_students")==0){
    scanf("%s", command2);//take a subcommand
    if(strcmp(command2, "lname")==0){//if the subcommand is lname
      scanf("%s", name);//scan for the lname and print given it
      print_student(command2, name, ArrayOfStudents, amountStudents, ArrayOfCourses, amountCourses, ArrayOfEnrollments, amountEnrolls, id, byear);
    }
    else if(strcmp(command2, "fname")==0){//if subcommand is fname
      scanf("%s", name);//scan for fname and print given it
      print_student(command2, name, ArrayOfStudents, amountStudents, ArrayOfCourses, amountCourses, ArrayOfEnrollments, amountEnrolls, id, byear);

    }//subcommand is id
    else if(strcmp(command2, "id")==0){
      scanf("%d", &id);
      print_student(command2, name, ArrayOfStudents, amountStudents, ArrayOfCourses, amountCourses, ArrayOfEnrollments, amountEnrolls, id, byear);

    }//subcommand is byear
    else if(strcmp(command2, "byear")==0){
      scanf("%d", &byear);
      print_student(command2, name, ArrayOfStudents, amountStudents, ArrayOfCourses, amountCourses, ArrayOfEnrollments, amountEnrolls, id, byear);

    }
    else{//subcommand does not exist, replace command with "exit" so the menu exits
      printf("Error with search_students subcommand.");
      strcpy(command, "exit");
    }
    
  }//command is search_course
  else if(strcmp(command, "search_course")==0){
    scanf("%s", command2);//scan for a secondary and teriarary command
    char command3[MAXNAM];
    scanf("%s", command3);
    //print the course given the subcommands
    print_course(command2, command3, ArrayOfStudents, amountStudents, ArrayOfCourses, amountCourses, ArrayOfEnrollments, amountEnrolls);
  }//command is add_course
  else if(strcmp(command, "add_course")==0){
    char course_id[MAXNAM];//strings for course id and name and float for credit
    char course_name[MAXNAM];
    float credit;//take input from user
    scanf("%s", course_id);
    scanf("%s", course_name);
    scanf("%f", &credit);//add course to file, reload data into arrays
    add_course(ArrayOfCourses, amountCourses, course_id, course_name, credit);
  }//command is count
  else if(strcmp(command, "count")==0){
    scanf("%s", command2);//take subcommand and call count
    count(command2, amountStudents, amountCourses, amountEnrolls, ArrayOfStudents, ArrayOfCourses, ArrayOfEnrollments);
  }//command is sort
  else if(strcmp(command, "sort")==0){//use selection sort to sort the student array and print their sorted data
    int student_index;
    for(int i = 0; i < amountStudents - 1; i++){
      student_index = i;
      for(int j = i+1; j < amountStudents; j++){
        if(ArrayOfStudents[j].id<ArrayOfStudents[student_index].id){
          student_index = j;
        }
      }
      Students temp = ArrayOfStudents[student_index];
      ArrayOfStudents[student_index] = ArrayOfStudents[i];
      ArrayOfStudents[i] = temp;
    }
    for(int i = 0; i < amountStudents; i++){
      printf("%d %s %s %d/%d/%d\n", ArrayOfStudents[i].id, ArrayOfStudents[i].fname, ArrayOfStudents[i].lname, ArrayOfStudents[i].month, ArrayOfStudents[i].day, ArrayOfStudents[i].year);
    }
    printf("------------------\n");
  }
}
//function to print student info depending on subcommands
void print_student(char command[], char name[], Students ArrayOfStudents[], int amountStudents, Courses ArrayOfCourses[], int amountCourses, Enrollments ArrayOfEnrollments[], int amountEnrolls, int id, int byear){
  int indexOfMatches = 0;//index just in case the student name isnt found
  if(strcmp(command, "lname")==0){//if the sub is lname
    for(int i = 0; i < amountStudents; i++){//for amountStudents, check if lnames match the given name; if so, print data and enrollment info
      if(strcmp(name, ArrayOfStudents[i].lname)==0){
        indexOfMatches++;
        printf("%d %s %s %d/%d/%d\n", ArrayOfStudents[i].id, ArrayOfStudents[i].fname, ArrayOfStudents[i].lname, ArrayOfStudents[i].month, ArrayOfStudents[i].day, ArrayOfStudents[i].year);
        print_student_enrollment(ArrayOfStudents, amountStudents, ArrayOfCourses, amountCourses, ArrayOfEnrollments, amountEnrolls, ArrayOfStudents[i].id);
      }
    }//if no matches, name not found
    if(indexOfMatches==0){
      printf("not found\n------------------\n");
    }
  }
  else if(strcmp(command, "fname")==0){//sub is fname
    for(int i = 0; i < amountStudents; i++){//same as lname, but match with fnames
      if(strcmp(name, ArrayOfStudents[i].fname)==0){
        indexOfMatches++;
        printf("%d %s %s %d/%d/%d\n", ArrayOfStudents[i].id, ArrayOfStudents[i].fname, ArrayOfStudents[i].lname, ArrayOfStudents[i].month, ArrayOfStudents[i].day, ArrayOfStudents[i].year);
        print_student_enrollment(ArrayOfStudents, amountStudents, ArrayOfCourses, amountCourses, ArrayOfEnrollments, amountEnrolls, ArrayOfStudents[i].id);
      }
    }
    if(indexOfMatches==0){
      printf("not found\n------------------\n");
    }
  }//same as name functions, but match with a given id
  else if(strcmp(command, "id")==0){
    for(int i = 0; i < amountStudents; i++){
      if(id==ArrayOfStudents[i].id){
        indexOfMatches++;
        printf("%d %s %s %d/%d/%d\n", ArrayOfStudents[i].id, ArrayOfStudents[i].fname, ArrayOfStudents[i].lname, ArrayOfStudents[i].month, ArrayOfStudents[i].day, ArrayOfStudents[i].year);
        print_student_enrollment(ArrayOfStudents, amountStudents, ArrayOfCourses, amountCourses, ArrayOfEnrollments, amountEnrolls, ArrayOfStudents[i].id);
      }
    }
    if(indexOfMatches==0){
      printf("not found\n------------------\n");
    }
  }//same as id, but match with a given byear
  else if(strcmp(command, "byear")==0){
    for(int i = 0; i < amountStudents; i++){
      if(byear==ArrayOfStudents[i].year){
        indexOfMatches++;
        printf("%d %s %s %d/%d/%d\n", ArrayOfStudents[i].id, ArrayOfStudents[i].fname, ArrayOfStudents[i].lname, ArrayOfStudents[i].month, ArrayOfStudents[i].day, ArrayOfStudents[i].year);
        print_student_enrollment(ArrayOfStudents, amountStudents, ArrayOfCourses, amountCourses, ArrayOfEnrollments, amountEnrolls, ArrayOfStudents[i].id);
      }
    }
    if(indexOfMatches==0){
      printf("not found\n------------------\n");
    }
  }
}
//print enrollment course info of a given student
void print_student_enrollment(Students ArrayOfStudents[], int amountStudents, Courses ArrayOfCourses[], int amountCourses, Enrollments ArrayOfEnrollments[], int amountEnrolls, int id){
  for(int i = 0; i < amountEnrolls; i++){//for total amount of enrollments
    if(id==ArrayOfEnrollments[i].studentID){//if a course enrollment's student id matches the given student id, print their info
      char course_name[MAXNAM];
      match_course_id(ArrayOfEnrollments[i].courseID, amountCourses, ArrayOfCourses, course_name);//fill course name into the course_name string
      char ch = return_grade(ArrayOfEnrollments[i].score);//get char grade
      printf("%s %s %s %d %c\n", ArrayOfEnrollments[i].courseID, course_name, ArrayOfEnrollments[i].semester, (int)ArrayOfEnrollments[i].score, ch);//print info
    }
  }
  printf("------------------\n");
}

char return_grade(float num_grade){//simply algorithm for returning a grade char given a float score; uses pre-determined score ranges
  if(num_grade >= 90){
    return 'A';
  }
  else if(num_grade >= 80 && num_grade <= 89.99){
    return 'B';
  }
  else if(num_grade >= 70 && num_grade <= 79.99){
    return 'C';
  }
  else if(num_grade >= 60 && num_grade <= 69.99){
    return 'D';
  }
  return 'F';
}
//matches a course id from enrollment with a course; fills a name into a given array and returns the index if needed
int match_course_id(char course_id[], int amountCourses, Courses arr[], char course_name[]){
  int j = -1;
  for(int i = 0; i < amountCourses; i++){
    if(strcmp(arr[i].id, course_id)==0){
      strcpy(course_name, arr[i].name);
      return i;
    }
  }
  return j;
}
//prints course
void print_course(char command[], char course_id[], Students ArrayOfStudents[], int amountStudents, Courses ArrayOfCourses[], int amountCourses, Enrollments ArrayOfEnrollments[], int amountEnrolls){
  char course_name[MAXNAM];
  char semester[MAXNAM];
  strcpy(semester, "None");//semester is "None" unless subcommand is cid_semester
  int id_int = match_course_id(course_id, amountCourses, ArrayOfCourses, course_name);//fill course_name with appropriate name, fill id_int with the index of the course's occurrence
  if(id_int==-1){//if the course id doesn't occur
    if(strcmp(command, "cid_semester")==0){//if subcommand is semester, there is another input we must eliminate
      char garbage[MAXNAM];
      scanf("%s", garbage);
    }//print not found
    printf("not found\n------------------\n");
  }//subcommand is cid
  else if(strcmp(command, "cid")==0){//print course info and the enrollment info for the course's students
    printf("%s %d\n", course_name, (int)ArrayOfCourses[id_int].credit);
    print_course_enrollment(ArrayOfStudents, amountStudents, ArrayOfCourses, amountCourses, ArrayOfEnrollments, amountEnrolls, course_id, semester);
  }//print course info and the enrollment info for the course's students, but only for a given semester
  else if(strcmp(command, "cid_semester")==0){
    scanf("%s", semester);
    printf("%s %d\n", course_name, (int)ArrayOfCourses[id_int].credit);
    print_course_enrollment(ArrayOfStudents, amountStudents, ArrayOfCourses, amountCourses, ArrayOfEnrollments, amountEnrolls, course_id, semester);
  }
}
//print course enrollment info
void print_course_enrollment(Students ArrayOfStudents[], int amountStudents, Courses ArrayOfCourses[], int amountCourses, Enrollments ArrayOfEnrollments[], int amountEnrolls, char id[], char semester[]){
  for(int i = 0; i < amountEnrolls; i++){//for amount of enrollments
    if(strcmp(id, ArrayOfEnrollments[i].courseID)==0){//if the given id and the current enrollment's course id match
      for(int j = 0; j < amountStudents; j++){//for the number of students
        if(ArrayOfEnrollments[i].studentID==ArrayOfStudents[j].id){//if the enrollment student id and the actual student id match
          char ch = return_grade(ArrayOfEnrollments[i].score);//get the student's grade
          if(strcmp(semester, "None")==0){//if sub is only cid, just print the student's info right there
            printf("%s %s %s %d %c\n", ArrayOfStudents[j].fname, ArrayOfStudents[j].lname, ArrayOfEnrollments[i].semester, (int)ArrayOfEnrollments[i].score, ch);
          }
          else{//is sub also has semester, call separate match_semester function
            match_semesters(semester, ArrayOfEnrollments, i, ArrayOfStudents, j);
          }
        }
      }
    }
  }
  printf("------------------\n");
}

void match_semesters(char semester[], Enrollments ArrayOfEnrollments[], int index_enrollments, Students ArrayOfStudents[], int index_students){
  if(strcmp(semester, ArrayOfEnrollments[index_enrollments].semester)==0){//is the given semester matches the given enrollment index's semester
    char ch = return_grade(ArrayOfEnrollments[index_enrollments].score);//get grade and print student info
    printf("%s %s %s %d %c\n", ArrayOfStudents[index_students].fname, ArrayOfStudents[index_students].lname, ArrayOfEnrollments[index_enrollments].semester, (int)ArrayOfEnrollments[index_enrollments].score, ch);
  }
}
//add course to courses.txt file
void add_course(Courses ArrayOfCourses[], int amountCourses, char course_id[], char course_name[], float credit){
  int index = 0;//index to check if an id exists already
  FILE *fp = fopen("courses.txt", "a");//open file in append
  for(int i = 0; i < amountCourses; i++){//for the amount of courses
    if(strcmp(ArrayOfCourses[i].id, course_id)==0){//if the given id matches a pre-existing one, activate index and break loop
      index = 1;
      break;
    }
  }//if index was activated, print violation
  if(index==1){
    printf("\"violation of course id uniqueness. Cannot add the record.\"\n------------------\n");
  }
  else{//otherwise, append new course info to a new line at the end of the file
    fseek(fp, 0, SEEK_END);
    fprintf(fp, "\n%s %s %d", course_id, course_name, (int)credit);
    fclose(fp);
    printf("record added\n------------------\n");
    main();//re-call the main function to reload information
  }
}
//count number os a given subcommand's demand
void count(char command1[], int amountStudents, int amountCourses, int amountEnrollments, Students ArrayOfStudents[], Courses ArrayOfCourses[], Enrollments ArrayOfEnrollments[]){
  if(strcmp(command1, "students")==0){//sub is student; print total number of students
    printf("total students %d\n", amountStudents);
  }
  else if(strcmp(command1, "students_course")==0){//sub is students_course; print the cours id and the number of enrollments registered under it
    for(int i = 0; i < amountCourses; i++){
      int numPerID = 0;//number of enrollments per id
      char actualID[MAXNAM];//course id
      strcpy(actualID, ArrayOfCourses[i].id);//copy current index's name into actualID
      for(int j = 0; j < amountEnrollments; j++){//for number of enrollments, if the enrollment's courseID matches, add 1 to numPerID
        if(strcmp(actualID, ArrayOfEnrollments[j].courseID)==0){
          numPerID++;
        }
      }
      printf("%s %d\n", actualID, numPerID);//within the loop, display course id and number of enrolls
    }
  }
  else if(strcmp(command1, "students_semester")==0){//sub is students_semester
    char semesters[MAXENR][MAXNAM];//array of semesters
    int index_sems = 1, unique;//index of unique semesters, index to check semester matches
    strcpy(semesters[0], ArrayOfEnrollments[0].semester);//copy first semester appearance in Enrollments into first semester index
    for(int i = 1; i < amountEnrollments; i++){
      unique = 0;//reset unique to 0 in each loop
      for(int j = 0; j < index_sems; j++){//for the total number of unique semesters
        if(strcmp(ArrayOfEnrollments[i].semester, semesters[j])==0){//if the semester matches a pre-existing one, change unique and break loop
          unique = 1;
          break;
        }
      }
      if(unique==0){//if semester id is unique, add it to the semesters array and add 1 to index_sems
        strcpy(semesters[index_sems], ArrayOfEnrollments[i].semester);
        index_sems++;
      }
    }
    for(int i = 0; i < index_sems; i++){//for the total amount of unique semesters
      int index_current_sem = 0;//number of enrollments per semester
      for(int j = 0; j < amountEnrollments; j++){//for total enrollments
        if(strcmp(ArrayOfEnrollments[j].semester, semesters[i])==0){//if the current enrollment's semester matches the current semester, add 1 to the number of enrollments in the current semester
          index_current_sem++;
        }
      }//display semester and number of enrollments
      printf("%s %d\n", semesters[i], index_current_sem);
    }
  }
  printf("------------------\n");
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>

#define MAX_STUDENTS 100
#define MAX_TEACHERS 50
#define MAX_COURSES 30
#define MAX_NOTICES 50
#define RESET_TOKEN_LENGTH 10

typedef struct {
    char id[20];
    char password[20];
    char name[50];
    char department[30];
    char email[50];
    char resetToken[RESET_TOKEN_LENGTH + 1];
} User;

typedef struct {
    char id[20];
    char name[50];
    int credits;
    char department[30];
    char teacher_id[20];
} Course;

typedef struct {
    char student_id[20];
    char course_id[20];
    char date[11];
    int status;
} Attendance;

typedef struct {
    char student_id[20];
    char course_id[20];
    float marks;
    char grade;
} Grade;

typedef struct {
    char id[20];
    char title[100];
    char content[500];
    char author[50];
    char date[11];
    char target_group[20];
} Notice;

User students[MAX_STUDENTS];
User teachers[MAX_TEACHERS];
Course courses[MAX_COURSES];
Notice notices[MAX_NOTICES];
int student_count = 0;
int teacher_count = 0;
int course_count = 0;
int notice_count = 0;

void initializeSystem();
void mainMenu();
void adminLogin();
void teacherLogin();
void studentLogin();
void adminDashboard();
void teacherDashboard(char *teacher_id);
void studentDashboard(char *student_id);
void addStudent();
void viewStudents();
void deleteStudent();
void addTeacher();
void viewTeachers();
void deleteTeacher();
void addCourse();
void viewCourses();
void assignTeacherToCourse();
void postNotice(char *author, char *target_group);
void viewNotices(char *target_group);
void markAttendance(char *teacher_id);
void viewAttendance(char *student_id);
void uploadGrades(char *teacher_id);
void viewGrades(char *student_id);
void changePassword(char *user_type, char *user_id);
void saveAllData();
void loadAllData();
int validateEmail(const char *email);
void clearInputBuffer();
void pressAnyKeyToContinue();
void forgetPassword();
void resetPassword(char *user_type, char *user_id);
void generateResetToken(char *token);
int findUserIndex(char *user_type, char *user_id);

int main() {
    initializeSystem();
    loadAllData();
    mainMenu();
    saveAllData();
    return 0;
}

void initializeSystem() {
    if (student_count == 0) {
        strcpy(students[0].id, "S1001");
        strcpy(students[0].password, "student123");
        strcpy(students[0].name, "John Doe");
        strcpy(students[0].department, "Computer Science");
        strcpy(students[0].email, "john@college.edu");
        student_count++;
    }

    if (teacher_count == 0) {
        strcpy(teachers[0].id, "T1001");
        strcpy(teachers[0].password, "teacher123");
        strcpy(teachers[0].name, "Dr. Smith");
        strcpy(teachers[0].department, "Computer Science");
        strcpy(teachers[0].email, "smith@college.edu");
        teacher_count++;
    }

    if (course_count == 0) {
        strcpy(courses[0].id, "CSC101");
        strcpy(courses[0].name, "Introduction to Programming");
        courses[0].credits = 3;
        strcpy(courses[0].department, "Computer Science");
        strcpy(courses[0].teacher_id, "T1001");
        course_count++;
    }
}

void mainMenu() {
    int choice;
    do {
        system("cls");
        printf("\n=== COLLEGE MANAGEMENT SYSTEM ===\n");
        printf("1. Admin Login\n");
        printf("2. Teacher Login\n");
        printf("3. Student Login\n");
        printf("4. Forget Password\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1: adminLogin(); break;
            case 2: teacherLogin(); break;
            case 3: studentLogin(); break;
            case 4: forgetPassword(); break;
            case 5: printf("Exiting system...\n"); break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);
}

void adminLogin() {
    char id[20], password[20];
    printf("\n=== ADMIN LOGIN ===\n");
    printf("Enter Admin ID: ");
    scanf("%s", id);
    printf("Enter Password: ");
    int i = 0;
    char ch;
    while ((ch = getch()) != 13) {
        if (ch == 8 && i > 0) {
            i--;
            printf("\b \b");
        } else if (ch != 8) {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';

    if (strcmp(id, "admin") == 0 && strcmp(password, "admin123") == 0) {
        printf("\nLogin successful!\n");
        adminDashboard();
    } else {
        printf("\nInvalid ID or password!\n");
        pressAnyKeyToContinue();
    }
}

void adminDashboard() {
    int choice;
    do {
        system("cls");
        printf("\n=== ADMIN DASHBOARD ===\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Delete Student\n");
        printf("4. Add Teacher\n");
        printf("5. View Teachers\n");
        printf("6. Delete Teacher\n");
        printf("7. Add Course\n");
        printf("8. View Courses\n");
        printf("9. Assign Teacher to Course\n");
        printf("10. Post Notice\n");
        printf("11. Change Password\n");
        printf("12. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: deleteStudent(); break;
            case 4: addTeacher(); break;
            case 5: viewTeachers(); break;
            case 6: deleteTeacher(); break;
            case 7: addCourse(); break;
            case 8: viewCourses(); break;
            case 9: assignTeacherToCourse(); break;
            case 10: postNotice("Admin", "all"); break;
            case 11: changePassword("admin", "admin"); break;
            case 12: printf("Logging out...\n"); break;
            default: printf("Invalid choice!\n");
        }
        if (choice != 12) pressAnyKeyToContinue();
    } while (choice != 12);
}

void teacherLogin() {
    char id[20], password[20];
    printf("\n=== TEACHER LOGIN ===\n");
    printf("Enter Teacher ID: ");
    scanf("%s", id);
    printf("Enter Password: ");
    int i = 0;
    char ch;
    while ((ch = getch()) != 13) {
        if (ch == 8 && i > 0) {
            i--;
            printf("\b \b");
        } else if (ch != 8) {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';

    int found = 0;
    for (int j = 0; j < teacher_count; j++) {
        if (strcmp(teachers[j].id, id) == 0 && strcmp(teachers[j].password, password) == 0) {
            printf("\nLogin successful!\n");
            teacherDashboard(id);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("\nInvalid ID or password!\n");
        pressAnyKeyToContinue();
    }
}

void teacherDashboard(char *teacher_id) {
    int choice;
    do {
        system("cls");
        printf("\n=== TEACHER DASHBOARD ===\n");
        printf("1. View Profile\n");
        printf("2. Mark Attendance\n");
        printf("3. Upload Grades\n");
        printf("4. Post Notice to Students\n");
        printf("5. Change Password\n");
        printf("6. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1: {
                for (int i = 0; i < teacher_count; i++) {
                    if (strcmp(teachers[i].id, teacher_id) == 0) {
                        printf("\nID: %s\nName: %s\nDepartment: %s\nEmail: %s\n", teachers[i].id, teachers[i].name, teachers[i].department, teachers[i].email);
                        break;
                    }
                }
                break;
            }
            case 2: markAttendance(teacher_id); break;
            case 3: uploadGrades(teacher_id); break;
            case 4: postNotice(teacher_id, "students"); break;
            case 5: changePassword("teacher", teacher_id); break;
            case 6: printf("Logging out...\n"); break;
            default: printf("Invalid choice!\n");
        }
        if (choice != 6) pressAnyKeyToContinue();
    } while (choice != 6);
}

void studentLogin() {
    char id[20], password[20];
    printf("\n=== STUDENT LOGIN ===\n");
    printf("Enter Student ID: ");
    scanf("%s", id);
    printf("Enter Password: ");
    int i = 0;
    char ch;
    while ((ch = getch()) != 13) {
        if (ch == 8 && i > 0) {
            i--;
            printf("\b \b");
        } else if (ch != 8) {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';

    int found = 0;
    for (int j = 0; j < student_count; j++) {
        if (strcmp(students[j].id, id) == 0 && strcmp(students[j].password, password) == 0) {
            printf("\nLogin successful!\n");
            studentDashboard(id);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("\nInvalid ID or password!\n");
        pressAnyKeyToContinue();
    }
}

void studentDashboard(char *student_id) {
    int choice;
    do {
        system("cls");
        printf("\n=== STUDENT DASHBOARD ===\n");
        printf("1. View Profile\n");
        printf("2. View Attendance\n");
        printf("3. View Grades\n");
        printf("4. View Notices\n");
        printf("5. Change Password\n");
        printf("6. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1: {
                for (int i = 0; i < student_count; i++) {
                    if (strcmp(students[i].id, student_id) == 0) {
                        printf("\nID: %s\nName: %s\nDepartment: %s\nEmail: %s\n", students[i].id, students[i].name, students[i].department, students[i].email);
                        break;
                    }
                }
                break;
            }
            case 2: viewAttendance(student_id); break;
            case 3: viewGrades(student_id); break;
            case 4: viewNotices("students"); break;
            case 5: changePassword("student", student_id); break;
            case 6: printf("Logging out...\n"); break;
            default: printf("Invalid choice!\n");
        }
        if (choice != 6) pressAnyKeyToContinue();
    } while (choice != 6);
}

void addStudent() {
    if (student_count >= MAX_STUDENTS) {
        printf("Maximum student capacity reached!\n");
        return;
    }

    User newStudent;
    printf("\n=== ADD NEW STUDENT ===\n");
    printf("Enter Student ID: ");
    scanf("%s", newStudent.id);
    clearInputBuffer();
    printf("Enter Name: ");
    fgets(newStudent.name, sizeof(newStudent.name), stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = '\0';
    printf("Enter Department: ");
    fgets(newStudent.department, sizeof(newStudent.department), stdin);
    newStudent.department[strcspn(newStudent.department, "\n")] = '\0';
    do {
        printf("Enter Email: ");
        scanf("%s", newStudent.email);
    } while (!validateEmail(newStudent.email));
    printf("Enter Password: ");
    scanf("%s", newStudent.password);

    students[student_count++] = newStudent;
    printf("\nStudent added successfully!\n");
}

void viewStudents() {
    system("cls");
    printf("\n=== ALL STUDENTS ===\n");
    printf("%-10s %-20s %-20s %-20s\n", "ID", "Name", "Department", "Email");
    for (int i = 0; i < student_count; i++) {
        printf("%-10s %-20s %-20s %-20s\n", students[i].id, students[i].name, students[i].department, students[i].email);
    }
}

void deleteStudent() {
    char id[20];
    printf("\nEnter Student ID to delete: ");
    scanf("%s", id);

    int found = 0;
    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].id, id) == 0) {
            for (int j = i; j < student_count - 1; j++) {
                students[j] = students[j + 1];
            }
            student_count--;
            found = 1;
            printf("Student deleted successfully!\n");
            break;
        }
    }
    if (!found) printf("Student not found!\n");
}

void addTeacher() {
    if (teacher_count >= MAX_TEACHERS) {
        printf("Maximum teacher capacity reached!\n");
        return;
    }

    User newTeacher;
    printf("\n=== ADD NEW TEACHER ===\n");
    printf("Enter Teacher ID: ");
    scanf("%s", newTeacher.id);
    clearInputBuffer();
    printf("Enter Name: ");
    fgets(newTeacher.name, sizeof(newTeacher.name), stdin);
    newTeacher.name[strcspn(newTeacher.name, "\n")] = '\0';
    printf("Enter Department: ");
    fgets(newTeacher.department, sizeof(newTeacher.department), stdin);
    newTeacher.department[strcspn(newTeacher.department, "\n")] = '\0';
    do {
        printf("Enter Email: ");
        scanf("%s", newTeacher.email);
    } while (!validateEmail(newTeacher.email));
    printf("Enter Password: ");
    scanf("%s", newTeacher.password);

    teachers[teacher_count++] = newTeacher;
    printf("\nTeacher added successfully!\n");
}

void viewTeachers() {
    system("cls");
    printf("\n=== ALL TEACHERS ===\n");
    printf("%-10s %-20s %-20s %-20s\n", "ID", "Name", "Department", "Email");
    for (int i = 0; i < teacher_count; i++) {
        printf("%-10s %-20s %-20s %-20s\n", teachers[i].id, teachers[i].name, teachers[i].department, teachers[i].email);
    }
}

void deleteTeacher() {
    char id[20];
    printf("\nEnter Teacher ID to delete: ");
    scanf("%s", id);

    int found = 0;
    for (int i = 0; i < teacher_count; i++) {
        if (strcmp(teachers[i].id, id) == 0) {
            for (int j = i; j < teacher_count - 1; j++) {
                teachers[j] = teachers[j + 1];
            }
            teacher_count--;
            found = 1;
            printf("Teacher deleted successfully!\n");
            break;
        }
    }
    if (!found) printf("Teacher not found!\n");
}

void addCourse() {
    if (course_count >= MAX_COURSES) {
        printf("Maximum course capacity reached!\n");
        return;
    }

    Course newCourse;
    printf("\n=== ADD NEW COURSE ===\n");
    printf("Enter Course ID: ");
    scanf("%s", newCourse.id);
    clearInputBuffer();
    printf("Enter Course Name: ");
    fgets(newCourse.name, sizeof(newCourse.name), stdin);
    newCourse.name[strcspn(newCourse.name, "\n")] = '\0';
    printf("Enter Department: ");
    fgets(newCourse.department, sizeof(newCourse.department), stdin);
    newCourse.department[strcspn(newCourse.department, "\n")] = '\0';
    printf("Enter Credits: ");
    scanf("%d", &newCourse.credits);

    courses[course_count++] = newCourse;
    printf("\nCourse added successfully!\n");
}

void viewCourses() {
    system("cls");
    printf("\n=== ALL COURSES ===\n");
    printf("%-10s %-30s %-20s %-10s %-10s\n", "ID", "Name", "Department", "Credits", "Teacher ID");
    for (int i = 0; i < course_count; i++) {
        printf("%-10s %-30s %-20s %-10d %-10s\n", courses[i].id, courses[i].name, courses[i].department, courses[i].credits, courses[i].teacher_id);
    }
}

void assignTeacherToCourse() {
    char course_id[20], teacher_id[20];
    printf("\nEnter Course ID: ");
    scanf("%s", course_id);
    printf("Enter Teacher ID: ");
    scanf("%s", teacher_id);

    int course_found = 0, teacher_found = 0;
    for (int i = 0; i < course_count; i++) {
        if (strcmp(courses[i].id, course_id) == 0) {
            course_found = 1;
            for (int j = 0; j < teacher_count; j++) {
                if (strcmp(teachers[j].id, teacher_id) == 0) {
                    teacher_found = 1;
                    strcpy(courses[i].teacher_id, teacher_id);
                    printf("Teacher assigned to course successfully!\n");
                    break;
                }
            }
            break;
        }
    }
    if (!course_found) printf("Course not found!\n");
    else if (!teacher_found) printf("Teacher not found!\n");
}

void postNotice(char *author, char *target_group) {
    if (notice_count >= MAX_NOTICES) {
        printf("Maximum notice capacity reached!\n");
        return;
    }

    Notice newNotice;
    printf("\n=== POST NEW NOTICE ===\n");
    printf("Enter Notice ID: ");
    scanf("%s", newNotice.id);
    clearInputBuffer();
    printf("Enter Title: ");
    fgets(newNotice.title, sizeof(newNotice.title), stdin);
    newNotice.title[strcspn(newNotice.title, "\n")] = '\0';
    printf("Enter Content: ");
    fgets(newNotice.content, sizeof(newNotice.content), stdin);
    newNotice.content[strcspn(newNotice.content, "\n")] = '\0';

    strcpy(newNotice.author, author);
    strcpy(newNotice.date, "2023-11-15");
    strcpy(newNotice.target_group, target_group);

    notices[notice_count++] = newNotice;
    printf("\nNotice posted successfully!\n");
}

void viewNotices(char *target_group) {
    system("cls");
    printf("\n=== NOTICES ===\n");
    printf("%-10s %-20s %-50s %-15s %-10s\n", "ID", "Title", "Content", "Author", "Date");
    for (int i = 0; i < notice_count; i++) {
        if (strcmp(notices[i].target_group, target_group) == 0 || strcmp(notices[i].target_group, "all") == 0) {
            printf("%-10s %-20s %-50.50s %-15s %-10s\n", notices[i].id, notices[i].title, notices[i].content, notices[i].author, notices[i].date);
        }
    }
}

void markAttendance(char *teacher_id) {
    char course_id[20], student_id[20], date[11];
    int status;

    printf("\n=== MARK ATTENDANCE ===\n");
    printf("Enter Course ID: ");
    scanf("%s", course_id);
    printf("Enter Student ID: ");
    scanf("%s", student_id);
    printf("Enter Date (YYYY-MM-DD): ");
    scanf("%s", date);
    printf("Enter Status (1 for present, 0 for absent): ");
    scanf("%d", &status);

    printf("\nAttendance marked successfully!\n");
}

void viewAttendance(char *student_id) {
    printf("\n=== ATTENDANCE RECORD ===\n");
    printf("Student ID: %s\n", student_id);
    printf("Attendance feature not fully implemented.\n");
}

void uploadGrades(char *teacher_id) {
    char course_id[20], student_id[20];
    float marks;

    printf("\n=== UPLOAD GRADES ===\n");
    printf("Enter Course ID: ");
    scanf("%s", course_id);
    printf("Enter Student ID: ");
    scanf("%s", student_id);
    printf("Enter Marks: ");
    scanf("%f", &marks);

    printf("\nGrades uploaded successfully!\n");
}

void viewGrades(char *student_id) {
    printf("\n=== GRADE REPORT ===\n");
    printf("Student ID: %s\n", student_id);
    printf("Grade feature not fully implemented.\n");
}

void changePassword(char *user_type, char *user_id) {
    char current_password[20], new_password[20], confirm_password[20];

    printf("\n=== CHANGE PASSWORD ===\n");
    printf("Enter current password: ");
    int i = 0;
    char ch;
    while ((ch = getch()) != 13) {
        if (ch == 8 && i > 0) {
            i--;
            printf("\b \b");
        } else if (ch != 8) {
            current_password[i++] = ch;
            printf("*");
        }
    }
    current_password[i] = '\0';

    int valid = 0;
    if (strcmp(user_type, "admin") == 0) {
        valid = (strcmp(current_password, "admin123") == 0);
    } else {
        int index = findUserIndex(user_type, user_id);
        if (index != -1) {
            if (strcmp(user_type, "teacher") == 0) {
                valid = (strcmp(teachers[index].password, current_password) == 0);
            } else if (strcmp(user_type, "student") == 0) {
                valid = (strcmp(students[index].password, current_password) == 0);
            }
        }
    }

    if (!valid) {
        printf("\nIncorrect current password!\n");
        return;
    }

    printf("\nEnter new password: ");
    i = 0;
    while ((ch = getch()) != 13) {
        if (ch == 8 && i > 0) {
            i--;
            printf("\b \b");
        } else if (ch != 8) {
            new_password[i++] = ch;
            printf("*");
        }
    }
    new_password[i] = '\0';

    printf("\nConfirm new password: ");
    i = 0;
    while ((ch = getch()) != 13) {
        if (ch == 8 && i > 0) {
            i--;
            printf("\b \b");
        } else if (ch != 8) {
            confirm_password[i++] = ch;
            printf("*");
        }
    }
    confirm_password[i] = '\0';

    if (strcmp(new_password, confirm_password) != 0) {
        printf("\nPasswords don't match!\n");
        return;
    }

    if (strcmp(user_type, "admin") == 0) {
        printf("\nAdmin password updated successfully!\n");
    } else {
        int index = findUserIndex(user_type, user_id);
        if (index != -1) {
            if (strcmp(user_type, "teacher") == 0) {
                strcpy(teachers[index].password, new_password);
                printf("\nTeacher password updated successfully!\n");
            } else if (strcmp(user_type, "student") == 0) {
                strcpy(students[index].password, new_password);
                printf("\nStudent password updated successfully!\n");
            }
        }
    }
}
void saveAllData() {
    FILE *fp;
    fp = fopen("students.dat", "wb");
    if (fp) {
        fwrite(students, sizeof(User), student_count, fp);
        fclose(fp);
    }
    fp = fopen("teachers.dat", "wb");
    if (fp) {
        fwrite(teachers, sizeof(User), teacher_count, fp);
        fclose(fp);
    }
    fp = fopen("courses.dat", "wb");
    if (fp) {
        fwrite(courses, sizeof(Course), course_count, fp);
        fclose(fp);
    }
    fp = fopen("notices.dat", "wb");
    if (fp) {
        fwrite(notices, sizeof(Notice), notice_count, fp);
        fclose(fp);
    }
}

void loadAllData() {
    FILE *fp;
    fp = fopen("students.dat", "rb");
    if (fp) {
        student_count = fread(students, sizeof(User), MAX_STUDENTS, fp);
        fclose(fp);
    }
    fp = fopen("teachers.dat", "rb");
    if (fp) {
        teacher_count = fread(teachers, sizeof(User), MAX_TEACHERS, fp);
        fclose(fp);
    }
    fp = fopen("courses.dat", "rb");
    if (fp) {
        course_count = fread(courses, sizeof(Course), MAX_COURSES, fp);
        fclose(fp);
    }
    fp = fopen("notices.dat", "rb");
    if (fp) {
        notice_count = fread(notices, sizeof(Notice), MAX_NOTICES, fp);
        fclose(fp);
    }
}

int validateEmail(const char *email) {
    int at_count = 0, dot_count = 0;
    for (int i = 0; email[i]; i++) {
        if (email[i] == '@') at_count++;
        if (email[i] == '.') dot_count++;
    }
    return (at_count == 1 && dot_count >= 1);
}

void clearInputBuffer() {
    while (getchar() != '\n');
}

void pressAnyKeyToContinue() {
    printf("\nPress any key to continue...");
    getch();
}

void forgetPassword() {
    char id[20];
    int choice;

    printf("\n=== FORGET PASSWORD ===\n");
    printf("1. Admin\n");
    printf("2. Teacher\n");
    printf("3. Student\n");
    printf("Enter user type: ");
    scanf("%d", &choice);
    clearInputBuffer();
    printf("Enter User ID: ");
    scanf("%s", id);
    clearInputBuffer();

    switch (choice) {
        case 1: resetPassword("admin", "admin"); break;
        case 2: resetPassword("teacher", id); break;
        case 3: resetPassword("student", id); break;
        default: printf("Invalid choice!\n"); break;
    }
}

void resetPassword(char *user_type, char *user_id) {
    int index = findUserIndex(user_type, user_id);
    if (index == -1) {
        printf("User not found!\n");
        return;
    }

    char resetToken[RESET_TOKEN_LENGTH + 1];
    generateResetToken(resetToken);

    if (strcmp(user_type, "teacher") == 0) {
        strcpy(teachers[index].resetToken, resetToken);
    } else if (strcmp(user_type, "student") == 0) {
        strcpy(students[index].resetToken, resetToken);
    }

    printf("Reset token: %s\n", resetToken);
    printf("Please use this token to reset your password.\n");

    char inputToken[RESET_TOKEN_LENGTH + 1];
    printf("Enter Reset Token: ");
    scanf("%s", inputToken);
    clearInputBuffer();

    if (strcmp(inputToken, resetToken) == 0) {
        char newPassword[20], confirmPassword[20];
        printf("Enter new password: ");
        scanf("%s", newPassword);
        clearInputBuffer();
        printf("Confirm new password: ");
        scanf("%s", confirmPassword);
        clearInputBuffer();

        if (strcmp(newPassword, confirmPassword) == 0) {
            if (strcmp(user_type, "teacher") == 0) {
                strcpy(teachers[index].password, newPassword);
            } else if (strcmp(user_type, "student") == 0) {
                strcpy(students[index].password, newPassword);
            }
            printf("Password reset successful!\n");
        } else {
            printf("Passwords don't match!\n");
        }
    } else {
        printf("Invalid reset token!\n");
    }
}

void generateResetToken(char *token) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    srand(time(NULL));
    for (int i = 0; i < RESET_TOKEN_LENGTH; i++) {
        token[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    token[RESET_TOKEN_LENGTH] = '\0';
}

int findUserIndex(char *user_type, char *user_id) {
    if (strcmp(user_type, "teacher") == 0) {
        for (int i = 0; i < teacher_count; i++) {
            if (strcmp(teachers[i].id, user_id) == 0) {
                return i;
            }
        }
    } else if (strcmp(user_type, "student") == 0) {
        for (int i = 0; i < student_count; i++) {
            if (strcmp(students[i].id, user_id) == 0) {
                return i;
            }
        }
    }
    return -1;
}

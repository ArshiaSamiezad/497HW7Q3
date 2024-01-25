#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct department
{
    int depID;
    char firstName[200][100];
    char lastName[200][100];
    int ID[200];
    int numStudents;

    char masterFirstName[200][100];
    char masterLastName[200][100];
    int masterID[200];

    char courseName[200][100];
    char coursePreend[200][100];
    int credit[200];
    int capacity[200];
    int registered[200];
    int numCourses;
};

struct student
{
    char firstName[100];
    char lastName[100];
    int ID;
    int depID;
    struct department *dept;

    char courseName[100][100];
    char masterFirstName[100][100];
    char masterLastName[100][100];
    int masterID[100];
    int credit[100];
    int numCourses;

    char passCourseName[100][100];
    float passMark[100];
    float passCredit[100];
    int passNumCourses;
    float gpa;
};

struct master
{
    char firstName[100];
    char lastName[100];
    int ID;

    char courseName[200][100];
    int depID[200];
    int numCourses;
};

int main()
{
    char input[1000];
    char inputCpy[1000];
    fgets(input, 1000, stdin);
    strcpy(inputCpy, input);

    int depIndex = 0;
    struct department *dp[100];
    for (int i = 0; i < 100; i++)
    {
        dp[i] = malloc(sizeof(struct department));
    }

    int stdIndex = 0;
    struct student *std[100];
    for (int i = 0; i < 100; i++)
    {
        std[i] = malloc(sizeof(struct student));
    }

    int mstrIndex = 0;
    struct student *mstr[100];
    for (int i = 0; i < 100; i++)
    {
        mstr[i] = malloc(sizeof(struct master));
    }

    int loginLevel = 0; // 0 = none, 1 = student, 2 = master, 3 = department
    char loginFirstName[100];
    char loginLastName[100];
    int loginID;
    int loginStudentIndex;
    int loginDepIndex;
    int loginMasterIndex;

    while (strcmp(input, "exit\n"))
    {
        char *inputList[1000];

        inputList[0] = strtok(input, " \0\n");
        int index = 0;
        while (inputList[index])
        {
            index++;
            inputList[index] = strtok(NULL, " \0\n");
        }
        inputList[index] = '\0';
        // printf("%d %s %s\n", index, inputList[0], inputList[1]);

        // register department
        if (strncmp(inputCpy, "register-d", 10) == 0)
        {
            if (inputCpy[11] == '-' || strlen(inputCpy) == 11 || strlen(inputCpy) == 12)
            {
                printf("Invalid inputs!\n");
            }
            else
            {
                int depNotExist = 1;
                for (int i = 0; i < depIndex; i++)
                {
                    if (strtol(inputList[1], NULL, 10) == dp[i]->depID)
                    {
                        printf("The department account already exists!\n");
                        depNotExist = 0;
                    }
                }
                if (depNotExist)
                {
                    dp[depIndex]->depID = strtol(inputList[1], NULL, 10);
                    dp[depIndex]->numStudents = 0;
                    dp[depIndex]->numCourses = 0;
                    depIndex++;
                    printf("The department added successfully\n");
                }
            }
        }

        // register student
        else if (strncmp(inputCpy, "register-s", 10) == 0)
        {
            if (index < 5)
            {
                printf("Invalid inputs!\n");
            }
            else if (inputList[4][0] == '-')
            {
                printf("Invalid department code!\n");
            }
            else
            {
                std[stdIndex]->gpa = 0;
                strcpy(std[stdIndex]->firstName, inputList[1]);
                strcpy(std[stdIndex]->lastName, inputList[2]);
                std[stdIndex]->ID = strtol(inputList[3], NULL, 10);
                std[stdIndex]->depID = strtol(inputList[4], NULL, 10);
                std[stdIndex]->passNumCourses = 0;
                // inja badan check konam ke age dep vojood nadasht error bede ya na
                for (int i = 0; i < depIndex; i++)
                {
                    if (dp[i]->depID == std[stdIndex]->depID)
                    {
                        std[stdIndex]->dept = dp[i];
                        strcpy(dp[i]->firstName[dp[i]->numStudents], std[stdIndex]->firstName);
                        strcpy(dp[i]->lastName[dp[i]->numStudents], std[stdIndex]->lastName);
                        dp[i]->ID[dp[i]->numStudents] = std[stdIndex]->ID;
                        dp[i]->numStudents++;
                    }
                }

                fgets(input, 1000, stdin);
                strcpy(inputCpy, input);
                while (strcmp(input, "end\n"))
                {
                    char *token[1000];

                    token[0] = strtok(input, " \0\n");
                    int indexStud = 0;
                    while (inputList[indexStud])
                    {
                        indexStud++;
                        token[indexStud] = strtok(NULL, " \0\n");
                    }

                    token[indexStud] = '\0';

                    strcpy(std[stdIndex]->passCourseName[std[stdIndex]->passNumCourses], token[0]);
                    std[stdIndex]->passMark[std[stdIndex]->passNumCourses] = atof(token[1]);
                    std[stdIndex]->passCredit[std[stdIndex]->passNumCourses] = strtol(token[2], NULL, 10);

                    std[stdIndex]->passNumCourses++;
                    fgets(input, 1000, stdin);
                    strcpy(inputCpy, input);
                }
                float sumpassCredits = 0;
                float sumpassMarks = 0;
                for (int i = 0; i < std[stdIndex]->passNumCourses; i++)
                {
                    sumpassCredits += std[stdIndex]->passCredit[i];
                    sumpassMarks += std[stdIndex]->passMark[i] * std[stdIndex]->passCredit[i];
                }
                std[stdIndex]->gpa = (float)(sumpassMarks) / (float)(sumpassCredits);
                printf("Registered successfully!\n");
                stdIndex++;
            }
        }

        // register master
        else if (strncmp(inputCpy, "register-m", 10) == 0)
        {
            if (index < 4)
            {
                printf("Invalid inputs!\n");
            }
            else
            {
                // inja badan check konam ke age dep vojood nadasht error bede ya na

                strcpy(mstr[mstrIndex]->firstName, inputList[1]);
                strcpy(mstr[mstrIndex]->lastName, inputList[2]);
                mstr[mstrIndex]->ID = strtol(inputList[3], NULL, 10);
                mstr[mstrIndex]->numCourses = 0;

                printf("Registered successfully\n"); // momken ast ! niaz dashte bashad
                mstrIndex++;
            }
        }

        // login student
        else if (strncmp(inputCpy, "login-s", 7) == 0)
        {
            if (loginLevel)
            {
                printf("You can't login without logging out of prev account!\n");
            }
            else if (index < 4 || inputList[3][0] == '-')
            {
                printf("Invalid inputs!\n");
            }
            else
            {
                int studentNotFound = 1;
                int idIsNotTrue = 1;
                for (int i = 0; i < stdIndex; i++)
                {
                    if ((strcmp(inputList[1], std[i]->firstName) == 0) && (strcmp(inputList[2], std[i]->lastName) == 0))
                    {
                        studentNotFound = 0;
                        if (std[i]->ID == strtol(inputList[3], NULL, 10))
                        {
                            idIsNotTrue = 0;
                            loginStudentIndex = i;
                        }
                    }
                }

                if (studentNotFound)
                {
                    printf("No student exists with given information!\n");
                }
                else if (idIsNotTrue)
                {
                    printf("Wrong id!\n");
                }
                else
                {
                    loginLevel = 1;
                    strcpy(loginFirstName, std[loginStudentIndex]->firstName);
                    strcpy(loginLastName, std[loginStudentIndex]->lastName);
                    loginID = std[loginStudentIndex]->ID;

                    printf("You're logged in as a student!\n");
                }
            }
        }

        // logout
        else if (strncmp(inputCpy, "logout", 6) == 0)
        {
            loginLevel = 0;
            strcpy(loginFirstName, "");
            strcpy(loginLastName, "");
            loginID = -1;
            printf("You're logged out!\n");
        }

        // show gpa
        else if (strncmp(inputCpy, "show-gpa", 8) == 0)
        {
            if (loginLevel != 1)
            {
                printf("You should login as a student to calculate gpa!\n");
            }
            else
            {
                float sum = 0;
                float passCredit = 0;
                for (int i = 0; i < std[loginStudentIndex]->passNumCourses; i++)
                {
                    sum += (std[loginStudentIndex]->passMark[i]) * (std[loginStudentIndex]->passCredit[i]);
                    passCredit += std[loginStudentIndex]->passCredit[i];
                }
                float gpa = sum / passCredit;
                printf("GPA: %.2f\n", gpa);
            }
        }

        // show passed courses
        else if (strncmp(inputCpy, "show-passed-courses", 19) == 0)
        {
            if (loginLevel != 1)
            {
                printf("You should login as a student to show passed courses!\n");
            }
            else
            {
                for (int i = 0; i < std[loginStudentIndex]->passNumCourses; i++)
                {
                    printf("%d Course: %s , Grade: %.2f\n", i + 1, std[loginStudentIndex]->passCourseName[i], std[loginStudentIndex]->passMark[i]);
                }
            }
        }

        // show total credits
        else if (strncmp(inputCpy, "show-total-credits", 18) == 0)
        {
            if (loginLevel != 1)
            {
                printf("You should login as a student to show number of credits!\n");
            }
            else
            {
                int sumpassCredits = 0;
                for (int i = 0; i < std[loginStudentIndex]->passNumCourses; i++)
                {
                    sumpassCredits += std[loginStudentIndex]->passCredit[i];
                }
                printf("Credits: %d\n", sumpassCredits);
            }
        }

        // login department
        else if (strncmp(inputCpy, "login-d", 7) == 0)
        {
            if (loginLevel)
            {
                printf("You can't login without logging out of prev account!\n");
            }
            else
            {
                int depNotExist = 1;
                for (int i = 0; i < depIndex; i++)
                {
                    if (strtol(inputList[1], NULL, 10) == dp[i]->depID)
                    {
                        depNotExist = 0;
                        loginDepIndex = i;
                        break;
                    }
                }
                if (depNotExist)
                {
                    printf("No department exists with given information!\n");
                }
                else
                {
                    loginLevel = 3;
                    loginID = dp[loginDepIndex]->depID;
                    printf("You're logged in as a department!\n");
                }
            }
        }

        // login master
        else if (strncmp(inputCpy, "login-m", 7) == 0)
        {
            if (loginLevel)
            {
                printf("You can't login without logging out of prev account!\n");
            }
            else if (index < 4 || inputList[3][0] == '-')
            {
                printf("Invalid inputs!\n");
            }
            else
            {
                int masterNotFound = 1;
                int idIsNotTrue = 1;
                for (int i = 0; i < mstrIndex; i++)
                {
                    if ((strcmp(inputList[1], mstr[i]->firstName) == 0) && (strcmp(inputList[2], mstr[i]->lastName) == 0))
                    {
                        masterNotFound = 0;
                        if (mstr[i]->ID == strtol(inputList[3], NULL, 10))
                        {
                            idIsNotTrue = 0;
                            loginMasterIndex = i;
                        }
                    }
                }

                if (masterNotFound)
                {
                    printf("No master exists with given information!\n");
                }
                else if (idIsNotTrue)
                {
                    printf("Wrong id!\n");
                }
                else
                {
                    loginLevel = 2;
                    strcpy(loginFirstName, mstr[loginMasterIndex]->firstName);
                    strcpy(loginLastName, mstr[loginMasterIndex]->lastName);
                    loginID = mstr[loginMasterIndex]->ID;

                    printf("You're logged in as a master!\n");
                }
            }
        }

        else if (strncmp(inputCpy, "create-course", 13) == 0)
        {
            if (loginLevel != 2)
            {
                printf("You should login as a master to create course!\n");
            }
            else if (index < 5)
            {
                printf("Invalid inputs!\n");
            }
            else
            {
                for (int i = 0; i < depIndex; i++)
                {
                    if (dp[i]->depID == strtol(inputList[4], NULL, 10))
                    {
                        strcpy(dp[i]->courseName[dp[i]->numCourses], inputList[1]);
                        dp[i]->credit[dp[i]->numCourses] = strtol(inputList[2], NULL, 10);
                        dp[i]->capacity[dp[i]->numCourses] = strtol(inputList[3], NULL, 10);
                        strcpy(dp[i]->masterFirstName[dp[i]->numCourses], loginFirstName);
                        strcpy(dp[i]->masterLastName[dp[i]->numCourses], loginLastName);
                        dp[i]->masterID[dp[i]->numCourses] = loginID;

                        strcpy(mstr[loginMasterIndex]->courseName[mstr[loginMasterIndex]->numCourses], inputList[1]);
                        mstr[loginMasterIndex]->depID = dp[i]->depID;
                        if (index > 5)
                        {
                            strcpy(dp[i]->coursePreend[dp[i]->numCourses], inputList[5]);
                        }
                        else
                        {
                            strcpy(dp[i]->courseName[dp[i]->numCourses], "");
                        }
                        dp[i]->numCourses++;
                        mstr[loginMasterIndex]->numCourses++;
                        printf("Course added successfully\n");
                        break;
                    }
                }
            }
        }

        // delete course master
        else if (strncmp(inputCpy, "delete_course", 13) == 0)
        {
            int doesntExist = 1;
            if (loginLevel == 1)
            { // ya loginLevel!=2
                printf("You don't have access to delete this course!\n");
            }

            else if (loginLevel == 2)
            {

                for (int i = 0; i < mstr[loginMasterIndex]->numCourses; i++)
                {
                    inputList[1][strlen(inputList[1]) - 1] = '\0';
                    if (strcmp(mstr[loginMasterIndex]->courseName[i], inputList[1]) == 0)
                    {
                        for (int j = 0; j < depIndex; j++)
                        {
                            for (int k = 0; k < dp[j]->numCourses; k++)
                            {
                                if (strcmp(dp[j]->courseName[k], inputList[1]) == 0 && loginID == dp[j]->masterID[k])
                                {
                                    for (int l = k; l < dp[j]->numCourses - 1; l++)
                                    {
                                        strcpy(dp[j]->courseName[l], dp[j]->courseName[l + 1]);
                                        strcpy(dp[j]->coursePreend[l], dp[j]->coursePreend[l + 1]);
                                        dp[j]->credit[l] = dp[j]->credit[l + 1];
                                        dp[j]->capacity[l] = dp[j]->capacity[l + 1];
                                        dp[j]->registered[l] = dp[j]->registered[l + 1];

                                        strcpy(dp[j]->masterFirstName[l], dp[j]->masterFirstName[l + 1]);
                                        strcpy(dp[j]->masterLastName[l], dp[j]->masterLastName[l + 1]);
                                        dp[j]->masterID[l] = dp[j]->masterID[l + 1];
                                        doesntExist = 0;
                                    }
                                    dp[i]->numCourses--;
                                    break;
                                }
                            }
                        }
                        for (int j = 0; j < stdIndex; j++)
                        {
                            for (int k = 0; k < std[j]->numCourses; k++)
                            {
                                if (strcmp(std[j]->courseName[k], inputList[1]) == 0)
                                {
                                    for (int l = k; l < std[j]->numCourses - 1; l++)
                                    {
                                        strcpy(std[j]->courseName[l], std[j]->courseName[l + 1]);
                                        std[j]->credit[l] = std[j]->credit[l + 1];
                                        dp[j]->capacity[l] = dp[j]->capacity[l + 1];
                                        dp[j]->registered[l] = dp[j]->registered[l + 1];

                                        strcpy(dp[j]->masterFirstName[l], dp[j]->masterFirstName[l + 1]);
                                        strcpy(dp[j]->masterLastName[l], dp[j]->masterLastName[l + 1]);
                                        dp[j]->masterID[l] = dp[j]->masterID[l + 1];
                                        doesntExist = 0;
                                    }
                                    dp[i]->numCourses--;
                                }
                            }
                        }
                        printf("Course deleted successfully!\n");
                    }
                }
            }
            else if (doesntExist)
            {
                printf("Course does not exist\n");
            }
        }

        // show-top-5
        else if (strncmp(inputCpy, "show-top-5", 10) == 0)
        {
            if (loginLevel != 3)
            {
                printf("Only a department account can access top 5 scores!\n");
            }
            else
            {
                float gpa1 = 0;
                float gpa2 = 0;
                float gpa3 = 0;
                float gpa4 = 0;
                float gpa5 = 0;
                int indexgpa1 = 0;
                int indexgpa2 = 0;
                int indexgpa3 = 0;
                int indexgpa4 = 0;
                int indexgpa5 = 0;
                for (int i = 0; i < stdIndex; i++)
                {
                    if (std[i]->depID == loginID)
                    {
                        if (std[i]->gpa > gpa1)
                        {
                            gpa5 = gpa4;
                            gpa4 = gpa3;
                            gpa3 = gpa2;
                            gpa2 = gpa1;
                            gpa1 = std[i]->gpa;
                            indexgpa1 = i;
                        }
                        else if (std[i]->gpa > gpa2)
                        {
                            gpa5 = gpa4;
                            gpa4 = gpa3;
                            gpa3 = gpa2;
                            gpa2 = std[i]->gpa;
                            indexgpa2 = i;
                        }
                        else if (std[i]->gpa > gpa3)
                        {
                            gpa5 = gpa4;
                            gpa4 = gpa3;
                            gpa3 = std[i]->gpa;
                            indexgpa3 = i;
                        }
                        else if (std[i]->gpa > gpa4)
                        {
                            gpa5 = gpa4;
                            gpa4 = std[i]->gpa;
                            indexgpa4 = i;
                        }
                        else if (std[i]->gpa > gpa5)
                        {
                            gpa5 = std[i]->gpa;
                            indexgpa5 = i;
                        }
                    }
                }
                printf("%s %s %.2f\n", std[indexgpa1]->firstName, std[indexgpa1]->lastName, gpa1);
                printf("%s %s %.2f\n", std[indexgpa2]->firstName, std[indexgpa2]->lastName, gpa2);
                printf("%s %s %.2f\n", std[indexgpa3]->firstName, std[indexgpa3]->lastName, gpa3);
                printf("%s %s %.2f\n", std[indexgpa4]->firstName, std[indexgpa4]->lastName, gpa4);
                printf("%s %s %.2f\n", std[indexgpa5]->firstName, std[indexgpa5]->lastName, gpa5);
            }
        }

        // delete_course master
        else if ((strncmp(inputCpy, "delete_course", 13) == 0) && loginLevel == 2)
        {
        }

        else
            printf("Invalid command!\n");
        // printf("previous input was %s. waiting to new input\n", input);
        fgets(input, 1000, stdin);
        strcpy(inputCpy, input);
    }
}

// by arshia samiezad 402111497

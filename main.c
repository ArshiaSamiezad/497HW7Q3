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
    int totalCredit;
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
    struct master *mstr[100];
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

    while (strncmp(input, "exit", 4))
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
        inputList[index - 1][strlen(inputList[index - 1]) - 1] = '\0';

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
                std[stdIndex]->totalCredit = 0;
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
                        mstr[loginMasterIndex]->depID[mstr[loginMasterIndex]->numCourses] = dp[i]->depID;
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
            int isInAnotherDep = 0;
            if (loginLevel == 1)
            { // ya loginLevel!=2
                printf("You don't have access to delete this course!\n");
            }

            else if (loginLevel == 2)
            {

                for (int i = 0; i < mstr[loginMasterIndex]->numCourses; i++)
                {
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
                                    }
                                    doesntExist = 0;

                                    dp[j]->numCourses--;
                                    // printf("dp[%d] numcourses is %d", j, dp[j]->numCourses);
                                    break;
                                }
                            }
                        }
                        for (int j = 0; j < stdIndex; j++)
                        {
                            for (int k = 0; k < std[j]->numCourses; k++)
                            {
                                if ((strcmp(std[j]->courseName[k], inputList[1]) == 0) && loginID == std[j]->masterID[k])
                                {
                                    doesntExist = 0;
                                    std[j]->totalCredit -= std[j]->credit[k];
                                    for (int l = k; l < std[j]->numCourses - 1; l++)
                                    {
                                        strcpy(std[j]->courseName[l], std[j]->courseName[l + 1]);
                                        std[j]->credit[l] = std[j]->credit[l + 1];

                                        strcpy(std[j]->masterFirstName[l], std[j]->masterFirstName[l + 1]);
                                        strcpy(std[j]->masterLastName[l], std[j]->masterLastName[l + 1]);
                                        std[j]->masterID[l] = std[j]->masterID[l + 1];
                                    }
                                    std[j]->numCourses--;
                                }
                            }
                        }
                        for (int j = i; j < mstr[loginMasterIndex]->numCourses - 1; j++)
                        {
                            mstr[loginMasterIndex]->depID[j] = mstr[loginMasterIndex]->depID[j + 1];
                            strcpy(mstr[loginMasterIndex]->courseName[j], mstr[loginMasterIndex]->courseName[j + 1]);
                        }
                        mstr[loginMasterIndex]->numCourses--;
                        printf("Course deleted successfully!\n");
                    }
                }
            }
            else if (loginLevel == 3)
            {
                isInAnotherDep = 0;
                doesntExist = 1;
                for (int i = 0; i < depIndex; i++)
                {
                    for (int j = 0; j < dp[i]->numCourses; i++)
                    {
                        if ((strcmp(dp[i]->courseName[j], inputList[1]) == 0) && (strcmp(dp[i]->masterFirstName[j], inputList[2]) == 0) && (strcmp(dp[i]->masterLastName[j], inputList[3]) == 0))
                        {
                            if (i != loginDepIndex)
                            {
                                printf("You can't delete another department's course!\n");
                                isInAnotherDep = 1;
                                i = depIndex;
                                break;
                            }
                            for (int k = j; j < dp[i]->numCourses - 1; k++)
                            {
                                strcpy(dp[i]->courseName[k], dp[i]->courseName[k + 1]);
                                strcpy(dp[i]->coursePreend[k], dp[i]->coursePreend[k + 1]);
                                dp[i]->credit[k] = dp[i]->credit[k + 1];
                                dp[i]->capacity[k] = dp[i]->capacity[k + 1];
                                dp[i]->registered[k] = dp[i]->registered[k + 1];

                                strcpy(dp[i]->masterFirstName[k], dp[i]->masterFirstName[k + 1]);
                                strcpy(dp[i]->masterLastName[k], dp[i]->masterLastName[k + 1]);
                                dp[i]->masterID[k] = dp[i]->masterID[k + 1];
                            }
                            doesntExist = 0;
                            dp[i]->numCourses--;
                            i = depIndex;
                        }
                    }
                }
                if (isInAnotherDep == 0)
                {
                    for (int j = 0; j < stdIndex; j++)
                    {
                        for (int k = 0; k < std[j]->numCourses; k++)
                        {
                            if ((strcmp(std[j]->courseName[k], inputList[1]) == 0) && inputList[2] == std[j]->masterFirstName[k] && inputList[3] == std[j]->masterLastName[k])
                            {
                                doesntExist = 0;
                                std[j]->totalCredit -= std[j]->credit[k];
                                for (int l = k; l < std[j]->numCourses - 1; l++)
                                {
                                    strcpy(std[j]->courseName[l], std[j]->courseName[l + 1]);
                                    std[j]->credit[l] = std[j]->credit[l + 1];

                                    strcpy(std[j]->masterFirstName[l], std[j]->masterFirstName[l + 1]);
                                    strcpy(std[j]->masterLastName[l], std[j]->masterLastName[l + 1]);
                                    std[j]->masterID[l] = std[j]->masterID[l + 1];
                                }
                                std[j]->numCourses--;
                            }
                        }
                    }
                    for (int i = 0; i < mstrIndex; i++)
                    {
                        if (strcmp(mstr[i]->firstName, inputList[2]) == 0 && strcmp(mstr[i]->lastName, inputList[3]) == 0)
                        {
                            for (int j = 0; j < mstr[i]->numCourses; j++)
                            {
                                if (strcmp(mstr[i]->courseName[j], inputList[1]) == 0)
                                {
                                    for (int k = j; k < mstr[i]->numCourses - 1; k++)
                                    {
                                        mstr[i]->depID[k] = mstr[i]->depID[k + 1];
                                        strcpy(mstr[i]->courseName[k], mstr[i]->courseName[k + 1]);
                                    }
                                    mstr[i]->numCourses--;
                                    printf("Course deleted successfully!\n");
                                    break;
                                }
                            }
                            break;
                        }
                    }
                }
            }
            else if (doesntExist && isInAnotherDep == 0)
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

        // add course student
        else if (strncmp(inputCpy, "add-s", 5) == 0)
        {
            if (loginLevel != 1)
            {
                printf("You should login as a student to add course!\n");
            }
            else
            {
                if (index < 4)
                {
                    printf("Invalid inputs!\n");
                }
                else
                {
                    int doesntExist = 1;
                    for (int i = 0; i < depIndex; i++)
                    {
                        for (int j = 0; j < dp[i]->numCourses; j++)
                        {
                            // printf("j is %d\ninputList[1] is %s and dp[%d]->courseName[%d] is %s\n and strcmp is %d\n", j, inputList[1], i, j, dp[i]->courseName[j],strcmp(inputList[1],dp[i]->courseName[j]));
                            // printf("inputList[2] is %s and dp[%d]->masterFirstName[%d] is %s\n and strcmp is %d\n", inputList[2], i, j, dp[i]->masterFirstName[j],strcmp(inputList[2],dp[i]->masterFirstName[j]));
                            // printf("inputList[3] is %s and dp[%d]->masterLastName[%d] is %s\n and strcmp is %d\n", inputList[3], i, j, dp[i]->masterLastName[j],strcmp(inputList[3],dp[i]->masterLastName[j]));
                            if ((strcmp(inputList[1], dp[i]->courseName[j]) == 0) && (strcmp(inputList[2], dp[i]->masterFirstName[j]) == 0) && (strcmp(inputList[3], dp[i]->masterLastName[j]) == 0))
                            {
                                int haveThisCourse = 0;
                                doesntExist = 0;
                                for (int k = 0; k < std[loginStudentIndex]->numCourses; k++)
                                {
                                    if (strcmp(inputList[1], std[loginStudentIndex]->courseName[k]) == 0)
                                    {
                                        printf("You already have this course!\n");
                                        i = depIndex + 1;
                                        break;
                                    }
                                }
                                for (int k = 0; k < std[loginStudentIndex]->passNumCourses; k++)
                                {
                                    if (strcmp(inputList[1], std[loginStudentIndex]->passCourseName[k]) == 0)
                                    {
                                        printf("You already have this course!\n");
                                        i = depIndex + 1;
                                        break;
                                    }
                                }
                                if (i == depIndex + 1)
                                {
                                    break;
                                }
                                if (haveThisCourse)
                                {
                                    doesntExist = 0;
                                    break;
                                }

                                int preendPassed = 0;
                                for (int k = 0; k < std[loginStudentIndex]->passNumCourses; k++)
                                {
                                    if (strcmp(std[loginStudentIndex]->passCourseName[k], dp[i]->coursePreend[j]) == 0)
                                    {
                                        preendPassed = 1;
                                    }
                                }
                                if (preendPassed == 0)
                                {
                                    printf("You haven't passed preneeded courses yet!\n");
                                    i = depIndex;
                                    doesntExist = 0;
                                    break;
                                }

                                if (dp[i]->registered[j] >= dp[i]->capacity[j])
                                {
                                    printf("The capacity of course is full!\n");
                                }

                                else if (std[loginStudentIndex]->totalCredit + dp[i]->credit[j] > 24)
                                {
                                    printf("You've reached the limit of taking courses!\n");
                                }
                                else
                                {
                                    strcpy(std[loginStudentIndex]->courseName[j], inputList[1]);
                                    strcpy(std[loginStudentIndex]->masterFirstName[j], inputList[2]);
                                    strcpy(std[loginStudentIndex]->masterLastName[j], inputList[3]);
                                    std[loginStudentIndex]->totalCredit += dp[i]->credit[j];
                                    std[loginStudentIndex]->numCourses++;
                                    dp[i]->registered[j]++;
                                    printf("You're added to course successfully!\n");
                                }
                                i = depIndex;
                                break;
                            }
                        }
                    }
                    if (doesntExist)
                    {
                        printf("No course exists with given name and master!\n");
                    }
                }
            }
        }

        // remove-s
        else if (strncmp(inputCpy, "remove-s", 8) == 0)
        {
            if (loginLevel != 1)
            {
                printf("You should login as a student to remove course!\n");
            }
            else if (index < 2)
            {
                printf("Invalid inputs!\n");
            }
            else
            {
                int isPassed = 0;
                for (int i = 0; i < std[loginStudentIndex]->passNumCourses; i++)
                {
                    if (strcmp(std[loginStudentIndex]->passCourseName[i], inputList[1]) == 0)
                    {
                        isPassed = 1;
                        break;
                    }
                }
                int isPassing = 0;
                int courseIndex;
                for (int i = 0; i < std[loginStudentIndex]->numCourses; i++)
                {
                    // printf("std[%d] courseName[%d] is %s and inputList[1] is %s\n",loginStudentIndex,i,std[loginStudentIndex]->courseName[i],inputList[1]);
                    if (strcmp(std[loginStudentIndex]->courseName[i], inputList[1]) == 0)
                    {
                        isPassing = 1;
                        courseIndex = i;
                        break;
                    }
                }
                if (isPassed)
                {
                    printf("You have already had this course!\n");
                }
                else if (isPassing == 0)
                {
                    printf("You don't belong to the student list of given course!\n");
                }
                else
                {
                    for (int i = 0; i < depIndex; i++)
                    {
                        for (int j = 0; j < dp[i]->numCourses; j++)
                        {
                            if (strcmp(std[loginStudentIndex]->courseName[courseIndex], dp[i]->courseName[j]) == 0 && strcmp(std[loginStudentIndex]->masterFirstName[courseIndex], dp[i]->masterFirstName[j]) == 0 && strcmp(std[loginStudentIndex]->masterLastName[courseIndex], dp[i]->masterLastName[j]) == 0)
                            {
                                dp[i]->registered[j]--;
                                i = depIndex;
                                break;
                            }
                        }
                    }
                    std[loginStudentIndex]->totalCredit -= std[loginStudentIndex]->credit[courseIndex];
                    for (int i = courseIndex; i < std[loginStudentIndex]->numCourses - 1; i++)
                    {
                        strcpy(std[loginStudentIndex]->courseName[i], std[loginStudentIndex]->courseName[i + 1]);
                        strcpy(std[loginStudentIndex]->masterFirstName[i], std[loginStudentIndex]->masterFirstName[i + 1]);
                        strcpy(std[loginStudentIndex]->masterLastName[i], std[loginStudentIndex]->masterLastName[i + 1]);
                        std[loginStudentIndex]->masterID[i] = std[loginStudentIndex]->masterID[i + 1];
                        std[loginStudentIndex]->credit[i] = std[loginStudentIndex]->masterID[i + 1];
                    }
                    std[loginStudentIndex]->numCourses--;

                    printf("The course is removed from your chart successfully!\n");
                }
            }
        }

        else if (strncmp(inputCpy, "show-courses", 12) == 0)
        {
            if (index < 2)
            {
                printf("Invalid inputs!\n");
            }
            else
            {
                int foundDep = 0;
                int depShowCourseIndex;
                for (int i = 0; i < depIndex; i++)
                {
                    if (strtol(inputList[1], NULL, 10) == dp[i]->depID)
                    {
                        depShowCourseIndex = i;
                        foundDep = 1;
                        break;
                    }
                }
                if (foundDep == 0)
                {
                    printf("This department code is invalid!\n");
                }
                else
                {
                    for (int i = 0; i < dp[depShowCourseIndex]->numCourses; i++)
                    {
                        printf("%s %s %d\n", dp[depShowCourseIndex]->courseName[i], dp[depShowCourseIndex]->masterLastName[i], dp[depShowCourseIndex]->capacity[i] - dp[depShowCourseIndex]->registered[i]);
                    }
                }
            }
        }

        // show-d-courses
        else if (strncmp(inputCpy, "show-d-courses", 14) == 0)
        {
            if (loginLevel != 3)
            {
                printf("You should login as a departmnet to show depaertment courses!\n");
            }
            else
            {
                for (int i = 0; i < dp[loginDepIndex]->numCourses; i++)
                {
                    printf("%s %s %d\n", dp[loginDepIndex]->courseName[i], dp[loginDepIndex]->masterLastName[i], dp[loginDepIndex]->capacity[i] - dp[loginDepIndex]->registered[i]);
                }
            }
        }

        else if (strncmp(inputCpy, "give_course", 11) == 0)
        {
            if (loginLevel != 1)
            {
                printf("You should login as a student to give course to your friend!\n");
            }
            else
            {
                int giveCourseDepIndex = -1;
                int giveCourseCourseIndex = -1;
                int friendIndex = -1;
                for (int i = 0; i < depIndex; i++)
                {
                    for (int j = 0; j < dp[i]->numCourses; j++)
                    {
                        if (strcmp(dp[i]->courseName[j], inputList[1]) == 0)
                        {
                            giveCourseCourseIndex = j;
                            giveCourseDepIndex = i;
                        }
                    }
                }
                for (int i = 0; i < stdIndex; i++)
                {
                    if (strcmp(std[i]->firstName, inputList[2]) == 0 && strcmp(std[i]->lastName, inputList[3]) == 0)
                    {
                        friendIndex = i;
                        break;
                    }
                }
                if (giveCourseCourseIndex == -1)
                {
                    printf("This course doesn't exist!\n");
                }
                else if (giveCourseCourseIndex != -1 && friendIndex == -1)
                {
                    printf("This person doesn't exist!\n");
                }
                else if (giveCourseCourseIndex != -1 && friendIndex != -1)
                {
                    int giveStudentPassIndex = -1;
                    int giveStudentNowIndex = -1;
                    for (int i = 0; i < std[loginStudentIndex]->numCourses; i++)
                    {
                        if (strcmp(inputList[1], std[loginStudentIndex]->courseName[i]) == 0)
                        {
                            giveStudentNowIndex = i;
                            break;
                        }
                    }
                    for (int i = 0; i < std[loginStudentIndex]->passNumCourses; i++)
                    {
                        if (strcmp(inputList[1], std[loginStudentIndex]->passCourseName[i]) == 0)
                        {
                            giveStudentPassIndex = i;
                            break;
                        }
                    }
                    if (giveStudentNowIndex == -1 && giveStudentPassIndex == -1)
                    {
                        printf("You don't belong to the student list of given course!\n");
                    }
                    else if (giveStudentNowIndex != -1)
                    {
                        int alreadyPassed = 0;
                        for (int i = 0; i < std[friendIndex]->numCourses; i++)
                        {
                            if (strcmp(inputList[1], std[friendIndex]->courseName[i]) == 0)
                            {
                                alreadyPassed = 1;
                            }
                        }
                        for (int i = 0; i < std[friendIndex]->passNumCourses; i++)
                        {
                            if (strcmp(inputList[1], std[friendIndex]->passCourseName[i]) == 0)
                            {
                                alreadyPassed = 1;
                            }
                        }
                        if (alreadyPassed)
                        {
                            printf("This person has already have this course!\n");
                        }
                        else
                        {
                            int finalDepIndex = -1;
                            int finalDepCourseIndex = -1;
                            for (int i = 0; i < depIndex; i++)
                            {
                                for (int j = 0; j < dp[i]->numCourses; j++)
                                {
                                    if (strcmp(std[loginStudentIndex]->courseName[giveStudentNowIndex], dp[i]->courseName[j]) == 0 && strcmp(std[loginStudentIndex]->masterFirstName[giveStudentNowIndex], dp[i]->masterFirstName[j]) == 0 && strcmp(std[loginStudentIndex]->masterLastName[giveStudentNowIndex], dp[i]->masterLastName[j]) == 0)
                                    {
                                        for (int k = 0; k < std[friendIndex]->passNumCourses; k++)
                                        {
                                            if (strcmp(std[friendIndex]->passCourseName[k], dp[i]->coursePreend[j]) == 0)
                                            {
                                                finalDepIndex = i;
                                                finalDepCourseIndex = j;
                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                            if (finalDepCourseIndex == -1)
                            {
                                printf("Your friend hasn't pass preneeded courses yet!\n");
                            }
                            else
                            {
                                strcpy(std[friendIndex]->courseName[std[friendIndex]->numCourses], std[loginStudentIndex]->courseName[giveStudentNowIndex]);
                                strcpy(std[friendIndex]->masterFirstName[std[friendIndex]->numCourses], std[loginStudentIndex]->masterFirstName[giveStudentNowIndex]);
                                strcpy(std[friendIndex]->masterLastName[std[friendIndex]->numCourses], std[loginStudentIndex]->masterLastName[giveStudentNowIndex]);
                                std[friendIndex]->masterID[std[friendIndex]->numCourses] = std[loginStudentIndex]->masterID[giveStudentNowIndex];
                                std[friendIndex]->credit[std[friendIndex]->numCourses] = std[loginStudentIndex]->credit[giveStudentNowIndex];
                                std[friendIndex]->totalCredit += std[friendIndex]->credit[std[friendIndex]->numCourses];
                                std[friendIndex]->numCourses++;

                                std[loginStudentIndex]->totalCredit -= std[loginStudentIndex]->credit[giveStudentNowIndex];
                                for (int i = giveStudentNowIndex; i < std[loginStudentIndex]->numCourses - 1; i++)
                                {
                                    strcpy(std[loginStudentIndex]->courseName[i], std[loginStudentIndex]->courseName[i + 1]);
                                    strcpy(std[loginStudentIndex]->masterFirstName[i], std[loginStudentIndex]->masterFirstName[i + 1]);
                                    strcpy(std[loginStudentIndex]->masterLastName[i], std[loginStudentIndex]->masterLastName[i + 1]);
                                    std[loginStudentIndex]->masterID[i] = std[loginStudentIndex]->masterID[i + 1];
                                    std[loginStudentIndex]->credit[i] = std[loginStudentIndex]->credit[i + 1];
                                }
                                std[loginStudentIndex]->numCourses--;

                                printf("Course transferd to %s %s successfully!\n", std[friendIndex]->firstName, std[friendIndex]->lastName);
                            }
                        }
                    }
                    // else if(giveStudentPassIndex!=-1){

                    // }
                }
            }
        }

        else
            printf("Invalid command!\n");
        // printf("previous input was %s. waiting to new input\n", input);
        fgets(input, 1000, stdin);
        strcpy(inputCpy, input);
    }
}

// by arshia samiezad 402111497

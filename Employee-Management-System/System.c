#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "strTools.c"
#include "Date.c"
#include "Time.c"
#include "Employee.c"
#include "database.c"
#include "dataIO.c"

#define EXIT 2
#define ERROR 1
#define SUCCESS 0

Time startWorking={0,0,0};
Time endWorking={0,0,0};
String password=NULL;
Date today={0,0,0}; 
DailyRecord recordToday={{0,0,0}, 0, NULL};

void printFunctions(){
    printf("\nType '1' to start clock-in\n");
    printf("Type '2' to change password\n");
    printf("Type '3' to set the working time\n");
    printf("Type '4' to query the detail of an employee\n");
    printf("Type '5' to add an employee;\n");
    printf("Type '6' to remove an employee;\n");
    printf("Type '7' to edit an employee;\n");
    printf("Type '8' to save data;\n");
    printf("Type '9' to set date;\n");
}

void setPassword(){
    password=(String)malloc(sizeof(String)*30);
    printf("Please set your password(Within 30 words): ");
    password=scanfModified();
    printf("\nYou are all set! Wellcome!\n\n");
}

char checkPassword(){
    String pw=(String)malloc(sizeof(String)*30);
    while (1)
    {
        printf("Password(Within 30 words): ");
        pw=scanfModified();
        if (stringCompare(pw, password)){
            return SUCCESS;
        }
        else if(stringCompare(strLower(pw), "e")){
            return EXIT;
        }
        else{
            printf("Incorrect password, try again->\n");
            continue;
        }
    }
    return ERROR;
}

String getFolderPath(String str){
    int exception=0;
    size_t end=indexOf(str, "System", 0, &exception);
    return strSlide(str, 0, end);
}

size_t getNum_s(String str, int* exit){
    size_t num=0;
    String temp=(String)malloc(sizeof(char)*__INT32_MAX__);
    while (1){
        printf("%s", str);
        temp=scanfModified();
        if (stringCompare(temp, "e")){
            *exit=EXIT;
            return EXIT;
        }
        if (!haveChar(temp)){
            num=strToInt(temp);
            free(temp);
            return num;
        }
        else{
            printf("Incorre input try again->\n");
        }
    }

    return ERROR;
}

String getStr_s(String str, int* exit){
    String re=NULL;
    String temp=(String)malloc(sizeof(char)*__INT32_MAX__);
    printf(str);
    temp=scanfModified();
    if (stringCompare(temp, "e")){
        *exit=EXIT;
        return "";
    }
    size_t end=strLen(temp);
    re=strSlide(temp, 0, end);
    free(temp);
    return re;
}

Time getTime_s(String str, int* exit){
    printf("\n%s\n", str);
    int tempExit=0;
    unsigned char hour=getNum_s("hour(Integer): ", &tempExit);
    if (tempExit==EXIT){
        *exit=EXIT;
        return (Time){0,0,0};
    }

    unsigned char minute=getNum_s("minute(Integer): ", &tempExit);
    if (tempExit==EXIT){
        *exit=EXIT;
        return (Time){0,0,0};
    }

    unsigned char second=getNum_s("second(Integer): ", &tempExit);
    if (tempExit==EXIT){
        *exit=EXIT;
        return (Time){0,0,0};
    }

    return (Time){hour, minute, second};
}

Employee* getEmployee_s(){
    int exit=0;
    ID id=getNum_s("ID(Integer): ", &exit);
    if (exit==EXIT){
        return NULL;
    }

    Frequency businessTrip=getNum_s("Business trip(Integer): ", &exit);
    if (exit==EXIT){
        return NULL;
    }

    Frequency absenceTimes=getNum_s("Number of absences(Integer): ", &exit);
    if (exit==EXIT){
        return NULL;
    }

    Frequency lateTimes=getNum_s("Number of lateness(Integer): ", &exit);
    if (exit==EXIT){
        return NULL;
    }

    String name=getStr_s("Employee name: ", &exit);
    if (exit==EXIT){
        return NULL;
    }

    String absenceReason=getStr_s("Absence reason: ", &exit);
    if (exit==EXIT){
        return NULL;
    }

    Time onDuty=getTime_s("On duty->", &exit);
    if (exit==EXIT){
        return NULL;
    }

    Time offDuty=getTime_s("Off duty->", &exit);
    if (exit==EXIT){
        return NULL;
    }

    return &(Employee){id, businessTrip, absenceTimes, lateTimes, name, absenceReason, onDuty, offDuty};
}

DailyRecord* getTodayRecord(){
    return getRecord(today);
}

char addStaff_s(){
    printf("\nPlease follow the instruction->\n");

    Employee* temp=getEmployee_s();
    if (temp==NULL){
        return EXIT;
    }
    
    addStaff(*temp);
    return SUCCESS;
}

char removeStaff_s(){
    printf("\nPlease follow the instruction->\n");

    int exit=0;
    ID id=getNum_s("ID(Integer): ", &exit);
    if (exit){
        return EXIT;
    }

    int exception=0;
    removeStaff(id, &exception);
    if (exception){
        return ERROR;
    }

    return SUCCESS;
}

char loadData(String path){
    String str=dataRead(path);
    password=getPassword(str);
    return getRList_f(str) && getStaff_f(str) && password!=NULL;
}

void writeData(String path){
    dataWrite(path, password);
}

char setWorkingTime(){
    int exit=0;
    String onDuty=getStr_s("Time for clock-in: ", &exit);
    if (exit==EXIT){
        return EXIT;
    }

    String offDuty=getStr_s("Closing time: ", &exit);
    if (exit==EXIT){
        return EXIT;
    }

    startWorking=getTime_f(onDuty);
    endWorking=getTime_f(offDuty);
    return SUCCESS;
}

Employee* getEmployeeFromStaff(){
    int exit=0;
    while (1)
    {
        ID id=getNum_s("ID: ", &exit);
        int exception=0;
        if (exit==EXIT){
            return getStaff(0, &exception);
        }

        Employee* e=getStaff(id, &exception);
        if (exception==ERROR){
            printf("Connot find this employee, try again->\n");
            continue;
        }

        return e;
    }
}

char checkDetail(){
    int exit=0;
    while (1)
    {
        Employee* temp=getEmployeeFromStaff();
        if (temp==NULL){
            return EXIT;
        }
        Employee e=*temp;
        printf("\nDetail of employee->\nID: %d->\nEmployee: %s\n\n", e.id, strEmployee(e));
    }
}

char editEmployee(){
    Employee* temp=getEmployeeFromStaff();
    if (temp==NULL){
        return EXIT;
    }

    Employee e=*temp;
    Employee copy={e.id, e.businessTrip, e.absenceTimes, e.lateTimes, e.name, e.absenceReason, e.onDuty, e.offDuty};
    String str=NULL;
    while (1){
        if (str!=NULL){
            free(str);
        }

        int exit=0;
        str=strLower(getStr_s("Option: ", &exit));
        if (exit==EXIT){
            return EXIT;
        }

        if (stringCompare(str, "save")){
            *temp=copy;
            free(str);
            return SUCCESS;
        }

        if (stringCompare(str, "business trip")){
            Frequency businessTrip=getNum_s("New number: ", &exit);
            if (exit==EXIT){
                return EXIT;
            }

            copy.businessTrip=businessTrip;
        }
        else if (stringCompare(str, "name")){
            String name=getStr_s("New name: ", &exit);
            if (exit==EXIT){
                return EXIT;
            }

            copy.name=name;
        }
        else if (stringCompare(str, "absence reason")){
            String absenceReason=getStr_s("Absence reason: ", &exit);
            if (exit==EXIT){
                return EXIT;
            }

            copy.absenceReason=absenceReason;
        }
        else if (stringCompare(str, "on")){
            Time onDuty=getTime_s("On duty: ", &exit);
            if (exit==EXIT){
                return EXIT;
            }

            copy.onDuty=onDuty;
        }
        else if (stringCompare(str, "off")){
            Time offDuty=getTime_s("Off duty: ", &exit);
            if (exit==EXIT){
                return EXIT;
            }

            copy.offDuty=offDuty;
        }
        else {
            printf("Illegal option, try again->\n");
        }
    }
}

char checkLate(Employee* e, Time time){
    e->onDuty=time;
    if (timeCompare(time, startWorking)==1){
        return 1;
    }
    return 0;
}

Employee* clockIn(){
    Employee* e=getEmployeeFromStaff();
    if (e->id==0){
        return e;
    }

    e->absenceTimes--;
    int exit=0;
    Time time=getTime_s("Test Time: ", &exit);
    if (checkLate(e, time)==1){
        e->lateTimes++;
    }
    addEmployee(*e, &recordToday.recordList, &recordToday.listSize);
    return e;
}

void startListen(){
    for (size_t i=1; i<staff.listSize; i++){
        staff.recordList[i].absenceTimes++;
    }
    
    while (1){
        Employee* e=clockIn();
        if (e->id==0){
            return;
        }
    }
}

void setDate(){
    int exit=0;
    String date=getStr_s("Date: ", &exit);
    if (exit==EXIT){
        return;
    }

    today=getDate_f(date);
}

void main(int argc, char const* argv[]){
    String path=getFolderPath(argv[0]);
    path=strAdd(path, "table.txt");

    if (!loadData(path)){
        writeData(path);
    }
    while (1){
        admin:
        if (password==NULL){
            printf("Wellcome to this system!\n");
            addStaff((Employee){0, 0, 0, 0, "admin", "", {0,0,0}, {0,0,0}});
            setPassword();
            writeData(path);
        }
        else{
            if (checkPassword()==EXIT){
                printf("\nExit...\n");
                exit(EXIT);
            }
        }
        printf("\nWellcome!\n");
        
        start:
        printFunctions();
        printf("\nInput: ");
        String commandStr=scanfModified();
        if(haveChar(commandStr)){
            printf("Error command, try again->\n");
            goto start;
        }

        int command=strToInt(commandStr);
        switch (command){

            case 1:
                startListen();
                goto admin;

            case 2:
                setPassword();
                goto start;
            
            case 3:
                setWorkingTime();
                goto start;

            case 4:
                checkDetail();
                goto start;

            case 5:
                addStaff_s();
                goto start;

            case 6:
                if (removeStaff_s()==ERROR){
                    printf("Cannot find the employee\n\n");
                }
                goto start;

            case 7:
                editEmployee();
                goto start;

            case 8:
                recordToday.date=today;
                addRecord(recordToday);
                writeData(path);
                exit(EXIT);

            case 9:
                setDate();
                goto start;

            case 10:
                printf("\n\n");
                printf("Staff: \n%s\n\n", staffToStr());
                goto start;

            default:
                printf("Incorrect command, try again->\n");
                goto start;
        }
    }
}
char dataWrite(String path, String password){
    FILE* f=fopen64(path, "w+");
    if (f==NULL){
        return 0;
    }

    String staffStr=staffToStr();
    staffStr=strAdd("\n&\n", staffStr);

    String str=RListToStr();
    str=strAdd("&\n", str);
    str=strAdd(staffStr, str);

    password=strAdd("\n^\n", password);

    str=strAdd(password, str);
    String size=intToStr(strLen(str));
    str=strAdd(size, str);

    fprintf(f, "%s", str);
    fclose(f);
    return 1;
}

size_t getTableSize(String path){
    FILE* f=fopen64(path, "r");
    if (f==NULL){
        return -1;
    }

    size_t size=0;
    fscanf(f, "%d", &size);
    fclose(f);
    return size;
}

String dataRead(String path){
    FILE* f=fopen64(path, "r");
    size_t size=getTableSize(path)+2;
    if (f==NULL || size==-1){
        return "";
    }

    String str=(String)malloc(size);
    size_t index=0;
    char determinant=0;
    do
    {
        char c=fgetc(f);
        if (feof(f)){
            break;
        }

        if (c=='^'){
            determinant=1;
        }
        if (determinant){
            str[index]=c;
            index++;
        }
    } while (1);

    str[index]='\0';
    fclose(f);
    return str;
}

String getPassword(String str){
    int exception=0;
    if (stringCompare(str, "")){
        return NULL;
    }
    size_t start=indexOf(str, "\n^", 0, &exception)+2;
    size_t end=indexOf(str, "\n", start, &exception);
    return strSlide(str, start, end);
}

String getRecordStr(String str, size_t index){
    int exception=0;
    size_t size=strLen(str);
    size_t start=indexOf(str, "&", 0, &exception);
    for (size_t i=0; i<size && i<index; i++){
        start=indexOf(str, "&", start+1, &exception);
    }
    size_t end=indexOf(str, "&", start+1, &exception);
    return strSlide(str, start+2, end+1);
}

String getDateStr(String record){
    int exception=0;
    size_t start=0;
    size_t end=indexOf(record, "\n", start, &exception);
    return strSlide(record, start, end);
}

Date getDate_f(String date){

    int exception=0;
    size_t yearEnd=indexOf(date, "/", 0, &exception);
    size_t monthEnd=indexOf(date, "/", yearEnd+1, &exception);

    String yearStr=strSlide(date, 0, yearEnd);
    String monthStr=strSlide(date, yearEnd+1, monthEnd);
    String dayStr=strSlide(date, monthEnd+1, strLen(date));

    unsigned int year=strToInt(yearStr);
    unsigned int month=strToInt(monthStr);
    unsigned int day=strToInt(dayStr);

    Date d={year, month, day};
    return d;
}

String getEmployeeStr(String record, size_t index){
    int exception=0;
    size_t start=indexOf(strLower(record), "id: ", 0, &exception);
    for (size_t i=0; i<index; i++){
        start=indexOf(record, "\n", start, &exception)+1;
    }
    size_t end=indexOf(record, "\n", start, &exception)+1;
    return strSlide(record, start, end);
}

String getIDStr(String EStr){
    int exception=0;
    size_t start=indexOf(EStr, " ", 0, &exception)+1;
    size_t end=indexOf(EStr, "|", start, &exception);
    return strSlide(EStr, start, end);
}

ID getID_f(String id){
    return strToInt(id);
}

String getENameStr(String EStr){
    int exception=0;
    size_t start=indexOf(EStr, "|", 0, &exception);
    start=indexOf(EStr, ": ", start, &exception)+2;

    size_t end=indexOf(EStr, "|", start, &exception);
    return strSlide(EStr, start, end);
}

String getReasonStr(String EStr){
    int exception=0;
    String temp=strLower(EStr);
    size_t start=indexOf(temp, "absence reason: ", 0, &exception);
    start=indexOf(temp, ": ", start, &exception)+2;

    size_t end=indexOf(temp, "|", start, &exception);
    return strSlide(EStr, start, end);
}

String getAbsenceTimesStr(String EStr){
    int exception=0;
    EStr=strLower(EStr);
    size_t start=indexOf(EStr, "number of absences: ", 0, &exception);
    start=indexOf(EStr, ": ", start, &exception)+2;

    size_t end=indexOf(EStr, "|", start, &exception);
    return strSlide(EStr, start, end);
}

Frequency getAbsenceTimes_f(String AbsenceTimesStr){
    return strToInt(AbsenceTimesStr);
}

String getBusinessTripStr(String EStr){
    int exception=0;
    EStr=strLower(EStr);
    size_t start=indexOf(EStr, "business trip:", 0, &exception);
    start=indexOf(EStr, ": ", start, &exception)+2;

    size_t end=indexOf(EStr, "|", start, &exception);
    return strSlide(EStr, start, end);
}

Frequency getBusinessTrip_f(String businessTripStr){
    return strToInt(businessTripStr);
}

String getTimeStr(String EStr, String onOffDuty){
    int exception=-1;
    size_t start=0;

    if (stringCompare(strLower(onOffDuty), "on")){
        start=indexOf(strLower(EStr), "on duty: ", 0, &exception);
    }
    else if (stringCompare(strLower(onOffDuty), "off")){
        start=indexOf(strLower(EStr), "off duty: ", 0, &exception);
    }

    start=indexOf(EStr, ": ", start, &exception)+2;
    size_t end=indexOf(EStr, "|", start, &exception);
    return strSlide(EStr, start, end);
}

Time getTime_f(String time){
    int exception=0;
    size_t hourEnd=indexOf(time, ":", 0, &exception);
    size_t minuteEnd=indexOf(time, ":", hourEnd+1, &exception);

    String hourStr=strSlide(time, 0, hourEnd);
    String minuteStr=strSlide(time, hourEnd+1, minuteEnd);
    String secondStr=strSlide(time, minuteEnd+1, strLen(time));

    unsigned char hour=strToInt(hourStr);
    unsigned char minute=strToInt(minuteStr);
    unsigned char second=strToInt(secondStr);

    Time t={hour, minute, second};
    return t;
}

String getLateTimesStr(String EStr){
    int exception=0;
    EStr=strLower(EStr);
    size_t start=indexOf(EStr, "number of lateness: ", 0, &exception);
    start=indexOf(EStr, ": ", start, &exception)+2;

    size_t end=indexOf(EStr, "\n", start, &exception);
    return strSlide(EStr, start, end);
}

Frequency getLateTimes_f(String lateTimesStr){
    return strToInt(lateTimesStr);
}

Employee getEmployee_f(String EStr){
    ID id=getID_f(getIDStr(EStr));
    Frequency businessTrip=getBusinessTrip_f(getBusinessTripStr(EStr));
    Frequency absenceTimes=getAbsenceTimes_f(getAbsenceTimesStr(EStr));
    Frequency lateTimes=getLateTimes_f(getLateTimesStr(EStr));
    String name=getENameStr(EStr);
    String absenceReason=getReasonStr(EStr);
    Time onDuty=getTime_f(getTimeStr(EStr, "on"));
    Time offDuty=getTime_f(getTimeStr(EStr, "off"));

    Employee e={id, businessTrip, absenceTimes, lateTimes, name, absenceReason, onDuty, offDuty};
    return e;
}

Employee* getEList_f(String record, size_t* listSize){
    *listSize=getStrLines(record, "\n")-1;
    Employee* recordList=createEList(*listSize);

    for (size_t i=0; i<*listSize; i++){
        recordList[i]=getEmployee_f(getEmployeeStr(record, i));
    }

    return recordList;
}

DailyRecord getRecord_f(String record){
    Date date=getDate_f(getDateStr(record));
    size_t listSize=0;
    Employee* recordList=getEList_f(record, &listSize);

    DailyRecord r={date, listSize, recordList};
    return r;
}

char getRList_f(String str){
    if (stringCompare(str, "")){
        return 0;
    }
    RListSize=getStrLines(str, "&")-2;
    RList=createRList(RListSize);
    for (size_t i=0; i<RListSize; i++){
        RList[i]=getRecord_f(getRecordStr(str, i+1));
    }
    return 1;
}

char getStaff_f(String str){
    if (stringCompare(str, "")){
        return 0;
    }
    staff.listSize=1;
    staff.recordList=createEList(1);
    staff=getRecord_f(getRecordStr(str, 0));

    return 1;
}
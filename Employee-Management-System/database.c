typedef struct record{
    Date date;
    size_t listSize;
    Employee* recordList;
} DailyRecord;

DailyRecord* RList=NULL;
size_t RListSize=0;

DailyRecord staff={{0,0,0}, 0, NULL};

DailyRecord* createRList(size_t length){
    return (DailyRecord*)malloc(sizeof(DailyRecord)*length);
}

String recordToStr(DailyRecord dr){
    String date=DateToStr(dr.date);
    String recordStr=EListToStr(dr.recordList, dr.listSize);
    String str=strAdd(date, "\n");
    String ret=strAdd(str, recordStr);
    return ret;
}

String RListToStr(){
    String str="";
    if (RListSize==0){
        return str;
    }

    for (size_t i=0; i<RListSize; i++){
        String rStr=recordToStr(RList[i]);
        str=strAdd(str, rStr);
        str=strAdd(str, "&\n");
    }

    return str;
}

void copyRList(DailyRecord* Dest, size_t start, size_t end){
    for (; start<end; start++){
        Dest[start]=RList[start];
    }
}

DailyRecord* concatRList(DailyRecord* left, DailyRecord* right, size_t sizeL, size_t sizeR){
    DailyRecord* list=createRList(sizeL+sizeR);
    for (size_t i=0; i<sizeL; i++){
        list[i]=left[i];
    }
    for (size_t i=0; i<sizeR; i++){
        list[i+sizeL]=right[i];
    }

    return list;
}

DailyRecord addRecord(DailyRecord d){
    RListSize++;
    DailyRecord* temp=createRList(RListSize);
    copyRList(temp, 0, RListSize-1);
    temp[RListSize-1]=d;
    RList=temp;
    return d;
}

DailyRecord* removeRecord(Date date){
    size_t end;
    int notFound=1;
    for (end=0; end<RListSize; end++){
        if (dateEqual(RList[end].date, date)){
            notFound=0;
            break;
        }
    }

    if (notFound){
        return NULL;
    }

    size_t sizeL=end;
    size_t sizeR=RListSize-end-1;
    DailyRecord* left=createRList(sizeL);
    DailyRecord* right=createRList(sizeR);
    for (size_t i=0; i<end; i++){
        left[i]=RList[i];
    }
    for (size_t i=0; i<RListSize-1; i++){
        right[i]=RList[i+end+1];
    }

    DailyRecord* pop=&RList[end];
    RList=concatRList(left, right, sizeL, sizeR);

    if (left!=NULL)
        free(left);
    if (right!=NULL)
        free(right);
    
    RListSize--;
    return pop;
}

DailyRecord* getRecord(Date date){
    for (size_t i=0; i<RListSize; i++){
        if (dateEqual(RList[i].date, date)){
            return &RList[i];
        }
    }
    return NULL;
}

Employee addStaff(Employee e){
    return addEmployee(e, &(staff.recordList), &(staff.listSize));
}

Employee* removeStaff(ID id, int* exception){
    return removeEmployee(id, &(staff.recordList), &(staff.listSize), exception);
}

String staffToStr(){
    return recordToStr(staff);
}

DailyRecord addStaffToRecord(Date date){
    return addRecord((DailyRecord){date, staff.listSize, staff.recordList});
}

Employee* getStaff(ID id, int* exception){
    int notFound=1;
    for (size_t i=0; i<staff.listSize; i++){
        if (staff.recordList[i].id==id){
            return &(staff.recordList[i]);
        }
    }
    *exception=notFound;
    return &(Employee){0, 0, 0, 0, "", "", {0,0,0}, {0,0,0}};
}
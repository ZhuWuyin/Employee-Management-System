#define ID size_t   // An alternate name of size_t
#define Frequency size_t    // An alternate name of size_t
typedef char* String;   // The alternate name of char*

// Create a type which is called Employee
typedef struct employee {
    ID id;
    Frequency businessTrip;
    Frequency absenceTimes;
    Frequency lateTimes;
    String name;
    String absenceReason;
    Time onDuty;
    Time offDuty;
} Employee;

Employee* createEList(size_t length){
    return (Employee*)malloc(sizeof(Employee)*length);
}

String strEmployee(Employee e){
    String id=intToStr(e.id);
    String name=e.name;
    String absenceReason=e.absenceReason;
    String absenceTimes=intToStr(e.absenceTimes);
    String businessTrip=intToStr(e.businessTrip);
    String onDuty=timeToStr(e.onDuty);
    String offDuty=timeToStr(e.offDuty);
    String lateTimes=intToStr(e.lateTimes);

    id=strAdd("id: ", id); id=strAdd(id, "|");
    name=strAdd("Employee name: ", name); name=strAdd(name, "|");
    absenceReason=strAdd("Absence reason: ", absenceReason); absenceReason=strAdd(absenceReason, "|");
    absenceTimes=strAdd("Number of absences: ", absenceTimes); absenceTimes=strAdd(absenceTimes, "|");
    businessTrip=strAdd("Business trip: ", businessTrip); businessTrip=strAdd(businessTrip, "|");
    onDuty=strAdd("On duty: ", onDuty); onDuty=strAdd(onDuty, "|");
    offDuty=strAdd("Off duty: ", offDuty); offDuty=strAdd(offDuty, "|");
    lateTimes=strAdd("Number of lateness: ", lateTimes);

    String str=strAdd(id, name);
    str=strAdd(str, absenceReason);
    str=strAdd(str,absenceTimes);
    str=strAdd(str, businessTrip);
    str=strAdd(str, onDuty);
    str=strAdd(str, offDuty);
    str=strAdd(str, lateTimes);

    return str;
}

String EListToStr(Employee* EList, size_t listSize){
    String str="";

    for (size_t i=0; i<listSize; i++){
        String eStr=strEmployee(EList[i]);
        str=strAdd(str, eStr);
        str=strAdd(str, "\n");
    }

    return str;
}

void copyEList(Employee* Dest, size_t start, size_t end, Employee* EList){
    for (; start<end; start++){
        Dest[start]=EList[start];
    }
}


Employee* concatEList(Employee* left, Employee* right, size_t sizeL, size_t sizeR){
    Employee* list=createEList(sizeL+sizeR);
    for (size_t i=0; i<sizeL; i++){
        list[i]=left[i];
    }
    for (size_t i=0; i<sizeR; i++){
        list[i+sizeL]=right[i];
    }

    return list;
}

Employee addEmployee(Employee e, Employee** EList, size_t* listSize){
    (*listSize)++;
    Employee* temp=createEList(*listSize);
    copyEList(temp, 0, (*listSize)-1, *EList);
    temp[*listSize-1]=e;
    *EList=temp;
    return e;
}

Employee* removeEmployee(ID id, Employee** EList, size_t* listSize, int* exception){
    size_t end;
    int notFound=1;
    for (end=0; end<*listSize; end++){
        if ((*EList)[end].id==id){
            notFound=0;
            break;
        }
    }

    if (notFound){
        *exception=notFound;
        return NULL;
    }

    size_t sizeL=end;
    size_t sizeR=*listSize-end-1;
    Employee* left=createEList(sizeL);
    Employee* right=createEList(sizeR);
    for (size_t i=0; i<end; i++){
        left[i]=(*EList)[i];
    }
    for (size_t i=0; i<*listSize-1; i++){
        right[i]=(*EList)[i+end+1];
    }

    Employee* pop=&(*EList)[end];
    *EList=concatEList(left, right, sizeL, sizeR);

    if (left!=NULL)
        free(left);
    if (right!=NULL)
        free(right);

    (*listSize)--;
    return pop;
}
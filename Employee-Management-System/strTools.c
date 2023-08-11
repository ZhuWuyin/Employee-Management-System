char* strSlide(char* str, size_t start, size_t end){
    if (start>=end){
        return "";
    }
    size_t size=end-start;
    char* result=(char*)malloc(sizeof(char)*size+1);
    for (size_t i=0; i<size; i++){
        result[i]=str[start+i];
    }
    result[size]='\0';
    return result;
}

void reverseStr(char* str, size_t size){
    size_t left=0;
    size_t right=size-1;
    while (left<right){
        register char temp=str[left];
        str[left]=str[right];
        str[right]=temp;
        left++; right--;
    }
}

int intLength(size_t num){
    int len=(num==0) ? 1:0;
    for (; num!=0; num/=10)
        len++;
    return len;
}

char* intToStr(size_t num){
    int size=intLength(num);
    char* str=(char*)malloc(sizeof(char)*(size+1));
    for (int i=0; i<size; i++){
        str[i]=0x30+num%10;
        num/=10;
    }
    reverseStr(str, size);
    str[size]='\0';
    return str;
}

size_t strLen(char* str){
    size_t len=0;
    for (; str!=NULL && str[len]!='\0'; len++);
    return len;
}

char* strAdd(char* left, char* right){
    size_t leftLen=strLen(left);
    size_t rightLen=strLen(right);
    size_t newSize=leftLen+rightLen;
    char* newStr=(char*)malloc(sizeof(char)*(newSize+1));

    for (size_t i=0; i<leftLen; i++){
        newStr[i]=left[i];
    }
    for (size_t i=0; i<rightLen; i++){
        newStr[i+leftLen]=right[i];
    }

    newStr[newSize]='\0';
    return newStr;
}

char stringCompare(char *str1, char *str2){
    for (int i=0;; i++){
        if (*str1!=*str2){
            return 0;
        }
        if (*str1=='\0' && *str2=='\0'){
            return 1;
        }
        str1+=1;
        str2+=1;
    }
    return 0;
}

size_t powerHelper(size_t num, size_t e){
    if (!e){
        return 1;
    }

    e--;
    size_t result=num;
    for (; e>0; e--){
        result*=num;
    }

    return result;
}

size_t strToInt(char* str){
    size_t num=0;
    size_t base=powerHelper(10, strLen(str)-1);
    for (size_t i=0; str[i]!='\0'; i++){
        num+=(str[i]-0x30)*base;
        base/=10;
    }

    return num;
}

void indexOfException(int* exception){
    *exception=1;
}

size_t indexOf(char* str1, char* str2, size_t start, int* exception){
    size_t size1=strLen(str1);
    size_t size2=strLen(str2);

    for (; start+size2<=size1; start++){
        if (str1[start]==str2[0]){
            char* temp=strSlide(str1, start, start+size2);
            if (stringCompare(temp, str2)){
                return start;
            }
            else {
                continue;
            }
        }
    }

    indexOfException(exception);
    return 0;
}

char* strLower(char* str){
    size_t size=strLen(str);
    char* lower=(char*)malloc(sizeof(char)*size);
    for (size_t i=0; i<size; i++){
        lower[i]=tolower(str[i]);
    }
    lower[size]='\0';
    return lower;
}

size_t getStrLines(char* str, char* split){
    size_t size=strLen(str);
    size_t counter=0;
    size_t index=0;
    do
    {
        int e=0;
        index=indexOf(str, split, index, &e)+1;
        if (e==1){
            return counter;
        }
        counter++;
    } while (1);
}

char haveChar(char* str){
    for (size_t i=0; str[i]!='\0'; i++){
        char temp=str[i];
        if ((temp>57 || temp<48) && temp!='\0'){
            return 1;
        }
    }
    return str[0]=='\0' ? 1:0;
}

char* scanfModified(){
    char* str="";
    
    while (1)
    {
        char* temp=(char*)malloc(sizeof(char)*2);
        char c=getchar();
        if (c=='\n'){
            return str;
        }
        temp[0]=c;
        temp[1]='\0';
        char* trash=str;
        str=strAdd(str, temp);
        if (!stringCompare(trash, "")){
            free(trash);
        }
    }
}
// A type of time
typedef struct time {
    unsigned char hour;
    unsigned char minute;
    unsigned char second;
} Time;

/**
 * @brief Convert a Time type to a formatted string
 * 
 * @param t A data of Time type
 * @return char* -> The formatted string
 */
char* timeToStr(Time t){
    char* hour=intToStr((size_t)t.hour);
    char* minute=intToStr((size_t)t.minute);
    char* second=intToStr((size_t)t.second);

    hour=strAdd(hour, ":");
    minute=strAdd(minute, ":");

    char* result=strAdd(hour, minute);
    result=strAdd(result, second);

    return result;
}

char timeCompare(Time t1, Time t2){
    if (t1.hour==t2.hour && t1.minute==t2.minute && t1.second==t2.second){
        return 0;
    }
    else if (t1.hour==t2.hour && t1.minute==t2.minute){
        if (t1.second>t2.second){
            return 1;
        }
        else {
            return 2;
        }
    }
    else if (t1.hour==t2.hour){
        if (t1.minute>t2.minute){
            return 1;
        }
        else {
            return 2;
        }
    }
    else if (t1.hour>t2.hour){
        return 1;
    }
    else {
        return 2;
    }
}
// A type of time
typedef struct date {
    unsigned int year;
    unsigned int month;
    unsigned int day;
} Date;

/**
 * @brief Convert a Date type to a formatted string
 * 
 * @param t A data of Date type
 * @return char* -> The formatted string
 */
char* DateToStr(Date d){
    char* year=intToStr((size_t)d.year);
    char* month=intToStr((size_t)d.month);
    char* day=intToStr((size_t)d.day);

    year=strAdd(year, "/");
    month=strAdd(month, "/");

    char* result=strAdd(year, month);
    result=strAdd(result, day);

    return result;
}

char dateEqual(Date a, Date b){
    return a.year==b.year && a.month==b.month && a.day==b.day;
}
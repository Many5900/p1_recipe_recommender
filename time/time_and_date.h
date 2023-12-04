//
// Created by Marc Nygaard on 04/12/2023.
//

#ifndef P1_RECIPE_RECOMMENDER_TIME_AND_DATE_H
#define P1_RECIPE_RECOMMENDER_TIME_AND_DATE_H

/***********************************
***** GET CURRENT month & year *****
***********************************/

int getCurrentMonth();
int getCurrentYear();

/*******************************
***** EXTRACT month & year *****
*******************************/

char* extractMonth(const char *date);
char* extractYear(const char *date);




struct Date convertToDate(const char *dateStr);
int calculateDaysDifference(struct Date expirationDate);
const char* getMonthString(int month);






struct Date {
    int day;
    int month;
    int year;
};

#endif //P1_RECIPE_RECOMMENDER_TIME_AND_DATE_H

//
// Created by Marc Nygaard on 04/12/2023.
//

#ifndef P1_RECIPE_RECOMMENDER_TIME_AND_DATE_H
#define P1_RECIPE_RECOMMENDER_TIME_AND_DATE_H

/***********************************
***** GET CURRENT month & year *****
***********************************/

int get_current_month();
int get_current_year();

/*******************************
***** EXTRACT month & year *****
*******************************/

char* extract_month(const char *date);
char* extract_year(const char *date);




struct Date_t convert_to_date(const char *dateStr);


const char* get_numeric_month_as_string(int month_numeric);



struct Date_t {
    int day;
    int month;
    int year;
};

#endif //P1_RECIPE_RECOMMENDER_TIME_AND_DATE_H

//
// Created by Marc Nygaard on 04/12/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#include "time_and_date.h"



/***********************************
***** GET CURRENT month & year *****
***********************************/

int get_current_month() {
    // Get the current time
    time_t t = time(NULL);
    struct tm tm_info = *localtime(&t);

    // Extract the current month
    int current_month = tm_info.tm_mon + 1;  // Months are zero-based

    return current_month;
}

int get_current_year() {
    // Get the current time
    time_t t = time(NULL);
    struct tm tm_info = *localtime(&t);

    // Extract the current year
    int current_year = tm_info.tm_year + 1900;

    return current_year;
}





/*******************************
***** EXTRACT month & year *****
*******************************/

char* extract_month(const char *date) {
    char *month = NULL;

    month = (char* )malloc(3 * sizeof(char));  // Allocate memory for the month string
    if (month != NULL) {
        strncpy(month, date + 3, 2);  // Copy the month substring
        month[2] = '\0';  // Null terminate the string
    }

    return month;  // Return the dynamically allocated month or NULL
}



char* extract_year(const char *date) {
    char *year = NULL;

    if (strlen(date) >= 10) {
        year = (char *)malloc(5 * sizeof(char));  // Allocate memory for the year string
        if (year != NULL) {
            strncpy(year, date + 6, 4);  // Copy the year substring
            year[4] = '\0';  // Null terminate the string
        }
    }

    return year;  // Return the dynamically allocated year or NULL
}





/**************************************
***** get_numeric_month_as_string *****
**************************************/

const char* get_numeric_month_as_string(int month_numeric) {
    switch (month_numeric) {
        case 1: return "January";
        case 2: return "February";
        case 3: return "March";
        case 4: return "April";
        case 5: return "May";
        case 6: return "June";
        case 7: return "July";
        case 8: return "August";
        case 9: return "September";
        case 10: return "October";
        case 11: return "November";
        case 12: return "December";
        default: return "Null";
    }
}


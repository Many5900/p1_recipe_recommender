// main.c
#include "api/api_functions.h"
#include "item/item_functions.h"
#include "deserializer/deserializer.h"
#include "print/print.h"
#include <stdio.h>
#include <stdlib.h>


#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
#include "time.h"

#define MAX_TITLE_LENGTH 30
#define MAX_DATE_LENGTH 11

void convertToLowerCase(char str[]);
void checkExpiration(const char *expiration_date);
void displayMainMenu();
void navigateterminal();
int settings(int People_in_household);
void add_item(char title[], char expiration_date[], int *qty, int *price);
struct Date convertToDate(const char *dateStr);
int calculateDaysDifference(struct Date expirationDate);

struct Date {
    int day;
    int month;
    int year;
};

struct Date convertToDate(const char *dateStr) {
    struct Date result;

    // Extract day, month, and year
    sscanf(dateStr, "%d-%d-%d", &result.day, &result.month, &result.year);

    return result;
}
// Function to calculate the difference in days between two dates
int calculateDaysDifference(struct Date expirationDate) {
    time_t t;
    struct tm *currentDate_tm, expirationDate_tm;

    // Get the current time
    time(&t);

    // Convert the current time to a UTC time structure
    currentDate_tm = gmtime(&t);

    // Set the time for the current date to midnight
    currentDate_tm->tm_hour = 0;
    currentDate_tm->tm_min = 0;
    currentDate_tm->tm_sec = 0;

    // Set the expiration date
    expirationDate_tm.tm_year = expirationDate.year - 1900;
    expirationDate_tm.tm_mon = expirationDate.month - 1;
    expirationDate_tm.tm_mday = expirationDate.day;
    expirationDate_tm.tm_hour = 0;
    expirationDate_tm.tm_min = 0;
    expirationDate_tm.tm_sec = 0;
    expirationDate_tm.tm_isdst = 0; // This assumes daylight saving time is not in effect

    // Convert both dates to time_t and calculate the difference
    time_t current_time = mktime(currentDate_tm);
    time_t expiration_time = mktime(&expirationDate_tm);

    // Calculate the difference in seconds
    int difference_in_seconds = difftime(expiration_time, current_time);

    // Convert seconds to days
    int difference_in_days = difference_in_seconds / (60 * 60 * 24);

    return difference_in_days;
}

void convertToLowerCase(char str[]) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}


int settings(int PEOPLE_IN_HOUSEHOLD){
    printf("Enter amount of people in household: \n");
    scanf(" %d", &PEOPLE_IN_HOUSEHOLD);
    return PEOPLE_IN_HOUSEHOLD;
}




void add_item(char title[], char expiration_date[], int *qty, int *price) {
    int i = 0;
    printf("Enter item name: ");
    scanf("%s", title);
    convertToLowerCase(title);

    printf("Enter quantity of item: ");
    scanf("%d", qty);
    printf("Enter expiration date of item (format : dd-mm-yyyy): ");
    scanf("%s", expiration_date);
    //printf(expiration_date);

    // Check if the item is expired
    int days_difference = calculateDaysDifference(convertToDate(expiration_date));

    printf("Enter price of item: ");
    scanf("%d", price);

    db_add_item(title, expiration_date, *qty, *price);
}



void displayMainMenu() {
    printf("MAIN MENU:\n[1] RECOMMEND RECIPES\n[2] ADD INGREDIENTS\n[3] INVENTORY\n[4] SETTINGS\n[5] EXIT\n");
}



void navigateterminal() {
    int PEOPLE_IN_HOUSEHOLD = 4;
    char terminal_number, sub_choice;
    char title[MAX_TITLE_LENGTH];
    char expiration_date[MAX_DATE_LENGTH];
    int qty, price;

    while (1){
        displayMainMenu();
        scanf(" %c", &terminal_number);

        switch (terminal_number){
            case '1': //Recipe tab
                // HER SKAL VÆRE 3 opskrifter som bliver printet gennem funktionpå bagggrund af
                printf("[R] Return to menu\n");
                scanf(" %c", &sub_choice);
                if (sub_choice == 'R')
                    break;

            case '2': // Add item function tab
                while (1) {
                    printf("[1] Add new ingredient to inventory \n[R] Return to menu\n");
                    scanf(" %c", &sub_choice);
                    if (sub_choice == '1') {
                        add_item(title, expiration_date, &qty, &price);
                        int daysdifference = calculateDaysDifference(convertToDate(expiration_date));
                    } else if (sub_choice == 'R' || sub_choice == 'r') {
                        break;
                    } else {
                        printf("Invalid input, try again\n");
                    }
                }
                break;


            case '3': //Inventory tab
                while (1){
                    printf("[1] Show inventory \n[2] Edit inventory\n[R] Return to menu\n");
                    scanf(" %c", &sub_choice);
                    if (sub_choice == '1') {

                    } else if (sub_choice == 'R' ||sub_choice =='r') {
                        break;
                    } else {
                        printf("Invalid input, try again\n");
                    }
                }
                break;


            case '4': //Settings tab
                while (1) {
                    printf("[1] Change number of people in household\n[R] Return to menu\n");
                    scanf(" %c", &sub_choice);
                    if (sub_choice == '1') {
                        PEOPLE_IN_HOUSEHOLD = settings(PEOPLE_IN_HOUSEHOLD); // Update PEOPLE_IN_HOUSEHOLD
                    } else if (sub_choice == 'R' ||sub_choice =='r') {
                        break;
                    } else {
                        printf("Invalid input, try again\n");
                    }
                }
                break;

            case '5': // Exit program
                printf("Exiting program. \n");
                printf("%d",PEOPLE_IN_HOUSEHOLD);
                exit(0);

        }
    }
}

int main(){
    navigateterminal();

}
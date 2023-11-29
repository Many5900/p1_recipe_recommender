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
void space();

char* extractYear(const char *date) {
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

char* extractMonth(const char *date) {
    char *month = NULL;

    if (strlen(date) >= 5) {
        month = (char* )malloc(3 * sizeof(char));  // Allocate memory for the month string
        if (month != NULL) {
            strncpy(month, date + 3, 2);  // Copy the month substring
            month[2] = '\0';  // Null terminate the string
        }
    }

    return month;  // Return the dynamically allocated month or NULL
}

struct Date {
    int day;
    int month;
    int year;
};

double UsedPrice(UsedItemsArray usedItemsArray, int idx) {
    double qty = (double) usedItemsArray.used_item[idx].qty;
    double start_qty = (double) usedItemsArray.used_item[idx].start_qty;
    double price = (double) usedItemsArray.used_item[idx].price;
    double used_amount = start_qty-qty;

    return used_amount/start_qty*price;
};

double LifetimeUsedPrice(UsedItemsArray usedItemsArray) {
    double total_lifetime_used = 0.0;

    for (int i = 0; i<usedItemsArray.count;i++) {
        total_lifetime_used += UsedPrice(usedItemsArray, i);
    }
    return total_lifetime_used;
};

double YearlyUsedPrice(UsedItemsArray usedItemsArray, int current_year) {
    double total_yearly_used = 0.0;

    for (int i = 0; i < usedItemsArray.count; i++) {
        int year = atoi(extractYear(usedItemsArray.used_item[i].expire_date));
        if (year == current_year) {
            total_yearly_used += UsedPrice(usedItemsArray, i);
        }
    }
    return total_yearly_used;
}


double WeekUsedPrice(UsedItemsArray usedItemsArray, int current_year, int current_week) {
    double total_week_used = 0.0;

    for(int i = 0; i < usedItemsArray.count; i++) {
        int year = atoi(extractYear(usedItemsArray.used_item[i].expire_date));
        int week = usedItemsArray.used_item[i].week;
        if (week = 52 || 53 || 54 && extractMonth(usedItemsArray.used_item[i].expire_date) == 1 || extractMonth(usedItemsArray.used_item[i].expire_date)==01){
            year = year - 1;

        }
        if (year == current_year) {
            if(week == current_week){
                total_week_used += UsedPrice(usedItemsArray, i);
            }
            return total_week_used;
        }

    }
}

double MonthlyUsedPrice(UsedItemsArray usedItemsArray, int current_year, int current_month) {
    double total_monthly_used = 0.0;
    for (int i = 0; i < usedItemsArray.count; i++) {
        int year = atoi(extractYear(usedItemsArray.used_item[i].expire_date));
        if (year == current_year) {
            int month = atoi(extractMonth(usedItemsArray.used_item[i].expire_date));
            if (month == current_month) {
                total_monthly_used += UsedPrice(usedItemsArray, i);
            }
        }
    }
    return total_monthly_used;
}


double ExpiredPriceLeft(StatsArray statsArray, int idx) {
    double qty = (double)statsArray.stats[idx].qty;
    double start_qty = (double)statsArray.stats[idx].start_qty;
    double price = (double)statsArray.stats[idx].price;

    return (qty / start_qty) * price;
}

double ExpiredLifetimeStats(StatsArray statsArray) {
    double total_life_waste = 0.0;

    for (int i = 0; i < statsArray.count; i++) {
        total_life_waste += ExpiredPriceLeft(statsArray, i);
    }
    return total_life_waste;
}

double ExpiredYearlyStats(StatsArray statsArray, int current_year) {
    double total_yearly_waste = 0.0;

    for (int i = 0; i < statsArray.count; i++) {
        int year = atoi(extractYear(statsArray.stats[i].expire_date));
        if (year == current_year) {
            total_yearly_waste += ExpiredPriceLeft(statsArray, i);
        }
    }
    return total_yearly_waste;
}

double ExpiredMonthlyStats(StatsArray statsArray, int current_year, int current_month) {
    double total_month_waste = 0.0;

    for (int i = 0; i < statsArray.count; i++) {
        int year = atoi(extractYear(statsArray.stats[i].expire_date));
        if (year == current_year) {
            int month = atoi(extractMonth(statsArray.stats[i].expire_date));
            if (month == current_month) {
                total_month_waste += ExpiredPriceLeft(statsArray, i);
            }
        }
    }
    return total_month_waste;
}

double ExpiredWeeklyStats(StatsArray statsArray, int current_year, int current_week) {
    double total_weekly_waste = 0.0;

    for (int i = 0; i <statsArray.count; i++) {
        int year = atoi(extractYear(statsArray.stats[i].expire_date));
        int week = statsArray.stats[i].week;
        if (week == 52 || 53 || 54 && extractMonth(statsArray.stats[i].expire_date) == 1 ||
            extractMonth(statsArray.stats[i].expire_date) == 01) {
            year = year - 1;
        }
        if (year == current_year) {
            if (week == current_week) {
                total_weekly_waste += ExpiredPriceLeft(statsArray, i);
            }
            return total_weekly_waste;
        }
    }
}


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

int getCurrentYear() {
    // Get the current time
    time_t t = time(NULL);
    struct tm tm_info = *localtime(&t);

    // Extract the current year
    int current_year = tm_info.tm_year + 1900;

    return current_year;
}

int getCurrentMonth() {
    // Get the current time
    time_t t = time(NULL);
    struct tm tm_info = *localtime(&t);

    // Extract the current month
    int current_month = tm_info.tm_mon + 1;  // Months are zero-based

    return current_month;
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

    printf("Enter price of item (in danish kr): ");
    scanf("%d", price);

    db_add_item(title, expiration_date, *qty, *price);
}

void delete_item() {
    char id[26];
    space();
    printf("Enter item id: ");
    scanf("%s", id);

    // Get the item with the specified ID
    const char *json_string = db_get_by_id(id);
    ItemArray itemArray = deserialize_items(json_string);
    print_items(&itemArray);
    free_items(&itemArray);

    // Are U sure?
    printf("Are you shure you want to delete the item above?\n");
    printf("[1] Yes\n");
    printf("[2] No\n");

    while (1) {
        char confirm;
        scanf("%c", &confirm);
        if (confirm == '1') {
            db_delete_by_id(id);
            space();
            break;
        } else if (confirm == '2') {
            space();
            break;
        }
    }


    // printf("%s", id);
}



void displayMainMenu() {
    space();
    printf("MAIN MENU:\n[1] RECOMMEND RECIPES\n[2] ADD INGREDIENTS\n[3] INVENTORY\n[4] CHECK STATISTICS\n[5] SETTINGS\n[6] EXIT\n");
}

void space() {
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
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
                    space();
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
                space();
                while (1){
                    printf("[1] Show inventory \n[2] Edit inventory\n[R] Return to menu\n");
                    scanf(" %c", &sub_choice);
                    if (sub_choice == '1') {
                        space();
                        const char *json_string = db_items();
                        ItemArray itemArray = deserialize_items(json_string);
                        print_items(&itemArray);
                        free_items(&itemArray);
                    } else if (sub_choice == '2') {
                        space();
                        printf("[1] Delete Item \n[2] Update item params\n[R] Go back\n");
                        scanf(" %c", &sub_choice);

                        if (sub_choice == '1') {
                            delete_item();
                        } else if (sub_choice == '2') {

                        } else if (sub_choice == 'R' || sub_choice =='r') {
                            space();
                            continue;
                        }
                    } else if (sub_choice == 'R' || sub_choice =='r') {
                        break;
                    } else {
                        printf("Invalid input, try again\n");
                    }
                }
                break;

            case '4': //Stats tab
                while (1) {
                    printf("[1] Check the Weekly statistics!\n[2] Check the Monthly statistics!\n[3] Check the Yearly statistics!\n[4] Check Lifetime statistics\n[R] Return to menu\n");
                    scanf(" %c", &sub_choice);
                    if (sub_choice == '1') {
                        printf("[1] Check the worth of last weeks used ingredients\n[2] Check the worth of lasts weeks ingredients that expired\n[R] Return to menu\n");
                        scanf(" %c", &sub_choice);
                        if (sub_choice == '1') {
                        }
                        else if (sub_choice == '2') {
                            const char *json_string = db_stats();
                            StatsArray statsArray = deserialize_stats(json_string);
                            double value = ExpiredWeeklyStats(statsArray, getCurrentYear(), 45-2);
                            double value2 = ExpiredWeeklyStats(statsArray, getCurrentYear(), 45 - 1);
                            if (value2 < value) {
                                double new_value = value - value2;
                                printf("You wasted %.2lf DDK worth of ingredients less last week than the previous week. Keep it up!\n",
                                       new_value);
                            } else {
                                double new_value = value2 - value;
                                printf("You wasted %.2lf DDK worth of ingredients more last week than the previous week. Tag dig sammen!\n",
                                       new_value);
                            }
                        }
                        else if (sub_choice == 'R' || sub_choice =='r') {
                            space();
                            continue;
                        }
                    } else if (sub_choice =='2'){
                        const char *json_string = db_stats();
                        StatsArray statsArray = deserialize_stats(json_string);
                        double value = ExpiredMonthlyStats(statsArray, getCurrentYear(), getCurrentMonth());
                        printf("In the year %d you have thrown out %.2lf DDK worth of food\n", getCurrentYear(), value);
                    }else if (sub_choice == '3') {
                        const char *json_string = db_stats();
                        StatsArray statsArray = deserialize_stats(json_string);
                        int current_year = getCurrentYear();
                        double value = ExpiredYearlyStats(statsArray, current_year);
                        printf("In the year %d you have thrown out %.2lf DDK worth of food\n", getCurrentYear(), value);
                    }else if (sub_choice == '4') {
                        const char *json_string = db_stats();
                        StatsArray statsArray = deserialize_stats(json_string);
                        ExpiredLifetimeStats(statsArray);
                    } else if (sub_choice == 'R' || sub_choice =='r') {
                        break;
                    } else {
                        printf("Invalid input, try again\n");
                    }
                }
                break;


            case '5': //Settings tab
                while (1) {
                    printf("[1] Change number of people in household\n[R] Return to menu\n");
                    scanf(" %c", &sub_choice);
                    if (sub_choice == '1') {
                        PEOPLE_IN_HOUSEHOLD = settings(PEOPLE_IN_HOUSEHOLD); // Update PEOPLE_IN_HOUSEHOLD
                    } else if (sub_choice == 'R' || sub_choice =='r') {
                        break;
                    } else {
                        printf("Invalid input, try again\n");
                    }
                }
                break;

            case '6': // Exit program
                printf("Exiting program. \n");
                printf("%d",PEOPLE_IN_HOUSEHOLD);
                exit(0);

        }
    }
}


int main() {

    db_add_used_item("salt", "27-11-2023", 20, 40, 50);


    // navigateterminal();
    return 0;
};
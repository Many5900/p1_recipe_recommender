//
// Created by Marc Nygaard on 04/12/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include "logic/menu_logic.h"
#include "../time/time_and_date.h"
#include "../deserializer/deserializer.h"
#include "../item/item_functions.h"
#include "../print/print.h"
#include "../stats/stats.h"

#define MAX_TITLE_LENGTH 30
#define MAX_DATE_LENGTH 11

/*******************
***** Settings *****
*******************/

int settings(int PEOPLE_IN_HOUSEHOLD) {
    printf("Enter amount of people in household: \n");
    scanf(" %d", &PEOPLE_IN_HOUSEHOLD);
    return PEOPLE_IN_HOUSEHOLD;
}





/****************************
***** display main menu *****
****************************/

void displayMainMenu() {
    space();
    printf("MAIN MENU:\n[1] RECOMMEND RECIPES\n[2] ADD INGREDIENTS\n[3] INVENTORY\n[4] CHECK STATISTICS\n[5] SETTINGS\n[6] EXIT\n");
}





/****************************
***** navigate terminal *****
****************************/

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
                    printf("[1] Check the Weekly statistics!\n"
                           "[2] Check the Monthly statistics!\n"
                           "[3] Check the Yearly statistics!\n"
                           "[4] Check Lifetime statistics\n"
                           "[R] Return to menu\n");

                    scanf(" %c", &sub_choice);

                    if (sub_choice == '1') {
                        while (1) {
                            const char *json_string = db_used_items();
                            UsedItemsArray usedItemArray = deserialize_used_items(json_string);
                            const char *json_string2 = db_stats();
                            StatsArray statsArray = deserialize_stats(json_string2);

                            double Used_previous_week = WeekUsedPrice(usedItemArray, getCurrentYear(), now_week() - 1);
                            double Expired_previous_week = ExpiredWeeklyStats(statsArray, getCurrentYear(), now_week() - 1);
                            double Expired_compare_week = ExpiredWeeklyStats(statsArray, getCurrentYear(), now_week() - 2);

                            printf("WEEKLY STATISTICS\n\n");
                            printf("stats for the previous week: %d\n", now_week() - 1);
                            printf("Used ingredients in DKK: %.2lf\n", Used_previous_week);
                            printf("Expired ingredients in DKK: %.2lf\n\n", Expired_previous_week);

                            if (Expired_previous_week < Expired_compare_week) {
                                double new_value = Expired_compare_week - Expired_previous_week;
                                double decrease_percentage = ((Expired_compare_week - Expired_previous_week) / Expired_previous_week) * 100.0;
                                printf("You wasted %.2lf DKK less the previous compared to the week before, which is %.1lf%% less.\nYou are saving the world, keep it up!\n",
                                       new_value, decrease_percentage);
                            } else if (Expired_previous_week>Expired_compare_week) {
                                double new_value = Expired_previous_week - Expired_compare_week;
                                double increase_percentage = ((Expired_previous_week - Expired_compare_week) / Expired_compare_week) * 100.0;
                                printf("You wasted %.2lf DKK more the previous week compared to the week before, which is %.1lf%% more.\nDo better!\n\n",
                                       new_value, increase_percentage);
                            } else {
                                printf("You wasted the same amount of DKK the previous week as the week before\n");
                            }

                            // Add a prompt to return to the weekly statistics menu
                            printf("[R] Return to statistics menu\n");
                            scanf(" %c", &sub_choice);
                            if (sub_choice == 'R' || sub_choice == 'r') {
                                break; // Return to the statistics menu
                            }
                        }

                    } else if (sub_choice =='2') {
                        while (1) {
                            const char *json_string = db_used_items();
                            UsedItemsArray usedItemArray = deserialize_used_items(json_string);
                            const char *json_string2 = db_stats();
                            StatsArray statsArray = deserialize_stats(json_string2);

                            double Used_previous_month = MonthlyUsedPrice(usedItemArray, getCurrentYear(),
                                                                          getCurrentMonth());
                            double Expired_previous_month = ExpiredMonthlyStats(statsArray, getCurrentYear(),
                                                                                getCurrentMonth());
                            printf("MONTHLY STATISTICS\n\n");
                            printf("So far you have used %.2lf DKK worth of ingredients this month, and a total of %.2lf DKK worth of ingredients have expired\n",
                                   Used_previous_month, Expired_previous_month);
                            printf("[1] Check the comparison between the previous month and the month before.\n"
                                   "[2] Compare previous month with the same month last year.\n"
                                   "[R] return to statistics\n");
                            scanf(" %c", &sub_choice);
                            if (sub_choice == '1') {

                                double Used_previous_month = MonthlyUsedPrice(usedItemArray, getCurrentYear(),
                                                                              now_month() - 1);
                                double Used_compare_month = MonthlyUsedPrice(usedItemArray, getCurrentYear(),
                                                                             now_month() - 2);
                                double Expired_previous_month = ExpiredMonthlyStats(statsArray, getCurrentYear(),
                                                                                    now_month() - 1);
                                double Expired_compare_month = ExpiredMonthlyStats(statsArray, getCurrentYear(),
                                                                                   now_month() - 2);

                                if (Expired_previous_month < Expired_compare_month) {
                                    double new_value = Expired_compare_month - Expired_previous_month;

                                    double decrease_percentage =
                                            ((Expired_compare_month - Expired_previous_month) / Expired_compare_month) *
                                            100.0;;
                                    printf("You wasted %.2lf DKK less the previous month compared to the month before, which is %.1lf% less.\n You are awesome!!! Keep it up!\n",
                                           new_value, decrease_percentage);
                                } else if (Expired_previous_month > Expired_compare_month) {
                                    double new_value = Expired_previous_month - Expired_compare_month;
                                    double increase_percentage =
                                            ((Expired_previous_month - Expired_compare_month) / Expired_compare_month) *
                                            100.0;
                                    printf("You wasted %.2lf DKK more the previous month compared to the month before, which is %.1lf% more.\n Do better!\n",
                                           new_value, increase_percentage);
                                } else {
                                    printf("You wasted the same amount of DKK the previous month as the month before\n");
                                }

                                // Add a prompt to return to the monthly statistics menu
                                printf("[R] Return to monthly statistics menu\n");
                                scanf(" %c", &sub_choice);
                                if (sub_choice == 'R' || sub_choice == 'r') {
                                    break; // Return to the statistics menu
                                }


                            } else if (sub_choice == '2') {
                                double used_previous_month = MonthlyUsedPrice(usedItemArray,getCurrentYear(),getCurrentMonth()-1);
                                double expired_previous_month = ExpiredMonthlyStats(statsArray,getCurrentYear(),getCurrentMonth()-1);
                                double used_last_year_month = MonthlyUsedPrice(usedItemArray, getCurrentYear()-1, getCurrentMonth()-1);
                                double expired_last_year_month = ExpiredMonthlyStats(statsArray, getCurrentYear()-1,getCurrentMonth()-1);

                                // Convert numeric month to string
                                const char* lastMonthString = getMonthString(getCurrentMonth() - 1);
                                printf("%s - %d you used %lf DKK worth of ingredients\n", lastMonthString, getCurrentYear()-1,
                                       MonthlyUsedPrice(usedItemArray, getCurrentYear()-1, getCurrentMonth()-1));
                                printf("%s - %d you wasted %lf DKK worth of ingredients\n", lastMonthString, getCurrentYear()-1,
                                       ExpiredMonthlyStats(statsArray, getCurrentYear()-1, getCurrentMonth()-1));
                                printf("%s - %d you used %lf DKK worth of ingredients\n", lastMonthString, getCurrentYear(),
                                       MonthlyUsedPrice(usedItemArray, getCurrentYear(), getCurrentMonth()-1));
                                printf("%s - %d you wasted %lf DKK worth of ingredients\n", lastMonthString, getCurrentYear(),
                                       ExpiredMonthlyStats(statsArray, getCurrentYear(), getCurrentMonth()-1));
                                if (expired_previous_month < expired_last_year_month){
                                    double decrease_percentage = ((expired_last_year_month - expired_previous_month) / expired_previous_month) * 100.0;;
                                    printf("This is %.2lf% less compared to the same %s last year\n", decrease_percentage, lastMonthString);
                                }
                                else if (expired_previous_month > expired_last_year_month){
                                    double increase_percentage = ((expired_previous_month - expired_last_year_month) / expired_last_year_month) * 100.0;;
                                    printf("This is %.2lf% more compared to the same %s last year\n", increase_percentage, lastMonthString);
                                } else {
                                    printf("You used the same amount of DKK in %s compared to the same %s last year\n", lastMonthString, lastMonthString);
                                }
                                printf("[R] Return to monthly statistics menu\n");
                                scanf(" %c", &sub_choice);
                                if (sub_choice == 'R' || sub_choice == 'r') {
                                    break; // Return to the statistics menu
                                }

                            } else if (sub_choice == 'R' || sub_choice == 'r') {
                                break; // Return to statistics menu
                            }
                        }


                    } else if (sub_choice == '3') {
                        const char *json_string = db_used_items();
                        UsedItemsArray usedItemArray = deserialize_used_items(json_string);
                        const char *json_string2 = db_stats();
                        StatsArray statsArray = deserialize_stats(json_string2);

                        double used_current_year = YearlyUsedPrice(usedItemArray, getCurrentYear());
                        double expired_current_year = ExpiredYearlyStats(statsArray, getCurrentYear());
                        double used_last_year = YearlyUsedPrice(usedItemArray, getCurrentYear()-1);
                        double expired_last_year = ExpiredYearlyStats(statsArray, getCurrentYear()-1);

                        printf("YEARLY STATISTICS\n\n");
                        printf("In the year %d so far, you have used %.2lf worth of ingredients, and wasted  %.2lf DKK worth of expired ingredients\n", getCurrentYear(), used_current_year, expired_current_year);
                        printf("Last year you used %.2lf worth of ingredients, and wasted %.2lf DKK worth of ingredients\n\n", used_last_year, expired_last_year);
                        printf("[R] Return to statistics menu\n");
                        scanf(" %c", &sub_choice);
                        if (sub_choice == 'R' || sub_choice == 'r') {
                            break; // Return to the statistics menu
                        }
                        else {
                            printf("Invalid input, try again\n");
                        }

                    }else if (sub_choice == '4') {
                        const char *json_string = db_used_items();
                        UsedItemsArray usedItemArray = deserialize_used_items(json_string);
                        const char *json_string2 = db_stats();
                        StatsArray statsArray = deserialize_stats(json_string2);

                        double expired_lifetime = ExpiredLifetimeStats(statsArray);
                        double used_lifetime = LifetimeUsedPrice(usedItemArray);
                        printf("LIFETIME STATISTICS\n\n");
                        printf("So far you have used %.2lf DKK worth of ingredients in total, and you have wasted %.2lf DKK worth of expired ingredients!\n\n", used_lifetime, expired_lifetime);
                        printf("[R] Return to statistics menu\n");
                        scanf(" %c", &sub_choice);
                        if (sub_choice == 'R' || sub_choice == 'r') {
                            break; // Return to the statistics menu
                        }
                        else {
                            printf("Invalid input, try again\n");
                        }


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
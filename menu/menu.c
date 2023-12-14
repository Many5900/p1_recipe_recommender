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
#include "../recipe_recommender/recipe_recommender.h"

// Defining global variables
#define MAX_TITLE_LENGTH 30
#define MAX_DATE_LENGTH 11

/************************************************
***** Settings - Change people in household *****
************************************************/

int change_people_in_household(int people_in_household) {
    printf("Enter amount of people in household: \n");
    scanf(" %d", &people_in_household);

    return people_in_household;
}

/**************************
***** Print main menu *****
**************************/

void print_main_menu() {
    space();
    printf("MAIN MENU:\n"
           "[1] RECOMMEND RECIPES\n"
           "[2] ADD INGREDIENT\n"
           "[3] INVENTORY\n"
           "[4] STATISTICS\n"
           "[5] SETTINGS\n"
           "[6] EXIT\n");
}

/*******************************
***** The main application *****
*******************************/

void application() {
    // Declaring some basic "global" state for the application
    int people_in_household = 1;
    char main_menu_option_number, sub_option_number;
    char title[MAX_TITLE_LENGTH];
    char expiration_date[MAX_DATE_LENGTH];
    int qty, price;

    // Infinite loop
    while (1) {
        print_main_menu();

        // User picks an option
        scanf(" %c", &main_menu_option_number);

        // Start of the switch
        switch (main_menu_option_number) {
            /****************************
            ***** RECOMMEND RECIPES *****
            ****************************/
            case '1': // If the user picks '1' --- RECOMMEND RECIPES
                space();

                // Find top 8 recipes based on available inventory and the amount of people in household
                recipe_recommender(people_in_household);

                // Prompt the user the option to use some of the ingredients from recipes or return to the main menu
                printf("\n[1] Use ingredient\n"
                         "[R] Return to main menu\n");

                // Check for what sub option the user picked
                scanf(" %c", &sub_option_number);

                if (sub_option_number == '1') { // Sub option [1][1] --- USE INGREDIENT
                    while (1) {
                        use_ingredient(); // Prompt the user for which ingredient to use

                        // Prompt the user that option to use another ingredient or return to menu
                        printf("\n[1] Use another ingredient"
                               "\n[R] Return to main menu \n");

                        // Check for what sub option the user picked
                        scanf(" %c", &sub_option_number);

                        if (sub_option_number == '1') { // Sub option [1][1][1] --- USE ANOTHER INGREDIENT
                            continue; // Run the loop from the beginning once more
                        } else if (sub_option_number == 'R' || sub_option_number =='r') { // Sub option [1][1][R] --- RETURN TO MENU
                            break; // Break out of the infinite loop in order to return to menu
                        } else {
                            printf("Invalid input, try again...\n"); // The user didn't type '1' or 'R'...
                        }
                    }
                } else if (sub_option_number == 'R' || sub_option_number =='r') { // Sub option [1][R] --- RETURN TO MAIN MENU
                    break; // Break out of switch case '1' (RECOMMEND RECIPES) in order to return to the main menu
                }
                break;





            /*************************
            ***** ADD INGREDIENT *****
            *************************/
            case '2': // If the user picks '2' --- ADD INGREDIENT
                space();

                while (1) {
                    // Prompt the user the option to add a new ingredient to the inventory or return to the main menu
                    printf("[1] Add new ingredient to inventory\n"
                           "[R] Return to main menu\n");

                    // Check for what sub option the user picked
                    scanf(" %c", &sub_option_number);

                    if (sub_option_number == '1') { // Sub option [2][1] --- ADD NEW INGREDIENT TO INVENTORY
                        // Ask the user for a title, expiration date, quantity & price. Afterward add it to the database
                        add_ingredient_to_inventory(title, expiration_date, &qty, &price);

                        // Reload the database in case the user add an ingredient that has expired
                        db_reload();

                    } else if (sub_option_number == 'R' || sub_option_number == 'r') { // Sub option [2][R] --- RETURN TO MAIN MENU
                        break; // Break out of switch case '2' (ADD INGREDIENT) in order to return to the main menu
                    } else {
                        printf("Invalid input, try again...\n"); // The user didn't type '1' or 'R'...
                    }
                }
                break;





            /********************
            ***** INVENTORY *****
            ********************/
            case '3': // If the user picks '3' --- INVENTORY
                space();

                while (1) {
                    // Prompt the user the option to show inventory, delete an ingredient or return to the main menu
                    printf("[1] Show inventory\n"
                           "[2] Delete ingredient\n"
                           "[R] Return to main menu\n");

                    // Check for what sub option the user picked
                    scanf(" %c", &sub_option_number);

                    if (sub_option_number == '1') { // Sub option [3][1] --- SHOW INVENTORY
                        space();

                        db_reload(); // Reload the database in case there are some changes to the expiration date and more

                        // Fetch all ingredients from the database and deserialize it from json into IngredientsArray_t
                        const char *json_string = db_ingredients();
                        IngredientsArray_t ingredients_array = deserialize_ingredients(json_string);

                        // Print all ingredients in the inventory/database one by one
                        print_ingredients(&ingredients_array);

                        // Afterward dealocate/free the memory
                        free_ingredients(&ingredients_array);

                    } else if (sub_option_number == '2') { // Sub option [3][2] --- DELETE INGREDIENT
                        space();

                        // Prompt the user about which ingredient they wish to delete
                        delete_ingredient();

                    } else if (sub_option_number == 'R' || sub_option_number =='r') { // Sub option [3][R] --- RETURN TO MAIN MENU
                        break; // Break out of switch case '3' (INVENTORY) in order to return to the main menu
                    } else {
                        printf("Invalid input, try again...\n"); // The user didn't type '1', '2' or 'R'...
                    }
                }
                break;





            /*********************
            ***** STATISTICS *****
            *********************/
            case '4': // If the user picks '4' --- STATISTICS
            space();

                while (1) {
                    /*
                     * Prompt the user the option to...
                     * check weekly statistics,
                     * check monthly statistics,
                     * check yearly statistics,
                     * check lifetime statistics or
                     * return to the main menu
                     */
                    printf("[1] Weekly statistics\n"
                           "[2] Monthly statistics\n"
                           "[3] Yearly statistics\n"
                           "[4] Lifetime statistics\n"
                           "[R] Return to main menu\n");

                    // Check for what sub option the user picked
                    scanf(" %c", &sub_option_number);



                    /* ---------------------------------------------------------------------------------------------------- */

                    // Fetch all used ingredients and deserialize it into UsedIngredientsArray_t
                    const char *json_string = db_used_ingredients();
                    UsedIngredientsArray_t used_ingredients_array = deserialize_used_ingredients(json_string);

                    // Fetch all stats and deserailize it into StatsArray_t
                    const char *json_string_2 = db_stats();
                    StatsArray_t stats_array = deserialize_stats(json_string_2);

                    // Get the last week and the week before that compared to the current week & get the current year
                    int one_week_ago = now_week() - 1;
                    int two_weeks_ago = now_week() - 2;
                    int current_year = get_current_year();

                    // Get the amount of money spend on ingredients one week ago
                    double money_spend_on_ingredients_previous_week = weekly_used_price(used_ingredients_array, current_year, one_week_ago);

                    // Get the amount of money wasted due to expired ingredients one week ago
                    double expired_ingredients_one_week_ago = expired_weekly_stats(stats_array, current_year, one_week_ago);

                    // Get the amount of money wasted due to expired ingredients two weeks ago
                    double expired_ingredients_two_weeks_ago = expired_weekly_stats(stats_array, current_year, two_weeks_ago);



                    // Get the last month and the month brefore that compared to the current month & get current month
                    int one_month_ago = get_current_month() - 1;
                    int two_months_ago = get_current_month() - 2;
                    int current_month = get_current_month();

                    // Get the amount of money spend on ingredients the current month
                    double money_spend_on_ingredients_current_month = monthly_used_price(used_ingredients_array, current_year, current_month);

                    // Get the amount of money wasted due to expired ingredients the current month
                    double expired_ingredients_current_month = expired_monthly_stats(stats_array, current_year, current_month);

                    // Get the amount of money wasted due to expired ingredients one month ago
                    double expired_ingredients_one_month_ago = expired_monthly_stats(stats_array, current_year,one_month_ago);

                    // Get the amount of money wasted due to expired ingredients two months ago
                    double expired_ingredients_two_months_ago = expired_monthly_stats(stats_array, current_year,two_months_ago);



                    // Get last year
                    int one_year_ago = current_year - 1;

                    // Get the amount of money wasted due to expired ingredients one month ago (last year)
                    double expired_ingredients_one_month_ago_last_year = expired_monthly_stats(stats_array, one_year_ago,one_month_ago);



                    // Convert numeric month to string eg. 2 = February or 8 = August
                    const char* last_month_as_string = get_numeric_month_as_string(one_month_ago);

                    // Get the amount of money spend on ingredients one month ago last year
                    double money_spend_on_ingredients_one_month_ago_last_year = monthly_used_price(used_ingredients_array, one_year_ago, one_month_ago);

                    // Get the amount of money spend on ingredients one month ago
                    double money_spend_on_ingredients_one_month_ago = monthly_used_price(used_ingredients_array, current_year, one_month_ago);



                    // Get the amount of money spend on ingredients the current year
                    double money_spend_on_ingredients_current_year = yearly_used_price(used_ingredients_array, current_year);

                    // Get the amount of money wasted due to expired ingredients the current year
                    double expired_ingredients_current_year = expired_yearly_stats(stats_array, current_year);

                    // Get the amount of money spend on ingredients one year ago
                    double money_spend_on_ingredients_one_year_ago = yearly_used_price(used_ingredients_array, one_year_ago);

                    // Get the amount of money wasted due to expired ingredients one year ago
                    double expired_ingredients_one_year_ago = expired_yearly_stats(stats_array, one_year_ago);



                    // Get the amount of money wasted due to expired ingredients (lifetime)
                    double expired_ingredients_lifetime = expired_lifetime_stats(stats_array);

                    // Get the amount of money spend on ingredients (lifetime)
                    double money_spend_on_ingredients_lifetime = lifetime_used_price(used_ingredients_array);

                    /* ---------------------------------------------------------------------------------------------------- */



                    if (sub_option_number == '1') { // Sub option [4][1] --- CHECK WEEKLY STATISTICS
                        space();

                        while (1) {
                            // Print weekly statistics
                            printf("WEEKLY STATISTICS:\n");
                            printf("Stats for the previous week: %d\n", one_week_ago);
                            printf("Used ingredients in DKK: %.2lf\n", money_spend_on_ingredients_previous_week);
                            printf("Expired ingredients in DKK: %.2lf\n\n", expired_ingredients_one_week_ago);

                            // Check if the amount of money wasted one week ago is less that the amount of money wasted two weeks ago
                            if (expired_ingredients_one_week_ago < expired_ingredients_two_weeks_ago) {
                                // Calcualte the difference between the amount of wasted money between week one and two
                                double difference_between_week_one_and_two = expired_ingredients_two_weeks_ago - expired_ingredients_one_week_ago;

                                // Calculate the percentage
                                double decrease_percentage = ((expired_ingredients_two_weeks_ago - expired_ingredients_one_week_ago) / expired_ingredients_two_weeks_ago) * 100.0;

                                // Print/Inform the user that they...
                                printf("You wasted %.2lf DKK less the previous compared to the week before, which is %.1lf%% less.\nYou are saving the world, keep it up!\n",
                                                   difference_between_week_one_and_two,                              decrease_percentage);

                            } else if (expired_ingredients_one_week_ago > expired_ingredients_two_weeks_ago) {
                                // Calcualte the difference between the amount of wasted money between week one and two
                                double difference_between_week_one_and_two = expired_ingredients_one_week_ago - expired_ingredients_two_weeks_ago;

                                // Calculate the percentage
                                double increase_percentage = ((expired_ingredients_one_week_ago - expired_ingredients_two_weeks_ago) / expired_ingredients_two_weeks_ago) * 100.0;

                                // Print/Inform the user that they...
                                printf("You wasted %.2lf DKK more the previous week compared to the week before, which is %.1lf%% more.\nDo better!\n\n",
                                                   difference_between_week_one_and_two,                                   increase_percentage);

                            } else {
                                // Print/Inform the user that they wasted the same amount of money on expired ingredients in week one and two
                                printf("You wasted the same amount of DKK the previous week as the week before\n");
                            }

                            // Prompt the user the option to return to statistics menu
                            printf("[R] Return to statistics menu\n");

                            // Check if the user wants to return to statistics menu
                            scanf(" %c", &sub_option_number);

                            if (sub_option_number == 'R' || sub_option_number == 'r') { // Sub option [4][1][R] --- RETURN TO STATISTICS MENU
                                space();

                                break; // Break out of the infinite loop in order to return to statistics menu
                            }
                        }

                    } else if (sub_option_number =='2') { // Sub option [4][2] --- CHECK MONTHLY STATISTICS
                        space();

                        while (1) {
                            // Print monthly statistics
                            printf("MONTHLY STATISTICS:\n");
                            printf("So far you have used %.2lf DKK worth of ingredients this month, and a total of %.2lf DKK worth of ingredients have expired\n",
                                                         money_spend_on_ingredients_current_month,                 expired_ingredients_current_month);

                            // Prompt the user the option to compare between the previous month and the month before, compare previous month with the same month last year or return to statistics
                            printf("[1] Check the comparison between the previous month and the month before\n"
                                   "[2] Compare previous month with the same month last year\n"
                                   "[R] Return to statistics menu\n");

                            // Check for what sub option the user picked
                            scanf(" %c", &sub_option_number);

                            if (sub_option_number == '1') { // Sub option [4][2][1] --- CHECT THE COMPARISON BETWEEN THE PRECIOUS MONTH AND THE MONTH BEFORE
                                space();

                                // Check if the amount of money wasted one month ago is less that the amount of money wasted two months ago
                                if (expired_ingredients_one_month_ago < expired_ingredients_two_months_ago) {
                                    // Calcualte the difference between the amount of wasted money between month one and two
                                    double difference_between_month_one_and_two = expired_ingredients_two_months_ago - expired_ingredients_one_month_ago;

                                    // Calculate the percentage
                                    double decrease_percentage = ((expired_ingredients_two_months_ago - expired_ingredients_one_month_ago) / expired_ingredients_two_months_ago) * 100.0;

                                    // Print/Inform the user that they...
                                    printf("You wasted %.2lf DKK less the previous month compared to the month before, which is %.1lf%% less. \nYou are awesome!!! Keep it up!\n",
                                                       difference_between_month_one_and_two,                                    decrease_percentage);

                                } else if (expired_ingredients_one_month_ago > expired_ingredients_two_months_ago) {
                                    // Calcualte the difference between the amount of wasted money between month one and two
                                    double difference_between_month_one_and_two = expired_ingredients_one_month_ago - expired_ingredients_two_months_ago;

                                    // Calculate the percentage
                                    double increase_percentage = ((expired_ingredients_one_month_ago - expired_ingredients_two_months_ago) / expired_ingredients_two_months_ago) * 100.0;

                                    // Print/Inform the user that they...
                                    printf("You wasted %.2lf DKK more the previous month compared to the month before, which is %.1lf%% more. \nDo better!\n",
                                                       difference_between_month_one_and_two,                                    increase_percentage);
                                } else {
                                    // Print/Inform the user that they wasted the same amount of money on expired ingredients in month one and two
                                    printf("You wasted the same amount of DKK the previous month as the month before\n");
                                }

                                // Prompt the user the option to return to monthly statistics menu
                                printf("[R] Return to monthly statistics menu\n");

                                // Check if the user wants to return to monthly statistics menu
                                scanf(" %c", &sub_option_number);

                                if (sub_option_number == 'R' || sub_option_number == 'r') { // Sub option [4][2][1][R] --- RETURN TO MONTHLY STATISTICS MENU
                                    space();

                                    continue; // Continue to the top of the loop in order to return to monthly statistics menu
                                }

                            } else if (sub_option_number == '2') { // Sub option [4][2][2] --- COMPARE PREVIOUS MONTH WITH THE SAME MONTH LAST YEAR
                                space();

                                // Print/Inform the user that...
                                printf("%s - %d you used %.2lf DKK worth of ingredients\n", last_month_as_string, one_year_ago, money_spend_on_ingredients_one_month_ago_last_year);

                                // Print/Inform the user that...
                                printf("%s - %d you wasted %.2lf DKK worth of ingredients\n", last_month_as_string, one_year_ago, expired_ingredients_one_month_ago_last_year);

                                // Print/Inform the user that...
                                printf("%s - %d you used %.2lf DKK worth of ingredients\n", last_month_as_string, current_year, money_spend_on_ingredients_one_month_ago);

                                // Print/Inform the user that...
                                printf("%s - %d you wasted %.2lf DKK worth of ingredients\n", last_month_as_string, current_year, expired_ingredients_one_month_ago);

                                if (expired_ingredients_one_month_ago < expired_ingredients_one_month_ago_last_year) {
                                    // Calculate the percentage
                                    double decrease_percentage = ((expired_ingredients_one_month_ago_last_year - expired_ingredients_one_month_ago) / expired_ingredients_one_month_ago_last_year) * 100.0;

                                    // Print/Inform the user that they...
                                    printf("This is %.2lf%% less compared to the same %s last year\n", decrease_percentage, last_month_as_string);
                                } else if (expired_ingredients_one_month_ago > expired_ingredients_one_month_ago_last_year) {
                                    // Calculate the percentage
                                    double increase_percentage = ((expired_ingredients_one_month_ago - expired_ingredients_one_month_ago_last_year) / expired_ingredients_one_month_ago_last_year) * 100.0;

                                    // Print/Inform the user that they...
                                    printf("This is %.2lf% more compared to the same %s last year\n", increase_percentage, last_month_as_string);
                                } else {
                                    // Print/Inform the user that they wasted the same amount of money on expired ingredients the given month compared to the same month the year before
                                    printf("You used the same amount of DKK in %s compared to the same %s last year\n", last_month_as_string, last_month_as_string);
                                }

                                // Prompt the user the option to return to monthly statistics menu
                                printf("[R] Return to monthly statistics menu\n");

                                // Check if the user wants to return to monthly statistics menu
                                scanf(" %c", &sub_option_number);

                                if (sub_option_number == 'R' || sub_option_number == 'r') { // Sub option [4][2][2][R] --- RETURN TO MONTHLY STATISTICS MENU
                                    space();

                                    continue; // Continue to the top of the loop in order to return to monthly statistics menu
                                }

                            } else if (sub_option_number == 'R' || sub_option_number == 'r') { // Sub option [4][2][R] --- RETURN TO STATISTICS MENU
                                space();

                                break; // Break out of the infinite loop in order to return to statistics menu
                            }
                        }


                    } else if (sub_option_number == '3') { // Sub option [4][3] --- CHECK YEARLY STATISTICS
                        space();

                        // Print yearly statistics
                        printf("YEARLY STATISTICS:\n");

                        // Print/Inform the user that they...
                        printf("In the year %d so far, you have used %.2lf worth of ingredients, and wasted %.2lf DKK worth of expired ingredients\n", current_year, money_spend_on_ingredients_current_year, expired_ingredients_current_year);

                        // Print/Inform the user that they...
                        printf("Last year you used %.2lf worth of ingredients, and wasted %.2lf DKK worth of ingredients\n\n", money_spend_on_ingredients_one_year_ago, expired_ingredients_one_year_ago);

                        // Prompt the user the option to return to statistics menu
                        printf("[R] Return to statistics menu\n");

                        // Check if the user wants to return to statistics menu
                        scanf(" %c", &sub_option_number);
                        if (sub_option_number == 'R' || sub_option_number == 'r') { // Sub option [4][3][R] --- RETURN TO STATISTICS MENU
                            space();

                            continue; // Continue to the top of the loop in order to return to statistics menu
                        } else {
                            printf("Invalid input, try again...\n"); // The user type an invalid character
                        }

                    } else if (sub_option_number == '4') { // Sub option [4][4] --- CHECK LIFETIME STATISTICS
                        space();

                        // Print lifetime statistics
                        printf("LIFETIME STATISTICS:\n");

                        // Print/Inform the user that they...
                        printf("So far you have used %.2lf DKK worth of ingredients in total, and you have wasted %.2lf DKK worth of expired ingredients!\n\n",
                                                     money_spend_on_ingredients_lifetime,                         expired_ingredients_lifetime);

                        // Prompt the user the option to return to statistics menu
                        printf("[R] Return to statistics menu\n");

                        // Check if the user wants to return to statistics menu
                        scanf(" %c", &sub_option_number);
                        if (sub_option_number == 'R' || sub_option_number == 'r') { // Sub option [4][4][R] --- RETURN TO STATISTICS MENU
                            space();

                            continue; // Continue to the top of the loop in order to return to statistics menu
                        } else {
                            printf("Invalid input, try again...\n"); // The user type an invalid character
                        }

                    } else if (sub_option_number == 'R' || sub_option_number =='r') { // Sub option [4][R] --- RETURN TO MAIN MENU
                        space();

                        break; // Break out of switch case '4' (STATISTICS) in order to return to the main menu
                    } else {
                        printf("Invalid input, try again...\n"); // The user didn't type '1', '2', '3', '4' or 'R'...
                    }
                }
                break;





            /*******************
            ***** SETTINGS *****
            *******************/
            case '5': // If the user picks '5' --- SETTINGS
                space();

                while (1) {
                    // Prompt the user the option to change amount of people in household or return to the main menu
                    printf("[1] Change amount of people in household\n"
                           "[R] Return to menu\n");

                    // Check for what sub option the user picked
                    scanf(" %c", &sub_option_number);

                    if (sub_option_number == '1') { // Sub option [5][1] --- CHANGE NUMBER OF PEOPLE IN HOUSEHOLD
                        space();

                        // Change the amount of people in house from the default value of '1' to something else
                        people_in_household = change_people_in_household(people_in_household);

                        space();
                    } else if (sub_option_number == 'R' || sub_option_number =='r') { // Sub option [5][R] --- RETURN TO MAIN MENU
                        break; // Break out of switch case '5' (SETTINGS) in order to return to the main menu
                    } else {
                        printf("Invalid input, try again...\n"); // The user didn't type '1' or 'R'...
                    }
                }
                break;





            /*******************
            ***** SETTINGS *****
            *******************/
            case '6': // If the user picks '6' --- EXIT
                printf("Exiting application...\n");
                exit(0);
        }
    }
}
#include <stdlib.h>

#include "../deserializer/deserializer.h"
#include "../time/time_and_date.h"

//
// Created by Marc Nygaard on 04/12/2023.
//

/**************************************************
***** USED PRICE week, month, year & lifetime *****
**************************************************/

double used_price(UsedIngredientsArray_t used_ingredients_array, int idx) {
    double qty = (double) used_ingredients_array.used_ingredients[idx].qty;
    double start_qty = (double) used_ingredients_array.used_ingredients[idx].start_qty;
    double price = (double) used_ingredients_array.used_ingredients[idx].price;

    return (qty / start_qty) * price;
};

double weekly_used_price(UsedIngredientsArray_t used_ingredients_array, int current_year, int current_week) {
    double total_week_used = 0.0;

    for(int i = 0; i < used_ingredients_array.count; i++) {
        int year = atoi(extract_year(used_ingredients_array.used_ingredients[i].expire_date));
        int week = used_ingredients_array.used_ingredients[i].week_of_year;
        if (week == 52 || week == 53 || week == 54 && atoi(extract_month(used_ingredients_array.used_ingredients[i].expire_date)) == 1){
            year = year - 1;

        }
        if (year == current_year) {
            if(week == current_week){
                total_week_used += used_price(used_ingredients_array, i);
            }
        }
    }
    return total_week_used;
}

double monthly_used_price(UsedIngredientsArray_t used_ingredients_array, int current_year, int current_month) {
    double total_monthly_used = 0.0;
    for (int i = 0; i < used_ingredients_array.count; i++) {
        int year = atoi(extract_year(used_ingredients_array.used_ingredients[i].expire_date));
        if (year == current_year) {
            int month = atoi(extract_month(used_ingredients_array.used_ingredients[i].expire_date));
            if (month == current_month) {
                total_monthly_used += used_price(used_ingredients_array, i);
            }
        }
    }
    return total_monthly_used;
}

double yearly_used_price(UsedIngredientsArray_t used_ingredients_array, int current_year) {
    double total_yearly_used = 0.0;

    for (int i = 0; i < used_ingredients_array.count; i++) {
        int year = atoi(extract_year(used_ingredients_array.used_ingredients[i].expire_date));
        if (year == current_year) {
            total_yearly_used += used_price(used_ingredients_array, i);
        }
    }
    return total_yearly_used;
}

double lifetime_used_price(UsedIngredientsArray_t used_ingredients_array) {
    double total_lifetime_used = 0.0;

    for (int i = 0; i<used_ingredients_array.count;i++) {
        total_lifetime_used += used_price(used_ingredients_array, i);
    }
    return total_lifetime_used;
};





/************************************************************************************
***** EXPIRED priceLeft, weeklyStats, monthlyStats, yearlyStats & lifetimeStats *****
************************************************************************************/

double expired_price_left(StatsArray_t stats_array, int idx) {
    double qty = (double)stats_array.stats[idx].qty;
    double start_qty = (double)stats_array.stats[idx].start_qty;
    double price = (double)stats_array.stats[idx].price;

    return (qty / start_qty) * price;
}

double expired_weekly_stats(StatsArray_t stats_array, int current_year, int current_week) {
    double total_weekly_waste = 0.0;

    for (int i = 0; i <stats_array.count; i++) {
        int year = atoi(extract_year(stats_array.stats[i].expire_date));
        int week = stats_array.stats[i].week;
        if (week == 52 || week == 53 || week == 54 && atoi(extract_month(stats_array.stats[i].expire_date)) == 1) {
            year = year - 1;
        }
        if (year == current_year) {
            if (week == current_week) {
                total_weekly_waste += expired_price_left(stats_array, i);
            }
        }
    }
    return total_weekly_waste;
}

double expired_monthly_stats(StatsArray_t stats_array, int current_year, int current_month) {
    double total_month_waste = 0.0;

    for (int i = 0; i < stats_array.count; i++) {
        int year = atoi(extract_year(stats_array.stats[i].expire_date));
        if (year == current_year) {
            int month = atoi(extract_month(stats_array.stats[i].expire_date));
            if (month == current_month) {
                total_month_waste += expired_price_left(stats_array, i);
            }
        }
    }
    return total_month_waste;
}

double expired_yearly_stats(StatsArray_t stats_array, int current_year) {
    double total_yearly_waste = 0.0;

    for (int i = 0; i < stats_array.count; i++) {
        int year = atoi(extract_year(stats_array.stats[i].expire_date));
        if (year == current_year) {
            total_yearly_waste += expired_price_left(stats_array, i);
        }
    }
    return total_yearly_waste;
}

double expired_lifetime_stats(StatsArray_t stats_array) {
    double total_life_waste = 0.0;

    for (int i = 0; i < stats_array.count; i++) {
        total_life_waste += expired_price_left(stats_array, i);
    }
    return total_life_waste;
}
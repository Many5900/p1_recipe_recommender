#include <stdlib.h>

#include "../deserializer/deserializer.h"
#include "../time/time_and_date.h"

//
// Created by Marc Nygaard on 04/12/2023.
//

/**************************************************
***** USED PRICE week, month, year & lifetime *****
**************************************************/

double used_price(UsedItemsArray_t usedItemsArray, int idx) {
    double qty = (double) usedItemsArray.used_item[idx].qty;
    double start_qty = (double) usedItemsArray.used_item[idx].start_qty;
    double price = (double) usedItemsArray.used_item[idx].price;

    return (qty / start_qty) * price;
};

double weekly_used_price(UsedItemsArray_t usedItemsArray, int current_year, int current_week) {
    double total_week_used = 0.0;

    for(int i = 0; i < usedItemsArray.count; i++) {
        int year = atoi(extract_year(usedItemsArray.used_item[i].expire_date));
        int week = usedItemsArray.used_item[i].week_of_year;
        if (week == 52 || week == 53 || week == 54 && atoi(extract_month(usedItemsArray.used_item[i].expire_date)) == 1){
            year = year - 1;

        }
        if (year == current_year) {
            if(week == current_week){
                total_week_used += used_price(usedItemsArray, i);
            }
        }
    }
    return total_week_used;
}

double monthly_used_price(UsedItemsArray_t usedItemsArray, int current_year, int current_month) {
    double total_monthly_used = 0.0;
    for (int i = 0; i < usedItemsArray.count; i++) {
        int year = atoi(extract_year(usedItemsArray.used_item[i].expire_date));
        if (year == current_year) {
            int month = atoi(extract_month(usedItemsArray.used_item[i].expire_date));
            if (month == current_month) {
                total_monthly_used += used_price(usedItemsArray, i);
            }
        }
    }
    return total_monthly_used;
}

double yearly_used_price(UsedItemsArray_t usedItemsArray, int current_year) {
    double total_yearly_used = 0.0;

    for (int i = 0; i < usedItemsArray.count; i++) {
        int year = atoi(extract_year(usedItemsArray.used_item[i].expire_date));
        if (year == current_year) {
            total_yearly_used += used_price(usedItemsArray, i);
        }
    }
    return total_yearly_used;
}

double lifetime_used_price(UsedItemsArray_t usedItemsArray) {
    double total_lifetime_used = 0.0;

    for (int i = 0; i<usedItemsArray.count;i++) {
        total_lifetime_used += used_price(usedItemsArray, i);
    }
    return total_lifetime_used;
};





/************************************************************************************
***** EXPIRED priceLeft, weeklyStats, monthlyStats, yearlyStats & lifetimeStats *****
************************************************************************************/

double expired_price_left(StatsArray_t statsArray, int idx) {
    double qty = (double)statsArray.stats[idx].qty;
    double start_qty = (double)statsArray.stats[idx].start_qty;
    double price = (double)statsArray.stats[idx].price;

    return (qty / start_qty) * price;
}

double expired_weekly_stats(StatsArray_t statsArray, int current_year, int current_week) {
    double total_weekly_waste = 0.0;

    for (int i = 0; i <statsArray.count; i++) {
        int year = atoi(extract_year(statsArray.stats[i].expire_date));
        int week = statsArray.stats[i].week;
        if (week == 52 || week == 53 || week == 54 && atoi(extract_month(statsArray.stats[i].expire_date)) == 1) {
            year = year - 1;
        }
        if (year == current_year) {
            if (week == current_week) {
                total_weekly_waste += expired_price_left(statsArray, i);
            }
        }
    }
    return total_weekly_waste;
}

double expired_monthly_stats(StatsArray_t statsArray, int current_year, int current_month) {
    double total_month_waste = 0.0;

    for (int i = 0; i < statsArray.count; i++) {
        int year = atoi(extract_year(statsArray.stats[i].expire_date));
        if (year == current_year) {
            int month = atoi(extract_month(statsArray.stats[i].expire_date));
            if (month == current_month) {
                total_month_waste += expired_price_left(statsArray, i);
            }
        }
    }
    return total_month_waste;
}

double expired_yearly_stats(StatsArray_t statsArray, int current_year) {
    double total_yearly_waste = 0.0;

    for (int i = 0; i < statsArray.count; i++) {
        int year = atoi(extract_year(statsArray.stats[i].expire_date));
        if (year == current_year) {
            total_yearly_waste += expired_price_left(statsArray, i);
        }
    }
    return total_yearly_waste;
}

double expired_lifetime_stats(StatsArray_t statsArray) {
    double total_life_waste = 0.0;

    for (int i = 0; i < statsArray.count; i++) {
        total_life_waste += expired_price_left(statsArray, i);
    }
    return total_life_waste;
}












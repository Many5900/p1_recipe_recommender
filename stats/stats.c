#include <stdlib.h>

#include "../deserializer/deserializer.h"
#include "../time/time_and_date.h"

//
// Created by Marc Nygaard on 04/12/2023.
//

/**************************************************
***** USED PRICE week, month, year & lifetime *****
**************************************************/

double UsedPrice(UsedItemsArray usedItemsArray, int idx) {
    double qty = (double) usedItemsArray.used_item[idx].qty;
    double start_qty = (double) usedItemsArray.used_item[idx].start_qty;
    double price = (double) usedItemsArray.used_item[idx].price;

    return (qty / start_qty) * price;
};

double WeekUsedPrice(UsedItemsArray usedItemsArray, int current_year, int current_week) {
    double total_week_used = 0.0;

    for(int i = 0; i < usedItemsArray.count; i++) {
        int year = atoi(extractYear(usedItemsArray.used_item[i].expire_date));
        int week = usedItemsArray.used_item[i].week_of_year;
        if (week == 52 || week == 53 || week == 54 && atoi(extractMonth(usedItemsArray.used_item[i].expire_date)) == 1){
            year = year - 1;

        }
        if (year == current_year) {
            if(week == current_week){
                total_week_used += UsedPrice(usedItemsArray, i);
            }
        }
    }
    return total_week_used;
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

double LifetimeUsedPrice(UsedItemsArray usedItemsArray) {
    double total_lifetime_used = 0.0;

    for (int i = 0; i<usedItemsArray.count;i++) {
        total_lifetime_used += UsedPrice(usedItemsArray, i);
    }
    return total_lifetime_used;
};





/************************************************************************************
***** EXPIRED priceLeft, weeklyStats, monthlyStats, yearlyStats & lifetimeStats *****
************************************************************************************/

double ExpiredPriceLeft(StatsArray statsArray, int idx) {
    double qty = (double)statsArray.stats[idx].qty;
    double start_qty = (double)statsArray.stats[idx].start_qty;
    double price = (double)statsArray.stats[idx].price;

    return (qty / start_qty) * price;
}

double ExpiredWeeklyStats(StatsArray statsArray, int current_year, int current_week) {
    double total_weekly_waste = 0.0;

    for (int i = 0; i <statsArray.count; i++) {
        int year = atoi(extractYear(statsArray.stats[i].expire_date));
        int week = statsArray.stats[i].week;
        if (week == 52 || week == 53 || week == 54 && atoi(extractMonth(statsArray.stats[i].expire_date)) == 1) {
            year = year - 1;
        }
        if (year == current_year) {
            if (week == current_week) {
                total_weekly_waste += ExpiredPriceLeft(statsArray, i);
            }
        }
    }
    return total_weekly_waste;
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

double ExpiredLifetimeStats(StatsArray statsArray) {
    double total_life_waste = 0.0;

    for (int i = 0; i < statsArray.count; i++) {
        total_life_waste += ExpiredPriceLeft(statsArray, i);
    }
    return total_life_waste;
}












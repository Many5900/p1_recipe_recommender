//
// Created by Marc Nygaard on 04/12/2023.
//
#include "../deserializer/deserializer.h"

#ifndef P1_RECIPE_RECOMMENDER_STATS_H
#define P1_RECIPE_RECOMMENDER_STATS_H

/**************************************************
***** USED PRICE week, month, year & lifetime *****
**************************************************/

double UsedPrice(UsedItemsArray usedItemsArray, int idx);
double WeekUsedPrice(UsedItemsArray usedItemsArray, int current_year, int current_week);
double MonthlyUsedPrice(UsedItemsArray usedItemsArray, int current_year, int current_month);
double YearlyUsedPrice(UsedItemsArray usedItemsArray, int current_year);
double LifetimeUsedPrice(UsedItemsArray usedItemsArray);

/************************************************************************************
***** EXPIRED priceLeft, weeklyStats, monthlyStats, yearlyStats & lifetimeStats *****
************************************************************************************/

double ExpiredPriceLeft(StatsArray statsArray, int idx);
double ExpiredWeeklyStats(StatsArray statsArray, int current_year, int current_week);
double ExpiredMonthlyStats(StatsArray statsArray, int current_year, int current_month);
double ExpiredYearlyStats(StatsArray statsArray, int current_year);
double ExpiredLifetimeStats(StatsArray statsArray);

#endif //P1_RECIPE_RECOMMENDER_STATS_H

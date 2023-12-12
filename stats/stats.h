//
// Created by Marc Nygaard on 04/12/2023.
//
#include "../deserializer/deserializer.h"

#ifndef P1_RECIPE_RECOMMENDER_STATS_H
#define P1_RECIPE_RECOMMENDER_STATS_H

/**************************************************
***** USED PRICE week, month, year & lifetime *****
**************************************************/

double used_price(UsedItemsArray_t usedItemsArray, int idx);
double weekly_used_price(UsedItemsArray_t usedItemsArray, int current_year, int current_week);
double monthly_used_price(UsedItemsArray_t usedItemsArray, int current_year, int current_month);
double yearly_used_price(UsedItemsArray_t usedItemsArray, int current_year);
double lifetime_used_price(UsedItemsArray_t usedItemsArray);

/*****************************************************************************************
***** EXPIRED price_left, weekly_stats, monthly_stats, yearly_stats & lifetime_stats *****
*****************************************************************************************/

double expired_price_left(StatsArray_t statsArray, int idx);
double expired_weekly_stats(StatsArray_t statsArray, int current_year, int current_week);
double expired_monthly_stats(StatsArray_t statsArray, int current_year, int current_month);
double expired_yearly_stats(StatsArray_t statsArray, int current_year);
double expired_lifetime_stats(StatsArray_t statsArray);

#endif //P1_RECIPE_RECOMMENDER_STATS_H

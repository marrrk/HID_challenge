#ifndef __MATCHER_H
#define __MATCHER_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

//constants
#define SAMPLE_SIZE 20
#define DB_SIZE 1000000

typedef enum {
    COLUMN_1,
    COLUMN_2,
} sample_csv_columns_t;


// Structure Declarations
typedef struct {
    float x;
    float y;

} minutia_t;


typedef struct {
    uint32_t id;
    minutia_t minutia[5];

} sample_t;


typedef struct {
    int match_id;
    int minutia_match;
    float distance_to_minutia;
} result_t;

minutia_t samples[SAMPLE_SIZE];
sample_t db_minutiae[DB_SIZE];
sample_t db2_minutiae[DB_SIZE];
result_t result;


//Function Declarations

/**
 * @brief Loads and stores data from the database 2 file.
 * Utilizes db2_minutiae array to hold the data read
 * 
 * @return 0 if successful
 */
int load_data(void);


/**
 * @brief Loads and stores the sample data from the sample file.
 * Utilizes samples array to hold the data
 * 
 * @return 0 if successful
 */
int load_samples(void);


/**
 * @brief For each sample, searches through database elements to find
 * distance between each minutiae and the sample.
 * outputs the closest minutia when the search is completed
 * 
 */
void search_through(void);


/**
 * @brief Calculates the distance between two points.
 * Implements formula D = ((x-x1)^2 + (y-y1)^2)^0.5
 * 
 * @param point_1 Sample point, x & y
 * @param point_2 Database point, x1 & y1
 * @return float: distance between the two input points
 */
float find_distance(minutia_t point_1, minutia_t point_2);


#endif
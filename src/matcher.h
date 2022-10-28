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
#define SAMPLE_SIZE 19
#define DB_SIZE 1000002

typedef enum {
    COLUMN_1,
    COLUMN_2,
    COLUMN_3,
    COLUMN_4,
    COLUMN_5,
    COLUMN_6,
    COLUMN_7,
    COLUMN_8,
    COLUMN_9,
    COLUMN_10,
    COLUMN_11
} csv_columns_t;

// Structure Definitions
typedef struct {
    float x;
    float y;

} minutia_t;



typedef struct {
    uint32_t id;
    minutia_t minutia[5];

} sample_t;




minutia_t samples[SAMPLE_SIZE];
sample_t db_minutiae[DB_SIZE];
sample_t db2_minutiae[DB_SIZE];


//Timing related vaiables
clock_t start_time, end_time;

//Function Declarations
int load_data(void);
void search_through(void);
float find_distance(minutia_t point_1, minutia_t point_2);


#endif
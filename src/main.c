#include <stdio.h>
#include <time.h>
#include "matcher.h"



int main(void){
    clock_t absolute_start = clock();
    if (load_data() == 1){
        printf("Error Loading Data\n");
        return 1;
    }

    clock_t search_start = clock();
    search_through();
    clock_t absolute_end = clock();


    int search_time = (absolute_end - search_start) * 1000/ CLOCKS_PER_SEC;
    printf("Time taken to search from db1: %.3fs\n", search_time/1000.0);

    int run_time = (absolute_end - absolute_start) * 1000/ CLOCKS_PER_SEC;
    printf("Total Runtime: %.3fs\n", run_time/1000.0);


    return 0;
}
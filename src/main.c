#include <stdio.h>
#include <time.h>
#include "timer.h"
#include "matcher.h"

int main(void){
    tic();
    clock_t absolute_start = clock();
    if (load_samples() == 1){
        printf("Error Loading Sample Data\n");
        return 1;
    }

    clock_t start_loading = clock();
    if (load_data() == 1){
        printf("Error Loading Database Data\n");
        return 1;
    }
    clock_t stop_loading = clock();


    printf("\n\nTime taken to load db2: %.3fs\n", toc());

    printf("\n-=Results=-\n");
    tic();
    clock_t search_start = clock();
    //search_through();
    search_through_threaded();
    clock_t absolute_end = clock();
    printf("-======-\n");
    printf("\n\nTime taken to search through db2: %.3fs\n", toc());



    printf("\n\n");
    int load_time = (stop_loading - start_loading) * 1000/ CLOCKS_PER_SEC;
    //printf("Time taken to load db2: %.3fs\n", load_time/1000.0);

    int search_time = (absolute_end - search_start) * 1000/ CLOCKS_PER_SEC;
    //printf("Time taken to search through db2: %.3fs\n", search_time/1000.0);

    int run_time = (absolute_end - absolute_start) * 1000/ CLOCKS_PER_SEC;
    //printf("Total Runtime: %.3fs\n", run_time/1000.0);

    
    //printf("Total Runtime: %.3fs\n", toc());

    return 0;
}
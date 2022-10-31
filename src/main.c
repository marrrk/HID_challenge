#include <stdio.h>
#include "timer.h"
#include "matcher.h"

int main(void){
    tic();
    if (load_samples() == 1){
        printf("Error Loading Sample Data\n");
        return 1;
    }

    if (load_data() == 1){
        printf("Error Loading Database Data\n");
        return 1;
    }
    double load_time = toc();
    printf("\n\nTime taken to load db2: %.3fs\n", toc());

    printf("\n-=Results=-\n");
    tic();
    //search_through();
    search_through_threaded();
    double search_time = toc();
    printf("-======-\n");
    printf("\n\nTime taken to search through db2: %.3fs\n", search_time);

    printf("Total Runtime: %.3fs\n", load_time + search_time);

    return 0;
}
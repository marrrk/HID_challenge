#include "matcher.h"

pthread_mutex_t Mutex = PTHREAD_MUTEX_INITIALIZER;

int load_samples(void){
    FILE *sample_file = fopen("samples.csv", "r");
    int sample_index = -1;  //start from -1 because it will still increment when the title row is read
    int sample_row = 0;     // row of sample file
    sample_csv_columns_t sample_column;

    if (sample_file == NULL) {
        printf("Could not open Sample File");
        return 1;
    }

    char buffer[30];

    // Reading Sample file
    while (fgets(buffer, 30, sample_file)){
        sample_column = COLUMN_1;
        sample_row++;

        char *token = strtok(buffer, ";");
        while(token){
            if (sample_row != 1) {                                  // Check to not include the title row, x;y
                float n = atof(token);                              //converts string to floating point number

                switch (sample_column){
                case COLUMN_1:                                      // column with x values
                    samples[sample_index].minutia[0].x = n;
                    samples[sample_index].id = sample_index;
                    break;
                case COLUMN_2:                                      // column with y values
                    samples[sample_index].minutia[0].y = n;
                    break;                    
                }
            }
            token=strtok(NULL,";");
            sample_column++;
        }
        sample_index++;            
    }
    
    fclose(sample_file);
    
    return 0;

}

int load_data(void){
    FILE *db2_file = fopen("db2.csv", "r");

    int db2_index = -1;                     //index of database array. start from -1 because it will still increment when the title row is read
    int db2_row = 0;                        // row of the database file
    int minutia_num = 0;                    // number of minutia

    if (db2_file == NULL) {
        printf("Could not open a file\n");
        return 1;
    } 
    
    char buffer[100];
    
    // Reading Database 2 File
    while(fgets(buffer, 100, db2_file)){
        int db2_column = 0;                         // column of database file
        db2_row++; 
        
        char *db2_token  = strtok(buffer, ";");

        while( db2_token ){            
            if (db2_row != 1){              // making sure not in title row
                float m = atof(db2_token);
                
                if (db2_column == 0) {                  // current column is ID
                    db2_minutiae[db2_index].id = (int)m;
                }

                if ((db2_column % 2 == 0) && (db2_column != 0) ){                // check if in a current y column, exclude ID column
                    db2_minutiae[db2_index].minutia[minutia_num].y = m;
                    if (minutia_num == 4) {                             // need to move to next minutia since in y column
                        minutia_num = 0;
                    } else {
                        minutia_num++;
                    }
                } else {
                    db2_minutiae[db2_index].minutia[minutia_num].x = m;
                }

            }

            db2_token =strtok(NULL,";");
            db2_column++;                            // moving to the next column of csv
        }
        db2_index++;
    }
    
    fclose(db2_file);  
    return 0;
}



void *thread_func(void *vargp){ //should take the sample & sample number
        sample_t sample = *((sample_t *) vargp);
        results[sample.id].distance_to_minutia = 100;
        
        for (int j =0; j<DB_SIZE; j++){                    // iterating through the database
            for (int k = 0; k<5; k++){                     // iterating through each minutia
                float temp_d = find_distance(sample.minutia[0], db2_minutiae[j].minutia[k]);                  
                if (temp_d < results[sample.id].distance_to_minutia){               //check if calculated distance closer than  what is stored 
                        results[sample.id].distance_to_minutia = temp_d;
                        results[sample.id].match_id = db2_minutiae[j].id;
                        results[sample.id].minutia_match = k;
                }
            }
        }
    return NULL;
}


void search_through_threaded(void){
    pthread_t threads[THREAD_COUNT];

    for (int i = 0 ; i < THREAD_COUNT; i++){
        pthread_create(threads+i, NULL, &thread_func, &samples[i]);
    }


    for(int j = 0; j < THREAD_COUNT; j++){ 
        if(pthread_join(threads[j], 0)){
            pthread_mutex_lock(&Mutex);
            printf("Problem joining thread %d\n", j);
            pthread_mutex_unlock(&Mutex);
        }
    }

    for (int i = 0; i<SAMPLE_SIZE; i++){
        printf("Sample %d, closest match ID: %d minutia %d at distance %.4f\n", samples[i].id, results[i].match_id, results[i].minutia_match, results[i].distance_to_minutia);
    }

}

void search_through(void){
    for (int i = 0; i<SAMPLE_SIZE; i++){                   //iterating through each sample
        result.distance_to_minutia = 100;                  //set distance to maximum
        for (int j =0; j<DB_SIZE; j++){                    // iterating through the database
            for (int k = 0; k<5; k++){                     // iterating through each minutia

                float temp_d = find_distance(samples[i].minutia[0], db2_minutiae[j].minutia[k]);                  
                if (temp_d < result.distance_to_minutia){               //check if calculated distance closer than  what is stored 
                        result.distance_to_minutia = temp_d;
                        result.match_id = db2_minutiae[j].id;
                        result.minutia_match = k;
                }
            }

        }
        //Output result of current sample
        printf("Sample %d, closest match ID: %d minutia %d at distance %.4f\n", i, result.match_id, result.minutia_match, result.distance_to_minutia);
    }
}


float find_distance(minutia_t point_1, minutia_t point_2){
    float distance = (float)pow((point_1.x - point_2.x), 2)+ pow((point_1.y - point_2.y), 2);
    return (float)sqrt(distance);
}
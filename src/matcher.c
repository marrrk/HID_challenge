#include "matcher.h"

int load_data(void){
    FILE *sample_file = fopen("samples.csv", "r");
    FILE *database_file = fopen("db.csv", "r");
    FILE *db2_file = fopen("db2.csv", "r");

    

    int sample_index = -1;
    int db_index = -1; //start from -1 because the incrementation will still occur when the title row will be read
    int db2_index = -1;
    int sample_row, db_row, db2_row = 0;
    int db_column, db2_column = 0;
    csv_columns_t sample_column;
    int minutia_num = 0;

    if ((sample_file == NULL) || (database_file == NULL) || (db2_file == NULL) ){
        printf("Could not open a file\n");
        return 1;
    } else {
        char buffer[100];
        
        // Reading Sample file
        while (fgets(buffer, 30, sample_file)){
            //now allocate data to specific sample section

            sample_column = COLUMN_1;
            sample_row++;

            char *token = strtok(buffer, ";");
            while(token){
                if (sample_row != 1) { // Check to not include the title row, x;y
                    float n = atof(token); //converts string to floating point number
                    /*
                    if (sample_column == 0){       //storing x value
                        samples[sample_index].x = n;
                        //printf("memory_value: %.4f , file_value: %.4f\n", samples[sample_index].minutia.x1, n);
                    } 
                    else if (sample_column == 1){  //storing y value
                        samples[sample_index].y = n;                        
                    }
                    */

                   switch (sample_column){
                    case COLUMN_1:
                        samples[sample_index].x = n;
                        sample_column = COLUMN_2;
                    case COLUMN_2:
                        samples[sample_index].y = n;         
                    default:
                        break;               
                   }
                    //printf("%.4f\n", n);
                }
                token=strtok(NULL,";");
            }
            sample_index++;            
        }
        

       
        for (int i = 0; i<SAMPLE_SIZE; i++) {
            printf("%.4f   :   %.4f\n", samples[i].x, samples[i].y);
       }
        


        start_time = clock();

        // Reading Database File
        while(fgets(buffer, 30, database_file)){

            db_column = 0;
            db_row++;
            
            char *db_token  = strtok(buffer, ";");

            while( db_token ){
                //db_minutiae = malloc(sizeof(sample_t) * db_row);
                
                if (db_row > 1){
                    float m = atof(db_token);

                    if (db_column == 0) {
                        int id = atoi(db_token);
                        db_minutiae[db_index].id = id;
                    }
                    else if (db_column == 1) {
                        db_minutiae[db_index].minutia[0].x = m;
                    }
                    else if (db_column == 2) {
                        db_minutiae[db_index].minutia[0].y = m;
                    }                   
                    //printf("%.4f\n", m);

                }
                db_token =strtok(NULL,";");
                db_column++;
            }
            db_index++;
        }
        

        
        // Reading Database 2 File
        while(fgets(buffer, 100, db2_file)){

            db2_column = 0;
            db2_row++;
            
            char *db2_token  = strtok(buffer, ";");

            while( db2_token ){
                //db2_minutiae = malloc(sizeof(sample_t) * db2_row);
                
                if (db2_row > 1){
                    float m = atof(db2_token);

                    if (db2_column == 0) {
                        int id = atoi(db2_token);
                        db2_minutiae[db2_index].id = id;
                    }
                    else if (db2_column == 1) {
                        db2_minutiae[db2_index].minutia[minutia_num].x = m;
                    }
                    else if (db2_column == 2) {
                        db2_minutiae[db2_index].minutia[minutia_num].y = m;
                    }                   
                    else if (db2_column == 3) {
                        db2_minutiae[db2_index].minutia[minutia_num].x = m;
                    }
                    else if (db2_column == 4) {
                        db2_minutiae[db2_index].minutia[minutia_num].y = m;
                    }
                    else if (db2_column == 5) {
                        db2_minutiae[db2_index].minutia[minutia_num].x = m;
                    }
                    else if (db2_column == 6) {
                        db2_minutiae[db2_index].minutia[minutia_num].y = m;
                    }
                    else if (db2_column == 7) {
                        db2_minutiae[db2_index].minutia[minutia_num].x = m;
                    }
                    else if (db2_column == 8) {
                        db2_minutiae[db2_index].minutia[minutia_num].y = m;
                    }
                    else if (db2_column == 9) {
                        db2_minutiae[db2_index].minutia[minutia_num].x = m;
                    }
                    else if (db2_column == 10) {
                        db2_minutiae[db2_index].minutia[minutia_num].y = m;
                    }
                }
                db2_token =strtok(NULL,";");

                if ((db2_column % 2 == 0) && (db2_column !=0) ) {
                    if (minutia_num == 4){
                        minutia_num = 0;
                    } else {
                        minutia_num++;
                    }
                }
                db2_column++;


            }
            db2_index++;
        }
        end_time = clock();
        
        
    }

    
    fclose(sample_file);
    fclose(database_file);  

    int load_time = (end_time - start_time) * 1000/ CLOCKS_PER_SEC;

    printf("Time taken to load data from db1: %dms\n", load_time);
    for (int i = 0; i<=DB_SIZE; i++) {
        //printf("%d    :   %.4f   :   %.4f    :   %.4f   :   %.4f    :   %.4f   :   %.4f    :   %.4f   :   %.4f    :   %.4f   :   %.4f\n",
        //db2_minutiae[i].id, db2_minutiae[i].minutia[0].x, db2_minutiae[i].minutia[0].y,
        //                    db2_minutiae[i].minutia[1].x, db2_minutiae[i].minutia[1].y,
        //                    db2_minutiae[i].minutia[2].x, db2_minutiae[i].minutia[2].y,
        //                    db2_minutiae[i].minutia[3].x, db2_minutiae[i].minutia[3].y,
        //                    db2_minutiae[i].minutia[4].x, db2_minutiae[i].minutia[4].y
        //                     );
    }

    for (int i = 0; i<=DB_SIZE; i++) {
        //printf("%d  :   %.4f   :   %.4f\n",db_minutiae[i].id, db_minutiae[i].minutia[0].x, db_minutiae[i].minutia[0].y);
    }

    return 0;
}

void search_through(void){
    float d = 100;

    for (register i = 0; i<SAMPLE_SIZE; i++){
        register found_id, minutia_num;


        for (register j =0; j<DB_SIZE; j++){

            for (register k = 0; k<5; k++){

                float temp_d = find_distance(samples[i], db2_minutiae[j].minutia[k]);

                if (temp_d < d){
                        d = temp_d;
                        found_id = db_minutiae[j].id;
                        minutia_num = k;
                }

            }

        }
        printf("Sample %d, closest match ID: %d minutia %d at distance %.4f\n", i, found_id, minutia_num, d);
        d = 100;
    }

}


float find_distance(minutia_t point_1, minutia_t point_2){
    double distance;
    distance = pow((point_1.x - point_2.x), 2)+ pow((point_1.y - point_2.y), 2);
    return (float)sqrt(distance);

}
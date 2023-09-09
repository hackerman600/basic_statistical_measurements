#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int** createIntArray(){
        FILE *filepointer;
        char catchr[100];
        int pre_out[8][4];
        int** out = (int**)malloc(8 * sizeof(int*) * 4);
        int row_itter = -1;
        int col_itter = 0;

        filepointer = fopen("/home/kali/Desktop/machine_learning/anomaly_detection/easy.csv","r");
        if (filepointer == NULL){
            perror("Error opening file");
            
        }

        while(fgets(catchr, sizeof(catchr), filepointer)){
            char *tok = strtok(catchr,",");
            //printf("%s,%s", tok,"\n");
            while (tok != NULL){
                if (strlen(tok) > 0){
                    //printf("tok = %s,%d,%d,%s", tok, row_itter, col_itter,"\n");
                } 

                if (row_itter >= 0){
                    pre_out[row_itter][col_itter] = atoi(tok);
                    col_itter += 1;
                }
                
                tok = strtok(NULL,",");
                
            }
            row_itter += 1;
            col_itter = 0;
        } 

        //check if the data as imported correctly
        printf("\n------------ dataset ------------\n");
        printf("\ngender,weight,height,loves pizza\n\n");
        for (int r = 0; r < 8; r++){
            out[r] = (int*)malloc(sizeof(int) * 4);
            for (int c = 0; c < 4; c++){
                out[r][c] = pre_out[r][c];
                printf("%d,%s",out[r][c],"     ");
            }
            printf("%s","\n");
        }

        printf("\n------------------------------\n");

        return out;

}


double** calculate_means(int** result){
    double** outme = (double**)malloc(sizeof(double*)*4);
    for (int c = 0; c < 4; c++){
        double* inout = (double*)malloc(sizeof(double)*4);
        outme[c] = inout;
        double catchr = 0.0;
        for (int r = 0; r < 8; r++){
            catchr += result[r][c];    
        }
        
        if (c == 0 || c == 3){
                double result = catchr/8;
                if (result < 0.5){
                    outme[c][0] = 0.0;
                } else{
                    outme[c][0] = 1.0;
                }
        } else {
             outme[c][0] = catchr/8;
        }       
       
    }

    return outme;
 
}


struct KeyValuePair {
    char type[50];
    char key[50];
    double value;
};


int main(){
    int** result = createIntArray();
    double** means = calculate_means(result);
    char columns[50][50] = {"gender", "weight", "height", "loves pizza"};
    struct KeyValuePair kvarr[4];
    
    printf("\n\n--------------means and modes:-------------- \n\n");
    for (int m = 0; m < 4; m++){
        char* col = columns[m];
        if (m == 0 || m == 3){
            strcpy(kvarr[m].type,"mode:");
        } else {
            strcpy(kvarr[m].type,"median:");
        } 
        
        strcpy(kvarr[m].key,col);
        kvarr[m].value = means[m][0]; 

        printf("%s,%s,%s,%s,%f,%s",kvarr[m].type,"        ",kvarr[m].key,"        ",kvarr[m].value,"\n");

    }

    printf("\n---------------------------------------------- \n\n");

    return 0;
}


















/*int main() {
    FILE *filePointer;
    char line_buffer[10000]; // Adjust the buffer size as needed
    char delimiter = ','; // CSV delimiter
    double *storevals[1000000] = {}; //can not store 47.04 mill in 1. 1 mill max on stack
    int itter = 0; 

    filePointer = fopen("/home/kali/Desktop/machine_learning/neural_networks/from_scratch/cpp_networks/x_train.csv", "r");
    if (filePointer == NULL) {
        perror("Error opening file");
        return 1;
    }

    while (fgets(line_buffer, sizeof(line_buffer), filePointer) != NULL) {
        // Tokenize the line based on the delimiter
        char *token = strtok(line_buffer, ",");
        while (token != NULL) {
            // Process each token and store it in storevals
            if (strlen(token) > 1) {
                double val = strtod(token,NULL); 
                //printf("val = %f",val);
                storevals[itter] = val;
                itter += 1;
            }

            if (itter == 999999){
                printf("999999 = %f\n", storevals[3000]);
                printf("%d\n", sizeof(storevals));
                return 0;
            }

            // Get the next token
            token = strtok(NULL, ",");


        }
    }

    fclose(filePointer);

    // Print the first value from storevals
    printf("%.2lf\n", sizeof(storevals));
  

    return 0;
}*/


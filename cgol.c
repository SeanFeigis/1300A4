#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define ROWS 20
#define COL 40

int main ( int argc, char *argv[] ) {
    FILE *f1;
    char filename[20];
    char letter;
    int x,y,i,j,k,l,m,end;
    int neighbours = 0;
    char currentGrid[ROWS][COL];
    
    char iterations[100];
    int intIterations;
    int currentIteration = 0;
    char userIn[1];

    int choice = 0;

    int intCurrentGrid[ROWS][COL];
    int nextGen[ROWS][COL];




    if(argv[2] != NULL) {
        strcpy(iterations, argv[2]);
    } else {
        strcpy(iterations, "50");
    }
    for (i = 0; i < strlen(iterations)-2; i++) {
        if (iterations[i] > '0' && iterations[i] > '9' ) {
            printf("Invald argument for iterations: %s\n",iterations);
            exit(0);
        }
    }
    intIterations = atoi(iterations);

    strcpy(filename, argv[1]);
    /*  open the file for reading */
    f1 = fopen(filename, "r");
    if (f1 == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
    x=0;
    y=0;

    while (letter != EOF){ 
        letter = fgetc(f1);
        if (letter == '0' || letter == '1'){
            currentGrid[x][y] = letter;
            y++;
        }
    }

    fclose(f1);

    /*

    for (y = 0; y < ROWS; y++) {
        printf("|");
        for (x = 0; x < COL; x++){
            printf("%c",currentGrid[y][x]);
        }
        printf("|\n");
    }

    */
                
    for (y = 0; y < ROWS; y++) {
        for (x = 0; x < COL; x++){
            /*
            printf("x: %d, y: %d\n", x,y);
            printf("%d\n", intCurrentGrid[y][x]);
            printf("%c\n", currentGrid[y][x]);
            */

            intCurrentGrid[y][x] = (currentGrid[y][x] - '0');
            
        }
    }

    printf("Initial Seed(Gen 0)\n");
    printf("-----------------------------------------\n");
    for (y = 0; y < ROWS; y++) {
        printf("|");
        for (x = 0; x < COL; x++){
            if (intCurrentGrid[y][x] == 1) {
                printf("X");
            } else {
                printf(" ");
            }
        }
        printf("|\n");
    }
    printf("-----------------------------------------\n");
    
    
    
    printf("\nWould you like to start?\n");
    fflush(stdin);

    i = 1;
    while (i != 0) {
        if (fgets(userIn, 500, stdin) != NULL) {
            userIn[1] = '\0';
            if (strcmp(userIn, "Y") == 0 || strcmp(userIn, "y") == 0 ) {
                choice = 1;
                i = 0;
            } else if (strcmp(userIn, "N") == 0 || strcmp(userIn, "n") == 0 ) {
                choice = 0;
                exit(0);
            } else {
                printf("Please enter a valid option\n");
                i = 1;
            }
        }
    }


    while (choice != 0 ) {

        for(m = 0; m < intIterations; m ++) {
            currentIteration ++;

            for (y = 0; y < ROWS; y++) {
                for (x = 0; x < COL; x++){
                    nextGen[y][x] = 0;
                }
            }

            for (i = 0; i < ROWS ; i ++ ) {
                for (j = 0; j < COL ; j++) {
                    neighbours = 0;
                    for (k = -1; k <=1; k++ ) {
                        for (l = -1; l <=1; l++) {

                            if ((i+k) > -1 && (i + k) < 19 && (j + l) > -1 && (j + l) < 39 ) {
                                neighbours += intCurrentGrid[i+k][j+l];
                            }
                               
                            if (neighbours > 8 || neighbours < 0) {
                                printf("y:%d  x:%d  neighbours: %d\n",(i+k), (j+l) ,neighbours);

                            }

                            }          
                        }

                    neighbours -= intCurrentGrid[i][j];
                    
                    if (intCurrentGrid[i][j] == 1 && neighbours < 2) {
                        nextGen[i][j] = 0;
                    } else if (intCurrentGrid[i][j] == 1 && neighbours > 3) {
                        nextGen[i][j] = 0;
                    } else if (intCurrentGrid[i][j] == 0 && neighbours == 3) {
                        nextGen[i][j] = 1;
                    } else {
                        nextGen[i][j] = intCurrentGrid[i][j];
                    }


                }

            }

            /*
            for (i = 34; i < 40; i++) {
            printf("value of last 6 digits in the bottom(nextgen): %d\n",nextGen[y][x]);
            }
            */
            end = 0;
            for (y = 0; y < ROWS; y++) {
                for (x = 0; x < COL; x++){
                    if (intCurrentGrid[y][x] == nextGen[y][x]) {
                        end++;
                    }
                }
            }
            if (end == 800) {
                exit(0);
            }

            /*
            for (i = 34; i < 40; i++) {
            printf("value of last 6 digits in the bottom(currentgen): %d\n",intCurrentGrid[y][x]);
            }
            */

            for (y = 0; y < ROWS; y++) {
                for (x = 0; x < COL; x++){
                    intCurrentGrid[y][x] = nextGen[y][x];
                }
            }




            system("clear");


            printf("-----------------------------------------\n");
            for (y = 0; y < ROWS; y++) {
                printf("|");
                for (x = 0; x < COL; x++){
                    if (intCurrentGrid[y][x] == 1) {
                        printf("X");
                    } else {
                        printf(" ");
                    }
                }
                printf("|\n");
            }
            printf("-----------------------------------------%d\n",currentIteration);

            system( "sleep 0.25");


        }

        printf("Continue? (Y or N)\n");
        i = 1;
        while (i != 0) {
            fflush(stdin);
            if (fgets(userIn, 500, stdin) != NULL) {
                userIn[1] = '\0';
                if (strcmp(userIn, "Y") == 0 || strcmp(userIn, "y") == 0 ) {
                    choice = 1;
                    i = 0;  
                } else if (strcmp(userIn, "N") == 0 || strcmp(userIn, "n") == 0 ) {
                    choice = 0;
                    exit(0);
                } else {
                    printf("Please enter a valid option\n");
                    i = 1;
                }
            }
        }



    }
    
    

    return(0);
}




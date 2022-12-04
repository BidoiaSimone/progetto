/*scriverò il main bello con il menù, non lo includo nel file normale 
così non faccio confusione con le challenge se riusciamo a consegnarle*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#define MS                  1227.133
#define SPEED               10

void delay_milliseconds(int milliseconds);
void delay_seconds(int seconds);

void eraser_ds();
void eraser_sd();

int milliseconds_calculator();


int milliseconds_calculator(){
    int start = time(NULL);
    double clock_start = clock();
    while(time(NULL) <= start+1){}
    double clock_finish = clock();
    double clocks_in_one_sec = clock_finish - clock_start;
    double clocks_in_one_millisec = clocks_in_one_sec / 1000;
    return clocks_in_one_millisec;
}


void delay_milliseconds(int milliseconds){
    double start_time = clock();
    while(clock() <= start_time + (milliseconds * MS)){}
}

void delay_seconds(int seconds){
    int start_time = time(NULL);
    while(time(NULL) <= start_time + seconds){}
}

void eraser_ds(){
    for(int i = 0; i < 62; i++){
        for(int j = 0; j < i; j++){
           printf("\b"); 
        }
        delay_milliseconds(5);
        for(int j = 0; j < i; j++){
           printf(" "); 
        }
        fflush(stdout);
    }
    for(int i = 0; i < 62; i++){
        printf("\b");
    }
}

void eraser_sd(){
    for(int i = 0; i < 62; i++){
        printf("\b"); 
    }
    for(int i = 0; i < 62; i++){
        printf(" ");
        delay_milliseconds(5);
        fflush(stdout);
    }
}





int main(int argc, char * argv[]){

    char test[]="faccio quello che voglio vaffanbrodo non sbattermi la macchina";

    


    for(int i = 0; i < 62; i++){
        delay_milliseconds(SPEED);
        printf("%c", test[i]);
        fflush(stdout);
        
    }

    eraser_ds();

    for(int i = 0; i < 62; i++){
        delay_milliseconds(SPEED);
        printf("%c", test[i]);
        fflush(stdout);
    }
    eraser_sd();


    printf("\n");
    return 0;
}

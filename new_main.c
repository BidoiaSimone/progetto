/*scriverò il main bello con il menù, non lo includo nel file normale 
così non faccio confusione con le challenge se riusciamo a consegnarle*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int milliseconds_calculator();

#define MS                  milliseconds_calculator()

void delay_milliseconds(int milliseconds);
void delay_seconds(int seconds);

void eraser_ds();
void eraser_sd();


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
    for(int i = 0; i < 127; i++){
        for(int j = 0; j < i; j++){
           printf("\b"); 
        }
        delay_milliseconds(50);
        for(int j = 0; j < i; j++){
           printf(" "); 
        }
        fflush(stdout);
    }
    for(int i = 0; i < 127; i++){
        printf("\b");
    }
}

void eraser_sd(){
    for(int i = 0; i < 127; i++){
        printf("\b"); 
    }
    for(int i = 0; i < 127; i++){
        printf(" ");
        delay_milliseconds(50);
        fflush(stdout);
    }
}





int main(int argc, char * argv[]){

    char test[]="ho visto un nero con le scarpe di gomma, porcodio e porcamdonna, le scarpe di gomma le volevo anch'io, porcamadonna e porcodio";

    printf("%d", MS);
    printf("%d\n", milliseconds_calculator());
    delay_milliseconds(100);
    printf("%d\n", milliseconds_calculator());
    delay_milliseconds(10);
    printf("%d\n", milliseconds_calculator());

    printf("\n");
    return 0;
}

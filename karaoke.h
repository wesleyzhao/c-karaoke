/*
  karoake.h
  Created by Wesley Zhao
  
  Header file for hw4a.c's main
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define SINGER_NAME_SIZE 15
#define TITLE_SIZE       40
#define SONG_NUMBER_SIZE 12
#define NUMBER_OF_SINGERS 15
#define EVENT_ACTION_SIZE 6

typedef struct song
{ 
  char singer[SINGER_NAME_SIZE]; 
  char title[TITLE_SIZE]; 
  int sung;  /* whether or not the song has been sung -- 0 or 1 */
} SONG; 

typedef struct singer
{ 
  char name[SINGER_NAME_SIZE]; 
  int numSongs; 
  SONG* songs; 
} SINGER;

typedef struct event
{ 
  int eventTime;
  char singerName[SINGER_NAME_SIZE]; 
  char eventAction[EVENT_ACTION_SIZE];
} EVENT;

void processStuff(char *singerFileLoc, char *eventsFileLoc);
void loadSingers(char *singersFileLoc);
void printStuff();
void printEvent(EVENT event);
void printSinger(SINGER singer);
/*
void PrintFullTrain(CAR train[]);

void PrintCar (CAR car);

void PrintPrettyCarView(CAR car);
*/

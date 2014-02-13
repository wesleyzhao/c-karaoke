/*
  karoake.c
  Created by Wesley Zhao
  
  Defining function in karaoke.h for hw4a.c
 */

#include "karaoke.h"

#define START_TIME 1800
#define END_TIME 2230
#define TIME_INCREMENT 5

SINGER singers[NUMBER_OF_SINGERS];
EVENT *events;

int singersNum;
/************************/
/* function definitions */
/************************/
void processStuff(char *singersFileLoc, char *eventsFileLoc){
  FILE * eventsReader = fopen(eventsFileLoc, "r");
  loadSingers(singersFileLoc);
  loadEvents(eventsFileLoc);
  printStuff();
}

void printStuff(){
  /* print Singers */
  int singersIndex = 0;
  for(singersIndex=0;singersIndex<singersNum;singersIndex++){
    printSinger(singers[singersIndex]);
  }


  /* print Events */
  int curTime;
  int eventsIndex = 0;
  for(curTime=START_TIME;curTime<=END_TIME;curTime+=TIME_INCREMENT){
    printf("current time: %d\n", curTime);
    EVENT tempEvent = events[eventsIndex];
    while(tempEvent.eventTime == curTime){
      printEvent(tempEvent);
      eventsIndex++;
      tempEvent = events[eventsIndex];
    }
    
  }
}

void printEvent(EVENT event){
  printf("EVENT!\n");
  printf("time: %d\n", event.eventTime);
  printf("singer name: %s\n", event.singerName);
  printf("action: %s\n", event.eventAction);
}

void printSinger(SINGER singer){
  printf("SINGER!\n");
  printf("name: %s\n", singer.name);
  printf("numSongs: %d\n", singer.numSongs);
  printf("songs:\n");

  int in;
  for (in=0;in<(singer.numSongs);in++){
    SONG song = (singer.songs)[in];
    /* printf("%s\n", song.singer);*/
    printf("%s\n", song.title);
    /*printf("%d\n", song.sung);*/
  }

}

void loadSingers(char *singersFileLoc){
  FILE * singersReader = fopen(singersFileLoc, "r");
  char line[80];
  
  int curSingerIndex = 0;
  int curSongNum = 0;
  int curSongTotal = 0;
  int isLineSinger = 1;

  while (fscanf(singersReader, "%s", line) != EOF)
    {
      SINGER *tempSinger = &(singers[curSingerIndex]);
      if (isLineSinger){
	strcpy(tempSinger->name, line);	
	
	isLineSinger = 0;
	curSongNum = 0;
      }
      else if (curSongNum == 0){
	/* this means we are reading the number of songs we have  */
	curSongTotal = strtol(line, (char **)NULL, 10);
	curSongNum = 1;
	
	tempSinger->numSongs = curSongTotal;
	tempSinger->songs = (SONG *) malloc(curSongTotal*sizeof(SONG));
      }
      else if (curSongNum <= curSongTotal){
	SONG *tempSong = &(tempSinger->songs[curSongNum-1]);
	strcpy(tempSong->singer, tempSinger->name);
	strcpy(tempSong->title,line);
	tempSong->sung = 0;
	if (curSongNum == curSongTotal){
	  /* we are on the last song for the singer  */
	  /* the next line will be another singer */
	  isLineSinger = 1;
	  curSongTotal = 0;
	  curSongNum = 0;
	  curSingerIndex++;

	}
	
	curSongNum++;
      }
      /* printf("%s\n", line); */
    }/* end while loop */
  singersNum = curSingerIndex;
  fclose(singersReader);
  
}

void loadEvents(char *eventsFileLoc){
  FILE * eventsReader = fopen(eventsFileLoc, "r");
  char line[80];
  
  int curSingerIndex = 0;
  int curSongNum = 0;
  int curSongTotal = 0;
  int isLineSinger = 1;
  
  int eventsTotal;
  int curEventIndex = 0;

  int isEventsTotalLine = 1;
  int lineType = 1;
  /* lineType 1 is time, 2 is name, 3 is event */

  while (fscanf(eventsReader, "%s", line) != EOF)
    {
      
      if (isEventsTotalLine == 1){
	eventsTotal = strtol(line, (char **)NULL, 10);
	events = (EVENT *) malloc(eventsTotal*sizeof(EVENT));
	isEventsTotalLine = 0;
      }
      else {
	EVENT *tempEvent = &(events[curEventIndex]);
	switch(lineType){
	case 1:
	  tempEvent->eventTime = strtol(line, (char **)NULL, 10);
	  lineType++;
	  break;
	case 2:
	  strcpy(tempEvent->singerName, line);
	  lineType++;
	  break;
	case 3:
	  strcpy(tempEvent->eventAction, line);
	  lineType=1;
	  curEventIndex++;
	  break;
	}
      }
    }/* end while loop */
  fclose(eventsReader);  
}

/*
  karoake.c
  Created by Wesley Zhao
  
  Defining function in karaoke.h for hw4a.c
 */

#include "karaoke.h"
#include "linkedList.h"

#define START_TIME 1800
#define END_TIME 2330
#define TIME_INCREMENT 5
#define TOTAL_INCREMENT_POSSIBLE 67

EVENT *events;
SINGER tempSinger;
NODEPTR possibleSingersHead;
NODEPTR rotationSingersHead;
NODEPTR curSingerPtr;

char **songsSung[TOTAL_INCREMENT_POSSIBLE][TITLE_SIZE+1];
int seedNum;
int curSongIndex=0;

int singersNum;
/************************/
/* function definitions */
/************************/
void processStuff(char *singersFileLoc, char *eventsFileLoc, char *seedNumStr){
  seedNum = strtol(seedNumStr, (char **)NULL, 10);
  srand(seedNum);

  loadSingers(singersFileLoc);
  loadEvents(eventsFileLoc);
  printStuff();
}

void printStuff(){
  /* print Singers */

  /* print Events */
  int curTime;
  int eventsIndex = 0;
  for(curTime=START_TIME;curTime<END_TIME;curTime=IncrementTime(curTime)){
    EVENT tempEvent = events[eventsIndex];
    while(tempEvent.eventTime == curTime){
      processEvent(tempEvent);

      printEvent(tempEvent);
      eventsIndex++;
      tempEvent = events[eventsIndex];
    }
    makeSing(curTime);
    
  }
}

int IncrementTime(int time)
{
  /* increment time by five minutes */
  time += 5;

  /* if minutes are now 60 */
  if ((time % 100) == 60)
    {
      /* reset minutes to 0 and increment hour */
      time += 40;
    }
  return time;
}

void makeSing(eventTime){
  SINGER singer;
  SONG song;
  int randomNum;
  int songSung;

  if (rotationSingersHead != NULL){
    if (curSingerPtr == NULL){
      curSingerPtr = rotationSingersHead;
    }
    singer = curSingerPtr -> data;
    songSung = 1;
    int i;
    while(songSung == 1){
      songSung = 0;
      randomNum = getRandomNum(singer.numSongs);
      song = (singer.songs)[randomNum];

      for(i=0; i<TOTAL_INCREMENT_POSSIBLE; i++){
	if(strcmp(songsSung[i],song.title) == 0){
	  songSung = 1;
	}
      }
    }

    song.sung = 1;
    strcpy(songsSung[curSongIndex], song.title);
    curSongIndex+=1;
    
    printf("%d - %s sings \"%s\"\n", eventTime, singer.name, song.title);
    /*
    fprintf(stderr, "press anykey to conitnue\n");
    getchar(); 
    */
    rotateSingers();
  }
}

void processEvent(EVENT event){
  if (strcmp(event.eventAction, "ENTER") == 0){
    addSingerToRotation(event.singerName);
  }
  else if (strcmp(event.eventAction, "EXIT") == 0){
    removeSingerFromRotation(event.singerName);
  }
}

void addSingerToRotation(char *singerName){
  NODEPTR singerNode;
  singerNode = FindNode(&possibleSingersHead, singerName);
  Move(singerNode, &possibleSingersHead, &rotationSingersHead);
}

void removeSingerFromRotation(char *singerName){
  NODEPTR singerNode;
  singerNode = FindNode(&rotationSingersHead, singerName);
  if (singerNode != NULL){
    Move(singerNode, &rotationSingersHead, &possibleSingersHead);
  }
}

void rotateSingers(){
  curSingerPtr = curSingerPtr->next;
}

void printEvent(EVENT event){
  printf("%d - %s %s\n", event.eventTime, event.singerName, event.eventAction);
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
      if (isLineSinger){
	strcpy(tempSinger.name, line);	
	
	isLineSinger = 0;
	curSongNum = 0;
      }
      else if (curSongNum == 0){
	/* this means we are reading the number of songs we have  */
	curSongTotal = strtol(line, (char **)NULL, 10);
	curSongNum = 1;
	
	tempSinger.numSongs = curSongTotal;
	tempSinger.songs = (SONG *) malloc(curSongTotal*sizeof(SONG));
      }
      else if (curSongNum <= curSongTotal){
	SONG *tempSong = &((tempSinger.songs)[curSongNum-1]);
	strcpy(tempSong->singer, tempSinger.name);
	strcpy(tempSong->title,line);
	tempSong->sung = 0;
	if (curSongNum == curSongTotal){
	  /* we are on the last song for the singer  */
	  /* the next line will be another singer */

	  /* first create the node for the linked list */
	  NODEPTR tempNode;
	  tempNode = CreateNode();
	  SetData(tempNode, tempSinger);
	  Insert(&possibleSingersHead, tempNode);

	  /* reset loop */
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

int getRandomNum(int rangeNum){
  /* 
     will return a random number seeded by seedNum
     anywhere from 0 through rangeNum-1
     if rangeNum is 100
     will be anyhere from 0 to 99
   */
  return rand() % rangeNum;
}

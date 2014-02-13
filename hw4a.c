/*
  hw4a.c
  Created by Wesley Zhao
  
  basic karoake C program
 */

#include "karaoke.h"

#define NUM_ARGS 3
/* there should be 3 args, executable name, file1, and file2  */

int main(int argc, char **argv){
  /*
    argc - number of arguments, including name of executable
    char **argv -- array of argument strings
      - argv[0] is string containing name of executable
      - argv[1] is first argument, etc...
    
   */
  
  if (argc != NUM_ARGS){
    fprintf(stderr, "Incorrect number of arguments.\n");
    fprintf(stderr, "Expected <exec> <input filename> <input filename>. \n");
    exit(-1);
  }

  printf("%s\n", argv[1]);
  printf("%s\n", argv[2]);
  printf("Welcome!\n");

  processStuff(argv[1], argv[2]);


  return 0;
}


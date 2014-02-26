/*
  hw4a.c
  Created by Wesley Zhao
  
  basic karoake C program
 */

#include "karaoke.h"

#define NUM_ARGS 4
/* there should be 3 args, executable name, file1, and file2, 
 and the integer to seed the random number generator
*/

int main(int argc, char **argv){
  /*
    argc - number of arguments, including name of executable
    char **argv -- array of argument strings
      - argv[0] is string containing name of executable
      - argv[1] is first argument, etc...
    
   */
  
  if (argc != NUM_ARGS){
    fprintf(stderr, "Incorrect number of arguments.\n");
    fprintf(stderr, "Expected <exec> <input filename> <input filename> <input randomNumberSeed>. \n");
    exit(-1);
  }

  processStuff(argv[1], argv[2], argv[3]);


  return 0;
}


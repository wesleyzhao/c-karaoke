#
# File:   Makefile
# Author: Wesley Zhao
# Desc:   Makefile for Spring 2014 CIS 190 HW 4B
#

# It is important that your makefile not have extra
# tab characters in it -- this can cause problems.

# rules are run by typing make 'rule name'
# for example: 'make all' (without the quotes) would run the first rule

### first rule in the file can also be run with simply 'make' ##



#########################################
# rules for compiling and linking files #
#########################################

# all calls the other rules (trains, hw2, link)
# to to compile the .o files, then link them
all: karaoke hw link

# rules to compile the individual .o files
karaoke:
	gcc -c -Wall karaoke.c
	gcc -c -Wall linkedList.c
hw:
	gcc -c -Wall hw4b.c

# rule to link the .o files into 'hw2' executable
link:
	gcc linkedList.o karaoke.o hw4b.o -o hw4b



########################################
# rules for cleaning away excess files #
########################################

# removes .o and executable files
clean:
	rm  -f linkedList.o karaoke.o hw4b.o hw4b

# removes any temporary (~) files
cleaner: 
	rm  -f *~

# runs both clean and cleaner
cleanest: clean cleaner



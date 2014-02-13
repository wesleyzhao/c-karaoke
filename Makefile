#
# File:   Makefile
# Author: Katherine Gibson (gibsonk@cis)
# Desc:   Makefile for Spring 2014 CIS 190 HW 2
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
hw:
	gcc -c -Wall hw4a.c

# rule to link the .o files into 'hw2' executable
link:
	gcc karaoke.o hw4a.o -o hw4a



########################################
# rules for cleaning away excess files #
########################################

# removes .o and executable files
clean:
	rm  -f karaoke.o hw4a.o hw4a

# removes any temporary (~) files
cleaner: 
	rm  -f *~

# runs both clean and cleaner
cleanest: clean cleaner



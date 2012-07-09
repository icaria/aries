# Universal makefile for single C++ program
#
# Use gcc flag -MMD (user) or -MD (user/system) to generate dependences among source files.
# Use gmake default rules for commonly used file-name suffixes and make variables names.
#
# % gmake (make)  [ a.out ]

########## Variables ##########

CXX = gcc					# compiler
#CXXFLAGS = -g -Wall -MMD			# compiler flags
CXXFLAGS = -m32
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS = lab2linux.o lab2.c 			# object files forming executable


EXEC = a.out					# executable name

########## Targets ##########

.PHONY : clean					# not file names

.PHONY : run

.PHONY : left
.PHONY : right

${EXEC} : ${OBJECTS} 				
	${CXX} ${CXXFLAGS} $^


%.o : %.c
	 
    
clean :						# remove files that can be regenerated
	rm -f lab2.o layer2.txt layer3.txt ${EXEC}

run :
	./${EXEC}

left:
	vim layer2.txt

right:
	vim layer3.txt

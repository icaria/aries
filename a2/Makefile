# Universal makefile for single C++ program
#
# Use gcc flag -MMD (user) or -MD (user/system) to generate dependences among source files.
# Use gmake default rules for commonly used file-name suffixes and make variables names.
#
# % gmake (make)  [ a.out ]

########## Variables ##########

CXX = g++					# compiler
#CXXFLAGS = -g -Wall -MMD			# compiler flags
CXXFLAGS = -O3
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

#OBJECTS = lab2linux.o lab2.o 			# object files forming executable
OBJECTS = lab2.o

EXEC = a.out					# executable name

########## Targets ##########

.PHONY : clean					# not file names

${EXEC} : ${OBJECTS}				# link step
	${CXX} $^ -o $@			# additional object files before $^

%.o : %.cc
	${CXX} $^ -m32 -c -o $@
    
clean :						# remove files that can be regenerated
	rm -f lab2.o ${EXEC}

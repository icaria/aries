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

OBJECTS = RandomForLab1.o simulator.o 			# object files forming executable

EXEC = a.out					# executable name

########## Targets ##########

.PHONY : clean					# not file names

${EXEC} : ${OBJECTS}				# link step
	${CXX} $^ -o $@				# additional object files before $^

%.o : %.c
	${CXX} $^ -c -o $@
    
clean :						# remove files that can be regenerated
	rm -f ${OBJECTS} ${EXEC}

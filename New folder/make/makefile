CXX = g++
CXXFLAGS = -g
EXEC = output
OBJS = main.o functions.o
${EXEC}: ${OBJS}
	${CXX} ${CXXFLAGS} -o ${EXEC} ${OBJS}
functions.o: functions.C classes.h
	${CXX} ${CXXFLAGS} -c functions.C
main.o: main.C classes.h logger/Logger.h
	${CXX} ${CXXFLAGS} -c main.C
clean: 
	rm *.o *.out output

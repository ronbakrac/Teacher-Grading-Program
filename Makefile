myproject: main.o datahandler.o passchange.o student.o
	g++ -o myproject main.o datahandler.o passchange.o student.o
main.o: main.cpp datahandler.h student.h passchange.h
	g++ -c main.cpp
datahandler.o: datahandler.cpp datahandler.h student.h passchange.h
	g++ -c datahandler.cpp
passchange.o: passchange.cpp passchange.h
	g++ -c passchange.cpp
student.o: student.cpp student.h
	g++ -c student.cpp
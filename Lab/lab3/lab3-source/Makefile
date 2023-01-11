CPPFLAGS = -std=c++11

all: lab3.exe

lab3.exe: GymSession.o GymClass.o GymPerson.o GymStudent.o GymCoach.o main.cpp
	g++ -o $@ $(CPPFLAGS) GymSession.o GymClass.o GymPerson.o GymStudent.o GymCoach.o main.cpp

%.o: %.cpp
	g++ $(CPPFLAGS) -c $< -o $@ 

clean:
	rm -f *.o *.exe
# On Windows, use: del *.o *.exe
# On Linux or MacOS, use: rm -f *.o *.exe

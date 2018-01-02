CXX = Main.cpp
CXX += Game.cpp
CXX += Game.hpp
CXX += Garden.hpp
CXX += Garden.cpp
CXX += Azathoth.hpp
CXX += Azathoth.cpp
CXX += Rooms.hpp
CXX += Rooms.cpp
CXX += Basement.cpp
CXX += Basement.hpp
CXX += CeremonyChamber.cpp
CXX += CeremonyChamber.hpp
CXX += Conservatory.hpp
CXX += Conservatory.cpp
CXX += Creature.cpp
CXX += Creature.hpp
CXX += Cultist.cpp
CXX += Cultist.hpp
CXX += DiningRoom.cpp
CXX += DiningRoom.hpp
CXX += Foyer.cpp
CXX += Foyer.hpp
CXX += GuestRoom.hpp
CXX += GuestRoom.cpp
CXX += Hallway.cpp
CXX += Hallway.hpp
CXX += Kitchen.hpp
CXX += Kitchen.cpp
CXX += MasterBedRoom.hpp
CXX += MasterBedroom.cpp
CXX += Study.hpp
CXX += Study.cpp

PROG1 = eldritchEstate
PROGS = ${PROG1}

default:
	g++ ${CXX} -o eldritchEstate

clean:
	rm -f ${PROGS} *.o *~

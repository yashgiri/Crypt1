ALL: ENCRYPT DECRYPT

DECRYPT: IO decrypt.o fileInteraction.o
	g++ -o decrypt decrypt.cpp

ENCRYPT: IO encrypt.o fileInteraction.o
	g++ -o encrypt encrypt.cpp

IO: fileInteraction.cpp
	g++ -c fileInteraction.cpp

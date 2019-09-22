ALL: ENCRYPT DECRYPT

DECRYPT: IO decrypt.o IO
	g++ -o decrypt decrypt.cpp

ENCRYPT: IO encrypt.o IO
	g++ -o encrypt encrypt.cpp

IO: fileInteraction.cpp
	g++ -c fileInteraction.cpp
	
CLEAN:
	rm -f decrypt
	rm -f encrypt
	make ALL
	
TEST: CLEAN
	./encrypt 0 input.txt encryption.txt
	./decrypt 0 encryption.txt decryption.txt
	diff input.txt decryption.txt
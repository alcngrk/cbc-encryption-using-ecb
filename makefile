test.exe: main.o fscrypt.o
	g++ fscrypt.o main.o -lcrypto -lssl -ldl -o test.exe

main.o: main.cc
	g++ -c main.cc

fscrypt.o: fscrypt.h fscrypt.cc
	g++ fscrypt.cc -c fscrypt.cc

clean:
	rm *.o *.exe

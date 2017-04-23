all: main.o
	gcc main.o -o Primalite -lgmp

main.o: main.c 
	gcc -o main.o -c main.c -lgmp 

run:
	./Primalite

clean:
	rm -rf Primalite *.o

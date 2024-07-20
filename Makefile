test : main
	./turing 1
manual: main
	./turing 2
	

main : main.o autre.o bd.o mt.o fonction.h
	gcc -o turing main.o autre.o bd.o mt.o -Wall

main.o : main.c fonction.h
	gcc -c main.c -Wall

autre.o : autre.c fonction.h
	gcc -c autre.c -Wall

bd.o : bd.c fonction.h
	gcc -c bd.c -Wall

mt.o : mt.c fonction.h
	gcc -c mt.c -Wall

clean :
	rm -f turing
	rm -f *.o
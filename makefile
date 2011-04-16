####################################
## MAC0328 - Algoritmos em grafos ##
##                                ##
## Rafael Reggiani Manzo          ##
## 6797150                        ##
####################################

#argumentos de compilacao
CFLAGS = -ansi -pedantic -Wall

Make: main.o text.o input.o output.o depdig.o digraph.o
	gcc main.o text.o input.o output.o depdig.o digraph.o -o Make

main.o: main.c io/text.h
	gcc -c main.c $(CFLAGS)

text.o: io/text.c io/text.h io/input.h io/output.h
	gcc -c io/text.c $(CFLAGS)

input.o: io/input.c io/input.h io/text.h
	gcc -c io/input.c $(CFLAGS)

output.o: io/output.c io/output.h io/text.h
	gcc -c io/output.c $(CFLAGS)

digraph.o: ed/digraph.h ed/digraph.c ed/vertex.h
	gcc -c ed/digraph.c $(CFLAGS)

depdig.o: depdig.c depdig.h io/input.h io/text.h ed/digraph.h ed/vertex.h
	gcc -c depdig.c $(CFLAGS)

#digraph.o: ed/vertex.h arc.o ed/digraph.h ed/digraph.c
#	gcc -c ed/digraph.c $(CFLAGS)

clean:
	rm *.o
	rm Make

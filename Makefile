make :
	make clean
	make new
new :
	gcc -g -c *.c
	gcc -lSDL2 *.o
clean :
	rm -f *.o *.out

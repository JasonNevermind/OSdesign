main:main.o print.o
	gcc -o main main.o print.o

print.o:print.c print.h
	gcc -c print.c

main.o:main.c print.h
	gcc -c main.c


.PHONY : clean
clean:
	del *.o main.exe -rf
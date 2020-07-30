CC=gcc
STD=-std=gnu99
BIN=game.bin
FLAG=-Wall -Werror -DDEBUG
OBJ=main.o tools.o stu_tools.o teacher_tools.o leader_tools.o

all:$(OBJ)
	$(CC) -o $(BIN) $(OBJ)

main.o:main.c tools.h stu_tools.h teacher_tools.h leader_tools.h
	$(CC) $(STD) $(FLAG) -c main.c

tools.o:tools.c tools.h
	$(CC) $(STD) $(FLAG) -c tools.c
stu_tools.o:stu_tools.c stu_tools.h tools.h
	$(CC) $(STD) $(FLAG) -c stu_tools.c
teacher_tools.o:teacher_tools.c teacher_tools.h tools.h
	$(CC) $(STD) $(FLAG) -c teacher_tools.c
leader_tools.o:leader_tools.c leader_tools.h tools.h
	$(CC) $(STD) $(FLAG) -c leader_tools.c
clean:
	rm -rf $(BIN) $(OBJ) 

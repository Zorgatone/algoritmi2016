NAME= es3
BIN= bin
SRC= src
EXE:= $(BIN)/$(NAME)
INPUT= input.txt

#RM=rm -rf
#CC=gcc

OBJS:= $(BIN)/$(NAME).o $(BIN)/student.o
FLAGS= -std=c11 -Wall -Wextra -pedantic

all: $(EXE)
$(EXE): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(EXE)

$(BIN)/$(NAME).o: $(SRC)/student/student.h $(SRC)/$(NAME).c
	$(CC) $(FLAGS) -c $(SRC)/$(NAME).c -o $(BIN)/$(NAME).o

$(BIN)/student.o: $(SRC)/student/student.h $(SRC)/student/student.c
	$(CC) $(FLAGS) -c $(SRC)/student/student.c -o $(BIN)/student.o

.PHONY: clean
clean:
	$(RM) $(EXE) $(OBJS)

.PHONY: run
run: $(EXE)
	@$(EXE) $(INPUT)

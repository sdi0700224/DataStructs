# paths
MODULES = ../../solutions-ergasia1/question4
INCLUDE = ../../solutions-ergasia1/question4

# compiler
CC = gcc

# Compile options. Το -I<dir> λέει στον compiler να αναζητήσει εκεί include files
CFLAGS = -Wall -Werror -g -I$(INCLUDE)

# Αρχεία .o
OBJS = quest4.o $(MODULES)/puzzlerec.o

# Το εκτελέσιμο πρόγραμμα
EXEC = quest4

# Παράμετροι για δοκιμαστική εκτέλεση
ARGS = #

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) -lm

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC) $(ARGS)
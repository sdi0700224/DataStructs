# paths
MODULES = ../../solutions-ergasia2/question1
INCLUDE = ../../solutions-ergasia2/question1

# compiler
CC = gcc

# Compile options. Το -I<dir> λέει στον compiler να αναζητήσει εκεί include files
CFLAGS = -Wall -Werror -g -I$(INCLUDE)

# Αρχεία .o
OBJS = insertion-sort.o

# Το εκτελέσιμο πρόγραμμα
EXEC = insertion-sort

# Παράμετροι για δοκιμαστική εκτέλεση
ARGS = 20

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC) $(ARGS)
# paths
MODULES = ../../solutions-ergasia2/question3
INCLUDE = ../../solutions-ergasia2/question3

# compiler
CC = gcc

# Compile options. Το -I<dir> λέει στον compiler να αναζητήσει εκεί include files
CFLAGS = -Wall -Werror -g -I$(INCLUDE)

# Αρχεία .o
OBJS = sorting.o $(MODULES)/PQImplementation.o

# Το εκτελέσιμο πρόγραμμα
EXEC = sorting

# Παράμετροι για δοκιμαστική εκτέλεση
ARGS =

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC) $(ARGS)
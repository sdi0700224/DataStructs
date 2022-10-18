# paths
MODULES = ../../solutions-ergasia2/question11
INCLUDE = ../../solutions-ergasia2/question11

# compiler
CC = gcc

# Compile options. Το -I<dir> λέει στον compiler να αναζητήσει εκεί include files
CFLAGS = -Wall -Werror -g -I$(INCLUDE)

# Αρχεία .o
OBJS = quest11.o $(MODULES)/bst-implementation.o item-implementation.o

# Το εκτελέσιμο πρόγραμμα
EXEC = quest11

# Παράμετροι για δοκιμαστική εκτέλεση
ARGS = 15

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC) $(ARGS)
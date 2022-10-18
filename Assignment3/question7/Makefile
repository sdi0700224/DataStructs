# paths
MODULES = ../../solutions-ergasia3/question7
INCLUDE = ../../solutions-ergasia3/question7

# compiler
CC = gcc

# Compile options. Το -I<dir> λέει στον compiler να αναζητήσει εκεί include files
CFLAGS = -Wall -Werror -g -I$(INCLUDE)

# Αρχεία .o
OBJS = quest7.o $(MODULES)/undirectedGraph.o bfs.o QImplementation.o

# Το εκτελέσιμο πρόγραμμα
EXEC = quest7

# Παράμετροι για δοκιμαστική εκτέλεση
ARGS = 'graph.txt'

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC) $(ARGS)
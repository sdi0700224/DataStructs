# paths
MODULES = ../../solutions-ergasia3/question8
INCLUDE = ../../solutions-ergasia3/question8

# compiler
CC = gcc

# Compile options. Το -I<dir> λέει στον compiler να αναζητήσει εκεί include files
CFLAGS = -Wall -Werror -g -I$(INCLUDE)

# Αρχεία .o
OBJS = quest8.o $(MODULES)/weightedGraph.o PRQ.o

# Το εκτελέσιμο πρόγραμμα
EXEC = quest8

# Παράμετροι για δοκιμαστική εκτέλεση
ARGS = 'graph.txt'

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC) $(ARGS)
# paths
MODULES = ../../solutions-ergasia1/question2
INCLUDE = ../../solutions-ergasia1/question2

# compiler
CC = gcc

# Compile options. Το -I<dir> λέει στον compiler να αναζητήσει εκεί include files
CFLAGS = -Wall -Werror -g -I$(INCLUDE)

# Αρχεία .o
OBJS = quest2.o $(MODULES)/DListImplementation.o

# Το εκτελέσιμο πρόγραμμα
EXEC = quest2

# Παράμετροι για δοκιμαστική εκτέλεση
ARGS = #

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC) $(ARGS)
# paths
MODULES = ../../solutions-ergasia1/question5
INCLUDE = ../../solutions-ergasia1/question5

# compiler
CC = gcc

# Compile options. Το -I<dir> λέει στον compiler να αναζητήσει εκεί include files
CFLAGS = -Wall -Werror -g -I$(INCLUDE)

# Αρχεία .o
OBJS = quest5.o $(MODULES)/STACKImplementation.o EvalImplementation.o

# Το εκτελέσιμο πρόγραμμα
EXEC = quest5

# Παράμετροι για δοκιμαστική εκτέλεση
ARGS = '(((25 + 31) * 44) * (2 + 31))'

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC) $(ARGS)
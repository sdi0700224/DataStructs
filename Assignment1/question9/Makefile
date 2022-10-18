# paths
MODULES = ../../solutions-ergasia1/question9
INCLUDE = ../../solutions-ergasia1/question9

# compiler
CC = gcc

# Compile options. Το -I<dir> λέει στον compiler να αναζητήσει εκεί include files
CFLAGS = -Wall -Werror -g -I$(INCLUDE)

# Αρχεία .o
OBJS = quest9.o $(MODULES)/PRQ.o STACKImplementation.o PQ.o

# Το εκτελέσιμο πρόγραμμα
EXEC = quest9

# Παράμετροι για δοκιμαστική εκτέλεση
ARGS = '(pm, onaz, bc, dfg, e, j)' '(adgpmj, noc, befz)'
#ARGS = '(plm, oknqaz, bxvc, dhfg, wertyui, js)' '(adgpmj, noc, befzy, qrstuvwxhikl)'

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC) $(ARGS)
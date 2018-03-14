CC		= gcc
CFLAGS	= -g3 -Wall
EXEC 	= fwf
OBJS 	= args.o files.o list.o main.o mem.o
SRCS 	= args.c files.c list.c main.c mem.c


.PHONY : all
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

args.o: args.c
	$(CC) $(CFLAGS) -c args.c

files.o: files.c
	$(CC) $(CFLAGS) -c files.c

list.o: list.c
	$(CC) $(CFLAGS) -c list.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

mem.o: mem.c
	$(CC) $(CFLAGS) -c mem.c



.PHONY: clean
clean:
	rm -f $(OBJS) $(EXEC)
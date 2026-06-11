CC := gcc
OBJS := hello.o first.o second.o
DEPENDS := first.h second.h

hello: $(OBJS)
	$(CC) -o hello $(OBJS)

%.o: %.c $(DEPENDS)
	$(CC) -c -o $@ $<

.PHONY: clean

clean:
	rm *.o
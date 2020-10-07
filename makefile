SRC= $(wildcard *.c)
TESTS = $(patsubst %.c, %, $(SRC))

.PHONY: all clean

all:
	gcc serveur.c -o serveur -lpthread
	gcc client.c -o client
clean:
	$(RM) $(TESTS)

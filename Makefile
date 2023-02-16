CC = gcc
PREFIX = /usr


install:
	$(CC) -o stlog stlog.c
	cp -f stlog $(PREFIX)/bin/

uninstall:
	rm -f stlog $(PREFIX)/bin/stlog $(MANPREFIX)/man1/stlog.1
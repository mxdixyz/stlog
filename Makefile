# See LICENSE file for copyright and license details.
CC = gcc
PREFIX = /usr/local


all:
	$(CC) -g -o stlog stlog.c

install: all
	mkdir -p "$(PREFIX)/bin"
	cp -f stlog "$(PREFIX)/bin"
	chmod 755 "$(PREFIX)/bin/stlog"

uninstall:
	rm -f "$(PREFIX)/bin/stlog"
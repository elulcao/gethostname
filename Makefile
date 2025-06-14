CC=gcc
PREFIX=/usr/local
BINDIR=$(PREFIX)/bin
LIBDIR=$(PREFIX)/lib
NAME=gethostname

all: clean build

build: lib$(NAME).so.1

lib$(NAME).so.1: $(NAME).c
	$(CC) -fPIC -rdynamic -g -Wall -shared -Wl,-soname,$@ -lc -ldl -o $@ $<

test:
	@out=`LD_PRELOAD=$(PWD)/lib$(NAME).so.1 NEWHOSTNAME=my_host_name hostname`; \
	if [ "$$out" = "my_host_name" ]; then \
	echo "hostname output matches my_host_name"; \
	else \
	echo "expected my_host_name but got $$out"; \
	exit 1; \
	fi

clean:
	-rm -f lib$(NAME).so.1

install: all
	install -m 0755 lib$(NAME).so.1 $(LIBDIR)

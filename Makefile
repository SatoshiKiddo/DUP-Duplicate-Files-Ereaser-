
all: link

install:
	sudo rm /usr/local/bin/dup
	gcc Dup.c -o dup
	sudo ln -s /Users/kiddo/Documents/SistemasP/dup /usr/local/
link:
	gcc -Wall Dup.c -o dup
	sudo ln -s /Users/kiddo/Documents/SistemasP/dup /usr/local/

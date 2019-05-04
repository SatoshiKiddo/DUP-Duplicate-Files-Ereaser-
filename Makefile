
all: link

install-copy:
	gcc Dup.c -o dup
	sudo cp	./dup /usr/local/
link:
	gcc -Wall Dup.c -o dup
	sudo ln -s ./dup /usr/local/
clean:
	sudo rm /usr/local/bin/dup

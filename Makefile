build: 
	gcc -Wall telefon.c -o telefon -std=c99
run: build
	./telefon
clean:
	rm -f telefon.o
	rm -f telefon

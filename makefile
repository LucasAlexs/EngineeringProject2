all:	matrizes aplicacao teste
matrizes:
	mkdir build
	gcc src/main.c -lgsl -o build/matrizes.o
aplicacao:
	gcc -c src/main.c -o build/main.o
	gcc build/matrizes.o build/main.o -lgsl -o build/matrizes.out
	gcc build/matrizes.o build/main.o -lgsl -o build/matrizes.exe
teste:
	./build/matrizes.out
	./build/matrizes.exe
clean:
	rm -rf build/*
	rmdir build
	rm -rf doc/html/*.css
	rm -rf doc/html/*.html
	rm -rf doc/html/*.png
	rm -rf doc/html/*.svg
	rm -rf doc/html/*.js
	rm -rf doc/html/*.dot
.PHONY:	doc
doc:
	doxygen
	

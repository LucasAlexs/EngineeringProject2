all:	doc matrizes aplicacao teste
matrizes:
	mkdir build
	gcc src/main.c -lgsl -o build/matrizes.o
aplicacao:
	mkdir -p build
	gcc -c src/main.c -o build/main.o
	gcc build/main.o -lgsl -lgslcblas -lm -o build/matrizes.out

teste:
	./build/matrizes.out
clean:
	rm -rf build/*
	rm -rf doc/*
	rmdir build
	rmdir doc
	rm -rf doc/html/*.css
	rm -rf doc/html/*.html
	rm -rf doc/html/*.png
	rm -rf doc/html/*.svg
	rm -rf doc/html/*.js
	rm -rf doc/html/*.dot
.PHONY:	doc
doc:
	doxygen
	

all:	matrizes
matrizes:
	mkdir build
	gcc src/main.c -lgsl -o build/matrizes
	./build/matrizes.out
aplicacao:
	gcc -c src/matrizes/matrizes.c -o build/matrizes.o
	gcc -c src/main.c -o build/main.o
	gcc build/matrizes.o build/main.o -o build/matrizes
teste:
	./build/matrizes
clean:
	rm build
	rm -rf build/*matrizes
	rm -rf doc/html/*.css
	rm -rf doc/html/*.html
	rm -rf doc/html/*.png
	rm -rf doc/html/*.svg
	rm -rf doc/html/*.js
	rm -rf doc/html/*.dot
.PHONY:	doc
doc:
	doxygen doxyfile
	

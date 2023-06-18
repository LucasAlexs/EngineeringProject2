all:	matrizes
matrizes:
	gcc src/main.c -lgsl -o build/matrizes.out
	gcc src/main.c -lgsl -o build/matrizes.exe
aplicacao:
	gcc -c src/matrizes/matrizes.c -o build/matrizes.o
	gcc -c src/main.c -o build/main.o
	gcc build/matrizes.o build/main.o -o build/matrizes
teste:
	./build/matrizes.out
	./build/matrizes.exe
clean:
	rm -rf build/*.o
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
	

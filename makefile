all:	doc matrizes aplicacao teste
matrizes:
	mkdir -m 777 build
aplicacao:
	mkdir -m 777 -p build
	gcc -c src/main.c -o build/main.o
	gcc -c src/matrizes/pds_telecom.c -o build/pds_telecom.o
	gcc -c src/matrizes/matrizes.c -o build/matrizes.o
	gcc build/matrizes.o build/pds_telecom.o -lgsl -lgslcblas -lm -o build/pds_telecom.out


teste:
	./build/pds_telecom.out
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

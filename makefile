all:	doc aplicacao teste
build:
	@if [ ! -d "build" ]; then \
		mkdir -m 777 build; \
	fi
aplicacao:
	@if [ ! -d "build" ]; then \
		mkdir -m 777 -p build; \
	fi
	gcc -c src/main.c -o build/main.o
	gcc -c src/matrizes/pds_telecom.c -o build/pds_telecom.o
	gcc -c src/matrizes/matrizes.c -o build/matrizes.o
	gcc build/matrizes.o build/pds_telecom.o -lgsl -lgslcblas -lm -o build/pds_telecom.out
	gcc build/matrizes.o build/main.o -lgsl -lgslcblas -lm -o build/matrizes.out

teste:
	./build/matrizes.out
	./build/pds_telecom.out
clean:
	@if [ -d "build" ]; then \
		rm -rf build/; \
	fi
	@if [ -d "doc" ]; then \
		rm -rf doc/; \
		rmdir doc; \
	fi
	rm -rf doc/html/*.css
	rm -rf doc/html/*.html
	rm -rf doc/html/*.png
	rm -rf doc/html/*.svg
	rm -rf doc/html/*.js
	rm -rf doc/html/*.dot
.PHONY:	doc
doc:
	doxygen

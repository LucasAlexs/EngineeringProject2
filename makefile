#pasta matrizes
mat = src/matrizes

#pasta html
ww = doc/html

#bandeiras para o compilador
flags = -lgsl -lgslcblas -lm

all:	doc aplicacao teste
build:
	@if [ ! -d "build" ]; then \
		mkdir -m 777 build; \
	fi
aplicacao: build
	gcc -c src/main.c -o build/main.o
	gcc -c $(mat)/pds_telecom.c -o build/pds_telecom.o
	gcc -c $(mat)/matrizes.c -o build/matrizes.o
	gcc build/matrizes.o build/pds_telecom.o $(flags) -o build/pds_telecom.out
	gcc build/matrizes.o build/main.o $(flags) -o build/matrizes.out
	@echo -e "\n Voce pode usar os comandos:"
	@echo -e "\n-make clean - para apagar arquivos da pasta html"
	@echo -e "\n-make teste - para executar o teste do canal"
	@echo -e "\n make doc - para gerar a documentação do projeto"
	@echo -e "\n make webpage - para abrir pagina web da documentação \n"
teste:
	./build/matrizes.out
	./build/pds_telecom.out
clean:
	@if [ -d "build" ]; then \
		rm -rf build/; \
	fi
	@if [ -d "doc" ]; then \
	find doc/ -type f ! -path '$(ww)/images/*' -delete; \
	find doc/ -type d -empty -delete; \
	fi
	rm -rf $(ww)/*.css
	rm -rf $(ww)/*.html
	rm -rf $(ww)/*.png
	rm -rf $(ww)/*.svg
	rm -rf $(ww)/*.js
	rm -rf $(ww)/*.dot
.PHONY:	doc
doc:
	doxygen
.PHONY: webpage
webpage: $(ww)/index.html
	start "$(ww)/index.html"
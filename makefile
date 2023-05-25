# Pasta source
src = ./src

# Pasta onde estao os codigos-fonte das matrizes
matrizes = ./src/matrizes

# Pasta de arquivos de saída do doc 
obj = ./build

# Regra aplicacao
acao = aplicacao

# Pasta html
html = ./doc/html

# Bandeiras para o compilador
flags = -W         \
        -Wall      \
        -pedantic


all: $(obj) $(acao) doc


$(acao):$(obj)/main.o $(obj)/matrizes.o
	@echo -e "\n Gerando o arquivo $@ ... "
	gcc $< $(obj)/matrizes.o -I $(obj) -o $@.exe $(flags)
	@echo -e "\n Para executar o arquivo a partir de 'main.c': execute o arquivo $(obj)/$@.exe ou a regra de comando 'make teste'."
	@echo -e "\n Para executar o projeto webpage: execute o arquivo $(html)/index.html ou a regra de comando 'make webpage'."

$(obj)/main.o: $(src)/main.c
	@echo -e "\n Gerando o arquivo $@... "
	gcc -c $< -I $(obj) -o $@ $(flags)

$(obj)/matrizes.o: $(src)/matrizes.c
	@echo -e "\n Gerando o arquivo $@... "
	gcc -c $< -I $(obj) -o $@ $(flags)


$(obj):
	mkdir$(obj)


teste: $(obj)/$(acao).exe 
         $(obj)/$(acao).exe

.PHONY: doc

doc: Doxyfile
	@echo -e "\n Gerando documentacao dos arquivos... "
	doxygen Doxyfile


.PHONY: webpage

webpage: $(html)/index.html
	@echo -e "\n Abrindo o documento de pagina web... "
	start "$(html)/index.html"


.PHONY: cyg

cyg: $(html)/index.html
	@echo -e "\n Abrindo o documento de pagina web... "
	cygstart "$(html)/index.html"

clean:
	rm - rf $(obj)/*exe
	rm - rf $(obj)/*exe
	
	find doc -type f ! -path "doc/rtf/*" ! -path "doc/html/*" -delete
	find doc -type d -empty -delete
	
	@echo -e "\n Arquivos '.o' e '.exe' sendo deletados"
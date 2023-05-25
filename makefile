# Pasta source
src = ./src

# Pasta onde estão os códigos-fonte das matrizes
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
        -ansi      \
        -pedantic


all: $(obj) $(acao) doc


$(acao): $(obj)/main.o $(obj)/matrizes.o
	@echo -e "\n Gerando o arquivo $@ ..."
	gcc $< $(obj)/matrizes.o -J $(obj) -o $@.exe $(flags)


$(obj)/main.o: $(src)/main.c
	@echo -e "\n Gerando o arquivo $@..."
	gcc -c $< -J $(obj) -o $@ $(flags)


$(obj)/matrizes.o: $(matrizes)/matrizes.c
	@echo -e "\n Gerando o arquivo $@..."
	gcc -c $< -J $(obj) -o $@ $(flags)


$(obj):
	mkdir $(obj)


teste: $(obj)/$(acao).exe
	$(obj)/$(acao).exe
@echo -e "\n criando $@..."


.PHONY: doc
doc: Doxyfile
	@echo -e "\n Gerando documentacao dos arquivos... "
	doxygen Doxyfile


.PHONY: webpage
webpage: $(html)/index.html
	@echo -e "\n Abrindo o documento de pagina web... "
	start "$(html)/index.html"


clean:
	@echo -e "\n Arquivos '.o' e '.exe' sendo deletados"
	rm -rf $(obj)/*.exe
	rm -rf $(obj)/*.o
	find doc -type f ! -path "doc/rtf/*" ! -path "doc/html/*" -delete
	find doc -type d -empty -delete

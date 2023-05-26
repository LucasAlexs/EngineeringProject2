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
        #-ansi      \
        -pedantic


all: $(obj) $(acao) #doc


$(acao): $(obj)/main.o $(obj)/matrizes.o
	gcc $^ -I $(obj) -o $@.exe $(flags)
	@echo -e "\n Arquivo $@ gerado"


$(obj)/main.o: $(src)/main.c
	gcc -c $< -J $(obj) -o $@ $(flags)
	@echo -e "\n Arquivo $@ gerado"


$(obj)/matrizes.o: $(matrizes)/matrizes.c
	gcc -c $< -J $(obj) -o $@ $(flags)
	@echo -e "\n Arquivo $@ gerado"

$(obj):
	mkdir $(obj)


teste: $(obj)/$(acao).exe
	$(obj)/$(acao).exe
	@echo -e "\n $@ criado"


.PHONY: doc
doc: Doxyfile
	doxygen Doxyfile
	@echo -e "\n Documentacao de arquivos gerada "


.PHONY: webpage
webpage: $(html)/index.html
	@echo -e "\n Abrindo o documento de pagina web: index"
	start "$(html)/index.html"


clean:
	rm -rf $(obj)/*.exe
	rm -rf $(obj)/*.o
	@echo -e "\n Arquivos '.o' e '.exe' deletados"
	find doc -type f ! -path "doc/rtf/*" ! -path "doc/html/*" -delete
	find doc -type d -empty -delete

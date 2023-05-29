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
        -pedantic


all: $(obj) $(acao) doc


$(acao): $(obj)/main.o $(obj)/matrizes.o
	gcc $^ -I $(obj) -o $(obj)/$@.exe $(flags)
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
	@echo -e "\n $@ gerado "


doc: Doxyfile
	doxygen Doxyfile
	@echo -e "\n Documentacao de arquivos gerada "
	@echo -e "\n Voce pode utilizar 'make teste' para testar o arquivo aplicacao"
	@echo -e "\n Voce pode utilizar 'make webpage' para abrir a documentacao online"
	@echo -e "\n Voce pode utilizar 'make clean' para deitar as pastas 'doc' e 'build'"


.PHONY: webpage
webpage: $(html)/index.html
	@echo -e "\n Abrindo o documento de pagina web: index"
	start "$(html)/index.html"


clean:
	rm -rf doc
	rm -rf $(obj)
	@echo -e "\n pastas 'build' e 'doc' deletadas"
# kompilator c
CCOMP = gcc

# konsolidator
LOADER = gcc

# opcje optymalizacji:
# wersja do debugowania
OPT = -g -DDEBUG
# wersja zoptymalizowana do mierzenia czasu
# OPT = -O3

# zaleznosci i komendy
atrybuty: atrybuty.o 
	$(LOADER) $(OPT) atrybuty.o -o atrybuty -lpthread $(LIB)

atrybuty.o: atrybuty.c
	$(CCOMP) -c $(OPT) atrybuty.c 

clean:
	rm -f *.o atrybuty
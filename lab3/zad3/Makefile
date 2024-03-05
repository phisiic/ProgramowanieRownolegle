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
struktura: struktura.o 
	$(LOADER) $(OPT) struktura.o -o struktura -lpthread $(LIB)

struktura.o: struktura.c
	$(CCOMP) -c $(OPT) struktura.c 

clean:
	rm -f *.o struktura
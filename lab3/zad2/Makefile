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
argumenty: argumenty.o 
	$(LOADER) $(OPT) argumenty.o -o argumenty -lpthread $(LIB)

argumenty.o: argumenty.c
	$(CCOMP) -c $(OPT) argumenty.c 

clean:
	rm -f *.o argumenty
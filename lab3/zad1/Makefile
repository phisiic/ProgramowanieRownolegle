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
pthreads_detach_kill: pthreads_detach_kill.o 
	$(LOADER) $(OPT) pthreads_detach_kill.o -o pthreads_detach_kill -lpthread $(LIB)

# jak uzyskac plik pthreads_kill_detach.o ?
pthreads_detach_kill.o: pthreads_detach_kill.c
	$(CCOMP) -c $(OPT) pthreads_detach_kill.c 

clean:
	rm -f *.o pthreads_detach_kill
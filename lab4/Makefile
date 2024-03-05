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
pub_sym_1: pub_sym_1.o 
	$(LOADER) $(OPT) pub_sym_1.o -o pub_sym_1 -lpthread $(LIB)

# jak uzyskac plik pthreads_kill_detach.o ?
pub_sym_1.o: pub_sym_1.c
	$(CCOMP) -c $(OPT) pub_sym_1.c 

# zaleznosci i komendy
pub_sym_1_2: pub_sym_1_2.o 
	$(LOADER) $(OPT) pub_sym_1_2.o -o pub_sym_1_2 -lpthread $(LIB)

# jak uzyskac plik pthreads_kill_detach.o ?
pub_sym_1_2.o: pub_sym_1_2.c
	$(CCOMP) -c $(OPT) pub_sym_1_2.c 

	# zaleznosci i komendy
pub_sym_2: pub_sym_2.o 
	$(LOADER) $(OPT) pub_sym_2.o -o pub_sym_2 -lpthread $(LIB)

# jak uzyskac plik pthreads_kill_detach.o ?
pub_sym_2.o: pub_sym_2.c
	$(CCOMP) -c $(OPT) pub_sym_2.c 

	# zaleznosci i komendy
pub_sym_bez_mutex: pub_sym_bez_mutex.o 
	$(LOADER) $(OPT) pub_sym_bez_mutex.o -o pub_sym_bez_mutex -lpthread $(LIB)

# jak uzyskac plik pthreads_kill_detach.o ?
pub_sym_bez_mutex.o: pub_sym_bez_mutex.c
	$(CCOMP) -c $(OPT) pub_sym_bez_mutex.c 

clean:
	rm -f *.o pub_sym_1 pub_sym_2 pub_sym_bez_mutex
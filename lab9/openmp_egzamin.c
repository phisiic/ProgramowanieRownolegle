
void funkcja_watku (double poczatek, double koniec) {
    //MAGIC
    double dlugosc_odcinka = koniec - poczatek;
    double srodek = (koniec - poczatek) / 2.0;

    if(dlugosc_odcinka > 0.99)
    {
        #pragma omp task
        {
            funkcja_watku(poczatek, srodek);
        }

        #pragma omp task
        {
            funkcja_watku(srodek, koniec);
        }
    }
}
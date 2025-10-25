#ifndef CALCOLATORELIMONCELLO_FUNZIONILIMONCELLO_NEW
#define CALCOLATORELIMONCELLO_FUNZIONILIMONCELLO_NEW

#endif //CALCOLATORELIMONCELLO_FUNZIONILIMONCELLO_NEW

#include <iostream>

// Costanti fisiche globali
namespace Costanti {
    const double DENSITA_ALCOOL = 0.789;   // g/ml per alcol etilico 96%
    const double GRADO_ALCOOL = 0.96;      // 96% vol
    const double PERCENTUALE_ACQUA_ALCOOL = 1 - GRADO_ALCOOL;
    const double ACQUA_BUCCE = 0.70;       // 70% acqua nelle bucce
    const double CONTRAZIONE = 0.03;       // contrazione volumetrica alcol-acqua 3%
    const double CONTRIBUTO_ZUCCHERO = 0.625; // ml/g volume aumentato da zucchero
}

class Tentativi {
    public:
        double massaAlcool;
        double massaZucchero;
        double massaAcqua;
        double gradazione;
        double dolcezza;

        Tentativi(int mAlcool, int mZucchero, int mAcqua) {
            // Crea un tentativo in base a dati già esistenti
            massaAlcool = mAlcool;
            massaZucchero = mZucchero;
            massaAcqua = mAcqua;
            massaBucce = mAlcool / 2.0;
            acquaBucce = massaBucce * Costanti::ACQUA_BUCCE;
            massaAlcoolPuro = massaAlcool * Costanti::GRADO_ALCOOL;
            volumeAlcol = massaAlcoolPuro / Costanti::DENSITA_ALCOOL;
            volumeZucchero = massaZucchero * Costanti::CONTRIBUTO_ZUCCHERO;
            massaAcquaTotale = massaAcqua + acquaBucce + (massaAlcool - massaAlcoolPuro);
            volumeAcqua = massaAcquaTotale;
            volumeTotale = (volumeAlcol + volumeAcqua) * (1.0- Costanti::CONTRAZIONE);
            gradazione = (volumeAlcol / volumeTotale) * 100.0;
            dolcezza = massaZucchero / volumeTotale;
        }

        Tentativi(Tentativi &t, double massaBucceLimone) {
            // Crea un tentativo a partire da un altro tentativo, sapendo la quantità di bucce di limone che si hanno
            massaAlcool = massaBucceLimone * 2;
            massaBucce = massaBucceLimone;
            massaZucchero = (massaAlcool * t.massaZucchero) / t.massaAlcool;
            massaAcqua = (massaAlcool * t.massaAcqua) / t.massaAlcool;
            acquaBucce = massaBucce * Costanti::ACQUA_BUCCE;
            massaAlcoolPuro = massaAlcool * Costanti::GRADO_ALCOOL;
            volumeAlcol = massaAlcoolPuro / Costanti::DENSITA_ALCOOL;
            volumeZucchero = massaZucchero * Costanti::CONTRIBUTO_ZUCCHERO;
            massaAcquaTotale = massaAcqua + acquaBucce + (massaAlcool - massaAlcoolPuro);
            volumeAcqua = massaAcquaTotale;
            volumeTotale = (volumeAlcol + volumeAcqua) * (1.0- Costanti::CONTRAZIONE);
            gradazione = (volumeAlcol / volumeTotale) * 100.0;
            dolcezza = massaZucchero / volumeTotale;
        }

        Tentativi(double massaBucceLimone, double gradazioneDesiderata, double dolcezzaDesiderata) {
            // Crea un tentativo a partire dalla gradazione e la dolcezza desiderata, sapendo la quantità di bucce di limone che si hanno
            massaAlcool = massaBucceLimone * 2;
            massaBucce = massaBucceLimone;
            massaAlcoolPuro = massaAlcool * Costanti::GRADO_ALCOOL;
            volumeAlcol = massaAlcoolPuro / Costanti::DENSITA_ALCOOL;
            gradazione = gradazioneDesiderata;
            massaZucchero = (volumeAlcol*dolcezzaDesiderata*100) / gradazioneDesiderata;
            acquaBucce = massaBucce * Costanti::ACQUA_BUCCE;
            volumeZucchero = massaZucchero * Costanti::CONTRIBUTO_ZUCCHERO;
            volumeTotale = (massaZucchero/dolcezzaDesiderata);
            volumeAcqua = (volumeTotale/(1- Costanti::CONTRAZIONE))-volumeAlcol;
            massaAcquaTotale = volumeAcqua;
            massaAcqua = volumeAcqua - (acquaBucce + (massaAlcool - massaAlcoolPuro));
            dolcezza = dolcezzaDesiderata;
        }

        void displayValori() const {
            std::cout << "Massa alcool: " << massaAlcool << std::endl;
            std::cout << "Massa zucchero: " << massaZucchero << std::endl;
            std::cout << "Massa acqua: " << massaAcqua << std::endl;
            std::cout << "Gradazione: " << gradazione << std::endl;
            std::cout << "Dolcezza: " << dolcezza << std::endl;
        }
    private:
        double massaBucce;
        double acquaBucce;
        double massaAlcoolPuro;
        double massaAcquaTotale;
        double volumeAlcol;
        double volumeAcqua;
        double volumeZucchero;
        double volumeTotale;
};
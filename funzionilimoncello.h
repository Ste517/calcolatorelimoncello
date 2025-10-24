//
// Created by graku on 24/10/2025.
//

#ifndef TEST_FUNZIONILIMONCELLO_H
#define TEST_FUNZIONILIMONCELLO_H

#endif //TEST_FUNZIONILIMONCELLO_H

#include <iostream>

// Costanti fisiche globali
const double DENSITA_ALCOOL = 0.789;   // g/ml per alcol etilico 96%
const double GRADO_ALCOOL = 0.96;      // 96% vol
const double PERCENTUALE_ACQUA_ALCOOL = 1 - GRADO_ALCOOL;
const double ACQUA_BUCCE = 0.70;       // 70% acqua nelle bucce
const double CONTRAZIONE = 0.03;       // contrazione volumetrica alcol-acqua 3%
const double CONTRIBUTO_ZUCCHERO = 0.625; // ml/g volume aumentato da zucchero

struct Tentativi {
    double massaAlcool;   // g di alcol usato (95-96%)
    double massaZucchero; // g di zucchero aggiunto
    double massaAcqua;    // g di acqua aggiunta

    double calcolaGradazione() {
        // Bucce = metà della massa di alcol
        double massa_bucce = massaAlcool / 2.0;
        double acqua_bucce = massa_bucce * ACQUA_BUCCE;

        // Composizione chimica: alcol puro e acqua residua
        double massa_alcol_puro = massaAlcool * GRADO_ALCOOL;
        double massa_acqua_totale = massaAcqua + acqua_bucce + (massaAlcool - massa_alcol_puro);

        // Calcolo volumi parziali
        double volume_alcol = massa_alcol_puro / DENSITA_ALCOOL;
        double volume_acqua = massa_acqua_totale; // densità acqua ~ 1 g/ml

        // Contrazione del volume durante la miscelazione
        double volume_miscelato = (volume_alcol + volume_acqua) * (1.0 - CONTRAZIONE);

        // Volume zucchero (incremento volumetrico)
        double volume_zucchero = massaZucchero * CONTRIBUTO_ZUCCHERO;

        // Volume totale finale
        double volume_finale = volume_miscelato + volume_zucchero;

        // Gradazione in % vol
        double gradazione_finale = (volume_alcol / volume_finale) * 100.0;

        return gradazione_finale;
    }

    double calcolaDolcezza() {
        // Dolcezza come percentuale in massa di zucchero sul volume totale (ml)
        double massa_bucce = massaAlcool / 2.0;
        double acqua_bucce = massa_bucce * ACQUA_BUCCE;
        double massa_alcol_puro = massaAlcool * GRADO_ALCOOL;
        double massa_acqua_totale = massaAcqua + acqua_bucce + (massaAlcool - massa_alcol_puro);
        double volume_alcol = massa_alcol_puro / DENSITA_ALCOOL;
        double volume_acqua = massa_acqua_totale;
        double volume_miscelato = (volume_alcol + volume_acqua) * (1.0 - CONTRAZIONE);
        double volume_zucchero = massaZucchero * CONTRIBUTO_ZUCCHERO;
        double volume_finale = volume_miscelato + volume_zucchero;
        // Dolcezza = massa zucchero / volume totale (g/ml) => valore senza unità proporzionale alla concentrazione
        return massaZucchero / volume_finale;
    }

    void displayValori() {
        std::cout << "Massa zucchero: " << massaZucchero << std::endl;
        std::cout << "Massa alcool: " << massaAlcool << std::endl;
        std::cout << "Massa acqua: " << massaAcqua << std::endl;
        std::cout << "Gradazione alcolica: " << calcolaGradazione() << std::endl;
        std::cout << "Dolcezza: " << calcolaDolcezza() << std::endl;
    }
};

// Funzione per adattare nuova quantità di scorze di limone
Tentativi ricreaTentativo(Tentativi base, double massaScorzeLimone) {
    Tentativi nuovo;
    nuovo.massaAlcool = massaScorzeLimone * 2.0; // Bucce = metà alcool → alcool = 2×bucce
    nuovo.massaZucchero = (nuovo.massaAlcool * base.massaZucchero) / base.massaAlcool;
    nuovo.massaAcqua    = (nuovo.massaAlcool * base.massaAcqua) / base.massaAlcool;
    return nuovo;
}

// Crea un Tentativo in base a gradazione e dolcezza desiderate
Tentativi creaTentativoDaObiettivi(double massaBucce, double gradazioneDesiderata, double dolcezzaDesiderata) {
    Tentativi t;
    t.massaAlcool = massaBucce * 2.0;
    double massa_alcol_puro = t.massaAlcool * GRADO_ALCOOL;
    double volume_alcol = massa_alcol_puro / DENSITA_ALCOOL;

    // Stima iniziale dello zucchero
    double volume_finale_target = volume_alcol / (gradazioneDesiderata / 100.0);
    t.massaZucchero = dolcezzaDesiderata * volume_finale_target;

    // Ricerca binaria per trovare la massa d’acqua giusta
    double low = 0.0;
    double high = 3000.0;
    double massaAcqua = (low + high) / 2.0;
    double gradazioneCorrente = 0.0;

    for (int i = 0; i < 200; ++i) { // limite massimo iterazioni
        t.massaAcqua = massaAcqua;
        gradazioneCorrente = t.calcolaGradazione();

        if (((gradazioneCorrente > gradazioneDesiderata) ? (gradazioneCorrente- gradazioneDesiderata) : (gradazioneDesiderata- gradazioneCorrente)) < 0.001)
            break;

        // Aggiorna intervallo in base all’errore
        if (gradazioneCorrente > gradazioneDesiderata)
            low = massaAcqua;
        else
            high = massaAcqua;

        massaAcqua = (low + high) / 2.0;
    }

    t.massaAcqua = massaAcqua;
    return t;
}
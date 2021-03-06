//Definizione struct prenotazioni - da modificare
typedef struct prenotazione Prenotazione;

Prenotazione *letturaPrenotazioni(FILE *fp, Utente *testaUtente, Mostra *testaMostra);

void registrazionePrenotazione(Prenotazione *testa, Utente *utente, Mostra *mostra);

void modificaPrenotazione(Prenotazione *testa, Prenotazione *prenotazione);

void eliminaPrenotazione(Prenotazione *testa, Prenotazione *prenotazione);

void scriviPrenotazioni(Prenotazione *testa);

void stampaPrenotazioni(Prenotazione *testa);

void stampaPrenotazione(Prenotazione *prenotazione);

Prenotazione *ricercaPrenotazione(Prenotazione *testa, int id);

bool prenotazioneModificabile(Prenotazione *prenotazione);

#include "prenotazione.c"

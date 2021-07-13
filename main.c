#define BUFFER_SIZE 1024

//librerie generali
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

//NOME DIVERSO? O LASCIARE IN MAIN.C? DOBBIAMO CREARE UN DATA.H?
#include "data.c"

#include "functions.h"
#include "utente.h"
#include "mostra.h"
#include "opera.h"
#include "prenotazione.h"

int main() {

    titolo();

    char scelta, scelta2;
    char sceltaGestP, sceltaGestM, sceltaGestO, sceltaGestPren;
    char email[60];
    
    /*TODO: forse non servono
    int nMostra, nOpera;
    long sizeM;
    long sizeO;
     */

    Utente       *testaUtente        = NULL;
    Mostra       *testaMostra        = NULL;
    Opera        *testaOpera         = NULL;
    Prenotazione *testaPrenotazioni  = NULL;

    Utente       *utenteLogin        = NULL; //utente che avrà eseguito il login
    Mostra       *mostraScelta       = NULL;
    Opera        *operaScelta        = NULL;
   // Prenotazione *prenotazioneScelta = NULL; TODO: forse non serve
    
    //Lettura utenti dal file
    FILE *fpU;
    fpU = fopen("utenti.csv", "r");

    //Lettura mostre dal file
    FILE *fpM;
    fpM = fopen("mostre.csv", "r");
    
    //Lettura opere dal file
    FILE *fpO;
    fpO = fopen("opere.csv", "r");

    //Lettura prenotazioni dal file
    FILE *fpP;
    fpP = fopen("prenotazioni.csv", "r");
 
    testaUtente       = letturaUtenti(fpU);
    testaMostra       = letturaMostre(fpM);
    testaOpera        = letturaOpere(fpO);
    testaPrenotazioni = letturaPrenotazioni(fpP, testaUtente, testaMostra);
    
    do {
        
        printf("---HOME---\n");
        printf("1: Login\n");
        printf("2: Registrazione\n");
        printf("0: Chiudi applicazione\n");
        printf("----------\n");
        printf("-> ");
        scanf(" %c", &scelta);
        
        //ripulisco la schermata
        clearConsole();
        titolo();

        scelta = (int)scelta - 48;
        
        switch (scelta) {
            case 1:
                while ('\n' != getchar());

                fseek(fpU, 0, SEEK_END);
                long sizeU = ftell(fpU);

                if(sizeU == 0) { //file vuoto - nessun utente registrato
                    
                    printColor("Attenzione!\n", COLOR_RED);
                    printf("Non ci sono utenti registrati.\n");
                
                } else { //file pieno - utenti registrati presenti
                
                    printf("Email o nickname: ");
                    fgets(email, 60, stdin);
                    email[strlen(email) - 1] = 0;

                    utenteLogin = accesso(testaUtente, email);
                    char *valore = (char *) utenteLogin;

                    if (valore != NULL) {
                        clearConsole();
                        titolo();

                        printColor("Benvenuto nella sezione privata del tuo account\n", COLOR_CYAN);
                        //Operazioni che può effettuare l'utente una volta che ha eseguito il login
                        do {
                            printf("\n---MENU'---\n");
                            printf("1: Visualizza informazioni personali\n");
                            printf("2: Gestione profilo\n");

                            if (utenteLogin->permessi == 2) {
                                //operazioni che può effettuare il dirigente
                                printf("3: Gestione mostre\n");
                                printf("4: Gestione opere\n");
                                printf("5: Modifica permessi\n");
                            } else {
                                //operazioni che può effettuare l'utente base
                                printf("3: Visualizza mostre\n");
                                printf("4: Mostra opere\n");
                                //printf("4: Prenotati ad una mostra\n");
                                //printf("5: Gestione prenotazione\n");
                            }

                            printf("9: Logout\n");
                            printf("0: Chiudi Applicazione\n");
                            printf("----------\n");
                            printf("-> ");
                            scanf(" %c", &scelta2);
                            
                            scelta2 = (int)scelta2 - 48;
                            
                            switch (scelta2) {
                                    
                                case 0:
                                    scelta = 0;
                                    clearConsole();
                                    titolo();
                                    break;
                                    
                                case 1:
                                    clearConsole();
                                    titolo();
                                    stampaUtente(utenteLogin);
                                    break;

                                case 2:
                                    clearConsole();
                                    titolo();
                                    printColor("Gestione profilo\n", COLOR_CYAN);
                                    printf("1: Modifica dati personali\n");
                                    printf("2: Elimina account\n");
                                    printf("0: Torna indietro\n");
                                    printf("----------\n");
                                    printf("-> ");
                                    scanf("%c", &sceltaGestP);
                                    
                                    sceltaGestP = (int)sceltaGestP - 48;
                                    
                                    clearConsole();
                                    titolo();
                                    
                                    switch (sceltaGestP) {
                                        case 1:
                                            while ('\n' != getchar());
                                            stampaUtente(utenteLogin);
                                            modificaUtente(utenteLogin, testaUtente);
                                            break;
                                        
                                        case 2:
                                            eliminaUtente(utenteLogin, testaUtente);
                                            break;
                                            
                                        default:
                                            break;
                                    }
                                    break;

                                case 3:
                                    clearConsole();
                                    titolo();

                                    while ('\n' != getchar());

                                    if (utenteLogin->permessi == 2) {
                                        printColor("Gestione mostra\n", COLOR_CYAN);
                                        printf("1: Aggiungi dati mostra\n");
                                        printf("2: Modifica dati mostra\n");
                                        printf("3: Cancella dati mostra\n");
                                        printf("0: Torna indietro\n");
                                        printf("----------\n");
                                        printf("-> ");
                                        scanf("%c", &sceltaGestM);
                                        
                                        sceltaGestM = (int)sceltaGestM - 48;
                                        
                                        clearConsole();
                                        titolo();
                                        
                                        switch (sceltaGestM) {
                                            
                                            case 1:
                                                browserMostra(fpM, testaMostra, false);
                                                break;

                                            case 2:
                                                //while ('\n' != getchar());
                                                aggiungiMostra(testaMostra);
                                                break;
                                            
                                            case 3:
                                                mostraScelta = browserMostra(fpM, testaMostra, true);
                                                
                                                if(mostraScelta != NULL) {
                                                    modificaMostra(testaMostra, mostraScelta);
                                                }
                                                break;
                                                
                                            case 4:
                                                mostraScelta = browserMostra(fpM, testaMostra, true);
                                                
                                                if(mostraScelta != NULL) {
                                                    eliminaMostra(testaMostra, mostraScelta);
                                                }
                                                break;
                                                
                                            default:
                                                break;
                                        }
                                        
                                    } else {
                                        browserMostra(fpM, testaMostra, false);
                                    }
                                    
                                    break;

                                case 4:
                                    clearConsole();
                                    titolo();

                                    while ('\n' != getchar());

                                    if (utenteLogin->permessi == 2) {
                                        
                                        printColor("Gestione opera\n", COLOR_CYAN);
                                        printf("1: Sfoglia le opere\n");
                                        printf("2: Aggiungi dati opera\n");
                                        printf("3: Modifica dati opera\n");
                                        printf("4: Cancella dati opera\n");
                                        printf("0: Torna indietro\n");
                                        printf("----------\n");
                                        printf("-> ");
                                        scanf("%c", &sceltaGestO);
                                        
                                        sceltaGestO = (int)sceltaGestO - 48;
                                        
                                        clearConsole();
                                        titolo();
                                        
                                        switch (sceltaGestO) {
                                            case 1:
                                                browserOpere(fpO, testaOpera, false);
                                                break;

                                            case 2:
                                                //while ('\n' != getchar());
                                                aggiungiOpera(testaOpera);
                                                break;
                                            
                                            case 3:
                                                operaScelta = browserOpere(fpO, testaOpera, true);
                                                
                                                if(operaScelta != NULL) {
                                                    modificaOpera(testaOpera, operaScelta);
                                                }
                                                break;
                                                
                                            case 4:
                                                operaScelta = browserOpere(fpO, testaOpera, true);
                                                printf("test\n");
                                                if(operaScelta != NULL) {
                                                    eliminaOpera(testaOpera, operaScelta);
                                                }
                                                break;
                                                
                                            default:
                                                break;
                                        }
                                        
                                    } else {
                                        browserOpere(fpO, testaOpera, false);
                                    }
                                    break;
                                    
                                case 5:
                                    clearConsole();
                                    titolo();

                                    while ('\n' != getchar());

                                    if (utenteLogin->permessi == 2) {
                                        modificaPermessi(testaUtente);
                                    } else {
                                        //gestione prenotazione (modifica e elimina)
                                    }
                                
                                case 9:
                                    clearConsole();
                                    titolo();
                                    break;
                                    
                                default:
                                    break;
                            }

                        } while (scelta2 != 9 /*&& sceltaGestP != 2 */&& scelta2 != 0);
                    }
                }
                break;

            case 2:
                printColor("Benvenuto! \nCrea il tuo account\n", COLOR_CYAN);
                registrazioneUtente(testaUtente);
                clearConsole();
                titolo();
                break;

            default:
                break;
        }
        printColor("-----------------------------\n", COLOR_CYAN);

    } while (scelta != 0);

    printf("\n");
    return 0;
}

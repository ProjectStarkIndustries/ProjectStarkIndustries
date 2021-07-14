/**
 * Function: letturaPrenotazioni
 * ----------------------------
 *   Permette di leggere i dati dal file "prenotazioni.csv" e salvarli all'interno della struct Prenotazione
 *
 *   @param fp : nome del file da cui leggere i dati, ovvero "prenotazioni.csv"
 *   @param testaUtente : lista utente
 *   @param testaMostra : lista mostra
 *
 *   @returns: //
 */
Prenotazione *letturaPrenotazioni(FILE *fp, Utente *testaUtente, Mostra *testaMostra) {
    int colonna = 0;
    char buf[BUFFER_SIZE];

    Prenotazione *testaPrenotazione = NULL;
    Prenotazione *tempPrenotazione  = NULL; //temporanea
    Prenotazione *precPrenotazione  = NULL;

    if (fp == NULL) {
        printColor("\t\t\t|--------------------------------|\n", COLOR_RED);
        printColor("\t\t\t|File \"prenotazioni\" non trovato!|\n", COLOR_RED);
        printColor("\t\t\t|\t\t...              |\n", COLOR_RED);
        printColor("\t\t\t|       File in creazione        |\n", COLOR_RED);
        printColor("\t\t\t|--------------------------------|\n", COLOR_RED);
    } else {
        while (!feof(fp)) {
            fgets(buf, BUFFER_SIZE, fp);
            tempPrenotazione = (Prenotazione *) malloc(sizeof(Prenotazione));
            tempPrenotazione->nextPrenotazione = NULL;

            if (precPrenotazione != NULL) {
                precPrenotazione->nextPrenotazione = tempPrenotazione;
            } else {
                testaPrenotazione = tempPrenotazione;
            }

            char *tok;
            tok = strtok(buf, ",");

            while (tok) {
                if (colonna == 0) {
                    tempPrenotazione->id = atoi(tok);
                }
                if (colonna == 1) {
                    strcpy(tempPrenotazione->data, tok);
                    tempPrenotazione->data[strlen(tempPrenotazione->data)] = 0;
                }
                if (colonna == 2) {
                    strcpy(tempPrenotazione->ora, tok);
                    tempPrenotazione->ora[strlen(tempPrenotazione->ora)] = 0;
                }
                if (colonna == 3) {
                    tempPrenotazione->utente = ricercaUtente(testaUtente,atoi(tok));
                }
                if (colonna == 4) {
                    tempPrenotazione->mostra = ricercaMostra(testaMostra,atoi(tok));
                }
                tok = strtok(NULL, ",");
                colonna++;
            }
            colonna = 0;
            precPrenotazione = tempPrenotazione;
        }
    }
    return testaPrenotazione;
}

/**
 * Function: registrazionePrenotazione
 * ----------------------------
 *   Permette agli utenti di prenotare una visita ad una mostra in un determinato giorno e orario
 *
 *   @param testa : lista prenotazione
 *   @param utente : utente che ha effettuato il login
 *   @param mostra : mostra scelta
 *
 *   @returns: //
 */
void registrazionePrenotazione(Prenotazione *testa, Utente *utente, Mostra *mostra) {
    
    Prenotazione *curr, *prec;
    prec = NULL;
    curr = testa;

    int ultimoID = 0;
    bool continuaInserimento = true;

    bool dataCorretta = true;
    int giorno, mese = 0, anno = 0, ora, minuti;

    Prenotazione *nuovoNodo = NULL;
    nuovoNodo = (Prenotazione *) malloc(sizeof(Prenotazione));

    FILE *fp;
    fp = fopen("prenotazioni.csv", "a+"); //apertura file

    

    consoleColor(COLOR_RED);
    printf("\t\t\t|-----------------------------|\n");
    printf("\t\t\t|         Attenzione!         |\n");
    printf("\t\t\t|   Se hai sbagliato e vuoi   |\n");
    printf("\t\t\t|       tornare al menu'      |\n");
    printf("\t\t\t|      premere il tasto 0     |\n");
    printf("\t\t\t|-----------------------------|\n");
    consoleColor(COLOR_RESET);

    printf("Inserisci data di prenotazione\n");
    
    do {
        if (!dataCorretta) {
            clearConsole();
            titolo();
            printColor("\nAttenzione!\n", COLOR_RED);
            printf("La data inserita non e' corretta.\nSi prega di inserirla nuovamente\n\n");
        }
        
        do {
            printf("Giorno: ");
            scanf("%d", &giorno);
            
            if(giorno == 0) {
                continuaInserimento = false;
                break;
            }
            
        } while (giorno < 1 || giorno > 31);
        
        if(continuaInserimento) {
            do {
                printf("Mese: ");
                scanf("%d", &mese);
            } while (mese < 1 || mese > 12);
            
            printf("Anno: ");
            scanf("%d", &anno);
            
            dataCorretta = dataInIntervallo(giorno, mese, anno, mostra->dataInizio, mostra->dataFine);
        }
        
    } while (!dataCorretta);

    snprintf(nuovoNodo->data, 11, "%d/%d/%d", giorno, mese, anno);
    
    printf("-----------------------------\n");
    if(continuaInserimento) {
        do {
            printf("Ora (dalle 9 alle 22): ");
            scanf("%d", &ora);
        } while (ora < 9 || ora > 22);
        
        do {
            printf("Minuti: ");
            scanf("%d", &minuti);
        } while (minuti < 0 || minuti >= 60);

        snprintf(nuovoNodo->ora, 6, "%d:%d", ora, minuti);
        
        nuovoNodo->utente = utente;
        nuovoNodo->mostra = mostra;

        //verifico se nel file ci sono già delle prenotazioni registrate o meno
        fseek(fp, 0, SEEK_END);
        long size = ftell(fp);
        
        ultimoID = letturaUltimoID("prenotazioni.csv") + 1;
        
        //ricerca della posizione di inserimento
        while (curr != NULL && ultimoID > curr->id) {
            prec = curr;
            curr = curr->nextPrenotazione;
        }
        
        if (size == 0) { //file vuoto
            nuovoNodo->id = 0;
            fprintf(fp, "%d,%s,%s,%d,%d", nuovoNodo->id, nuovoNodo->data, nuovoNodo->ora, nuovoNodo->utente->id, nuovoNodo->mostra->id);
            
        } else { //file pieno
            nuovoNodo->id = ultimoID;
            fprintf(fp, "\n%d,%s,%s,%d,%d", nuovoNodo->id, nuovoNodo->data, nuovoNodo->ora, nuovoNodo->utente->id, nuovoNodo->mostra->id);
        }
        
        fclose(fp);

        //aggiornamento dei collegamenti
        if (prec == NULL) {
            nuovoNodo->nextPrenotazione = testa;
            testa = nuovoNodo;
        } else {
            prec->nextPrenotazione = nuovoNodo;
            nuovoNodo->nextPrenotazione = curr;
        }
        
        clearConsole();
        titolo();
        printColor("Prenotazione avvenuta con successo.\n", COLOR_GREEN);
        pausa();
    }
}

void modificaPrenotazione(Prenotazione *testa, Prenotazione *prenotazione) {
    int scelta;
    char risposta = '\0';
    bool flagDate = false;
    bool continuaModifica = true;
    
    bool dataCorretta = true;
    int giorno = 0, mese = 0, anno = 0;
    int ora, minuti;

    do {
        
        clearConsole();
        titolo();
        //while ('\n' != getchar());
        
        //elenco campi modificabili
        printf("Scegliere il campo da modificare\n");
        printf("----------\n");
        printf("1: Data\n");
        printf("2: Ora\n");
        printf("0: Annulla\n");
        printf("----------\n");
        printf("-> ");
        scanf("%d", &scelta);
        printf("\n");
        while ('\n' != getchar());
        
        clearConsole();
        titolo();
        
        switch (scelta) {
            case 0:
                break;

            case 1:;
                char data[11];
                
                clearConsole();
                printColor("Dati prenotazione.\n", COLOR_CYAN);
                stampaPrenotazione(prenotazione);
                printColor("--------------------------\n", COLOR_CYAN);
                
                consoleColor(COLOR_RED);
                printf("\t\t\t|-----------------------------|\n");
                printf("\t\t\t|         Attenzione!         |\n");
                printf("\t\t\t|   Se hai sbagliato e vuoi   |\n");
                printf("\t\t\t|       tornare al menu'      |\n");
                printf("\t\t\t|      premere il tasto 0     |\n");
                printf("\t\t\t|-----------------------------|\n");
                consoleColor(COLOR_RESET);
                
                do {
                    continuaModifica = true;
                    if (!dataCorretta) {
                        clearConsole();
                        titolo();
                        printf("\n----------");
                        printColor("\nAttenzione!\n", COLOR_RED);
                        printf("La data inserita non e' corretta.\nSi prega di inserirla nuovamente.\n");
                    }
                    
                    printf("----------\n");
                    printColor("Attenzione!\n", COLOR_RED);
                    printf("La mostra si svolge dal ");
                    printColor(prenotazione->mostra->dataInizio, COLOR_CYAN);
                    printf(" al ");
                    printColor(prenotazione->mostra->dataFine, COLOR_CYAN);
                    printf("\nSi prega di inserire una data in questo intervallo.\n");
                    printf("----------\n\n");
                    
                    printf("Inserisci la nuova data:\n");
                    
                    do {
                        printf("Giorno: ");
                        scanf("%d", &giorno);
                        if(giorno == 0) {
                            continuaModifica = false;
                            break;
                        }
                        
                    } while (giorno < 1 || giorno > 31);
                    
                    if(continuaModifica) {
                        do {
                            printf("Mese: ");
                            scanf("%d", &mese);
                        } while (mese < 1 || mese > 12);
                        
                        printf("Anno: ");
                        scanf("%d", &anno);
                        
                        dataCorretta = dataInIntervallo(giorno, mese, anno, prenotazione->mostra->dataInizio, prenotazione->mostra->dataFine);
                    }
                    
                } while (!dataCorretta);
                
                if(continuaModifica) {
                    snprintf(data, 11, "%d/%d/%d", giorno, mese, anno);
                    strcpy(prenotazione->data, data);
                }
                
                break;
                
            case 2:
                clearConsole();
                printColor("Dati prenotazione.\n", COLOR_CYAN);
                stampaPrenotazione(prenotazione);
                printColor("--------------------------\n", COLOR_CYAN);
                
                consoleColor(COLOR_RED);
                printf("\t\t\t|-----------------------------|\n");
                printf("\t\t\t|         Attenzione!         |\n");
                printf("\t\t\t|   Se hai sbagliato e vuoi   |\n");
                printf("\t\t\t|       tornare al menu'      |\n");
                printf("\t\t\t|      premere il tasto 0     |\n");
                printf("\t\t\t|-----------------------------|\n");
                consoleColor(COLOR_RESET);
                
                
                do {
                    printf("Ora (dalle 9 alle 22): ");
                    scanf("%d", &ora);
                    if(ora == 0) {
                        continuaModifica = false;
                        break;
                    }
                    
                } while (ora < 9 || ora > 22);
                
                if(continuaModifica) {
                    do {
                        printf("Minuti: ");
                        scanf("%d", &minuti);
                    } while (minuti < 0 || minuti >= 60);

                    snprintf(prenotazione->ora, 6, "%d:%d", ora, minuti);
                }
                break;
                
              
            default:
                break;
        }
        
        if (scelta != 0 && continuaModifica) {
            do {
                printf("----------\n");
                printf("Vuoi modificare un altro campo? (s/n): ");
                while ('\n' != getchar());
                risposta = getchar();
                while ('\n' != getchar());
                
                //rendo la risposta in maiuscolo per evitare errori
                risposta = toupper(risposta);
                
                if (risposta == 'N') {
                    scriviPrenotazioni(testa);
                }
                
            } while (risposta != 'S' && risposta != 'N');
        } else {
            scriviPrenotazioni(testa);
        }
        
        clearConsole();
        titolo();
    } while (risposta == 'S' && scelta != 0);
}

//stampa a video
void stampaPrenotazioni(Prenotazione *testa) {
    for (Prenotazione *temp = testa; temp != NULL; temp = temp->nextPrenotazione) {
        stampaPrenotazione(temp);
        printf("----------\n");
    }
}

void stampaPrenotazioniUtente(Prenotazione *testa, Utente *utente) {
    bool trovato = false;
    
    for (Prenotazione *temp = testa; temp != NULL; temp = temp->nextPrenotazione) {
        if (temp->utente->id == utente->id) {
            stampaPrenotazione(temp);
            trovato = true;
            printf("----------\n");
        }
    }
    if(!trovato) {
        printf("\n----------\n");
        printColor("Attenzione!\n", COLOR_RED);
        printf("Non hai effettuato nessuna prenotazione.\n");
        printf("----------\n\n");
    }
}

void stampaPrenotazione(Prenotazione *prenotazione) {
    printf("Id: %d\n", prenotazione->id);
    printf("Utente: %s %s\n", prenotazione->utente->nome, prenotazione->utente->cognome);
    printf("Mostra: %s - %s\n", prenotazione->mostra->citta, prenotazione->mostra->indirizzo);
    printf("Prenotazione in data: %s\n", prenotazione->data);
    printf("Ora: %s\n", prenotazione->ora);
}

//scrittura su file
void scriviPrenotazioni(Prenotazione *testa) {
    FILE *fp;
    fp = fopen("prenotazioni.csv", "w"); //apertura file

    for (Prenotazione *temp = testa; temp != NULL; temp = temp->nextPrenotazione) {
        long size = ftell(fp);
        
        if (size == 0) { //file vuoto
            fprintf(fp, "%d,%s,%s,%d,%d", temp->id, temp->data, temp->ora, temp->utente->id, temp->mostra->id);
        } else { //file pieno
            fprintf(fp, "\n%d,%s,%s,%d,%d", temp->id, temp->data, temp->ora, temp->utente->id, temp->mostra->id);
        }
    }
    fclose(fp);
}


Prenotazione *ricercaPrenotazione(Prenotazione *testa, int id) {
    bool flag = false;
    Prenotazione *nuovoNodo = NULL;

    for (Prenotazione *temp = testa; temp != NULL; temp = temp->nextPrenotazione) {
        if (temp->id == id) {
            nuovoNodo = temp;
            flag = true;
            break;
        }
    }

    if (!flag) {
        printf("\n----------\n");
        printColor("Attenzione!\n", COLOR_RED);
        printf("Prenotazione non trovata.\n");
        printf("----------\n\n");
    }

    return nuovoNodo;
}

bool prenotazioneModificabile(Prenotazione *prenotazione) {

    int data[3];
    char dataPrenotazione[11];
    
    strcpy(dataPrenotazione, prenotazione->data);

    char *tok = strtok(dataPrenotazione, "/");

    for (int i = 0; i < 3; i++ ) {
        data[i] = atoi(tok);
        tok = strtok(NULL, "/");
    }

    data[0] = data[0] - 2;
    if (data[0]<1) {
        int giorniDaSottrarre = data[0];
        data[1]--;
        if (data[1]<1) {
            data[2]--;
            data[1]=12;
        }
        if (data[1] == 2) {
            data[0] = (annoBisestile(data[1]) ? 29 : 28 ) + giorniDaSottrarre;
        } else {
            switch(data[1]) {
                case 4:
                case 6:
                case 9:
                case 11:
                    data[0] = 30 + giorniDaSottrarre;
                    break;

                default:
                    data[0] = 31 + giorniDaSottrarre;
                    break;
            }
        }
    }

    return (differenzaDateOggi(data[0], data[1], data[2]) == 1);
}

void eliminaPrenotazione(Prenotazione *testa, Prenotazione *prenotazione) {
    char risposta;
    Prenotazione *curr, *prec;
    Prenotazione *temp;
    
    temp = prenotazione;
    prec = NULL;
    curr = testa;
    
    clearConsole();
    titolo();
    
    if(prenotazioneModificabile(prenotazione)) {
        do {
            
            //while ('\n' != getchar());
            printColor("ATTENZIONE!\n", COLOR_RED);
            printf("Sei sicuro/a di voler eliminare la prenotazione?\n");
            printf("Risposta (s/n): ");
            scanf("%c", &risposta);
            printf("\n");
            
            //rendo la risposta tutta maiuscola per evitare errori
            risposta = toupper(risposta);
        } while (risposta != 'S' && risposta != 'N');
        
        clearConsole();
        titolo();
        
        if (risposta == 'S') {
            while (curr != NULL && temp->id != curr->id) {
                prec = curr;
                curr = curr->nextPrenotazione;
            }
            
            if (temp->id == curr->id) {
                if (prec == NULL) {
                    //elemento trovato in testa
                    testa = curr->nextPrenotazione;
                } else {
                    //elemento al centro della lista
                    prec->nextPrenotazione = curr->nextPrenotazione;
                }
                free(curr);
            }
            scriviPrenotazioni(testa);
            printColor("Eliminazione completata con successo!\n", COLOR_GREEN);
            
        }
    } else {
        
        printf("\n----------\n");
        printColor("Attenzione!\n", COLOR_RED);
        printf("I termini per la cancellazione della prenotazione sono scaduti.\n");
        printf("----------\n\n");
    }
}

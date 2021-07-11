Mostra *letturaMostre(FILE *fp) {
    
    //Lettura mostre dal file
    int colonna1 = 0;
    char buf[BUFFER_SIZE];
    
    Mostra *testaMostra = NULL;
    Mostra *tempMostra  = NULL; //temporanea
    Mostra *tempMostra1 = NULL;
    
    if (fp == NULL) {
        printColor("\t\t\t|-----------------------------|\n", COLOR_RED);
        printColor("\t\t\t|  File \"mostre\" non trovato! |\n", COLOR_RED);
        printColor("\t\t\t|             ...             |\n", COLOR_RED);
        printColor("\t\t\t|      File in creazione      |\n", COLOR_RED);
        printColor("\t\t\t|-----------------------------|\n", COLOR_RED);
    } else {
        while (!feof(fp)) {
            fgets(buf, BUFFER_SIZE, fp);
            tempMostra = (Mostra *) malloc(sizeof(Mostra));
            tempMostra->nextMostra = NULL;
            
            if (tempMostra1 != NULL) {
                tempMostra1->nextMostra = tempMostra;
            } else {
                testaMostra = tempMostra;
            }
            
            char *tok2;
            tok2 = strtok(buf, ",");
            
            while (tok2) {
                if (colonna1 == 0) {
                    tempMostra->id = atoi(tok2);
                }
                if (colonna1 == 1) {
                    strcpy(tempMostra->responsabile, tok2);
                    tempMostra->responsabile[strlen(tempMostra->responsabile)] = 0;
                }
                if (colonna1 == 2) {
                    strcpy(tempMostra->luogo, tok2);
                    tempMostra->luogo[strlen(tempMostra->luogo)] = 0;
                }
                if (colonna1 == 3) {
                    strcpy(tempMostra->citta, tok2);
                    tempMostra->citta[strlen(tempMostra->citta)] = 0;
                }
                if (colonna1 == 4) {
                    strcpy(tempMostra->indirizzo, tok2);
                    tempMostra->indirizzo[strlen(tempMostra->indirizzo)] = 0;
                }
                if (colonna1 == 5) {
                    strcpy(tempMostra->dataInizio, tok2);
                    tempMostra->dataInizio[strlen(tempMostra->dataInizio)] = 0;
                }
                if (colonna1 == 6) {
                    strcpy(tempMostra->dataFine, tok2);
                    tempMostra->dataFine[strlen(tempMostra->dataFine)] = 0;
                }
                if (colonna1 == 7) {
                    tempMostra->nOpere = atoi(tok2);
                }
                tok2 = strtok(NULL, ",");
                colonna1++;
            }
            colonna1 = 0;
            tempMostra1 = tempMostra;
        }
    }
    
    return testaMostra;
    
}

void aggiungiMostra(Mostra *testa) {
    
    Mostra *curr, *prec;
    prec = NULL;
    curr = testa;
    
    bool continuaInserimento = true;
    bool testInput = false; //flag per controllare i vari input
    bool flagDate = false;
    char dataIn[11];
    bool dataCorrettaIn = true;
    int giornoIn, meseIn, annoIn;
    int ultimoID = 0, i;
    
    char dataFin[11];
    bool dataCorrettaFin = true;
    int giornoFin, meseFin, annoFin;
    
    Mostra *nuovoNodo = NULL;
    
    
    nuovoNodo = (Mostra *) malloc(sizeof(Mostra));
    
    FILE *fp;
    fp = fopen("mostre.csv", "a+"); //apertura file
    
    notificaAnnulla();
    
    do {
        testInput = false;
        printf("Inserisci il responsabile: ");
        fgets(nuovoNodo->responsabile, 30, stdin);
        nuovoNodo->responsabile[strlen(nuovoNodo->responsabile) - 1] = 0;
        nuovoNodo->responsabile[0] = toupper(nuovoNodo->responsabile[0]);
        
        if(strlen(nuovoNodo->responsabile) == 0) {
            continuaInserimento = false;
            clearConsole();
            titolo();
            break;
        }
        
        for(i=0; i<strlen(nuovoNodo->responsabile); i++) {
            if(isalpha(nuovoNodo->responsabile[i]) == 0) {
                testInput = true; //carattere non alfabetico
            }
        }
        
        if(testInput) {
            clearConsole();
            titolo();
            printf("\n----------");
            printColor("\nAttenzione!\n", COLOR_RED);
            printf("Responsabile non valido.\n");
            printf("----------\n\n");
        }
    } while (testInput);
    
    if(continuaInserimento) {
        
        clearConsole();
        titolo();
        
        do {
            testInput = false;
            printf("Inserisci il luogo: ");
            fgets(nuovoNodo->luogo, 25, stdin);
            nuovoNodo->luogo[strlen(nuovoNodo->luogo) - 1] = 0;
            nuovoNodo->luogo[0] = toupper(nuovoNodo->luogo[0]);
            
            for(i=0; i<strlen(nuovoNodo->luogo); i++) {
                if(isalpha(nuovoNodo->luogo[i]) == 0) {
                    testInput = true; //carattere non alfabetico
                }
            }
            
            if(testInput || strlen(nuovoNodo->luogo) == 0) {
                clearConsole();
                titolo();
                printf("\n----------");
                printColor("\nAttenzione!\n", COLOR_RED);
                printf("Luogo non valido.\n");
                printf("----------\n\n");
            }
        } while (testInput || strlen(nuovoNodo->luogo) == 0);
        
        printf("-----------------------------\n");
        
        do {
            testInput = false;
            printf("Inserisci Citta': ");
            fgets(nuovoNodo->citta, 20, stdin);
            nuovoNodo->citta[strlen(nuovoNodo->citta) - 1] = 0;
            nuovoNodo->citta[0] = toupper(nuovoNodo->citta[0]);
            
            for(i=0; i<strlen(nuovoNodo->citta); i++) {
                if(isalpha(nuovoNodo->citta[i]) == 0) {
                    testInput = true; //carattere non alfabetico
                }
            }
            
            if(testInput || strlen(nuovoNodo->citta) == 0) {
                clearConsole();
                titolo();
                printf("\n----------");
                printColor("\nAttenzione!\n", COLOR_RED);
                printf("Citta' non valida.\n");
                printf("----------\n\n");
            }
        } while (testInput || strlen(nuovoNodo->luogo) == 0);
        
        printf("-----------------------------\n");
        
        do {
            printf("Inserisci Indirizzo: ");
            fgets(nuovoNodo->indirizzo, 20, stdin);
            nuovoNodo->indirizzo[strlen(nuovoNodo->indirizzo) - 1] = 0;
            nuovoNodo->indirizzo[0] = toupper(nuovoNodo->indirizzo[0]);
            
            if(strlen(nuovoNodo->indirizzo) == 0) {
                testInput = true;
                clearConsole();
                titolo();
                printf("\n----------");
                printColor("\nAttenzione!\n", COLOR_RED);
                printf("Indirizzo non valido.\n");
                printf("----------\n\n");
            }
        } while (testInput);
        
        printf("-----------------------------\n");
        
        do {
            printf("Inserisci data d'");
            printColor("inizio ", COLOR_CYAN);
            printf("mostra\n");
            
            do {
                if (!dataCorrettaIn) {
                    printColor("\nAttenzione!\n", COLOR_RED);
                    printf("La data inserita non e' corretta.\nSi prega di inserirla nuovamente\n\n");
                }
                
                do {
                    printf("Giorno: ");
                    scanf("%d", &giornoIn);
                } while (giornoIn < 1 || giornoIn > 31);
                
                do {
                    printf("Mese: ");
                    scanf("%d", &meseIn);
                } while (meseIn < 1 || meseIn > 12);
                
                do {
                    printf("Anno (dal 1900 in poi): ");
                    scanf("%d", &annoIn);
                } while (annoIn < 1900);
                
                dataCorrettaIn = verificaData(giornoIn, meseIn, annoIn);
                
            } while (!dataCorrettaIn);
            
            while ('\n' != getchar());
            
            snprintf(dataIn, 11, "%d/%d/%d", giornoIn, meseIn, annoIn);
            
            printf("-----------------------------\n");
            
            printf("\nInserisci data di ");
            printColor("fine ", COLOR_CYAN);
            printf("mostra\n");
            
            do {
                if (!dataCorrettaFin) {
                    printColor("\nAttenzione!\n", COLOR_RED);
                    printf("La data inserita non e' corretta.\nSi prega di inserirla nuovamente\n\n");
                }
                
                do {
                    printf("Giorno: ");
                    scanf("%d", &giornoFin);
                } while (giornoFin < 1 || giornoFin > 31);
                
                do {
                    printf("Mese: ");
                    scanf("%d", &meseFin);
                } while (meseFin < 1 || meseFin > 12);
                
                do {
                    printf("Anno (dal 1900 in poi): ");
                    scanf("%d", &annoFin);
                } while (annoFin < 1900);
                
                dataCorrettaFin = verificaData(giornoFin, meseFin, annoFin);
                
            } while (!dataCorrettaFin);
            
            while ('\n' != getchar());
            
            snprintf(dataFin, 11, "%d/%d/%d", giornoFin, meseFin, annoFin);
            
            printf("\n");
            if (differenzaDate(giornoIn, meseIn, annoIn, giornoFin, meseFin, annoFin)) {
                flagDate = true;
            } else {
                printColor("Attenzione!\n", COLOR_RED);
                printf("La data di fine mostra deve susseguire la data d'inizio.\n");
                printf("Si prega di inserire nuovamente le date.\n\n");
            }
        } while (!flagDate);
        strcpy(nuovoNodo->dataInizio, dataIn);
        strcpy(nuovoNodo->dataFine, dataFin);
        
        printf("-----------------------------\n");
        
        printf("Inserisci Il Numero delle Opere: ");
        scanf("%d", &nuovoNodo->nOpere);
        printf("\n");
        
        
        //verifico se nel file ci sono già delle mmostre registrate o meno
        fseek(fp, 0, SEEK_END);
        long size = ftell(fp);
        
        ultimoID = letturaUltimoID("mostre.csv") + 1;
        
        //ricerca della posizione di inserimento
        while (curr != NULL && ultimoID > curr->id) {
            prec = curr;
            curr = curr->nextMostra;
        }
        
        if (size == 0) { //file vuoto
            
            nuovoNodo->id = 0;
            
            fprintf(fp, "%d,%s,%s,%s,%s,%s,%s,%d", nuovoNodo->id, nuovoNodo->responsabile, nuovoNodo->luogo,
                    nuovoNodo->citta, nuovoNodo->indirizzo, nuovoNodo->dataInizio, nuovoNodo->dataFine, nuovoNodo->nOpere);
            
        } else { //file pieno
            
            nuovoNodo->id = ultimoID;
            
            fprintf(fp, "\n%d,%s,%s,%s,%s,%s,%s,%d", nuovoNodo->id, nuovoNodo->responsabile, nuovoNodo->luogo,
                    nuovoNodo->citta, nuovoNodo->indirizzo, nuovoNodo->dataInizio, nuovoNodo->dataFine, nuovoNodo->nOpere);
        }
        
        fclose(fp);
        
        //aggiornamento dei collegamenti
        if (prec == NULL) {
            nuovoNodo->nextMostra = testa;
            testa = nuovoNodo;
        } else {
            prec->nextMostra = nuovoNodo;
            nuovoNodo->nextMostra = curr;
        }
    }
}

void modificaMostra(Mostra *testa, Mostra *mostra) {
    int scelta, colonna = 0;
    char risposta = '\0';
    bool flagDate = false;
    bool continuaModifica = true;
    
    Mostra *temp = NULL;
    temp = mostra;
    
    char responsabile[30];
    char luogo[25];
    char citta[20];
    char indirizzo[30];
    
    
    
    //int nOpere = 0;
    
    char dataIn[11];
    bool dataCorrettaIn = true;
    int giornoIn = 0, meseIn = 0, annoIn = 0;
    
    char dataFin[11];
    bool dataCorrettaFin = true;
    int giornoFin = 0, meseFin = 0, annoFin = 0;
    
    printColor("\nDati relativi alla mostra scelta:\n", COLOR_CYAN);
    printf("Id: %d\n", temp->id);
    printf("Responsabile: %s\n", temp->responsabile);
    printf("Luogo di esposizione: %s\n", temp->luogo);
    printf("Citta': %s\n", temp->citta);
    printf("Indirizzo: %s\n", temp->indirizzo);
    printf("Data inizio mostra: %s\n", temp->dataInizio);
    printf("Data fine mostra: %s\n", temp->dataFine);
    //printf("Numero opere esposte: %d\n", temp->nOpere);
    printColor("----------\n\n", COLOR_CYAN);
    
    do {
        while ('\n' != getchar());
        
        //elenco campi modificabili
        printf("Scegliere il campo da modificare\n");
        printf("----------\n");
        printf("1: Responsabile\n");
        printf("2: Luogo\n");
        printf("3: Citta'\n");
        printf("4: Indirizzo\n");
        printf("5: Data Inizio\n");
        printf("6: Data Fine\n");
       // printf("7: Numero Opere\n");
        printf("0: Annulla\n");
        printf("----------\n");
        printf("-> ");
        scanf("%d", &scelta);
        printf("\n");
        while ('\n' != getchar());
        
        switch (scelta) {
            case 0:
                break;
                
            case 1:
                clearConsole();
                titolo();
                notificaAnnulla();
                
                printf("Inserisci il responsabile: ");
                fgets(responsabile, 30, stdin);
                responsabile[strlen(responsabile) - 1] = 0;
                responsabile[0] = toupper(responsabile[0]);
                
                if(strlen(responsabile) == 0) {
                    continuaModifica = false;
                    break;
                } else {
                    strcpy(temp->responsabile, responsabile);
                }
                break;
                
            case 2:
                clearConsole();
                titolo();
                notificaAnnulla();
                
                printf("Inserisci il luogo: ");
                fgets(luogo, 25, stdin);
                responsabile[strlen(responsabile) - 1] = 0;
                responsabile[0] = toupper(responsabile[0]);
                
                if(strlen(luogo) == 0) {
                    continuaModifica = false;
                    break;
                } else {
                    strcpy(temp->luogo, luogo);
                }
                break;
                
            case 3:
                clearConsole();
                titolo();
                notificaAnnulla();
                
                printf("Inserisci la citta': ");
                fgets(citta, 20, stdin);
                citta[strlen(citta) - 1] = 0;
                citta[0] = toupper(citta[0]);
                
                if(strlen(citta) == 0) {
                    continuaModifica = false;
                    break;
                } else {
                    strcpy(temp->citta, citta);
                }
                break;
                
            case 4:
                clearConsole();
                titolo();
                notificaAnnulla();
                
                printf("Inserisci l'indirizzo: ");
                fgets(indirizzo, 20, stdin);
                indirizzo[strlen(indirizzo) - 1] = 0;
                indirizzo[0] = toupper(indirizzo[0]);
                
                if(strlen(indirizzo) == 0) {
                    continuaModifica = false;
                    break;
                } else {
                    strcpy(temp->indirizzo, indirizzo);
                }
                break;
                
            case 5:
                flagDate = false;
                
                clearConsole();
                titolo();
                
                consoleColor(COLOR_RED);
                printf("\t\t\t|-----------------------------|\n");
                printf("\t\t\t|         Attenzione!         |\n");
                printf("\t\t\t|   Se hai sbagliato e vuoi   |\n");
                printf("\t\t\t|       tornare al menu'      |\n");
                printf("\t\t\t|      premere il tasto 0     |\n");
                printf("\t\t\t|-----------------------------|\n");
                consoleColor(COLOR_RESET);
                
                do {
                    printf("Inserisci data d'");
                    printColor("inizio ", COLOR_CYAN);
                    printf("mostra\n");
                    
                    do {
                        if (!dataCorrettaIn) {
                            printColor("\nAttenzione!\n", COLOR_RED);
                            printf("La data inserita non e' corretta.\nSi prega di inserirla nuovamente\n\n");
                        }
                        
                        do {
                            printf("Giorno: ");
                            scanf("%d", &giornoIn);
                            
                            if(giornoIn == 0) {
                                continuaModifica = false;
                                flagDate = true;
                                break;
                            }
                            
                        } while (giornoIn < 1 || giornoIn > 31);
                        
                        if(continuaModifica) {
                            
                            do {
                                printf("Mese: ");
                                scanf("%d", &meseIn);
                            } while (meseIn < 1 || meseIn > 12);
                            
                            printf("Anno: ");
                            scanf("%d", &annoIn);
                            
                            dataCorrettaIn = verificaData(giornoIn, meseIn, annoIn);
                        }
                        
                    } while (!dataCorrettaIn);
                    
                    if(continuaModifica) {
                        snprintf(dataIn, 11, "%d/%d/%d", giornoIn, meseIn, annoIn);
                        
                        char *tok;
                        tok = strtok(temp->dataFine, "/");
                        
                        while (tok) {
                            if (colonna == 0) {
                                giornoFin = atoi(tok);
                            }
                            if (colonna == 1) {
                                meseFin = atoi(tok);
                            }
                            if (colonna == 2) {
                                annoFin = atoi(tok);
                            }
                            tok = strtok(NULL, "/");
                            colonna++;
                        }
                        
                        if (differenzaDate(giornoIn, meseIn, annoIn, giornoFin, meseFin, annoFin)) {
                            flagDate = true;
                        } else {
                            printColor("Attenzione!\n", COLOR_RED);
                            printf("La data di fine mostra deve susseguire la data d'inizio.\n");
                            printf("Si prega di inserire nuovamente le date.\n\n");
                        }
                    }
                    
                } while (!flagDate);
                strcpy(temp->dataInizio, dataIn);
                
                break;
                
            case 6:
                flagDate = false;
                do {
                    printf("Inserisci data di fine mostra\n");
                    do {
                        if (!dataCorrettaFin) {
                            printColor("\nAttenzione!\n", COLOR_RED);
                            printf("La data inserita non e' corretta.\nSi prega di inserirla nuovamente\n\n");
                        }
                        
                        do {
                            printf("Giorno: ");
                            scanf("%d", &giornoIn);
                            
                            if(giornoIn == 0) {
                                continuaModifica = false;
                                flagDate = true;
                                break;
                            }
                            
                        } while (giornoIn < 1 || giornoIn > 31);
                        
                        if(continuaModifica) {
                            do {
                                printf("Mese: ");
                                scanf("%d", &meseFin);
                            } while (meseFin < 1 || meseFin > 12);
                            
                            printf("Anno: ");
                            scanf("%d", &annoFin);
                            
                            dataCorrettaFin = verificaData(giornoFin, meseFin, annoFin);
                        }
                        
                    } while (!dataCorrettaFin);
                    
                    if(continuaModifica) {

                        snprintf(dataFin, 11, "%d/%d/%d", giornoFin, meseFin, annoFin);
                        
                        char *tok;
                        tok = strtok(temp->dataInizio, "/");
                        
                        while (tok) {
                            if (colonna == 0) {
                                giornoIn = atoi(tok);
                            }
                            if (colonna == 1) {
                                meseIn = atoi(tok);
                            }
                            if (colonna == 2) {
                                annoIn = atoi(tok);
                            }
                            tok = strtok(NULL, "/");
                            colonna++;
                        }
                        
                        if (differenzaDate(giornoIn, meseIn, annoIn, giornoFin, meseFin, annoFin)) {
                            flagDate = true;
                        } else {
                            printColor("Attenzione!\n", COLOR_RED);
                            printf("La data di fine mostra deve susseguire la data d'inizio.\n");
                            printf("Si prega di inserire nuovamente le date.\n\n");
                        }
                    }
                    
                } while (!flagDate);
                strcpy(temp->dataFine, dataFin);
                
                break;
              
                /*
            case 7:
                printf("Inserisci il numero delle opere: ");
                scanf("%d", &nOpere);
                temp->nOpere = nOpere;
                break;
                 */
                
            default:
                break;
        }
        
        if (scelta != 0 && continuaModifica) {
            do {
                
                printf("Vuoi modificare un altro campo? (s/n): ");
                risposta = getchar();
                while ('\n' != getchar());
                
                //rendo la risposta in maiuscolo per evitare errori
                risposta = toupper(risposta);
                
                if (risposta == 'N') {
                    scriviMostre(testa);
                }
                
            } while (risposta != 'S' && risposta != 'N');
        } else {
            scriviMostre(testa);
        }
        
        clearConsole();
        titolo();
    } while (risposta == 'S' && scelta != 0);
}

//stampa a video
void stampaMostre(Mostra *testa) {
    
    for (Mostra *temp = testa; temp != NULL; temp = temp->nextMostra) {
        printf("Mostra numero: %d \n", temp->id);
        printf("Responsabile: %s \n", temp->responsabile);
        printf("Luogo di esposizione: %s \n", temp->luogo);
        printf("Luogo: %s - %s\n", temp->citta, temp->indirizzo);
        printf("Durata: dal %s al %s\n", temp->dataInizio, temp->dataFine);
        printf("----------\n");
    }
}

//scrittura su file
void scriviMostre(Mostra *testa) {
    Mostra *temp = NULL;
    FILE *fp;
    fp = fopen("mostre.csv", "w"); //apertura file
    
    for (temp = testa; temp != NULL; temp = temp->nextMostra) {
        long size = ftell(fp);
        
        if (size == 0) {
            //file vuoto.
            fprintf(fp, "%d,%s,%s,%s,%s,%s,%s,%d", temp->id, temp->responsabile, temp->luogo, temp->citta,
                    temp->indirizzo, temp->dataInizio, temp->dataFine, temp->nOpere);
        } else {
            //file pieno
            fprintf(fp, "\n%d,%s,%s,%s,%s,%s,%s,%d", temp->id, temp->responsabile, temp->luogo, temp->citta,
                    temp->indirizzo, temp->dataInizio, temp->dataFine, temp->nOpere);
        }
    }
    fclose(fp);
}

void eliminaMostra(Mostra *testa, Mostra *mostra) {
    char risposta;
    Mostra *curr, *prec;
    Mostra *temp = NULL;
    
    temp = mostra;
    prec = NULL;
    curr = testa;
    
    do {
        while ('\n' != getchar());
        printColor("ATTENZIONE!\n", COLOR_RED);
        printf("Sei sicuro/a di voler eliminare la mostra?\n");
        printf("Risposta (s/n): ");
        scanf("%c", &risposta);
        printf("\n");
        
        //rendo la risposta tutta maiuscola per evitare errori
        risposta = toupper(risposta);
        
    } while (risposta != 'S' && risposta != 'N');
    
    if (risposta == 'S') {
        while (curr != NULL && temp->id != curr->id) {
            prec = curr;
            curr = curr->nextMostra;
        }
        
        if (temp->id == curr->id) {
            if (prec == NULL)   //elemento trovato in testa
            {
                testa = curr->nextMostra;
            } else     //elemento al centro della lista
            {
                prec->nextMostra = curr->nextMostra;
            }
            free(curr);
        }
        
        scriviMostre(testa);
        
        clearConsole();
        printColor("Eliminazione completata con successo!\n", COLOR_GREEN);
    }
}


Mostra *ricercaMostra(Mostra *testa, int id) {
    bool flag = false;
    Mostra *nuovoNodo = NULL;
    Mostra *temp;
    
    for (temp = testa; temp != NULL; temp = temp->nextMostra) {
        
        if (temp->id == id) {
            
            nuovoNodo = temp;
            flag = true;
            break;
            
        }
    }
    
    if (!flag) {
        printColor("Attenzione!\n", COLOR_RED);
        printf("Mostra non trovata.");
    }
    
    if (flag)
        return nuovoNodo;
    else
        return NULL;
}

# voting-tools
A set of tools for majority judgement and random election systems

**Autore**: Mauro Fiorentini

  * [Introduzione](#introduzione)
    + [Sicurezza](#sicurezza)
    + [Passaggio dei dati](#passaggio-dei-dati)
    + [Opzioni](#opzioni)
    + [Parallelismo](#parallelismo)
  * [Elezioni tramite sorteggio](#elezioni-tramite-sorteggio)
    + [Procedura di estrazione](#procedura-di-estrazione)
    + [Inizio dell'elezione](#inizio-dell-elezione)
    + [Scelta delle parole chiave da parte dei garanti](#scelta-delle-parole-chiave-da-parte-dei-garanti)
    + [Scelta delle parole chiave da parte dei candidati](#scelta-delle-parole-chiave-da-parte-dei-candidati)
    + [Comunicazione delle parole chiave da parte dei garanti](#comunicazione-delle-parole-chiave-da-parte-dei-garanti)
    + [Lettura dello stato e proclamazione dei risultati](#lettura-dello-stato-e-proclamazione-dei-risultati)
    + [Calcolo dell'hash](#calcolo-dell-hash)
  * [Elezioni tramite *majority judgement*](#elezioni-tramite--majority-judgement-)
    + [Procedura di elezione](#procedura-di-elezione)
    + [Chiavi crittografiche](#chiavi-crittografiche)
    + [Inizio dell'elezione](#inizio-dell-elezione-1)
    + [Ricezione dei voti](#ricezione-dei-voti)
    + [Generazione di dati casuali](#generazione-di-dati-casuali)
    + [Proclamazione dei risultati](#proclamazione-dei-risultati)
- [Messaggi d'errore](#messaggi-d-errore)
  * [Errori fatali](#errori-fatali)
  * [Errori di I/O](#errori-di-i-o)
  * [Errori dell'applicazione](#errori-dell-applicazione)
- [Parametri dei programmi](#parametri-dei-programmi)
  * [Elezioni tramite sorteggio](#elezioni-tramite-sorteggio-1)
  * [Elezioni tramite *majority judgement*](#elezioni-tramite--majority-judgement--1)
  * [License](#license)

## Introduzione

Il sistema di elezioni consta di due gruppi di programmi:

- un gruppo per gestire elezioni tramite sorteggio,
- un gruppo per gestire le elezioni tramite l'algoritmo majority judgement.


Installazione:

- Per fare pulizia: `make clean`
- per generare gli eseguibi: `make all`
- per generare la documentazione tecnica  `make documentation`

Alla documentazione si accede con qualsiasi browser, partendo da html/index.html

**ATTENZIONE: La crittografia NON è abilitata**

### Sicurezza

I programmi non implementano misure di sicurezza: i programmi che comunicano con gli utenti sono responsabili di verificare le credenziali degli utenti e attivare i programmi consentiti con i dati corretti.

I programmi non gestiscono ridondanza e backup, che devono essere implementati esternamente.

### Passaggio dei dati

Nel passare i dati ai programmi devono essere rispettate le seguenti convenzioni:

- le chiavi, le firme e i valori di hash vanno rappresentati in esadecimale, due caratteri per ogni byte, con lunghezza fissa;
- i numeri vanno rappresentati in notazione decimale, sono ammessi zeri in testa, il numero di cifre non è fissato, ma i valori devono essere negli intervalli specificati nei vari casi;
- i nomi di directory devono essere stringhe rappresentanti percorsi di directory valide nel file system, nelle quali i programmi abbiano diritti di creazione di file, lettura e scrittura.

I vari argomenti non possono contenere caratteri estranei, oltre a quelli sopra indicati.

### Opzioni

Tutti i programmi accettano l'opzione facoltativa numeric-errors come primo parametro;

Se tale opzione viene specificata, i messaggi d'errore contengono solo un codice numerico che indica l'errore, altrimenti contengono una breve descrizione dell'errore.

### Parallelismo

Elezioni distinte, che utilizzino directory diverse, possono eseguire contemporaneamente i relativi programmi, senza alcun pericolo di interferenze.

Tutti i programmi, tranne quelli che creano le elezioni, utilizzano meccanismi di mutua esclusione, quindi più istanze possono essere lanciate in parallelo sulla stessa elezione, senza alcun limite.

Se un programma che accetta voti è in esecuzione al momento della chiusura dell'elezione, può concludere regolarmente la sua esecuzione, registrando il voto.

## Elezioni tramite sorteggio

Le elezioni tramite sorteggio permettono di selezionare un numero predefinito di eletti da un insieme di candidati, garantendo la correttezza del sorteggio.

Nell'elezione vi sono 3 parti attive:

- il presidente, i cui unici compiti sono indire l'elezione e dichiarare la chiusura delle votazioni;
- i garanti, il compito dei quali è scegliere le parole chiave, dalle quali dipende l'esito dell'elezione;
- i candidati, il compito (facoltativo) di ciascuno dei quali è scegliere una parola chiave, dalla quale dipenderà il suo piazzamento.

Garanti e candidati sono identificati da un numero progressivo; la corrispondenza tra tali numeri e l'identità delle persone dev'essere gestita separatamente.

Ogni elezione avviene in 4 fasi:

- inizio dell'elezione,
- scelta delle parole chiave da parte dei garanti,
- scelta delle parole chiave da parte dei candidati (facoltativa),
- comunicazione delle parole chiave da parte dei garanti e proclamazione dei vincitori.

Alle fasi corrispondono 4 possibili stati:

- CREATA, dopo l'inizio,
- INIZIATA, dopo la scelta delle parole chiave da parte dei garanti,
- CHIUSA, dopo scelta delle parole chiave da parte dei candidati,
- TERMINATA dopo la comunicazione delle parole chiave da parte dei garanti.

### Procedura di estrazione

La procedura di estrazione degli eletti è studiata per garantire che nessuno possa pilotarne il risultato, che è totalmente casuale.

I garanti inseriscono ciascuno una chiave e l'or esclusivo di tali chiavi determina una chiave di elezione; l'or esclusivo di tale chiave tale con quelle inserite da ciascun candidato costituisce una stringa, diversa per ogni candidato.

Di tali stringhe viene calcolato un hash tramite la funzione SHA2-256 e i candidati sono ordinati in base ai valore di tale funzione.

Si ritiene che non esista modo di costruire una stringa con un valore di hash prefissato, se non provando una frazione consistente delle stringhe possibili, operazione assolutamente al di fuori della portata delle macchine oggi conosciute.

La correttezza dell'elezione è assicurata dal fatto che la stringa assegnata a ogni candidato dipende dalle chiavi di tutti i garanti, quindi servirebbe l'accordo di tutti i garanti per poter suggerire a un candidato una chiave personale che garantisca un valore elevato della funzione, chiave che in ogni caso richiederebbe un elevato numero di tentativi.

I garanti sono costretti a scegliere le loro chiavi prima dei candidati, quindi non hanno modo di sceglierle in modo da favorire qualcuno; i candidati a loro volta non conoscono le chiavi dei garanti, a meno di un accordo con tutti questi, quindi non possono avvantaggiarsi in alcun modo.

All'inizio i garanti non comunicano le loro chiavi, che restano segrete, ma solo il valore della funzione di hash delle stesse, rendendo irrevocabile la scelta, ma mantenendo la segretezza delle chiavi.

I garanti comunicano le loro chiavi solo al termine dell'elezione, dopo che i candidati hanno scelto le loro, ma non possono al termine dell'elezione indicare, per favorire qualche candidato, una chiave differente da quella scelta all'inizio, perché sono vincolati al valore della funzione di hash già comunicato.

Ogni candidato può comunque rendersi in un certo senso arbitro delle proprie fortune e svincolarsi dalle chiavi scelte dei garanti, inserendo una propria chiave che concorre a determinare la sua stringa e quindi il suo valore della funzione di hash.

Alla chiave di ogni candidato viene premesso il suo progressivo; in questo modo se un candidato non inserisce una chiave personale, il suo numero progressivo funge da chiave. Inoltre essendo il progressivo differente per ogni candidato, anche se due candidati inserissero, deliberatamente o per caso, la stessa chiave, le stringhe generate e quindi i valori della funzione di hash sarebbero diversi.

Al termine della procedura viene scritto l'elenco dei candidati in ordine decrescente della funzione di hash, creando una graduatoria; il numero di eletti presi dalla testa della graduatoria e il numero di eventuali riserve, destinate eventualmente a subentrare agli eletti in caso di impedimento o decadenza, sono stabiliti dal regolamento dell'elezione.

Il regolamento dell'elezione può anche prevedere l'esclusione dei candidati che non abbiano comunicato una propria chiave, come pure prevedere che i candidati non possano comunicare una chiave; in questo caso la fave di voto viene eliminata.

Il sistema non gestisce il caso di pareggio tra candidati, che dev'essere stabilito nel regolamento; per le caratteristiche della funzione di hash utilizzata si tratta di un evento estremamente improbabile, molto vicino all'impossibilità assoluta (probabilità per due candidati fissati dell'ordine di 2256, circa 0.864 · 1077.

### Inizio dell'elezione

Il presidente indice l'elezione tramite il programma CreateRandom, da lanciare con i seguenti parametri:

CreateRandom [--numeric-errors] *directory* *candidati* *garanti*

dove:

- *directory* è la directory che conterrà tutti i file creati durante l'elezione;
- *candidati* è il numero di candidati, nell'intervallo [2 .. 9999999];
- *garanti* è il numero di garanti, nell'intervallo [1 .. 99].

Il programma crea i file necessari nella directory indicata e pone l'elezione in stato CREATA.

### Scelta delle parole chiave da parte dei garanti

Durante questa fase i garanti scelgono ciascuno una parola chiave (o meglio, una frase) e comunicano al server solo l'hash delle stesse con il programma StartRandom, da lanciare con i seguenti parametri:

StartRandom [--numeric-errors] *directory* *garante* *hash* [*firma*]

dove:

- *directory* è la directory che contiene tutti i file creati durante l'elezione;
- *garante* è il numero del garante;
- *hash* è l'hash della chiave;
- *firma* è una firma, facoltativa.

Il programma verifica che l'hash della chiave non sia già stato comunicato e lo archivia.

Quando tutti gli hash delle chiavi dei garanti sono stati comunicati, il programma pone l'elezione in stato INIZIATA.

### Scelta delle parole chiave da parte dei candidati

Durante questa fase i candidati scelgono ciascuno una parola chiave (o meglio, una frase) e comunicano al server solo l'hash delle stesse con il programma VoteRandom, da lanciare con i seguenti parametri:

VoteRandom [--numeric-errors] *directory* * candidato * *chiave* [*firma*]

dove:

- *directory* è la directory che contiene tutti i file creati durante l'elezione;
- *candidato* è il numero del candidato;
- *chiave* è la chiave;
- *firma* è una firma, facoltativa.

Il programma verifica che la chiave non sia già stata comunicata e la archivia.

Quando scade il termine della votazione, il presidente abilita l'esecuzione del programma Close, permettendo ai garanti di comunicare le loro parole chiave.

### Comunicazione delle parole chiave da parte dei garanti

Durante questa fase i garanti comunicano la loro parola chiave con il programma CloseRandom, da lanciare con i seguenti parametri:

CloseRandom [--numeric-errors] *directory* *garante* *chiave*

dove:

- *directory* è la directory che contiene tutti i file creati durante l'elezione;
- *garante* è il numero del garante;
- *chiave* è la chiave.

Il programma verifica che la chiave non sia stata comunicata e che l'hash della chiave coincida con quello comunicato in precedenza.

Alla comunicazione della prima chiave il programma pone l'elezione in stato CHIUSA.

Quando tutte le chiavi dei garanti sono state comunicate, il programma pone l'elezione in stato TERMINATA.

### Lettura dello stato e proclamazione dei risultati

Il programma StateRandom permette di conoscere lo stato dell'elezione e di proclamare i risultati; va lanciato con i seguenti parametri:

StateRandom [--numeric-errors] *directory*

dove *directory* è la directory che contiene tutti i file creati durante l'elezione;

Il programma scrive su standard output lo stato dell'elezione, quanti garanti debbano ancora comunicare hash o parola chiave e quanti candidati debbano ancora votare; se l'elezione è terminata, il programma scrive la classifica dei candidati.

### Calcolo dell'hash

Il programma Hash permette di calcolare l'hash di una parola o frase, conoscere lo stato dell'elezione e di proclamare i risultati; va lanciato con i seguenti parametri:

Hash [--numeric-errors] *chiave*

dove *chiave* è la chiave della quale si vuole calcolare l'hash.

## Elezioni tramite *majority judgement*

Le elezioni tramite majority judgement permettono di selezionare un eletto da un insieme di candidati, garantendo la correttezza dell'elezione e la segretezza del voto.

Nell'elezione vi sono 3 parti attive:

- il presidente, i cui unici compiti sono indire l'elezione e dichiarare la chiusura delle votazioni;
- i custodi, il compito dei quali è scegliere le chiavi crittografiche, che garantiscono la segretezza dei voti;
- i votanti, il compito (facoltativo) di ciascuno dei quali è votare i candidati.

Custodi e votanti sono identificati da un numero progressivo; la corrispondenza tra tali numeri e l'identità delle persone dev'essere gestita separatamente.

Ogni elezione avviene in 3 fasi:

- inizio dell'elezione,
- votazione,
- proclamazione del vincitore.

Alle fasi corrispondono 4 possibili stati:

- APERTA, dopo l'inizio,
- TERMINATA dopo la votazione.

### Procedura di elezione

La procedura di elezione degli eletti è studiata per garantire la segretezza del voto e la sua integrità.

La segretezza dipende da due chiavi crittografiche di 16 byte, che i custodi scelgono all'inizio della votazione; ciascun custode può essere costituito da più persone, le chiavi delle quali vengono combinate per ottenere le due chiavi.

Il sistema è studiato in modo datale che la conoscenza di una delle chiavi non sia sufficiente a scoprire i voti dati da un votante, neppure con la complicità dell'amministratore di sistema.

Si ritiene che non esista modo di decodificare la crittografia impiegata, se non provando una frazione consistente delle chiavi possibili, operazione assolutamente al di fuori della portata delle macchine oggi conosciute.

Il metodo crittografico impiegato, inoltre è stato scelto per rendere molto scomoda e costosa l'implementazione in hardware.

Creata l'elezione viene lanciato un programma che riceve ed archivia i voti, confermando la ricezione. Il programma gira fino al termine dell'elezione; in caso di arresto imprevisto (per esempio per interruzione dell'alimentazione), può essere riavviato, con gli stessi parametri.

Il programma garantisce che i voti dei quali ha inviato conferma sono archiviati in un apposito file.

Per evitare la possibilità di vendita di voti, il programma permette a ciascun votante di votare più volte; ogni nuovo voto annulla l'eventuale precedente.

Per rendere non individuabile il votante, e quindi impossibile scoprire l'eventuale rettifica del voto, quando viene ricevuti un voto vengono riscritti i record corrispondenti a un gran numero di votanti, con dati differenti, in modo che i byte scritti, dopo essere stati crittografati, siano diversi.

Il file dei dati, infatti, contiene per ogni votante una metà di dati e una metà di numeri casuali, mescolati tra loro; modificando la parte casuale non si influisce sul risultato della votazione, ma si cambiano i byte scritti sul file.

In questo modo un amministratore di sistema che osservasse il file vedrebbe numerosi valori cambiare continuamente e non potrebbe stabilire se uno specifico votante abbia rivoltato o meno.

Questo sistema impedisce anche tentativi di individuazione dei voti basati sull'inserire combinazioni di voti predeterminate: se non ci fossero i dati casuali, infatti, sarebbe possibile individuare una parte dei voti con la collaborazione di due votanti e dell'amministratore del sistema. Basterebbe infatti che i due inserissero la stessa identica combinazione, per poi cercare nel file due record identici; a quel punto, variando un po' per volta i voti sarebbe possibile risalire alla codifica di ogni combinazione voluta.

Analogamente sarebbe possibile individuare con ragionevole probabilità una combinazione di voti, inserendone una uguale e questo renderebbe possibile la verifica di un voto comprato.

Il sistema non gestisce il caso di pareggio tra candidati, che dev'essere stabilito nel regolamento; per le caratteristiche dell'algoritmo utilizzato, un pareggio è possibile solo se due o più candidati hanno ricevuto esattamente lo stesso numero di voti per ciascuno dei voti possibili.

### Chiavi crittografiche

Le chiavi crittografiche impiegate sono due, di 16 byte ciascuna. I programmi leggono le chiavi da un file, che per garantire la sicurezza deve in realtà essere una pipe con nome, nella quale custodi scrivono le loro chiavi e che viene chiusa immediatamente dopo.

Se si desidera una maggior segretezza, ognuna delle chiavi può essere la combinazione d più chiavi, scelte da persone diverse e combinate con un semplice programma.

Le chiavi non sono permanentemente conservate in alcun luogo e devono essere immesse nuovamente ogni volta che si avvia uno dei programmi, vale a dire almeno tre volte.

Nel caso in cui l'esecuzione del programma che riceve i voti sia interrotta, è necessario rilanciarlo, immettendo nuovamente le chiavi. Di conseguenza i custodi devono garantire la loro disponibilità per tutto il tempo in cui l'elezione resta aperta.

### Inizio dell'elezione

Il presidente indice l'elezione tramite il programma CreateMajority, da lanciare con i seguenti parametri:

CreateMajority [--numeric-errors] *directory* *candidati* *votanti* *voti* *file delle chiavi*

dove:

- *directory* è la directory che conterrà tutti i file creati durante l'elezione;
- *candidati* è il numero di candidati, nell'intervallo [2 .. 9999999];
- *votanti* è il numero di votanti, nell'intervallo [1 .. 9999999];
- *voti* è il massimo voto che un votante può assegnare a ogni candidato, nell'intervallo [1 .. 15];
- *file delle chiavi* è il path name del file contenente le chiavi di crittografia.

Il programma crea i file necessari nella directory indicata e pone l'elezione in stato CREATA.

### Ricezione dei voti

I voti sono raccolti dal programma VoteMajority, da lanciare con i seguenti parametri:

VoteMajority [--numeric-errors] *directory* *file delle chiavi*

dove:

- *directory* è la directory che contiene tutti i file creati durante l'elezione;
- *file delle chiavi* è il path name del file contenente le chiavi di crittografia.

Il programma gira in continuazione, fino a quando viene interrotto o trova la fine del file di input.

I programma legge da standard input i voti, nel formato:

*votante* *voti* *firma*

dove:

- *votante* è il numero del votante;
- *voti* sono tanti voti quanti i candidati, nell'ordine degli stessi; ciascun voto è un numero da 0 al massimo voto possibile;

- *firma* è una firma.

Numero del votante, voti e firma devono essere separati da esattamente uno spazio e scritti su un'unica riga.

Il programma registra il voto e provvede a modificare la parte casuale di altri votanti, in numero scelto casualmente tra RANDOM\_VOTES e RANDOM\_VOTES \* 3 / 2, dopodichè scrive su standard output una riga nel formato *votante* *messaggio*, dove:

- *votante* è il numero del votante;
- *messaggio* è un messaggio di conferma dell'avvenuta votazione o un messaggio d'errore.

Numero del votante e messaggio sono separati da uno spazio.

In caso di errore nei dati di ingresso il programma scrive standard output una riga contenente il messaggio che specifica l'errore e continua a leggere i voti in arrivo.

### Generazione di dati casuali

Il programma NoiseMajority altera la parte casuale di voti scelti casualmente, in modo da rendere estremamente complesso anche all'amministratore di sistema l'identificazione dei voti attributi da uno specifico votante. Va lanciato con i seguenti parametri:

NoiseMajority [--numeric-errors] *directory* *file delle chiavi* * iterazioni* [*intervallo*]

dove:

- *directory* è la directory che contiene tutti i file creati durante l'elezione;
- *file delle chiavi* è il path name del file contenente le chiavi di crittografia;
- *iterazioni* è il numero di iterazioni, ossia il numero complessivo di dati da alterare;
- *intervallo* è l'intervallo di tempo, in secondi, tra due alterazioni successive di dati; se non è specificato, l'intervallo di default è 1 secondo.

L'intervallo, se specificato, deve essere maggiore di zero e non deve superare il massimo possibile (3600, ovvero un'ora).

### Proclamazione dei risultati

Il programma ResultMajority permette di conoscere lo stato dell'elezione e di proclamare i risultati; va lanciato con i seguenti parametri:

ResultMajority [--numeric-errors] *directory* *file delle chiavi* [*intervallo*]

dove:

- *directory* è la directory che conterrà tutti i file creati durante l'elezione;
- *file delle chiavi* è il path name del file contenente le chiavi di crittografia;
- *intervallo* è l'intervallo di tempo, in minuti, tra due alterazioni successive di dati; se non è specificato, la proclamazione dei risultati viene fatta una sola volta.

Il programma scrive su standard output data, ora, quanti votanti abbiano votato e la classifica dei candidati.

Se l'intervallo è specificato, il programma ripete la proclamazione dopo l'intervallo dato e continua fino a quando il processo viene ucciso. La proclamazione può avvenire mentre l'elezione è in corso, permettendo quindi di conoscere i risultati parziali.

L'intervallo, se specificato, deve essere maggiore di zero e non deve superare il massimo possibile (1440, ovvero un giorno).

# Messaggi d'errore

Questa sezione descrive i messaggi d'errore che i programmi per la gestione delle elezioni possono produrre.

Gli errori sono segnalati con un breve messaggio o con un codice numerico, se è stata usata l'opzione numeric-errors.

## Errori fatali

La tabella seguente descrive gli errori irrimediabili, che indicano un malfunzionamento irrimediabile, dovuto a un errore nel codice o all'esaurimento della memoria.

| Messaggio | Codice | Errore |
| --- | --- | --- |
| out of memory | 1000 | Mancanza di memoria |
| index out of bounds | 1001 | Indice di vettore al di fuori dei limiti |
| illegal argument | 1002 | Argomento di una funzione non valido |
| illegal conversion | 1003 | Conversione non valida tra caratteri e numeri |
| invalid pointer | 1004 | Puntatore non valido |
| illegal function call | 1005 | Chiamata di funzione non valida |

## Errori di I/O

La tabella seguente descrive gli errori di I/O. I primi 6 indicano un errore nel codice.

I messaggi d'errore di I/O sono seguitti da *on file* e dal path name del file che ha causato l'errore.

| Messaggio | Codice | Errore |
| --- | --- | --- |
| file not closed | 2000 | File non chiuso correttamente |
| file not open | 2001 | Operazione tentata su un file non aperto |
| file already open | 2002 | Tentativo di apertura di un file già aperto |
| illegal open mode | 2003 | Modo di apertura errato |
| invalid path name | 2004 | Path name non valido |
| too many open files | 2005 | Tentativo di aprire troppi file simultaneamente |
| I/O error | 2006 | Errore di I/O |
| file close error | 2007 | Errore durante la chiusura di un file |
| file read error | 2008 | Errore durante la lettura di un file |
| file write error | 2009 | Errore durante la scrittura di un file |
| file seek error | 2010 | Errore durante il posizionamento su un file |
| end of file | 2011 | Tentativo di lettura oltre la fine di un file |
| file does not exist | 2012 | File inesistente |
| file already exists | 2013 | Tentativo di creare un file o directory già esistente |
| file is a directory | 2014 | Tentativo di aprire una directory come file |
| file is not a directory | 2015 | Tentativo di aprire un file come directory |
| permission denied | 2016 | Permessi non corretti durante l'apertura di un file |
| file lock causes a deadlock | 2017 | Il tentativo di mettere un lock su un file causa un deadlock |
| too many locks | 2018 | Tentativo di mettere troppi lock |

## Errori dell'applicazione

La tabella seguente descrive gli errori dell'applicazione, dovuti a errori dell'utente.

| Messaggio | Codice | Errore |
| --- | --- | --- |
| a command line argument does not represent a valid integer | 3000 | Un argomento sulla riga comandi non è un intero valido |
| a hexadecimal string has a wrong length | 3001 | Stringa esadecimale di lunghezza errata |
| a string is not a valid hexadecimal string | 3002 | Una stringa non è un numero esadecimale valido |
| the number of candidates is not valid | 3003 | Il numero di candidati non è valido |
| the number of guarantors is not valid | 3004 | Il numero di garanti non è valido |
| the number of voters is not valid | 3005 | Il numero di votanti non è valido |
| the maximum vote is not valid | 3006 | Il massimo voto non è valido |
| the file containing candidates data has invalid length | 3007 | Il file contenente i dati dei candidati ha una lunghezza non valida |
| the file containing guarantors data has invalid length | 3008 | Il file contenente i dati dei garanti ha una lunghezza non valida |
| the file containing voters' indices has invalid length | 3009 | Il file contenente gli indici dei votanti ha una lunghezza non valida |
| the file containing votes has invalid length | 3010 | Il file contenente i voti ha una lunghezza non valida |
| the voters' key is not correct | 3011 | La chiave crittografica dei votanti non è corretta |
| the votes' key is not correct | 3012 | La chiave crittografica dei voti non è corretta |
| the time interval is zero or greater than the maximum valid value | 3013 | L'intervallo di tempo è zero o maggiore del valore massimo |
| the file containing candidates' data is corrupted | 3014 | Il file contenente i dati dei candidate è corrotto |
| the file containing guarantors' data is corrupted | 3015 | Il file contenente i dati dei garanti è corrotto |
| the file containing election parameters is corrupted | 3016 | Il file contenente i parametri dell'elezione è corrotto |
| the file containing voters' indices is corrupted | 3017 | Il file contenente gli indici dei votanti è corrotto |
| the file containing votes is corrupted | 3018 | Il file contenente i voti è corrotto |
| the hash of the key of a candidate is not correct | 3019 | L'hash della chiave di un candidato non è corretto |
| the hash of the key of a guarantor is not correct | 3020 | L'hash della chiave di un garante non è corretto |
| the election state is not valid for the requested operation | 3021 | Lo stato dell'elezione è incompatibile con l'operazione richiesta |
| the key is zero | 3022 | La chiave è zero |
| the hash is zero | 3023 | L'hash è zero |
| the number of the candidate is not valid | 3024 | Il numero del candidate non è valido |
| the number of the guarantor is not valid | 3025 | Il numero del garante non è valido |
| the number of the voter is not valid | 3026 | Il numero del votante non è valido |
| the format of the line containing votes is not valid | 3027 | Il formato della riga dei voti non è valido |
| a vote is not valid | 3028 | Un voto non è valido |
| some vote is missing | 3029 | Mancano uno o più voti |
| the signature is missing | 3030 | Manca la firma |
| the key of the guarantor has already been set | 3031 | La chiave del garante è già stata inserita |
| the vote of the candidate has already been set | 3032 | Il voto del candidate è già stato inserito |
| yhe format of the encryption file is not valid | 3033 | Il formato del file contenente le chiavi di crittografia non è valido |

# Parametri dei programmi

Questa sezione descrive i parametri dei programmi per la gestione delle elezioni.

## Elezioni tramite sorteggio

La tabella seguente descrive i parametri che regolano il funzionamento dei programmi che gestiscono le elezioni tramite sorteggio.

| Parametro | Valore |
| --- | --- |
| Lunghezza delle chiavi dei garanti | 55 byte |
| Lunghezza delle chiavi dei votanti | 48 byte |
| Lunghezza del numero progressivo dei votanti | 7 cifre |
| Lunghezza del valore prodotto dalla funzione di hash | 32 byte |
| Lunghezza delle firme | 32 byte |
| Numero minimo di garanti | 1 |
| Numero massimo di garanti | 99 |
| Numero minimo di candidati | 2 |
| Numero massimo di candidati | 9999999 |

## Elezioni tramite *majority judgement*

La tabella seguente descrive i parametri che regolano il funzionamento dei programmi che gestiscono le elezioni tramite *majority judgement*.

| Parametro | Valore |
| --- | --- |
| Lunghezza delle chiavi dei custodi | 16 byte |
| Lunghezza delle firme | 32 byte |
| Numero minimo di candidati | 2 |
| Numero massimo di candidati | 9999999 |
| Numero minimo di votanti | 1 |
| Numero massimo di votanti | 9999999 |
| Numero minimo di voti | 3 |
| Numero massimo di voti | 15 |
| Massimo intervallo per la generazione di dati casuali, in secondi | 3600 |
| Massimo intervallo per la proclamazione dei risultati, in minuti | 1440 |


## License

see [LICENSE file](LICENSE)

Specifiche del progetto:

Specifica Progetto di Laboratorio
Programmazione ad Oggetti
a.a. 2025/26
1 Introduzione
L’obiettivo del progetto `e sviluppare un’applicazione per la gestione di attivit`a
personali, come impegni, eventi, scadenze o promemoria, utilizzando il linguag-
gio di programmazione C++ e il framework Qt per la creazione dell’interfaccia
grafica utente (GUI).
L’applicazione dovr`a permettere agli utenti di gestire un elenco di attivit`a,
consentendo di creare, modificare, eliminare, cercare e visualizzare i diversi tipi
di attivit`a, ognuna delle quali dovr`a possedere attributi specifici. Ogni tipo di
attivit`a sar`a rappresentato da una classe derivata da una classe base comune,
che descrive gli attributi e i comportamenti condivisi.
L’interfaccia grafica dovr`a consentire all’utente di navigare tra le diverse viste
(lista delle attivit`a, dettaglio di una singola attivit`a, schermata di creazione e
modifica) e di gestire le operazioni principali attraverso pulsanti, menu o scorci-
atoie. `E possibile adottare pattern architetturali come il Model-View-Controller
o Model-View per la progettazione della GUI. Il framework Qt offre una doc-
umentazione completa e dettagliata che sar`a la principale guida di riferimento
per lo sviluppo dell’interfaccia grafica. Si incoraggia anche l’applicazione di de-
sign pattern comunemente utilizzati in C++ per migliorare la manutenibilit`a e
l’estensibilit`a del progetto.
Il progetto potr`a essere svolto individualmente o in coppia, e dovr`a
richiedere approssimativamente 40 ore di lavoro individuale.
La valutazione del progetto e il voto dell’esame scritto saranno calcolati
separatamente ed entrambi concorreranno al voto finale dell’esame. In linea
generale, il voto dell’esame scritto avr`a un peso maggiore, ma la valutazione
del progetto potr`a influire positivamente o negativamente sul risultato finale.
Gli studenti avranno la possibilit`a di ripresentare il progetto mantenendo il
voto dell’esame scritto, e viceversa. Tuttavia, la valutazione del progetto sar`a
effettuata solo per gli studenti che abbiano superato l’esame scritto e si siano
iscritti correttamente nella lista Uniweb per la registrazione del voto finale.
2 Vincoli
Il progetto deve obbligatoriamente soddisfare i seguenti vincoli:
1. essere un lavoro originale dello studente o della coppia di studenti
2. essere interamente scritto in C++
1
3. prevedere un’interfaccia grafica realizzata in Qt
4. compilare senza errori sul container Docker fornito (sono tollerati,
sebbene generalmente penalizzati, i warning durante la compilazione)
5. rispettare i principi di incapsulamento e information hiding della
programmazione orientata agli oggetti: una classe deve rappresentare
un singolo concetto e includere attributi e metodi con livelli di visibilit`a
appropriati
6. mantenere una separazione netta tra il modello logico e l’interfaccia
grafica, ovvero il codice del modello deve essere riutilizzabile senza dipen-
denze dall’interfaccia; `e consentito che il modello utilizzi strumenti Qt
non legati all’interfaccia, come le funzioni di I/O o le classi per la gestione
di JSON, e l’interfaccia grafica pu`o (e dovrebbe) utilizzare le classi del
modello
7. eseguire in maniera efficiente e robusta, senza errori a runtime
8. utilizzare il polimorfismo in maniera non banale; esempi di utilizzo
banale sono distruttori virtuali o semplici getter. Un utilizzo non banale
include metodi che si comportano in maniera profondamente diversa in
base al tipo dinamico dell’oggetto invocante, come la visualizzazione di
interfacce o azioni specifiche per ogni tipo di attivit`a; si incoraggia l’uti-
lizzo di uno o pi`u design pattern, in quanto questi richiedono spesso un
uso approfondito del polimorfismo
9. non utilizzare metodi virtuali come getType che restituiscono una
stringa rappresentate il tipo dell’oggetto per gestire il controllo di flusso in
sostituzione al polimorfismo; l’uso di tali metodi `e consentito unicamente
se finalizzati a mostrare effettivamente una semplice stringa
10. implementare una gerarchia di classi per le attivit`a con almeno tre clas-
si concrete per i progetti svolti singolarmente, o almeno cinque classi
concrete per i progetti svolti in coppia; in ogni caso le classi dovranno
presentare differenze significative, quali attributi e metodi diversi
11. consentire la ricerca, creazione, visualizzazione, modifica e cancel-
lazione di attivit`a tramite l’interfaccia grafica; le procedure di creazione
e modifica, in particolare, devono tenere conto dei differenti attributi delle
classi concrete
12. implementare la persistenza dei dati per le attivit`a in un file locale
in almeno un formato strutturato (ad esempio JSON o XML) per
i progetti di individuali, o in almeno due formati strutturati per i
progetti di coppia
13. consentire, in ogni momento durante l’esecuzione, il salvataggio e il
caricamento dei file contenenti i dati delle attivit`a attraverso finestre
di dialogo grafiche, evitando percorsi cablati nel codice sorgente
14. gestire la navigazione tra le diverse schermate all’interno della stessa
finestra, evitando l’apertura non necessaria di molteplici finestre; fanno
2
eccezione finestre di dialogo quali la selezione dei file, piccole modali in-
formative ed eventuali popup di conferma; in particolare le schermate di
creazione e modifica delle attivit`a devono prevedere schermate apposite
all’interno della finestra principale
15. essere corredato di una relazione in formato PDF, in lingua italiana o
inglese, di massimo 8 pagine con testo a 10pt, che riporti:
(a) nome, cognome e numero di matricola di tutti i componenti del
gruppo (o del singolo autore)
(b) una breve introduzione che descriva il contesto del progetto
(c) la descrizione delle classi principali del modello logico
(d) la descrizione dell’utilizzo non banale del polimorfismo, identificando
quali metodi sono polimorfi (in maniera ”non banale”) e qual `e il loro
valore aggiunto all’interno del progetto
(e) la descrizione del metodo di persistenza dei dati
(f) la descrizione delle funzionalit`a aggiuntive implementate
(g) la rendicontazione delle ore previste e di quelle effettivamente svolte
(h) solo per i progetti svolti in coppia: la suddivisione delle attivit`a tra
i membri del gruppo
(i) solo per progetti riconsegnati: una sezione che riporti le modifiche
rispetto all’ultima consegna
In caso di progetto di coppia, le relazioni devono essere distinte.
Assieme alle specifiche viene fornito un modello commentato di relazione,
il cui utilizzo non `e obbligatorio. Si suggerisce l’uso di LaTeX per redigere
la relazione, dato che `e largamente utilizzato in ambito accademico
La Fig. 1 mostra un esempio di struttura dell’interfaccia grafica.
3 Consegna
La consegna avverr`a tramite il Moodle del corso, all’interno del quale saran-
no attivate cinque sessioni di consegna del progetto per gli altrettanti appelli
d’esame previsti durante l’anno accademico (due sessioni di consegna a gen-
naio/febbraio 2026, due sessioni di consegna a giugno/luglio 2026, una sessione
di consegna a settembre 2026). Si dovr`a consegnare un unico archivio in formato
zip della dimensione massima di 256MB attraverso l’apposita pagina Moodle.
Non saranno accettati tentativi di consegna con modalit`a diverse o
formati che non siano zip. La cartella compressa dovr`a contenere:
•la relazione in formato PDF
•una sottocartella con i file sorgente del progetto (.h, .cpp, .pro, eventuali
sottocartelle) ed eventuali file multimediali necessari (immagini, icone,
ecc.)
•almeno un file d’esempio per la persistenza dei dati (almeno due, in diversi
formati, per i progetti in coppia)
3
Figura 1: Esempio di scheletro di una possibile interfaccia della finestra
principale
La cartella non dovrebbe contenere codice oggetto compilato, eseguibili, file
generati dall’IDE o in generale qualsiasi file non utile ai fini della valutazione.
Si raccomanda di verificare il corretto caricamento dei file su Moodle e di
comunicare tempestivamente eventuali malfunzionamenti.
Nei progetti di coppia ogni studente dovr`a provvedere separatamente alla
propria consegna includendo il codice (lo stesso per i due membri della coppia)
e la propria relazione (diversa per ciascuno). Se nella coppia solamente uno
studente `e sufficiente all’esame scritto, questo studente pu`o comunque procedere
alla consegna del progetto con l’obiettivo di finalizzare l’esame. Si ricorda che la
valutazione del progetto con relativo feedback avverr`a solamente per gli studenti
sufficienti all’esame scritto ed iscritti alla lista uniweb per il voto finale.
4 Criteri di valutazione
Il progetto viene valutato sulla base dei vincoli obbligatori e delle funzionalit`a
implementate. Pi`u precisamente, se uno o pi`u vincoli obbligatori non
risultano soddisfatti il progetto verr`a considerato insufficiente e sar`a
necessaria una riconsegna in uno degli appelli successivi. Viceversa, se tutti i
vincoli obbligatori sono soddisfatti il progetto `e considerato (almeno)
sufficiente e la valutazione aumenter`a in base alla qualit`a delle funzionalit`a
sviluppate e, in misura minore, in base alla qualit`a della relazione.
Una funzionalit`a viene valutata positivamente in base alla sua pertinenza al
tema, all’utilit`a, all’usabilit`a, alla complessit`a e alla qualit`a del codice attraverso
cui `e implementata. Funzionalit`a pi`u semplici o generiche migliorano la valu-
tazione, sebbene non tanto quanto idee pi`u complesse o articolate. Le scorciatoie
da tastiera, per esempio, sono migliorie generiche semplici da ottenere con poche
righe di codice in Qt, cos`ı come la gestione del ridimensionamento delle finestre
o l’uso di icone. Per contro l’integrazione con un sistema di API o l’uso di basi
4
di dati come SQL o MongoDB per la persistenza sono significativamente pi`u
complessi e richiedono la scrittura di classi apposite.
Poich ́e il corso non tratta di usabilit`a o resa estetica della GUI la loro man-
canza non verr`a penalizzata, purch ́e questo non pregiudichi il corretto fun-
zionamento del programma. Tuttavia, se il progetto viene sviluppato ponendo
particolare attenzione a queste caratteristiche, verr`a riconosciuto un bonus come
se si trattasse di una funzionalit`a aggiuntiva.
La valutazione terr`a conto dello storico delle valutazioni, e vedr`a una
progressiva riduzione all’aumentare del numero di consegne.
La qualit`a della relazione, pur avendo un’incidenza minore, verr`a valutata
sulla base della completezza, della chiarezza e della coesione. Errori linguisti-
ci evidenti come sistematica mancanza di punteggiatura o errori di battitura
frequenti verranno penalizzati. `E possibile redigere la relazione in Italiano
o Inglese, a propria discrezione. La scelta della lingua non avr`a effetti sulla
valutazione.
Ciascuna finestra di consegna presente nella pagina Moodle del corso mostr-
er`a una data limite: non sar`a in alcun modo possibile consegnare oltre
tale data o con modalit`a diverse da quelle previste.
La valutazione del progetto consegnato in una delle cinque sessioni d’esame
`e valida solamente per quella sessione; se in quella sessione non verr`a
registrato il voto finale, il progetto dovr`a essere riconsegnato in una successiva
sessione per ottenere una nuova valutazione, eventualmente senza modifiche.
La valutazione `e accompagnata da un feedback testuale che motiva la va-
lutazione ed evidenzia i punti di forza e debolezza del progetto. `E possibile
riconsegnare un progetto per ottenere una nuova valutazione, che potrebbe an-
che essere peggiorativa, tuttavia se si seguono le indicazioni fornite dal feedback
sar`a generalmente migliorativa. La valutazione `e idempotente: riconsegnare lo
stesso progetto senza modifiche produrr`a esattamente la stessa valutazione. Se
un progetto viene riconsegnato senza la sezione riportante le modifiche rispetto
alla consegna precedente nella relazione, questo non verr`a valutato nuovamente
e ricever`a automaticamente la stessa valutazione della consegna precedente.
Figura 2: Schema di valutazione indicativo
La Fig. 2 presenta la distribuzione dei pesi assegnati alle diverse caratteris-
tiche del progetto, da considerarsi indicativa e utile come guida nello sviluppo.
5
Poich ́e la valutazione dipende dalle funzionalit`a scelte dagli studenti, la griglia
serve principalmente come riferimento orientativo.
5 Verbalizzazione del voto
La registrazione del voto finale `e possibile solo dopo:
•avere superato con valutazione maggiore o uguale a 18 la prova scritta
•essersi iscritti alla lista Uniweb della per la registrazione del voto finale
•avere consegnato il progetto entro la scadenza prevista per la sessione in
cui si intende verbalizzare il voto e aver ottenuto una valutazione positiva
Si ricorda che le liste Uniweb verificato il soddisfacimento delle propedeuticit`a e
hanno una data di chiusura anticipata di almeno 5 giorni. Non saranno ammesse
iscrizioni manuali in ritardo, per nessun motivo.
La valutazione dei progetti sar`a completata generalmente entro 15 giorni
dalla consegna, in base al numero di progetti da esaminare. Una volta pronta,
la valutazione finale, comprensiva del voto della prova scritta e del progetto,
sar`a caricata su Uniweb, mentre il feedback relativo al progetto verr`a inviato
tramite Moodle esclusivamente agli utenti iscritti alla lista Uniweb. In caso
di valutazione negativa del progetto l’esame non sar`a superato: sar`a quindi
necessaria la riconsegna del progetto per una successiva scadenza di consegna
all’interno dello stesso anno accademico; in questo caso il voto dell’esame scrit-
to rimane comunque valido. Lo studente che rifiuter`a il voto finale proposto
via Uniweb dovr`a riconsegnare il progetto per una successiva scadenza di con-
segna nello stesso anno accademico (tranne all’ultimo appello d’esame, per cui
ovviamente non esiste una successiva scadenza di consegna), cercando quindi di
porre rimedio ai punti deboli segnalati nel feedback di valutazione e descrivendo
obbligatoriamente le modifiche apportate al progetto nella relazione aggiorna-
ta; anche in questo caso il voto sufficiente dell’esame scritto rimane comunque
valido.
6 Note
La parte di laboratorio dell’insegnamento di Programmazione a Oggetti ha
una propria pagina ufficiale su GitHub all’indirizzo github.com/Unipd-Object-
Oriented-Programming. Questo spazio contiene il materiale didattico relativo
a questo modulo dell’insegnamento, inclusi i lucidi delle lezioni e gli esempi del
codice, suddivisi per anno accademico.
I video-tutorati dell’anno accademico 2020/2021 del tutor Benedetto Cosenti-
no dedicati all’apprendimento delle caratteristiche di base del framework Qt per
la progettazione di GUI sono disponibili su YouTube.

--------------------------------------------------

Consigli:

Certo 👍 ti faccio un riassunto strutturato e riutilizzabile della chat, così puoi ripartire da qui in qualsiasi momento senza perderti.

🧠 📦 RIASSUNTO DEL PROGETTO (Qt + C++ + CMake + Git)
🎯 Obiettivo iniziale

Hai un progetto C++ con Qt (Calendar) e volevi:

renderlo versionabile con Git
renderlo portabile su altri PC
evitare riconfigurazioni manuali ogni volta
⚙️ 🧱 STRUTTURA DEL PROGETTO

Attuale (semplificata):

ProgettoPAO/
├─ src/
├─ build/
├─ QT/ (Qt + MinGW dentro progetto o vicino)
├─ CMakeLists.txt
├─ .vscode/

✔ compilazione con CMake
✔ Qt Widgets (Qt6)
✔ MinGW (compiler GCC)

⚙️ 🧠 CONFIGURAZIONE TOOLCHAIN
CMake
usa find_package(Qt6 REQUIRED COMPONENTS Widgets)
richiede CMAKE_PREFIX_PATH per trovare Qt

Problemi riscontrati:

Qt non trovato → errore Qt6Config.cmake not found
compiler confusi (MinGW / MSYS2 / Qt MinGW)
VSCode

File coinvolti:

settings.json → CMAKE_PREFIX_PATH
c_cpp_properties.json → include Qt + compiler
tasks.json → build manuale MinGW

Problemi:

path hardcoded
uso di variabili non esistenti (${env:MINGW_PATH})
IntelliSense disallineato con CMake
💥 PROBLEMI PRINCIPALI RISCONTRATI
1. ❌ Compiler confusi
Qt MinGW
MSYS2 UCRT64
MinGW esterno

👉 risultato: CMake a volte usa c++.exe sbagliato

2. ❌ Qt non trovato da CMake

Errore:

Qt6Config.cmake not found

✔ risolto con CMAKE_PREFIX_PATH

3. ❌ App non parte dopo build

Exit code:

-1073741515

👉 significa:

DLL Qt mancanti

✔ risolto con windeployqt

4. ❌ problema Git iniziale
repo GitHub già inizializzato
conflitto “unrelated histories”
risolto con:
git push --force
5. ❌ warning Git LF → CRLF
solo warning Windows
legato a file Qt/MinGW

✔ non critico

🚀 SOLUZIONE ARCHITETTURALE CHE HAI ADOTTATO
✔ build system
CMake
✔ Qt linking
find_package(Qt6 Widgets)
✔ runtime fix
windeployqt
✔ Git
repo creato
force push iniziale
🧠 CONCETTO CHIAVE CHE HAI IMPARATO
💡 CMake NON gestisce runtime Qt

Serve sempre:

compile → link → deploy Qt DLL → run
📦 PORTABILITÀ DEL PROGETTO (IMPORTANTE)
❌ NON portabile “out of the box”

se fai solo:

git clone
run exe
✔ portabile come codice

Serve su ogni PC:

Qt installato (o incluso localmente)
MinGW compatibile
CMake configurato
✔ portabile come eseguibile

Serve:

windeployqt
oppure packaging finale
⚙️ DECISIONE FINALE CHE HAI PRESO

✔ NON includere Qt nel Git
✔ usare Qt esterno
✔ usare CMake + windeployqt
✔ mantenere repo pulito

👉 questa è la scelta CORRETTA

📁 STATO FINALE DEL GIT

Repo contiene:

✔ src/
✔ CMakeLists.txt
✔ .vscode (parzialmente)
✔ codice progetto

Repo NON contiene:

❌ QT/
❌ build/
❌ exe
❌ DLL

🚨 PROBLEMA RESIDUO CHE HAI RISOLTO

App che “non si avvia senza errori”

👉 causa:

DLL Qt mancanti
runtime non deployato

✔ risolto con windeployqt

🎯 RISULTATO FINALE

Hai ottenuto:

✔ progetto compilabile
✔ progetto eseguibile
✔ Git funzionante
✔ Qt funzionante
✔ MinGW integrato
✔ build system corretto

💡 LEZIONE PRINCIPALE

👉 Qt su Windows NON è “plug & play”
👉 serve separare:

build (CMake)
runtime (Qt DLL)
deploy (windeployqt)
version control (Git)
🚀 SE VUOI IL PROSSIMO PASSO

Posso aiutarti a fare una versione:

🔥 “clone → build → run senza errori mai”
🔥 oppure README da consegna perfetto
🔥 oppure CMake auto-deploy definitivo

Dimmi 👍


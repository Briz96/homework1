# homework1

Per far partire il programma aprire un terminale e scrivere "roslaunch homework1 homework1.launch" si aprirà un menù dove verranno spiegati brevemente i comandi.

Per realizzare il programma ho  creato un messaggio definito da me, chiamato myMsg.msg composto da tre attributi name,age,course.

Il programma è strutturato su tre nodi:
Publisher: che ogni secondo invia un messaggio di tipo myMsg inizializzato con i miei dati al reader.

Filtered_msg: stampa a video il menù con i vari comandi, una volta inserito da tastiera viene fatto un controllo sul dato inserito dall'utente per verificarne se è valido.
Se lo è viene mandato un messaggio contenente il comando al reader.
Il filtered_msg rimane in attesa di nuovi comandi fino alla chiusura del programma. 

Reader: è strutturato su due funzioni, la commandCallback e la filteredCallback, la prima ascolta i messaggi in arrivo dal filtered_msg e li assegna ad una variabile c che verrà usata per il filtraggio, la seconda rimane in ascolto dei messaggi di tipo myMsg. Finchè la variabile c non contiene un valore rimane in attesa, una volta arrivato il comando vinene valutato da uno switch, se questo è valido viene stampata la parte di messaggio corrispondente altrimenti esce un messaggio di errore.

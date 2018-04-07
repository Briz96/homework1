# homework1

Per far partire il programma aprire un terminale e scrivere "roslaunch homework1 homework1.launch" si aprirà un menù dove verranno spiegati brevemente i comandi.

Per realizzare il programma ho  creato un messaggio definito da me, chiamato myMsg.msg composto da tre attributi name,age,course.

Il programma è strutturato su tre nodi:
Publisher: che ogni secondo invia un messaggio di tipo myMsg inizializzato con i miei dati.

Filtered_msg: stampa a video un piccolo menù per l'esecuzione delle istruzioni e rimane in ascolto dei messaggi, una volta intercettato aspetta che venga inserito un comando da tastiera dall'utente.
Per ogni comando viene eseguito uno switch che va ad eseguire le istruzioni corrispondenti al comando.
Il filtraggio del messaggio viene fatto creando un nuovo messaggio myMsg ed inizializzandolo solo i campi di interesse e viene inviato.

Reader: rimane in ascolto di messaggi provenienti da filtered_msg una volta intercattati li stampa a video.

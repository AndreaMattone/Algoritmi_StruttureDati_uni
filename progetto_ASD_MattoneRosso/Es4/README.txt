Caricare le cartelle di test all'interno di "Es4/"

javac ConnectedGraph.java
ruby run-tests.rb "java ConnectedGraph"

___________________________________________

 #### NB ####

L'algoritmo riesce a terminare in meno di 60 secondi solo sui test 3, 4 e 5, e quindi solo su questi test crea completamente il file output.txt

Sugli altri test superando i 60 secondi viene interrotta l'esecuzione INTERROMPENDO LA SCRITTURA del file output.txt perciò OMETTENDO DEI RISULTATI che sarebbero risultati corretti lasciando eseguire l'algoritmo per più di 60 secondi.
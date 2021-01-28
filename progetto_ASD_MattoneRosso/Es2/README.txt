Inserire i dataset "correctme.txt" e "dictionary.txt" nella cartella Es2/src/

COMPILAZIONE ED ESECUZIONE WINDOWS:
javac -cp .;junit-4.12.jar;hamcrest-core-1.3.jar Esercizio2_tests.java
java -cp .;junit-4.12.jar;hamcrest-core-1.3.jar org.junit.runner.JUnitCore Esercizio2_tests

COMPILAZIONE ED ESECUZIONE UNIX:
javac -cp .:junit-4.12.jar:hamcrest-core-1.3.jar Esercizio2_tests.java
java -cp .:junit-4.12.jar:hamcrest-core-1.3.jar org.junit.runner.JUnitCore Esercizio2_tests

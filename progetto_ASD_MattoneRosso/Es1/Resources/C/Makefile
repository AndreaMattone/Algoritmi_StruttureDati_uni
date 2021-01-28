
# lista dei target da eseguire sempre
all: tests exec

# compila (grazie alla dipendenza) e esegue i test
tests: bin/ordered_array_tests
	bin/ordered_array_tests

#  compila (grazie alla dipendenza) e esegue ordered_array
exec: bin/ordered_array
	bin/ordered_array ../ordered_array_sample_file.csv

# Flags per il compilatore -- su gcc -Weverything non esiste
#    sostituire con -Wall -Wpedantic
CFLAGS = -g -Weverything -Wno-padded -Werror

# Lista degli header files
INCLUDES = src/*.h

# tutti i target vanno ricompilati se cambiano gli header o
# questo Makefile
COMMON_DEPS = $(INCLUDES) Makefile

# regola per compilare un .c in un .o
# viene applicata ogni volta che una dipendenza richiede di compilare un file in
#    `build` e con suffisso .o. Il simbolo % effettua pattern matching con quanto
#    compreso tra 'build/' e '.o', la stringa in questione viene quindi usata sul lato
#    destro della regola per indicare il file da compilare.
# Le variabili $< e $@ sono gestite automaticamente da `make` esse corrispondono:
#   $@ : l'intero target della regola (in questo caso: build/<nomefile>.o)
#   $< : la prima dipendenza della regola (in questo caso: src/<nomefile>.c)
build/%.o: src/%.c $(COMMON_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

bin/ordered_array: build/ordered_array.o build/ordered_array_main.o $(COMMON_DEPS)
	$(CC) -o bin/ordered_array build/ordered_array.o build/ordered_array_main.o

bin/ordered_array_tests: build/ordered_array_tests.o build/ordered_array.o build/unity.o $(COMMON_DEPS)
	$(CC) -o bin/ordered_array_tests  build/ordered_array_tests.o build/ordered_array.o build/unity.o

clean:
	rm -f build/* bin/*

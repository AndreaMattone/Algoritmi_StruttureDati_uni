#pragma once
#include <stdlib.h>

/**Definizione della compare function*/
typedef int (*SortedStructureCompareFun)(void*, void*);

struct _SortedStructure{
  /*Array di elementi generici*/
  void** array;
  /*Capacità totale dell'array*/
  int capacity;
  /*Dimenzione attuale dell'array*/
  int size;
  /*Compare function*/
  /*SortedStructureCompareFun compare;*/
};
typedef struct _SortedStructure SortedStructure;

/**Struttura di un Record*/
typedef struct{
  int id;
  char* field1;
  int field2;
  float field3;
}Record;

/**Costruttore*/
SortedStructure* sorted_structure_new();
/**Distruttore*/
void sorted_structure_free(SortedStructure*);

/**Funzione di insert*/
void sorted_structure_insert(SortedStructure*, void*);
/**Rimozione un oggetto di indice i dalla struttura*/
void sorted_structure_remove(SortedStructure*, int);
/**Ottiene l'elemento di indice i dalla struttura*/
void* sorted_structure_get(SortedStructure*, int);
/**Ritorna la size attuale della struttura*/
int sorted_structure_size(SortedStructure* ss);

/*## Fornti dall'utente ##*/
int compare_first_field(Record* rec1, Record* rec2);
int compare_second_field(Record* rec1, Record* rec2);
int compare_third_field(Record* rec1, Record* rec2);
void load_data(SortedStructure* myStr, char* filename);
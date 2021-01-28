#include <stdlib.h>
#include <stdio.h>
#include "sorted_structure.h"
#define INTIAL_CAPACITY 100

/*
Costruttore
*/
SortedStructure* sorted_structure_new(){
  SortedStructure* myStruct = (SortedStructure*) malloc(sizeof(SortedStructure));
  myStruct->capacity = INTIAL_CAPACITY;
  myStruct->array = (void**) malloc(sizeof(void*)*myStruct->capacity);
  myStruct->size = 0;
  return myStruct;
}

/*
Distruttore
*/
void sorted_structure_free(SortedStructure* ss){
  free(ss->array);
  free(ss);
}

/**
Inserisce l'oggetto in input nella struttura ss
*/
void sorted_structure_insert(SortedStructure* ss, void* object){
  if(ss->capacity == ss->size){
    ss->capacity = ss->capacity*2;
    ss->array = (void**) realloc(ss->array,sizeof(void*)*ss->capacity);
  }
  ss->array[ss->size] = object;
  ss->size++;
}

/**
Rimuove l'oggetto di indice index dalla struttura ss
*/
void sorted_structure_remove(SortedStructure* ss, int index){
  if(ss->capacity > ss->size*2){
    ss->capacity = ss->capacity/2;
    ss->array = (void**) realloc(ss->array,ss->capacity);
  }
  for(int j=index; j<ss->size-1; j++){
    ss->array[j] = ss->array[j+1];
  }
  ss->size--;
}

/*
Restituisce l'oggetto di indice index dalla struttura ss
*/
void* sorted_structure_get(SortedStructure* ss, int index){
  return ss->array[index];
}

/**
Ritorna la size della struttura data in input
*/
int sorted_structure_size(SortedStructure* ss){
  return ss->size;
}



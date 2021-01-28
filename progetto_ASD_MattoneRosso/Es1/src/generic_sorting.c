#include <stdlib.h>
#include "sorted_structure.h"
#include "generic_sorting.h"

/**
Effettua la swap tra due oggetti di indice i e j nella struttura passata in input
*/
void swap(SortedStructure* ss,int a,int b){
  void* temp;
  temp = ss->array[a];
  ss->array[a]=ss->array[b];
  ss->array[b]=temp;
}


/**
  Generic Insertion sort 
*/
void generic_insertion_sort(SortedStructure* ss,SortedStructureCompareFun myCompareFunction){
   int j;
    for(int i=1;i<(ss->size);i++){
    j=i;    
    while(j>0 && myCompareFunction(sorted_structure_get(ss,j-1),sorted_structure_get(ss,j))>0){
      swap(ss,j-1,j);
      j--;
    }
  }
}

/**
Funzione di appoggio per il quicksort
Ritorna il pivot dell'algoritmo di quicksort
*/
int partition(SortedStructure* ss,int min,int max, SortedStructureCompareFun myCompareFunction){
  void* pivot = ss->array[max];
    int i=min-1,j=max;
    while(1){
      while(i<max && myCompareFunction(sorted_structure_get(ss,++i),sorted_structure_get(ss,max))<0)
        continue;
      while(j>min && myCompareFunction(sorted_structure_get(ss,--j),sorted_structure_get(ss,max))>0)
        continue;
      if(i>=j)
        break;
      else
          swap(ss,i,j);
    }
  swap(ss,i,max);
  return i;
}

/**
GenericQuick sort
*/
void generic_quick_sort(SortedStructure* ss,int i,int j,SortedStructureCompareFun myCompareFunction){
  int p;
  if(j-i<=0)
    return;
  else{
    p = partition(ss,i,j,myCompareFunction);
    generic_quick_sort(ss,i,p-1,myCompareFunction);
    generic_quick_sort(ss,p+1,j,myCompareFunction);
  } 
}

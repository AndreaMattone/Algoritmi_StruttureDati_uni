#pragma once

/**Effettua la swap tra due oggetti di indice i e j nella struttura passata in input*/
void swap(SortedStructure*,int,int);
/**Funzione di appoggio per il quicksort*/
int partition(SortedStructure*,int,int,SortedStructureCompareFun);
/**Insertion sort of generic elements*/
void generic_insertion_sort(SortedStructure*,SortedStructureCompareFun);
/**Quick sort of generic elements*/
void generic_quick_sort(SortedStructure*,int,int,SortedStructureCompareFun);
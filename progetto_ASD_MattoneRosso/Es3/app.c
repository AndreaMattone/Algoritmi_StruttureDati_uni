#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "hash.h"

/*#### FORNITA DALL'UTENTE ####*/
#define SIZEOFDATASET 6321078
#define SIZEKEYS 10000000


/*#### FORNITA DALL'UTENTE ####*/
/*Struttura con chiave,valore (K,V) con il tipo deciso dall'utente
*/
typedef struct{
  int key;
  int value;
}KeyValueStructure_int;

typedef struct{
  char* key;
  char* value;
}KeyValueStructure_string;


/*#### FORNITA DALL'UTENTE ####*/
/*Funzione di compare tra due elementi del tipo che voglio inserire nella HashMap
  restituisce 0 se i due elementi sono uguali
*/
int compare_elem_string(void* elem1, void* elem2){
  char* temp1 = (char*)elem1;
  char* temp2 = (char*)elem2;
  return strcmp(temp1,temp2);
}
int compare_elem_int(void* elem1, void* elem2){
  int* temp1 = (int*)elem1;
  int* temp2 = (int*)elem2;
  int ret;
  return *temp1-*temp2;
}


/*#### FORNITA DALL'UTENTE ####*/
/*Funzione di hash delle chiavi
*/
int hash_func_string(void* key1, int size){
  unsigned long hash = 5381;
    int c;
    while (c = *(unsigned char*)key1++){
      hash = ((hash << 5) + hash) + c;
    }   
    return hash % size;
}
int hash_func_int(void* key1, int size){
    /* Robert Jenkins' 32 bit Mix Function*/
    unsigned int key = *(int*)key1;
    key += (key << 12);
    key ^= (key >> 22);
    key += (key << 4);
    key ^= (key >> 9);
    key += (key << 10);
    key ^= (key >> 2);
    key += (key << 7);
    key ^= (key >> 12);
    key = (key >> 3) * 2654435761;
    return key % size;
}


/*#### FORNITA DALL'UTENTE ####*/
/*Funzione di load dei dati dal dataset dell'utente nella struct
*/
void loadData(HashTable* myHashTable, char* filename){
  FILE* file;
  if( (file=fopen(filename, "r"))==NULL){
    printf("Errore nell'apertura del file\n");
    exit(1);
  }
  int key;
  int value;
  int lineno=0;
  while(!feof(file)){
    lineno++;
    KeyValueStructure_int* myKV = (KeyValueStructure_int*)malloc(sizeof(KeyValueStructure_int));
    int n = fscanf(file, "%d,%d\n", &myKV->key, &myKV->value);
    if(n!=2){
      if(feof(file)){
        continue;
      }
      printf("Error while reading file\n");
      exit(1);
    }
    int r = hashtable_insert(myHashTable, (void*)&myKV->key,(void*)&myKV->value,SIZEOFDATASET);
  }
  fclose(file);
}

void loadDataStatic(KeyValueStructure_int* myStaticArray,char* filename){
  FILE* file;
  if( (file=fopen(filename, "r"))==NULL){
    printf("Errore nell'apertura del file\n");
    exit(1);
  }
  int lineno=0;
  while(!feof(file)){



    int n = fscanf(file, "%d,%d\n", &myStaticArray[lineno].key, &myStaticArray[lineno].value);
    lineno++;



    if(n!=2){
      if(feof(file)){
        continue;
      }
      printf("Error while reading file\n");
      exit(1);
    }
  }
  fclose(file);
}





/**
  Print della NodeList
  Input: Puntatore alla NodeList
*/
void print_node_list_string(NodeList* myList, int line){
  Node* node;
  Node* succ;

  node = myList->head;
  printf("%d: ",line);
  while(node!=NULL){
    succ = node->succ;
    printf("%s ->",(char*)node->elem);
    node = succ;
  }
  printf("nil\n");
}

void print_node_list_int(NodeList* myList, int line){
  Node* node;
  Node* succ;

  node = myList->head;
  printf("%d: ",line);
  while(node!=NULL){
    succ = node->succ;
    printf("%d ->",*(int*)node->elem);
    node = succ;
  }
  printf("nil\n");
}

/**
  Stampa il contenuto della HashMap
  Input: HashTable
  Valori di ritorno: Un array con tutti gli indici della HashMap per cui è presente una associazione
*/
void print_hashmap_stringelem(HashTable myHashTable){
  int line=0;


  for(int i=0;i < myHashTable.size;i++){
    line++;
    if( ((myHashTable.myArrayList+i)->head) != NULL){ 

      print_node_list_string(myHashTable.myArrayList+i,line);
    }else{
      printf("%d: NULL\n",line);
    }
  }
}

void print_hashmap_intelem(HashTable myHashTable){
  int line=0;


  for(int i=0;i < myHashTable.size;i++){
    line++;
    if( ((myHashTable.myArrayList+i)->head) != NULL){ 

      print_node_list_int(myHashTable.myArrayList+i,line);
    }else{
      printf("%d: NULL\n",line);
    }
  }
}




void quick_sort(KeyValueStructure_int* myStaticArray, int primo,int ultimo){
  int i,j,pivot;
  KeyValueStructure_int temp;

  if(primo<ultimo){
    pivot=primo;
    i=primo;
    j=ultimo;

    while(i<j){
      while(myStaticArray[i].key <= myStaticArray[pivot].key && i<ultimo)
        i++;
      while(myStaticArray[j].key > myStaticArray[pivot].key)
        j--;
      if(i<j){
        temp.key = myStaticArray[i].key;
        temp.value = myStaticArray[i].value;
        myStaticArray[i].key=myStaticArray[j].key;
        myStaticArray[i].value=myStaticArray[j].value;
        myStaticArray[j].key = temp.key;
        myStaticArray[j].value = temp.value;
      }
    }
    temp.key = myStaticArray[pivot].key;
    temp.value = myStaticArray[pivot].value;
    myStaticArray[pivot].key = myStaticArray[j].key;
    myStaticArray[pivot].value = myStaticArray[j].value;
    myStaticArray[j].key = temp.key;
    myStaticArray[j].value = temp.value;
    quick_sort(myStaticArray, primo,j-1);
    quick_sort(myStaticArray,j+1,ultimo);

  }
}







/*Ritorna l'indice di x in un array dato se presente, altrimenti -1*/
  int binarySearch(KeyValueStructure_int* myStaticArray, int l, int r, int x) { 
    if (r >= l) { 
        int mid = l + (r - l) / 2; 
        // If the element is present at the middle 
        // itself 
        if (myStaticArray[mid].key == x) 
            return myStaticArray[mid].value; 
  
        // If element is smaller than mid, then 
        // it can only be present in left subarray 
        if (myStaticArray[mid].key > x) 
            return binarySearch(myStaticArray, l, mid - 1, x); 
  
        // Else the element can only be present 
        // in right subarray 
        return binarySearch(myStaticArray, mid + 1, r, x); 
    } 
    // We reach here when element is not 
    // present in array 
    return -1; 
} 








/**
 "./app dataset/dataset.csv"
*/
int main(int argc, char* argv[]){

  HashTable myHashTable;
  //(K,V) -> (int,int)
  char* dataset_path;
  if(argc!=2){
    printf("Parameters error\n");
    exit(1);
  }


  /*
  CARICAMENTO DEL FILE IN UNA HASMAP
  */
  dataset_path= argv[1];
  int hashTableCreate1 = hashtable_create(&myHashTable, SIZEOFDATASET, hash_func_int, compare_elem_int);
  printf("--------------------------------------------------\n");
  printf("| Creazione hasmap e caricamento del dataset...\n");
  loadData(&myHashTable, dataset_path);
  printf("| Caricamento del dataset nella hashmap completato...\n");
  printf("--------------------------------------------------\n\n");
  //printf("%d\n", count_hashmap_associations(&myHashTable));
  //print_hashmap_intelem(myHashTable);
  


  /*
  CARICAMENTO DEL FILE IN UN ARRAY
  */
  printf("--------------------------------------------------\n");
  printf("| Inizio il caricamento nell'array...\n");
  KeyValueStructure_int* myStaticArray = (KeyValueStructure_int*)malloc(sizeof(KeyValueStructure_int)*SIZEOFDATASET);
  loadDataStatic(myStaticArray, dataset_path);
  printf("| Caricamento nell'array completato...\n");

  /*
  ORDINAMENTO DEI RECORD SECONDO IL CAMPO KEY NELL'ARRAY
  */
  printf("| Inizio ad ordinare i record secondo i campi key nell'array...\n");
  quick_sort(myStaticArray, 0,SIZEOFDATASET-1);
  printf("| Record nell'array ordinati...\n");
  printf("--------------------------------------------------\n\n\n\n");
  /* //Verifica ordinamento
  for(int i=0;i<50;i++){
   printf("%d, %d\n" ,myStaticArray[i].key, myStaticArray[i].value);
  }*/







  /*
  GENERAZIONE IN UN ARRAY KEYS DI SIZEKEYS VALORI INTERI CASUALI
  */

  printf("--------------------------------------------------\n");
  printf("| Generazione di un array keys di %d valori casuali.\n",SIZEKEYS);
  printf("--------------------------------------------------\n\n\n\n");
  int* keys = (int*)malloc(sizeof(int)*SIZEKEYS);
  srand(getpid());
  for(int i=0;i<SIZEKEYS;i++){
    keys[i] = rand() % (SIZEKEYS+1);
  }





  /*
  RECUPERO I VALORI ASSOCIATI ALLE CHIAVI IN KEYS USANDO LA HASHMAP
  */
  NodeList* temp;
  int* countH = (int*)malloc(sizeof(int)*SIZEOFDATASET);
  for(int i=0;i<SIZEOFDATASET;i++){
    countH[i]=0;
  }
  printf("-----------------------------------------------------\n");
  printf("Inizio a recuperare i valori associati alle chiavi usando la hashmap...\n");
  for(int i=0;i<SIZEKEYS;i++){
    int hash_temp = myHashTable.hash_func((void*)&keys[i], myHashTable.size);
    temp = find_hashmap_key_values(&myHashTable, (void*)&keys[i]);
    if(temp->head!=NULL){
      countH[hash_temp] = countH[hash_temp]+1;
    }
  }
  printf("Ho recuperato tutti i valori associati alle chiavi usando la hashmap...\n");
  printf("-----------------------------------------------------\n\n\n\n");




  /*
  RECUPERO I VALORI ASSOCIATI ALLE CHIAVI IN KEYS USANDO LA RICERCA DICOTOMICA
  */
  int countA=0;
  printf("-----------------------------------------------------\n");
  printf("Inizio a recuperare i valori associati alle chiavi usando la ricerca binaria...\n");
  for(int i = 0; i < SIZEOFDATASET; i++){
    /*binary search ritorna -1 se non trova la chiave altrimenti ritorna il valore sicuramente diverso da -1*/
    if(binarySearch(myStaticArray, 0, SIZEOFDATASET-1, keys[i]) != -1){
      countA++;
    }
  }
  printf("Ho recuperato tutti i valori associati alle chiavi usando la ricerca binaria...\n");
  printf("-----------------------------------------------------\n\n\n\n");




  /*
  VERIFICA SE IL NUMERO DI CHIAVI E UGUALE
  */
  int association_array=0;
  for(int i=0;i<SIZEOFDATASET;i++){
    if(countH[i]!=0){
      association_array = association_array + 1;
    }
  }
  printf("Risultati: \n");
  printf("Associazioni della hashmap: %d\n", count_hashmap_associations(&myHashTable));
  printf("Associazioni da keys usando la hashmap: %d\n", association_array);
  printf("Associazioni da keys usando la binary search: %d\n", countA);


  free(countH);
  free(keys);
  free(myStaticArray);
  hashtable_free(&myHashTable);
  printf("Ok\n");
  return 0;
}
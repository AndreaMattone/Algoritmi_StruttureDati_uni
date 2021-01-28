#include <stdlib.h>
#include <stdio.h>
#include "hash.h"

/**
  Creazione ed inizializzazione di una Lista di 0 elementi
  Input: Puntatore ad una NodeList
         Puntatore alla funzione di compare tra due elementi del tipo che voglio inserire nella lista
*/
void create_list(NodeList* myList, int (*compare_elem)(void*,void*)) {
  myList->head =NULL;
  myList->n_elem=0;
  myList->compare_elem = compare_elem;
}


/**
  Allocazione di un Node con all'interno un elemento dato
  Input: Elemento da inserire nel nodo
         L'indirizzo del puntatore a Node in cui inserire l'elemento
  Valori di ritorno: 0 -> successo nella creazione del Node
                    -1 -> fallimento
*/
int create_node(void* elem, Node** myNode){
  /*Alloca la dimensione per un Node*/
  *myNode = (Node*)malloc(sizeof(Node));

  if(*myNode != NULL){ /*la malloc ritorna NULL in caso di errore*/
    (*myNode)->prec = NULL;
    (*myNode)->succ = NULL;
    (*myNode)->elem = elem;
    return 0;
  }else{
    printf("Error in create_node\n");
    return -1;
  }
}


/**
  Inserimento di un elemento in una NodeList
  Input: Puntatore alla NodeList in cui voglio inserire l'elemento
         Elemento che voglio inserire nella NodeList
  Valori di ritorno: 0 -> successo nell'iserimento dell'elemento
                    -1 -> altrimenti
*/
int insert_elem_list(NodeList* myList, void* elem){
  Node* myNode;

  if(create_node(elem, &myNode) == 0){
  if(myList->n_elem != 0){ 
    /* -> La lista ha già degli elementi*/
    /*Effettua un inserimento in testa*/
    Node* temp = myList->head;
    myList->head = myNode;
    myList->head->succ = temp;
    temp->prec = myList->head;
  }else{ 
    /* -> La mia lista non aveva elementi inseriti*/
    /*Metto come head della lista il nodo appena creato*/
    myList->head = myNode;
  }
    /*Aumento il numero di elementi nella mia lista*/
    myList->n_elem = (myList->n_elem) + 1;
    return 0;
  }else{
    printf("Error in insert_elem_list\n");
    return -1;
  }
}


/**
  Verifica se un elemento è nella NodeList data
  Input: Puntatore alla NodeList in cui voglio cercare l'elemento
         L'elemento che voglio cercare nella NodeList
         Puntatore all'indirizzo dell'elemento se trovato (a *ptrElemFind viene assegnato il puntatore del Node con l'elemento)
          Nota: se l'elemento c'è ptrElemFind è diverso da NULL
  Valori di ritorno: /

  compare_elem(void*, void*) -> primo argomento: i-esimo elemento della lista da confrontare con il secondo argomento
                             -> secondo argomento: Elemento da trovare
*/
void find_elem(NodeList* myList, void* elemToFind, void** ptrElemFind){
  Node* node = myList->head;

  if(node==NULL){ 
    /*La lista è vuota e l'elemento non c'è*/
    *(Node**)ptrElemFind = NULL;
  }else{
    /*La lista ha degli elementi*/
    int exit = 0; /*Se exit=1 ho trovato il nodo*/
    while((node!=NULL) && (exit==0)){
      if((myList->compare_elem(node->elem,elemToFind)) == 0){
        /*Ho trovato l'elemento e sono posizionato sul suo puntatore*/
        exit=1;
      }else{
        node=node->succ;
      }
    }

    /*Valorizzo ptrElemFind*/
    if(ptrElemFind != NULL){
      if(exit==1){ /*Ho trovato l'elemento*/
        *(Node**)ptrElemFind = (void*)node;
      }else{ /*Non ho trovato l'elemento*/
        *(Node**)ptrElemFind = NULL;
      }
    }
  }
}


/**
  Rimozione di un Node da una NodeList
  Input: Puntatore alla NodeList da cui voglio rimuovere il Node
         Puntatore al nodo che voglio rimuovere

*/
void remove_node(NodeList* myList, void* node){
  Node* to_delete = node;
  Node* prec_to_delete;
  Node* succ_to_delete;

  if(to_delete == NULL){
    printf("Error il nodo da rimuovere non esiste\n");
  }else{
    prec_to_delete = to_delete->prec;
    succ_to_delete = to_delete->succ;

    /*La lista ha solo un elemento, ovvero quello da eliminare*/
    if((prec_to_delete == NULL) && (succ_to_delete ==NULL)){
      myList->head = NULL;
      
    /*L'elemento da cancellare è in testa ma ci sono piu elementi*/
    }else if((prec_to_delete==NULL) && (succ_to_delete!=NULL)){
      myList->head = succ_to_delete;
      succ_to_delete->prec = NULL; /*Succ diventa il primo elemento della lista*/
		
    /*L'elemento da cancellare è l'ultimo della lista ma ce ne sono prima*/
    }else if((prec_to_delete!=NULL) && (succ_to_delete==NULL)){
      prec_to_delete->succ = NULL; /*Cancella l'ultimo elemento della lista*/
		
    /*L'elemento da cancellare è in mezzo ad una lista di piu elementi*/
    }else{
      prec_to_delete->succ = succ_to_delete;
      succ_to_delete->prec = prec_to_delete;
    }

    free(to_delete->elem);
    free(to_delete);
    myList->n_elem = (myList->n_elem) - 1;
  }
}


/**
  Free di tutti i nodi all'interno della lista data
  Chiamata una volta per ogni "indice" della lista PRINCIPALE della hash table
  Input: Puntatore alla NodeList
*/
void free_list(NodeList* myList){
  Node* node;
  Node* succ;

  node = myList->head;
  while(node!=NULL){
    succ = node->succ;
    /*free(node->elem);*/
    free(node);
    node = succ;
  }
  myList->head = NULL;
}






/**
  Creazione di una hashmap vuota
  Input: Il puntatore alla HashTable
         Numero di campi presenti nella NodeList PRINCIPALE dell'hashtable
         la funzione di Hash -> (fornita dall'utente)
         La funzione di compare tra due elementi nei nodi delle liste -> (fornite dall'utente)
  Valori di ritorno: 0 -> HashTable creata correttamente
                    -1 -> Altrimenti
*/
int hashtable_create(HashTable* myHashTable, int size, int(*hash_func)(void*, int), int(*compare_elem)(void*,void*)){
  myHashTable->size = size;
  myHashTable->hash_func = hash_func;
  myHashTable->myArrayList = (NodeList*)malloc(size * sizeof(NodeList));

  if(myHashTable->myArrayList == NULL){
    printf("Error la malloc ha ritornato null\n");
    return -1;
  }else{
    for(int i=0;i<size;i++){
      create_list(myHashTable->myArrayList + i, compare_elem);
    }
    myHashTable->numElemTot = 0;
  }
  return 0;
}


/**
  Verifica se la hashmap è vuota
  Input: Puntatore alla HashTable
  Valori di ritorno: 0 -> La hashmap è vuota
                    -1 -> Altrimenti
*/
int is_hashmap_empty(HashTable* myHashTable){
  if(myHashTable->numElemTot == 0){
    return 0;
  }else{
    return -1;
  }
}


/**
  Inserisce un elemento all'interno della hashmap
  Input: Puntatore alla HashTable in cui inserire l'elemento
         Puntatore alla chiave dell'elemento da inserire (K)
         Puntatore all'elemento da inserire              (V)
         Size della HashTable
  Valori di ritorno: 0 -> Inserimento avvenuto con successo
                    -1 -> Altrimenti
*/
int hashtable_insert(HashTable* myHashTable, void* KEY_elemToInsert, void* elemToInsert, int size){
  int hashed_index = myHashTable->hash_func(KEY_elemToInsert, myHashTable->size);
  int ret = insert_elem_list(myHashTable->myArrayList + hashed_index, elemToInsert);
  
  if(ret==0){
    myHashTable->numElemTot = (myHashTable->numElemTot) +1;
    return ret;
  }else{
    printf("Errore nell'inserimento dell'elemento\n");
    return -1;
  }
}


/**
  Verifica se la chiave (K) data è nella hashmap
  Input: Hashmap in cui controllare se ci sono associazioni alla chiave (K) data
         Chiave (K) che voglio controllare
  Valori di ritorno: 0 -> Nella hashmap ci sono gia elementi associati a quella chiave
                    -1 -> Altrimenti
*/
int is_key_in_hashmap(HashTable* myHashTable, void* KEY_elemToFind){
  int hashed_index = myHashTable->hash_func(KEY_elemToFind, myHashTable->size);
  if( ((myHashTable->myArrayList+hashed_index)->head) == NULL){
    return -1;
  }else{
    return 0;
  }
}


/**
  Conta il numero di associazioni presenti nella HashMap data
  Input: La HashTable in cui contare le associazioni
  Valori di ritorno: il numero di associazioni presenti nella HashMap
*/
int count_hashmap_associations(HashTable* myHashTable){
  int not_valorized=0;
  for(int i=0;i < myHashTable->size;i++){
    if( ((myHashTable->myArrayList+i)->head) == NULL){
      not_valorized++;
    }
  }
  return ((myHashTable->size) - not_valorized);
}


/**
  Elimina tutte le associazioni di una HashMap
  Input: Hashmap da cui eliminare le associazioni
*/
void free_all_hashmap_associations(HashTable* myHashTable){
  for(int i=0;i<myHashTable->size;i++){
    /*Fa la free di ogni lista associata ad ogni "indice" della lista principale*/
    free_list(myHashTable->myArrayList + i);
  }
}


/**
  Cancellazione e deallocazione di una HashTable data 
  Input: hashTable da deallocare
*/
void hashtable_free(HashTable* myHashTable){
  free_all_hashmap_associations(myHashTable);
  free(myHashTable->myArrayList);
}


/**
  Trova nella HashMap tutti i valori associati ad una certa chiave (K)
  Input: HashMap in cui trovare i valori relativi ad una chiave (K)
         Chiave (K)
  Valori di ritorno: Un puntatore alla head della lista di indice associato alla chiave (K) data
*/
void* find_hashmap_key_values(HashTable* myHashTable, void* KEY_elemToFind){
  int hashed_index = myHashTable->hash_func(KEY_elemToFind, myHashTable->size);
  return myHashTable->myArrayList + hashed_index;
}


/**
  Rimozione dalla HashMap di tutte le associazioni ad una chiave (K) specificata
  Input: HashMap
         Chiave (K)
  Valori di ritorno: 0 -> Rimozione avvenuta con successo
                    -1 -> Altrimenti
*/
int hashtable_remove_key(HashTable* myHashTable,void* KEY_toRemove){
  int hashed_index = myHashTable->hash_func(KEY_toRemove, myHashTable->size);
  if(is_key_in_hashmap(myHashTable,KEY_toRemove) == 0){ //Chiave presente nell'hashMap

    /*Prima di fare la free di tutti i valori associati alla lista di chiave K
    conto quanti valori ho associati a quella lista e decremento il numElemTot di quegli n valori*/
    NodeList* temp = find_hashmap_key_values(myHashTable, KEY_toRemove);
    int counter=0;
    Node* n = temp->head;
    while(n!=NULL){
      counter++;
      n = n->succ;
    }
    myHashTable->numElemTot = (myHashTable->numElemTot) - counter;

    /*Rimozione degli elementi*/
    free_list(myHashTable->myArrayList + hashed_index);

    return 0;
  }else{
    printf("La chiave da rimuovere non esiste\n");
    return -1;
  }
}


/**
  Recupera le chiavi presenti attualmente in una HashMap
  Input: HashTable
  Valori di ritorno: Un array con tutti gli indici della HashMap per cui è presente una associazione
*/
int* get_all_keys(HashTable* myHashTable){
  int* associationsArray = (int*) malloc(myHashTable->size*sizeof(int));
  int indexCounter=0;
  for(int i=0;i < myHashTable->size;i++){
    if( ((myHashTable->myArrayList+i)->head) != NULL){ /*Ho una associazione*/
      *(associationsArray + indexCounter) = i; /*Inserisco nell'array l'indice*/
      indexCounter++;
    }
  }
  associationsArray = realloc(associationsArray,(indexCounter+1)*sizeof(int)); /*Ridimensiono l'array nel caso in cui ci siano state delle collissioni, 
                                                                                 quindi meno associazioni di size*/
  return associationsArray;
}



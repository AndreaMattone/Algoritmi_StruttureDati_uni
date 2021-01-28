#include <stdlib.h>

/**Nodo structure*/
typedef struct _Node{
	struct _Node* prec;
	struct _Node* succ;
	void* elem;
}Node;

/**Lista di nodi structure*/
typedef struct _NodeList{
	/*Puntatore alla testa della lista*/
	Node* head;
	/*Numero elementi della lista*/
	int n_elem;
	/* Funzione di compare tra due elementi generici dati
	 * -> restituisce un intero che indica se la comparazione ha trovato una uguaglianza
	 */
	int (*compare_elem)(void*, void*);
}NodeList;

/**HashTable structure*/
typedef struct _HashTable{
	/*Lista di nodi principale della hash table*/
	NodeList* myArrayList;
	/*Numero di campi totali presenti nella lista PRINCIPALE dell'hashtable*/
	int size;
	/*Numero di elementi totali contenuti nell'hash table*/
	int numElemTot;

	/* Funzione di hash
	 * -> Restituisce un intero che indica l'indice nell'"array principale" su dove si trova il valore della chiave data
	 * -> (*hash) è il puntatore alla funzione di hash data dall'utente
	 * -> come parametri prende la chiave che associerà all'indice e la size della hashtable (per evitare overflow)
	*/
	int (*hash_func)(void* key, int size);
}HashTable;


void create_list(NodeList* myList, int(*compare_elem)(void*,void*));
int insert_elem_list(NodeList* myList, void* elem);
void find_elem(NodeList* mylist, void* elemToFind, void** ptrElemFind);
void remove_node(NodeList* mylist, void* node);
void free_list(NodeList* myList);


int hashtable_create(HashTable* myHashTable,int size, int(*hash_func)(void*, int size), int(*compare_elem)(void*,void*));
int is_hashmap_empty(HashTable* myHashTable);
int hashtable_insert(HashTable* myHashTable, void* KEY_elemToInsert,void* elemToInsert, int size);
int is_key_in_hashmap(HashTable* myHashTable, void* KEY_elemToFind);
int count_hashmap_associations(HashTable* myHashTable);
void free_all_hashmap_associations(HashTable* myHashTable);
void hashtable_free(HashTable* myHashTable);
void* find_hashmap_key_values(HashTable* myHashTable, void* KEY_elemToFind);
int hashtable_remove_key(HashTable* myHashTable,void* KEY_toRemove);
int* get_all_keys(HashTable* myHashTable);

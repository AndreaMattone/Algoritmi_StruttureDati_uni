#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./Resources/C/Unity/unity.h"
#include "hash.h"

/*FORNITE DALL'UTENTE*/
typedef struct{
  int key;
  int value;
}KeyValueStructure_int;
typedef struct{
  char* key;
  char* value;
}KeyValueStructure_string;

int compare_elem_string(void* elem1, void* elem2){
  char* temp1 = (char*)elem1;
  char* temp2 = (char*)elem2;
  return strcmp(temp1,temp2);
}
int compare_elem_int(void* elem1, void* elem2){
  int* temp1 = (int*)elem1;
  int* temp2 = (int*)elem2;
  return *temp1==*temp2;
}

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



/*TESTS*/

static void hashtable_empty(){
  HashTable myHashTable;
  int hashTableCreate = hashtable_create(&myHashTable, 0, hash_func_int, compare_elem_int);
  TEST_ASSERT_EQUAL(0,is_hashmap_empty(&myHashTable));
  hashtable_free(&myHashTable);
}

static void hashtable_onesized(){
  HashTable myHashTable;
  char* key = "test";
  char* value = "test_value ";

  int hashTableCreate = hashtable_create(&myHashTable, 1, hash_func_string, compare_elem_string);
  int hashTableInsert = hashtable_insert(&myHashTable, (void*)key,(void*)value, 1);

  TEST_ASSERT_EQUAL(-1,is_hashmap_empty(&myHashTable));
  TEST_ASSERT_EQUAL(1,count_hashmap_associations(&myHashTable));
  TEST_ASSERT_EQUAL(0,is_key_in_hashmap(&myHashTable, (void*)key));
  TEST_ASSERT_EQUAL(1, myHashTable.size);
  TEST_ASSERT_EQUAL(1, myHashTable.numElemTot);


  hashtable_remove_key(&myHashTable,(void*)key);

  TEST_ASSERT_EQUAL(0,is_hashmap_empty(&myHashTable)); /*E' vuota*/
  TEST_ASSERT_EQUAL(0,count_hashmap_associations(&myHashTable)); /*Non ci sono associazioni nella hastable*/
  TEST_ASSERT_EQUAL(-1,is_key_in_hashmap(&myHashTable, (void*)key)); /* La chiave che ho appena rimosso non è nella hashtable*/
  TEST_ASSERT_EQUAL(1, myHashTable.size); /*La size rimane 1 perchè è quella data in create*/
  TEST_ASSERT_EQUAL(0, myHashTable.numElemTot); /*Avendo tolto 1 elemento da una hashtable di size 1 ora ho 0 elementi totali*/

  hashtable_free(&myHashTable);
}

static void hashtable_multivalue(){
  
  HashTable myHashTable;
  char* key_d[5] = {"a", "ba", "c", "da", "fer"};
  char* value_d[5] = {"x", "xx", "xxx", "xxxx", "xxxxx"};
  int hashTableCreate = hashtable_create(&myHashTable, 5,hash_func_string,compare_elem_string);
  for(int i =0;i<5;i++){
    KeyValueStructure_string* myKV = (KeyValueStructure_string*)malloc(sizeof(KeyValueStructure_string));
    myKV->key = key_d[i];
    myKV->value = value_d[i];
    int r = hashtable_insert(&myHashTable, (void*)myKV->key,(void*)myKV->value,5);
  }




  /*
  1: xx -> x -> NIL               (Key=a,ba)
  2: xxxx -> NIL                  (Key=da)
  3: xxxxx -> xxx -> NIL          (Key=fer,c)
  4: NIL
  5: NIL
  */
  /*Group tests 1*/
  TEST_ASSERT_EQUAL(0, hashTableCreate);
  TEST_ASSERT_EQUAL(-1,is_hashmap_empty(&myHashTable));
  TEST_ASSERT_EQUAL(5, myHashTable.size);
  TEST_ASSERT_EQUAL(5, myHashTable.numElemTot);
  TEST_ASSERT_EQUAL(3,count_hashmap_associations(&myHashTable));
  /*print_hashmap_stringelem(myHashTable);*/
  for(int i=0;i<5;i++){
  	TEST_ASSERT_EQUAL(0,is_key_in_hashmap(&myHashTable, (void*)key_d[i]));
  }
  NodeList* temp;
  Node* tempn;

  temp = find_hashmap_key_values(&myHashTable, (void*)key_d[4]);
  tempn = temp->head;
  tempn=tempn->succ;
  TEST_ASSERT_EQUAL(0, strcmp(tempn->elem, value_d[2]));

  temp = find_hashmap_key_values(&myHashTable, (void*)key_d[2]);
  tempn = temp->head;
  tempn=tempn->succ;
  TEST_ASSERT_EQUAL(0, strcmp(tempn->elem, value_d[2]));
  


  /*
  1: xx -> x -> NIL               (Key=a,ba)
  2: xxxx -> NIL                  (Key=da)
  3: NIL                          (Key=fer,c)
  4: NIL
  5: NIL
  */
  /*Group tests 2*/
  hashtable_remove_key(&myHashTable,(void*)key_d[4]);
  TEST_ASSERT_EQUAL(-1,is_hashmap_empty(&myHashTable));
  TEST_ASSERT_EQUAL(5, myHashTable.size);
  TEST_ASSERT_EQUAL(3, myHashTable.numElemTot);
  TEST_ASSERT_EQUAL(2,count_hashmap_associations(&myHashTable));
  TEST_ASSERT_EQUAL(-1,is_key_in_hashmap(&myHashTable, (void*)key_d[4]));
  TEST_ASSERT_EQUAL(-1,is_key_in_hashmap(&myHashTable, (void*)key_d[2]));


  hashtable_free(&myHashTable);
}




int main(int argc, char const *argv[]){
  UNITY_BEGIN();

  RUN_TEST(hashtable_empty);
  RUN_TEST(hashtable_onesized);
  RUN_TEST(hashtable_multivalue);

  UNITY_END();

  return 0;
}
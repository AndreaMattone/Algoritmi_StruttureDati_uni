#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sorted_structure.h"
#include "generic_sorting.h"
#define MAX_BUF_LEN 1024


/*###### FORNITE DALL'UTENTE ######*/
/*Funzioni di compare*/
/**Compare first field*/
int compare_first_field(Record* rec1, Record* rec2){
  return strcmp(rec1->field1, rec2->field1);
}
/**Compare second field*/
int compare_second_field(Record* rec1, Record* rec2){
  return rec1->field2 - rec2->field2;
}
/**Compare third field*/
int compare_third_field(Record* rec1, Record* rec2){
  if(rec1->field3==rec2->field3){
    return 0;
  }else if(rec1->field3>rec2->field3){
    return 1;
  }else if(rec1->field3<rec2->field3){
    return -1;
  }
}


/*###### FORNITA DALL'UTENTE ######*/
/**Load data da CSV nella struttura*/
void load_data(SortedStructure* myStr, char* filename){
  FILE* file;
  if((file=fopen(filename, "r"))==NULL) {
    printf("Errore nell'apertura del file'");
    exit(1);
  }
    int  id;  /*ID*/
    char buf[MAX_BUF_LEN];  /*field1*/
    int field2;  /*field2*/
    float field3;  /*field3*/
    int lineno = 0;  /*line number*/
    int n;
    while(!feof(file)) { // && lineno<2000 
      Record* record = (Record*) malloc(sizeof(Record));
      int n = fscanf(file, "%d,%1024[^,],%d,%f\n", &id,buf,&field2,&field3);
      lineno++;
      if(n != 4) {
        if(feof(file)) {
          continue;
        }          
        printf("Error while reading file at line: %d\n", lineno);
        exit(1);
      }
      record->id = id;
      record->field1 = strndup(buf, MAX_BUF_LEN);
      record->field2 = field2;
      record->field3 = field3;
      sorted_structure_insert(myStr,record);
    }
  fclose(file);
}


/*###### FORNITA DALL'UTENTE ######*/
/**Stampa tutti i record della struttura*/
void print_records(SortedStructure* myStr){
  for(int i=0; i<sorted_structure_size(myStr);i++){
    Record* tempRec = sorted_structure_get(myStr, i);
    printf("%d,     %s,     %d,     %f\n", tempRec->id,tempRec->field1,tempRec->field2,tempRec->field3);
  }
}



int main(int argc, char *argv[]){
  SortedStructureCompareFun myCompareFunction;
  SortedStructure* myStr;
  char* dataset_path;
  if(argc!=2) {
    printf("Parameters error\n");
    exit(1);
  }
  dataset_path = argv[1];


  /*
  myCompareFunction = (SortedStructureCompareFun)compare_first_field;
  myStr = sorted_structure_new();
  printf("Quicksort: load data...\n");
  load_data(myStr, dataset_path);
  //printf("To order:\n");
  //print_records(myStr);
  printf("Quicksort: Ordering first field...\n");
  generic_quick_sort(myStr,0,sorted_structure_size(myStr)-1, myCompareFunction);
  printf("Quicksort: Ordered first field with quicksort\n");
  //print_records(myStr);
  printf("Quicksort: free struct...\n");
  printf("\n\n");
  sorted_structure_free(myStr);*/

  myCompareFunction = (SortedStructureCompareFun)compare_second_field;
  myStr = sorted_structure_new();
  printf("Quicksort: load data...\n");
  load_data(myStr, dataset_path);
  //printf("To order\n");
  //print_records(myStr);
  printf("Quicksort: Ordering second field...\n");
  generic_quick_sort(myStr,0,sorted_structure_size(myStr)-1, myCompareFunction);
  printf("Quicksort: Ordered second field with quicksort\n");
  //print_records(myStr);
  printf("Quicksort: free struct...\n");
  printf("\n\n");
  sorted_structure_free(myStr);


  /*myCompareFunction = (SortedStructureCompareFun)compare_third_field;
  myStr = sorted_structure_new();
  load_data(myStr, dataset_path);
  //printf("To order\n");
  //print_records(myStr);
  printf("Quicksort: Ordering third field...\n");
  generic_quick_sort(myStr,0,sorted_structure_size(myStr)-1, myCompareFunction);
  printf("Quicksort: Ordered third field with quicksort\n");
  //print_records(myStr);
  printf("Quicksort: free struct...\n");
  printf("\n\n");
  sorted_structure_free(myStr);*/

  printf("ok\n");

  return 0;
}
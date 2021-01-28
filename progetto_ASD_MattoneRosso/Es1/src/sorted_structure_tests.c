#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../Resources/C/Unity/unity.h"
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
  /*
  return rec1->field3-rec2->field3
  */
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


/*
Genera un csv con valori casuali del tipo indicato di dimensione (numero righe) pari alla size data in input
Criterio di generazione:
id: intero crescente sempre differente
field1: "field1_example"
field2: intero da size a 0
field3: float generato randomicamente
*/
static void generate_csv_file(int size){
    FILE *fp;
    unsigned seed;

    if(!size){
       fp = fopen("dataset/test.csv", "w+");
       fclose(fp);
    }else{
        fp = fopen("dataset/test.csv", "w+");
        srand(seed);
        for(int i = 0; i < size; i++)
            fprintf(fp, "%d,%s,%d,%f\n", i, "field1_example", size-i, (float)rand()/(float)(RAND_MAX/100));
        fclose(fp);
    }       
}

static void remove_csv_file(){
    system("rm ./dataset/test.csv");
}



static void sorted_structure_sort_generic_sized_array(){    
    SortedStructureCompareFun myCompareFunction = (SortedStructureCompareFun)compare_second_field;
    SortedStructure* myStr = sorted_structure_new();
    Record* rec;

    generate_csv_file(4);
    load_data(myStr, "./dataset/test.csv");

    /*Controllo la size = 4*/
    TEST_ASSERT_EQUAL(4, sorted_structure_size(myStr));
    /*Verifico l'ordinamento dei campi sul field 2 con l'insertion sort*/
    generic_insertion_sort(myStr,myCompareFunction);
    rec= sorted_structure_get(myStr,0);
    TEST_ASSERT_EQUAL(1,rec->field2);
    rec= sorted_structure_get(myStr,1);
    TEST_ASSERT_EQUAL(2,rec->field2);
    rec= sorted_structure_get(myStr,2);
    TEST_ASSERT_EQUAL(3,rec->field2);
    rec= sorted_structure_get(myStr,3);
    TEST_ASSERT_EQUAL(4,rec->field2);

    remove_csv_file();
    sorted_structure_free(myStr);

    /*Analogo per il quicksort*/
    myStr = sorted_structure_new();
    generate_csv_file(4);
    load_data(myStr, "./dataset/test.csv");

    TEST_ASSERT_EQUAL(4, sorted_structure_size(myStr));
    generic_quick_sort(myStr,0,sorted_structure_size(myStr)-1,myCompareFunction);
    rec= sorted_structure_get(myStr,0);
    TEST_ASSERT_EQUAL(1,rec->field2);
    rec= sorted_structure_get(myStr,1);
    TEST_ASSERT_EQUAL(2,rec->field2);
    rec= sorted_structure_get(myStr,2);
    TEST_ASSERT_EQUAL(3,rec->field2);
    rec= sorted_structure_get(myStr,3);
    TEST_ASSERT_EQUAL(4,rec->field2);
    remove_csv_file();
    sorted_structure_free(myStr);
}


static void sorted_structure_sort_one_sized_array(){    
    SortedStructureCompareFun myCompareFunction = (SortedStructureCompareFun)compare_second_field;
    SortedStructure* myStr = sorted_structure_new();
    Record* rec;

    generate_csv_file(1);
    load_data(myStr, "./dataset/test.csv");

    /*Verifico che la dimensione della sorted structure sia 1*/
    TEST_ASSERT_EQUAL(1, sorted_structure_size(myStr));
    /*Ordino con l'insertion sort il field 2*/
    generic_insertion_sort(myStr,myCompareFunction);
    /*Recupero il primo ed unico record che avrà field1 = 1*/
    rec = sorted_structure_get(myStr,0);
    TEST_ASSERT_EQUAL(1,rec->field2);

    remove_csv_file();
    sorted_structure_free(myStr);

    /*Analogo con il quicksort*/
    myStr = sorted_structure_new();
    generate_csv_file(1);
    load_data(myStr, "./dataset/test.csv");

    TEST_ASSERT_EQUAL(1, sorted_structure_size(myStr));
    generic_quick_sort(myStr,0,sorted_structure_size(myStr)-1,myCompareFunction);
    rec= sorted_structure_get(myStr,0);
    TEST_ASSERT_EQUAL(1,rec->field2);
    remove_csv_file();
    sorted_structure_free(myStr);
}


static void sorted_structure_create_zero_sized_array(){   

    SortedStructureCompareFun myCompareFunction = (SortedStructureCompareFun)compare_second_field;
    SortedStructure* myStr = sorted_structure_new(myCompareFunction); 

    TEST_ASSERT_EQUAL(0, sorted_structure_size(myStr));
    sorted_structure_free(myStr);
}




int main(){
        UNITY_BEGIN();

        RUN_TEST(sorted_structure_create_zero_sized_array);
        RUN_TEST(sorted_structure_sort_one_sized_array);
        RUN_TEST(sorted_structure_sort_generic_sized_array);

        UNITY_END();
}
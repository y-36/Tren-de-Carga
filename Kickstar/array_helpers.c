/*
@file array_helpers.c
@brief Array Helpers method implementation
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_helpers.h"
#include "wagon.h"

char * cargo_type_to_str(cargo_t cargo) {
  if (cargo == rice)
    return "rice";
  if (cargo == mushrooms)
    return "mushrooms";
  if (cargo == oatmeal)
    return "oatmeal";
  if (cargo == pepper)
    return "pepper";
  return "error";
}

//funtion for sort array wagon only in this archive :)
static int compare_wagons(const void *a, const void *b) {
    Wagon *wagonA = (Wagon *)a;
    Wagon *wagonB = (Wagon *)b;
    return wagonA->number - wagonB->number;
}

void array_dump(Train t, unsigned int size) {

  qsort(t, size, sizeof(Wagon), compare_wagons);
  
  for (unsigned int i = 0u; i < size; ++i) {
    Wagon w = t[i];
    fprintf(stdout, "wagon %u: %u kg of %s", w.number, w.weight, cargo_type_to_str(w.cargo));
    if (i != size-1) {
      fprintf(stdout, "\n");
    }
  }
}

// the wagon data should be saved on array
// the number of wagons should be stored on trainSize
void array_from_file(Train array, unsigned int * trainSize, const char *filepath) {
  FILE *file = NULL;

  file = fopen(filepath, "r");
  if (file == NULL) {
    fprintf(stderr, "File does not exist.\n");
    fclose(file);
    exit(EXIT_FAILURE);
  }

  char code;
  unsigned int size = 0u;
  unsigned int totalKg = 0u;

    int res = fscanf(file, "<%c> %u %u\n", &code, &size, &totalKg);
    if (res != 3) {
        fprintf(stderr, "Invalid file format.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    *trainSize = size;

    unsigned int i = 0;
    unsigned int currentTotalKg = 0u;
    
    while (i < size && !feof(file)) {
        Wagon wagon = wagon_from_file(file);
        array[i] = wagon;
        currentTotalKg += wagon.weight;
        i++;
    }

    if (currentTotalKg != totalKg) {
        fprintf(stderr, "Total weight does not match.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }
  fclose(file);
}

unsigned int discarded_wagons (Train t, unsigned int size) {
    unsigned int discard_count = 0;
    unsigned int oatmeal_count = 0;
    for (unsigned int i = 0; i < size; i++) {
        if (t[i].cargo == oatmeal) {
            oatmeal_count++;
        } else {
            if (oatmeal_count > 2) {
                discard_count += oatmeal_count - 2;
            }
            oatmeal_count = 0;
        }
    }
    if (oatmeal_count > 2) {
        discard_count += oatmeal_count - 2;
    }
    return discard_count;
}

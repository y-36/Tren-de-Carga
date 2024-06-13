/*
@file wagon.c
@brief Implements wagon structure and methods
*/
#include <stdlib.h>
#include "wagon.h"

Wagon wagon_from_file(FILE* file)
{
  Wagon wagon;
  char cargoType;

    int res = fscanf(file, "%u %c %u\n", &wagon.number, &cargoType, &wagon.weight);
    if (res != 3) {
        fprintf(stderr, "Invalid wagon line format.\n");
        exit(EXIT_FAILURE);
    }

  if (cargoType == 'r') {
    wagon.cargo = rice;
  } else if (cargoType == 'm') {
    wagon.cargo = mushrooms;
  } else if (cargoType == 'o') {
    wagon.cargo = oatmeal;
  } else if (cargoType == 'p') {
    wagon.cargo = rice;
  }

  return wagon;
}

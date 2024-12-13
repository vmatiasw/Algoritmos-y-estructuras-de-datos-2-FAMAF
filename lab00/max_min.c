#include <stdio.h>   /* printf(), scanf() */
#include <stdbool.h> /* tipo bool         */

#include <assert.h> /* assert() */

#define ARRAY_SIZE 10

struct max_min_result
{
  int max_value;
  int min_value;
  unsigned int max_position;
  unsigned int min_position;
};

struct max_min_result compute_max_min(int array[], unsigned int length)
{
  assert(length > 0);
  struct max_min_result result = {array[0], array[0], 0, 0};
  // IMPLEMENTAR
  unsigned int i = 0u;
  while (i < length)
  {
    if (result.max_value < array[i])
    {
      result.max_value = array[i];
      result.max_position = i;
    }
    if (result.min_value > array[i])
    {
      result.min_value = array[i];
      result.min_position = i;
    }
    i = i + 1;
  }

  return result;
}

void ask_array_data(int array[], unsigned int length) {
  unsigned int i = 0u;
  int input = 0;
  while(i < length) {
    scanf("%d", &input);
    array[i] = input;
    ++i;
  }
}

int main(void)
{
  int array[ARRAY_SIZE] = {4, -1, 5, 8, 9, 0, 3, 6, 0, 0};
  // PEDIR AL USUARIO QUE INGRESE LOS ELEMENTOS DEL ARREGLO.
  printf("Ingrese los elementos del arreglo\n");
  ask_array_data(array, ARRAY_SIZE);
  struct max_min_result result = compute_max_min(array, ARRAY_SIZE);
  printf("Máximo: %d\n", result.max_value);
  printf("Posición del máximo: %u\n", result.max_position);
  printf("Mínimo: %d\n", result.min_value);
  printf("Posición del mínimo: %u\n", result.min_position);
  return 0;
}
#include <stdio.h>
#include <stdlib.h>

#include "data.h"

void
print_data(data_t d) {
    printf("NOMBRE: %s\n"
           "EDAD  : %d años\n"
           "ALTURA: %d cm\n\n",
           d.name, d.age, d.height);
}

int main(void) {

    data_t messi = {"Leo Messi", 35, 169};
    print_data(messi);

    printf("name-size  : %lu bytes\n"
           "age-size   : %lu bytes\n"
           "height-size: %lu bytes\n"
           "data_t-size: %lu bytes\n", sizeof(messi.name),sizeof(messi.age),sizeof(messi.height),sizeof(data_t));

    return EXIT_SUCCESS;
}

/*
name-size  : 30 bytes
age-size   : 4 bytes
height-size: 4 bytes
data_t-size: 40 bytes

No da igual pero casi, lo que si es seguro supongo es que no puede dar mayor y por este motivo no da exactamente igual ya que lo 
almacenado no usa el maximo de espacio del tipo. 
*/


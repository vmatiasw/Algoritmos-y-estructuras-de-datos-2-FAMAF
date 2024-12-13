#include <stdlib.h>
#include <stdio.h>
/*
proc absolute(in x : int, out *y : pointer to int)
alloc(y);
if x >= 0 then
*y := x
else
*y := -x
fi
end proc
*/
void absolute(int x, int *y) {
    if (x>=0)
    {
        *y = x;
    }
    else {
        *y=-x;
    }
}

/*
fun main() ret r : int
var a, b : int
a := -10
absolute(a, res)
{- supongamos que print() muestra el valor de una variable -}
print(res)
{- esta última asignación es análoga a `return EXIT_SUCCESS;` -}
r := 0
*/
int main(void) {
    int a=0, res=0;  // No modificar esta declaración
    a = -10;
    absolute(a, &res);
    printf("%d \n",res);
    return EXIT_SUCCESS;
}

/*
El parámetro int *y de absolute() tecnicamente creo yo que en este lenguaje es tipo in aunque el el teorico/practico seria 
de tipo in/out. Esto es asi ya que es ingresada y ademas modifica el valor de res fuera de la funcion.

C creo que solo tiene parametros in por como hemos programado hasta ahora.
*/

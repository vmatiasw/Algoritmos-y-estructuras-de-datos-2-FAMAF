#include <stdlib.h>
#include <stdio.h>

/*
proc absolute(in x : int, out y : int)
if x >= 0 then
y := x
else
y := -x
fi
end proc
*/
void absolute(int x, int y) {
    if (x>=0)
    {
        y = x;
    }
    else {
        y=-x;
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
    int a=0, res=0;
    a = -10;
    absolute(a, res);
    printf("%d \n",res);
    return EXIT_SUCCESS;
}

/*
El programa imprime en pantalla res=0 ya que el programa no esta bien implementado para modificar a la variable res. 
*/


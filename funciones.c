#include <stdlib.h>
#include <stdio.h>
#include <stdint.h> //libreria de los uint16_t
// #include <time.h> //libreria para funciones del tiempo

// ___________________ Shortcuts ________________
/*
--> CTRL + } Comenta o descomenta el bloque seleccionado
--> CTRL + K + CTRL + F ordena la identacion del bloque seleccionado
*/


// ___________________ifdefs________________
/* USO:
    sirven para activar o desactivar parte del codigo para correr una
    funcionalidad  u otra
#define MALLOC // si comento esta linea, no esta definido entonces no entra al if
#define CALLOC
#define REALLOC*/
#define ARRAY_LEN 5
#ifdef MALLOC
    // cosas
#endif
// _________________________________________

// ________ Structs, Unions y enmums ________
/*
// Struct
typedef struct {
    int temperatura;
    int humedad;
} datosSensor_t;
//cómo inicializarlo (dos opciones):
datosSensor_t d = {a, b}; //opcion 1.

datosSensor_t d; //opcion 2: definirlo y luego iniciarlo.
d.temperatura = 10;
d.humedad = 20;
// Union
typedef union {
    int entero;
    float decimal;
    char caracter;
} MiUnion;

// Uso:
MiUnion u;
u.entero = 10;



// Enum:
typedef enum {
    ESTADO_NORMAL,
    ESTADO_ALERTA_TEMP,
    ESTADO_ALERTA_HUM,
    ESTADO_ERROR,
} estado_t;
*/

// _________________ Punteros ________________
/* Declaracion de puntero
int *ptr; // ptr es un puntero a un entero
Inicializacion de puntero
nombre_puntero = &variable;
Ejemplo:
void punteros()
{
    int a = 5;
    ptr = &a; // ptr ahora apunta a la direccion de memoria de 'a'
    int* ptr = &a;
    int **ptrptr = &ptr;
    printf("\na = %d\t\t\t\t Cuanto vale 'a'\n*ptr = %d\t\t\t Lo que esta en la direcciond de memoria guardada en ptr\n&a = %p\t\t La direccion de memoria de 'a'\nptr = %p\t\t La direccion de memoria guardada en ptr\n&ptr = %p\t\t La direccion de memoria de 'ptr'\nptrptr = &ptr = %p \t La direccion de memoria guardada en ptrptr\n",a,*ptr,&a,ptr,&ptr,ptrptr);
    void argumentoUnPuntero(int *p)
    {
        printf("Valor en argumentoUnPuntero: %d\n", *p);
        *p = 20; // Modifica EL VALOR que se encuentra en la direccion de memoria a la que apunta p
    }
    argumentoUnPuntero(ptr)
    argumentoUnPuntero(&a) // Lo mismo que la linea anterior, pero con la direccion de memoria de 'a' directamente
}
int a = 5;
ptr = &a; // ptr ahora apunta a la direccion de memoria de 'a'
int* ptr = &a;
int **ptrptr = &ptr;
printf("\na = %d\t\t\t\t Cuanto vale 'a'\n*ptr = %d\t\t\t Lo que esta en la direcciond de memoria guardada en ptr\n&a = %p\t\t La direccion de memoria de 'a'\nptr = %p\t\t La direccion de memoria guardada en ptr\n&ptr = %p\t\t La direccion de memoria de 'ptr'\nptrptr = &ptr = %p \t La direccion de memoria guardada en ptrptr\n",a,*ptr,&a,ptr,&ptr,ptrptr);
*/
//_________________funciones utiles_________

// Funcion que imprime arrays/vectores:
/*
// declaracion
void print_array(const int *arr, int len, const char *label);
// definicion
void print_array(const int *arr, int len, const char *label) // en *label poner el titulo ente "". Ej: "arr_num_bin"
{
    printf("%s: ", label);
    for (size_t i = 0; i < len; ++i)
    {
        printf(" %d -", arr[i]);
    }
    printf("\n");
}
*/

// Funcion "compress_array" que comprime un array eliminando elementos consecutivos repetidos(y devuelve la nueva longitud del array)
/*
int compress_array(int *arr, int n)
{
    // quiero un for que lea y compare dos vagones. Si son iguales se reescribe con el primero distinto
    // => necesito un contador aux que aumente en un if(arr[i-1]!=arr[i])
    int j = 1;
    for(int i = 1; i<n-1; i++)
    {
        if(arr[i-1] != arr[i])
        {
            
            arr[j] = arr[i];
            j++;
        }
    }return j;
}
*/

// Funcion "bubbleSort" que ordena un array de enteros usando el algoritmo de ordenamiento burbuja
/*
int bubbleSort(int arr[], int length) {
    int i, j, temp;
    int orden = 1;
    for (i = 0; i < length - 1; i++) {
        // Últimos i elementos ya están ordenados
        for (j = 0; j < length - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Intercambiar arr[j] y arr[j+1]
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                orden = 0;
            }
        }
    }return orden;
}



*/
// Funcion Binary Search es biseccion de datos ordenados.
/*
int binarySearch(int arr[], int size, int target) {
    if(arr == NULL)
    {
        return INT32_MIN;
    }
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2; // Evita desbordamiento

        // Verifica si el objetivo está en el medio
        if (arr[mid] == target)
        {
            while(arr[mid-1]==arr[mid])
            {
                printf("\nmid = %d\n", mid);
                mid--;
            }
            
            return mid;

        }       
        
        // Si el objetivo es mayor, ignora la mitad izquierda
        if (arr[mid] < target)
            left = mid + 1;
        // Si el objetivo es menor, ignora la mitad derecha
        else
            right = mid - 1;
    }
    // El elemento no está presente
    return INT32_MIN;
}
*/

//_____MEMORIA DINAMICA, MALLOC CALLOC REALLOC FREE______

// ___________ MALLOC ___________________________________
#ifdef MALLOC
#define ARRAY_LEN 5
int main(void)
{
    int *malloc_array = (int *)malloc(ARRAY_LEN * sizeof(int)); /* No - inicializado */
    // salvataje de error
    if (!malloc_array)
    { /* equivalente a malloc_array == NULL */
        perror("malloc failed");
        return 1;
    }

    // INICIALIZACION DEL ARRAY DE MEMORIA VARIABLE (WARNING: EN MALLOC NO SE INICIALIZA SOLO)
    for (int i = 0; i < ARRAY_LEN; ++i)
    {
        malloc_array[i] = i + 1; /* Inicializo */
    }
    print_array(malloc_array, ARRAY_LEN, "malloc_array");
    free(malloc_array);
    return 1;
}
#endif

//____________ CALLOC ___________________________________
#ifdef CALLOC
int main(void)
{
    printf("\n=== calloc() ===\n");
    int *calloc_array = (int *)calloc(ARRAY_LEN, sizeof(int));

    if (!calloc_array)
    {
        perror("calloc failed");
        return 1;
    }
    /* No necesito inicializarlo, estoy seguro que va a ser 0 */
    print_array(calloc_array, ARRAY_LEN, "calloc_array");
    free(calloc_array);
    return 0;
}
#endif

//____________ REALLOC ___________________________________
#ifdef REALLOC
int main(void)
{
    // Caso a: cambio el tamaño pero no el lugar de memoria
    printf("\n=== realloc() - Caso a: re-asignacion en el lugar ===\n");
    /* (1): creo bloque con malloc. (2): chequeo si se creo correctamente. (3): Inicializo el bloque (array)*/
    // (1):
    int *realloc_array = (int *)malloc(5 * sizeof(int)); 
    // (2):
    if (!realloc_array)
    {
        perror("malloc failed");
        return 1;
    }
    // (3):
    for (int i = 0; i < ARRAY_LEN; i++)
    {
        realloc_array[i] = i + 10; /* inicializo miembros */
    }
    print_array(realloc_array, ARRAY_LEN, "Original array");

    int *original_ptr = realloc_array;
    printf("Original pointer --> %p\n", original_ptr);
    realloc_array = (int *)realloc(realloc_array, (ARRAY_LEN + 1) * sizeof(int)); /* Intento modificar */
    if (!realloc_array)
    { /* esto me indica que falle */
        perror("realloc failed");
        free(original_ptr); /* antes de salir del programa, libero la memoria del bloque original */
        return 1;
    }
    /* Si no falle, continuo */

    /* el bloque original iba de realloc_array[0] a realloc_array[4] --> longitud 5 (ARRAY_LEN)
     * despues de modificarlo, le agregue un miembro, por lo que voy de
     * realloc_array[0] a realloc_array[ARRAY_LEN]
     */
    realloc_array[ARRAY_LEN] = 99; 
    /* i.e. 0x02 + ARRAY_LEN * sizeof(int) = 0x16 = &realloc_array[ARRAY_LEN]*/
    //*(realloc_array + ARRAY_LEN) = 100; // Lo mismo que dos lineas antes pero con puntero.
    print_array(realloc_array, ARRAY_LEN + 1, "realloc array");
    printf("New pointer      --> %p\n", realloc_array);


    // CASO B: se mueve solo de lugar un bloque por aumento excesivo de tamanio
    printf("\n\n\n\n=== realloc() - Case b: El bloque se mueve de lugar ===\n");

    /* uso bloques grandes para 'asegurar' el movimiento */
    int *big = (int *)malloc(1000000 * sizeof(int));
    printf("Original block pointer (big)  --> %p\n", big);

    int *moved = (int *)realloc(big, 2000000 * sizeof(int)); /* Es gigante, ppr lo que probablemente se mueva */
    if (moved)
    {
        printf("→ Large block successfully resized. (it may have moved)\n");
        printf("Moved block pointer (moved)   --> %p\n", moved);
        free(moved);
    }
    else
    {
        printf("→ Failed to realloc large block.\n");
        free(big);
    }

    printf("\n\n\n");

    printf("\n\n\n\n=== realloc() - Case c: No logro modificar el tamanio del bloque ===\n");
    /* Simulo caso de falla usando bloques gigantes */
    int *huge = (int *)malloc(1000 * sizeof(int));
    int *attempt = (int *)realloc(huge, 10000000000000000); /* absurdamente grande */
    if (!attempt)
    { /* me fijo si funciona */
        printf("→ realloc no logro expandir el bloque de memoria .\n\n\n");
        free(huge); /* Importante liberar el original */
    }
    else
    {
        free(attempt);
    }
    return 0;
}
#endif

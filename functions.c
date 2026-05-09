#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "header.h"

/* =============   EJERCICIO 1   ============= */

void createTree(int* arr, int size, BSTNode** root)
{
    *root = NULL; // inicializo la primera vez el root en NULL
    
    for(int i = 0; i < size; i++)
    {
        BSTNode* nuevoPerreque = (BSTNode*) malloc(sizeof(BSTNode));
        // if error.
        if (!nuevoPerreque)
        {
            fprintf(stderr, "Memory allocation failed!\n");
            exit(1);
        }
        nuevoPerreque->data = arr[i];
        nuevoPerreque->left = NULL;
        nuevoPerreque->right = NULL;
        if(*root == NULL)// esto solo anda en la primer vuelta
        {
            *root = nuevoPerreque;
        }
        BSTNode* current = *root; // si es el primer nodo, lo asignamos a la raiz.
        for(;i>0;)
        {
            if(arr[i] < current->data)
            {
                if(current->left == NULL)
                {
                    printf("\nL Se asigno '%d' en la posicion '%d'",arr[i], i);
                    current->left = nuevoPerreque;
                    break;
                }
                current = current->left;
            }else if(arr[i] > current->data)
            {
                if(current->right == NULL)
                {
                    printf("\nR Se asigno '%d' en la posicion '%d'",arr[i], i);
                    current->right = nuevoPerreque;
                    break;
                }
                current = current->right;
            }else
            {
                printf("ERROR: No se pueden insertar valores repetidos en el arbol, modificar el array de entrada\n");
                return;
            }
        }        
    }
}

int findNode(BSTNode* root, int value)
{
    BSTNode* current = root;

    for(int i = 0;current != NULL;i++)
    {
        if(value == current->data)
        {
            return 1;
        }else if(value > current->data)
        {
            current = current->right;
            printf("\nR");
        }else if(value < current->data)
        {
            current = current->left;
            printf("\nL");

        }

    }
    return 0;
}

/* =============   EJERCICIO 2   ============= */

void createGraph(tnode_info_t* info, int size, GraphNode** root) //size es la cantidad de nodos
{
    GraphNode *grafo[size];
    for(int i = 0; i < size; i++)
    {
        GraphNode* nuevoPerreque = (GraphNode*) malloc(sizeof(GraphNode));
         if (!nuevoPerreque)
        {
            fprintf(stderr, "Memory allocation failed!\n");
            exit(1);
        }
        
        if(info[i].nombre_padre == 0)
        {
            *root = nuevoPerreque;
        }
        nuevoPerreque->nombre = info[i].nombre_propio;
        nuevoPerreque->dist_a_padre = info[i].dist_a_padre;
        grafo[i] = nuevoPerreque;
    }
    int j, k;
    k = 0;
    GraphNode *hijos = (GraphNode *)malloc(sizeof(GraphNode));
    if (!hijos)
    { /* equivalente a malloc_array == NULL */
        perror("malloc failed");
    }
    for(int i = 0; i < size; i++)
    {
        for (j = i + 1; j < size - 1; j++)
        {
            if (info[j].nombre_padre == grafo[i]->nombre)
            {
                k++;
                GraphNode *original_ptr = hijos;
                hijos = (GraphNode *)realloc(hijos, (k) * sizeof(GraphNode)); /* Intento modificar */
                if (!hijos)
                { /* esto me indica que falle */
                    perror("hijos failed");
                    free(original_ptr); /* antes de salir del programa, libero la memoria del bloque original */
                    return 1;
                }
                hijos[k - 1] = *grafo[j];
            }
            grafo[i]->children = hijos;
        }
        grafo[i]->num_children = k;
    }
    printf("la cantidad de hijos que tiene es: %d\n",k);
}


void minDistAtLevel(GraphNode* root, int level)
{
    int lvl = level;
    int *l = &lvl;
    int p = 0;
    int *paths = &p;
    //printf("\n la cantdad de hijos que tiene es: %d\n",root->num_children);
    *paths += root->num_children;
    for(int i = 0; i<level;i++)
    {
        countPaths(root->children[i], l, paths);
    }
    int peso [*paths];
    int flagPaths;
    int i = 0;
    pesoPaths(root, *peso, paths, &i, level, &flagPaths);
    // if(root == NULL)
    // {
    //     printf("ERROR no hay nodos al nivel que buscas \n");
    //     return;
    // }

}
void pesoPaths(GraphNode* node, int peso [], int *paths,int *lvl,int level, int *n);
void pesoPaths(GraphNode* node, int peso [], int *paths, int *lvl,int level, int *n)
{
    // necesito crear una funcion que cargue el peso de cada camino en un array, y despues sacar el minimo del array.
    {
        printf("hola\n");
        int newLvl = *lvl + 1;
        paths[*n]+=node->dist_a_padre;
        if(lvl == level)
        {
            printf("Posicion: %d",n);
            printf("Peso camino: %d\n",paths[*n]);

            *n++;
            return;
        }
        else
        {
            for(int i = 0; i<node->num_children;i++)
            {
                pesoPaths(node->children[i], &newLvl, paths);
            }

        }

    }
}
void countPaths(GraphNode* node, int *lvl, int *paths);
void countPaths(GraphNode* node, int *lvl, int *paths)
{
    if(!node)
    {
        return;
    }
    {
        *paths += node->num_children;
        printf("hola\n");
        int newLvl = *lvl - 1;
        
        for(int i = 0; i<node->num_children;i++)
        {
        countPaths(node->children[i], &newLvl, paths);


        }
        
    }else// ver esto que onda
    {
        return;
    }
} 
 

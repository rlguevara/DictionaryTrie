#ifndef TRIE_H
#define TRIE_H

#define LONG_MAX_LINEA  1024
#define NOM_ARCHIVO  "Diccionario.txt" 
#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0]) 
#define ALPHABET_SIZE (26)
#define INDEX(c) ((int)c - (int)'a')
#define FREE(p) \
    free(p);    \
    p = NULL;    
    
    
// Definicion de los nodos del arbol
typedef struct nodo_trie nodo_trie_t;
 
// nodo del arbol
struct nodo_trie{
    int value; // Nos indica si el noso es una hoja
    nodo_trie_t *hijos[ALPHABET_SIZE]; // arreglo de 26 apuntadores
    char sin1[10];
    char sin2[10];
    char sin3[10];
    char def[1000];
};
 
// Definicion del arbol
typedef struct trie trie_t;
 
struct trie
{
    nodo_trie_t *raiz;
    int count;
};

nodo_trie_t *Nuevo_nodo(void);

int Borrar_palabra(nodo_trie_t *pNode, char palabra[], int i, int len);

void Esperar_tecla();

int Nodo_hoja(nodo_trie_t *pNode);

void archivo(trie_t *pTrie, char nombre[]);

void borrar_pal(trie_t *pTrie, char palabra[]);

int buscar(trie_t *pTrie, char palabra[]);

int contar();

void Esperar_tecla();

void help();

void ayuda();

void estadisticas();

void inicializar(trie_t *pTrie);

void insertar(trie_t *pTrie, char palabra[], char sin1[], char sin2[], char sin3[], char def[]);

void insertar_iterativo(trie_t *pTrie);

int isItFreeNode(nodo_trie_t *pNode);

#endif

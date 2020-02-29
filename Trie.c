#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Trie.h"

nodo_trie_t *Nuevo_nodo(void){ //Crea un nodo nuevo
int i;
    nodo_trie_t *pNode = NULL;
 
    pNode = (nodo_trie_t *)malloc(sizeof(nodo_trie_t));
    
    if( pNode ){
        pNode->value   = 0;
        for(i = 0; i < ALPHABET_SIZE; i++){
            pNode->hijos[i] = NULL;
        }
        strcpy(pNode->sin1," ");
        strcpy(pNode->sin2," ");
        strcpy(pNode->sin3," ");
        strcpy(pNode->def," ");
    }
    return pNode;
}    
    
void inicializar(trie_t *pTrie){//Inicializa el arbol
    pTrie->raiz = Nuevo_nodo();
    pTrie->count = 0;
}
 
void insertar(trie_t *pTrie, char palabra[], char sin1[], char sin2[], char sin3[], char def[]){
    int i;
    int length = strlen(palabra);
    int index;
    nodo_trie_t *pNode;
 
    pTrie->count++;
    pNode = pTrie->raiz;
 
    for( i = 0; i < length; i++ ){
        index = INDEX(palabra[i]);
 
        if( pNode->hijos[index] ){
            pNode = pNode->hijos[index];
        }
        else{
            pNode->hijos[index] = Nuevo_nodo();
            pNode = pNode->hijos[index];
        }
    }
    pNode->value = pTrie->count;
   
    strcpy(pNode->sin1,sin1);
    strcpy(pNode->sin2,sin2);
    strcpy(pNode->sin3,sin3);
	strcpy(pNode->def,def);
}
 
int buscar(trie_t *pTrie, char palabra[])
{
    int level;
    int length = strlen(palabra); 
    int index; 
    nodo_trie_t *pNode; 
    
    pNode = pTrie->raiz; 
 
    for( level = 0; level < length; level++ ){
        index = INDEX(palabra[level]); 
 
        if( !pNode->hijos[index] )
        {
            return 0;
        }
 
        pNode= pNode->hijos[index]; 
    }
		if (pNode!=0 && pNode->value){
		printf("%s\n", palabra);
		printf("Sinonimos: %s %s %s\n", pNode->sin1, pNode->sin2, pNode->sin3);
		printf("Definicion: %s\n", pNode->def);
		return 1;
		}
		
		printf("La palabra no se encuentra en el arbol\n");
		
return 0;
}
 
int Nodo_hoja(nodo_trie_t *pNode){
    return (pNode->value != 0);
}
 
int isItFreeNode(nodo_trie_t *pNode){
    int i;
    for(i = 0; i < ALPHABET_SIZE; i++)
    {
        if( pNode->hijos[i] )
            return 0;
    }
    return 1;
}
 
int Borrar_palabra(nodo_trie_t *pNode, char palabra[], int i, int len){
int index;

    if( pNode ){
        if(i==len){
            if(pNode->value){
                pNode->value = 0;
 
                if(isItFreeNode(pNode)){
                    return 1;
                }
                return 0;
            }
        }
        else{
            index = INDEX(palabra[i]);
 
            if(Borrar_palabra(pNode->hijos[index], palabra, i+1, len)){
                FREE(pNode->hijos[index]);
 
                if (!Nodo_hoja(pNode) && isItFreeNode(pNode))
                return 1;
            }
        }
    }
    return 0;
}
 
void borrar_pal(trie_t *pTrie, char palabra[])
{
    int len=strlen(palabra);
 
    if(len>0){
        Borrar_palabra(pTrie->raiz, palabra, 0, len);
    }
}

void archivo(trie_t *pTrie, char nombre[]){
	
   FILE *entrada; 
   char linea[LONG_MAX_LINEA];
   char *token,pal[100],sin1[100],sin2[100],sin3[100],def[1000]; 
   int cn=0,paldef=0;
   nodo_trie_t *pNode;
       
       pNode = pTrie->raiz;
        
			strcpy(pal,"");
			strcpy(sin1,"");
			strcpy(sin2,"");
			strcpy(sin3,"");
			strcpy(def,"");
    
   if ((entrada = fopen(nombre, "r")) == NULL){ 
      perror(NOM_ARCHIVO); 
      exit(1); 
   } 
    
   while (fgets(linea, LONG_MAX_LINEA, entrada) != NULL) {
	        cn=0; 
	        if (paldef%2==0){
				token = strtok(linea ," "); /*Separamos por espacios*/
				while (token != NULL){
					if(cn==0){
						strcpy(pal,token);
					}
					if(cn==1){
						
						strcpy(sin1,token);
					}
					if(cn==2){
						
						strcpy(sin2,token);
					}
					if(cn==3){
						
						strcpy(sin3,token);
					}
					cn++;
					token = strtok(NULL," ");
						
				}
		 } else {
			strcpy(def,linea);
			insertar(pTrie,pal,sin1,sin2,sin3,linea);
			strcpy(pal,"");
			strcpy(sin1,"");
			strcpy(sin2,"");
			strcpy(sin3,"");
			strcpy(def,"");
		 }
        paldef++;
	}
   fclose(entrada);  
	}

void insertar_iterativo(trie_t *pTrie){
	
	FILE *entrada;
	char pal[100],sin1[100],sin2[100],sin3[100],def[1000],string[50];
	printf("Introduzca el nombre del archivo que va a crear o al cual se va a agregar palabras\n");
	scanf("%s",string);
	
	if ((entrada = fopen(string, "a")) == NULL){ 
      perror(string); 
      exit(1); 
   }  
	printf("\nPalabra: ");
	gets(pal);
	gets(pal);
	printf("\nSinonimo: ");
	gets(sin1);
	printf("\nSinonimo: ");
	gets(sin2);
	printf("\nSinonimo: ");
	gets(sin3);
	printf("\nDefinicion: ");
	gets(def);
	printf("\n\n");
	fprintf(entrada,"%s %s %s %s\n%s\n",pal,sin1,sin2,sin3,def);
	fclose(entrada);
	insertar(pTrie,pal,sin1,sin2,sin3,def);
}

int contar(){
	int cont=0, paldef=0;
	
	FILE *entrada; 
    char linea[LONG_MAX_LINEA];
    char string[50];
       
   printf("Introduzca el nombre del archivo\n");
   scanf("%s",string);
   
   if ((entrada = fopen(string, "r")) == NULL){ 
      perror(string); 
      return EXIT_FAILURE; 
   } 
   while (fgets(linea, LONG_MAX_LINEA, entrada) != NULL) {
	   if (paldef%2==0){
	   cont++;
   }
   paldef++;
	}
	fclose(entrada);
	printf("La cantidad de palabras es: %d\n", cont);
	
	return 0;
}

void Esperar_tecla(){
	setbuf(stdin,NULL);
	getchar();
	system("clear");
}

void ayuda(){
	printf("\nBienvenido!!\n");
	printf("Para utilizar el programa introduzca el numero de la funcion que desea realizar\n");
	printf("Por ejemplo: 1 Crear (Crea un archivo o introduce mas palabras en el)");
	printf("Se debe tener en cuenta que solo se pueden introducir las palabras en minusculas\n\n");
	}
	
void help(){
	printf("\nBienvenido!!\n");
	printf("Para ingresar el archivo a utilizar coloque el siguiente comando: a nombre del archivo\n");
	printf("Para ver las estadisticas del diccionario coloque el siguiente comando: s\n");
	printf("Para buscar una palabra se utiliza el comando: palabra\n");
	Esperar_tecla();
	}

void estadisticas(){
	printf("Las estadisticas del diccionario son las siguientes: \n");
	contar();
	}

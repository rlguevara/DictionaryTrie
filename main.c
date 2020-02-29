#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Trie.h"

char nombrearch[100];


int main(int argc,char *argv[]){
int caso;
trie_t trie;
inicializar(&trie);
char string[100];

if(argc==1){
cas:
printf("0 salir  1 crear  2 archivo  3 eliminar\n4 buscar  5 estadistica  6 help \n");
scanf("%d",&caso);
system("clear");
switch(caso){
	case 1:
		insertar_iterativo(&trie);		
		goto cas;
	case 2:
		printf("Nombre del archivo: ");
		scanf("%s",nombrearch);
		printf("\n");
		archivo(&trie,nombrearch);
		printf("Presione una tecla para continuar...");
		Esperar_tecla();		
		goto cas;
	case 3:
		printf("Palabra a eliminar: ");
		scanf("%s",string);
		printf("\n");
		borrar_pal(&trie, string);
		printf("Se ha borrado la palabra\n\n");
		printf("Presione una tecla para continuar...");
		Esperar_tecla();
		goto cas;	
	case 4:
		printf("Palabra a buscar: ");
		scanf("%s",string);
		printf("\n");
		if(buscar(&trie, string)==0)
		printf("La palabra no se encuentra en el arbol\n\n");
		else
		printf("Se ha encontrado la palabra\n\n");
		printf("Presione una tecla para continuar...");
		Esperar_tecla();
		goto cas;
	case 5:
		contar();
		printf("Presione una tecla para continuar...");
		Esperar_tecla();
		goto cas;	
	case 6:
		ayuda();
		printf("Presione una tecla para continuar...");
		Esperar_tecla();
		goto cas;
			
	case 0:
		break;
	default:
		goto cas;
}
}
else{
	if(strcmp(argv[1],"h")==0)
		help();
	if(strcmp(argv[1],"s")==0)
		estadisticas();	
	if(strcmp(argv[1],"a")==0){
		archivo(&trie,argv[2]);
		goto cas;	
	}
	if(strcmp(argv[1],"palabra")==0){
		printf("Nombre del archivo: ");
		scanf("%s",nombrearch);
		printf("\n");
		archivo(&trie,nombrearch);
		printf("Palabra a buscar: ");
		scanf("%s",string);
		printf("\n");	
		buscar(&trie,string);
	}		
}
	return 0;
}

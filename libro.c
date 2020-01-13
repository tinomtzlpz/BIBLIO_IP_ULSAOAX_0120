#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char titulo[50];
    char autor[50];
    int lleno;
}libro;

typedef struct{
    char titulo[50];
    int lleno;
    libro libros[50];
}biblioteca;

biblioteca bibliotecas[50];
        
void abiblio();
void alibro();
void clibro();
void vaciar();
void cambiar(char palabras[50]);

int main(){
    int opcion, continuar;
    
    vaciar();
    
    do{
        do{
            printf("sleccione una opcion: \n\n");
            printf("[1] - agregar.\n");
            printf("[2] - listar.\n");
            printf("[3] - buscar.\n");
            printf("opcion: ");
            scanf("%i", &opcion);
            printf("\n");
        } while(opcion < 1 || opcion > 3);
        switch(opcion){
                case 1:{
            abiblio(opcion);
            break;
                }
                case 2:{
                alibro(opcion);
                break;
            }
                case 3:{
                clibro(opcion);
                break;
            }
    }
        printf("quieres continuar?.");
    printf("[1] - continuar. \n");
    printf("[2] - salir del programa.\n\n");
    printf("opcion: ");
    scanf("%i", &continuar);
    printf("\n");
    } while(continuar == 1);
    
    system("pause");
    return 0;
}

void abiblio(){
    int i, aux;
    
    aux = 0;
    
    for(i = 0; i < 50 && aux == 0; i++){
        if(bibliotecas[i].lleno == 0){
            printf("introduce un nombre para la biblioteca: ");
            fflush(stdin);
            fgets(bibliotecas[i].titulo,50,stdin);
            cambiar(bibliotecas[i].titulo);
            printf("\n");
            printf("bibliotecas introducidas: %i\n\n",i+1);
            bibliotecas[i].lleno = 1;
            aux =1;
        }
    }
}
void alibro(){
    int i,j,aux,opcion;
    
    aux = 0;
    
    do{
        printf("selecciona la biblioteca donde quieres guardar el libro:\n\n");
        for(i = 0; i < 50; i++){
            printf("%i - %s.\n",i,bibliotecas[i].titulo);
        }
        printf("opcion: ");
        scanf("%i", &opcion);
        printf("\n");
    }while(opcion < 0 || opcion > 50);
    
    for(i = 0; i < 50; i++){
        for(j = 0; j < 50 && aux == 0; j++){
            if(bibliotecas[opcion].libros[j].lleno == 0){
                printf("introduce un titulo para el libro: ");
                fflush(stdin);
                fgets(bibliotecas[i].libros[j].titulo,50,stdin);
                cambiar(bibliotecas[i].libros[j].titulo);
                printf("\n");
                printf("ahora introduce el nombre del autor del libro: ");
                fflush(stdin);
                fgets(bibliotecas[i].libros[j].autor,50,stdin);
                cambiar(bibliotecas[i].libros[j].autor);
                printf("\n");
                printf("libros registrados: %i.\n\n",j+1);
                bibliotecas[opcion].libros[j].lleno = 1;
                aux = 1;
            }
        }
    }
}
void clibro(){
    int i,j,aux,comparar;
    char comprobar[50];
    
    aux = 0;
    printf("introuce el titulo el libro que deseas buscar: ");
    fflush(stdin);
    fgets(comprobar,50,stdin);
    cambiar(comprobar);
    printf("\n");
    for(i = 0; i < 50; i++){
        for(j = 0; j < 50 && aux == 0; j++){
            comparar = strcmp(comprobar,bibliotecas[i].libros[j].titulo);
            if(comparar == 0){
                printf("el libro %s se encuentra en la estanteria %s y pertenece al autor %s.\n\n",bibliotecas[i].libros[j].titulo,bibliotecas[i].titulo,bibliotecas[i].libros[j].autor);
                aux = 1;
            }
        }
    }
}
void vaciar(){
    int i,j;
    
    for(i = 0; i < 50; i++){
        for(j = 0; j < 50; j++){
            bibliotecas[i].lleno = 0;
            bibliotecas[i].libros[j].lleno = 0;
        }
    }
}
void cambiar(char bibliotecas[50]){
    int i,j,aux;
    
    aux = 0;
    for(i = 0; i < 50; i++){
        for(j = 0; j < 50; j ++){
            if(bibliotecas[i] == '\n'){
                bibliotecas[i] = '\0';
            }
        }
    }
}

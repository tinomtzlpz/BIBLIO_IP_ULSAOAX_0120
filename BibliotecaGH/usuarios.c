#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"datatypes.h"

#define MAT 10 					
#define NOM 40
#define CAR 40

void agregarusuario();
void listar();
void buscar();  
void modificar();

void admon_usuarios() {
    
    int opcion = 0;
    do{
		printf("Escoge\n");
		printf("(1)Agregar usuario\n");
		printf("(2)listar usuarios\n");
		printf("(3)Busqueda de usuario\n");
		printf("(4)Menu principal\n");
        scanf("%d", &opcion);
        switch(opcion){
            case 1:
                agregarusuario();
                break;
            case 2:
                listar();
                break;
            case 3:
                buscar();
                break;
        	default:
                printf("Adios\n");
        }
        
    }while(opcion != 0);

    return 0;
}
void agregarusuario(){
    FILE *archivo;
    archivo = fopen("usuarios.dat", "ab");
    
    usuario USUARIO;
    printf("\nMATRICULA?: ");
    scanf("%s", &usuario.matricula);
    printf("\nNOMBRE?: ");
    scanf("%s", &usuario.nombre);
    printf("\nCARRERA?: ");
    scanf("%s", &usuario.carrera);
    
    fwrite(&usuario, sizeof(USUARIO), 1, archivo);
    fclose(archivo);
    
}

void listar(){
    FILE* archivo;
    archivo = fopen("usuarios.dat", "rb");
    usuario USUARIO;
    while(fread(&USUARIO, sizeof(usuario), 1, archivo) != 0){
        printf("%s %s %s\n",usuario.matricula,usuario.nombre,usuario.carrera);
    }
}
void buscar(){
    char nombre[40];
    printf("NOMBRE: ");
    scanf("%s", nombre);
    
    FILE *archivo;
    archivo = fopen("usuarios.dat", "rb+");
    usuario USUARIO;
    int bandera = 1;
    while(bandera){
        fread(&USUARIO, sizeof(USUARIO), 1, archivo) != 0;
        if(strcmp(nombre,usuario.nombre) == 0){
        	printf("%s %s %s\n",usuario.matricula,usuario.nombre,usuario.carrera);
            bandera = 0;
        }
    }
    fclose(archivo);
}

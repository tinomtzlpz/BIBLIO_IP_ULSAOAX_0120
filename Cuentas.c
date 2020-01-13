#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAT 10
#define NOM 40
#define CAR 40
typedef struct{
	char matricula[MAT];
	char nombre[NOM];
	char carrera[CAR];
}USUARIO;

void agregarusuario();
void listar();
void buscar();
void modificar();

int main() {
    
    int opcion = 0;
    do{
		printf("Escoge\n");
		printf("(1)Agregar usuario\n");
		printf("(2)listar usuarios\n");
		printf("(3)Menu principal\n");
        scanf("%d", &opcion);
        switch(opcion){
            case 1:
                agregarusuario();
                break;
            case 2:
                listar();
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
    
    USUARIO usuario;
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
    USUARIO usuario;
    while(fread(&usuario, sizeof(USUARIO), 1, archivo) != 0){
        printf("%s %s %s\n",usuario.matricula,usuario.nombre,usuario.carrera);
    }
}


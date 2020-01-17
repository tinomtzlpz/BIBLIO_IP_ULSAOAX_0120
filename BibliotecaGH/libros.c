#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include "datatypes.h"

void admon_libros_agregar();
void admon_libros_listar();
void admon_libros_buscar();
void cambiar();

int main(int argc, char** argv) {
    carga_datos_de_archivos();
    admon_libros();
    return (0);
}

void admon_libros(){
    char opcion = '0', c;
    system("clear");
    printf("Bienvenido al modulo de libros\n");
    printf("\n");
    sleep(1);
    do{
        //system("clear");
        printf("\t[1] Agregar Libro\n");
        printf("\t[2] listar libro\n");
        printf("\t[3] buscar libro\n");
        printf("\t[4] eliminar libro\n");
        printf("\n");
        printf("\t\tOpcion: ");
        scanf("%c", &opcion);
        while((c = getc(stdin)) != '\n' && c != EOF); //Esta linea hace flush a la entrada standard, no quitar
        //fflush(stdin);
        opcion = toupper(opcion);
        switch(opcion)
        {
            case '1':
                        //system("clear");
                        printf("Se ha llamado al modulo de agregar libro\n");
                        //Aqui estará la llamada real a la función de administracion de usuarios
                        admon_libros_agregar();
                        //Aqui estara la funcion de void_libros_agregar//
                        //sleep(2);
                        //system("clear");
                        break;
            case '2':
                        //system("clear");
                        printf("Se ha llamado al modulo de listar libro\n");
                        //Aqui estará la llamada real a la función de administracion de libros
                        admon_libros_listar();
                        break;
            case '3':
                        //system("clear");
                        //printf("Se ha llamado al modulo de administracion de prestamos\n");
                        //Aqui estará la llamada real a la función de administracion de prestamos
                        //sleep(2);
                        printf("Se ha llamado al modulo de buscar libro\n");
                        admon_libros_buscar();
                        break;
            //case '4':   
                        //system("clear");
                        //eliminar libro//
                        //system("clear");
                       // break;
            default:
                        return;
                        break;
        }
    }
    while(1);
}

//Aqui se agregan los libros//
void admon_libros_agregar(){
    char opcion = '0', c;
    unsigned short int i=0;
     //system("clear");
     for(i=0;i<MAX_ELEMENTOS_ARRAY;i++){
        
         if(array_de_libros[i].id_ejemplar==0)
         {
            printf("\t Titulo de libro: \n");
            fgets(array_de_libros[i].titulo,100,stdin);
            while((c = getc(stdin)) != '\n' && c != EOF);
            printf("\t Nombre del autor: \n");
            fgets(array_de_libros[i].autor,150,stdin);
            while((c = getc(stdin)) != '\n' && c != EOF);
            printf("\t Nombre de la editorial: \n");
            fgets(array_de_libros[i].editorial,100,stdin);
            while((c = getc(stdin)) != '\n' && c != EOF);
            printf("\t Anio de edicion:\n");
            scanf("%d", &array_de_libros[i].anio_edicion);
            while((c = getc(stdin)) != '\n' && c != EOF);
            printf("\t Identificador de ejemplar del libro: \n");
            scanf("%d", &array_de_libros[i].id_ejemplar);
            while((c = getc(stdin)) != '\n' && c != EOF);
            printf("\t ISBN: \n");
            scanf("%s", &array_de_libros[i].isbn);
            while((c = getc(stdin)) != '\n' && c != EOF);
            guarda_datos_en_archivos();
            break;
         }
     }
    //system("clear");
    }

//Aqui se listaran los libros//
void admon_libros_listar()
{
    char c;
    short int i=0;

    /* Mostrar los datos que están en el array correspondiente */
    //system("clear");
     for(i=0; i < MAX_ELEMENTOS_ARRAY; i = i+1)
         
    {
         if (array_de_libros[i].id_ejemplar != 0){
        printf("%0.2d.- ",i+1);
        printf("\t Titulo de libro: %s\n", array_de_libros[i].titulo); fflush(stdin);
        printf("\t Nombre del autor: %s\n", array_de_libros[i].autor); fflush(stdin);
        printf("\t Nombre de la editorial: %s\n", array_de_libros[i].editorial); fflush(stdin);
        printf("\t Anio de edicion: %u \n", array_de_libros[i].anio_edicion); fflush(stdin);
        printf("\t Identificador de ejemplar del libro: %u \n", array_de_libros[i].id_ejemplar); fflush(stdin);
        printf("\t ISBN: %s\n", array_de_libros[i].isbn); fflush(stdin);
         }
    }
}
   
       

//Aqui se buscan los libros//
void admon_libros_buscar()
{
    char c;
    short int i=0;
    /* Mostrar los datos que están en el array correspondiente */
    //system("clear");}
    short int ingreso;
    short int elegir;
    char palabra[100];
    printf("\t[1] Buscar por ID Ejemplar \n ");
    printf("\t[2] Buscar por ISBN \n");
    printf("\t[3] Bucsar por Titulo\n");
    scanf("%d", &elegir);
    while((c = getc(stdin)) != '\n' && c != EOF);
    switch(elegir)
    {
        case 1:
            printf("ingresa el id ejemplar que quieres buscar");
            scanf("%d",&ingreso);
            while((c = getc(stdin)) != '\n' && c != EOF);
            for(i=0; i < MAX_ELEMENTOS_ARRAY; i = i+1)
            {
                 if (array_de_libros[i].id_ejemplar !=0 && ingreso==array_de_libros[i].id_ejemplar)
                {
                    printf("\t Titulo de libro: %s\n", array_de_libros[i].titulo); fflush(stdin);
                    printf("\t Nombre del autor: %s\n", array_de_libros[i].autor); fflush(stdin);
                    printf("\t Nombre de la editorial: %s\n", array_de_libros[i].editorial); fflush(stdin);
                    printf("\t Anio de edicion: %d \n", array_de_libros[i].anio_edicion); fflush(stdin);
                    printf("\t Identificador de ejemplar del libro: %d \n", array_de_libros[i].id_ejemplar); fflush(stdin);
                    printf("\t ISBN: %s\n", array_de_libros[i].isbn); fflush(stdin);
                    break;
                 }
            }
            break;
        case 2:
            printf("ingresa el ISBN que quieres buscar");
            fgets(palabra,100,stdin);
            while((c = getc(stdin)) != '\n' && c != EOF);
            for(i=0; i < MAX_ELEMENTOS_ARRAY; i = i+1)
            {
                 if (array_de_libros[i].id_ejemplar !=0 && (strcmp(palabra,array_de_libros[i].isbn))==0)
                 {
                    printf("\t Titulo de libro: %s\n", array_de_libros[i].titulo); fflush(stdin);
                    printf("\t Nombre del autor: %s\n", array_de_libros[i].autor); fflush(stdin);
                    printf("\t Nombre de la editorial: %s\n", array_de_libros[i].editorial); fflush(stdin);
                    printf("\t Anio de edicion: %d \n", array_de_libros[i].anio_edicion); fflush(stdin);
                    printf("\t Identificador de ejemplar del libro: %d \n", array_de_libros[i].id_ejemplar); fflush(stdin);
                    printf("\t ISBN: %s\n", array_de_libros[i].isbn); fflush(stdin);
                    break;
                 }
            }
            break;
            
        case 3:
            printf("ingresa el titulo que quieres buscar");
            fgets(palabra,100,stdin);
            while((c = getc(stdin)) != '\n' && c != EOF);
            for(i=0; i < MAX_ELEMENTOS_ARRAY; i = i+1)
            {
                 if (array_de_libros[i].id_ejemplar != 0 && (strcmp(palabra,array_de_libros[i].isbn))==0)
                 {
                    printf("\t Titulo de libro: %s\n", array_de_libros[i].titulo); fflush(stdin);
                    printf("\t Nombre del autor: %s\n", array_de_libros[i].autor); fflush(stdin);
                    printf("\t Nombre de la editorial: %s\n", array_de_libros[i].editorial); fflush(stdin);
                    printf("\t Anio de edicion: %d \n", array_de_libros[i].anio_edicion); fflush(stdin);
                    printf("\t Identificador de ejemplar del libro: %d \n", array_de_libros[i].id_ejemplar); fflush(stdin);
                    printf("\t ISBN: %s\n", array_de_libros[i].isbn); fflush(stdin);
                    break;
                    
                 }
            }
            break;
        default:
            printf("OPCION INVALIDO");
            break;
    }
    
} 

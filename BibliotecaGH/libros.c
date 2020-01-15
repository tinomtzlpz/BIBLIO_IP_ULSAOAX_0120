#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include "datatypes.h"

void admon_libros_agregar();
void admon_libros_listar();

int main(int argc, char** argv) {
    admon_libros();
}

void admon_libros(){
    char opcion = '0', c;
    system("clear");
    printf("Bienvenido al modulo de libros\n");
    printf("\n");
    sleep(1);
    do{
        system("clear");
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
                        system("clear");
                        printf("Se ha llamado al modulo de agregar libro\n");
                        //Aqui estará la llamada real a la función de administracion de usuarios
                        admon_libros_agregar();
                        //Aqui estara la funcion de void_libros_agregar//
                        sleep(2);
                        system("clear");
                        break;
            case '2':
                        system("clear");
                        printf("Se ha llamado al modulo de listar libro\n");
                        //Aqui estará la llamada real a la función de administracion de libros
                        admon_libros_listar();
                        sleep(2);
                        system("clear");
                        break;
            case '3':
                        system("clear");
                        //printf("Se ha llamado al modulo de administracion de prestamos\n");
                        //Aqui estará la llamada real a la función de administracion de prestamos
                        //sleep(2);
                        system("clear");
                        break;
            case '4':
                        system("clear");
                        //eliminar libro//
                        system("clear");
            default:
                        return;
        }
    }
    while(1);
}

//Aqui se agregan los libros//
void admon_libros_agregar(){
    char opcion = '0', c;
    unsigned short int i=0;
     system("clear");

    {
        printf("\t Titulo de libro: %s\n",array_de_libros[i].titulo); fflush(stdin);
        scanf("%s", &array_de_libros[i].titulo);
        while((c = getc(stdin)) != '\n' && c != EOF);
        printf("\t Nombre del autor: %s\n",array_de_libros[i].autor); fflush(stdin);
        scanf("%s", &array_de_libros[i].autor);
        while((c = getc(stdin)) != '\n' && c != EOF);
        printf("\t Nombre de la editorial: %s\n",array_de_libros[i].editorial); fflush(stdin);
        scanf("%s", &array_de_libros[i].editorial);
        while((c = getc(stdin)) != '\n' && c != EOF);
        printf("\t Anio de edicion: %d\n",array_de_libros[i].anio_edicion); fflush(stdin);
        scanf("%d", &array_de_libros[i].anio_edicion);
        while((c = getc(stdin)) != '\n' && c != EOF);
        printf("\t Identificador de ejemplar del libro: %d\n", array_de_libros[i].id_ejemplar); fflush(stdin);
        scanf("%d", &array_de_libros[i].id_ejemplar);
        while((c = getc(stdin)) != '\n' && c != EOF);
        printf("\t ISBN: %s\n",array_de_libros[i].isbn); fflush(stdin);
        scanf("%s", &array_de_libros[i].isbn);
        while((c = getc(stdin)) != '\n' && c != EOF);
    }
    system("clear");
    }

//Aqui se listaran los libros//
void admon_libros_listar(){
    char opcion = '0', c;
    unsigned short int i=0;

    /* Mostrar los datos que están en el array correspondiente */
    system("clear");
    {
        printf("\t Titulo de libro: %s\n",array_de_libros[i].titulo); fflush(stdin);
        printf("\t Nombre del autor: %s\n",array_de_libros[i].autor); fflush(stdin);
        printf("\t Nombre de la editorial: %s\n",array_de_libros[i].editorial); fflush(stdin);
        printf("\t Anio de edicion: %d\n",array_de_libros[i].anio_edicion); fflush(stdin);
        printf("\t Identificador de ejemplar del libro: %d\n", array_de_libros[i].id_ejemplar); fflush(stdin);
        printf("\t ISBN: %s\n",array_de_libros[i].isbn); fflush(stdin);
        while((c = getc(stdin)) != '\n' && c != EOF);
    }
    //sleep(8);
    printf("\n\nCerrando archivo y regresando a modulo de libros"); fflush(stdin);
    system("clear");
    printf("\n"); fflush(stdin);
    }

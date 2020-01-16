/* 
 * File:   main.c
 * Author: tino
 *
 * Created on 9 de enero de 2020, 01:03 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include "datatypes.h"
void genera_arrays_de_prueba();

const char *name_dayweek[10] =
{
    "Domingo",
    "Lunes",
    "Martes",
    "Miercoles",
    "Jueves",
    "Viernes",
    "Sabado"
};

const char *lista_carreras[20] =
{
    "Contaduria",
    "Negocios",
    "Arquitectura",
    "Enfermeria",
    "Fisioterapia",
    "Psicologia",
    "Nutricion",
    "Deporte",
    "Artes",
    "Comunicacion",
    "Derecho",
    "Educacion",
    "Gastronomia",
    "Turismo",
    "Lenguas",
    "Electronica",
    "Sistemas",
    "Industrial",
    "Civil",
    "Ambiental"
};

int main(int argc, char** argv) {
    
    carga_datos_de_archivos();
    char opcion = '0', c;
    system("clear");
    printf("Bienvenido al programa de administracion de biblioteca\n");
    printf("\n");
    sleep(1); //Mostrar el mensaje de bienvenida por 1 segundo y pasar al menú principal
    do{
        system("clear");
        printf("\t[A] Administracion de usuarios\n");
        printf("\t[B] Administracion de libros\n");
        printf("\t[C] Administracion de prestamos\n");
        printf("\n");
        printf("\t\tOpcion: ");
        scanf("%c", &opcion);
        while((c = getc(stdin)) != '\n' && c != EOF); //Esta linea hace flush a la entrada standard, no quitar
        //fflush(stdin);
        opcion = toupper(opcion);
        switch(opcion)
        {
            case 'A':
                        system("clear");
                        //printf("Se ha llamado al modulo de administracion de usuarios\n");
                        admon_usuarios();
                        //sleep(2);
                        system("clear");
                        break;
            case 'B':
                        system("clear");
                        //printf("Se ha llamado al modulo de administracion de libros\n");
                        admon_libros();
                        sleep(2);
                        system("clear");
                        break;
            case 'C':
                        system("clear");
                        //printf("Se ha llamado al modulo de administracion de prestamos\n");
                        //Aqui estará la llamada real a la función de administracion de prestamos
                        admon_prestamos();
                        //sleep(2);
                        system("clear");
                        break;
            case 'Z':
                        system("clear");
                        printf("Se ha llamado al modulo que genera archivos de prueba\n");
                        genera_arrays_de_prueba();
                        //sleep(1);
                        system("clear");
                        break;
            default:
                        system("clear");
                        guarda_datos_en_archivos();
                        printf("\n\n\nGracias por usar el programa de administracion de biblioteca\n");
                        fflush(stdin);
                        exit(EXIT_SUCCESS);
                        break;
        }
    }while(1);
    
    return (EXIT_SUCCESS);
}


void genera_arrays_de_prueba()
{
    /* Datos de prueba de usuarios*/
    array_de_usuarios[0].matricula = 100000001;
    array_de_usuarios[0].carrera = Ambiental;
    strcpy(array_de_usuarios[0].nombre, "John Doe");
    //////////////////////////////////////////
    array_de_usuarios[1].matricula = 100000002;
    array_de_usuarios[1].carrera = Electronica;
    strcpy(array_de_usuarios[1].nombre, "Jane Doe");
    
    /* Datos de prueba de libros*/
    array_de_libros[0].id_ejemplar = 1;
    array_de_libros[0].anio_edicion = 2013;
    strcpy(array_de_libros[0].titulo, "C How to program");
    strcpy(array_de_libros[0].autor, "Deitel & Deitel");
    strcpy(array_de_libros[0].editorial, "Pearson");
    strcpy(array_de_libros[0].isbn, "978-0-13-299044-8");
    //////////////////////////////////////
    array_de_libros[1].id_ejemplar = 2;
    array_de_libros[1].anio_edicion = 2011;
    strcpy(array_de_libros[1].titulo, "Head First C");
    strcpy(array_de_libros[1].autor, "Griffiths & Griffiths");
    strcpy(array_de_libros[1].editorial, "O'Reilly");
    strcpy(array_de_libros[1].isbn, "978-1-449-39991-7");
    ///////////////////////////////////////
    array_de_libros[2].id_ejemplar = 3;
    array_de_libros[2].anio_edicion = 2013;
    strcpy(array_de_libros[2].titulo, "C How to program");
    strcpy(array_de_libros[2].autor, "Deitel & Deitel");
    strcpy(array_de_libros[2].editorial, "Pearson");
    strcpy(array_de_libros[2].isbn, "978-0-13-299044-8");
    //////////////////////////////////////
    array_de_libros[3].id_ejemplar = 4;
    array_de_libros[3].anio_edicion = 2011;
    strcpy(array_de_libros[3].titulo, "Head First C");
    strcpy(array_de_libros[3].autor, "Griffiths & Griffiths");
    strcpy(array_de_libros[3].editorial, "O'Reilly");
    strcpy(array_de_libros[3].isbn, "978-1-449-39991-7");    
}

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
                        printf("Se ha llamado al modulo de administracion de usuarios\n");
                        //Aqui estará la llamada real a la función de administracion de usuarios
                        sleep(2);
                        system("clear");
                        break;
            case 'B':
                        system("clear");
                        printf("Se ha llamado al modulo de administracion de libros\n");
                        //Aqui estará la llamada real a la función de administracion de libros
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

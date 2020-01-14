/* 
 * File:   prestamos.c
 * Author: tino
 *
 * Created on 14 de enero de 2020, 12:55 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "datatypes.h"

void admon_prestamos()
{
    unsigned short int i=0;

    /* Mostrar los datos que están en el array correspondiente */
    system("clear");
    printf("Informacion de prestamos obtenida desde el archivo:\n\n");
    for(i=0; i < MAX_ELEMENTOS_ARRAY; i = i+1)
    {
        printf("%02d.-  ", i+1);
        printf("\tMatricula del usuario: %d\n",array_de_prestamos[i].matricula); fflush(stdin);
        printf("\tIdentificador de ejemplar del libro: %d\n", array_de_prestamos[i].id_ejemplar); fflush(stdin);
        printf("\tFecha de prestamo [dd/m/aaaa]: %02d/%02d/%04d\n",array_de_prestamos[i].fecha_prestamo.dia, \
                array_de_prestamos[i].fecha_prestamo.mes,array_de_prestamos[i].fecha_prestamo.anio); fflush(stdin);
        printf("\tFecha de devolucion [dd/m/aaaa]: %02d/%02d/%04d\n\n\n\n",array_de_prestamos[i].fecha_devolucion.dia, \
                array_de_prestamos[i].fecha_devolucion.mes,array_de_prestamos[i].fecha_devolucion.anio); fflush(stdin);
    }
    sleep(8);
    printf("\n\nCerrando archivo y regresando a menu principal"); fflush(stdin);
    sleep(1);
    system("clear");
    printf("\n"); fflush(stdin);   
}

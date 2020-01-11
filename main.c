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
#include "datatypes.h"
/*
 * 
 */
int main(int argc, char** argv) {
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
                        printf("\n\n\nGracias por usar el programa de administracion de biblioteca\n");
                        //fflush(stdin);
                        exit(EXIT_SUCCESS);
                        break;
        }
    }while(1);

    return (EXIT_SUCCESS);
}

void admon_prestamos()
{
    unsigned short int i=0;

    prestamo array_de_prestamos[10];
    prestamo prestamos_desde_archivo[10]; //Este array contendra los datos del archivo binario
    FILE *pArchivo;
    
    /* Abrir archivo binario para escribir los datos*/
    pArchivo = fopen("prestamos.est","wb");
    if(pArchivo==NULL)
    {
        printf("\nError al abrir el archivo prestamos.est");
        exit(1);
    }
    //El arcivo se abrio correctamente
    
    /* Obtener los datos de los prestamos */
    for(i=0; i < 10; i = i+1)
    {
        printf("Matricula del usuario: "); fflush(stdin);
        scanf("%d", &array_de_prestamos[i].matricula);
        printf("Identificador de ejemplar del libro: "); fflush(stdin);
        scanf("%d", &array_de_prestamos[i].id_ejemplar);
        printf("Fecha de prestamo\n"); fflush(stdin);
        printf("Dia [1-31]: "); fflush(stdin);
        scanf("%d", &array_de_prestamos[i].fecha_prestamo.dia);
        printf("Mes [1-12]: "); fflush(stdin);
        scanf("%d", &array_de_prestamos[i].fecha_prestamo.mes);
        printf("Año [Ejemp. 2020]: "); fflush(stdin);
        scanf("%d", &array_de_prestamos[i].fecha_prestamo.anio);
        printf("Fecha de devolucion\n"); fflush(stdin);
        printf("Dia [1-31]: "); fflush(stdin);
        scanf("%d", &array_de_prestamos[i].fecha_prestamo.dia);
        printf("Mes [1-12]: "); fflush(stdin);
        scanf("%d", &array_de_prestamos[i].fecha_prestamo.mes);
        printf("Año [Ejemp. 2020]: "); fflush(stdin);
        scanf("%d", &array_de_prestamos[i].fecha_prestamo.anio);
    }
    /* Escribir los datos de los prestamos al archivo */
    fwrite(array_de_prestamos,sizeof(prestamo),10,pArchivo);
    fclose(pArchivo); //Cerrar el archivo
    
    /* Abrir el archivo binario en modo lectura */
    pArchivo = fopen("prestamos.est","rb");
    if(pArchivo==NULL)
    {
        printf("\nError al abrir el archivo prestamos.est");
        exit(1);
    }
    /* Leer el contenido del archivo */
    fread(prestamos_desde_archivo, sizeof(prestamo),10,pArchivo);
    /* Mostrar los datos leidos desde el archivo */
    system("clear");
    printf("Informacion de prestamos obtenida desde el archivo:\n\n");
    for(i=0; i < 10; i = i+1)
    {
        printf("%02d.-  ", i+1);
        printf("\tMatricula del usuario: %d\n",prestamos_desde_archivo[i].matricula); fflush(stdin);
        printf("\tIdentificador de ejemplar del libro: %d\n", prestamos_desde_archivo[i].id_ejemplar); fflush(stdin);
        printf("\tFecha de prestamo [dd/m/aaaa]: %02d/%02d/%04d\n",prestamos_desde_archivo[i].fecha_prestamo.dia, \
                prestamos_desde_archivo[i].fecha_prestamo.mes,prestamos_desde_archivo[i].fecha_prestamo.anio); fflush(stdin);
        printf("\tFecha de devolucion [dd/m/aaaa]: %02d/%02d/%04d\n\n\n\n",prestamos_desde_archivo[i].fecha_devolucion.dia, \
                prestamos_desde_archivo[i].fecha_devolucion.mes,prestamos_desde_archivo[i].fecha_devolucion.anio); fflush(stdin);
    }
    printf("\n\nCerrando archivo y regresando a menu principal");
    sleep(15);
    system("clear");
    //Determinar cuantos registros existen en el archivo
    //Crear un arreglo de tantos elementos como registros hay eel archivo
    //Desplegar el menu
    
}

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
 * Variables globales 
 */
#define MAX_ELEMENTOS_ARRAY 10
#define ARCHIVO_USUARIOS  "usuarios.est"
#define ARCHIVO_LIBROS "libros.est2"
#define ARCHIVO_PRESTAMOS "prestamos.est"

usuario array_de_usuarios[MAX_ELEMENTOS_ARRAY];
libro array_de_libros[MAX_ELEMENTOS_ARRAY];
prestamo array_de_prestamos[MAX_ELEMENTOS_ARRAY];


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

//    prestamo prestamos_desde_archivo[MAX_ELEMENTOS_ARRAY]; //Este array contendra los datos del archivo binario
//    FILE *pArchivo;
//    
//    /* Abrir archivo binario para escribir los datos*/
//    pArchivo = fopen(ARCHIVO_PRESTAMOS,"wb");
//    if(pArchivo==NULL)
//    {
//        printf("\nError al abrir el archivo prestamos.est");
//        exit(1);
//    }
//    //El arcivo se abrio correctamente
//    
//    /* Obtener los datos de los prestamos */
//    for(i=0; i < MAX_ELEMENTOS_ARRAY; i = i+1)
//    {
//        printf("Matricula del usuario: "); fflush(stdin);
//        scanf("%d", &array_de_prestamos[i].matricula);
//        printf("Identificador de ejemplar del libro: "); fflush(stdin);
//        scanf("%d", &array_de_prestamos[i].id_ejemplar);
//        printf("Fecha de prestamo\n"); fflush(stdin);
//        printf("Dia [1-31]: "); fflush(stdin);
//        scanf("%d", &array_de_prestamos[i].fecha_prestamo.dia);
//        printf("Mes [1-12]: "); fflush(stdin);
//        scanf("%d", &array_de_prestamos[i].fecha_prestamo.mes);
//        printf("Año [Ejemp. 2020]: "); fflush(stdin);
//        scanf("%d", &array_de_prestamos[i].fecha_prestamo.anio);
//        printf("Fecha de devolucion\n"); fflush(stdin);
//        printf("Dia [1-31]: "); fflush(stdin);
//        scanf("%d", &array_de_prestamos[i].fecha_prestamo.dia);
//        printf("Mes [1-12]: "); fflush(stdin);
//        scanf("%d", &array_de_prestamos[i].fecha_prestamo.mes);
//        printf("Año [Ejemp. 2020]: "); fflush(stdin);
//        scanf("%d", &array_de_prestamos[i].fecha_prestamo.anio);
//    }
//    /* Escribir los datos de los prestamos al archivo */
//    fwrite(array_de_prestamos,sizeof(prestamo),10,pArchivo);
//    fclose(pArchivo); //Cerrar el archivo
//    
//    /* Abrir el archivo binario en modo lectura */
//    pArchivo = fopen(ARCHIVO_PRESTAMOS,"rb");
//    if(pArchivo==NULL)
//    {
//        printf("\nError al abrir el archivo prestamos.est");
//        exit(1);
//    }
//    /* Leer el contenido del archivo */
//    fread(prestamos_desde_archivo, sizeof(prestamo),10,pArchivo);
    /* Mostrar los datos leidos desde el archivo */
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
    printf("\n\nCerrando archivo y regresando a menu principal");
    sleep(15);
    system("clear");
    //Determinar cuantos registros existen en el archivo
    //Crear un arreglo de tantos elementos como registros hay eel archivo
    //Desplegar el menu
    
}

void carga_datos_de_archivos()
{
    FILE *pArchivoUsuarios=NULL, *pArchivoLibros=NULL, *pArchivoPrestamos=NULL;
    int i = 0;
    pArchivoPrestamos = fopen(ARCHIVO_PRESTAMOS,"rb");
    if(pArchivoPrestamos == NULL)
    {
        //El archivo no se pudo abrir (no existe)
        //Crear el archivo para escritura e inicializar el array correspondiente
            pArchivoPrestamos = fopen(ARCHIVO_PRESTAMOS,"wb");
            if(pArchivoPrestamos == NULL)
            {
                printf("\nError al abrir el archivo prestamos.est");
                exit(1);           
            }
            for(i=0; i < MAX_ELEMENTOS_ARRAY; i = i+1)
            {
                array_de_prestamos[i].matricula = 0;
                array_de_prestamos[i].id_ejemplar = 0;
            }        
    }
    /* Leer el contenido del archivo */
    fread(array_de_prestamos, sizeof(prestamo),10,pArchivoPrestamos);
    fclose(pArchivoPrestamos);
}
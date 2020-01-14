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
/*
 * Variables globales 
 */
#define MAX_ELEMENTOS_ARRAY 10
#define ARCHIVO_USUARIOS  "usuarios.est"
#define ARCHIVO_LIBROS "libros.est"
#define ARCHIVO_PRESTAMOS "prestamos.est"
#define NO_VALIDO "Dato Invalido"

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
                        guarda_datos_en_archivos();
                        printf("\n\n\nGracias por usar el programa de administracion de biblioteca\n");
                        fflush(stdin);
                        exit(EXIT_SUCCESS);
                        break;
        }
    }while(1);
    
    return (EXIT_SUCCESS);
}

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

void carga_datos_de_archivos()
{
    FILE *pArchivoUsuarios=NULL, *pArchivoLibros=NULL, *pArchivoPrestamos=NULL;
    int i = 0;

    /***** Bloque de archivo de usuarios *****/
    pArchivoUsuarios = fopen(ARCHIVO_USUARIOS,"rb");
    if(pArchivoUsuarios == NULL)
    {
        //El archivo no se pudo abrir (no existe)
        //Crear el archivo para escritura e inicializar el array correspondiente
            pArchivoUsuarios = fopen(ARCHIVO_USUARIOS,"wb");
            if(pArchivoUsuarios == NULL)
            {
                printf("\nError al abrir el archivo %s", ARCHIVO_USUARIOS );
                exit(1);           
            }
            for(i=0; i < MAX_ELEMENTOS_ARRAY; i = i+1)
            {
                array_de_usuarios[i].matricula = 0;
                array_de_usuarios[i].carrera = 19;
                strcpy(array_de_usuarios[i].nombre, NO_VALIDO);
            }        
    }
    // Leer el contenido del archivo
    fread(array_de_usuarios, sizeof(usuario),MAX_ELEMENTOS_ARRAY,pArchivoUsuarios);
    fclose(pArchivoUsuarios);

    /***** Bloque de archivo de libros *****/
    pArchivoLibros = fopen(ARCHIVO_LIBROS,"rb");
    if(pArchivoLibros == NULL)
    {
        //El archivo no se pudo abrir (no existe)
        //Crear el archivo para escritura e inicializar el array correspondiente
            pArchivoLibros = fopen(ARCHIVO_LIBROS,"wb");
            if(pArchivoLibros == NULL)
            {
                printf("\nError al abrir el archivo %s", ARCHIVO_LIBROS );
                exit(1);           
            }
            for(i=0; i < MAX_ELEMENTOS_ARRAY; i = i+1)
            {
                array_de_libros[i].id_ejemplar = 0;
                strcpy(array_de_libros[i].titulo, NO_VALIDO);
                strcpy(array_de_libros[i].autor, NO_VALIDO);
                strcpy(array_de_libros[i].editorial, NO_VALIDO);
                strcpy(array_de_libros[i].isbn, NO_VALIDO);
                array_de_libros[i].anio_edicion = 1900;
            }        
    }
    // Leer el contenido del archivo
    fread(array_de_libros, sizeof(libro),MAX_ELEMENTOS_ARRAY,pArchivoLibros);
    fclose(pArchivoLibros);
    
    /***** Bloque de archivo de prestamos *****/
    pArchivoPrestamos = fopen(ARCHIVO_PRESTAMOS,"rb");
    if(pArchivoPrestamos == NULL)
    {
        //El archivo no se pudo abrir (no existe)
        //Crear el archivo para escritura e inicializar el array correspondiente
            pArchivoPrestamos = fopen(ARCHIVO_PRESTAMOS,"wb");
            if(pArchivoPrestamos == NULL)
            {
                printf("\nError al abrir el archivo %s", ARCHIVO_PRESTAMOS );
                exit(1);           
            }
            for(i=0; i < MAX_ELEMENTOS_ARRAY; i = i+1)
            {
                array_de_prestamos[i].matricula = 0;
                array_de_prestamos[i].id_ejemplar = 0;
            }        
    }
    // Leer el contenido del archivo
    fread(array_de_prestamos, sizeof(prestamo),MAX_ELEMENTOS_ARRAY,pArchivoPrestamos);
    fclose(pArchivoPrestamos);
}

void guarda_datos_en_archivos()
{
    FILE *pArchivoUsuarios=NULL, *pArchivoLibros=NULL, *pArchivoPrestamos=NULL;

    /***** Bloque de archivo de usuarios *****/
    pArchivoUsuarios = fopen(ARCHIVO_USUARIOS,"wb");
    if(pArchivoUsuarios == NULL)
    {
        printf("\nError al abrir el archivo %s", ARCHIVO_USUARIOS );
        exit(1);           
    }
    fwrite(array_de_usuarios, sizeof(usuario), MAX_ELEMENTOS_ARRAY, pArchivoUsuarios);
    fclose(pArchivoUsuarios);
    
    /***** Bloque de archivo de libros *****/
    pArchivoLibros = fopen(ARCHIVO_LIBROS,"wb");
    if(pArchivoLibros == NULL)
    {
        printf("\nError al abrir el archivo %s", ARCHIVO_LIBROS );
        exit(1);           
    }
    fwrite(array_de_libros, sizeof(libro), MAX_ELEMENTOS_ARRAY, pArchivoLibros);
    fclose(pArchivoLibros);

    /***** Bloque de archivo de prestamos *****/
    pArchivoPrestamos = fopen(ARCHIVO_PRESTAMOS,"wb");
    if(pArchivoPrestamos == NULL)
    {
        printf("\nError al abrir el archivo %s", ARCHIVO_PRESTAMOS );
        exit(1);           
    }
    fwrite(array_de_prestamos, sizeof(prestamo), MAX_ELEMENTOS_ARRAY, pArchivoPrestamos);
    fclose(pArchivoPrestamos);
    
}
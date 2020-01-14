#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datatypes.h"

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
                array_de_prestamos[i].estado_actual = invalido;
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

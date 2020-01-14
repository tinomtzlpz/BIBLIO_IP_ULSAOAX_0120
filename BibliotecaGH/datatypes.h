/* 
 * File:   datatypes.h
 * Author: tino
 *
 * Created on 9 de enero de 2020, 01:04 PM
 */

#ifndef DATATYPES_H
#define	DATATYPES_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    

    typedef enum
    {
        Contaduria, Negocios, Arquitectura, Enfermeria, Fisioterapia, Psicologia,
                Nutricion, Deporte, Artes, Comunicacion, Derecho, Educacion,
                Gastronomia, Turismo, Lenguas, Electronica, Sistemas, Industrial,
                Civil, Ambiental
    } carreras;

    typedef struct
    {
        unsigned short int dia;
        unsigned short int mes;
        unsigned short int anio;	
    } fecha;

    typedef struct
    {
        unsigned int matricula;
        char nombre[50];
        carreras carrera;
    }   usuario;
    
    //Estructura Libro//
    typedef struct
    {
        unsigned int id_ejemplar;
        char isbn[15];
        char titulo[100];
        char autor[150];
        char editorial[100];
        unsigned int anio_edicion;
    } libro;

    //ESTRUCTURA PRESTAMO
    typedef struct
    {
	unsigned int matricula;
	unsigned int id_ejemplar;
        fecha fecha_prestamo;
	fecha fecha_devolucion;
    } prestamo;
	
    void admon_prestamos();
    void admon_libros();
    void admon_usuarios();
    void carga_datos_de_archivos();
    void guarda_datos_en_archivos();

#ifdef	__cplusplus
}
#endif

#endif	/* DATATYPES_H */
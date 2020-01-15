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
    
    
    #define MAX_ELEMENTOS_ARRAY 10
    #define ARCHIVO_USUARIOS  "usuarios.est"
    #define ARCHIVO_LIBROS "libros.est"
    #define ARCHIVO_PRESTAMOS "prestamos.est"
    #define NO_VALIDO "Dato Invalido"

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
	char dias_semana[10];
    } 
    fecha;
	
    typedef enum
    {
        invalido,vigente,vencido,devuelto
    }
    estado_prestamo;

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
	estado_prestamo estado_actual;
    } prestamo;
	
    void admon_prestamos();
    void admon_libros();
    void admon_usuarios();
    void carga_datos_de_archivos();
    void guarda_datos_en_archivos();
    
    /*
     * Variables globales 
     */

    usuario array_de_usuarios[MAX_ELEMENTOS_ARRAY];
    libro array_de_libros[MAX_ELEMENTOS_ARRAY];
    prestamo array_de_prestamos[MAX_ELEMENTOS_ARRAY];

//    const char *name_dayweek[10] =
//    {
//        "Domingo",
//        "Lunes",
//        "Martes",
//        "Miercoles",
//        "Jueves",
//        "Viernes",
//        "Sabado"
//    };
//    
//    const char *lista_carreras[20] =
//    {
//        "Contaduria",
//        "Negocios",
//        "Arquitectura",
//        "Enfermeria",
//        "Fisioterapia",
//        "Psicologia",
//        "Nutricion",
//        "Deporte",
//        "Artes",
//        "Comunicacion",
//        "Derecho",
//        "Educacion",
//        "Gastronomia",
//        "Turismo",
//        "Lenguas",
//        "Electronica",
//        "Sistemas",
//        "Industrial",
//        "Civil",
//        "Ambiental"
//    };
    
#ifdef	__cplusplus
}
#endif

#endif	/* DATATYPES_H */

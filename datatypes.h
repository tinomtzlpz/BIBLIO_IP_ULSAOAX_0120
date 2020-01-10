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
    
    typedef struct
    {
        unsigned short int dia;
        unsigned short int mes;
        unsigned short int anio;
    } fecha;

    typedef enum
    {
        Contaduria, Negocios, Arquitectura, Enfermeria, Fisioterapia, Psicologia,
                Nutricion, Deporte, Artes, Comunicacion, Derecho, Educacion,
                Gastronomia, Turismo, Lenguas, Electronica, Sistemas, Industrial,
                Civil, Ambiental
    } carreras;

    typedef struct
    {
        unsigned int matricula;
        char nombre[50];
        carreras carrera;
    } usuario;

#ifdef	__cplusplus
}
#endif

#endif	/* DATATYPES_H */


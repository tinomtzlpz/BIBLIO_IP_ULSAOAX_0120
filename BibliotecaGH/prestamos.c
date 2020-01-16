#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include "datatypes.h"
extern const char *name_dayweek[];

void ingresar_datos_prestamo();
void ingresa_compara_matriculas(short int *contador,short int i);
void duplicar_datos(short int num_duplicar,short int i);
void dar_fecha_prestamo(short int i);
void dar_fecha_devolucion(short int i);
void dias_restantes(int j);
void verificar_ingreso(short int i);
void ver_prestamos();
void actualizar_estado_prestamos();
void terminar_prestamo();
void imprimir_name(unsigned int matricula);
void imprimir_title(unsigned int ejemplar);

void admon_prestamos()
{
    actualizar_estado_prestamos();
    char elegir='a',a;
    short int salida=0;
    int flush=0;
    do
    {
        carga_datos_de_archivos();
        printf("\t**MENU DE PRESTAMOS**\n");fflush(stdin);
        printf("\n(A)hacer un prestamo\n(B)checar tu registro de prestamo\n(C)terminar un prestamo\n(culquier tecla)salir\n");fflush(stdin);
        if((flush%2)!=0)
        {
            while((a = getc(stdin)) != '\n' && a != EOF);
        }
        scanf("%c",&elegir);
        while((a = getc(stdin)) != '\n' && a != EOF); //Esta linea hace flush a la entrada standard, no quitar
        flush++;
        elegir=toupper(elegir);
        switch(elegir){
            case'A':
                system("clear");
                ingresar_datos_prestamo();
                system("clear");
                break;
            case'B': 
                system("clear");
                ver_prestamos();
                system("clear");
                break;
            case'C':
                system("clear");
                terminar_prestamo();
                system("clear");
                break;
            default:
                system("clear");
                salida=1;
                break;
        }
        guarda_datos_en_archivos();
    }while(salida==0);


}

void ingresar_datos_prestamo()
{
    //SE INGRESAN LOS DATOS
    short int i=0;
    char guardar='Y',aux;
    short int contador=-1;
    short int num_duplicar=0; 
    do
    {
        
        for(i=0; i < MAX_ELEMENTOS_ARRAY; i++)
        {
            if(array_de_prestamos[i].matricula==0)
            {
                contador=0;
                ingresa_compara_matriculas(&contador,i);
                if(contador >= 3)
                {
                    printf("YA NO PUEDES TENER MAS PRESTAMOS,SORRY\n");
                    guardar='Y';
                    break;
                }
                printf("cuantos prestamos quieres hacer HOY? EL MAXIMO SON 3\nAcualtmente puedes hacer %d prestamos\n",(3-contador));fflush(stdin);
                scanf("%hd",&num_duplicar);
                if(num_duplicar<=0 || num_duplicar>(3-contador))
                    num_duplicar=1;
            
                duplicar_datos(num_duplicar,i);
                
                verificar_ingreso(i);
                
                break;
            }
        }
        if(contador < 3)
        {
            printf("si hay algun ERROR ingresa (N)... si no continuar para GUARDAR(Y)\n"); fflush(stdin);
            while((aux = getc(stdin)) != '\n' && aux != EOF); //Esta linea hace flush a la entrada standard, no quitar
            scanf("%c", &guardar);
            guardar=toupper(guardar);
            if(guardar!='Y')//SI ESCRIBIO ALGO QUE NO QUERIA PONER,CON ESTO LO RECETEA SIN DAÑAR NADA
            {
                int aux;
                aux=array_de_prestamos[i].matricula;
                for(int j=0;j<MAX_ELEMENTOS_ARRAY;j++)
                {
                    if(array_de_prestamos[j].matricula==aux && array_de_prestamos[j].estado_actual==invalido)
                        array_de_prestamos[j].matricula=0;
                } 
            }
        }
    }while(guardar!='Y');
    if (guardar=='Y')
    {
        for(int j=0;j<MAX_ELEMENTOS_ARRAY;j++)
        {
            if(array_de_prestamos[j].matricula==array_de_prestamos[i].matricula)
                array_de_prestamos[j].estado_actual=vigente;//YA NO PERMITE SOBREESCRIBIR LA MISMA ESTRUCTURA
        }    
    }
        
}

void ingresa_compara_matriculas(short int *contador,short int i)
{
    short int name_user=0;
    unsigned int matricula_ingresada;
    short int cambiar=1;
    do
    {
    printf("ESCRIBE Matricula del usuario: "); fflush(stdin);
    scanf("%u", &matricula_ingresada);
    for (int j=0;j<MAX_ELEMENTOS_ARRAY;j++)
    {
        if(matricula_ingresada==array_de_prestamos[j].matricula)
            (*contador)++;
        if(array_de_prestamos[j].estado_actual==vencido)
            printf("---------------------------\nTIENES VENCIDO EL LIBRO CON IDENTIFICACION: %u\n---------------------------\n",array_de_prestamos[j].id_ejemplar);
        if(matricula_ingresada==array_de_usuarios[j].matricula)
            cambiar=0;    
    }
    if(cambiar==1)
        printf("LA MATRICULA NO EXISTE\n");
    }while(cambiar==1);
    if((*contador)>=0 && (*contador)<3)
    {
        array_de_prestamos[i].matricula=matricula_ingresada;
    }
}

void duplicar_datos(short int num_duplicar,short int i)
{
    short int cambiar=0;
    for (int k=0;k<num_duplicar;k++)
    {
        for(int j=0;j<MAX_ELEMENTOS_ARRAY;j++)
        {
            if(array_de_prestamos[j].matricula==0)
            {
                array_de_prestamos[j].matricula=array_de_prestamos[i].matricula;
                do{
                    printf("PRESTAMO NUMERO %d:\nEscribe el identificador del libro:",k+1);
                    scanf("%u",&array_de_prestamos[j].id_ejemplar);
                    if(array_de_prestamos[j].id_ejemplar==array_de_libros[j].id_ejemplar)
                    {   
                        cambiar=0;
                    }
                    else
                    {
                        printf("NO EXISTE ESE IDENTIFICADOR DE LIBRO\n");
                        cambiar=1;
                    }
                }while(cambiar==1);
                    
                dar_fecha_prestamo(j);
                dar_fecha_devolucion(j);
                break;
            }
        }
    }
}

void dar_fecha_prestamo(short int i)
{  
//EL PROGRMA DA LA FECHA DEL PRESTAMO
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    char aux[10];
    array_de_prestamos[i].fecha_prestamo.dia=tlocal->tm_mday;
    array_de_prestamos[i].fecha_prestamo.mes=tlocal->tm_mon+1;
    array_de_prestamos[i].fecha_prestamo.anio=tlocal->tm_year+1900;
    switch(tlocal->tm_wday)
    {
        case 0:
            strcpy(aux,name_dayweek[0]);
            break;
        case 1:  
            strcpy(aux,name_dayweek[1]);
            break;
        case 2:
            strcpy(aux,name_dayweek[2]);
            break;
        case 3:
            strcpy(aux,name_dayweek[3]);
            break;
        case 4:
            strcpy(aux,name_dayweek[4]);
            break;
        case 5:
            strcpy(aux,name_dayweek[5]);
            break;
        case 6:
            strcpy(aux,name_dayweek[6]);
            break;
    }
    strcpy(array_de_prestamos[i].fecha_prestamo.dias_semana,aux);
}

void dar_fecha_devolucion(short int i)
{
//LA FECHA DE PRESTAMO SE LE SUMA DIAS PARA LA FECHA DE DEVOLUCION
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    short int dias_sumados=3;//cuantos dias
    short int num_mes=0;
    char aux[10];
    int new_dayweek;
    new_dayweek=tlocal->tm_wday+dias_sumados;
    if(new_dayweek==6)
    {
         dias_sumados+=2;
         new_dayweek=1;
    }
    if (new_dayweek==0)
    {
        dias_sumados+=1;
        new_dayweek=1;
    }
    switch(new_dayweek)
    {
        case 0:
            strcpy(aux,name_dayweek[0]);
            break;
        case 1:  
            strcpy(aux,name_dayweek[1]);
            break;
        case 2:
            strcpy(aux,name_dayweek[2]);
            break;
        case 3:
            strcpy(aux,name_dayweek[3]);
            break;
        case 4:
            strcpy(aux,name_dayweek[4]);
            break;
        case 5:
            strcpy(aux,name_dayweek[5]);
            break;
        case 6:
            strcpy(aux,name_dayweek[6]);
            break;
    }
    strcpy(array_de_prestamos[i].fecha_devolucion.dias_semana,aux);
    array_de_prestamos[i].fecha_devolucion.dia=(tlocal->tm_mday+dias_sumados);
    array_de_prestamos[i].fecha_devolucion.anio=(tlocal->tm_year)+1900;
    array_de_prestamos[i].fecha_devolucion.mes=(tlocal->tm_mon)+1;
    switch ((tlocal->tm_mon))
    {
        case 0: case 2: case 4: case 6: case 7: case 9: case 11:
            if((tlocal->tm_mday+dias_sumados)>31)
            {
                if (tlocal->tm_mon==11)
                {
                array_de_prestamos[i].fecha_devolucion.anio=tlocal->tm_year+1901;
                array_de_prestamos[i].fecha_devolucion.mes=1;
                }
                num_mes=31;
            }
            break;
        case 3: case 5: case 8: case 10:
            if((tlocal->tm_mday+dias_sumados)>30)
                num_mes=30;
            break;
        case 1:
            if((tlocal->tm_year%4)==0)
            {
                if((tlocal->tm_mday+dias_sumados)>29)
                num_mes=29;
                
            }
            else
            {
                if((tlocal->tm_mday+dias_sumados)>28)
                num_mes=28;
            }
            break;
    }
    if(num_mes!=0)
    {
        array_de_prestamos[i].fecha_devolucion.mes=tlocal->tm_mon+1;
        array_de_prestamos[i].fecha_devolucion.dia=(tlocal->tm_mday+dias_sumados)-num_mes;
    }
}

void verificar_ingreso(short int i)
{
//SE VERIFICA LO QUE SE ESCRIBIO
                printf("VERIFCA QUE TODO ESTE CORRECO:\n");
                printf("\t*matricula: %u *\n",array_de_prestamos[i].matricula);fflush(stdin);
                imprimir_name(array_de_prestamos[i].matricula);  
                short int aux=1;
                for(int j=0;j<MAX_ELEMENTOS_ARRAY;j++)
                {
                    
                    if(array_de_prestamos[j].matricula==array_de_prestamos[i].matricula && array_de_prestamos[j].estado_actual==invalido)
                    {
                        imprimir_title(array_de_prestamos[j].id_ejemplar);
                        printf("identificador de libro numero %hd: %u\n",aux,array_de_prestamos[j].id_ejemplar); 
                        aux++;
                    }
                }    
                printf("\t*fecha de PRESTAMO: %02hu/%02hu/%hu Dia: %s *\n",array_de_prestamos[i].fecha_prestamo.dia,array_de_prestamos[i].fecha_prestamo.mes,array_de_prestamos[i].fecha_prestamo.anio,array_de_prestamos[i].fecha_prestamo.dias_semana);fflush(stdin);
                printf("\t*fecha de DEVOLUCION: %02hu/%02hu/%hu Dia: %s *\n",array_de_prestamos[i].fecha_devolucion.dia,array_de_prestamos[i].fecha_devolucion.mes,array_de_prestamos[i].fecha_devolucion.anio,array_de_prestamos[i].fecha_devolucion.dias_semana);fflush(stdin);
}

void ver_prestamos()
{
    /* Mostrar los datos leidos desde el archivo */
    short int i,j;
    short int ubicacion[3]={0,0,0};
    short int aux=0;
    short int contador=0;
    printf("Informacion de prestamos obtenida desde el archivo:\n\n"); fflush(stdin);
    for(i=0;i<MAX_ELEMENTOS_ARRAY;i++)
    {
        contador=0;
        aux=0;
        if(i!=ubicacion[0] || i!=ubicacion[1] || i!=ubicacion[2] )
        {
            continue;
        }
        for(j=0;j<MAX_ELEMENTOS_ARRAY;j++)
        {
            if(array_de_prestamos[i].matricula!=0)
            {
                if(array_de_prestamos[j].matricula==array_de_prestamos[i].matricula)
                {
                    ubicacion[aux]=j;
                    aux++;
                    contador++;
                }
            }
        }
        printf("\n\t ** MATRICULA: %u **\n",array_de_prestamos[ubicacion[0]].matricula); fflush(stdin);
        imprimir_name(array_de_prestamos[ubicacion[0]].matricula);
        for (j=0;j<contador;j++)
        {
            if(array_de_prestamos[ubicacion[j]].estado_actual==vencido)
                printf("\t-----------------------\n\tTU PRESTAMO ESTA VENCIDO\n\t-----------------------\n");
            imprimir_title(array_de_prestamos[ubicacion[j]].id_ejemplar);
            printf("Identificador de ejemplar del libro: %u\n",array_de_prestamos[ubicacion[j]].id_ejemplar); fflush(stdin);
            printf("fecha de PRESTAMO: %02hu/%02hu/%hu Dia: %s\n",array_de_prestamos[ubicacion[j]].fecha_prestamo.dia,array_de_prestamos[ubicacion[j]].fecha_prestamo.mes,array_de_prestamos[ubicacion[j]].fecha_prestamo.anio,array_de_prestamos[ubicacion[j]].fecha_prestamo.dias_semana);fflush(stdin);
            printf("fecha de DEVOLUCION: %02hu/%02hu/%hu Dia: %s\n\n",array_de_prestamos[ubicacion[j]].fecha_devolucion.dia,array_de_prestamos[ubicacion[j]].fecha_devolucion.mes,array_de_prestamos[ubicacion[j]].fecha_devolucion.anio,array_de_prestamos[ubicacion[j]].fecha_devolucion.dias_semana);fflush(stdin);   
            dias_restantes(j);
        }                
    } 
    printf("\n\npresiona ENTER para volver al menu PRESTAMO\n");fflush(stdin);
    getchar();
    
}


void actualizar_estado_prestamos()
{
    //PRIMERO SE CHECA EL ESTADO DE LOS PRESTAMOS
     time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    for(int j=0;j<MAX_ELEMENTOS_ARRAY;j++)
    {
        if(array_de_prestamos[j].estado_actual!=invalido);
        {
            if(array_de_prestamos[j].fecha_devolucion.dia < tlocal->tm_mday)
                array_de_prestamos[j].estado_actual==vencido;
        }
    }
}

void terminar_prestamo()
{
    unsigned int matricula;
    short int ubicacion[3]={-1,-1,-1};
    short int aux=0;
    short int contador=0;
    short int cambiar=1;
    do
    {
    printf("ESCRIBE Matricula del usuario: ");
        scanf("%u",&matricula);
    for(int j=0;j<MAX_ELEMENTOS_ARRAY;j++)
    {
        if(matricula==array_de_usuarios[j].matricula)
        {
            printf("\t*usuario: %s *\n\n",array_de_usuarios[j].nombre);
            cambiar=0;
        }
        if(matricula==array_de_prestamos[j].matricula)
        {
            ubicacion[aux]=j;
            aux++;
            contador++;
        }
    }
    if(cambiar==1)
        printf("LA MATRICULA NO EXISTE\n");
    }while(cambiar==1);
    if(contador==0)
    {    
        printf("\tNO HAS HECHO NINGUN PRESTAMO\n");
    }
    else
    {
        for (int j=0;j<contador;j++)
        {
            if(array_de_prestamos[ubicacion[j]].estado_actual==vencido)
                printf("\t-----------------------\n\tTU PRESTAMO ESTA VENCIDO\n\t-----------------------\n");
            imprimir_title(array_de_prestamos[ubicacion[j]].id_ejemplar);
            printf("Identificador del libro: %u\n",array_de_prestamos[ubicacion[j]].id_ejemplar); fflush(stdin);
//            printf("fecha de PRESTAMO: %02hu/%02hu/%hu Dia: %s\n",array_de_prestamos[ubicacion[j]].fecha_prestamo.dia,array_de_prestamos[ubicacion[j]].fecha_prestamo.mes,array_de_prestamos[ubicacion[j]].fecha_prestamo.anio,array_de_prestamos[ubicacion[j]].fecha_prestamo.dias_semana);fflush(stdin);
//            printf("fecha de DEVOLUCION: %02hu/%02hu/%hu Dia: %s\n\n",array_de_prestamos[ubicacion[j]].fecha_devolucion.dia,array_de_prestamos[ubicacion[j]].fecha_devolucion.mes,array_de_prestamos[ubicacion[j]].fecha_devolucion.anio,array_de_prestamos[ubicacion[j]].fecha_devolucion.dias_semana);fflush(stdin);   
        }
        printf("\n¿CUAL QUIERES DEVOLVER?\n");    
        switch(contador)
        {
            case 1:
                printf("PRIMERO(1)\n");
                break;
            case 2:
                printf("PRIMERO(1)\n");
                printf("SEGUNDO(2)\n");
                break;
            case 3:
                printf("PRIMERO(1)\n");
                printf("SEGUNDO(2)\n");
                printf("TERCERO(3)\n");
                break;
            default:
                printf("ERROR EEERROR");
                break;
        }
        short int elegir;
        scanf("%hd",&elegir);
        switch(elegir)
        {
            case 1:
                array_de_prestamos[ubicacion[0]].matricula=0;
                array_de_prestamos[ubicacion[0]].estado_actual=invalido;
                break;
            case 2:
                array_de_prestamos[ubicacion[1]].matricula=0;
                array_de_prestamos[ubicacion[1]].estado_actual=invalido;
                break;
            case 3:
                array_de_prestamos[ubicacion[2]].matricula=0;
                array_de_prestamos[ubicacion[2]].estado_actual=invalido;
                break;
            default:
                printf("ERROR ERROR ERROR");
                break;
        }
        printf("\n\t!Devolucion Completada¡\n   ...regresando a menu PRESTAMO\n");fflush(stdin);
        sleep(10);
    }
    
}

void imprimir_name(unsigned int matricula)
{
    for(int j=0;j<MAX_ELEMENTOS_ARRAY;j++)
    {
        if(matricula==array_de_usuarios[j].matricula)
        {
            printf("\t*usuario: %s *\n\n",array_de_usuarios[j].nombre);
            break;
        }
    }    
        
}

void imprimir_title(unsigned int ejemplar)
{
    for(int j=0;j<MAX_ELEMENTOS_ARRAY;j++)
    {
        if(ejemplar==array_de_libros[j].id_ejemplar)
        {
            printf("titulo: %s\n",array_de_libros[j].titulo);
            break;
        }
    }    
}

void dias_restantes(int j)
{
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    short int today;
    int num_mes;
    if(array_de_prestamos[j].fecha_devolucion.dia<tlocal->tm_mday)
    {
        switch ((tlocal->tm_mon))
        {
            case 0: case 2: case 4: case 6: case 7: case 9: case 11:
                    num_mes=31;           
                break;
            case 3: case 5: case 8: case 10:
                    num_mes=30;
                break;
            case 1:
                if((tlocal->tm_year%4)==0)
                {
                    num_mes=29; 
                }
                else
                {
                    num_mes=28;
                }
                break;
        }
        today=(array_de_prestamos[j].fecha_devolucion.dia+num_mes)-tlocal->tm_mday;
    }
    else
    {
        today=array_de_prestamos[j].fecha_devolucion.dia-tlocal->tm_mday;
    }
    if(array_de_prestamos[j].fecha_devolucion.dia==tlocal->tm_mday)
    printf("HOY CADUCA TU PRESTAMO");
    
    printf("dias restsntes: %d",today);
}




#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include "datatypes.h"
extern const char *name_dayweek[];

void comparar_matriculas(unsigned int *matricula);
void ingresar_datos_prestamo(unsigned int matricula);
void duplicar_datos(short int num_duplicar,short int ubicacion[]);
void dar_fecha_prestamo(short int i);
void dar_fecha_devolucion(short int i);
void verificar_ingreso(short int num_duplicar,short int ubicacion[]);
void ver_prestamo_user(unsigned int matricula);
void terminar_prestamo(unsigned int matricula);
void actualizar_estado_prestamos();
void imprimir_title(unsigned int ejemplar);
void dias_restantes(short int j);
void ver_all();

void admon_prestamos()
{
                        
//                        unsigned int x=5,y=0;
//                        for(int i=0;i<MAX_ELEMENTOS_ARRAY;i++)
//                        {
//                            array_de_usuarios[i].matricula=x++;
//                            array_de_libros[i].id_ejemplar=x++;
//                            array_de_usuarios[i].carrera=y++;
//                            printf("%u\n",array_de_usuarios[i].matricula);
//                            printf("%u\n",array_de_usuarios[i].carrera);
//                            printf("%u\n\n",array_de_libros[i].id_ejemplar);
//                        }
    unsigned int matricula;
    comparar_matriculas();                    
    actualizar_estado_prestamos(&matricula);
    char elegir='a',a;
    short int salida=0;
    int flush=0;
    do
    {
        carga_datos_de_archivos();
        printf("\t**MENU DE PRESTAMOS**\n");fflush(stdin);
        printf("\n[A]hacer un prestamo\n[B]checar tu registro de prestamo\n[C]terminar un prestamo\n(culquier tecla)salir\n");fflush(stdin);
        scanf("%c",&elegir);
        while((a = getc(stdin)) != '\n' && a != EOF); //Esta linea hace flush a la entrada standard, no quitar
        flush++;
        elegir=toupper(elegir);
        switch(elegir){
            case'A':
                system("clear");
                ingresar_datos_prestamo(matricula);
                system("clear");
                break;
            case'B': 
                system("clear");
                ver_prestamo_user(matricula);
                system("clear");
                break;
            case'C':
                system("clear");
                terminar_prestamo(matricula);
                system("clear");
                break;
            case'X':
                system("clear");
                ver_all();      
                system("clear");
                break;
            default:
                salida=1;
                break;
        }
        guarda_datos_en_archivos();
    }while(salida==0);


}

void comparar_matriculas(unsigned int *matricula)
{
    char a;
    short int cambiar=1;
    do
    {
        printf("Matricula del usuario: "); fflush(stdin);
        scanf("%u", &(*matricula));while((a = getc(stdin)) != '\n' && a != EOF);
        for (short int j=0;j<MAX_ELEMENTOS_ARRAY;j++)
        {
            if((*matricula)==array_de_usuarios[j].matricula)
            {
                printf("BIENVENIDO %s\n<3\n",array_de_usuarios[j].nombre);fflush(stdin);
                cambiar=0;
                break;
            }
            
        }
        if(cambiar==1)
            printf("LA MATRICULA NO EXISTE\n");fflush(stdin);
    }while(cambiar==1);
}

void ingresar_datos_prestamo(unsigned int matricula)
{
    //SE INGRESAN LOS DATOS
    short int contador=0;
    for(short int j=0; j < MAX_ELEMENTOS_ARRAY; j++)
    {
        if(matricula==array_de_prestamos[j].matricula && array_de_prestamos[j].estado_actual==vigente)
            contador++;
        if(contador==3)
            break;
    }
    if(contador>=3)
    {
        printf("YA NO PUEDES HACER MAS PRESTAMOS\n");
    }
    else
    {
        short int ubicacion[3]={-1,-1,-1},aux=0;
        for(short int j=0; j < MAX_ELEMENTOS_ARRAY; j++)
        {
            if(array_de_prestamos[j].matricula==0)
            {
                ubicacion[aux]=j;
                aux++;
            }   
            if(aux==(3-contador))
                break;
        }
        short int nose;
        short int num_duplicar=0; 
        //char guardar='Y', a;
        short int guardar=0;
        do
        {
            char a;
            printf("cuantos prestamos quieres hacer HOY? EL MAXIMO SON 3\nAcualtmente puedes hacer %d prestamos\n",(3-contador));fflush(stdin);
            scanf("%hd",&num_duplicar);
            while((a = getc(stdin)) != '\n' && a != EOF);
            if(num_duplicar<=0 || num_duplicar>(3-contador))
            num_duplicar=1;
            nose=num_duplicar;
            duplicar_datos(num_duplicar,ubicacion);
            verificar_ingreso(num_duplicar,ubicacion);
            
            printf("si hay algun ERROR ingresa [0]... si no continuar para GUARDAR[1]\n"); fflush(stdin);
            scanf("%d", &guardar);
            while((a = getc(stdin)) != '\n' && a != EOF); //Esta linea hace flush a la entrada standard, no quitar
            //guardar=toupper(guardar);
            
        }while(guardar==0);
        for(short int j=0;j<nose;j++)
        {
            array_de_prestamos[ubicacion[j]].estado_actual=vigente;//YA NO PERMITE SOBREESCRIBIR LA MISMA ESTRUCTURA
            array_de_prestamos[ubicacion[j]].matricula=matricula;
        }    
    }   
}

void duplicar_datos(short int num_duplicar,short int ubicacion[])
{
    char a;
    short int cambiar=1;
    unsigned int id;
    for(short int j=0;j<num_duplicar;j++)
    {
        cambiar=1;
        do{
            printf("PRESTAMO NUMERO %d:\nEscribe el identificador del libro:",j+1);fflush(stdin);
            scanf("%u",&id);
            while((a = getc(stdin)) != '\n' && a != EOF);
            for(short int i=0;i<MAX_ELEMENTOS_ARRAY;i++)
            {
                if(id==array_de_libros[i].id_ejemplar)
                {
                    cambiar=0;
                    break;
                }
            }
            if(cambiar==1)
                printf("NO EXISTE ESE IDENTIFICADOR DE LIBRO\n");fflush(stdin);
        }while(cambiar==1);
        array_de_prestamos[ubicacion[j]].id_ejemplar=id;
        dar_fecha_prestamo(ubicacion[j]);
        dar_fecha_devolucion(ubicacion[j]);
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
    if(new_dayweek>6)
        new_dayweek-=7;
        
    if(new_dayweek==6)
    {
         dias_sumados+=2;
         new_dayweek=1;
    }
    if (new_dayweek==0)
    {
        dias_sumados++;
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
                num_mes=31;
                if (tlocal->tm_mon==11)
                {
                    array_de_prestamos[i].fecha_devolucion.anio=tlocal->tm_year+1901;
                    array_de_prestamos[i].fecha_devolucion.mes=0;
                    
                }
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

void verificar_ingreso(short int num_duplicar,short int ubicacion[])
{
//SE VERIFICA LO QUE SE ESCRIBIO
                printf("VERIFCA QUE TODO ESTE CORRECO:\n");  
                for(short int j=0;j<num_duplicar;j++)
                {               
                        imprimir_title(array_de_prestamos[ubicacion[j]].id_ejemplar);
                        printf("identificador de libro numero %d: %u\n",j+1,array_de_prestamos[ubicacion[j]].id_ejemplar);              
                }    
                printf("\t*fecha de PRESTAMO: %02hu/%02hu/%hu Dia: %s *\n",array_de_prestamos[ubicacion[0]].fecha_prestamo.dia,array_de_prestamos[ubicacion[0]].fecha_prestamo.mes,array_de_prestamos[ubicacion[0]].fecha_prestamo.anio,array_de_prestamos[ubicacion[0]].fecha_prestamo.dias_semana);fflush(stdin);
                printf("\t*fecha de DEVOLUCION: %02hu/%02hu/%hu Dia: %s *\n",array_de_prestamos[ubicacion[0]].fecha_devolucion.dia,array_de_prestamos[ubicacion[0]].fecha_devolucion.mes,array_de_prestamos[ubicacion[0]].fecha_devolucion.anio,array_de_prestamos[ubicacion[0]].fecha_devolucion.dias_semana);fflush(stdin);
}

void ver_prestamo_user(unsigned int matricula)
{
    /* Mostrar los datos leidos desde el archivo */
    char a;
    short int ubicacion[10],aux=0,contador=0,contador2=0;
    for(short int j=0;j<MAX_ELEMENTOS_ARRAY;j++)
    {
        if(array_de_prestamos[j].matricula==matricula)
        {
            ubicacion[aux]=j;
            aux++;
            contador++;
        }
    }
    if(contador==0)
    {
        printf("NO HAY NADA QUE MOSTRAR\n");
    }
    else
    {
        for(short int k=vigente;k<=devuelto;k++)
        {
            contador2=0;
            printf("\t*ESTADO ACTUAL: ");
            switch(k)
            {
                case 1:
                    printf("VIGENTE*\n");
                    break;
                case 2:
                    printf("VENCIDO*\n");
                    break;
                case 3:
                    printf("DEVUELTO*\n");
                    break;
            }
            for(short int j=0;j<contador;j++)
            {
                if(array_de_prestamos[ubicacion[j]].estado_actual==k)
                {
                    imprimir_title(array_de_prestamos[ubicacion[j]].id_ejemplar);
                    printf("Identificador de ejemplar del libro: %u\n",array_de_prestamos[ubicacion[j]].id_ejemplar); fflush(stdin);
                    printf("fecha de PRESTAMO: %02hu/%02hu/%hu Dia: %s\n",array_de_prestamos[ubicacion[j]].fecha_prestamo.dia,array_de_prestamos[ubicacion[j]].fecha_prestamo.mes,array_de_prestamos[ubicacion[j]].fecha_prestamo.anio,array_de_prestamos[ubicacion[j]].fecha_prestamo.dias_semana);fflush(stdin);
                    contador2++;
                    if(array_de_prestamos[ubicacion[j]].estado_actual!=devuelto)
                    {
                    printf("fecha de DEVOLUCION: %02hu/%02hu/%hu Dia: %s\n",array_de_prestamos[ubicacion[j]].fecha_devolucion.dia,array_de_prestamos[ubicacion[j]].fecha_devolucion.mes,array_de_prestamos[ubicacion[j]].fecha_devolucion.anio,array_de_prestamos[ubicacion[j]].fecha_devolucion.dias_semana);fflush(stdin);   
                    dias_restantes(ubicacion[j]);
                    }
                    else
                    {
                        printf("fecha de prestamo DEVUELTO el libro: %02hu/%02hu/%hu Dia: %s\n",array_de_prestamos[ubicacion[j]].fecha_prestamo.dia,array_de_prestamos[ubicacion[j]].fecha_prestamo.mes,array_de_prestamos[ubicacion[j]].fecha_prestamo.anio,array_de_prestamos[ubicacion[j]].fecha_prestamo.dias_semana);   
                    }
                }
            }
            if(contador2==0)
            {
                printf("NO HAY NINGUNO\n");
            }
        }
    }
    
    
    printf("\npresiona ENTER para volver al menu PRESTAMO\n");fflush(stdin);
    getchar(); 
    //while((a = getc(stdin)) != '\n' && a != EOF);
}


void actualizar_estado_prestamos()
{
    //PRIMERO SE CHECA EL ESTADO DE LOS PRESTAMOS
     time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    for(int j=0;j<MAX_ELEMENTOS_ARRAY;j++)
    {
        if(array_de_prestamos[j].estado_actual==vigente && array_de_prestamos[j].fecha_devolucion.dia < tlocal->tm_mday);
                array_de_prestamos[j].estado_actual==vencido;
        
    }
}

void terminar_prestamo(unsigned int matricula)
{
    char a;
    short int ubicacion[3],aux=0,contador=0;
    for(short int j=0;j<MAX_ELEMENTOS_ARRAY;j++)
    {
        if(array_de_prestamos[j].matricula==matricula && array_de_prestamos[j].estado_actual==vigente)
        {
            ubicacion[aux]=j;
            aux++;
            contador++;
        }
        if(aux==3)
            break;
    }
    if(contador==0)
    {    
        printf("\tNO TIENES NINGUN PRESTAMO\n");
        sleep(3);
    }
    else
    {
        short int elegir_cuantos=-1,elegir_cuales=-1,salir=1;
        do
        {
            for (short int j=0;j<contador;j++)
            {
                if(array_de_prestamos[ubicacion[j]].estado_actual==vencido)
                    printf("\t-----------------------\n\tTU PRESTAMO ESTA VENCIDO\n\t-----------------------\n");
                printf("[%d]Identificador del libro: %u\n",j+1,array_de_prestamos[ubicacion[j]].id_ejemplar); fflush(stdin);
                imprimir_title(array_de_prestamos[ubicacion[j]].id_ejemplar);
                dias_restantes(ubicacion[j]);
            }
            printf("¿CUANTOS QUIERES DEVOLVER?\n");
            if(contador==1)
                printf("SOLO PUEDES DEVOLVER UN PRESTAMO\n");
            if(contador==2)
                printf("SOLO PUEDES DEVOLVER DOS PRESTAMOS\n");
            if(contador==3)    
                printf("PUEDES DEVOLVER LOS TRES PRESTAMOS\n");
            scanf("%hd",&elegir_cuantos);while((a = getc(stdin)) != '\n' && a != EOF);      
            if(elegir_cuantos<1 || elegir_cuantos>contador)
            {
            printf("ERROR EEERROR\n");
            }
            else
            {
                if(elegir_cuantos==contador )
                {
                    printf("SE ELIMINARAN TODOS TUS PRESTAMOS ACTULES\n");

                }
                else
                {
                    printf("ESCRIBE EL NUMERO DE CUALES QUIERES DEVOLVER, SEPARDO POR ESPACIOS:\n");
                    if(contador==1)
                        printf("PRIMERO[1]\n");
                    if(contador==2)
                        printf("PRIMERO[1] SEGUNDO[2]\n");
                    if(contador==3)    
                        printf("PRIMERO[1] SEGUNDO[2] TERCERO[3]\n");

                    for(short int j=0;j<elegir_cuantos;j++)
                    {
                        scanf("%d",&elegir_cuales);
                        while((a = getc(stdin)) != '\n' && a != EOF);
                        if(elegir_cuales==1 || elegir_cuales==2 || elegir_cuales==3)
                        {
                                       
                        }
                        else
                        {
                            printf("ERROR EEERROR\n");
                            break;
                        }

                    }
                }
                printf("ESTAS SEGURO?\n[1]YES [0]NO");
                scanf("%d",&salir);
                while((a = getc(stdin)) != '\n' && a != EOF);
            }
        }while(salir==1);
        array_de_prestamos[ubicacion[elegir_cuales-1]].estado_actual=devuelto;
        dar_fecha_prestamo(ubicacion[elegir_cuales-1]);
         if(elegir_cuantos==contador )
        {
            for(short int j=0;j<contador;j++)
            {
                array_de_prestamos[ubicacion[j]].estado_actual=devuelto;
                dar_fecha_prestamo(ubicacion[j]);
            }
        }
        printf("\n\t!Devolucion Completada¡\n   ...regresando a menu PRESTAMO\n");fflush(stdin);
        sleep(3);
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

void dias_restantes(short int j)
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
    
    printf("dias restantes para devolver el prestamo: %hd\n\n",today);
}

void ver_all()
{
    char a;
    short int salir=0;
    do
    {
        printf("COMO QUIERES VERLO ENLISTADO?[1]por matriculas ordenads\n[2]por carrera\n[3]por estado actual\n[4]por nombre alfaticamente\n[culaquier tecla]SALIR\n");
        short int elegir;
        short int contador=0,contador2=0,contador3=0,aux1=0,aux2=0,ubicacion[10],tipo[10],id[10];
        scanf("%d",&elegir);
        while((a = getc(stdin)) != '\n' && a != EOF);
        switch(elegir)
        {
            case 1:
                for(short int j=0;j<MAX_ELEMENTOS_ARRAY;j++)
                {   
                    for(short int i=0;i<MAX_ELEMENTOS_ARRAY;i++)
                    {
                        if(array_de_prestamos[j].matricula==array_de_usuarios[i].matricula && array_de_prestamos[j].matricula!=0)
                        {
                            ubicacion[aux2]=j;
                            tipo[aux2]=i;
                            aux2++;
                            contador++;
                        }
                        
                    }
                }
                for(short int j=0;j<contador;j++)
                {
                    printf("MATRICULA: %u\n",array_de_prestamos[ubicacion[j]].matricula);
                    printf("USUARIO: %s\n",array_de_usuarios[tipo[j]]);
                    imprimir_title(ubicacion[j]);
                    printf("Identificador de ejemplar del libro: %u\n",array_de_prestamos[ubicacion[j]].id_ejemplar); fflush(stdin);
                    printf("fecha de PRESTAMO: %02hu/%02hu/%hu Dia: %s\n",array_de_prestamos[ubicacion[j]].fecha_prestamo.dia,array_de_prestamos[ubicacion[j]].fecha_prestamo.mes,array_de_prestamos[ubicacion[j]].fecha_prestamo.anio,array_de_prestamos[ubicacion[j]].fecha_prestamo.dias_semana);fflush(stdin);
                    contador2++;
                    if(array_de_prestamos[ubicacion[j]].estado_actual!=devuelto)
                    {
                        printf("fecha de DEVOLUCION: %02hu/%02hu/%hu Dia: %s\n\n",array_de_prestamos[ubicacion[j]].fecha_devolucion.dia,array_de_prestamos[ubicacion[j]].fecha_devolucion.mes,array_de_prestamos[ubicacion[j]].fecha_devolucion.anio,array_de_prestamos[ubicacion[j]].fecha_devolucion.dias_semana);fflush(stdin);   
                        dias_restantes(ubicacion[j]);
                    }
                    else
                    {
                        printf("fecha en la que se DEVOLVIO el libro: %02hu/%02hu/%hu Dia: %s\n\n",array_de_prestamos[ubicacion[j]].fecha_prestamo.dia,array_de_prestamos[ubicacion[j]].fecha_prestamo.mes,array_de_prestamos[ubicacion[j]].fecha_prestamo.anio,array_de_prestamos[ubicacion[j]].fecha_prestamo.dias_semana);   
                    }
                }
                printf("\n\nPRESIONA ENTER");
                getchar();
                break;
            case 2:
                for(short int j=0;j<MAX_ELEMENTOS_ARRAY;j++)
                {   
                    if(array_de_prestamos[j].matricula!=0)
                    {
                        for(short int i=0;i<MAX_ELEMENTOS_ARRAY;i++)
                        {
                            if(array_de_prestamos[j].matricula==array_de_usuarios[i].matricula)
                            {
                                ubicacion[aux2]=j;
                                tipo[aux2]=i;
                                aux2++;
                                contador++;
                                break;
                            }

                        }
                    }
                }
                for(short int i=Contaduria;i<=Ambiental;i++)
                {
                    contador2=0;
                    contador3=0;
                    printf("\t*CARRERA %hd*\n",i);
                    
                    for(short int j=0;j<contador;j++)
                    {
                        if(array_de_usuarios[tipo[j]].carrera==i)
                        {
                            if(array_de_prestamos[ubicacion[j]].matricula==array_de_usuarios[tipo[j]].matricula && contador3==0)
                            {
                                printf("MATRICULA: %u\n",array_de_prestamos[ubicacion[j]].matricula);
                                printf("USUARIO: %s\n",array_de_usuarios[tipo[j]]);
                                contador3++;
                            }
                            imprimir_title(ubicacion[j]);
                            printf("Identificador de ejemplar del libro: %u\n",array_de_prestamos[ubicacion[j]].id_ejemplar); fflush(stdin);
                            printf("fecha de PRESTAMO: %02hu/%02hu/%hu Dia: %s\n",array_de_prestamos[ubicacion[j]].fecha_prestamo.dia,array_de_prestamos[ubicacion[j]].fecha_prestamo.mes,array_de_prestamos[ubicacion[j]].fecha_prestamo.anio,array_de_prestamos[ubicacion[j]].fecha_prestamo.dias_semana);fflush(stdin);
                            contador2++;
                            if(array_de_prestamos[ubicacion[j]].estado_actual!=devuelto)
                            {
                                printf("fecha de DEVOLUCION: %02hu/%02hu/%hu Dia: %s\n\n",array_de_prestamos[ubicacion[j]].fecha_devolucion.dia,array_de_prestamos[ubicacion[j]].fecha_devolucion.mes,array_de_prestamos[ubicacion[j]].fecha_devolucion.anio,array_de_prestamos[ubicacion[j]].fecha_devolucion.dias_semana);fflush(stdin);   
                                dias_restantes(ubicacion[j]);
                            }
                            else
                            {
                                printf("fecha en la que se DEVOLVIO el libro: %02hu/%02hu/%hu Dia: %s\n\n",array_de_prestamos[ubicacion[j]].fecha_prestamo.dia,array_de_prestamos[ubicacion[j]].fecha_prestamo.mes,array_de_prestamos[ubicacion[j]].fecha_prestamo.anio,array_de_prestamos[ubicacion[j]].fecha_prestamo.dias_semana);   
                            }
                            
                        }
                    }
                    if(contador2==0)
                    {
                        printf("NO HAY NINGUNO\n");
                    }
                }
                printf("\n\nPRESIONA ENTER");
                getchar();
                break;
            case 3:
                break;
            case 4:
                break;
            default:
                salir=1;
                break;

        }
    }while(salir==0);
}

void name_carrera(short int j)
{
    switch(j)
    {
        case 1:
            printf("");
    }
            
}

/*
     short int i,j;
    short int ubicacion[3]={-1,-1,-1};
    short int aux=0;
    short int contador=0;
    printf("Informacion de prestamos obtenida desde el archivo:\n\n"); fflush(stdin);
    for(i=0;i<MAX_ELEMENTOS_ARRAY;i++)
    {
        contador=0;
        aux=0;
        if(i==ubicacion[0] || i==ubicacion[1] || i==ubicacion[2])
            continue;
        
        for(j=0;j<MAX_ELEMENTOS_ARRAY;j++)
        {
            if(array_de_prestamos[j].matricula==array_de_prestamos[i].matricula && array_de_prestamos[i].matricula!=0)
            {
                ubicacion[aux]=j;
                aux++;
                contador++;
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
     
            
        }
      
    }    
*/
        
        
        
        
        
        

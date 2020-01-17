#include<stdio.h>
#include<iostream>
#include "datatypes.h"
using namespace std;

extern const char *lista_carreras[];

void admon_usuarios() {
	string producto[100];
	string matricula[100];
	int opc=0, i=0, k=0, menu, a;
		while (opc!=4) {

		printf("1 agregar usuario\n");
		printf("2 modificar usuario\n");
		printf("3 listar\n");
		printf("4 salir \n");
		scanf("%d", &opc);
			string nombre;
			string nuevo;
			string ID;
			string IDN;
			string estudio;
		switch(opc)
		{
		case 1:

			cout<<"ingrese el nombre del usuario"<<endl;
			cin>>nombre;
			producto[i]=nombre;
			i++;
			cout<<"ingrese matricula"<<endl;
			cin>>ID;
			matricula[k]=ID;
			k++;
			cout<<"ingrese carrera"<<endl;
			cin>>a;
			//carreras[a]=estudio;
			for(int j=0; j<=19; j++) {

                  printf(lista_carreras[j]);
	}
		

        break;

		case 2:
			cout<<"1 modificar nombre"<<endl;
			cout<<"2 modificar matricula"<<endl;
			cout<<"3 modificar carrera"<<endl;
			cin>>menu;
			switch (menu)
			{
				case 1:
           	cout<<"ingrese nombre a modificar"<<endl;
			cin>>nombre;
			cout<<"ingrese nuevo nombre"<<endl;
			cin>>nuevo;
			for (int j=0; j<i; j++)
		    {
				if(producto[j] == nombre)
				{
                    producto[j] = nuevo;
                    cout<<"usuario modificado correctamente"<<endl;

				}

	}
	 break;
	       case 2: cout<<"ingrese matricula a modifiar"<<endl;
	       cin>>ID;
	       cout<<"ingrese la nueva matricula"<<endl;
	       cin>>IDN;
	       for (int j=0; j<k; j++){

if(matricula[j]==ID) {
	matricula[j]=IDN;
	cout<<"matricula modificada"<<endl;
	}
				}
				break;
				case 3:

                 break;

                    break;


	 	   }

		 case 3:
                	for (int j=0; j<i; j++) {
						cout<<(j+1)<<producto[j]<<endl;
					}
						for (int j=0; j<i; j++){
							cout<<matricula[j]<<endl;
							}


 		}
	}
}

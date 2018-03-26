/*
 * Receptor.cpp
 *
 *  Created on: 26/4/2017
 *      Author: Ignacio Caro Cumplido y Javier Ballesteros Morón
 */

#include "Receptor.h"

using namespace std;

Receptor::Receptor() {
	control = false;
	fich = false;
	campo = 1;
	contadorDatos = 0;
	cuentaDebug = 0;
	finish = false;
	// TODO Auto-generated constructor stub

}
/**
 * Método que recibe los datos del Puerto y los ingresa y devuelve en una trama
 */
void Receptor::recDatos(HANDLE &PuertoCOM, Trama& trama, char car,
		bool &finish) {
	car = RecibirCaracter(PuertoCOM);
	if (car) { //Comprobamos el dato a recibir
		switch (campo) { //Campo, variable que define el campo a recibir
		case 1: //Caracter de Sincronismo
			if (car == 22) { //Trama de Control
				trama.setS(car);
				campo++;
			} else {
				if (car == '#') {
					f.open("Frc-R.txt"); //Abrimos el fichero
					printf("\nRecibiendo fichero...\n");
					fich = true;
				}
				if (car == '@') {
					f.close(); //cerramos el fichero
					printf("\nFichero recibido\n");
					fich = false;
				}
			}
			break;
		case 2:		//Dirección
			trama.setD(car);
			campo++;
			break;
		case 3:		//Control
			trama.setC(car);
			if (car != 02) {
				control = true;
			}
			campo++;
			break;
		case 4:		//Numero de Trama
			trama.setNt(car);
			if (control) {
				printf("Trama ");
				trama.showControl();
				printf(" Recibida.\n");
				campo = 1;
				control = false;
				finish = true;
			} else {
				campo++;
			}
			break;

		case 5:		//Longitud
			trama.setL(car);
			campo++;
			break;
		case 6:		//Datos

			datos[contadorDatos] = car;
			if (contadorDatos < trama.getL() - 1) {
				contadorDatos++;
			} else {
				datos[contadorDatos + 1] = '\0';
				trama.setDatos(datos);
				contadorDatos = 0;
				campo++;
			}
			break;
		case 7:		//BCE
			cuentaDebug++;
			trama.setBce(car);
			if (!fich) {
				trama.showDatos();
			} else {
				recFich(trama);
			}
			campo = 1;
			finish = true;
			break;
		}
	}
}
/**
 * Método que recibe los datos y los devuelve en una trama del método maestro esclavo
 *
 */
void Receptor::recDatosMS(HANDLE& PuertoCOM, Trama& trama, char car,
		bool& error, bool& finish) {
	car = RecibirCaracter(PuertoCOM);
	if (car) { //Comprobamos el dato a recibir
		switch (campo) { //Campo, variable que define el campo a recibir
		case 1: //Caracter de Sincronismo
			if (car == 22) { //Trama de Control
				trama.setS(car);
				campo++;
			} else {
				if (car == '#') {
					f.open("Frc-R.txt"); //Abrimos el fichero
					fich = true;
				}
				if (car == '@') {
					f.close(); //cerramos el fichero
					fich = false;

				}
			}
			break;
		case 2:		//Dirección
			trama.setD(car);
			campo++;
			break;
		case 3:		//Control
			trama.setC(car);
			if (car != 02) {
				control = true;
			}
			campo++;
			break;
		case 4:		//Numero de Trama
			trama.setNt(car);
			if (control) {
				campo = 1;
				control = false;
				finish = true;
			} else {
				campo++;
			}
			break;

		case 5:		//Longitud
			trama.setL(car);
			campo++;
			break;
		case 6:		//Datos
			datos[contadorDatos] = car;
			if (contadorDatos < trama.getL() - 1) {
				contadorDatos++;
			} else {
				datos[contadorDatos + 1] = '\0';
				trama.setDatos(datos);
				contadorDatos = 0;
				campo++;
			}
			break;
		case 7:		//BCE
			trama.setBce((unsigned char) car);
			if (trama.getBce()
					!= (unsigned char) trama.calcBCE(trama.getDatos())
					&& !finish) {

				error = true;
			} else {
				recFich(trama);
			}
			campo = 1;
			finish = true;
			break;
		}
	}

}
/**
 * Metodo que escribe los datos de la trama en el fichero de destino
 */
void Receptor::recFich(Trama trama) {
	char cadena[255];
	strcpy(cadena, trama.getDatos());
	int i = 0;
	if (f.is_open()) {
		while (i < trama.getL()) {
			f.put(cadena[i]);
			i++;
		}
	} else {
		printf("Error en el fichero al recibir.");
	}
}
/**
 * Método que sirve para recibir el tipo de trama de control a enviar
 */
void Receptor::recControl(HANDLE &PuertoCOM, Trama &trama, bool &fin) {
	char car;
	car = RecibirCaracter(PuertoCOM);

	if (car) //Comprobamos si hay datos que recibir
		switch (campo) {
		case 1: //Posible carácter de sincronismo
			trama.setS(car);
			campo++;
			break;
		case 2: //Carácter de dirección
			trama.setD(car);
			campo++;
			break;
		case 3: //Carácter de control
			trama.setC(car);
			campo++;
			break;
		case 4: //Número de trama
			trama.setNt(car);
			campo = 1;
			fin = true;
			break;
		default:
			//Haremos algo distinto
			break;
		}
}

Receptor::~Receptor() {
// TODO Auto-generated destructor stub
}


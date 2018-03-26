/*
 * Trama.cpp
 *
 *  Created on: 26/4/2017
 *      Author: Ignacio Caro Cumplido y Javier Ballesteros Morón
 */

#include "Trama.h"

using namespace std;

Trama::Trama() {
	// TODO Auto-generated constructor stub
	this->S = 22;
	this->D = 'T';
	this->C = 02;
	this->L = 0;
	this->NT = '0';
	this->BCE = 1;
}

/***********************UTILES***********************/
/**
 * Selección trama de control
 */
void Trama::tramaControl() {
	printf("Seleccione qué tipo de trama de control desea enviar:\n");
	printf("1 - Trama ENQ\n");
	printf("2 - Trama EOT\n");
	printf("3 - Trama ACK\n");
	printf("4 - Trama NACK\n");
	printf("\n");
	bool select = false;
	char car;

	while (!select) {
		car = getch();
		printf("%c", car);
		printf("\n");
		switch (car) {

		case '1':
			printf("Trama ENQ seleccionada.\n");
			this->C = 05;
			select = true;
			break;
		case '2':
			printf("Trama EOT seleccionada.\n");
			this->C = 04;
			select = true;
			break;
		case '3':
			printf("Trama ACK seleccionada.\n");
			this->C = 06;
			select = true;
			break;
		case '4':
			printf("Trama ENQ seleccionada.\n");
			this->C = 21;
			select = true;
			break;
		default:
			printf("Seleccione una Trama Válida.\n");
			break;
		}
	}
	this->S = 22;
	this->D = 'T';
	this->NT = '0';

}
/**
 * Definir trama de Datos
 */
void Trama::tramaDatos() {
	this->S = 22;
	this->D = 'T';
	this->C = 02;
	this->L = 0;
	this->NT = '0';
	this->BCE = 1;
}
/**
 * Mostrar la trama de control recibida
 */
void Trama::showControl() {
	unsigned char car = this->C;
	if (car)
		switch (car) {
		case 05:
			printf("ENQ");
			break;
		case 04:
			printf("EOT");
			break;
		case 06:
			printf("ACK");
			break;
		case 21:
			printf("NACK");
			break;
		case 02:
			printf("STX");
			break;
		default:
			printf("default");
			break;
		}
}
/**
 * Recorre los datos de la trama de control y los muestra por pantalla
 */
void Trama::showDatos() {
//	printf("%s", this->Datos);
	for (int i = 0; i < this->L; i++) {
		printf("%c", this->Datos[i]);
	}
}
/**
 * Método que calcula el BCE y lo devuelve en unsigned char
 */
unsigned char Trama::calcBCE(char cadena[]) {
	unsigned char resultado = cadena[0];
	for (int i = 1; i < this->getL(); i++) {
		resultado = resultado xor cadena[i];
	}
	if (resultado == '@' || resultado == 0 || resultado == '$')
		resultado = 1;
	return resultado;
}
/**
 * Muestra trama de control enviada
 */
void Trama::mSEC(char u) {
	printf("E   ");
	printf("%c   ", u);
	showControl();
	printf("	%c \n", getNt());
}
/**
 * Muestra trama de Datos enviada
 */
void Trama::mSED(bool x, char u) {
	printf("E   ");
	printf("%c   ", u);
	showControl();
	printf("	%c", getNt());
	if (x) {
		printf("   %d \n", getBce());
	} else {
		printf("   %d	%d \n", getBce(), calcBCE(getDatos()));
	}
}
/**
 * Muestra trama de Control Recibida
 */
void Trama::mSRC(char u) {
	printf("R   ");
	printf("%c   ", u);
	showControl();
	printf("	%c \n", getNt());
}
/**
 * Muestra trama de Datos Recibida
 */
void Trama::mSRD(bool x, char u) {
	printf("R   ");
	printf("%c   ", u);
	showControl();
	printf("	%c", getNt());
	if (x) {
		printf("   %d \n", getBce());
	} else {
		printf("   %d	%d \n", getBce(), calcBCE(getDatos()));
	}
}

/***********************SET***********************/
void Trama::setBce(unsigned char bce) {
	this->BCE = bce;
}

void Trama::setC(unsigned char c) {
	this->C = c;
}

void Trama::setD(unsigned char d) {
	this->D = d;
}

void Trama::setL(unsigned char l) {
	this->L = l;
}

void Trama::setNt(unsigned char nt) {
	this->NT = nt;
}

void Trama::setS(unsigned char s) {
	this->S = s;
}

void Trama::setDatos(const char datos[]) {
//	strcpy(this->Datos, datos);
	for (int x = 0; x < this->L; x++) {
		this->Datos[x] = datos[x];
	}
}

/***********************GET***********************/
unsigned char Trama::getBce() {
	return this->BCE;
}

unsigned char Trama::getC() {
	return this->C;
}

unsigned char Trama::getD() {
	return this->D;
}

char* Trama::getDatos() {
	return this->Datos;
}

unsigned char Trama::getL() {
	return this->L;
}

unsigned char Trama::getNt() {
	return this->NT;
}

unsigned char Trama::getS() {
	return this->S;
}

Trama::~Trama() {
// TODO Auto-generated destructor stub
}


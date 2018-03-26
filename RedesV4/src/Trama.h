/*
 * TramaClass.h
 *
 *  Created on: 25/4/2017
 *      Author: Ignacio Caro Cumplido y Javier Ballesteros Morón
 */

#ifndef TRAMA_H_
#define TRAMA_H_

#include <conio.h>
#include <windows.h>
#include <iostream>
#include <fstream>

#include <string.h>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include "PuertoSerie.h"

#define SYN 22
#define STX 02

using namespace std;

class Trama {
private:
	unsigned char S;	//Sincr 22
	unsigned char D;	//Dirección
	unsigned char C;	//Control (05=ENQ, 04=EOT, 06=ACK, 21=NACK)
	unsigned char NT;	//Numero de Trama
	unsigned char L;	//Longitud del campo Datos(usados)
	char Datos[255];
	unsigned char BCE;	// iniciado a 1
public:
	Trama();

	//Métodos Útiles
	void tramaControl();

	void showControl();

	void tramaDatos();

	void showDatos();

	void mSEC(char u);
	void mSED(bool x, char u);

	void mSRC(char u);
	void mSRD(bool x, char u);

	unsigned char calcBCE(char Cadena[]);

	//Métodos SET
	void setS(unsigned char s);

	void setD(unsigned char d);

	void setC(unsigned char c);

	void setNt(unsigned char nt);

	void setL(unsigned char l);

	void setDatos(const char datos[]);

	void setBce(unsigned char bce);

	//Métodos GET
	unsigned char getS();

	unsigned char getD();

	unsigned char getC();

	unsigned char getNt();

	unsigned char getL();

	char* getDatos();

	unsigned char getBce();

	virtual ~Trama();

};

#endif /* TRAMACLASS_H_ */

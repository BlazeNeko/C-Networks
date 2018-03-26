/*
 * Control.h
 *
 *  Created on: 26/4/2017
 *      Author: Ignacio Caro Cumplido y Javier Ballesteros Morón
 */

#ifndef CONTROL_H_
#define CONTROL_H_

#include "Trama.h"
#include "Emisor.h"
#include "Receptor.h"

using namespace std;

class Control {
private:
	HANDLE PuertoCOM;
	char mensaje[802];
	bool selectPort(HANDLE &puerto);
	void writeMsg(char * cadena, int& acumulador, char car);
	void pressEnter(char* cadena, int &acumulador);
	void pressBack(int &acumulador, char car);
	void masterSlave(Trama &trama);
	void master(Trama &trama);
	void slave(Trama &trama);
	void selectMS(Trama &trama);
	void sondeo(Trama &trama);
	bool confPort(HANDLE &PuertoCOM, string puerto);
	void showMenu();
	int liberar();
	void prueba_receptor();
	void prueba_emisor();
	void pruebas();
public:
	Control();

	void start();

	virtual ~Control();
};

/* namespace std */

#endif /* CONTROL_H_ */

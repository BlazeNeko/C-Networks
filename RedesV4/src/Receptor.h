/*
 * Receptor.h
 *
 *  Created on: 26/4/2017
 *      Author: Ignacio Caro Cumplido y Javier Ballesteros Morón
 */

#ifndef RECEPTOR_H_
#define RECEPTOR_H_

#include <fstream>

#include "Trama.h"

using namespace std;

class Receptor {
private:
	int campo;
	bool control;
	int cuentaDebug;
	bool fich;
	int contadorDatos;
	char datos[255];
	ofstream f;
	bool finish;
public:
	Receptor();

	void recDatos(HANDLE &PuertoCOM, Trama& trama, char car, bool &finish);

	void recDatosMS(HANDLE &PuertoCOM, Trama& trama, char car, bool &error,
			bool &finish);
	void recControl(HANDLE &PuertoCOM, Trama &trama, bool &fin);

	void recFich(Trama trama);

	virtual ~Receptor();
};

#endif /* RECEPTOR_H_ */

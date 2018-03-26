/*
 * Emisor.h
 *
 *  Created on: 25/4/2017
 *      Author: Ignacio Caro Cumplido y Javier Ballesteros Morón
 */

#ifndef EMISOR_H_
#define EMISOR_H_

#include "Trama.h"
#include "Receptor.h"

using namespace std;

class Emisor {
private:
	void sendTramaDatos(HANDLE& PuertoCOM, Trama trama);
	void sendTramaFich(HANDLE& PuertoCOM, Trama trama);
public:
	Emisor();
	void sendTramaControl(HANDLE& PuertoCOM, Trama trama);

	void sendDatos(HANDLE& PuertoCOM, Trama& trama, char datos[], int contador);
	void sendControl(HANDLE& PuertoCOM, Trama& trama);
	void sendFich(HANDLE& PuertoCOM, Trama &trama);
	void sendFichMS(HANDLE& PuertoCOM, Trama &trama);
	virtual ~Emisor();
};

#endif /* EMISOR_H_ */

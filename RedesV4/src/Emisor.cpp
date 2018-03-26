/*
 * Emisor.cpp
 *
 *  Created on: 25/4/2017
 *      Author: Ignacio Caro Cumplido y Javier Ballesteros Morón
 */

#include "Emisor.h"

using namespace std;

Emisor::Emisor() {
	// TODO Auto-generated constructor stub

}
/**
 * Método que envia por Puerto una Trama de DATOS
 */
void Emisor::sendTramaDatos(HANDLE& PuertoCOM, Trama trama) {
	EnviarCaracter(PuertoCOM, trama.getS());
	EnviarCaracter(PuertoCOM, trama.getD());
	EnviarCaracter(PuertoCOM, trama.getC());
	EnviarCaracter(PuertoCOM, trama.getNt());
	EnviarCaracter(PuertoCOM, trama.getL());
	EnviarCadena(PuertoCOM, trama.getDatos(), trama.getL());
	EnviarCaracter(PuertoCOM, trama.getBce());
}

/**
 * Método que envia por Puerto una Trama de CONTROL
 */
void Emisor::sendTramaControl(HANDLE& PuertoCOM, Trama trama) {
	EnviarCaracter(PuertoCOM, trama.getS());
	EnviarCaracter(PuertoCOM, trama.getD());
	EnviarCaracter(PuertoCOM, trama.getC());
	EnviarCaracter(PuertoCOM, trama.getNt());
}
/**
 * Método para elegir la trama de control y enviarla
 */
void Emisor::sendControl(HANDLE& PuertoCOM, Trama& trama) {
	trama.tramaControl();
	sendTramaControl(PuertoCOM, trama);
}

/**
 * Método para enviar por los datos mediante X tramas por Puerto con un límite en la Cadena
 */
void Emisor::sendDatos(HANDLE& PuertoCOM, Trama& trama, char datos[],
		int contador) {
	datos[contador] = '\n';
	contador++;
	char mensaje[255];
	int nTramas = contador / 254;
	if (contador % 254 != 0) {
		nTramas++;
	}
	/***********************************/
	for (int v = 0; v < nTramas; v++) {
		trama.tramaDatos();
		//Calculamos la longitud del numero de trama
		if (v != nTramas - 1) {
			trama.setL(254);
		} else {
			trama.setL(contador % 254);

		}
		//Rellenamos los datos de la trama
		for (int m = 0; m < trama.getL(); m++) {
			mensaje[m] = datos[m + v * 254];
		}
		mensaje[trama.getL() + 1] = '\0';
		//Calculamos el BCE
		trama.setDatos(mensaje);
		trama.setBce(trama.calcBCE(mensaje));

		sendTramaDatos(PuertoCOM, trama);

	}
	/***********************************/
}
/**
 * Método que abre el fichero si existe y lo envia por tramas
 */
void Emisor::sendFich(HANDLE& PuertoCOM, Trama &trama) {
	char cadena[255];
	char car=0;
	bool finish = false, fi = false;
	int contDebug = 0;
	int contador = 0;
	Receptor R;
	ifstream f("Frc-E.txt");
	Trama recibida = Trama();
	if (f.is_open()) {
		printf("Enviando Fichero...\n");
		//Caracter que declara la entrada de un fichero
		EnviarCaracter(PuertoCOM, '#');
		while (!f.eof() && !finish) {
			R.recDatos(PuertoCOM, recibida, car, fi);
			if (kbhit()) { // comprobamos que no se haya pulsado ESC
				car = getch();
				if (car == 27)
					finish = true;
			} else {
				f.read(cadena, 254);
				cadena[f.gcount()] = '\0'; //añade el barra cero final
				contador = strlen(cadena);
				trama.tramaDatos();
				trama.setL(contador);
				trama.setDatos(cadena);
				trama.setBce(trama.calcBCE(cadena));
				if (f.gcount() != 0) {
					sendTramaDatos(PuertoCOM, trama); //envio de la trama
				}
			}
			contDebug++;
		}
		//Caracter que declara la
		EnviarCaracter(PuertoCOM, '@');
		printf("Fichero Enviado...\n");
		contDebug = 0;

	} else {
		printf(
				"Se ha producido un error al abrir archivo, comprueba que existe 'Frc-E.txt'...\n");
	}

}
/**
 * Método que envia el fichero mediante el método Maestro-Esclavo permitiendo la introducción de errores en tramas
 */
void Emisor::sendFichMS(HANDLE& PuertoCOM, Trama &trama) {
	Receptor R;
	char cadenaAux[255];
	char cadena[255];
	char car;
	int i = 0;
	bool finish = false;
	bool fin = false;
	Trama Rec = Trama();
	//Abre fichero a enviar

	ifstream f("Frc-E.txt");
//Comprueba que está abierta
	if (f.is_open()) {
		trama.setS(22);
		if (trama.getD() == 'T') {
			trama.setD('T');
		} else {
			trama.setD('R');
		}

		//Envía caracter de inicio de fichero
		trama.setC(STX);
		EnviarCaracter(PuertoCOM, '#');
		while (!f.eof() && !finish) {
			//Añade control STX

			f.read(cadena, 254);
			cadena[f.gcount()] = '/0';
			if (i % 2 == 0)
				trama.setNt('0');
			else
				trama.setNt('1');
			trama.setL(f.gcount());
			i++;

			for (int x = 0; x < f.gcount(); x++) {
				cadenaAux[x] = cadena[x];
			}
			char m = trama.calcBCE(cadena);
			trama.setBce(m);
			//Introduce error
			//******************************************************/
			if (kbhit()) {
				car = getch();
				if (car == 63) {
					cadena[0] = 'ç';
//					printf("Introduciendo error en la cadena \n");
				}
				if (car == 27) {
					finish = true;
				}
			}
			//******************************************************/
			trama.setDatos(cadena);
			sendTramaDatos(PuertoCOM, trama);
			trama.mSED(true, trama.getD());
			fin = false;
			while (!fin) { //Recepcion de trama con ACK o NACK
				R.recControl(PuertoCOM, Rec, fin);
			}
			Rec.mSRC(Rec.getD());
			//Recibe NACK
			//******************************************************/
			if (Rec.getC() == 21) {
				trama.setDatos(cadenaAux);
				trama.setBce(trama.calcBCE(cadenaAux));
				sendTramaDatos(PuertoCOM, trama);
				trama.mSED(true, trama.getD());
				fin = false;
				while (!fin) { //Recepcion de trama con ACK o NACK
					R.recControl(PuertoCOM, Rec, fin);
				}
				Rec.mSRD(true, Rec.getD());
			}
			//******************************************************/

		}
		EnviarCaracter(PuertoCOM, '@');
		f.close();
	} else {
		printf("No encuentra el archivo.\n");
	}
}
Emisor::~Emisor() {
// TODO Auto-generated destructor stub
}

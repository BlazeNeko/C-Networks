/*
 * Control.cpp
 *
 *  Created on: 26/4/2017
 *      Author: Ignacio Caro Cumplido y Javier Ballesteros Morón
 */

#include "Control.h"

using namespace std;

Control::Control() {
	PuertoCOM = NULL;

}
/**
 * Seleccion del Puerto
 */
bool Control::selectPort(HANDLE& PuertoCOM) {
	bool rightChoice = false;
	string puerto;
	char car;
	while (!rightChoice) {
		printf("Introduzca el puerto que desea utilizar \n");
		printf("1 - COM1\n");
		printf("2 - COM2\n");
		printf("3 - COM3\n");
		printf("4 - COM4\n");
		car = getch();

		switch (car) {
		case '1':
			puerto = "COM1";
			rightChoice = true;
			break;
		case '2':
			puerto = "COM2";
			rightChoice = true;
			break;
		case '3':
			puerto = "COM3";
			rightChoice = true;
			break;
		case '4':
			puerto = "COM4";
			rightChoice = true;
			break;
		default:
			printf(
					"Opcion erronea. Por favor, inserte de nuevo el número de la opcion\n");

		}
	}
	return confPort(PuertoCOM, puerto);
}
/**
 * Configuracion del puerto
 */
bool Control::confPort(HANDLE &PuertoCOM, string puerto) {
	bool rightChoice = false;
	bool rightCustom = false;

	int bps;
	int bitsDatos;
	int paridad;
	int bitsParada;
	char car;
	while (rightChoice == false) {
		printf("Introduzca la opcion deseada:\n");
		printf("1 - Configuracion por defecto\n");
		printf("2 - Configuracion personalizada\n");

		car = getch();

		switch (car) {
		case '1':
			bps = 9600;
			bitsDatos = 8;
			paridad = 0;
			bitsParada = 0;
			rightChoice = true;
			break;
		case '2':
			while (rightCustom == false) {
				printf("Introduzca los bits por segundo:\n");
				printf("1 - 1400\n");
				printf("2 - 4800\n");
				printf("3 - 9600\n");
				printf("4 - 19200\n");
				car = getch();

				switch (car) {
				case '1':
					bps = 1400;
					rightCustom = true;
					break;
				case '2':
					bps = 4800;
					rightCustom = true;
					break;
				case '3':
					bps = 9600;
					rightCustom = true;
					break;
				case '4':
					bps = 19200;
					rightCustom = true;
					break;
				default:
					printf(
							"Opcion erronea. Por favor, inserte de nuevo el número de la opcion");

				}
			}

			rightCustom = false;

			while (rightCustom == false) {
				printf("Introduzca los bits de datos:\n");
				printf("1 - 5\n");
				printf("2 - 6\n");
				printf("3 - 7\n");
				printf("4 - 8\n");
				car = getch();

				switch (car) {
				case '1':
					bitsDatos = 5;
					rightCustom = true;
					break;
				case '2':
					bitsDatos = 6;
					rightCustom = true;
					break;
				case '3':
					bitsDatos = 7;
					rightCustom = true;
					break;
				case '4':
					bitsDatos = 8;
					rightCustom = true;
					break;
				default:
					printf(
							"Opcion erronea. Por favor, inserte de nuevo el número de la opcion");

				}
			}

			rightCustom = false;

			while (rightCustom == false) {
				printf("Introduzca la paridad:\n");
				printf("1 - Sin Paridad\n");
				printf("2 - Impar\n");
				printf("3 - Par\n");
				printf("4 - Marca\n");
				printf("5 - Espacio\n");

				car = getch();

				switch (car) {
				case '1':
					paridad = 0;
					rightCustom = true;
					break;
				case '2':
					paridad = 1;
					rightCustom = true;
					break;
				case '3':
					paridad = 2;
					rightCustom = true;
					break;
				case '4':
					paridad = 3;
					rightCustom = true;
					break;
				case '5':
					paridad = 4;
					rightCustom = true;
					break;
				default:
					printf(
							"Opcion erronea. Por favor, inserte de nuevo el número de la opcion");

				}
			}

			rightCustom = false;

			while (rightCustom == false) {
				printf("Introduzca los bits de parada:\n");
				printf("1 - 1\n");
				printf("2 - 1,5\n");
				printf("3 - 2\n");
				cin >> car;

				switch (car) {
				case '1':
					bitsParada = 0;
					rightCustom = true;
					break;
				case '2':
					bitsParada = 1;
					rightCustom = true;
					break;
				case '3':
					bitsParada = 2;
					rightCustom = true;
					break;

				default:
					printf(
							"Opcion erronea. Por favor, inserte de nuevo el número de la opcion");

				}
			}
			rightChoice = true;
			break;
		default:
			printf(
					"Opcion erronea. Por favor, inserte de nuevo el número de la opcion");

		}
	}
	if (puerto == "COM1")
		PuertoCOM = AbrirPuerto("COM1", bps, bitsDatos, paridad, bitsParada); //Abrimos el puertoCOM COM1 (en la sala siempre abrimos el COM1)
	if (puerto == "COM2")
		PuertoCOM = AbrirPuerto("COM2", bps, bitsDatos, paridad, bitsParada);
	if (puerto == "COM3")
		PuertoCOM = AbrirPuerto("COM3", bps, bitsDatos, paridad, bitsParada);
	if (puerto == "COM4")
		PuertoCOM = AbrirPuerto("COM4", bps, bitsDatos, paridad, bitsParada);

	if (PuertoCOM == NULL) {
		printf("Error al abrir el puerto\n");
		return false;
	} else {
		printf("Puerto abierto correctamente\n");
		return true;
	}
}
/**
 * Muestra el menú inicial
 */
void Control::showMenu() {
	printf("*******************************************\n");
	printf("Que desea hacer: \n");
	printf("F1 - Trama de Datos\n");
	printf("F2 - Trama de Control\n");
	printf("F3 - Fichero\n");
	printf("F4 - Maestro/Esclavo\n");
	printf("*******************************************\n");
}
/**
 * Va guardando en la cadena cada caracter escrito antes de pasarselo a la trama
 */
void Control::writeMsg(char* cadena, int &acumulador, char car) {
	if (acumulador < 800) {
		cadena[acumulador] = car;
		acumulador++;
		printf("%c", car);
	} else {
		printf(
				" \n No puede escribir mas, la cadena ha llegado a su limite \n");
	}
}
/**
 * Añade el salto de linea a la cadena
 */
void Control::pressEnter(char* cadena, int &acumulador) {
	cadena[acumulador] = '\n';
	printf("\n");
	acumulador++;
}
/**
 * Borra el último caracter de pantalla y resta el acumulador
 */
void Control::pressBack(int& acumulador, char car) {
	if (acumulador > 0) {
		printf("\b");
		printf(" ");
		printf("\b");
		acumulador--;
	}
}
/**
 * Metodo para la seleccion de maestro esclavo
 */
void Control::masterSlave(Trama &trama) {
	bool select = false;
	char car;
	select = false;

	printf("***********************************\n");
	printf("*	1 - Maestro               *\n");
	printf("*	2 - Esclavo               *\n");
	printf("***********************************\n");

	while (!select) {
		car = getch();
		if (car == '1') {
			master(trama);
			select = true;
		}
		if (car == '2') {
			slave(trama);
			select = true;
		}
	}
}
/**
 * Metodo de maestro y seleccion de tipo de envio(seleccion o sondeo)
 */
void Control::master(Trama &trama) {
	Emisor E;
	bool select = false;
	printf("**************Maestro**************\n");
	printf("*	1 - Seleccion             *\n");
	printf("*	2 - Sondeo                *\n");
	printf("***********************************\n");

	while (!select) {
		char car2 = getch();
		if (car2 == '1') {
			selectMS(trama);
			select = true;
		}
		if (car2 == '2') {
			sondeo(trama);
			select = true;
		}
	}
}
/**
 * Metodo de envio seleccion de Maestro
 */
void Control::selectMS(Trama& trama) {
	Receptor R;
	Emisor E;
	bool finish = false;
//Envia
	trama.setS(22);
	trama.setD('R');	//Seleccion
	trama.setC(05);		//ENQ
	trama.setNt('0');
	trama.setBce(1);
	E.sendTramaControl(PuertoCOM, trama);
	trama.mSEC(trama.getD());
//Recibe
	while (!finish) {
		R.recControl(PuertoCOM, trama, finish);
	}
	trama.mSRC(trama.getD());
//Envia fichero
	E.sendFichMS(PuertoCOM, trama);
// Finaliza
	trama.setC(04);
	trama.setNt('0');

	E.sendTramaControl(PuertoCOM, trama);
	trama.mSEC(trama.getD());
	finish = false;
	while (!finish) {
		R.recControl(PuertoCOM, trama, finish);
	}
	trama.mSRC(trama.getD());
}
/**
 * Metodo de maestro, sondeo
 */
void Control::sondeo(Trama &trama) {
	Trama Rec = Trama();
	Receptor R;
	Emisor E;
	bool finish = false;
	bool error = false;
	char car = 0;
	//
	trama.setS(22);
	trama.setD('T');	//Sondeo
	trama.setC(05);		//ENQ
	trama.setNt('0');
	trama.setBce(1);

	E.sendTramaControl(PuertoCOM, trama);
	trama.mSEC(Rec.getD());

	//Recibe confirmacion
	while (!finish) {
		R.recControl(PuertoCOM, Rec, finish);
	}
	Rec.mSRC(Rec.getD());

	//Pasa a recibir cada trama
	while (Rec.getC() != 04) { //EOT
		finish = false;
		error = false;
		while (!finish) {
			R.recDatosMS(PuertoCOM, Rec, car, error, finish);
		}

		if (Rec.getC() == 04) {
			Rec.mSRC(Rec.getD());
		} else {
			Rec.mSRD(false, Rec.getD());
		}

		trama.setNt(Rec.getNt());
		if (Rec.getC() != 04) {
			if (error) {
				trama.setC(21);
			} else {
				trama.setC(06);
			}
			E.sendTramaControl(PuertoCOM, trama);
			trama.mSEC(trama.getD());
		}
	}
	do {
		trama.setC(liberar());
		trama.setNt(Rec.getNt());

		E.sendTramaControl(PuertoCOM, trama);
		trama.mSEC(trama.getD());
		//recibe aceptacion
		if (trama.getC() != 06) {
			finish = false;
			while (!finish) {
				R.recControl(PuertoCOM, Rec, finish);
			}
			Rec.mSRC(Rec.getD());
		}
	} while (trama.getC() == 21); //No libera

}
/**
 * Método para decidir si liberar al esclavo o no
 */
int Control::liberar() {
	char car = 05;
	printf("**************¿Liberar al esclavo?**************\n");
	printf("*	1 - Si                *\n");
	printf("*	2 - No                *\n");
	printf("*************************************	***********\n\n");

	while (car != 1 || car != 2) {
		car = getch();
		if (car == '1') {
			return 06;		//Libera ACK
		} else if (car == '2') {
			return 21;		//No libera NACK
		} else {
			printf("Seleccione una opcion correcta\n");
		}
	}
}
/**
 * Metodo de esclavo y sus acciones
 */
void Control::slave(Trama &trama) {
	Receptor R;
	Emisor E;
	Trama Rec = Trama();

	int i = 0;
	char car = 0;
	bool fail = false;
	bool finish = false;

	printf("**************Esclavo**************\n");
	while (!finish) {
		R.recControl(PuertoCOM, Rec, finish);
	}
	Rec.mSRC(Rec.getD());
	//*********************Seleccion*********************
	if (Rec.getD() == 'R') { //Seleccion
		//Acepta
		trama.setS(22);
		trama.setD('R');

		while (Rec.getC() != 04) {		//04=EOT
			trama.setNt(Rec.getNt());
			if (fail) {
				trama.setC(21);		//21=NACK
			} else {
				trama.setC(06); //06=ACK
			}
			E.sendTramaControl(PuertoCOM, trama);
			trama.mSEC(Rec.getD());

			fail = false;
			finish = false;
			while (!finish) {
				R.recDatosMS(PuertoCOM, Rec, car, fail, finish);
			}
			if (Rec.getC() == 04) { //04=EOT
				Rec.mSRC(Rec.getD());
			} else {

				Rec.mSRD(false, Rec.getD());
			}
		}
		trama.setNt(Rec.getNt());
		E.sendTramaControl(PuertoCOM, trama);
		trama.mSEC(Rec.getD());

	}
	//*********************Sondeo*********************
	else {
		trama.setS(22);
		trama.setD('T');
		trama.setC(06);
		trama.setNt(Rec.getNt());

		E.sendTramaControl(PuertoCOM, trama);
		trama.mSEC(Rec.getD());

		E.sendFichMS(PuertoCOM, trama);
		trama.setC(21);
		trama.setNt('0');
		trama.setC(04);
		i = 0;
		while (Rec.getC() != 06) {
			if (i % 2 == 0) {
				trama.setNt('0');
			} else {
				trama.setNt('1');
			}
			i++;
			trama.setC(04);
			E.sendTramaControl(PuertoCOM, trama);
			trama.mSEC(Rec.getD());

			finish = false;
			while (!finish) {
				R.recControl(PuertoCOM, Rec, finish);
			}
			Rec.mSRC(Rec.getD());
		}
	}
}
/**
 * Método principal que ejecuta el resto
 */
void Control::start() {
//Declarar variables necesarias y más usuales
	char car = 0;
	char mensaje[802];
// Parámetros necesarios al llamar a AbrirPuerto:
// - Nombre del puerto a abrir ("COM1", "COM2", "COM3", ...).
// - Velocidad (1200, 1400, 4800, 9600, 19200, 38400, 57600, 115200).
// - Número de bits en cada byte enviado o recibido (4, 5, 6, 7, 8).
// - Paridad (0=sin paridad, 1=impar, 2=par, 3=marca, 4=espacio).
// - Bits de stop (0=1 bit, 1=1.5 bits, 2=2 bits)

	//Seleccionamos y configuramos puerto
	if (selectPort(PuertoCOM)) {
//TRAMA
		Trama Tramar = Trama();
//Creamos Emisor y receptor
		Emisor E;
		Receptor R;
//	Mostramos las opciones posibles
		showMenu();

		bool finish = true;
// Escritura y lectura
		int acumulador = 0; //acumulador de caracteres
		while (car != 27) { // ESC
			R.recDatos(PuertoCOM, Tramar, car, finish);
			if (kbhit()) {
				car = getch();
				switch (car) {
				case '\0':
					car = getch();
					switch (car) {
					case 59:	//F1-Datos
						if (acumulador != 0) {
							E.sendDatos(PuertoCOM, Tramar, mensaje, acumulador);
							acumulador = 0;
							printf("\n");
						}
						break;
					case 60:
						//F2-Control
						E.sendControl(PuertoCOM, Tramar);
						printf("\n");
						break;
					case 61:
						//F3-Fichero
						E.sendFich(PuertoCOM, Tramar);
						printf("\n");
						break;
					case 62:
						//F4-Maestro/Esclavo
						masterSlave(Tramar);
						printf("\n");
						break;
					}
					break;
				default:
					//Escribir
					switch (car) {
					case 8:
						//back-> Borrar
						pressBack(acumulador, car);
						break;
					case 13:
						//Enter
						pressEnter(mensaje, acumulador);
						break;
					case 27:
						printf("Hasta luego");
						break;

					default:
						writeMsg(mensaje, acumulador, car);
						break;
					}
					break;
				}
			}
		}
		CerrarPuerto(PuertoCOM);
	} else {
		printf("No se ha podido configurar el puerto. Cerrando Programa");
	}
}

Control::~Control() {
// TODO Auto-generated destructor stub
}


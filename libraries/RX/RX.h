/*  
	This file is part of RX library.

    RX is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    RX is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with RX.  If not, see <http://www.gnu.org/licenses/>.
*/

 /*
	Esta librería ha sido creada para 
	el alisado de señales con un rango de valores enteros 
	por defecto entre 990 y 2010. Estos valores pueden ser 
	alterados de acuerdo a las necesidades del proyecto.

	Autor: Alejandro Gabriel Gorosito
 */

#ifndef RX_h
#define RX_h
#define LIBRARY_VERSION 1.0

class RX
{

public:

	// Funciones

	int Procesar(int entrada);
	void DefCantLecturas(int cantLecturas);
	void DefLimitesRX(int minCh, int maxCh);
	void deadBand(int val);
	void Inicializar();
	int Min();
	int Max();

private:
	// Variables para filtrado del Canal de RX

	float _ch, _chAnt = 0;
	int _cantLecturas = 6, _pos = 0, _pin;
	int _lectCh[6], _totalCh = 0, _salida = 0, _deadBand = 10;
	
	// Limites de rangos de entradas de RX
	int _minCh = -40, _maxCh = 40;

};

#endif
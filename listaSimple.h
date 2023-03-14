#pragma once
#include <stdlib.h>
#include <iostream>

#include "nodoS.h"

//Definicion de la clase, se definenlos atributos y los metodos
//TDA: se construye la definicion del TAD y sus operaciones.

class listaSimple
{
private:
	nodoS* cab; //cab es el puntero al primer nodo de la lista, si la lista vacia apunta a NULL.
	int largo; //largo es el que define la cantidad de datos.

public:
	listaSimple(); // constructor de la lista
	~listaSimple();

	nodoS* getCab();
	int getLargo();

	void setCab(nodoS*);
	void setLargo(int);

	/*UTILITARIOS */
	
	nodoS* dirNodo(int); //Devuelve la direccion del nodo de un dato.
	nodoS* dirAnterior(int); //Devuelve la direccion del nodo anterior al dato de referencia.
	nodoS* dirSiguiente(int); //Devuelve la direccion del nodo siguiente al dato de referencia.
	nodoS* dirUltimo(); //Direccion del ultimo de la lista.

	
	bool esVacia(); //Devuelve true si la lista esta vacia... cab = NULL o largo = 0

	void agregarInicio(int); //Agregar un dato al inicio de la lista
	void agregarFinal(int); //Agregar un dato al final de la lista.
	bool agregarAntesDe(int, int); //Agregar un dato antes de otro dato en la lista.
	bool agregarDespuesDe(int, int); //Agregar un dato despues de otro en la lista.

	bool eliminar(int); //Eliminar de la lista el dato de referencia.
	void eliminarRepetidos(); //Eliminar todos los repetidos.

	void desplegarLista(); //Desplegar todos los datos de la lista, del primero al ultimo.


};


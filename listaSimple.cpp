#include "listaSimple.h"

listaSimple::listaSimple()
{
	this->cab = NULL;
	this->largo = 0;
}

listaSimple::~listaSimple()
{
}

nodoS* listaSimple::getCab()
{
	return this->cab;
}

int listaSimple::getLargo()
{
	return this->largo;
}

void listaSimple::setCab(nodoS* ptr)
{
	this->cab = ptr;
}

void listaSimple::setLargo(int pLargo)
{
	this->largo = pLargo;
}

nodoS* listaSimple::dirNodo(int x)
{ //Devuelve la direcci�n del nodo cuyo valor sea x
	nodoS* aux = NULL;
	
	if (!esVacia()) {
		aux = getCab(); //Apunto al primer nodo de la lista
		while (aux !=NULL && aux->getDato() != x) //Mientras no haya recorrido toda la estructura y no haya encontrado el dato
			aux = aux->getSgte(); //Pase al siguiente nodo
	}
	
	return aux;
}

nodoS* listaSimple::dirAnterior(int x)
{ //Devuelve la direcci�n del nodo anterior al nodo cuyo valor sea x

	bool encontrado = false;
	nodoS* aux = NULL;

	if (getLargo() > 1) {
		aux = getCab();
		while ((aux->getSgte() != NULL) && (!encontrado)) {
			if (aux->getSgte()->getDato() == x)
				encontrado = true;
			else
				aux = aux->getSgte();
		}
			
	}

	if (encontrado)
		return aux;
	else
		return NULL;


}

nodoS *listaSimple::dirSiguiente(int x)
{
    bool encontrado = false;
	nodoS* aux = NULL;

	if (getLargo() > 1) {
		aux = getCab();
		while ((aux->getSgte() != NULL) && (!encontrado)) {
			if (aux->getDato() == x) {
				encontrado = true;
			}
				aux = aux->getSgte();
		}
			
	}

	if (encontrado)
		return aux;
	else
		return NULL;
}

nodoS* listaSimple::dirUltimo()
{  /*Devuelve la direcci�n del �ltimo nodo, si la lista est� vac�a devuelve NULL*/
	nodoS* ult = NULL;
	if (!esVacia()) {
		ult = this->cab; //Iniciando buscar a partir del primer nodo.
		while (ult->getSgte() != NULL)
			ult = ult->getSgte();

	}
	return ult;
}

bool listaSimple::esVacia()
{
	return cab==NULL;
}

void listaSimple::agregarInicio(int x)
{
	nodoS* nuevo = new nodoS(x); //Paso #1 crear el nodo
	if (!esVacia()) 
		nuevo->setSgte(getCab()); //Paso #2 Enlazar el nuevo nodo a la lista
	setCab(nuevo);//Paso #3 Reacomodar la lista con el nuevo nodo
	setLargo(getLargo() + 1);
	
}

void listaSimple::agregarFinal(int x)
{   //Agrega al final de la lista un nodo con el valor de x
	nodoS* nuevo = new nodoS(x); //Paso #1 crear el nodo
	if (esVacia()) {
		setCab(nuevo); //Paso #3 Reacomodar la lista con el nuevo nodo
	}
	else {
		dirUltimo()->setSgte(nuevo);//Paso #3 Reacomodar la lista con el nuevo nodo
	}
	setLargo(getLargo() + 1);
}

bool listaSimple::agregarAntesDe(int _dato, int _ref)
{ //Agregar un nodo con el valor _dato antes de nodo cuyo valor sea _ref
	bool agregado = false;
	if (!esVacia()) {
		if (getCab()->getDato() == _ref) {
			agregarInicio(_dato);
			agregado = true;
		}
		else {
			nodoS* ant = dirAnterior(_ref); //Direcci�n del nodo anterior a _ref.
			if (ant != NULL) { //Encontr� el anterior
				nodoS* aux = ant->getSgte();
				nodoS* nuevo = new nodoS(_dato);//Paso #1. Crear el nodo
				nuevo->setSgte(aux);//Paso #2. Enlazar el nuevo nodo a la lista
				ant->setSgte(nuevo);//Paso #3. Reacomodar la lista con el nuevo nodo.
				setLargo(this->largo + 1);
				agregado = true;
			}
		}
	}

	return agregado;
}
// dato = 1  ref = 6               |        lista = 3, 6
bool listaSimple::agregarDespuesDe(int _dato, int _ref)
{
    bool agregado = false;
	if (!esVacia()) {
			nodoS* desp = dirSiguiente(_ref); //Devuelve el siguiente nodo de la referencia
			if (desp != NULL) { // Comprueba que no es el ultimo
				nodoS* aux = dirNodo(_ref); //aux toma el valor del nodo de la referencia
				nodoS* nuevo = new nodoS(_dato);//Paso #1. Crear el nodo
				nuevo->setSgte(desp);//Paso #2. Enlazar el nuevo nodo a la lista
				aux->setSgte(nuevo);//Paso #3. Reacomodar la lista con el nuevo nodo.
				setLargo(this->largo + 1);
			} else {
				agregarFinal(_dato); //agrega al final si la referencia es el ultimo
			}
			agregado = true;
	}

	return agregado;
}

bool listaSimple::eliminar(int _dato)
{ //Eliminar el primer nodo cuyo valor sea igual a _dato
	bool removido = false;
	if (!esVacia()) {
		nodoS* aux = NULL;
		if (getCab()->getDato() == _dato) {
			//Proceso de remover el primer nodo
			aux = getCab();//Paso #1: Apunte el nodo a eliminar
			//Paso #2: reacomodar la lista sin el nodo
			setCab(aux->getSgte());
			setLargo(getLargo() - 1);
			delete aux; //Paso #3: Eliminar el nodo
			removido = true;
		}
		else {
			nodoS* ant = dirAnterior(_dato);
			if (ant != NULL) {
				aux = ant->getSgte();//Paso #1: Apunte el nodo a eliminar
				ant->setSgte(aux->getSgte());
				setLargo(getLargo() - 1);
				delete aux; //Paso #3: Eliminar el nodo
				removido = true;
			}
		}
	}


	return removido;
}
// 1,3,4,5,3,3,6
void listaSimple::eliminarRepetidos()
{
	if (getLargo() > 1) { //Verifica que la lista tenga al menos 2 valores
		nodoS* aux = getCab(); //Obtiene la cabeza
		while (aux->getSgte() != NULL) //Recorre la lista desde la cabeza hasta la cola
		{
			nodoS* act = aux->getSgte(); //Obtiene el valor con que se va a comparar con el que empieza a recorrer la lista
			nodoS* ant = aux; //Define como anterior el valor que esta antes del valor a comparar
			while (act->getSgte() != NULL) //Recorre el resto de la lista buscando repetidos
			{
				if (aux->getDato() == act->getDato()) { //Verifica si el valor con el que comienza a recorrer la lista en el ciclo padre es igual al valor actual a comparar
					nodoS* borrado = act; //Si son iguales los valores, define como borrado ese valor que esta comparando
					ant->setSgte(act->getSgte()); //Le dice al anterior que su nuevo siguiente es el siguiente del valor a comparar
					act = act->getSgte(); //Define como actual el valor siguiente del valor a comparar
					delete borrado; //Se borra el puntero que apunta al valor repetido
				} else { //En el caso de no encontrar repetidos
					ant = act; //Define como anterior el valor actual
					act = act->getSgte(); //Define como actual el siguiente valor
				}
			}
			aux = aux->getSgte(); //Continua con el siguiente valor de la lista
		}
		
	}
}

void listaSimple::desplegarLista()
{
	if (esVacia())
		std::cout << "La lista est� vac�a...";
	else {
		nodoS* aux = getCab(); //aux apunte al primer nodo de la lista
		while (aux != NULL) { //la lista termina cuando llega a NULL
			std::cout << aux->getDato() << "-";
			aux = aux->getSgte(); //permite pasar al siguiente nodo
		}
		std::cout << "Fin de la lista \n" ;

	}
}

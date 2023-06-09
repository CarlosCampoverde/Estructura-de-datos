/** UNIVERSIDAD DE LAS FUERZAS ARMADAS "ESPE"
*			INGENIERIA SOFTWARE
*@author 
*TEMA: Calculadora Polaca inversa
*FECHA DE CREACION : 
*FECHA DE MODIFICACION: 
*/

#pragma once
#include <iostream>
#include <ctime>
#include <random>
template <class T>
class Nodo
{
private:
	T dato;
	Nodo<T>* siguiente;
public:

	/**
	 * @brief Construct a new Nodo< T> object
	 * 
	 */
	Nodo<T>(T, Nodo*);

	/**
	 * @brief Get the dato object
	 * 
	 * @return T 
	 */
	T get_dato();

	/**
	 * @brief Set the dato object
	 * 
	 */
	void set_dato(T);

	/**
	 * @brief Get the siguiente object
	 * 
	 * @return Nodo<T>* 
	 */
	Nodo<T>* get_siguiente();

	/**
	 * @brief Set the siguiente object
	 * 
	 */
	void set_siguiente(Nodo*);
	
	
	
};
template<class T>
Nodo<T>::Nodo(T val, Nodo* sig)
{
	sig = NULL;
	this->dato = val;
	this->siguiente = sig;
}
template<class T>
T Nodo<T>::get_dato()
{
	try
	{
		return this->dato;
	}
	catch (...)
	{
		std::cout << "Error" << std::endl;
	}
	
}

template<class T>
void Nodo<T>::set_dato(T val)
{
	this->dato = val;
}


template<class T>
Nodo<T>* Nodo<T>::get_siguiente()
{
	return this->siguiente;
}
template<class T>
void Nodo<T>::set_siguiente(Nodo<T>* nuevo)
{
	this->siguiente = nuevo;
}

//#include "Nodo.cpp"

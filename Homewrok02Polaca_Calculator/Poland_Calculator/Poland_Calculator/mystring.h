/** UNIVERSIDAD DE LAS FUERZAS ARMADAS "ESPE"
*			INGENIERIA SOFTWARE
*@author 
*TEMA: Calculadora Polaca inversa
*FECHA DE CREACION : 
*FECHA DE MODIFICACION: 
*/

#pragma once
#include <string>
using namespace std;
class mystring
{
public:
	/**
	 * @brief transformar a minusculas
	 * 
	 * @return char 
	 */
	char to_lower( char);

	/**
	 * @brief transformar a mayusculas
	 * 
	 * @return char 
	 */
	char to_upper(char);

	/**
	 * @brief Capitalizar
	 * 
	 * @return string 
	 */
	string capitalize(string);

	/**
	 * @brief Minusculas
	 * 
	 * @return string 
	 */
	string minusculize(string);

	/**
	 * @brief Buscar por caracter
	 * 
	 * @return int 
	 */
	int find_character(string, char, int);

	/**
	 * @brief Buscar por string
	 * 
	 * @return int 
	 */
	int find(string, string, int);

	/**
	 * @brief obtener tamaño
	 * 
	 * @return int 
	 */
	int length(string);

	/**
	 * @brief extraer en cadena
	 * 
	 * @return string 
	 */
	string substract(string, int, int);

	/**
	 * @brief comparar strings
	 * 
	 * @return true 
	 * @return false 
	 */
	bool is_equal(string, string);

	/**
	 * @brief transformar a int
	 * 
	 * @return int 
	 */
	int atoi(char);

	/**
	 * @brief string a int
	 * 
	 * @return int 
	 */
	int stoi(string);

	/**
	 * @brief long a string
	 * 
	 * @return long 
	 */
	long stol(string);

	/**
	 * @brief string a double
	 * 
	 * @return double 
	 */
	double stod(string);

	/**
	 * @brief revertir string
	 * 
	 * @return string 
	 */
	string reverse(string);

	/**
	 * @brief comprobar si es numero
	 * 
	 * @return true 
	 * @return false 
	 */
	bool is_number(string);

	/**
	 * @brief potencia
	 * 
	 * @param num 
	 * @param pot 
	 * @return double 
	 */
	double potencia(double num, double pot);
};


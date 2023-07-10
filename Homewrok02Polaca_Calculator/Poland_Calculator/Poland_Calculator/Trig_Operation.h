/** UNIVERSIDAD DE LAS FUERZAS ARMADAS "ESPE"
*			INGENIERIA SOFTWARE
*@author 
*TEMA: Calculadora Polaca inversa
*FECHA DE CREACION : 
*FECHA DE MODIFICACION: 
*/


#pragma once

class Trig_Operation
{
public:
	/**
 	* @brief calculate sine with taylor series
 	* 
 	* @return double 
 	*/
	double sin(double);
	
	/**
	 * @brief calculate contangent with taylor series
	 * 
	 * @return double 
	 */
	double cot(double);
	
	/**
	 * @brief calculate cosine with taylor series
	 * 
	 * @return double 
	 */
	double cos(double);
	
	/**
	 * @brief calculate tangent with taylor series
	 * 
	 * @return double 
	 */
	double tan(double);
	
	/**
	 * @brief calculate tangent with taylor series
	 * 
	 * @return double 
	 */
	double sec(double);
	
	/**
	 * @brief calculate factorial with recursive function 
	 * 
	 * @return long 
	 */
	long factorial(int);
	double potencia(double, double);
};


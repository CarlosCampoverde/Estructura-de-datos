/** UNIVERSIDAD DE LAS FUERZAS ARMADAS "ESPE"
*			INGENIERIA SOFTWARE
*@author 
*TEMA: Calculadora Polaca inversa
*FECHA DE CREACION : 
*FECHA DE MODIFICACION: 
*/

#pragma once
#include "mystring.h"
#include "Stack.h"
class Operation
{
public:
	/**
	 * @brief infix a prefix
	 * 
	 * @return string 
	 */
	string infix_to_prefix(string);

	/**
	 * @brief infix a prefix
	 * 
	 * @return Stack<string> 
	 */
	Stack<string> infix_to_prefix1(Stack<string>);

	/**
	 * @brief infix a postfix
	 * 
	 * @return string 
	 */
	string infix_to_postfix(string);

	/**
	 * @brief infix a postfix
	 * 
	 * @return Stack<string> 
	 */
	Stack<string> infix_to_postfix1(Stack<string>);
	
	/**
	 * @brief infix a funcional
	 * 
	 * @return string 
	 */
	string infix_to_funtional(string);
	
	/**
	 * @brief prefix a infix
	 * 
	 * @return string 
	 */
	string prefix_to_infix(string);
	
	/**
	 * @brief prefix a postfix
	 * 
	 * @return string 
	 */
	string prefix_to_postfix(string);
	
	/**
	 * @brief prefix a funcional
	 * 
	 * @return string 
	 */
	string prefix_to_funtional(string);
	
	/**
	 * @brief postfix a infix
	 * 
	 * @return string 
	 */
	string postfix_to_infix(string);
	
	/**
	 * @brief postfix a prefix
	 * 
	 * @return string 
	 */
	string postfix_to_prefix(string);
	
	/**
	 * @brief postfix a funcional
	 * 
	 * @return string 
	 */
	string postfix_to_funtional(string);
	
	/**
	 * @brief comprobar operador
	 * 
	 * @return true 
	 * @return false 
	 */
	bool is_operator(char);
	
	/**
	 * @brief comprobar operador
	 * 
	 * @return true 
	 * @return false 
	 */
	bool is_operator1(string);
	
	/**
	 * @brief comprobar char trigonometrica
	 * 
	 * @return true 
	 * @return false 
	 */
	bool is_trig_fun(char);
	
	/**
	 * @brief comprobar trigonometrica
	 * 
	 * @return true 
	 * @return false 
	 */
	bool is_trig_fun1(string);
	
	/**
	 * @brief comprobar operando
	 * 
	 * @return true 
	 * @return false 
	 */
	bool is_operand(char);
	
	/**
	 * @brief char precedente
	 * 
	 * @return int 
	 */
	int precedence(char);
	
	/**
	 * @brief elemento precedente
	 * 
	 * @return int 
	 */
	int precedence1(string);
	
	/**
	 * @brief calcular
	 * 
	 * @return double 
	 */
	double calculate(Stack<string>);
	
	/**
	 * @brief ingresar datos
	 * 
	 * @return Stack<string> 
	 */
	Stack<string> ingresar_datos();
	Stack<string> ingresar_datos_enteros();
	/**
	 * @brief invertir pila
	 * 
	 * @return Stack<string> 
	 */
	Stack<string> invertir_pila(Stack<string>);

	/**
	 * @brief copiar pila
	 * 
	 * @return Stack<string> 
	 */
	Stack<string> copiar_pila(Stack<string>);
	Stack<string> desencolar_pila_cifrada(Stack<string>,int);
	string cifrar(string, int);
	bool evaluar_expresion(Stack<string>);
	char* ingreso(const char*);
};


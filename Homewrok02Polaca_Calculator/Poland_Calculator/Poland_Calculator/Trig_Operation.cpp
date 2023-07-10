/** UNIVERSIDAD DE LAS FUERZAS ARMADAS "ESPE"
*			INGENIERIA SOFTWARE
*
*
*@author THEO ROSERO
*@author YULLIANA ROMAN
*@author JUNIOR JURADO
*@author ALEX PAGUAY
*@author SANTIAGO SAÑAY
*TEMA: Calculadora Polaca inversa
*FECHA DE CREACION : 3 DE JULIO DE 2021
*FECHA DE MODIFICACION: 6 DE JUNIO 2021
*/

#include "Trig_Operation.h"
#include "Math.h"
#include <iostream>
using namespace std;
double Trig_Operation::sin(double angle )
{
    double x = angle;
    double result,precission;
    result = 0;
    precission = 0;
    int sign=0,final_sign;
    final_sign = 0;
    const double pi = 3.141592654;
    while (x > pi) {
        x = x - pi;
        final_sign = final_sign + 1;
    }
    for (int i = 1; i <= 11; i = i + 2) {
        precission = pow(-1, sign)*(potencia(x,i) / factorial(i));

        result = result + precission;
        sign = sign + 1;
        
    }
    if (final_sign % 2 != 0) {
        result = result * -1;
    }
    return result;
}


double Trig_Operation::cos(double angle)
{
    
    double result = 0; 
    int presicion = 8; 
    const double pi = 3.141592654;
    int cont = 0;
    while (angle > pi) {
        angle = angle - pi;
        cont++;
 
    }
    for (int i = 0; i < presicion; i++)
    {
        result += ((pow(-1, i)) / factorial(2 * i)) * potencia(angle, 2 * i);
    }
    if (cont%2==1) {
       result = result * -1;
    }
    return result;
}

double Trig_Operation::tan(double angle)
{
    double tan;
    tan = Trig_Operation::sin(angle) / Trig_Operation::cos(angle);
    return tan;
}


double Trig_Operation::cot(double angle)
{
    double cot;
    cot = 1 / Trig_Operation::tan(angle);
    return cot;
}

double Trig_Operation::sec(double angle)
{
    double sec;
    sec = 1 / Trig_Operation::sin(angle);
    return sec;
}

long Trig_Operation::factorial(int n)
{
    //Funciona hasta 16! 
    if (n < 1) {
        return 1;
    }
    else {
        return n * factorial(n - 1);
    }
}

double Trig_Operation::potencia(double num, double pot)
{
    double result=1;
    if (pot == 0) {
        return 1;
    }
    if (pot == 1) {
        return num;
    }
    if (pot == 0.5) {
        double raiz = 0;
        while ((num - raiz*raiz) > 0.00001) {
            raiz = raiz + 0.00001;
        }
        
        return raiz;
    }
    for (int i = 0; i < pot; i++) {
        result = result * num;
    }
    return result;
}

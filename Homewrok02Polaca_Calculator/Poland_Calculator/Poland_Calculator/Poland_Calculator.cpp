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

#include <iostream>
#include "Operation.h"
#include "Stack.h"
#include "Utils.h"
#include "mystring.h"
int main()
{
    try
    {
        Operation op;

        mystring str;
       
        Stack<string> datos;
        datos = op.ingresar_datos();
        
        cout << "INFIJA         :   ";
        if (op.evaluar_expresion(datos)) {
            datos.mostrar_expresion();
            Stack<string> prefija;
            Stack<string> postfija;

            prefija = op.infix_to_prefix1(datos);
            cout << "PREFIJA        :   ";
            prefija.mostrar_expresion();

            postfija = op.infix_to_postfix1(datos);
            cout << "POSTFIJA       :   ";
            postfija.mostrar_expresion();
            cout << "RESULTADO      :   ";
            cout << op.calculate(prefija) << endl;
        }
        else {
            cout << "EXPRESION INVALIDA" << endl;
        }
        
    }
    catch (const std::exception&)
    {
        cout << "Error" << endl;

    }
    
    /*Stack<string> datos2;
    string num = "12.36";
    int clave = 0;
    //cout << str.stod(num) << endl;
    Stack<string> datos;
    Stack<string> datos2;
    datos = op.ingresar_datos_enteros();
    cout << "expresion inicial" << endl;
    datos.mostrar_expresion();
    cout << "ingrese la clave" << endl;
    cin >> clave;
    datos2=op.desencolar_pila_cifrada(datos, clave);
    cout << "expresion cifrada" << endl;
    datos2.mostrar_expresion();*/

       
        
        
}


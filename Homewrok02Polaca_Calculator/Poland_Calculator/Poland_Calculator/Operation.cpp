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

#include "Operation.h"
#include "Trig_Operation.h"
#include <Math.h>
#include <iostream>
#include <string>
#include <conio.h>
#include <cstring>
#include "Utils.h"
string Operation::infix_to_prefix(string infix)
{
    Stack<char> stack;
    mystring str;
    string cad = str.reverse(infix);
    string result,prefix;
    string aux;
    char anterior = '.';
    for (char& character : cad) {
        if (character == '(') {
            character = ')';
        }
        else if (character == ')') {
            character = '(';
        }
    }
    infix=cad;
    for (char& character : infix) {
        //if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z')) {
        if ((character >= 'a' && character <= 'z' || character >= '0' && character <= '9')) {
            prefix += character;
        }
        else if (character == '(') {
            stack.insertar_por_la_cabeza(character);
        }
        else if (character == ')') {
            while ((stack.get_primero()->get_dato() != '(') && (!stack.empty_stack())) {
                prefix += stack.get_primero()->get_dato();
                stack.borrar_por_la_cabeza();
            }

            if (stack.get_primero()->get_dato() == '(') {
                stack.borrar_por_la_cabeza();
            }
        }
        
        else if (is_operator(character)) {
            if (stack.empty_stack()) {
                stack.insertar_por_la_cabeza(character);
            }
            else {
                if (precedence(character) > precedence(stack.get_primero()->get_dato())) {
                    stack.insertar_por_la_cabeza(character);
                }
                else if ((precedence(character) == precedence(stack.get_primero()->get_dato()))
                    && (character == '^')) {
                    while ((precedence(character) == precedence(stack.get_primero()->get_dato()))
                        && (character == '^')) {
                        prefix += stack.get_primero()->get_dato();
                        stack.borrar_por_la_cabeza();
                    }
                    stack.insertar_por_la_cabeza(character);
                }
                else if (precedence(character) == precedence(stack.get_primero()->get_dato())) {
                    stack.insertar_por_la_cabeza(character);
                }
                else {
                    while ((!stack.empty_stack()) && (precedence(character) < precedence(stack.get_primero()->get_dato()))) {
                        prefix += stack.get_primero()->get_dato();
                        stack.borrar_por_la_cabeza();
                    }
                    stack.insertar_por_la_cabeza(character);
                }
            }
        }
        //
        else if (is_trig_fun(character) && anterior == ')') {
            prefix += character;
        }
        anterior = character;
    }
   
    while (!stack.empty_stack()) {
        prefix += stack.get_primero()->get_dato();
        stack.borrar_por_la_cabeza();
    }

    reverse(prefix.begin(), prefix.end());
    return prefix;
}
Stack<string> Operation::infix_to_prefix1(Stack<string> infix)
{
   
    mystring str;
    
    Stack<string> cad = copiar_pila(infix);
    string result;
    string aux;
    string anterior = "";
    Nodo<string>* character = cad.get_primero();
    Stack<string> prefix;
    Stack<string> stack;
   while (character) {
        if (character->get_dato() == "(") {
            character->set_dato(")");
        }
        else if (character->get_dato() == ")") {
            character->set_dato("(");
        }
        character = character->get_siguiente();
    }
    character = cad.get_primero();
    string character1="";
    while (character) {
        character1 = character->get_dato();
        if (str.is_number(character1)) {
            prefix.insertar_por_la_cabeza(character1);
        }
        else if (character1 == "(") {
            stack.insertar_por_la_cabeza(character1);
        }
        else if (character1 == ")") {
            while ((stack.get_primero()->get_dato() != "(") && (!stack.empty_stack())) {
                prefix.insertar_por_la_cabeza( stack.get_primero()->get_dato());
                stack.borrar_por_la_cabeza();
            }

            if (stack.get_primero()->get_dato() == "(") {
                stack.borrar_por_la_cabeza();
            }
        }
        else if (is_operator1(character1)) {
           
            if (stack.empty_stack()) {
                stack.insertar_por_la_cabeza(character1);
            }
            else {
                if (precedence1(character1) > precedence1(stack.get_primero()->get_dato())) {
                    stack.insertar_por_la_cabeza(character1);
                }
                else if ((precedence1(character1) == precedence1(stack.get_primero()->get_dato()))
                    && (character1 == "^")) {
                    while ((precedence1(character1) == precedence1(stack.get_primero()->get_dato()))
                        && (character1 == "^")) {
                        prefix.insertar_por_la_cabeza( stack.get_primero()->get_dato());
                        stack.borrar_por_la_cabeza();
                    }
                    stack.insertar_por_la_cabeza(character1);
                }
                else if (precedence1(character1) == precedence1(stack.get_primero()->get_dato())) {
                    stack.insertar_por_la_cabeza(character1);
                }
                else {
                    while ((!stack.empty_stack()) && (precedence1(character1) < precedence1(stack.get_primero()->get_dato()))) {
                        prefix.insertar_por_la_cabeza(stack.get_primero()->get_dato());
                        stack.borrar_por_la_cabeza();
                    }
                    stack.insertar_por_la_cabeza(character1);
                }
            }
        }
       
        else if (is_trig_fun1(character1) && anterior == ")") {
            
            prefix.insertar_por_la_cabeza( character1);
        }
        anterior = character1;
        character = character->get_siguiente();
    }
    while (!stack.empty_stack()) {
        prefix.insertar_por_la_cabeza(stack.get_primero()->get_dato());
        stack.borrar_por_la_cabeza();
    }
    
   
    return prefix;
}
int Operation::precedence(char c)
{
    if (c == '^')
        return 3;
    else if (c == '%' )
        return 2;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

int Operation::precedence1(string c)
{
    if (c == "^")
        return 3;
    else if (c == "%")
        return 2;
    else if (c == "*" || c == "/")
        return 2;
    else if (c == "+" || c == "-")
        return 1;
    else
        return -1;
}

double Operation::calculate(Stack<string> prefix)
{
    if (prefix.empty_stack()) {
        return 0;
    }
    try
    {
        Trig_Operation trig;
        mystring str;
        Stack<string> cad = invertir_pila(prefix);
        //string result, prefix;
        string aux, aux2;
        string charac = "";
        char anterior = '.';
        Stack<string> stack;
        Nodo<string>* character = cad.get_primero();
        string character1 = "";
        while (character) {
            character1 = character->get_dato();
            if (str.is_number(character1)) {


                stack.insertar_por_la_cabeza(character1);


            }
            else if (character1 == "+") {
                aux = stack.get_primero()->get_dato();
                stack.borrar_por_la_cabeza();
                aux2 = stack.get_primero()->get_dato();
                stack.borrar_por_la_cabeza();
                stack.insertar_por_la_cabeza(to_string(str.stod(aux) + str.stod(aux2)));

            }
            else if (character1 == "-") {
                aux = stack.get_primero()->get_dato();
                stack.borrar_por_la_cabeza();
                aux2 = stack.get_primero()->get_dato();
                stack.borrar_por_la_cabeza();
                stack.insertar_por_la_cabeza(to_string(str.stod(aux) - str.stod(aux2)));

            }
            else if (character1 == "*") {
                aux = stack.get_primero()->get_dato();
                stack.borrar_por_la_cabeza();
                aux2 = stack.get_primero()->get_dato();
                stack.borrar_por_la_cabeza();
                stack.insertar_por_la_cabeza(to_string(str.stod(aux) * str.stod(aux2)));

            }
            else if (character1 == "/") {
                aux = stack.get_primero()->get_dato();
                stack.borrar_por_la_cabeza();
                aux2 = stack.get_primero()->get_dato();
                stack.borrar_por_la_cabeza();
                stack.insertar_por_la_cabeza(to_string(str.stod(aux) / str.stod(aux2)));

            }
            else if (character1 == "%") {
                aux = stack.get_primero()->get_dato();
                stack.borrar_por_la_cabeza();
                aux2 = stack.get_primero()->get_dato();
                stack.borrar_por_la_cabeza();
                stack.insertar_por_la_cabeza(to_string(int(str.stod(aux)) % int(str.stod(aux2))));

            }
            else if (character1 == "^") {
                aux = stack.get_primero()->get_dato();
                stack.borrar_por_la_cabeza();
                aux2 = stack.get_primero()->get_dato();
                stack.borrar_por_la_cabeza();
                stack.insertar_por_la_cabeza(to_string(trig.potencia(str.stod(aux), str.stod(aux2))));

            }
            else if (character1 == "sen") {
                aux = stack.get_primero()->get_dato();
                stack.borrar_por_la_cabeza();

                stack.insertar_por_la_cabeza(to_string(trig.sin(str.stod(aux))));

            }
            else if (character1 == "cos") {
                aux = stack.get_primero()->get_dato();
                stack.borrar_por_la_cabeza();

                stack.insertar_por_la_cabeza(to_string(trig.cos(str.stod(aux))));

            }
            else if (character1 == "tan") {
                aux = stack.get_primero()->get_dato();
                stack.borrar_por_la_cabeza();

                stack.insertar_por_la_cabeza(to_string(trig.tan(str.stod(aux))));

            }

            character = character->get_siguiente();

        }
        return stod(stack.get_primero()->get_dato());
    }
    catch (...)
    {
        cout << "excepcion" << endl;

    }
    
}

Stack<string> Operation::ingresar_datos()
{
    Stack<string> datos;
    Stack<string> datos1;
    Stack<string> datos2;
    mystring str;
    string dato="";
    while (dato != "=") {
        system("cls");
        cout << "       CALCULADORA POLACA "<< endl;
        cout << "_______________________________________" << endl;
        datos.mostrar_expresion_invertida();
        cout << "_______________________________________" << endl;
        cout << "|   +   -   *   /   %   sen cos tan (   )  |" << endl;
        cout << "|   1          2           3               |" << endl;
        cout << "|   4          5           6               |" << endl;
        cout << "|   7          8           9               |" << endl;
        cout << "|   0          .                           |" << endl;
        cout << "--------------------------------------------" << endl;
        cout << "   ingrese un numero u operador : " ;
        cin >> dato;
        if (!datos.empty_stack()) {
            if (str.is_number(dato) && datos.get_primero()->get_dato() == ")" ) {
                datos.insertar_por_la_cabeza("*");
            }
            if (is_trig_fun1(dato) && str.is_number(datos.get_primero()->get_dato()) ) {
                datos.insertar_por_la_cabeza("*");
            }
            if (is_trig_fun1(dato) && datos.get_primero()->get_dato() == ")") {
                datos.insertar_por_la_cabeza("*");
            }
            if (dato=="(" && datos.get_primero()->get_dato() == ")") {
                datos.insertar_por_la_cabeza("*");
            }
            if (dato == "(" && str.is_number(datos.get_primero()->get_dato())) {
                datos.insertar_por_la_cabeza("*");
            }
        }
        if (str.is_number(dato)) {
            datos.insertar_por_la_cabeza(dato);
        }
        else {
            if (dato == "=" || dato == "sen" || dato == "cos" || dato == "tan" || dato == "+" || dato == "-" || dato == "/" || dato == "*" || dato == "(" || dato == ")" || dato == "%" || dato == "^") {
                datos.insertar_por_la_cabeza(dato);
            }
            else{ 
                cout << "Ingrese datos validos" << endl;
                system("pause");
            }
        }
        //datos.insertar_por_la_cabeza(dato);
        
        
    }
    cout << "_______________________________________" << endl;


    datos.borrar_por_la_cabeza();
    if (datos.empty_stack()) {
        return datos;
    }
    return invertir_pila(datos);
}

Stack<string> Operation::ingresar_datos_enteros()
{
    string dato="99";
    Stack<string> datos;
    mystring str;
    int num = 0;
    char datos2[11];
    while (dato != "999" ) {
      
        
       
        strcpy_s(datos2, ingreso("ingrese un numero a la pila "));
        //cout << datos2 << endl;
        dato=datos2 ;
        
        cout << endl;
        //cin >> dato;
        if (dato != "999" && str.stoi(dato) > 9) {
            datos.insertar_por_la_cabeza(dato);
            
        }
        
       
    }
    return datos;

}

Stack<string> Operation::invertir_pila(Stack<string> datos)
{
    Nodo<string> *dato = datos.get_primero();
    Stack<string> datos1;
    string aux;
    while (!datos.StackVacia()) {
        aux = datos.get_primero()->get_dato();
        datos.borrar_por_la_cabeza();
        datos1.insertar_por_la_cabeza(aux);
    }
    free(datos.get_primero());
    return datos1;
}

Stack<string> Operation::copiar_pila(Stack<string> datos)
{
    Nodo<string>* dato = datos.get_primero();
    Stack<string> datos1;
    string aux;
    while (dato) {
        aux = dato->get_dato();
        datos1.insertar_por_la_cabeza(aux);
        dato = dato->get_siguiente();
        
    }
    return datos1;
}

Stack<string> Operation::desencolar_pila_cifrada(Stack<string> datos, int clave)
{
    Nodo<string>* dato = datos.get_primero();
    Stack<string> datos1;
    string aux;
    string aux2;
    while (dato) {
        
        aux = dato->get_dato();
        aux2 = cifrar(aux, clave);
        datos1.insertar_por_la_cabeza(aux2);
        dato = dato->get_siguiente();

    }
    return datos1;
}

string Operation::cifrar(string dato, int clave)
{
    mystring str;
    string data;
    
   
    data = to_string(clave);
    
    if (str.find(dato, data, 0) == -1) {
        return dato;
    }
    else {
        int aux = str.stoi(dato);
       
        int sum = 0;
        for (int i = 0; i < str.length(dato); i++) {
            sum = sum + aux % 10;
            
            aux = aux / 10;
        }
        
        dato = to_string(sum);
        
        return cifrar(dato, clave);

    }
    
}

bool Operation::evaluar_expresion(Stack<string> datos1)
{
    
    Stack<string> datos = copiar_pila(datos1);
    Nodo<string>* dato = datos.get_primero();
    if (datos.empty_stack()) {
        return true;
    }
    
    string aux;
    string anterior;
    string cabeza;
    mystring str;
    bool result = false;
    int cont_paren_abi = 0;
    int cont_paren_cerr= 0;
   /* while (dato) {
        aux = dato->get_dato();
        datos1.insertar_por_la_cabeza(aux);
        dato = dato->get_siguiente();

    }*/
    if (dato->get_dato() == "(") {
        cout << "aqui 13" << endl;
        return false;
    }
    if (dato->get_dato() == ")") {
        cont_paren_cerr++;
    }
    anterior = dato->get_dato();
    if (!is_trig_fun1(anterior)) {
        if (!str.is_number(anterior)) {
            if (!is_operator1(anterior)) {
                if (anterior != "(") {
                    if (anterior != ")") {
                        cout << "termino no valido" << endl;
                        return false;
                    }
                }
            }
        }

    }
    datos.borrar_por_la_cabeza();
    int cont_data = 0;
    while (!datos.empty_stack()) {
        aux = datos.get_primero()->get_dato();
        if (aux == "(") {
            if (is_operator1(anterior)) {
                cout << "Expresion Invalida" << endl;
                return false;
            }
            if (anterior == ")") {
                cout << "Expresion Invalida" << endl;
                return false;
            }
            cont_paren_abi++;

        }
        if (aux == ")") {
            cont_paren_cerr++;
            
            /*if (is_operator1(anterior)) {
                cout << "aqui 3" << endl;
                return false;
            }*/
            
        }

        if (is_operator1(aux)) {
            if (is_operator1(anterior)) {
                cout << "Expresion Invalida" << endl;
                return false;
            }
            
            if (anterior == ")") {
                cout << "Expresion Invalida" << endl;
                return false;
            }
            
            

        }
        if (str.is_number(aux)) {
            if (str.is_number(anterior)) {
                cout << "Expresion Invalida" << endl;
                return false;
            }
            if (is_trig_fun1(anterior)) {
                cout << "Expresion Invalida" << endl;
                return false;
            }


        }
        if (is_trig_fun1(aux)) {
            if (str.is_number(anterior)) {
                cout << "Expresion Invalida" << endl;
                return false;
            }
            if (is_trig_fun1(anterior)) {
                cout << "Expresion Invalida" << endl;
                return false;
            }
        }
        if (!is_trig_fun1(aux)) {
            if (!str.is_number(aux)) {
                if (!is_operator1(aux)) {
                    if (aux != "(") {
                        if (aux != ")") {
                            cout << "Expresion Invalida" << endl;
                            return false;
                        }
                    }
                }
           }
            
        }
       
        anterior = aux;
        datos.borrar_por_la_cabeza();
        cont_data++;

        
    }
    
    if (is_operator1(anterior)) {
        cout << "Expresion Invalida" << endl;
        return false;
    }
    if (is_trig_fun1(anterior)&&cont_data==0) {
        cout << "Expresion Invalida" << endl;
        return false;
    }
    if (anterior == ")") {
        cout << "Expresion Invalida" << endl;
        return false;
    }
    if (cont_paren_abi != cont_paren_cerr) {
        cout << "faltan parentesis" << endl;
        return false;
    }
   
    return true;
}

char* Operation::ingreso(const char* msj) {
    char dato[10];
    char c;
    int i = 0;
    printf("%s", msj);
    cout << endl;
    while ((c = _getch()) != 13) {
        if (c >= '0' && c <= '9') {
            printf("%c", c);
            dato[i++] = c;
        }
    }
    dato[i] = '\0';
    return dato;
}
string Operation::infix_to_postfix(string infix)
{
    Stack<char> stack;
    mystring str;
    string cad = infix;
    string result, postfix;
    string aux;
    char anterior = '.';
    for (char& character : infix) {
        if ((character >= 'a' && character <= 'z' || character >= '0' && character <= '9')) {
            postfix += character;
        }
        else if (character == '(') {
            stack.insertar_por_la_cabeza(character);
        }
        else if (character == ')') {
            while ((stack.get_primero()->get_dato() != '(') && (!stack.empty_stack())) {
                postfix += stack.get_primero()->get_dato();
                stack.borrar_por_la_cabeza();
            }
            if (stack.get_primero()->get_dato() == '(') {
                stack.borrar_por_la_cabeza();
            }
        }
        else if (is_operator(character)) {
            if (stack.empty_stack()) {
                stack.insertar_por_la_cabeza(character);
            }
            else {
                if (precedence(character) > precedence(stack.get_primero()->get_dato())) {
                    stack.insertar_por_la_cabeza(character);
                }
                else if ((precedence(character) == precedence(stack.get_primero()->get_dato()))
                    ) {
                    while ((precedence(character) == precedence(stack.get_primero()->get_dato()))
                        ) {
                        postfix += stack.get_primero()->get_dato();
                        stack.borrar_por_la_cabeza();
                    }
                    stack.insertar_por_la_cabeza(character);
                }
                else if (precedence(character) == precedence(stack.get_primero()->get_dato())) {
                    stack.insertar_por_la_cabeza(character);
                }
                else {
                    while ((!stack.empty_stack()) && (precedence(character) < precedence(stack.get_primero()->get_dato()))) {
                        postfix += stack.get_primero()->get_dato();
                        stack.borrar_por_la_cabeza();
                    }
                    stack.insertar_por_la_cabeza(character);
                }
            }
        }
        if (is_trig_fun(anterior) && character == '(') {
            stack.insertar_por_la_cabeza(anterior);
        }
        anterior = character;

    }

    while (!stack.empty_stack()) {
       
        postfix += stack.get_primero()->get_dato();
        stack.borrar_por_la_cabeza();
    }
    return postfix;
}

Stack<string> Operation::infix_to_postfix1(Stack<string> infix)
{

    mystring str;

    Stack<string> cad = copiar_pila(infix);
    cad.insertar_por_la_cabeza(")");
    cad=invertir_pila(cad);
    cad.insertar_por_la_cabeza("(");
   
    
    string result;
    string aux;
    string anterior = "";
    Nodo<string>* character = cad.get_primero();
    
    Stack<string> postfix;
    Stack<string> stack;
    string character1 = "";
    while (character) {
        character1 = character->get_dato();
        if (str.is_number(character1)) {
            postfix.insertar_por_la_cabeza(character1) ;
        }
        else if (character1 == "(") {
            stack.insertar_por_la_cabeza(character1);
        }
        else if (character1 == ")") {
            while ((stack.get_primero()->get_dato() != "(") && (!stack.empty_stack())) {
                postfix.insertar_por_la_cabeza( stack.get_primero()->get_dato());
                stack.borrar_por_la_cabeza();
            }
            if (stack.get_primero()->get_dato() == "(") {
                stack.borrar_por_la_cabeza();
            }
        }
        else if (is_operator1(character1)) {
            
            if (stack.empty_stack()) {
                stack.insertar_por_la_cabeza(character1);
                //stack.mostrar_expresion();
            }
            else {
                if (precedence1(character1) > precedence1(stack.get_primero()->get_dato())) {
                    stack.insertar_por_la_cabeza(character1);
                }
                else if ((precedence1(character1) == precedence1(stack.get_primero()->get_dato()))
                    ) {
                    
                   
                   
                    while ((precedence1(character1) == precedence1(stack.get_primero()->get_dato()))
                        ) {
                       
                        //stack.mostrar_expresion();
                        postfix.insertar_por_la_cabeza(stack.get_primero()->get_dato());
                        stack.borrar_por_la_cabeza();
                    }
                    stack.insertar_por_la_cabeza(character1);
                }
                else if (precedence1(character1) == precedence1(stack.get_primero()->get_dato())) {
                    stack.insertar_por_la_cabeza(character1);
                }
                else {
                    while ((!stack.empty_stack()) && (precedence1(character1) < precedence1(stack.get_primero()->get_dato()))) {
                        postfix.insertar_por_la_cabeza(stack.get_primero()->get_dato());
                        stack.borrar_por_la_cabeza();
                    }
                    stack.insertar_por_la_cabeza(character1);
                }
            }
        }
        if (is_trig_fun1(anterior) && character1 == "(") {
            stack.insertar_por_la_cabeza(anterior);
        }




        anterior = character1;
        character = character->get_siguiente();

    }
    while (!stack.empty_stack()) {
        
        postfix.insertar_por_la_cabeza( stack.get_primero()->get_dato());
        stack.borrar_por_la_cabeza();
    }
    postfix = invertir_pila(postfix);

    return postfix;
}

string Operation::infix_to_funtional(string)
{
    return string();
}

string Operation::prefix_to_infix(string prefix)
{
   
    return string();
}

string Operation::prefix_to_postfix(string)
{
    return string();
}

string Operation::prefix_to_funtional(string prefix)
{
    mystring str;
    string cad = str.reverse(prefix);
    //string result, prefix;
    string aux, aux2;
    string charac = "";
    char anterior = '.';
    Stack<string> stack;

    for (char& character : cad) {
        if (is_operand(character)) {

            charac.push_back(character);
            stack.insertar_por_la_cabeza(charac);
            charac = "";
        }
        else if (character == '+') {
            aux = stack.get_primero()->get_dato();
            stack.borrar_por_la_cabeza();
            aux2 = stack.get_primero()->get_dato();
            stack.borrar_por_la_cabeza();
            stack.insertar_por_la_cabeza("SUMA("+aux + "," + aux2+")");

        }
        else if (character == '-') {
            aux = stack.get_primero()->get_dato();
            stack.borrar_por_la_cabeza();
            aux2 = stack.get_primero()->get_dato();
            stack.borrar_por_la_cabeza();
            stack.insertar_por_la_cabeza("RESTA(" + aux + "," + aux2 + ")");

        }
        else if (character == '*') {
            aux = stack.get_primero()->get_dato();
            stack.borrar_por_la_cabeza();
            aux2 = stack.get_primero()->get_dato();
            stack.borrar_por_la_cabeza();
            stack.insertar_por_la_cabeza("MULTIPLICACION(" + aux + "," + aux2 + ")");

        }
        else if (character == '/') {
            aux = stack.get_primero()->get_dato();
            stack.borrar_por_la_cabeza();
            aux2 = stack.get_primero()->get_dato();
            stack.borrar_por_la_cabeza();
            stack.insertar_por_la_cabeza("DIVISION(" + aux + "," + aux2 + ")");

        }
        else if (character == '%') {
            aux = stack.get_primero()->get_dato();
            stack.borrar_por_la_cabeza();
            aux2 = stack.get_primero()->get_dato();
            stack.borrar_por_la_cabeza();
            stack.insertar_por_la_cabeza("MODULO(" + aux + "," + aux2 + ")");

        }
        else if (character == '^') {
            aux = stack.get_primero()->get_dato();
            stack.borrar_por_la_cabeza();
            aux2 = stack.get_primero()->get_dato();
            stack.borrar_por_la_cabeza();
            stack.insertar_por_la_cabeza("POTENCIA(" + aux + "," + aux2 + ")");

        }
        else if (character=='T') {
            aux = stack.get_primero()->get_dato();
            stack.borrar_por_la_cabeza();
            stack.insertar_por_la_cabeza("TANGENTE(" + aux + ")");
        }
        else if (character == 'S') {
            aux = stack.get_primero()->get_dato();
            stack.borrar_por_la_cabeza();
            stack.insertar_por_la_cabeza("SENO(" + aux + ")");
        }
        else if (character == 'C') {
            aux = stack.get_primero()->get_dato();
            stack.borrar_por_la_cabeza();
            stack.insertar_por_la_cabeza("COSENO(" + aux + ")");
        }

    }
    return stack.get_primero()->get_dato();
    return string();
}

string Operation::postfix_to_infix(string)
{
    return string();
}

string Operation::postfix_to_prefix(string postfix)
{
    mystring str;
    string cad = postfix;
    string aux, aux2;
    string charac = "";
    char anterior = '.';
    Stack<string> stack;

    for (char& character : cad) {
        if (is_operand(character)) {

            charac.push_back(character);
            stack.insertar_por_la_cabeza(charac);
            charac = "";
        }
        else if (is_operand(character )) {
            aux = stack.get_primero()->get_dato();
            stack.borrar_por_la_cabeza();
            aux2 = stack.get_primero()->get_dato();
            stack.borrar_por_la_cabeza();
            charac.push_back(character);
            stack.insertar_por_la_cabeza(charac+aux + aux2);
            charac = "";
        } 
        else if (is_trig_fun(character)) {
            aux = stack.get_primero()->get_dato();
            stack.borrar_por_la_cabeza();
            charac.push_back(character);
            stack.insertar_por_la_cabeza(charac + aux);
            charac = "";
        }

    }
    return stack.get_primero()->get_dato();
}

string Operation::postfix_to_funtional(string)
{
    return string();
}

bool Operation::is_operator(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^') {
        return true;
   }
    return false;
}

bool Operation::is_operator1(string c)
{
    if (c == "+" || c == "-" || c == "*" || c == "/" || c == "%" || c == "^") {
        return true;
    }
    return false;
}

bool Operation::is_trig_fun(char c)
{
    if (c == 'S' || c == 'C' || c == 'T' ) {
        return true;
    }
    return false;
}

bool Operation::is_trig_fun1(string c)
{
    if (c == "sen" || c == "cos" || c == "tan") {
        return true;
    }
    return false;
}

bool Operation::is_operand(char c)
{
    if (c >= 'a' && c <= 'z' || c >= '0' && c <= '9') {
        return true;
    }
    return false;
}

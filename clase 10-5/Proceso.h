/***********************************************************************
 * Module:  Proceso.h
 * Author:  Fernando
 * Modified: miércoles, 10 de mayo de 2023 8:20:15
 * Purpose: Declaration of the class Proceso
 ***********************************************************************/

#if !defined(__Class_Diagram_1_Proceso_h)
#define __Class_Diagram_1_Proceso_h

#include <Fraccion.h>

class Proceso
{
public:
   virtual Fraccion calculo(Fraccion obj1, Fraccion ojb2)=0;
   virtual float calculo(float obj1, float obj2)=0;

protected:
private:

};

#endif
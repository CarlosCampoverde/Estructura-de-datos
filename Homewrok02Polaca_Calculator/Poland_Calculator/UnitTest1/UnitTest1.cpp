#include "pch.h"
#include "CppUnitTest.h"
#include "..//Poland_Calculator/Operation.h"
#include "..//Poland_Calculator/Operation.cpp"
#include "..//Poland_Calculator/Stack.h"
#include "..//Poland_Calculator/Stack.cpp"
#include "..//Poland_Calculator/List.h"
#include "..//Poland_Calculator/List.cpp"
#include "..//Poland_Calculator/Utils.h"
#include "..//Poland_Calculator/Utils.cpp"
#include "..//Poland_Calculator/mystring.h"
#include "..//Poland_Calculator/mystring.cpp"
#include "..//Poland_Calculator/Trig_Operation.h"
#include "..//Poland_Calculator/Trig_Operation.cpp"
#include <math.h>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(Operation1)
	{
	public:

		TEST_METHOD(Calculate1)
		{
			Operation op;
			Stack<string> prefix;
			prefix.insertar_por_la_cola("^");
			prefix.insertar_por_la_cola("-");
			prefix.insertar_por_la_cola("20");
			prefix.insertar_por_la_cola("10");
			prefix.insertar_por_la_cola("*");
			prefix.insertar_por_la_cola("4");
			prefix.insertar_por_la_cola("6");
			double result = pow((20 - 10), (4 * 6));
			Assert::AreEqual(result, op.calculate(prefix));
		}
		TEST_METHOD(Calculate2)
		{
			Operation op;
			Stack<string> prefix;
			prefix.insertar_por_la_cola("/");
			prefix.insertar_por_la_cola("*");
			prefix.insertar_por_la_cola("tan");
			prefix.insertar_por_la_cola("+");
			prefix.insertar_por_la_cola("4");
			prefix.insertar_por_la_cola("20");
			prefix.insertar_por_la_cola("6");
			prefix.insertar_por_la_cola("10");
			double result = tan(4 + 20) * 6 / 10;
			Assert::AreEqual(result, op.calculate(prefix));
		}
		TEST_METHOD(Calculate3)
		{
			Operation op;
			Stack<string> prefix;
			prefix.insertar_por_la_cola("-");
			prefix.insertar_por_la_cola("+");
			prefix.insertar_por_la_cola("20");
			prefix.insertar_por_la_cola("*");
			prefix.insertar_por_la_cola("4");
			prefix.insertar_por_la_cola("/");
			prefix.insertar_por_la_cola("20");
			prefix.insertar_por_la_cola("10");
			prefix.insertar_por_la_cola("sen");
			prefix.insertar_por_la_cola("7");
			double result = 20 + 4 * (20 / 10) - sin(7);
			Assert::AreEqual(result, op.calculate(prefix));
		}
		TEST_METHOD(Calculate4)
		{
			Operation op;
			Stack<string> prefix;
			prefix.insertar_por_la_cola("/");
			prefix.insertar_por_la_cola("*");
			prefix.insertar_por_la_cola("2");
			prefix.insertar_por_la_cola("6");
			prefix.insertar_por_la_cola("+");
			prefix.insertar_por_la_cola("5");
			prefix.insertar_por_la_cola("11");
			prefix.insertar_por_la_cola("^");
			prefix.insertar_por_la_cola("8");
			prefix.insertar_por_la_cola("9");
			double result = (2 + 6) / ((5 + 11) * (8 ^ 9));
			Assert::AreEqual(result, op.calculate(prefix));
		}
	};
}

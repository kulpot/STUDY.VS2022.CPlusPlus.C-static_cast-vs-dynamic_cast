#include <iostream>
#include <ctime>	//ref:C++ dynamic_cast
//#include <typeinfo>		//ref:C++ typeid()
//#include <time.h>		//ref C++ typeid() // srand(time(0)); -> every random type has to start with a number
//#include <cstdlib> //ref:C++ static_cast	//c standard library - ex. sqaure root(sqrt)
using std::cout;
using std::endl;

//----------------------- C++ dynamic_cast -------------------------------------------------------------
//ref link:https://www.youtube.com/watch?v=tRyLVEUSJkM&list=PLRwVmtr-pp05motkiTlDIuU5ZfoRr-kWC&index=4

//Dynamic_cast - is another RTTI(RunTimeTypeIdentification) checking
//Static_cast - compile time type checking

//class Base {};		// no polymorphism
class Base	// with polymorphism
{
	virtual void f() {};
};
class Derived1 : public Base {};
class Derived2 : public Base {};

void main()
{
	srand(time(0));
	Base* b =
		(rand() % 2 == 0) ? 
		static_cast<Base*>(new Derived1) 
		: new Derived2;
	//####RTTI################
	Derived1* d1 = dynamic_cast<Derived1*>(b);	//<----- dynamic_casting return null(or0) if Derived2
	//if(d1 != NULL) // explicit same as if(d1 != 0)
	if(d1)			// C++ trick that converts a pointer to boolean type
	//if (typeid(*b) == typeid(Derived1))
	{
		cout << "Derived1" << endl;
	}
	Derived2* d2 = dynamic_cast<Derived2*>(b);	//<----- dynamic_casting return null(or0) if Derived1
	if(d2)
	//else if (typeid(*b) == typeid(Derived2))
	{
		cout << "Derived2" << endl;
	}
}






























//----------------------- C++ typeid() -------------------------------------------------------------
//ref link:https://www.youtube.com/watch?v=TFwW36dLoHY&list=PLRwVmtr-pp05motkiTlDIuU5ZfoRr-kWC&index=7

//typeid - one of runtime type identification constructs requires polymorphism(vTable)
//typeid - can be useful in debugging tool if you have a compileTimeType pointer of basetype pointed to a derived so you get the runtime type out
//the compiler creates one typeinfo instance per type(static instance per every type in the program)

//typeid Stores information about a type. It allows you to compare types of objects(==,!=), get their hash code or get their name
// In this sample the.name() fct is used.
/*
Base b = new Derived1;
typeid(b).name() => Base. If there are no virtual function(so no virtual table in the base object)
typeid(b).name() => Derived1. If there exists a virtual function(the vTable will point to the derived object)

Typeid return a constant typeinfo reference(&)
const tipeinfo& t = typeid(Base);
*/



////class Base {};		// no polymorphism
//class Base	// with polymorphism
//{
//	virtual void f() {};
//};
//class Derived1 : public Base {};
//class Derived2 : public Base {};
//
//void main()
//{
//	//Base* b =										new Derived2;  // determined by runtime
//	//####random boolean#### return static_cast<Base*>#######
//	srand(time(0));					//seedrandom
//	Base* b =
//		(rand() % 2 == 0) ? static_cast<Base*>(new Derived1) : new Derived2;
//	if (typeid(*b) == typeid(Derived1))
//	{
//		//van static casting
//		cout << "Derived1" << endl;
//	}
//	else if (typeid(*b) == typeid(Derived2))
//	{
//		cout << "Derived2" << endl;
//	}
//
//	//const type_info& t = typeid(Base);
//	//cout << t.name() << endl;
//
//	//Base* b = new Derived1;
//	//cout << typeid(*b).name() << endl;	//*b - redereference
//
//	//cout << typeid(Base).name() << endl;
//	//cout << typeid(Derived1).name() << endl;
//}
































//------------------------ C++ static_cast ---------------------------------------------------------
//ref link:https://www.youtube.com/watch?v=M4y5KnnlDhE&list=PLRwVmtr-pp05motkiTlDIuU5ZfoRr-kWC&index=3

//static cast - (static means compile time) , not recommended in pointers
//static_cast doesnot have a runtime cost, it will just do it
//dynamic cast should be recommended in casting hierarchies, and pointers

//void main()
//{// casting explicitly with the type 
//	int i = 25;
//	//sqrt(i);	// 11 years ago this was an ERROR - i is an overloaded func, it can be long/float/double
//	sqrt(static_cast<double>(i)); // this expression: it takes as int returns into a double then sqrt of the double version will be invoke
//	// d1
//	double d = sqrt(static_cast<double>(i));
//	cout << d << endl;		// result: sqrt of 25 is 5
//}
//
////##########################################
////class Base {};
////class Derived1 : public Base {};
////class Derived2 : public Base {};
////
////void main()
////{
////	Base* b =																		new Derived1;	// static - Compile time but in runtime it will show
////	//Derived1* d1 = b;	//error: b cant be recognize because its in static(compile time) requires static_cast
////	Derived1* d1 = static_cast<Derived1*>(b); 
////	// d1
////	Derived2* d1 = static_cast<Derived2*>(b); //<---- error: Undefined 
////	// d1	<---- error: Undefined 
////}
































// --------------------------- C++ reinterpret_cast -----------------------------------------------------
//ref link:https://www.youtube.com/watch?v=wcKXGvi1JRk&list=PLRwVmtr-pp05motkiTlDIuU5ZfoRr-kWC&index=2&t=7s

//reinterpret cast allows you to cast a pointer type into another type
//reinterpret casting - does not change the address while changing the value type of a RAM in compile time
//one thing to point out is reinterpret cast should be used keeping in mind the packing done by the compiler and if you don't want to check the packing, then just use pragma pack 1(compiler optimization won't be applied and there would be no packing)

//struct Cow		//struct defaults to public
//{
//	int mooCount;
//	int legCount;
//	char gender;
//	bool isButchered;
//};
//
//int main()
//{
//	Cow cow;		// cow contains 2x int, char, bool, packing(compiler)
//	cow.mooCount = 8; cow.legCount = 5;
//	cow.gender = 'f'; cow.isButchered = true;
//	Cow* cowPtr = &cow;		//cow pointer - address
//	//cout << cowPtr->gender;		// -> dereference
//	int* intPtr = reinterpret_cast<int*>(cowPtr);		// reinterpret_cast
//	//cout << cowPtr << endl; cout << intPtr << endl;		// Result:same address as intPtr cause of reinterpret_casting
//	//cout << intPtr << endl;	//Result: 8 <- the first value of struct Cow
//	//############################
//	//intPtr++;		//PointerArithmetic-SameAs: intPtr = intPtr + 1;
//	//intPtr = intPtr + 1;	
//	//cout << intPtr << endl;		//result: address + int size value
//	//############################
//	//cout << *intPtr << endl;	//points to mooCount value
//	//intPtr++;
//	//cout << *intPtr << endl;	// *intPtr points to legCount cause of intPtr++
//	//############################
//	intPtr += 2;
//	cout << *intPtr << endl;	// points to gender(int value)
//	cout << *reinterpret_cast<char*>(intPtr) << endl;	// points to gender(char value) and the value char is not save to char point value
//	char* charPtr = reinterpret_cast<char*>(intPtr);
//	//cout << *charPtr << endl;	// stored in charPtr value
//	charPtr++;			// *charPtr pointer move to 4 bytes
//	cout << *charPtr << endl;	// charPtr points to isButchered(charr value)
//	cout << *reinterpret_cast<bool*>(charPtr) << endl;	// charPtr points to isButchered(bool value)
//	cout << true << endl; // prove bool result of isButchered bool value
//}
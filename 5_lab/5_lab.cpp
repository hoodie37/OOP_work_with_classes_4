
#include "pch.h"
#include <iostream>
#include <conio.h>
#include <cmath>
#include <string>
using namespace std;



class ExampleBase {

public:
	ExampleBase() { printf("ExampleBase: constructed\n"); }
	void Override() { printf("ExampleBase: overrided method\n"); }
	virtual void New() { printf("ExampleBase: \n"); }
	virtual ~ExampleBase() { printf("~ExampleBase: destroyed \n"); }

	void Method1() {
		printf("Base:Method 1\n");
		Method2();
	}

	virtual void Method2() {
		printf("Base:Method 2\n");
	}

	virtual string classname() { return " "; }
	virtual bool isA(string s) { return " "; }

};

class ExampleDesc1 : public ExampleBase {

public:
	ExampleDesc1() { printf("ExampleDesc1: constructed\n"); }
	void Override() { printf("ExampleDesc1: overrided method\n"); }
	void ExD1() { printf("ExampleDesc1: method\n"); }
	virtual void New() { printf("ExampleDesc1: new method\n"); }
	virtual ~ExampleDesc1() { printf("ExampleDesc1: destroyed\n"); }

	void Method2() {
		printf("Desc:Method 2\n");
	}

	string classname() { return "ExampleDesc1"; }
	virtual bool isA(string s) { return (s == "ExampleDesc1" || s == "ExampleBase"); }
};


class Animal {

public:
	virtual void sound() {}
	virtual bool isA(string s) { return true; }
	virtual string classname() { return ""; }
	virtual ~Animal() {}
};


class Cat : public Animal {

public:
	Cat() { printf("Cat created\n"); }

	virtual void sound() {
		printf("Meow\n");
	}

	string classname() {
		return "Cat";
	}

	void _catch() {
		printf("Cat Cathcing\n");
	}

	bool isA(string s) {
		return (s == "Cat" || s == "Animal");
	}

	~Cat() { printf("Cat destructed"); }
};

class Dog : public Animal {

public:
	Dog() { printf("Dog created\n"); }

	virtual void sound() {
		printf("Bark\n");
	}

	string classname() {
		return "Dog";
	}

	void chase() {
		printf("Dog Chasing\n");
	}

	bool isA(string s) {
		return (s == "Dog" || s == "Animal");
	}

	~Dog() { printf("Dog destructed"); }
};


class Tiger : public Cat {

public:
	Tiger() { printf("Tiger created\n"); }
	virtual void sound() {
		printf("Rrrrr\n");
	}
	string classname() {
		return "Tiger";
	}
	void _catch() {
		printf("Tiger Cathcing\n");
	}
	bool isA(string s) {
		return (s == "Tiger" || s == "Cat");
	}
	~Tiger() { printf("Tiger destructed"); }
};



class BasePoint {

public:
	int x, y;
public:
	BasePoint() {
		this->x = 1;
		this->y = 1;
		printf("Base Default\n");
	}
	BasePoint(BasePoint* obj) {
		this->x = obj->x;
		this->y = obj->y;
		printf("Base*\n");
	}
	BasePoint(BasePoint& obj) {
		this->x = obj.x;
		this->y = obj.y;
		printf("Base&\n");
	}
	virtual ~BasePoint() {
		printf("~BasePoint x: %d - y: %d\n", this->x, this->y);
	}
};

class DescPoint3D : public BasePoint {

public:
	int z;
public:
	DescPoint3D() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
		printf("Desc Default\n");
	}
	DescPoint3D(DescPoint3D* obj) {
		this->x = obj->x;
		this->y = obj->y;
		this->z = obj->z;
		printf("Desc*\n");
	}
	DescPoint3D(DescPoint3D& obj) {
		this->x = obj.x;
		this->y = obj.y;
		this->z = obj.z;
		printf("Desc&\n");
	}
	virtual ~DescPoint3D() {
		printf("DescPoint3D x: %d - y: %d\n", this->x, this->y);
	}
};

void func1(BasePoint obj) {
	printf("Func1 Default x: %d - y: %d\n", obj.x + 3, obj.y + 3);
};

void func2(BasePoint* obj) {
	printf("Func2 * x: %d - y: %d\n", obj->x + 4, obj->y + 4);
};

void func3(const BasePoint& obj) {
	printf("Func3 & x: %d - y: %d\n", obj.x + 5, obj.y + 5);
};

int main()
{

	/////////////////Methods///////////////

	ExampleBase *n1 = new ExampleBase;
	printf("\n");
	ExampleBase* n2 = new ExampleDesc1;
	printf("\n");
	ExampleDesc1* n3 = new ExampleDesc1;
	printf("\n");

	n1->New();
	printf("\n");
	n2->New();
	printf("\n");
	n3->New();
	printf("\n");

	n1->Override();
	n2->Override();
	n3->Override();
	printf("\n");

	n3->Method1();

	delete n1;
	delete n2;
	delete n3;


	/////////////CAST//////////////

	Animal* storage[10];

	// Добавляем объекты
	for (int i = 0; i < 10; i++)
		if (rand() % 3 == 0)
			storage[i] = new Cat;
		else if (rand() % 3 == 1)
			storage[i] = new Dog;
		else storage[i] = new Tiger;
	printf("\n");
	//Небезопасное приведение типов
	printf("Not safe \n");
	for (int i = 0; i < 10; i++) {
		((Dog*)storage[i])->chase();
	}
	printf("\n safe trought classname()\n");
	//безопасное приведение типов через classname()
	for (int i = 0; i < 10; i++) {
		if (storage[i]->classname() == "Dog")
			((Dog*)storage[i])->chase();
	}
	printf("\n safe trought isA\n");
	//безопасное приведение типов через isA
	for (int i = 0; i < 10; i++) {
		if (storage[i]->isA("Cat"))
			((Cat*)storage[i])->_catch();
	}
	printf("\n safe trought dynamic_cast \n");
	//безопасное приведение типов с помощью dynamic_cast
	for (int i = 0; i < 10; i++) {
		if (Tiger* c = dynamic_cast<Tiger*>(storage[i]))
			c->_catch();
	}
	printf("\n");


	///////////////FUNCS/////////////////


	/*printf("Base:\n");
	{
		BasePoint p1;
		printf("\n");
		BasePoint p2(p1);
		printf("\n");
		BasePoint p3(&p1);
		printf("\n");

		printf("\nDesc:\n");
		DescPoint3D p4;
		printf("\n");
		DescPoint3D p5(p4);
		printf("\n");
		DescPoint3D p6(&p4);
		printf("\n");

		printf("Base() and Desc()\n");

		printf("1:\n");
		func1(p1);

		printf("2:\n");
		func1(p4);

		printf("func2\n");
		func2(&p1);
		func2(&p4);

		printf("func3\n");
		func3(p1);
		func3(p4);

		printf("\n");
		printf("Base(&) and Desc(&)\n");
		printf("func1\n");
		func1(p2);
		func1(p5);

		printf("func2\n");
		func2(&p2);
		func2(&p5);

		printf("func3\n");
		func3(p2);
		func3(p5);

		printf("\n");
		printf("Base(*) and Desc(*)\n");
		printf("func1\n");
		func1(p3);
		func1(p6);

		printf("func2\n");
		func2(&p3);
		func2(&p6);

		printf("func3\n");
		func3(p3);
		func3(p6);



		printf("\n");
	}*/


}


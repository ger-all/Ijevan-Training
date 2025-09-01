#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Cat;
class Dog;

// === Abstract classes === Visitor, Animal
class IVisitor {
public:
	virtual void visit(Cat* ob) = 0;
	virtual void visit(Dog* ob) = 0;
};

class Animal {
public:
	virtual void accept(IVisitor* visitor) = 0;

	Animal(string name) : m_name(name) {}
	virtual void makeNoise() { cout << "Animal noise" << endl; }
	virtual string getName() { return m_name; }

private:
	string m_name;
};

// === Derived classes === Cat, Dog, YellowVisitor, BlueVisitor
class Cat : public Animal {
public:
	Cat(string name) : Animal(name) {}

	void makeNoise() override {
		cout << "meow" << endl;
	}

	void accept(IVisitor* visitor) override {
		visitor->visit(this);
	}
};

class Dog : public Animal {
public:
	Dog(string name) : Animal(name) {}

	void makeNoise() override {
		cout << "woof" << endl;
	}

	void accept(IVisitor* visitor) override {
		visitor->visit(this);
	}
};

class YellowVisitor : public IVisitor {
public:
	void visit(Cat* ob) {
		cout << "\033[33m" << ob->getName() << ": ";
		ob->makeNoise();
		cout << "\033[0m";
	}
	void visit(Dog* ob) {
		cout << "\033[33m" << ob->getName() << ": ";
		ob->makeNoise();
		cout << "\033[0m";
	}
};

class BlueVisitor : public IVisitor {
public:
	void visit(Cat* ob) {
		cout << "\033[34m" << ob->getName() << ": ";
		ob->makeNoise();
		cout << "\033[0m";
	}
	void visit(Dog* ob) {
		cout << "\033[34m" << ob->getName() << ": ";
		ob->makeNoise();
		cout << "\033[0m";
	}
};

// === main ===
int main() {
	vector<Animal*> vecAnimals;

	Animal* pDog = new Dog("Laika");
	Animal* pCat = new Cat("Tom");
	Animal* pDog2 = new Dog("Belka");
	Animal* pDog3 = new Dog("Strelka");

	vecAnimals.push_back(pDog);
	vecAnimals.push_back(pCat);
	vecAnimals.push_back(pDog2);
	vecAnimals.push_back(pDog3);

	IVisitor* visitor = new YellowVisitor();
	for (Animal* item : vecAnimals) {
		item->accept(visitor);
	}
	
	cout << "=========" << endl;

	IVisitor* visitor2 = new BlueVisitor();
	for (Animal* item : vecAnimals) {
		item->accept(visitor2);
	}

	// cleanup
	delete visitor;
	delete visitor2;
	for (auto item : vecAnimals)
		delete item;

	return 0;
}


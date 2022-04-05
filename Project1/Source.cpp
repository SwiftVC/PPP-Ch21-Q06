/*
*	Author:	CS
*	Date:	2022_03_17	YYYY_MM_DD
*
*	Implementing a set of pointers, instead of raw data objects, requires a different comparison with dereferencing
*	as well as extra dereferencing required by the user to access the pointed to value.
*/

#include <iostream>
#include <set>
#include <string>

struct Fruit {
	std::string name;
	int count;
	double unit_price;
	//Date last_sale_date;
	// . . .
	Fruit(std::string n, int number, double price_per_unit) : name{ n }, count{ number }, unit_price{ price_per_unit } {}
	Fruit(std::string n, int number) : name{ n }, count{ number }, unit_price{ -1 } {}
};
struct Fruit_order {
	bool operator()(const Fruit& a, const Fruit& b) const
	{
		return a.name < b.name;
	}
};

struct Fruit_order_2 {
	bool operator()(const Fruit* a, const Fruit* b) const
	{
		return a->name < b->name;
	}
};

std::ostream& operator<<(std::ostream& out, Fruit fr) {
	out << fr.name;
	return out;
}


int main() {
	std::set<Fruit, Fruit_order> inventory; // use Fruit_order(x, y) to compare Fruits
	std::cout << "Textbook example using std::set<Fruit, Fruit_order>:\n";
	inventory.insert(Fruit("quince", 5));
	inventory.insert(Fruit("apple", 200, 0.37));
	for (auto p = inventory.begin(); p != inventory.end(); ++p)
		std::cout << *p << '\n';
	for (const auto& x : inventory)
		std::cout << x << '\n';

	std::cout << std::endl;

	std::set<Fruit*, Fruit_order_2> inventory_2; // use Fruit_order(x, y) to compare Fruits
	std::cout << "Question answer example using std::set<Fruit*, Fruit_order_2>:\n";
	Fruit* first = new Fruit("quince", 5);
	Fruit* second = new Fruit("apple", 200, 0.37);
	inventory_2.insert(first);
	inventory_2.insert(second);
	for (auto p = inventory_2.begin(); p != inventory_2.end(); ++p)
		std::cout << **p << '\n';
	for (const auto& x : inventory_2)
		std::cout << *x << '\n';

	delete first;
	delete second;
	inventory_2.clear();

	return 0;
}
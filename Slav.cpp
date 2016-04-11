#include "Slav.h"
#include <fstream>

using namespace std;

vector <string> Slav::names;
int Slav::_counter = 0;

void Slav::init()
{
	srand(time(NULL));
	ifstream file("names.dat");
	copy(istream_iterator<string>(file),
		istream_iterator<string>(),
		back_inserter(names));
	file.close();
}

Slav::Slav()
{
	static int amountOfNames = (init(), names.size()); /* Jest to lazy initialization (leniwa inicjalizacja).
	Korzystamy tu z tego, że dzięki operatorowi przecinka
	niejako "oszukujemy" kompilator - wykonujemy dwie instrukcje,
	a jako wartość amountOfNames zostanie przypisany tylko wynik tej
	ostatniej*/
	_name = names[rand() % amountOfNames];
	_id = _counter++;
}

string Slav::description()
{
	return string("  ") + _name + " [" + to_string(_id) + "]";
}

sex Slav::checkSex()
	{
		if (_name[_name.length()-1]=='a')
			return female;
		else
			return male;
	}
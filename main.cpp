// Kontenery
#include <vector>	// Tablica
#include <set>		// Zbiór
#include <map>		// Słownik

// Adaptery
#include <queue>	// Kolejka
#include <stack>	// Stos

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>

#include "Slav.h"

#define REPORT_ADAPTERS showMeAdapterSizes(queueOfSlavs,stackOfSlavs)
#define REPORT_CONTAINERS showMeContainerSizes(vectorOfSlavs,setOfSlavs,mapOfSlavs)

using namespace std;

void showMeContainerSizes(vector <Slav *>, set <Slav *>, map <Slav *, Slav*>);
void showMeAdapterSizes(queue <Slav *>, stack <Slav *>);

void containers(Slav *, int);
void adapters(Slav *, int);
void displaySex(Slav*, int, sex);

int main(int argc, char const *argv[])
{
	int n = 2 * atoi(argv[1]);
	Slav *slavs = new Slav[n];
	cout << "# Generated Slavs" << endl;
	for (int i = 0; i < n; ++i)
		cout << slavs[i].description() << endl;

	containers(slavs, n);
	adapters(slavs, n);
	displaySex(slavs, n, male);
	displaySex(slavs, n, female);

	delete [] slavs;
}

void containers(Slav * slavs, int n)
{
	vector <Slav *> vectorOfSlavs;
	set <Slav *> setOfSlavs;
	map <Slav *, Slav *> mapOfSlavs;
	
	srand(time(NULL));

	printf("# Containers\n");
	REPORT_CONTAINERS;
	printf("## vector\n");
	vectorOfSlavs.push_back(NULL);
	
	for (int i=0; i<n; i++)
		vectorOfSlavs.insert(vectorOfSlavs.begin() + i, slavs+i);
	vectorOfSlavs.pop_back();
	random_shuffle(vectorOfSlavs.begin(), vectorOfSlavs.end());
	for (std::vector<Slav *>::iterator it = vectorOfSlavs.begin(); it != vectorOfSlavs.end(); it++)
		cout << (*it)->description();

	REPORT_CONTAINERS;
	printf("## set\n");

	for(int i=0;i<n;i++)
			setOfSlavs.insert(vectorOfSlavs[i]);
	
	REPORT_CONTAINERS;
	printf("## map\n");

	// Stwórz słownik tworzący pary Słowian, z tych znajdujących się w zbiorze, czyszcząc zbiór

	for(set<Slav*>::iterator it = setOfSlavs.begin(); !setOfSlavs.empty();)
	{
		mapOfSlavs.insert(pair<Slav *, Slav*>(*(it = setOfSlavs.erase(it)), *it));
		it = setOfSlavs.erase(it);
	}
	
	for (std::map<Slav *, Slav *>::iterator it = mapOfSlavs.begin(); it != mapOfSlavs.end(); it++)
		cout << (*it).first->description() << (*it).second->description() << "\n";
	
	REPORT_CONTAINERS;
}

void adapters(Slav * slavs, int n)
{
	queue <Slav *> queueOfSlavs;
	stack <Slav *> stackOfSlavs;

	printf("# Adapters\n");
	REPORT_ADAPTERS;
	printf("## queue\n");

	for (int i=0; i<n; i++)
		queueOfSlavs.push(slavs+i);
	
	REPORT_ADAPTERS;

	printf("## stack\n");
	// Przenieś Słowian z kolejki do stosu.
	for (int i=0; i<n; i++)
		stackOfSlavs.push(queueOfSlavs.front()+i);

	REPORT_ADAPTERS;

	// Wyświetl Słowian zdejmowanych ze stosu.
	while (!stackOfSlavs.empty())
	{
		cout << (stackOfSlavs.top())->description();
		stackOfSlavs.pop();
	}

	REPORT_ADAPTERS;
}

void displaySex(Slav * slavs, int n, sex s)
{
	map <sex, vector<Slav*>> mapOfSex;

	for(int i=0; i<n; i++)
	{
		if(slavs[i].checkSex() == male)
			mapOfSex[male].push_back(&slavs[i]);
		else
			mapOfSex[female].push_back(&slavs[i]);
	}

	if (s == male) 
		printf("## men\n");
	else 
		printf("## women\n");
	for(vector<Slav *>::iterator it = mapOfSex[s].begin() ; it != mapOfSex[s].end() ; it++)
	{
		cout << (*it)->description() << endl;
	}
}

void showMeContainerSizes(vector <Slav *> vector, set <Slav *> set, map <Slav *, Slav*> map)
{
	printf("[vector_size = %lu, set_size = %lu, map_size = %lu, existingSlavs = %i]\n",
		vector.size(),
		set.size(),
		map.size(),
		Slav::counter());
}

void showMeAdapterSizes(queue <Slav *> queue, stack <Slav *> stack)
{
	printf("[queue_size = %lu, stack_size = %lu, existingSlavs = %i]\n",
		queue.size(),
		stack.size(),
		Slav::counter());
}

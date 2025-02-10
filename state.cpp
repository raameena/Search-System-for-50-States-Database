#include "state.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

State::State(string a, string n, string c, int pop, int y, int numc) // creates object with all attributes
{
	stateAbrv = a;
	stateName = n;
	capital = c;
	population = pop;
	year = y;
	numCongress = numc;
}
void State::setStateAbrv(string a) // setter methods
{
	stateAbrv = a;
}
void State::setStateName(string n)
{
	stateName = n;
}
void State::setCapital(string c)
{
}
void State::setPopulation(int pop)
{
	population = pop;
}
void State::setYear(int y)
{
	year = y;
}
void State::setNumCongress(int numc)
{
	numCongress = numc;
}
string State::getStateAbrv() // getter methods
{
	return stateAbrv;
}
string State::getStateName()
{
	return stateName;
}
string State::getCapital()
{
	return capital;
}
int State::getPopulation()
{
	return population;
}
int State::getYear()
{
	return year;
}
int State::getNumCongress()
{
	return numCongress;
}
int State::computeResidentsPerRep() // computes residents per rep , returns integer
{
	int resPerRep;
	resPerRep = population / numCongress;
	return resPerRep;
}
void State::displayStateInfo() // displays state's info
{
	cout << endl;
	cout << right << setw(20) << stateAbrv << setw(20) << stateName
		<< setw(20) << capital << setw(20) << population << setw(11)
		<< year << setw(15) << numCongress << endl;
	cout << endl;
}
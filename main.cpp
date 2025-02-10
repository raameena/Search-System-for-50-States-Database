/* Author: Raameen Ahmed
Creation Date: 12/05/2024
Last Modification Date: 12/06/2024
Purpose: Lab 11 Question 1 ~ The purpose of this program is to filter and sort a
database consisting of the 50 states'
abbreviation, name, capital, population, year, and number of represenitives in
congress. By using a temporary object,
the program is able to retrieve attributes of the states from each line of the
file, read them into a string ( and
convert back to an integer if need be ), and place them into a vector which stores
all of the data from the database.
In doing so, the program is able to create a search system by comparing the user's
input to items in the vector, and
displays the information of the selected state using a displayStateInfo class, if
the selected state exists. The program
also consists of an option to display all of the sorted information for the user
and a class which computes the amount of
citizens per represenitive of each state.
*/
#include "state.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;
void displayTableHeader(); // prototypes
void readStateInfo(ifstream&, vector<State>&);
void displayMenu();
int searchByAbrv(vector <State>&, string);
void searchByStatehood(vector <State>&, int, int&);

int main()
{
	vector <State> stateVec;
	ifstream ifs;
	int userChoice = 0, stYear, index = -1, stateIndex, totalIndex = 50; //initializing variables
	string abrev;


	ifs.open("usstates_lab11.txt");

	if (!ifs.is_open()) // if file does not open correctly, error message will appear
	{
		cerr << "Error encountered while opening file : usstates_lab11" << endl;
		system("pause");
		return 0;
	}

	readStateInfo(ifs, stateVec); // begin with reading info from file

	displayMenu(); // display menu for user
	cin >> userChoice;

	while (userChoice != 4)
	{
		if (userChoice == 4) // end program if user enters 4
		{
			ifs.close();
			system("pause");
			return 0;
		}
		else if (userChoice == 1) // search by state if user enters 1
		{
			cout << "Please enter the state abbreviation: ";
			cin >> abrev;
			cout << endl;
			index = searchByAbrv(stateVec, abrev); // returns the index of the state if found, -1 otherwise
			if (index == -1)
			{
				cout << "No state exists with this information." << endl;
			}
			else
			{
				displayTableHeader();
				stateVec[index].displayStateInfo(); // displays state's info
				cout << endl << endl;
			}
			displayMenu(); // displays menu for user to choose another option
			cin >> userChoice;
			cout << endl;
		}
		else if (userChoice == 2) // search by year if user enters 2
		{
			cout << "Please enter the year of statehood: ";
			cin >> stYear;
			searchByStatehood(stateVec, stYear, stateIndex); // runs search with state info vector, the chosen year, and state index
			if (stateIndex == -1) // state index remains -1 if no states were found
			{
				cout << endl << "No state exists with this information." <<
					endl;
			}
			cout << endl << endl;
			displayMenu(); // displays menu and asks user to choose again
			cin >> userChoice;
		}
		else if (userChoice == 3) // display all information if user enters 3
		{
			displayTableHeader();

			for (int i = 0; i < totalIndex; i++) // loop runs 50 times for all 50 states
			{
				stateVec[i].displayStateInfo(); // displays 50 times, one time for each state
			}
			cout << endl << endl;
			displayMenu(); // displays menu and asks user to choose again
			cin >> userChoice;
		}
	}
	ifs.close();
	system("break"); // end program
	return 0;
}
void displayTableHeader() // displays header
{
	cout << endl;
	cout << right << setw(20) << "State Abr." << setw(20) << "Name" << setw(20)
		<< "Capital" << setw(20) << "Population" << setw(11) << "Year"
		<< setw(15) << "#Congress" << endl;
	cout << endl;
}
void readStateInfo(ifstream& ifs, vector<State>& stateVec) // reads all info from file, puts it into vector
{
	string abrv, name, capital, Spop, Syear, SnumCon;
	int pop = 0, year = 0, numCon = 0;

	while (!ifs.eof())
	{
		getline(ifs, abrv, ','); // 1. get line puts file info into strings
		getline(ifs, name, ',');
		getline(ifs, capital, ',');
		getline(ifs, Spop, ',');

		istringstream iss(Spop); // 2. strings of file info get stored in istringstream(if original info was int)

		iss >> pop; // 3. stringstream converts string into integer(back to original type)

		getline(ifs, Syear, ',');
		istringstream iss2(Syear);
		iss2 >> year;
		getline(ifs, SnumCon);
		istringstream iss3(SnumCon);
		iss3 >> numCon;

		State tmpState(abrv, name, capital, pop, year, numCon); // each line info gets stored into temporary object

		tmpState.setStateAbrv(abrv); // stores attributes from each line of file into temp object
		tmpState.setStateName(name);
		tmpState.setCapital(capital);
		tmpState.setPopulation(pop);
		tmpState.setYear(year);
		tmpState.setNumCongress(numCon);
		stateVec.push_back(tmpState); // pushes temp object to vector, creating vector that stores all info from file
	}
}
void displayMenu() // displays menu for user
{
	cout << "Welcome back to your database! Please select an option below:" << endl;
	cout << "1. Search by state abbreviation (e.g. MI)." << endl;
	cout << "2. Search by year of statehood (e.g. 1837)." << endl;
	cout << "3. Browse all information of states (State Abrv., Name, Capital, Population, Year, and #Congress)" << endl;
	cout << "4. Exit program." << endl << endl;
	cout << "Please enter your choice (1-4): ";
}

int searchByAbrv(vector <State>& stateVec, string abrev) // search using state abrev., returns index if found, -1 otherwise
{
	int index = -1; // default -1

	for (int i = 0; i < stateVec.size(); i++)
	{
		if (stateVec[i].getStateAbrv() == abrev)
		{
			index = i; // if found place i into index and return index
			return index;
		}
	}
	if (index == -1) // if index remains unchanged, return index
	{
		return index;
	}
}

void searchByStatehood(vector <State>& stateVec, int year, int& startIndex) // search using state year, returns every state with given year
{
	startIndex = -1; // default -1

	for (int i = 0; i < stateVec.size(); i++)
	{
		if (stateVec[i].getYear() == year)
		{
			startIndex++;
			if (startIndex == 0)
			{
				displayTableHeader(); // display header only if at least 1 state with qualifying info exists
			}
			stateVec[i].displayStateInfo(); // display state
		}
	}
}
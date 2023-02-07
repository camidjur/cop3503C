#include <iostream>
#include <map>
#include <random>
#include <ctime>
#include <fstream>
#include <sstream>
using namespace std;

mt19937 random_mt;

int Random(int min, int max)
{
	uniform_int_distribution<int> dist(min, max);
	return dist(random_mt);
}

void RollDice(int numberOfRolls, int numberOfSides) {
	map <int, int> DiceRolls;
	int result;

	// initializing the map
	for (int i = 1; i < numberOfSides + 1; i++) {
		DiceRolls.emplace(i, 0);
	}

	// rolling the dice the desired times 
	for (int j = 0; j < numberOfRolls; j++) {
		result = Random(1, numberOfSides);
		DiceRolls[result] += 1;
	}
	// printing out the info
	for (int x = 1; x < numberOfSides + 1; x++) {
		cout << x << ": " << DiceRolls[x] << endl;
	}

}

int main()
{
	class States {
	private:
		string name;
		int income;
		int popu;
		int hhIncome;
		int numHH;

	public:
		States() {
			name = "";
			income = 0;
			popu = 0;
			hhIncome = 0;
			numHH = 0;
		}
		States(string name, int income, int popu, int hhIncome, int numHH) {
			this->name = name;
			this->income = income;
			this->popu = popu;
			this->hhIncome = hhIncome;
			this->numHH = numHH;
		}
		void Print() {
			cout << this->name << endl;
			cout << "Population: " << this->popu << endl;
			cout << "Per Capita Income: " << this->income << endl;
			cout << "Median Household Income: " << this->hhIncome << endl;
			cout << "Number of Households: " << this->numHH << endl;
		}
	};


	cout << "1. Random Numbers" << endl;
	cout << "2. State Info" << endl;

	int option;
	cin >> option;

	if (option == 1)
	{
		int randomSeed;
		cout << "Random seed value: ";
		cin >> randomSeed;
		random_mt.seed(randomSeed);

		int numOfRolls;
		cout << "Number of times to roll the die: ";
		cin >> numOfRolls;

		int sidesOfDie;
		cout << "Number of sides on this die: ";
		cin >> sidesOfDie;

		RollDice(numOfRolls, sidesOfDie);
	}
	else if (option == 2)
	{
		// Load the states
		string name;
		int income;
		int population;
		int hhIncome;
		int numHH;
		string temp;

		map<string, States> states;

		ifstream inFile("states.csv");
		if (inFile.is_open()) {
			string linesInFile;
			getline(inFile, linesInFile);

			while (getline(inFile, linesInFile)) {
				istringstream anotherStream(linesInFile);

				getline(anotherStream, name, ',');

				getline(anotherStream, temp, ',');
				income = stoi(temp);

				temp = "";
				getline(anotherStream, temp, ',');
				population = stoi(temp);

				temp = "";
				getline(anotherStream, temp, ',');
				hhIncome = stoi(temp);

				temp = "";
				getline(anotherStream, temp, ',');
				numHH = stoi(temp);

				States s(name, income, population, hhIncome, numHH);
				states.emplace(name, s);
			}
		}
		inFile.close();

		// Get input for option 1 (show all states) or 2 (do a search for a particular state)
		int choice; 

		cout << "1. Print all states" << endl;
		cout << "2. Search for a state" << endl;

		cin >> choice;
		map<string, States>::iterator iter;

		if (choice == 1) {
			for (iter = states.begin(); iter != states.end(); iter++) {
				iter->second.Print();
			}
		}
		else if (choice == 2) {
			string searchingS;
			cin >> searchingS;

			iter = states.find(searchingS);

			if (iter != states.end()) {
				iter->second.Print();
			}
			else {
				cout << "No match found for " + searchingS << endl;
			}
		}



	}

	return 0;
}

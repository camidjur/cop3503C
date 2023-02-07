#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "Lego.h"
using namespace std;

void ReadInFiles(string file, vector<Lego>& legoInfo) {
	string tempSetNum;
	string tempTheme;
	string tempName;
	unsigned int tempMinifigNum;
	unsigned int tempPiecesNums;
	double tempPrice;

	ifstream inFile(file);
	if (inFile.is_open()) {
		string linesInFile;
		getline(inFile, linesInFile);

		while (getline(inFile, linesInFile)) {
			//getline(inFile, linesInFile);
			istringstream anotherStream(linesInFile);

			getline(anotherStream, tempSetNum, ',');
			
			getline(anotherStream, tempTheme, ',');
			
			getline(anotherStream, tempName, ',');
	
			string temp;
			getline(anotherStream, temp, ',');
			tempMinifigNum = stoi(temp);

			temp = "";
			getline(anotherStream, temp, ',');
			tempPiecesNums = stoi(temp);

			temp = "";
			getline(anotherStream, temp, ',');
			tempPrice = stod(temp);

			Lego l(tempSetNum, tempTheme, tempName, tempMinifigNum, tempPiecesNums, tempPrice);
			legoInfo.push_back(l);
		}
	}
}
void MostExpensive(vector<Lego>& legoInfo) {
	double mostExpensivePrice = 0;
	unsigned int num;
	for (unsigned int i = 0; i < legoInfo.size(); i++) {
		if (legoInfo[i].GetPrice() > mostExpensivePrice) {
			mostExpensivePrice = legoInfo[i].GetPrice();
			num = i;
		}
	}
	
	cout << "The most expensive set is:" << endl;
	cout << "Name: " << legoInfo[num].GetName() << endl;
	cout << "Number: " << legoInfo[num].GetSetNum() << endl;
	cout << "Theme: " << legoInfo[num].GetTheme() << endl;
	cout << "Price: $" << legoInfo[num].GetPrice() << endl;
	cout << "Minifigures: " << legoInfo[num].GetMinifigs() << endl;
	cout << "Piece count: " << legoInfo[num].GetPieces() << endl;
	
}
void LargestPieceCount(vector<Lego>& legoInfo) {
	unsigned int greatestLegoPieces = 0;
	unsigned int num;
	for (unsigned int i = 0; i < legoInfo.size(); i++) {
		if (legoInfo[i].GetPieces() > greatestLegoPieces) {
			greatestLegoPieces = legoInfo[i].GetPieces();
			num = i;
		}
	}
	cout << "The set with the highest parts count:" << endl;
	cout << "Name: " << legoInfo[num].GetName() << endl;
	cout << "Number: " << legoInfo[num].GetSetNum() << endl;
	cout << "Theme: " << legoInfo[num].GetTheme() << endl;
	cout << "Price: $" << legoInfo[num].GetPrice() << endl;
	cout << "Minifigures: " << legoInfo[num].GetMinifigs() << endl;
	cout << "Piece count: " << legoInfo[num].GetPieces() << endl;
}
void SetNamesContaining(string userInput, vector<Lego>& legoInfo) {
	int count = 0;
	vector <Lego> temp;
	for (unsigned int i = 0; i < legoInfo.size(); i++) {
		if (legoInfo[i].GetName().find(userInput) != string::npos) {
			temp.push_back(legoInfo[i]);
			count++;
		}
	}
	if (count == 0) {
		cout << "No sets found matching that search term" << endl;
	}
	else {
		cout << "Sets matching \" " << userInput << "\": " << endl;
		for (unsigned int i = 0; i < temp.size(); i++) {
			cout << temp[i].GetSetNum() << " ";
			cout << temp[i].GetName() << " $";
			cout << temp[i].GetPrice() << endl;
		}
	}
}
void SetThemes(string userInput, vector<Lego>& legoInfo) {
	int count = 0;
	vector <Lego> temp;
	for (unsigned int i = 0; i < legoInfo.size(); i++) {
		if (legoInfo[i].GetTheme().find(userInput) != string::npos) {
			temp.push_back(legoInfo[i]);
			count++;
		}
	}
	if (count == 0) {
		cout << "No sets found matching that search term" << endl;
	}
	else {
		cout << "Sets matching \" " << userInput << "\": " << endl;
		for (unsigned int i = 0; i < temp.size(); i++) {
			cout << temp[i].GetSetNum() << " ";
			cout << temp[i].GetName() << " $";
			cout << temp[i].GetPrice() << endl;
		}
	}
}
void AveragePartCount(vector<Lego>& legoInfo) {
	unsigned int totalPartCount = 0;
	for (unsigned int i = 0; i < legoInfo.size(); i++) {
		totalPartCount += legoInfo[i].GetPieces();
	}
	cout << "Average part count for " << legoInfo.size() << " sets: ";
	cout << (totalPartCount / legoInfo.size()) << endl;
}
void PriceInformation(vector<Lego>& legoInfo) {
	double totalPrice = 0.0;
	double minimumPrice = legoInfo[0].GetPrice();
	double maximumPrice = legoInfo[0].GetPrice();
	unsigned int num1;
	unsigned int num2;

	for (unsigned int i = 0; i < legoInfo.size(); i++) {
		totalPrice += legoInfo[i].GetPrice();
		if (legoInfo[i].GetPrice() > maximumPrice) {
			maximumPrice = legoInfo[i].GetPrice();
			num1 = i;
		}
		if (legoInfo[i].GetPrice() < minimumPrice) {
			minimumPrice = legoInfo[i].GetPrice();
			num2 = i;
		}
	}
	cout << "Average price for " << legoInfo.size() << " sets: ";
	cout << "$" << (totalPrice / legoInfo.size()) << endl;
	
	cout << "Least expensive set: " << endl;
	cout << "Name: " << legoInfo[num2].GetName() << endl;
	cout << "Number: " << legoInfo[num2].GetSetNum() << endl;
	cout << "Theme: " << legoInfo[num2].GetTheme() << endl;
	cout << "Price: $" << legoInfo[num2].GetPrice() << endl;
	cout << "Minifigures: " << legoInfo[num2].GetMinifigs() << endl;
	cout << "Piece count: " << legoInfo[num2].GetPieces() << endl;
	
	
	cout << "Most expensive set: " << endl;
	cout << "Name: " << legoInfo[num1].GetName() << endl;
	cout << "Number: " << legoInfo[num1].GetSetNum() << endl;
	cout << "Theme: " << legoInfo[num1].GetTheme() << endl;
	cout << "Price: $" << legoInfo[num1].GetPrice() << endl;
	cout << "Minifigures: " << legoInfo[num1].GetMinifigs() << endl;
	cout << "Piece count: " << legoInfo[num1].GetPieces() << endl;
}
void MinifigureInformation(vector<Lego>& legoInfo) {
	unsigned int totalMinifigs = 0;
	unsigned int maximumMinifigs = legoInfo[0].GetMinifigs();
	unsigned int num;

	for (unsigned int i = 0; i < legoInfo.size(); i++) {
		totalMinifigs += legoInfo[i].GetMinifigs();
		if (legoInfo[i].GetMinifigs() > maximumMinifigs) {
			maximumMinifigs = legoInfo[i].GetMinifigs();
			num = i;
		}
	}
	cout << "Average number of minifigures: ";
	cout << (totalMinifigs / legoInfo.size()) << endl;

	cout << "Set with the most minifigures: " << endl;
	cout << "Name: " << legoInfo[num].GetName() << endl;
	cout << "Number: " << legoInfo[num].GetSetNum() << endl;
	cout << "Theme: " << legoInfo[num].GetTheme() << endl;
	cout << "Price: $" << legoInfo[num].GetPrice() << endl;
	cout << "Minifigures: " << legoInfo[num].GetMinifigs() << endl;
	cout << "Piece count: " << legoInfo[num].GetPieces() << endl;
}
void OneOfEverything(vector<Lego>& legoInfo) {
	double totalPrice = 0.0;
	unsigned int totalPieces = 0;
	unsigned int totalMinifigures = 0;
	for (unsigned int i = 0; i < legoInfo.size(); i++) {
		totalPrice += legoInfo[i].GetPrice();
		totalPieces += legoInfo[i].GetPieces();
		totalMinifigures += legoInfo[i].GetMinifigs();
	}
	cout << "If you bought one of everything..." << endl;
	cout << "It would cost: $" << totalPrice << endl;
	cout << "You would have " << totalPieces << " pieces in your collection" << endl;
	cout << "You would have an army of " << totalMinifigures << " minifigures!" << endl;

}

int main()
{
	vector<Lego> lego1;
	vector<Lego> lego2;
	vector<Lego> lego3;
	vector<Lego> bigVector;

	cout << std::fixed << setprecision(2);
	cout << "Which file(s) to open?\n";
	cout << "1. lego1.csv" << endl;
	cout << "2. lego2.csv" << endl;
	cout << "3. lego3.csv" << endl;
	cout << "4. All 3 files" << endl;
	int option;
	cin >> option;

	/*======= Load data from file(s) =======*/
	if (option == 1) {
		ReadInFiles("lego1.csv", lego1);
	}
	else if (option == 2) {
		ReadInFiles("lego2.csv", lego2);
	}
	else if (option == 3) {
		ReadInFiles("lego3.csv", lego3);
	}
	else if (option == 4) {
		ReadInFiles("lego1.csv", lego1);
		for (unsigned int i = 0; i < lego1.size(); i++) {
			bigVector.push_back(lego1[i]);
		}
		ReadInFiles("lego2.csv", lego2);
		for (unsigned int i = 0; i < lego2.size(); i++) {
			bigVector.push_back(lego2[i]);
		}
		ReadInFiles("lego3.csv", lego3);
		for (unsigned int i = 0; i < lego3.size(); i++) {
			bigVector.push_back(lego3[i]);
		}
	}

	cout << "1. Most Expensive set" << endl;
	cout << "2. Largest piece count" << endl;
	cout << "3. Search for set name containing..." << endl;
	cout << "4. Search themes..." << endl;
	cout << "5. Part count information" << endl;
	cout << "6. Price information" << endl;
	cout << "7. Minifigure information" << endl;
	cout << "8. If you bought one of everything..." << endl;
	cout << "0. Exit" << endl;

	int choice;
	cin >> choice;
	cin.get(); // clearing line 

	/*======= Print out how many sets were loaded =======*/
	if (option == 1) {
		cout << "Total number of sets: ";
		cout << lego1.size() << endl;
	}
	else if (option == 2) {
		cout << "Total number of sets: ";
		cout << lego2.size() << endl;
	}
	else if (option == 3) {
		cout << "Total number of sets: ";
		cout << lego3.size() << endl;
	}
	else if (option == 4) {
		cout << "Total number of sets: ";
		cout << bigVector.size() << endl;
	}

	/*======= Based on the choice, execute the appropriate task and show the results =======*/

	if (choice == 1) {
		if (option == 1) {
			MostExpensive(lego1);
		}
		else if (option == 2) {
			MostExpensive(lego2);
		}
		else if (option == 3) {
			MostExpensive(lego3);
		}
		else if (option == 4) {
			MostExpensive(bigVector);
		}
	}
	else if (choice == 2) {
		if (option == 1) {
			LargestPieceCount(lego1);
		}
		else if (option == 2) {
			LargestPieceCount(lego2);
		}
		else if (option == 3) {
			LargestPieceCount(lego3);
		}
		else if (option == 4) {
			LargestPieceCount(bigVector);
		}
	}
	else if (choice == 3) {
		string input;
		getline(cin, input);
		if (option == 1) {
			SetNamesContaining(input, lego1);
		}
		else if (option == 2) {
			SetNamesContaining(input, lego2);
		}
		else if (option == 3) {
			SetNamesContaining(input, lego3);
		}
		else if (option == 4) {
			SetNamesContaining(input, bigVector);
		}
	}
	else if (choice == 4) {
		string userInput;
		getline(cin, userInput);
		if (option == 1) {
			SetThemes(userInput, lego1);
		}
		else if (option == 2) {
			SetThemes(userInput, lego2);
		}
		else if (option == 3) {
			SetThemes(userInput, lego3);
		}
		else if (option == 4) {
			SetThemes(userInput, bigVector);
		}
	}
	else if (choice == 5) {
		if (option == 1) {
			AveragePartCount(lego1);
		}
		else if (option == 2) {
			AveragePartCount(lego2);
		}
		else if (option == 3) {
			AveragePartCount(lego3);
		}
		else if (option == 4) {
			AveragePartCount(bigVector);
		}
	}
	else if (choice == 6) {
		if (option == 1) {
			PriceInformation(lego1);
		}
		else if (option == 2) {
			PriceInformation(lego2);
		}
		else if (option == 3) {
			PriceInformation(lego3);
		}
		else if (option == 4) {
			PriceInformation(bigVector);
		}
	}
	else if (choice == 7) {
		if (option == 1) {
			MinifigureInformation(lego1);
		}
		else if (option == 2) {
			MinifigureInformation(lego2);
		}
		else if (option == 3) {
			MinifigureInformation(lego3);
		}
		else if (option == 4) {
			MinifigureInformation(bigVector);
		}
	}
	else if (choice == 8) {
		if (option == 1) {
			OneOfEverything(lego1);
		}
		else if (option == 2) {
			OneOfEverything(lego2);
		}
		else if (option == 3) {
			OneOfEverything(lego3);
		}
		else if (option == 4) {
			OneOfEverything(bigVector);
		}
	}
	else if (choice == 0) {
		return 0;
	}

	return 0;
}



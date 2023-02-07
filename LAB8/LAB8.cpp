#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <map>
#include <sstream>
#include "Color.h"
using namespace std;

void ReadFile(const char* filename, map<string, Color>& colors);
void PrintColors(const map<string, Color>& colors);
void PrintColor(const Color& color);
void SearchForColor(map<string, Color>& colors);

int main()
{
	cout << "1-6: Load colors1/2/3/4/5/6.txt" << endl;
	cout << "7. Load all 6 files" << endl;
	int choice;
	cin >> choice;

	map<string, Color> colors;
	if (choice >= 1 && choice <= 6)
	{
		string file = "colors" + to_string(choice) + ".txt";
		ReadFile(file.c_str(), colors);
	}
	else if (choice == 7)
	{
		for (int i = 1; i <= 6; i++)
		{
			string file = "colors" + to_string(i) + ".txt";
			ReadFile(file.c_str(), colors);
		}

	}

	// Secondary menu
	cout << "1. Show all colors" << endl;
	cout << "2. Search for a color" << endl;
	cin >> choice;

	if (choice == 1)
		PrintColors(colors);
	else if (choice == 2)
		SearchForColor(colors);
	return 0;
}

void ReadFile(const char* filename, map<string, Color>& colors)
{
	// TODO: Read the file, create and store some Color objects
	ifstream inFile(filename);
	string name;
	string temp;
	int fullNum;

	if (inFile.is_open()) {
		string linesInFile;

		while (getline(inFile, linesInFile)) {
			istringstream anotherstream(linesInFile);

			getline(anotherstream, name, ' ');

			getline(anotherstream, temp, ' ');
			fullNum = stoi(temp);


			unsigned char red = fullNum >> 16;
			red = red & 255;

			unsigned char green = fullNum >> 8;
			green = green & 255;


			unsigned char blue = fullNum;
			blue = blue & 255;

			Color c(name, red, green, blue);
			colors.emplace(name, c);
		}
	}
	inFile.close();
}
void PrintColors(const map<string, Color>& colors)
{
	// TODO: iterate through all entries in the map and print each color, one at a time
	// Print out the color count afterward

	for (auto iter = colors.begin(); iter != colors.end(); iter++) {
		PrintColor(iter->second);
	}
	cout << "Number of colors: " << colors.size() << endl;


}
void PrintColor(const Color& color)
{
	cout << left << setw(20) << color.GetName();
	cout << right << setw(10) << color.GetHexValue();
	cout << "\t\t" << (int)color.GetR() << "," << (int)color.GetG() << "," << (int)color.GetB() << endl;
}
void SearchForColor(map<string, Color>& colors)
{
	// TODO: Get some input, check if that key exists, then print out the color (or an error message)
	map<string, Color>::iterator iter; 
	string name;
	cin >> name;

	iter = colors.find(name);

	if (iter != colors.end()) {
		PrintColor(colors[name]);
	}
	else {
		cout << name << " not found!" << endl;
	}
}

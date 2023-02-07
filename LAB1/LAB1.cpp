// LAB1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

int main()
{
    string bookTitle = "";
    string header1 = "";
    string header2 = "";
    string dataPoint = "";
    int i = 0;
    vector <string> authorColumns(0);
    vector <int> numberColumns(0);
    int commaCount = 0;
    string tempString = "";
    int tempInt = 0;

    cout << "Enter a title for the data:" << endl;
    getline(cin, bookTitle);
    cout << "You entered: " << bookTitle << endl;

    cout << "Enter the column 1 header:" << endl;
    getline(cin, header1);
    cout << "You entered: " << header1 << endl;

    cout << "Enter the column 2 header:" << endl;
    getline(cin, header2);
    cout << "You entered: " << header2 << endl;

    while (true) {
        commaCount = 0;

        cout << "Enter a data point (-1 to stop input):" << endl;
        getline(cin, dataPoint);

        if (dataPoint == "-1") {
            break;
        }

        for (i = 0; i < dataPoint.size(); i++) {
            if (dataPoint.at(i) == ',') {
                commaCount++;
            }
        }
        if (commaCount == 1) {
            try {
                for (i = 0; i < dataPoint.size(); i++) {
                    if (dataPoint.at(i) == ',') {
                        
                        tempString = dataPoint.substr(0, i); 
                        tempInt = stoi(dataPoint.substr(i + 1, dataPoint.size() - 1));

                        authorColumns.push_back(tempString);
                        numberColumns.push_back(tempInt);

                        cout << "Data string: " << tempString << endl;
                        cout << "Data integer: " << tempInt << endl;
                    }
                }
            }
            catch (invalid_argument e) {
                cout << "Error: Comma not followed by an integer." << endl;
                continue;
            }
        }
         if (commaCount == 0) {
            cout << "Error: No comma in string." << endl;
            continue;
        }
         if (commaCount > 1) {  
            cout << "Error: Too many commas in input." << endl;
            continue;
        }
    } 
    cout << endl;
    cout << setw(33) << right << bookTitle << endl;
    cout << setw(20) << left << header1 << "|" << setw(23) << right << header2 << endl;
    cout << setfill('-') << setw(44) << "" << endl;
    cout << setfill(' ');

    for (i = 0; i < authorColumns.size(); i++) {
        cout << setw(20) << left << authorColumns.at(i) << "|";
        cout << setw(23) << right << numberColumns.at(i) << endl;
    } 

    cout << endl;
    
    for (i = 0; i < authorColumns.size(); i++) {
        cout << setw(20) << right << authorColumns.at(i) << " ";
        cout << setfill('*') << setw(numberColumns.at(i)) << "" << endl;
        cout << setfill(' ');
    } 
}


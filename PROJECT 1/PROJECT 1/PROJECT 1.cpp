#include <iostream>
#include <string>
#include <sstream>
#include "LinkedList.h"
using namespace std;

// PART1
void TestAddHead();
void TestAddTail();
void TestAddingArrays();

//PART2
void TestFindAll();
void TestCopyCtor();
void TestAssignment();

//PART3
void TestInsertBeforeAfter();
void TestInsertAt();

int main()
{
	//PART 1

	int testNum;
	cin >> testNum;
	if (testNum == 1)
		TestAddHead();
	else if (testNum == 2)
		TestAddTail();
	else if (testNum == 3)
		TestAddingArrays();

	return 0;
}

void TestAddHead()
{
	cout << "=====Testing AddHead() functionality====" << endl;
	LinkedList<int> data;
	for (int i = 0; i < 12; i += 2)
		data.AddHead(i);
	cout << "Node count: " << data.NodeCount() << endl;
	cout << "Print list forward:" << endl;
	data.PrintForward();
	cout << "Print list in reverse:" << endl;
	data.PrintReverse();
}

void TestAddTail()
{
	cout << "=====Testing AddTail() functionality====" << endl;
	LinkedList<int> data;
	for (int i = 0; i <= 21; i += 3)
		data.AddTail(i);
	cout << "Node count: " << data.NodeCount() << endl;
	cout << "Print list forward:" << endl;
	data.PrintForward();
	cout << "Print list in reverse:" << endl;
	data.PrintReverse();
}

void TestAddingArrays()
{
	cout << "=====Testing AddNodesHead() and AddNodesTail() =====" << endl;

	string values[5];
	values[0] = "*";
	values[1] = "**";
	values[2] = "***";
	values[3] = "****";
	values[4] = "*****";

	LinkedList<string> list;
	list.AddHead("**");
	list.AddHead("***");
	list.AddHead("****");
	list.AddHead("*****");
	list.AddHead("******");
	list.AddHead("*******");
	list.AddHead("********");
	list.AddHead("*********");
	list.AddHead("********");
	list.AddHead("*******");
	list.AddHead("******");

	list.AddNodesHead(values, 5);
	list.AddNodesTail(values, 5);
	list.PrintForward();

	//PART2
	int testNum;
	cin >> testNum;
	if (testNum == 1)
		TestFindAll();
	else if (testNum == 2)
		TestCopyCtor();
	else if (testNum == 3)
		TestAssignment();

}

void TestFindAll()
{
	cout << "=====Testing FindAll() functionality=====" << endl;
	LinkedList<int> data;
	int searchVal = 256;

	data.AddTail(searchVal);
	data.AddTail(10);
	data.AddTail(20);
	data.AddTail(searchVal);
	data.AddTail(30);
	data.AddTail(searchVal);
	data.AddTail(40);
	data.AddTail(searchVal);

	cout << "Initial list: " << endl;
	data.PrintForward();

	vector<LinkedList<int>::Node*> nodes;
	data.FindAll(nodes, searchVal);

	cout << "\nNodes found: " << nodes.size() << endl;
	for (unsigned int i = 0; i < nodes.size(); i++)
	{
		cout << "Node #" << (i + 1) << ":\n";
		cout << "Value: " << nodes[i]->data << endl;

		cout << "Prev value: ";
		if (nodes[i]->prev != nullptr)
			cout << nodes[i]->prev->data;
		else
			cout << "nullptr";

		cout << "\nNext value: ";
		if (nodes[i]->next != nullptr)
			cout << nodes[i]->next->data;
		else
			cout << "nullptr";
		cout << endl;
	}
}

void TestCopyCtor()
{
	cout << "=====Testing Copy Constructor functionality=====" << endl;
	LinkedList<int> original;
	for (int i = 0; i <= 10; i += 5)
		original.AddTail(i);

	cout << "Printing original:" << endl;
	original.PrintForward();
	cout << endl;

	cout << "Printing copy:" << endl;
	LinkedList<int> copy = original;
	copy.PrintForward();
	cout << endl;

	cout << "Changing copy... adding to head and tail..." << endl;
	copy.AddHead(99);
	copy.AddTail(-102);
	cout << "Printing copy again:" << endl;
	copy.PrintForward();
	cout << endl;

	cout << "Printing original again:" << endl;
	original.PrintForward();
	cout << endl;
}

void TestAssignment()
{
	cout << "=====Testing Copy Assignment Operator functionality=====" << endl;
	LinkedList<int> first;
	LinkedList<int> second;

	for (int i = 20; i <= 30; i += 5)
		first.AddTail(i);
	for (int i = 17; i < 100; i += 22)
		second.AddTail(i);

	cout << "Printing first list:" << endl;
	first.PrintForward();
	cout << endl;

	cout << "Printing second list:" << endl;
	second.PrintForward();
	cout << endl;

	cout << "Assigning one list to another..." << endl;
	first = second;

	cout << "Printing after copying:" << endl;
	first.PrintForward();
	cout << endl;

	cout << "Changing both lists..." << endl;
	first.AddTail(66);
	second.AddTail(19);
	first.AddHead(-100);
	second.AddHead(-512);
	cout << "Printing first list: " << endl;
	first.PrintForward();
	cout << endl;
	cout << "Printing second list: " << endl;
	second.PrintForward();

//PART3

	int testNum;
	cin >> testNum;
	if (testNum == 1)
		TestInsertBeforeAfter();
	else if (testNum == 2)
		TestInsertAt();
}

void TestInsertBeforeAfter()
{
	LinkedList<int> data;
	data.AddTail(10);
	data.AddHead(9);
	data.AddTail(11);
	data.AddHead(8);
	data.AddTail(12);

	cout << "Initial list: " << endl;
	data.PrintForward();

	LinkedList<int>::Node* node = data.Find(10);
	cout << "\nSearching for node with value of 10..." << endl;

	if (node != nullptr)
	{
		cout << "Node found! Value: " << node->data << endl;
		cout << "Prev value: " << node->prev->data << endl;
		cout << "Next value: " << node->next->data << endl;
	}
	else
		cout << "Error! Returned node was a nullptr.";

	cout << "\nInserting 2048 before node and 4096 after node." << endl;
	data.InsertBefore(node, 2048);
	data.InsertAfter(node, 4096);
	data.PrintForward();
}

void TestInsertAt()
{
	cout << "=====Testing InsertAt() functionality=====" << endl;
	LinkedList<string> data;
	string test = "great benefit linked is the ability to easily into the";
	stringstream x(test);
	string tmp;
	while (getline(x, tmp, ' '))
		data.AddTail(tmp);

	cout << "Initial list: " << endl;
	data.PrintForward();
	cout << "Node count: " << data.NodeCount() << endl;

	cout << "\nInserting words into the list with InsertAt()..." << endl;

	data.InsertAt("One", 0);
	data.InsertAt("of", 3);
	data.InsertAt("lists", 5);
	data.InsertAt("insert", 10);
	data.InsertAt("nodes", 11);
	data.InsertAt("list.", 15);

	data.PrintForward();
	cout << "Node count: " << data.NodeCount() << endl;
}
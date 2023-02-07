#pragma once
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class LinkedList {
public:
	struct Node {

		T data;
		Node* next;
		Node* prev;

		Node() {
			next = nullptr;
			prev = nullptr;
		}
		Node(const T& givenData) {
			next = nullptr;
			prev = nullptr;
			data = givenData;
		}

	};
private:
	Node* head = nullptr;
	Node* tail = nullptr;
	unsigned int officialCount = 0;

	void DeletingNodes() {
		if (officialCount != 0) {
			Node* temp = head;
			while (temp->next != nullptr) {
				temp = temp->next;
				delete temp->prev;
			}
			delete temp;
			officialCount = 0;
			head = nullptr;
			tail = nullptr;
		}
	}

	void DeepCopies(const LinkedList<T>& list) {
		Node* temp = list.head;
		for (int i = 0; i < list.officialCount; i++) {
			this->AddTail(temp->data);
			temp = temp->next;
			// head is declared when the first tail is assigned
		}
		this->officialCount = list.officialCount;
		// not necessary but just in case 
	}

public:
	// Constructors //
	LinkedList() {
		head = nullptr;
		tail = nullptr;
		officialCount = 0;
	}

	// BIG THREE //
	LinkedList(const LinkedList<T>& list) {
		this->DeepCopies(list);
	}
	LinkedList<T> operator=(const LinkedList<T>& rhs) {
		// deletes everything first
		this->DeletingNodes();

		//copying everything 
		this->DeepCopies(rhs);
		return *this;
	}
	~LinkedList() {
		this->DeletingNodes();
	}
	// Inserters //
	void AddHead(const T& data) {
		Node* newHead = new Node(data);
		newHead->next = this->head;

		if (officialCount == 0) {
			tail = newHead;
		}
		else {
			this->head->prev = newHead;
		}
		this->head = newHead; 
		this->officialCount++;
	}
	
	void AddTail(const T& data) {
		Node* newTail = new Node(data);
		newTail->prev = this->tail;
		if (officialCount == 0) {
			this->head = newTail;
		}
		else {
			this->tail->next = newTail;
		}
		tail = newTail;
		this->officialCount++;
	}
	void AddNodesHead(const T* data, unsigned int count) {
		for (int i = count-1; i >= 0; i--) {
			AddHead(data[i]);
		}
	}

	void AddNodesTail(const T* data, unsigned int count) {

		for (unsigned int i = 0; i <count; i++) {
			AddTail(data[i]);
		}
	}
	void InsertAfter(Node* node, const T& data) {
		Node* temp = head;
		Node* holder = nullptr;
		for (unsigned int i = 0; i < officialCount; i++) {
			if (temp == node) {
				Node* newNode = new Node(data);
				holder = temp->next;

				temp->next = newNode;
				newNode->next = holder;

				holder->prev = newNode;
				newNode->prev = temp;
				break;
			}
			else {
				temp = temp->next;
			}
		}

		officialCount++;
	}
	void InsertBefore(Node* node, const T& data) {
		Node* temp = head;
		Node* holder = nullptr;
		for (unsigned int i = 0; i < officialCount; i++) {
			if (temp->next == node) {
				Node* newNode = new Node(data);
				holder = temp->next;

				temp->next = newNode;
				newNode->next = holder;

				holder->prev = newNode;
				newNode->prev = temp;
				break;
			}
			else {
				temp = temp->next;
			}
		}
		officialCount++;
	}
	void InsertAt(const T& data, unsigned int index) {
		if (index > officialCount) {
			throw out_of_range("Index out of range");
		}

		if (index == 0) {
			AddHead(data);
		}
		else if (index == officialCount) {
			AddTail(data);
		}
		else {
			Node* temp = head;
			for (unsigned int i = 0; i < index-1; i++) {
				temp = temp->next;
			}

			Node* newNode = new Node(data);
			Node* holder = temp->next;

			temp->next = newNode;
			newNode->next = holder;

			newNode->prev = temp;
			holder->prev = newNode;

			officialCount++;
		}
	}
	// Removal //
	bool RemoveHead() {
		if (head == nullptr) {
			return false;
		}
		else {
			if (officialCount == 1) {
				delete head;
				head = nullptr;
			}
			else {
				Node* temp = head->next;

				delete head;
				head = temp;

				head->prev = nullptr;
			}

			officialCount--;
			return true;
		}
	}
	bool RemoveTail() {
		if (tail == nullptr) {
			return false;
		}
		else {
			if (officialCount == 1) {
				delete tail;
				tail = nullptr;
			}
			else {
				Node* temp = tail->prev;

				delete tail;
				tail = temp;

				tail->next = nullptr;
			}

			officialCount--;
			return true;
		}
	}
	unsigned int Remove(const T& data) {

		Node* holder = nullptr;
		Node* holder2 = nullptr;

		vector <Node*> temporaryVector;
		FindAll(temporaryVector, data);

		if (temporaryVector.size() == 0) {
			return 0;
		}

		for (unsigned int i = 0; i < temporaryVector.size(); i++) {
			if (temporaryVector[i] == head) {
				RemoveHead();
			}
			else if (temporaryVector[i] == tail) {
				RemoveTail();
			}
			else {
				holder = temporaryVector[i]->prev;
				holder2 = temporaryVector[i]->next;

				holder->next = holder2;
				holder2->prev = holder;

				delete temporaryVector[i];
				officialCount--;
			}
		}
		return temporaryVector.size();
	}
	bool RemoveAt(unsigned int index) {
		if (index >= officialCount) {
			return false;
		}
		else {
			Node* temp = GetNode(index -1);

			if (temp == head) {
				RemoveHead();
			}
			else if (temp == tail) {
				RemoveTail();
			}
			else {
				Node* holder = temp->prev;
				Node* holder2 = temp->next;

				holder->next = holder2;
				holder2->prev = holder;

				delete temp;
				officialCount--;
			}
			return true;
		}
	}
	void Clear() {
		DeletingNodes();
	}

	// Accessors //
	unsigned int NodeCount() const{
		return officialCount;
	}
	Node* Head() {
		return head;
	}
	const Node* Head() const {
		return head;
	}
	Node* Tail() {
		return tail;
	}
	const Node* Tail() const{
		return tail;
	}
	Node* GetNode(unsigned int index) {
		Node* temp = head;
		if (index > officialCount - 1) {
			throw out_of_range("Index out of range");
		}
		else {
			for (unsigned int i = 0; i < index+1; i++) {
				temp = temp->next;
			}
		}
		return temp;
	}
	const Node* GetNode(unsigned int index) const {
		Node* temp = head;
		if (index > officialCount - 1) {
			throw out_of_range("Index out of range");
		}
		else {
			for (int i = 0; i < index + 1; i++) {
				temp = temp->next;
			}
		}
		return temp;
	}
	Node* Find(const  T& data) {
		Node* temp = head;
		for (unsigned int i = 0; i < officialCount; i++) {
			if (temp->data == data) {
				return temp;
			}
			else {
				temp = temp->next;
			}
		}
		return temp; 
	}
	const Node* Find(const  T& data) const {
		Node* temp = head;
		for (unsigned int i = 0; i < officialCount; i++) {
			if (temp->data == data) {
				return temp;
			}
			else {
				temp = temp->next;
			}
		}
		return temp; 
	}

	void FindAll(vector<Node*>& outData, const T& value) const {
		Node* temp = head;
		for (unsigned int i = 0; i < officialCount; i++) {
			if (temp->data == value) {
				outData.push_back(temp);
			}
				temp = temp->next;
		}
	}

	// Operators //
	const T& operator[](unsigned int index) const {
		if (index > officialCount) {
			throw out_of_range("Index out of range");
		}
		else{
			Node* temp = head;
			for (unsigned int i = 0; i < officialCount; i++) {
				if (i == index) {
					return temp->data;
				}
				else {
					temp = temp->next;
				}
			}
		}
	}
	bool operator== (const LinkedList<T>& rhs) const {
		Node* temp = head;
		Node* temp2 = rhs.head;

		for (unsigned int i = 0; i < officialCount; i++) {
			if (temp->data == temp2->data) {
				temp2 = temp2->next;
				temp = temp->next;
			}
			else {
				return false;
			}
		}
		return true;
	}

	// Behaviors //
	void PrintForward() const {
		Node* temp = head;
		while (temp!= nullptr) {
			cout << temp->data << endl;
			temp = temp->next;
		}
	}
	void PrintReverse() const {
		Node* temp = tail;
		while (temp!= nullptr) {
			cout << temp->data << endl;
			temp = temp->prev;
		}
	}
	void PrintForwardRecursive(const Node* node) const {
		cout << node->data << endl;
		if (node->next != nullptr) {
			PrintForwardRecursive(node->next);
		}
	}
	void PrintReverseRecursive(const Node* node) const {
		cout << node->data << endl;
		if (node->prev != nullptr) {
			PrintReverseRecursive(node->prev);
		}
	}

};

#pragma once
#include <iostream>

template<typename T>
class LinkedList
{
	struct Node
	{
		T data;
		Node* next = nullptr;
	};


public:
	LinkedList()
		: mHead(nullptr)
	{}

	~LinkedList()
	{
		if (IsEmpty())
		{
			return;
		}

		if (mHead->next == nullptr)
		{
			delete mHead;
			mHead = nullptr;
			return;
		}

		Node* previous = mHead;
		Node* current = mHead->next;

		while (current != nullptr)
		{
			delete previous;
			previous = current;
			current = current->next;
		}

		delete previous;
		mHead = nullptr;
		previous = nullptr;
	}

	void Insert(T data)
	{
		Node* newNode = CreateNode(data);
		if (IsEmpty())
		{
			mHead = newNode;
			return;
		}

		Node* currentNode = mHead;
		while (currentNode != nullptr)
		{
			if (currentNode->next == nullptr)
			{
				currentNode->next = newNode;
				currentNode = nullptr;
				break;
			}
			currentNode = currentNode->next;
		}
	}

	void Remove(T data)
	{
		if (IsEmpty())
		{
			std::cout << "The list is empty.\n";
			return;
		}

		if (mHead->data == data)
		{
			Node* temp = mHead->next;
			delete mHead;
			mHead = temp;
			temp = nullptr;
			return;
		}

		Node* currentNode = mHead->next;

		while (currentNode->next->data != data && currentNode != nullptr)
		{
			currentNode = currentNode->next;
		}

		if (currentNode == nullptr)
		{
			std::cout << "The element is not in the list.\n";
			return;
		}
		Node* temp = currentNode->next;
		currentNode->next = temp->next;
		delete temp;
		temp = nullptr;

	}

	bool IsEmpty()
	{
		return mHead == nullptr;
	}

	//Displays all the elements of the linked list
	void DisplayList()
	{
		// TODO: 1
		if (IsEmpty())
		{
			std::cout << "No elements in the list\n";
			return;
		}

		Node* temp = mHead;

		std::cout << "Display list: ";

		while (temp != nullptr)
		{
			std::cout << temp->data << ", ";
			temp = temp->next;
		}
		std::cout << "\n===================\n";
	}

	//Displays all the elements of the linked list in reverse order
	void DisplayReverseList()
	{
		// TODO: 2
		if (IsEmpty())
		{
			std::cout << "No elements in the list\n";
			return;
		}

		Node* temp = mHead;

		int size = 0;

		//find size of new list
		while (temp != nullptr)
		{
			++size;
			temp = temp->next;
		}
		//retake head
		temp = mHead;
		T* ReverseList = new T[size];

		for (int i = 0; i < size; i++)
		{
			ReverseList[i] = temp->data;
			temp = temp->next;
		}

		std::cout << "After Reverse: ";
		for (int i = size - 1; i >= 0; --i)
		{
			std::cout << ReverseList[i] << ", ";
		}
		std::cout << "\n===================\n";
	}

	//This function allows the user to modify an existance data
	//Returns true if the conten was modified and false if it wasn't.
	bool ModifyContent(T content, T newContent)
	{
		//TODO: 3
		if (IsEmpty())
		{
			std::cout << "No elements in the list\n";
			return false;
		}

		Node* temp = mHead;

		while (temp->data != content && temp != nullptr)
		{
			temp = temp->next;
		}

		if (temp == nullptr)
		{
			std::cout << "There is no existance data can be modiffy in this list.\n";
			return false;
		}
		else
		{
			temp->data = newContent;
			return true;
		}
	}

	//Clear all the data from the linked list
	void ClearList()
	{
		// TODO: 4
		if (IsEmpty())
		{
			std::cout << "No elements in the list\n";
			return;
		}

		Node* temp=mHead;

		while (temp != nullptr)
		{
			mHead = mHead->next;
			delete temp;

			temp = mHead;
		}

		std::cout << "Have Deleted all data in the linked list.\n";
		return;
	}

private:
	Node* mHead;

	Node* CreateNode(T data)
	{
		Node* newNode = new Node();
		newNode->data = data;
		return newNode;
	}
};

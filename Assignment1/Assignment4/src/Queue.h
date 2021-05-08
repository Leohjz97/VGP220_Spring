#pragma once

//TODO: 5 - Implement a Queue class from scratch
//Remember that your queue should follow the FIFO standard (First In First Out)

template<typename T>
class Queue
{
public:
	Queue() 
		:front(0), rear(-1), mCapacity(5), mCurrentSize(0)
	{
		mData = new T[mCapacity];
	};
	~Queue()
	{
		delete[] mData;
		mData = nullptr;
	};

	//Inserts the data in the queue.
	void Enqueue(T data)
	{
		if (mCurrentSize == mCapacity)
		{
			std::cout << "Already overflow. Expansion before insert more datas\n";
		}
		else
		{
			std::cout << "Inserting the data: " << data << std::endl;
			rear = (rear + 1) % mCapacity;
			mData[rear] = data;
			mCurrentSize++;
		}
	};

	//Removes an element from the queue and returns this element in the output parameter
	//Also it returns true if the object was removed and false if the Queue is empty
	bool Daqueue(T& output)
	{
		int a = 0;
		if (isEmpty())
		{
			return false;
		}
		else
		{
			if (output == 0)
			{
				mData[front] = 0;
				front++;
			}
			else
			{
				while (a != output)
				{
					a++;
				}

				std::cout << "Removing #" << a << ": " << mData[a] << std::endl;
				for (int i = a; i < mCurrentSize; i++)
				{
					mData[i] = mData[i + 1];
				}

			}
			return true;
		}
	
	};

	//Returns true if queue is empty, false otherwise
	bool isEmpty()
	{
		if (mCurrentSize == 0)
		{
			std::cout << "The queue list is empty.\n";
			return true;
		}
		return false;
	};

	//Display all the elements in the queue:
	//Example, lets suppose you inserted 1, 2, 3, 4, 5
	//Display should print: "front->1, 2, 3, 4, 5<-rear"
	void DisplayQueue()
	{
		std::cout << "Display Queue: ";
		for (int i = front; i <= rear; ++i)
		{
			std::cout << mData[i] << ", ";
		}
		std::cout << "\n";
	};
private:
	int front;
	int rear;
	int mCurrentSize;
	int mCapacity;
	T* mData;
};
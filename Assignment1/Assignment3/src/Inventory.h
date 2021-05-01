#pragma once

#include <iostream>
#include "Item.h"

class Inventory
{
public:
	Inventory()
		:mMaxSlots(5), mSlotsOccupied(0)
	{
		//TODO: Implement a default constructor for the Inventory class where the max number of slots
		// is 5 and all the slots are free (They are not occupied).
		mInventory = new Item[5];
	}
	Inventory(uint32_t capacity)
		:mMaxSlots(capacity), mSlotsOccupied(0)
	{
		//TODO: Implement a non default constructor for the Inventory class where 
		//all the slots are free (They are not occupied).
		mInventory = new Item[capacity];
	}
	Inventory(const Inventory& other)
	{
		//TODO: Implement a copy constructor for this class. Avoid shallow copy.
		mMaxSlots = other.mMaxSlots;
		mSlotsOccupied = other.mSlotsOccupied;

		delete[] mInventory;
		mInventory = nullptr;

		mInventory=new Item[other.mMaxSlots];

		for (int i = 0; i < other.mMaxSlots; ++i)
		{
			mInventory[i] = other.mInventory[i];
		}
	}
	Inventory(Inventory&& other)
	{
		//TODO: Implement a move constructor for this class. Reset to a default state the other inventory.
		mMaxSlots = other.mMaxSlots;
		other.mMaxSlots = 0;
	
		mSlotsOccupied = other.mSlotsOccupied;
		other.mSlotsOccupied = 0;

		delete[] mInventory;
		mInventory = nullptr;

		mInventory = other.mInventory;
		other.mInventory = nullptr;
	}
	~Inventory()
	{
		//TODO: Implement a destructor for this class.
		delete[] mInventory;
		mInventory = nullptr;	
	}

	//TODO: Implement a copy assignment operator
	Inventory& operator=(const Inventory& other)
	{
		if (this != &other)
		{
			mMaxSlots = other.mMaxSlots;
			mSlotsOccupied = other.mSlotsOccupied;

			delete[] mInventory;
			mInventory = nullptr;

			mInventory = new Item[other.mMaxSlots];

			for (int i = 0; i < other.mMaxSlots; ++i)
			{
				this->mInventory[i] = other.mInventory[i];
			}
		}
		return *this;
	}

	//TODO: Implement a move assignment operator
	Inventory& operator=(Inventory&& other)
	{
		if (this != &other)
		{
			mMaxSlots = other.mMaxSlots;
			other.mMaxSlots = 0;

			mSlotsOccupied = other.mSlotsOccupied;
			other.mSlotsOccupied = 0;

			delete[] mInventory;
			mInventory = nullptr;

			mInventory = other.mInventory;
			other.mInventory = nullptr;
		}
		return *this;
	}

	void AddItem(Item newItem)
	{
		//TODO: Implement AddItem MethodThis method adds a new item to the inventory. 
		//First it searches for this item to see if the item exists, and if the item exists 
		//it checks the quantity, because the max quantity allowed per slot is 50.
		//So, for example, if you have 50 healing potions in your inventory, and you want to add one more, this potion
		//should occupy a new slot. Pay attention that the SearchItem function already does this quantity check for you.
		//The extra check that you should do is for the accumulated quantity. So your function should check
		//how many items this current slot has and if you add this new item quantity, how many items you will have.
		//If it's greater than 50, you should make the quantity of one slot 50 and add the remainder quantity to a new slot.
		//For example:
		//[ HP 48 ] [  ] [  ] [  ] [  ] Inventory has a HP(healing potions) with 48 as quantity and you want to add more 5 HP
		//[ HP 50 ] [HP 3] [  ] [  ] [  ] Inventory after you added 5 HP

		//If the Inventory is full, return a message to the user that the inventory is full and the items will be discarted.
		//Use the method IsFullForItem;

		//check full or not
		//Full
		if (isFullForItem(&newItem) == true) 
		{
			space();
			std::cout << "The inventory is full and the items will be discarted.\n";
			return;
		}
		//!Full
		else
		{
			//If after you insert the item your inventory becomes full for the remainder, Print a message to the user with how many
			//items will be discarted;

			//Find same item and Find the index of the item
			if (SearchItemByName(newItem.name) != -1)
			{
				int index = SearchItemByNameLessThan50(newItem.name);
				int totalquantity = mInventory[index].quantity + newItem.quantity;

				//check new quantity is bigger than 50 or not
				if (totalquantity > 50)
				{
					int drop = totalquantity - 50;
					int add = 50 - mInventory[index].quantity;
					mInventory[index].quantity = 50;

					space();
					std::cout << "Alarm! " << newItem.name << "is Full!\n";
					std::cout << "Adding " << add << " " << newItem.name << " in inventory.\n";

					if (isFullForItem(&newItem) == true)
					{
						space();
						std::cout << "You has no space in your inventory!\n";
						std::cout << newItem.name << "has lost " << drop << std::endl;
					}
					else
					{
						newItem.quantity = drop;
						mInventory[mSlotsOccupied] = newItem;
						++mSlotsOccupied;

						space();
						std::cout << "Adding other " << newItem.quantity << " " << newItem.name << " in inventory.\n";
					}
				}
				else
				{
					mInventory[index].quantity = totalquantity;

					space();
					std::cout << "Adding" << newItem.quantity << " " << newItem.name << " in inventory.\n";
				}
			}
			//SPECIAL CASE: If the user adds an item of type charm with the name "Expansion" your inventory
			//should expand adding 5 more empty slots for the user.
			else if (newItem.name == "Expansion")
			{
				space();
				Expansion();
			}
			//no same in the inventory
			//add new item
			else
			{
				mInventory[mSlotsOccupied] = newItem;
				mSlotsOccupied++;

				space();
				std::cout << "Adding " << newItem.quantity << " " << newItem.name << " in inventory." << "\n";
			}

		}
	}

	void RemoveItem(std::string itemName, int quantity)
	{
		//TODO: Implement RemoveItem method
		//RemoveItem, should remove a quantity from the slot with the item. If the whole slot 
		//is empty, you should shift all the other items of the inventory;
		//If you try to remove more than what you have in one slot, just make the slot empty.
		//For example:
		//[ HP 50 ] [ HP 30 ] [  ] [  ] [  ] //You tried to remove 80 HP from the inventory
		//[ HP 30 ] [  ] [  ] [  ] [  ] //You just remove from one slot.

		int index = SearchItemByName(itemName);

		//> max
		if (quantity >= 50)
		{
			for (int i = index; i < mSlotsOccupied; ++i)
			{
				mInventory[i] = mInventory[i + 1];
			}
			mSlotsOccupied -= 1;
		}

		//SPECIAL CASE: If the user removes the charm Expansion from the inventory, your inventory 
		//should reduce the number of slots in 5, discarting all the items from the removed slots.

		else if (itemName == "Expansion")
		{
			space();
			Reduce();
		}

		//<max
		else
		{
			mInventory[index].quantity -= quantity;
		}
		space();
		std::cout << "Removing " << quantity << " " << itemName << " from inventory." << "\n";
	}

	Item* UseItem(std::string itemName)
	{
		// TODO: Search for the item and if it exists, return this item and remove one from the inventory
		// otherwise, return nullptr.
		// The user is just allowed to use the Types: Posion and Utility.

		int idex = SearchItemByName(itemName);
		
		if (idex != -1)
		{
			if (mInventory[idex].type == ItemType::Potion || mInventory[idex].type == ItemType::Utility)
			{
				space();
				std::cout << "Using " << itemName << "\n";
				mInventory[idex].quantity -= 1;
			}
			else
			{
				space();
				std::cout << "Worry types, Only POSION and UTILITY can be used now!\n";
			}
		}

		return &mInventory[idex];
	}
private:
	//Array of Items
	Item* mInventory;
	//This variable tracks the capacity of the inventory
	uint32_t mMaxSlots;
	//This variable tracks how many slots are occupied.
	uint32_t mSlotsOccupied;

	void space()
	{
		std::cout << "====================\n";
	}

	//Expansion
	void Expansion(int add5 = 5)
	{
		Item* temp = mInventory;
		mInventory = new Item[mMaxSlots + add5];
		mMaxSlots += add5;

		for (int i = 0; i < mSlotsOccupied; ++i)
		{
			mInventory[i] = temp[i];
		}
		delete[] temp;
		temp = nullptr;

		std::cout << "#Add 5 sizes, successful\n";
	}

	//reduce
	void Reduce(int reduce5 = 5)
	{
		Item* temp = mInventory;
		mInventory = new Item[mMaxSlots - reduce5];
		mMaxSlots -= reduce5;

		for (int i = 0; i < mSlotsOccupied; ++i)
		{
			mInventory[i] = temp[i];
		}
		delete[] temp;
		temp = nullptr;

		std::cout << "#Redce 5 sizes, items in these sizes have disppeared\n";
	}

	//This method seaches for the item inside the Inventory and if it finds the item with less than
	//50 as quantity, it returns the index of the item inside the inventory array, otherwise, returns -1.
	int SearchItemByNameLessThan50(std::string target) const
	{
		int index = -1;
		for (int i = 0; i < mSlotsOccupied; ++i)
		{
			if (target.compare(mInventory[i].name) == 0 && mInventory[i].quantity < 50)
			{
				index = i;
				break;
			}
		}

		return index;
	}

	//Returns the index of the item if it exists and -1 if it doesn't.
	int SearchItemByName(std::string target) const
	{
		int index = -1;
		for (int i = 0; i < mSlotsOccupied; ++i)
		{
			if (target.compare(mInventory[i].name) == 0)
			{
				index = i;
				break;
			}
		}
		return index;
	}

	//If you don't have the item inside the inventory and all the slots are occupied - True
	//If you have the item in the inventory with max capacity and all the other slots are occupied - True
	//Otherwise - False.
	bool isFullForItem(Item* item) const
	{
		int index = SearchItemByNameLessThan50((*item).name);
		if (index == -1 && mSlotsOccupied == mMaxSlots)
		{
			return true;
		}
		if (index != -1 && mInventory[index].quantity >= 50 && mSlotsOccupied == mMaxSlots)
		{
			return true;
		}
		return false;
	}
};
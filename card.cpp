#include <iostream>
#include <string>
#include <time.h> //allows the use of time()
#include <cstdlib>
#include "card.h" //class declarations in header file

using namespace std;

// CONSTRUCTORS
Card::Card()
{
	suit = "null";
	cardvalue = 0;
}

Deck::Deck()
{
	for (int x = 0, y = 1; x < 10; x++, y++) //assigns suit "hearts" to ten seperate cards valued 1-10 for Deck instance
	{
		deck[x].setsuit("Hearts");
		deck[x].setcardvalue(y);
	}
	for (int x = 10, y = 1; x < 20; x++, y++) //assigns suit "clubs" to ten seperate cards valued 1-10 for Deck instance
	{
		deck[x].setsuit("Clubs");
		deck[x].setcardvalue(y);
	}
	for (int x = 20, y = 1; x < 30; x++, y++) //assigns suit "diamonds" to ten seperate cards valued 1-10 for Deck instance
	{
		deck[x].setsuit("Diamonds");
		deck[x].setcardvalue(y);
	}

}

// MODIFICATION MEMBER FUNCTIONS
void Card::setsuit(const string value)
{
	if (value == "Hearts" || value == "Diamonds" || value == "Clubs")
		suit = value;
}

void Card::setcardvalue(const int value)
{
	if (value >= 1 && value <= 10)
		cardvalue = value;
}

Card Deck::getcardmember(const int value) //This was to test what members are in the array since deck is private, may not be needed in final program
{
	return deck[value];
}

// CONSTANT MEMBER FUNCTIONS
string Card::getsuit(void) const
{
	return suit;
}

int Card::getcardvalue(void) const
{
	return cardvalue;
}

void Card::displayall(void) const
{
	if (suit == "null" || cardvalue == 0)
		cout << "Either the suit or card has not been given a value!";
	else
	{
		cout << cardvalue << " of " << suit;
	}
}

void Deck::shuffle()
{
	srand(time(0)); //intializes the random function to the clock
	Card temp;
	int x, y;
	
	for (int i = 0; i < 2000; i++) //for loop to shuffle card deck by switching two array members each iteration
	{
		x = rand() % 30; //value 0-29 to pick Card instance out of deck array
		y = rand() % 30; //value 0-29 to pick another Card instance out of deck array

		if (x != y) //ensures two seperate cards are swapped
		{
			temp = deck[x]; //saves Card instance in a temporary location to allow for swapping
			deck[x] = deck[y];
			deck[y] = temp;  
		}
	
		else
		{
			i--; //keeps the number of swaps to 2000 in the event the same card wants to be swapped
		}
		
	}
}
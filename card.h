// CLASS PROVIDED:  Card
//
// CONSTRUCTOR for the Card class:
//   Card()
//     Description:		constructor will initialize Card objects
//     Preconditions:	none
//     Postcondition:	card has been set to "null" and 0. 
//
// MODIFICATION MEMBER FUNCTIONS for the Card class
//   void setsuit (const string value)
//     Description:		set the suit of the card 
//     Precondition:	value is either "hearts" or "diamonds" or "clubs"
//     Postcondition:	suit of the card has been assigned to a string
//
//   void setcardvalue (const int value)
//     Description:		set the integer representation of the card
//     Precondition:	cardvalue is a positive number between 1 and 10, inclusive
//     Postcondition:	cardvalue is set to integer value
//
// CONSTANT MEMBER FUNCTIONS for the Card class
//   string getsuit (void) const
//     Description:		obtain suit of card
//     Preconditions:	none
//     Postcondition:	suit of the card is returned
//
//   int  getcardvalue(void) const
//     Description:		obtain the integer representation of the card
//     Preconditions:	none
//     Postcondition:	integer of cardvalue is returned
//
//   void displayall (void) const
//     Description:		display card with suit to screen
//     Preconditions:	none
//     Postcondition:	cardvalue of the card is displayed on the screen

// CLASS PROVIDED:  Deck
//
// CONSTRUCTOR for the Deck class:
//   Deck()
//     Description:		constructor will initialize Deck objects
//     Preconditions:	none
//     Postcondition:	deck creates array of Card objects size 30. 
//
// CONSTANT MEMBER FUNCTIONS for the Deck class
//   Card getcardmember(const int value)
//     Description:		returns specified Card member in Deck object
//     Preconditions:	integer between 0-29
//     Postcondition:	returns Card object from Deck at specified array position
//
//   shuffle (void) const
//     Description:		Shuffles the Card array members of Deck object
//     Preconditions:	none
//     Postcondition:	none


#ifndef CARD_H
#define CARD_H

#include <string>

const int SIZE = 30;

class Card
{
public:
    // CONSTRUCTOR
    Card();

    // MODIFICATION MEMBER FUNCTIONS
    void setsuit(const std::string);
    void setcardvalue(const int);

    // CONSTANT MEMBER FUNCTIONS
    std::string getsuit(void) const;
    int  getcardvalue(void) const;
    void displayall(void) const;

private:
    std::string suit;
    int  cardvalue;
};

class Deck
{
public:
    //CONSTRUCTOR
    Deck();

    //CONSTANT MEMBER FUNCTIONS
    Card getcardmember(const int value);
    void shuffle(); 

private:
    Card deck[SIZE];
};

#endif

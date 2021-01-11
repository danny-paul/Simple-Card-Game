#include <iostream>
#include <string>
#include <cstdlib>
#include "card.h"
#include <time.h>
#include <stdio.h>

using namespace std;


Card userturn(Card* hand, int tricknumber); //handles user turn, returns their selected card
void displayhand(Card* hand, int handsize); //displays chosen hand to the screen.
int inputcheck(int size); //Restricts user input for choosing active cards from 1 to size of cards in play
int inputcheckbid(); //Restricts user input for choosing bid (1-10)
Card compfollowsuit(Card* hand, int* suitarray, Card cardtofollow, int tricknumber); //when a computer player follows a lead card, returns their selected card
void countsuits(Card* handtocount, int* suitarray, int tricknumber); //counts number of each suit a hand has. 
int highestCardOfSuit(Card* hand, string suit, int tricknumber); //returns the array position of the highest suit in a specified hand
int lowestCardOfSuit(Card* hand, string suit, int tricknumber); //returns the array positoin of the lowest suit in a specified hand
void moveCardToBack(Card* hand, int cardToMove, int tricknumber); //effectively takes a card out of play by moving it to the back of the deck
Card compsetsuit(Card* hand, int* suitarray, int tricknumber); //when a computer leads a trick, returns their selected card
char findWinnerTrick(Card leadCard, Card player1, Card player2, char leadIs); //determines the winner of the match, returns the corresponding character associated with the winner


int main()
{
	Card card1; //object for testing 
	Card user[10], comp1[10], comp2[10]; //hand for all players
	Deck deckofcards; //object containing 30 cards in an array
	int bid; //user guess for number of tricks they will win
	int cardcount = 10; //Keeps track of rounds
	int comp1suitcount[3], comp2suitcount[3]; //array for suit count; [0]=Hearts, [1]=Clubs, [2]= Diamonds
	char trickwinner = 'a'; //set as 'a' by default to allow user to lead first
	int userScore = 0, comp1Score = 0, comp2Score = 0; //score for each round
	int userScoreTotal = 0, comp1ScoreTotal = 0, comp2ScoreTotal = 0; //score for total game
	int usertrickwins = 0, comp1trickwins = 0, comp2trickwins = 0; //trickwins for each player
	int handsPlayed = 1; //keeps track of number of hands played
	Card usercard; //user selected card object
	Card leadcard; //leading card regardless of player
	Card comp1card, comp2card; //holds computer cards for the round
	char originalLead; //keeps track of lead in the event of a tie setting trickWinners='d'.


	while (userScoreTotal < 100 && comp1ScoreTotal < 100 && comp2ScoreTotal < 100) { //loop to play rounds until someone wins at 100 points

		deckofcards.shuffle(); //randomizes the deck

		//Assigns cards from deck to each hand
		for (int i = 0; i < 30; i++) {
			if (i < 10) {
				user[i] = deckofcards.getcardmember(i); //assigns card from deck into user's hand at array 0-9
			}
			else if (i < 20 && i >= 10) {
				comp1[i - 10] = deckofcards.getcardmember(i); //assigns cards 10-19 from deck into computer1's hand at 0-9
			}
			else {
				comp2[i - 20] = deckofcards.getcardmember(i); //assigns cards 20-29 from deck into computer2's hand at 0-9
			}
		}

		//place user bid
		cout << "Looking at your hand, determine what your bid will be for this match.\n";
		cout << "Bids are guesses on how many tricks will be won each hand played.\n";
		cout << "At the end of each hand, if you manage to reach or exceed your bid, you will receive points equal to ten times your bid.\n";
		cout << "However, if you fail to reach your bid, you will be deducted points equal to ten times your bid.\n";
		cout << "The first player to reach 100 points wins!\n\n";
		displayhand(user, 10); //shows user hand intially
		cout << "\n\n";
		cout << "Please enter how many tricks you believe you will win: ";
		bid = inputcheckbid(); //checks user input for integer 1-10
		system("cls"); //clears terminal
		cout << "Your bid is: " << bid << "." << "\n";

		for (cardcount = 10; cardcount >= 1; cardcount--) { //Loop to play the whole hand
			if (trickwinner == 'a') { //user leads
				//a = user

				cout << "You are leading this round, please select a card.\n\n";


				displayhand(user, cardcount); //displays user hand restricted to number of cards in play


				leadcard = userturn(user, cardcount); //returns card object for comparison 
				comp1card = compfollowsuit(comp1, comp1suitcount, leadcard, cardcount); //sets comp1 card in this trick compared to lead
				comp2card = compfollowsuit(comp2, comp2suitcount, leadcard, cardcount); //sets comp2 card in this trick compared to lead
				trickwinner = findWinnerTrick(leadcard, comp1card, comp2card, trickwinner); //picks trick winner or returns 'd' for tie
				if (trickwinner == 'd') {
					originalLead = 'a'; //remembers who originally led in the event of 'd' (aka a tie)
				}

				system("PAUSE");
				system("cls");
				//reviews the round 
				cout << "Your card is: "; leadcard.displayall(); cout << "\n";
				cout << "Computer 1 selected: "; comp1card.displayall(); cout << "\n";
				cout << "Computer 2 selected: "; comp2card.displayall(); cout << "\n\n";
			}
			else if (trickwinner == 'b') { //comp1 leads
				//b = comp1

				leadcard = compsetsuit(comp1, comp1suitcount, cardcount); //returns lead card object for comparison
				comp2card = compfollowsuit(comp2, comp2suitcount, leadcard, cardcount); //sets comp2 card in this trick compared to lead
				cout << "Computer 1 is leading this round.\n"; cout << "Lead Card: "; leadcard.displayall(); cout << "\n\n"; //tells who leads and shows lead card

				cout << "Playerhand\n\n";
				displayhand(user, cardcount);
				usercard = userturn(user, cardcount);
				system("cls");


				trickwinner = findWinnerTrick(leadcard, usercard, comp2card, trickwinner); //picks trick winner or returns 'd' for tie
				if (trickwinner == 'd') {
					originalLead = 'b'; //remembers who originally led in the event of 'd' (aka a tie)
				}

				//displays review of round
				cout << "Your card is: "; usercard.displayall(); cout << "\n";
				cout << "Computer 1 selected: "; leadcard.displayall(); cout << "\n";
				cout << "Computer 2 selected: "; comp2card.displayall(); cout << "\n\n";
				system("PAUSE");
				system("cls");
			}
			else if (trickwinner == 'c') { //comp2 leads, cannot use else since there is a 'd' and 'e' possiblity
				//c = comp2

				leadcard = compsetsuit(comp2, comp2suitcount, cardcount); //returns lead card object for comparison
				comp1card = compfollowsuit(comp1, comp1suitcount, leadcard, cardcount); //sets comp1 card in this trick compared to lead
				cout << "Computer 2 is leading this round.\n"; cout << "Lead Card: "; leadcard.displayall(); cout << "\n\n";

				cout << "Player Hand\n\n";
				displayhand(user, cardcount);
				usercard = userturn(user, cardcount);
				system("cls");

				trickwinner = findWinnerTrick(leadcard, usercard, comp1card, trickwinner);
				if (trickwinner == 'd') {
					originalLead = 'c'; //remembers who originally led in the event of 'd' (aka a tie)
				}

				cout << "Your card is: "; usercard.displayall(); cout << "\n";
				cout << "Computer 1 selected: "; comp1card.displayall(); cout << "\n";
				cout << "Computer 2 selected: "; leadcard.displayall(); cout << "\n\n";
			}

			//incrementing scores based on winner
			if (trickwinner == 'a') { //user won, increment their score
				usertrickwins++;
				cout << "You won the trick!";
			}
			else if (trickwinner == 'b') { //comp1 won, increment their score
				comp1trickwins++;
				cout << "Computer 1 won the trick";
			}
			else if (trickwinner == 'c') { //comp2 won, increment their score
				comp2trickwins++;
				cout << "Computer 2 won the trick";
			}
			else if (trickwinner == 'd') { //tie, increment no one and let original lead pick again
				trickwinner = originalLead;
				cout << "It was a tie!";
			}

			if (cardcount != 0) { //prints rounds remaining
				cout << "\n\n" << (cardcount - 1) << " Rounds remaining.\n\n";
			}
			system("PAUSE");
			system("cls");
		}


		//review of round and round calculations
		//tally user score and output for user
		cout << "Your tricks won: " << usertrickwins << ". Your bid: " << bid << ". ";
		if (usertrickwins >= bid) { //if reached bid
			userScoreTotal = userScoreTotal + (bid * 10);
			cout << "You reached your bid!\n\n" << "Your Points: " << userScoreTotal << ".\n";
		}
		else { //if failed to reach bid
			userScoreTotal = userScoreTotal + (bid * (-10));
			cout << "You didn't reach your bid!\n\n" << "Your Points: " << userScoreTotal << ".\n";
		}
		//tally computer scores and print them
		comp1ScoreTotal = comp1ScoreTotal + (comp1trickwins * 10);
		comp2ScoreTotal = comp2ScoreTotal + (comp2trickwins * 10);
		cout << "Computer 1 tricks won: " << comp1trickwins << ". Points: " << comp1ScoreTotal << ". \n";
		cout << "Computer 2 tricks won: " << comp2trickwins << ". Points: " << comp2ScoreTotal << ". \n\n";

		system("PAUSE");
		system("cls");

		//resets the values for next round
		comp1trickwins = 0;
		comp2trickwins = 0;
		usertrickwins = 0;
		handsPlayed++; //increments number of hands played
		trickwinner = 'a'; //ensures user starts the game

	}
	system("PAUSE");
	system("cls");

	//prints winner of the game
	cout << "Game Over!\n\n";
	cout << "Your Points: " << userScoreTotal << ".\n";
	cout << "Computer 1 Points: " << comp1ScoreTotal << ". \n";
	cout << "Computer 2 Points: " << comp2ScoreTotal << ". \n\n";

	if (userScoreTotal >= comp1ScoreTotal && userScoreTotal >= comp2ScoreTotal) { //user winning or being tied
		if (userScoreTotal == comp1ScoreTotal) { //tied with comp1
			cout << "You tied with Computer 1";
		}
		else if (userScoreTotal == comp2ScoreTotal) { //tied with comp2
			cout << "You tied with Computer 2";
		}
		else { //last possible instance is winning
			cout << "You win!";
		}
	}
	else if (comp2ScoreTotal > userScoreTotal && comp2ScoreTotal >= comp1ScoreTotal) { //comp2 having the highest score or tieing
		if (comp2ScoreTotal == comp1ScoreTotal) { //if tie occurs between comp1/comp2
			cout << "Computer 1 and Computer 2 tied";
		}
		else { //if comp2 is not tied with comp2
			cout << "Computer 2 won";
		}

	}
	else { //last possible case is computer 1 being greater than all
		cout << "Computer 1 won";
	}


}


void displayhand(Card* hand, int handsize) {
	for (int i = 0; i < handsize; i++) { //limits to only cards in play
		cout << i << ". "; //card number 0-handsize
		hand[i].displayall(); //displays suit and Card object in hand array
		cout << "\n";
	}
}

//input check needs to be fixed
int inputcheckbid() {
	int check;

	while (!(cin >> check) || cin.peek() != '\n' || check < 1 || check > 10) //restricts only integers between 1-10
	{
		cout << "Please enter an integer between 1 and 10: ";
		cin.clear();
		cin.ignore(30000, '\n');
	}

	return check;
}

int inputcheck(int size) {
	int check;

	while (!(cin >> check) || cin.peek() != '\n' || check < 0 || check > size) //restricts only integers between 1-10
	{
		cout << "Please enter an integer between 0 and " << size << ": ";
		cin.clear();
		cin.ignore(30000, '\n');
	}

	return check;
}

Card userturn(Card* hand, int tricknumber) {
	Card usercard; //allows for swap to back of the deck
	int userChoice; //holds array position of selected card

	cout << "Please select a card by typing the number next to the card" << "\n";
	userChoice = inputcheck(tricknumber - 1); //assigns the selected card and goes through inputcheck to ensure valid
	usercard = hand[userChoice]; //selects card and calls input check via the tricknumber to limit input range 1-tricknumber

	hand[userChoice] = hand[tricknumber - 1]; //assigns unused card to position of just selected card
	hand[tricknumber - 1] = usercard; //sets the newly used card to the back of the deck.

	return usercard; //returns card object of selected card
}

Card compfollowsuit(Card* hand, int* suitarray, Card cardtofollow, int tricknumber) {
	int arrayposition; //holds array position of highest card
	Card tempCard; //holds card so we can return the correct card after moving selected card back
	int highestHeart = hand[highestCardOfSuit(hand, "Hearts", tricknumber)].getcardvalue(); //will hold highest cardValue of Hearts
	int highestClub = hand[highestCardOfSuit(hand, "Clubs", tricknumber)].getcardvalue(); //will hold highest cardValue of Clubs
	int highestDiamond = hand[highestCardOfSuit(hand, "Diamonds", tricknumber)].getcardvalue(); //will hold highest cardValue of Diamond

	countsuits(hand, suitarray, tricknumber); //function to count amount of each suit in hand of cards in plays

	if (cardtofollow.getsuit() == "Hearts") { //if hand has the suit of lead card
		//0 = hearts
		if (suitarray[0] != 0) { //if hand has atleast 1 heart card
			if (highestHeart < cardtofollow.getcardvalue()) { //throw the lowest heart card if cannot beat
				arrayposition = lowestCardOfSuit(hand, "Hearts", tricknumber);
				tempCard = hand[arrayposition];
				moveCardToBack(hand, arrayposition, tricknumber); //moves lowest heart to back of hand
				return tempCard; //returns lowest card hand has
			}
			else if (highestHeart >= cardtofollow.getcardvalue()) { //throw the highest card of heart card when able to beat, or tie
				arrayposition = highestCardOfSuit(hand, "Hearts", tricknumber);
				tempCard = hand[arrayposition];
				moveCardToBack(hand, arrayposition, tricknumber); //moves highest heart to back of hand
				return tempCard; //returns highest card hand had
			}
		}
		else { //if no hearts, then throws lowest card from the largest suit count
			if (suitarray[1] > suitarray[2]) { //# of clubs > diamonds
				arrayposition = lowestCardOfSuit(hand, "Clubs", tricknumber);
				tempCard = hand[arrayposition];
				moveCardToBack(hand, arrayposition, tricknumber); //hides card in back
				return tempCard; //returns lowest card hand has
			}
			else { // # of diamonds > clubs (or tie chooses diamonds)
				arrayposition = lowestCardOfSuit(hand, "Diamonds", tricknumber);
				tempCard = hand[arrayposition];
				moveCardToBack(hand, arrayposition, tricknumber); //hides card in back
				return tempCard; //returns lowest card hand has
			}
		}
	}
	else if (cardtofollow.getsuit() == "Clubs") {
		//1=clubs
		if (suitarray[1] != 0) { //if hand has atleast 1 club
			if (highestClub < cardtofollow.getcardvalue()) { //throw the low card of clubs if cannot beat
				arrayposition = lowestCardOfSuit(hand, "Clubs", tricknumber);
				tempCard = hand[arrayposition];
				moveCardToBack(hand, arrayposition, tricknumber); //hides card in back
				return tempCard; //returns lowest card hand has
			}
			else if (highestClub >= cardtofollow.getcardvalue()) { //throw the high card of club if able to beat, or tie
				arrayposition = highestCardOfSuit(hand, "Clubs", tricknumber);
				tempCard = hand[arrayposition];
				moveCardToBack(hand, arrayposition, tricknumber); //hides card in back
				return tempCard; //returns highest card hand had
			}
		}
		else { //if no clubs, then throws lowest card from the largest suit count
			if (suitarray[0] > suitarray[2]) { //# of hearts > # of diamonds
				arrayposition = lowestCardOfSuit(hand, "Hearts", tricknumber);
				tempCard = hand[arrayposition];
				moveCardToBack(hand, arrayposition, tricknumber); //hides card in back
				return tempCard; //returns lowest card hand has
			}
			else { // # of diamonds > # of hearts (or tie chooses diamonds)
				arrayposition = lowestCardOfSuit(hand, "Diamonds", tricknumber);
				tempCard = hand[arrayposition];
				moveCardToBack(hand, arrayposition, tricknumber); //hides card in back
				return tempCard; //returns lowest card hand has
			}
		}
	}
	else {
		//2 Diamonds
		if (suitarray[2] != 0) { //if hand has atleast 1 diamond
			if (highestDiamond < cardtofollow.getcardvalue()) { //throw the lowest diamond card if cannot beat
				arrayposition = lowestCardOfSuit(hand, "Diamonds", tricknumber);
				tempCard = hand[arrayposition];
				moveCardToBack(hand, arrayposition, tricknumber); //hides card in back
				return tempCard; //returns lowest card hand has
			}
			else if (highestDiamond >= cardtofollow.getcardvalue()) { //throw the highest diamond card if can beat, or tie
				arrayposition = highestCardOfSuit(hand, "Diamonds", tricknumber);
				tempCard = hand[arrayposition];
				moveCardToBack(hand, arrayposition, tricknumber); //hides card in back
				return tempCard; //returns highest diamond hand had
			}
		}
		else { //if no diamonds, then throws lowest card from the largest suit count
			if (suitarray[1] > suitarray[0]) { //# of clubs > # of hearts
				arrayposition = lowestCardOfSuit(hand, "Clubs", tricknumber);
				tempCard = hand[arrayposition];
				moveCardToBack(hand, arrayposition, tricknumber); //hides card in back
				return tempCard; //returns lowest card hand has
			}
			else { // # of hearts > # of clubs (or tie chooses Hearts)
				arrayposition = lowestCardOfSuit(hand, "Hearts", tricknumber);
				tempCard = hand[arrayposition];
				moveCardToBack(hand, arrayposition, tricknumber);
				return tempCard; //returns lowest card hand has
			}
		}
	}

}

void countsuits(Card* handtocount, int* suitarray, int tricknumber) {
	int hearts = 0, clubs = 0, diamonds = 0;

	for (int i = 0; i < tricknumber; i++) { //counts number of each suit in hand for cards in play
		if (handtocount[i].getsuit() == "Hearts") {
			hearts++;
		}
		if (handtocount[i].getsuit() == "Diamonds") {
			diamonds++;
		}
		if (handtocount[i].getsuit() == "Clubs") {
			clubs++;
		}
	}
	suitarray[0] = hearts; //array position 0 is hearts
	suitarray[1] = clubs; //array position 1 is clubs
	suitarray[2] = diamonds; //array position 2 is diamonds
}

int highestCardOfSuit(Card* hand, string suit, int tricknumber) {
	int arraypositionhigh = 0, highestcardofsuit = 0;

	for (int i = 0; i < tricknumber; i++) { //checks only cards in play
		if (hand[i].getcardvalue() > highestcardofsuit && hand[i].getsuit() == suit) { //checks highest value of suit in question
			highestcardofsuit = hand[i].getcardvalue();
			arraypositionhigh = i; //tracks array position of highest card of suit
		}
	}

	return arraypositionhigh; //returns integer position in the hand of the highest card value of suit
}

int lowestCardOfSuit(Card* hand, string suit, int tricknumber) {
	int arraypositionlow = 0, lowestcardofsuit = 11;

	for (int i = 0; i < tricknumber; i++) { //checks only cards in play
		if (hand[i].getcardvalue() < lowestcardofsuit && hand[i].getsuit() == suit) { //checks lowest value of suit in question
			lowestcardofsuit = hand[i].getcardvalue();
			arraypositionlow = i; //tracks array position of lowest card of suit
		}
	}

	return arraypositionlow; //returns integer position in the hand of the lowest card value of suit
}

void moveCardToBack(Card* hand, int cardToMove, int tricknumber) {
	Card tempCard; //user selected card, also allows for swap to back of the deck

	tempCard = hand[cardToMove]; //selects card and calls input check via the tricknumber to limit input range 1-tricknumber

	hand[cardToMove] = hand[tricknumber - 1]; //assigns unused card to position of just selected card
	hand[tricknumber - 1] = tempCard; //sets the newly used card to the back of the deck.
}

Card compsetsuit(Card* hand, int* suitarray, int tricknumber) {
	srand(time(NULL)); //initialize random seed
	int randomSuit = 1 + rand() % 3; //random number 1-3 to randomly select suit
	int arrayposition; //holds posiiton of card in array
	Card tempCard; //for switching

	countsuits(hand, suitarray, tricknumber); //function to count suits in corresponding playerhand

	while (suitarray[randomSuit] == 0) { //ensures that the selected suit in the suitarray has atleast one member
		randomSuit = 1 + rand() % 3;
	}

	if (randomSuit == 0) { //returns highest hearts card object
		arrayposition = highestCardOfSuit(hand, "Hearts", tricknumber); //assigns highest card integer positon
		tempCard = hand[arrayposition];
		moveCardToBack(hand, arrayposition, tricknumber); //moves card to back of hand
		return tempCard;
	}
	else if (randomSuit == 1) { //returns highest clubs card object
		arrayposition = highestCardOfSuit(hand, "Clubs", tricknumber); //assigns highest card integer positon
		tempCard = hand[arrayposition];
		moveCardToBack(hand, arrayposition, tricknumber); //hides card in back of hand
		return tempCard;
	}
	else { //returns highest diamond card as card object
		arrayposition = highestCardOfSuit(hand, "Diamonds", tricknumber); //assigns highest card integer positon
		tempCard = hand[arrayposition];
		moveCardToBack(hand, arrayposition, tricknumber); //hides card in back of hand
		return tempCard;
	}
}

char findWinnerTrick(Card leadCard, Card player1, Card player2, char leadIs) {
	string leadSuit = leadCard.getsuit(), player1Suit = player1.getsuit(), player2Suit = player2.getsuit(); //assigns suit to local strings
	int leadNum = leadCard.getcardvalue(), player1Num = player1.getcardvalue(), player2Num = player2.getcardvalue(); //assigns card number to local int
	char winnerIs = 'e'; //returns the winner, 'e' allocates memory space for compiler and also helps in debugging

	if (leadIs == 'a') { //user led round
		if (leadSuit == player1Suit && leadSuit == player2Suit) { //if everyone has the leading suit
			if (leadNum >= player1Num && leadNum >= player2Num) { //lead has highest card
				if (leadNum != player1Num && leadNum != player2Num) { //if lead is also winner
					winnerIs = 'a';
				}
				else {
					winnerIs = 'd';
				}
			}
			else { //if lead is not highest card of suit
				if (player1Num <= player2Num) { //player2Num is highest or there is a tie
					if (player1Num != player2Num) {
						winnerIs = 'c';
					}
					else { //tie
						winnerIs = 'd';
					}
				}
				else { //player1 is winner, tie's are dealt with already
					winnerIs = 'b';
				}
			}
		}
		else if (leadSuit == player1Suit) { //if player2 doesnt have suit, but player1 does.
			if (leadNum > player1Num) { //lead wins
				winnerIs = 'a';
			}
			else if (leadNum < player1Num) { //player1 wins
				winnerIs = 'b';
			}
			else { //tie
				winnerIs = 'd';
			}
		}
		else if (leadSuit == player2Suit) { //if player1 doesnt have suit, but player2 does
			if (leadNum > player2Num) { //lead wins
				winnerIs = 'a'; //user
			}
			else if (leadNum < player2Num) { //player2 wins
				winnerIs = 'c'; //comp2
			}
			else { //tie
				winnerIs = 'd';
			}
		}
		else { //no players have suit of leading card
			winnerIs = 'a';
		}
	}
	else if (leadIs == 'b') { //comp1 led round
		if (leadSuit == player1Suit && leadSuit == player2Suit) { //if everyone has the leading suit
			if (leadNum >= player1Num && leadNum >= player2Num) { //lead has highest card
				if (leadNum != player1Num && leadNum != player2Num) { //if lead is also winner
					winnerIs = 'b'; //comp1
				}
				else { //tie
					winnerIs = 'd';
				}
			}
			else { //if lead is not highest card of suit
				if (player1Num <= player2Num) { //player2Num is highest or there is a tie
					if (player1Num != player2Num) {
						winnerIs = 'c'; //comp2
					}
					else { //tie
						winnerIs = 'd';
					}
				}
				else { //player1 is winner, tie's are dealt with already
					winnerIs = 'a'; //user
				}
			}
		}
		else if (leadSuit == player1Suit) { //if player2 doesnt have suit, but player1 does.
			if (leadNum > player1Num) { //lead wins
				winnerIs = 'b'; //comp1
			}
			else if (leadNum < player1Num) { //player1 wins
				winnerIs = 'a'; //user
			}
			else { //tie
				winnerIs = 'd';
			}
		}
		else if (leadSuit == player2Suit) { //if player1 doesnt have suit, but player2 does
			if (leadNum > player2Num) { //lead wins
				winnerIs = 'b'; //comp1
			}
			else if (leadNum < player2Num) { //player2 wins
				winnerIs = 'c'; //comp2
			}
			else { //tie
				winnerIs = 'd';
			}
		}
		else { //if no one has lead suit
			winnerIs = 'b'; //comp1 wins
		}
	}
	else if (leadIs == 'c') { //comp2 led round
		if (leadSuit == player1Suit && leadSuit == player2Suit) { //if everyone has the leading suit
			if (leadNum >= player1Num && leadNum >= player2Num) { //lead has highest card
				if (leadNum != player1Num && leadNum != player2Num) { //if lead is also winner
					winnerIs = 'c'; //comp2
				}
				else { //tie
					winnerIs = 'd';
				}
			}
			else { //if lead is not highest card of suit
				if (player1Num <= player2Num) { //player2Num is highest or there is a tie
					if (player1Num != player2Num) {
						winnerIs = 'b'; //comp1
					}
					else { //tie
						winnerIs = 'd';
					}
				}
				else { //player1 is winner, tie's are dealt with already
					winnerIs = 'a'; //user
				}
			}
		}
		else if (leadSuit == player1Suit) { //if player2 doesnt have suit, but player1 does
			if (leadNum > player1Num) { //lead wins
				winnerIs = 'c'; //comp2
			}
			else if (leadNum < player1Num) { //player1 wins
				winnerIs = 'a'; //user
			}
			else { //tie
				winnerIs = 'd';
			}
		}
		else if (leadSuit == player2Suit) { //if player1 doesnt have suit, but player2 does
			if (leadNum > player2Num) { //lead wins
				winnerIs = 'c'; //comp2
			}
			else if (leadNum < player2Num) { //player2 wins
				winnerIs = 'b'; //comp1
			}
			else { //tie
				winnerIs = 'd';
			}
		}
		else { //no players have suit of lead card
			winnerIs = 'c';
		}
	}
	if (winnerIs == 'e') { //test
		cout << "winnerIs = 'e', check function findWinnerTrick and the condition which caused this before hitting enter"; //test
		system("PAUSE"); //test
	}
	return winnerIs;
}

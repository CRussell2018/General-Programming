// Original code base here - http://argoslair.blogspot.com/2012/04/very-simple-blackjack-game-c.html //
// Modifications, fixes, documentation, & QOL improvements to code base by Craig Russell 10-26-2017  //

#include <iostream>
#include <cstdlib>  // NOT INLCUDED IN ORIGINAL CODE AND NEEDED OR ELSE COMPILER CRASH ERROR //
#include <ctime>
#include <cmath>    // NOT INLCUDED IN ORIGINAL CODE AND NEEDED OR ELSE COMPILER CRASH ERROR //
 
using namespace std;
 
// Global Variables - Had to fix these because original code did not have "CONST" and caused compiler errors //
 
const char *card_num[] = {"2","3","4","5","6","7","8","9","10","Jack","Queen","King","Ace"};
const char *card_type[] = {"Clubs","Diamonds","Spades","Hearts"};
 
 
// Structures //
 
struct cardtype {
    int color;
    int number;
    int value;
};
 
struct decktype {
    bool deck[52];
    int size;
};
 
// Functions //
 
void SeedRandom() {
    time_t tTime;
    time(&tTime);
    srand(tTime);
    rand();
}
 
struct cardtype PickACard(struct decktype &deck) {
    struct cardtype card;
    int randnum = (int) (1.0 * rand() / (RAND_MAX + 1) * deck.size);
    int counter = 0;
    int i;
    for (i=0; i<52; ++i) {
        if (deck.deck[i] == true) {
            ++counter;
        }
        if (counter == randnum+1) {
            break;
        }
    }
    --deck.size;
    deck.deck[i] = false;
    card.number = i / 4;
    card.color = i % 4;
    if (card.number == 10 || card.number == 11) { // Could combine these first two conditions since they all equal "10"? //
        card.value = 10;
    } else if (card.number == 9) {
        card.value = 10; // Fix for "Jack of Spades (1)" - ORIGINAL CODE: card.value=1 //
    } else if (card.number == 12) {
        int CardChoice;
        cout << "This Card is an Ace - Do you want to add 1 or 11 to total?" << endl; 
        cin >> CardChoice;
        if (CardChoice == 1) {
            card.value = 1;}
        else {    
        card.value = 11;} // Original Code DID NOT discern between 1 and 11 value - now it does //
    } else {
        card.value = card.number + 2;
    }
    return card;
}
 
struct decktype DeckInit() {
    struct decktype deck;
    deck.size = 52;
    for (int i=0; i<52; ++i) {
        deck.deck[i] = true;
    }
    return deck;
}
 
char *TextCard(struct cardtype &card) {
    char *str = (char *) malloc (22 * sizeof(char));
    sprintf(str,"%s of %s (%d)",card_num[card.number],card_type[card.color],card.value);
    return str;
}
 
// Main //
 
int main(){
    SeedRandom();
 
    bool IsGameOver = false;
    char WantCard;
 
    int totalvalue = 0;
 
    cout << "Welcome to blackjack!" << endl;
    struct decktype deck = DeckInit();
 
    while (!IsGameOver) {
        bool ValidChoice = false;
        while (!ValidChoice) {
            cout << "Do you want a card? (Y)es / (N)o" << endl;
            cin >> WantCard;
            if (WantCard == 'Y' || WantCard == 'y') {          // Fixed this to accept lowercase and uppercase - formerly uppercase only //
                struct cardtype card = PickACard(deck);
                totalvalue += card.value;
                cout << "You received a " << TextCard(card) << ", current total value at " << totalvalue << "." << endl;
                if (totalvalue > 21) {
                    cout << "Sorry, you have exceeded 21 points and thus lost!" << endl;
                    IsGameOver = true;
                }
                if (totalvalue == 21) {
                    cout << "Congratulations, you have won!" << endl;
                    IsGameOver = true;
                }
                ValidChoice = true;
            } else if (WantCard == 'N' || WantCard == 'n') {   // Fixed this to accept lowercase and uppercase - formerly uppercase only //
                cout << "You stopped prematurely, and since there isn't an opponent, you won :)" << endl;
                ValidChoice = true;
                IsGameOver = true;
            } else {
                cout << "Invalid choice, please try again" << endl; // Added "endl" to prevent this sentence from running on to next text line //
            }                                                       // ORIGINAL: "Invalid choice, please try againDo you want a card? (Y)es / (N)o" //
        }
 
    }
    cout << "The game is over now, thanks for playing!" << endl;
 
 cin.ignore(); // This makes the user hit "ENTER" to exit the program after exiting WHILE loop //
 cin.get();    // This could be turned into Y/N Question to keep the program running instead   //
}
// </ctime></iostream> - OLD CONNECTION CLOSING COMMANDS NOT NEEDED IN JGRASP //

/* OUTPUT
 ----jGRASP exec: D:\Blackjack.exe
Welcome to blackjack!
Do you want a card? (Y)es / (N)o
y
You received a 8 of Diamonds (8), current total value at 8.
Do you want a card? (Y)es / (N)o
y
This Card is an Ace - Do you want to add 1 or 11 to total?
1
You received a Ace of Clubs (1), current total value at 9.
Do you want a card? (Y)es / (N)o
y
This Card is an Ace - Do you want to add 1 or 11 to total?
11
You received a Ace of Hearts (11), current total value at 20.
Do you want a card? (Y)es / (N)o
n
You stopped prematurely, and since there isn't an opponent, you won :)
The game is over now, thanks for playing!

 ----jGRASP: operation complete.
*/
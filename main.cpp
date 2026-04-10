#include <iostream>
#include <string>
#include <vector>
using namespace std;
// TO DO: Card -> Suits, Ranks;
// TO DO: Hand -> Dealer, Player;
// TO DO: Deck -> void Shuffle(), void dealCards(), void addCard(), void countCards() etc..
// TO DO: Functionalities classes(Polimorfism, implementarea claselor virtuale): Hit, Stand, Double Down
// TO DO: Interfata utilizator: Comand Line Interface, gestionarea situatiilor de bust , Scoring,  optiunea de exit sau de a continua jocul dupa incheiere
class Card
{

public:
    struct Suits
    {
        string Spades = "Spades";
        string Hearts = "Hearts";
        string Clubs = "Clubs";
        string Diamonds = "Diamonds";
    };

    enum Ranks : unsigned short int
    {
        TWO = 2,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        NINE,
        TEN,
        JACK = 10,
        QUEEN = 10,
        KING = 10,
        ACE,
    };

protected:
    Ranks rank;
    Suits suit;
};
int main()
{

    return 0;
}

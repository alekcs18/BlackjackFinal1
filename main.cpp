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
    enum Suits
    {
        SPADES,
        HEARTS,
        CLUBS,
        DIAMONDS
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
        JACK,
        QUEEN,
        KING,
        ACE,
    };

protected:
    Ranks rank;
    Suits suit;

public:
    // class constructor
    Card(Suits s, Ranks r) : suit(s), rank(r)
    {
    }

    Ranks getRank() const
    {
        return rank;
    }
    int getValue() const
    {
        switch (rank)
        {
        case Ranks::JACK:
        case Ranks::QUEEN:
        case Ranks::KING:
            return 10;
        case Ranks::ACE:
            return 11;
        default:
            return rank;
        }
    }
    void printCard() const
    // This function will be used to identify Card
    {
        switch (rank)
        {
        case Ranks::JACK:
            cout << "Jack ";
            break;
        case Ranks::QUEEN:
            cout << "Queen ";
            break;
        case Ranks::KING:
            cout << "King ";
            break;
        case Ranks::ACE:
            cout << "Ace ";
            break;
        default:
            cout << rank << " ";
            break;
        }
        cout << "of ";
        switch (suit)
        {
        case Suits::SPADES:
            cout << "Spades";
            break;
        case Suits::CLUBS:
            cout << "Clubs";
            break;
        case Suits::HEARTS:
            cout << "Hearts";
            break;
        case Suits::DIAMONDS:
            cout << "Diamonds";
            break;
        }
    }
};
class Deck
{
};
class Hand
{
};
class Functionalities
{
    // This class will be used for polimorphism for functionalities such as Play, Hit, Stand, DoubleDown etc
public:
    virtual ~Functionalities()
    {
        // deconstructor for virtual class
    }
    virtual void exectute(/*TBD AFTER DECK AND HAND CLASSES*/);
};
class Play : public Functionalities
{
    // TBD
};
class Hit : public Functionalities
{
    // TBD
};
class Stand : public Functionalities
{
};
class DoubleDown : public Functionalities
{
};

int main()
{

    return 0;
}

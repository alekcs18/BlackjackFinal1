#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

// TO DO: Hand -> Dealer, Player; addCard(); getTotalValue(); display(); //We will use this functions to determine players and dealers hand

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
            return static_cast<int>(rank);
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
            cout << static_cast<int>(rank) << " ";
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
private:
    vector<Card> cards;

public:
    void shuffle()
    {
        std::random_device rd;                        // declaration of rng
        std::mt19937 mt(rd());                        // engine used for card shuffling
        std::shuffle(cards.begin(), cards.end(), mt); // actual shuffling
    }

    Card drawCard()
    {
        if (cards.empty())
        {
            throw runtime_error("Deck is empty!");
        }

        Card dealtCard = cards.back(); // This gives out the last card from the deck Ex: vector<int>someint =  {1, 2, 3 ,4}; cout<<someint.back() --> 4
        cards.pop_back();              // this actually removes the card
        return dealtCard;              // returning the dealt card! :D
    }

    Deck() // then we construct the deck using push
    {
        for (int s = 0; s < 4; ++s)
        {
            for (int r = 2; r <= 14; ++r)
            {
                cards.push_back(Card(static_cast<Card::Suits>(s), static_cast<Card::Ranks>(r)));
            }
        }
    }
};
class Hand
{
private:
    vector<Card> cards;

public:
    void addCard(Card c)
    {
        cards.push_back(c);
    }
    int getTotalValue() const
    {
        int total = 0;
        int aceCount = 0;
        for (const auto &card : cards)
        {
            total += card.getValue();               // we also use getValue() function declared in Card class to add the rank of named card
            if (card.getRank() == Card::Ranks::ACE) // check for ace card
            {
                aceCount++;
            }
        }
        while (total > 21 && aceCount) // here we actually implement ace logic: if total > 21 and ace card present we decrement 10 from the total and ace value turns into 1
        {
            total -= 10;
            aceCount--;
        }
        return total;
    }
    void display() // this is used to display the hand!
    {
        for (const auto &card : cards)
        {
            card.printCard();
            cout << ", ";
        }
        cout << "(Total: " << getTotalValue() << ")\n";
    }

    void displayFirstCard() // in bj the player can only see dealers first card untill the end so we need to implement a separate logic
    {
        if (!cards.empty())
        {
            cards[0].printCard();
            cout << ", " << "Hidden Card\n";
        }
    }
    int getCardCount() const // This will be used later to restrict player in some functionality cases
    {
        return static_cast<int>(cards.size());
    }
};
class Functionalities
{
    // This class will be used for polimorphism and will be considered Parent for functionalities such as Play, Hit, Stand, DoubleDown etc.

public:
    virtual ~Functionalities()
    {
        // deconstructor for virtual class
    }
    virtual void execute(Deck &d, Hand &p, Hand &dh) = 0; // d--> dealer p--> player hd -->  dealer hand
};
class Play : public Functionalities
{
    void execute(Deck &d, Hand &p, Hand &dh) override
    {
        d.shuffle();
        p.addCard(d.drawCard());
        dh.addCard(d.drawCard());
        p.addCard(d.drawCard());
        dh.addCard(d.drawCard());
        cout << "Dealers Cards: \n";
        dh.displayFirstCard();
        cout << "Your Cards: \n";
        p.display();
    }
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
    cout << "Welcome to Blackjack!!\n";
    Deck myDeck;                 // we construct the deck
    Hand dealerHand, playerHand; // we construct dealer and player Hand
    Play starter;
    return 0;
};

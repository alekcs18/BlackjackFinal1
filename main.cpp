#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

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
    int cardsRemaining() const
    {
        return cards.size();
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
        d.shuffle(); // shuffling deck
        // the following will deal the initial cards
        p.addCard(d.drawCard());
        dh.addCard(d.drawCard());
        p.addCard(d.drawCard());
        dh.addCard(d.drawCard());
        //
        cout << "\nGame starts now! \n";
        cout << "\nDealers Cards: \n";
        dh.displayFirstCard();
        cout << "\nYour Cards: \n";
        p.display();
    }
};
class Hit : public Functionalities
{
    void execute(Deck &d, Hand &p, Hand &dh) override
    {
        p.addCard(d.drawCard()); // this deals the player another card
        cout << "Your Cards: \n";
        p.display();
    };
};

class DoubleDown : public Functionalities
{
    void execute(Deck &d, Hand &p, Hand &dh) override
    {
        // This option will only be available to the player in the first round
        cout << "Double down called..\n";
        cout << "Your last card: ";
        p.addCard(d.drawCard());
        p.display();
    };
};

void dealerAction(Hand &playerHand, Hand &dealerHand, Deck &myDeck, int &playerScore, int &dealerScore)
{
    // With this function when the player chooses to stand the dealer will begin to make his move
    cout << "Dealers turn..\n";
    dealerHand.display();                   // This displays dealers hand including the hidden card
    while (dealerHand.getTotalValue() < 17) // In BJ dealer must stand on 17 or above
    {
        cout << "Dealer hits..\n";
        dealerHand.addCard(myDeck.drawCard());
        dealerHand.display();
    } // here we use int pScore/dScore to compare the two hands and deal with the following scenarios
    int pScore = playerHand.getTotalValue();
    int dScore = dealerHand.getTotalValue();
    if (dScore > 21)
    {
        cout << "Dealer gone bust..\n";
        cout << "You win!\n";
        playerScore++;
    }
    else if (pScore > dScore)
    {
        cout << "You win!\n";
        playerScore++;
    }
    else if (dScore > pScore)
    {
        cout << "Dealer wins!\n";
        dealerScore++;
    }
    else if (dScore == pScore)
    {
        cout << "It's a Tie!\n";
        // nothing is added to the scoring system
    }
}

class Stand : public Functionalities
{
    // This will act as a wrapper for dealerAction function
private:
    int &pScoreRef;
    int &dScoreRef;

public:
    Stand(int &pS, int &dS) : pScoreRef(pS), dScoreRef(dS) {} // we need a constructor to use this in main
    void execute(Deck &d, Hand &p, Hand &dh) override
    {
        cout << "You stand..\n";
        dealerAction(p, dh, d, pScoreRef, dScoreRef); // This will run the dealerAction function declared earlier to handle the actual Stand functionality
    }
};

int main()
{
    cout << "Welcome to Blackjack!!\n";
    Deck myDeck;
    int playerScore = 0;               // initial player score
    int dealerScore = 0;               // initial dealer score
    Functionalities *action = nullptr; // we'll use this as our action button
    bool gameRunning = true;
    while (gameRunning) // This is the actual game running;
    {
        Hand playerHand, dealerHand;
        cout << "\nScoreboard..\n"
             << "Player's score: " << playerScore << "\nDealer's score: " << dealerScore << endl;
        int choice = 0; // this will be the player's choice

        Play starter;
        action = &starter;
        action->execute(myDeck, playerHand, dealerHand);
        if (playerHand.getTotalValue() == 21) // if player's cards are a blackjack it will grant him/she an instant win
        {
            cout << "You instantly win!\n";
            playerScore++;
        }
        else
        {
            while (true)
            {

                cout << "\n1. Hit\n2. Stand \n3. Double Down\n4. Exit Game\nChoice: ";
                // We'll use 1,2,3,4 as buttons! 1-> Hit, 2-> Stand, 3-> Double Down, 4-> Exit Game
                if (!(cin >> choice)) // This will check if players choice is valid
                {
                    cout << "!Error!\nYou can only choose from 1, 2, 3, 4\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }
                if (choice == 1) // integration of Hit button in Command line + possible Bust or Win scenarios
                {
                    Hit hitCmd;
                    action = &hitCmd;
                    action->execute(myDeck, playerHand, dealerHand);
                    if (playerHand.getTotalValue() > 21)
                    {
                        cout << "Bust, dealer wins!\n";
                        dealerScore++;
                        break;
                    }
                    else if (playerHand.getTotalValue() == 21) // possible blackjack scenario
                    {
                        cout << "Blackjack! You win!\n";
                        playerScore++;
                        break;
                    }
                }
                if (choice == 2) // integration of Stand button in Command line. This will trigger dealerAction function used by our wrapper class
                {
                    Stand standAction(playerScore, dealerScore);
                    action = &standAction;
                    action->execute(myDeck, playerHand, dealerHand);
                    break;
                }
                if (choice == 3) // integration of Double down button in Command line.
                {
                    if (playerHand.getCardCount() != 2) // Checks the condition to see if the player fulfills the condition
                    {
                        cout << "You can only double down in first round!\n";
                        continue;
                    }
                    DoubleDown doubleCmd;
                    action = &doubleCmd;
                    action->execute(myDeck, playerHand, dealerHand);
                    if (playerHand.getTotalValue() > 21) // Possible bust scenario
                    {
                        cout << "Bust, dealer wins!\n";
                        dealerScore++;
                        break;
                    }
                    else // After double down player stands in which case it triggers dealerAction here we use this instead of the wrapper used in Stand button
                    {
                        dealerAction(playerHand, dealerHand, myDeck, playerScore, dealerScore);
                    }
                    break;
                }
                if (choice == 4) // Integration button in case the player wants to quit
                {
                    cout << "\nThank you for playing Blackjack! See you again soon!\n";
                    return 0; // exit code
                }
                else // This is a message displayed for the player in case of typoos
                {
                    std::cout << "Invalid choice. Pick 1, 2, 3 or 4\n";
                }
            }
        }
        char playAgain; // We'll use this for the rematch/continue playing feature
        do              // after round ends the program will enter this loop in which it will ask the player:
        {
            cout << "Do you want to play again?(y/n)\n";
            cin >> playAgain;
            if (playAgain == 'n' || playAgain == 'N') // this is no which means the game will end and program will return 0
            {
                gameRunning = false;
                break;
            }
            if (playAgain == 'y' || playAgain == 'Y') // this will cause another round to start
            {
                gameRunning = true;
                break;
            }
            cout << "Invalid choice! please choose from (y/n)\n"; // If player's choice is invalid it will display this message
        } while (true);
        if (myDeck.cardsRemaining() < 15) // in case the deck is running out of cards the deck will reshuffle
        {
            cout << "Reshuffling deck..\n";
            myDeck = Deck();
        }
    }
    cout << "Goodbye!\n"; // in case the player chooses to no longer play it will display this message
    return 0;
};

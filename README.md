# **BLACKJACK**
## A classic Blackjack game written in C++ that utilizes OOP principles to simulate a casino style card game in which the player competes against the dealer.

### Feature
### 1. Core Mechanics:
- **Standard 52-Card Deck**: Full implementation of suits(Spades, Hearts, Clubs, Diamonds) and ranks (from 2-Ace);
- **Automatic Reshuffling**: The deck automatically reshuffles using an rng in order to prevent "out of card errors";
- **AI dealer**: 
    -**Hidden Card**: Dealer only displays the second card after the player's hand is completed;
    -**House rules**: Dealer can only Hit after the player's hand is completed. Dealer only can hit when <17, otherwise they must stand;
- **Scoring**:
 - **Scoreboard**: The game uses a scoreboard to keep track of the wins of player/dealer;
 - **Ace Card logic**: Ace card value automatically adjusts if the hand total exceeds 21;
 - **Card Evaluation**: All named cards with the exception of Ace card have the value of 10;
### 2. Player Interface:
- **Command line interface**:
 -*User needs to interact with the terminal in order to play the game*:
  -**Hit**: Deals the player another card, adding up to the score (in which case it can be a win/bust scenario);
  -**Stand**: Gives the player the option to stand, player's hand is completed and dealer logic begins to unfold;
  -**Double Down**: Only available to the player in first round, in which case player recieves one last card before being forced to stand;
  -**Exit Game**: Gives the player the posibility to quit the game at any time;
  -**Rematch**: Gives the player the posibility to choose if he/she wants to proceed with another round;
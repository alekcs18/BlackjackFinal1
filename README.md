# **BLACKJACK**
## A classic Blackjack game written in C/C++ that utilizes OOP principles to simulate a casino style card game in which the player competes against the dealer.

### Feature
### Packages:
    -Build System: CMake;
    -Dev Containers;
    -Linux Environment: Debian;

### 1. Core Mechanics:
- **Standard 52-Card Deck**: Full implementation of suits(Spades, Hearts, Clubs, Diamonds) and ranks (from 2-Ace);
- **Automatic Reshuffling**: The deck automatically reshuffles using an rng in order to prevent "out of card errors";
- **AI dealer**: 
    -**House rules**: Dealer can only Hit after the player's hand is completed. Dealer only can hit when <17, otherwise they must stand;
- **Scoring**:
 - **Scoreboard**: The game uses a scoreboard to keep track of the wins of player/dealer;
 - **Ace Card logic**: Ace card value automatically adjusts if the hand total exceeds 21;
 - **Card Evaluation**: All named cards with the exception of Ace card have the value of 10;
### 2. Player Interface:
**Command line interface**:
   *User needs to interact with the terminal in order to play the game*:
- **Functionalities:**
   -  **Hit**: Deals the player another card, adding up to the score (in which case it can be a win/bust scenario);
   -  **Stand**: Gives the player the option to stand, player's hand is completed and dealer logic begins to unfold;
   -  **Double Down**: Only available to the player in first round, in which case player receives one last card before being forced to stand;
   -  **Exit Game**: Gives the player the possibility to quit the game at any time;
   -  **Rematch**: Gives the player the possibility to choose if he/she wants to proceed with another round;
- **Visual:**
   -  **Hidden Card**: Dealer only displays the second card after the player's hand is completed, in order to maintain game integrity;
   -  **Formatted Strings**: Converts enums into readable card names(For instance: "Spades" instead of 0);
   -  **Game State Announcment**: Tracks the game's events, outcomes and informs the player about the games transition:
      - **Dynamic Feedback System**: This includes game results and real-time scoreboard
### 3. Technical Implementation:
**Object Oriented Programing (OOP):** Game uses concepts like: Encapsulation, Inheritance, Polymorphism, etc, in order to make the code easier to maintain and extend core classes:
    - **Pure Virtual Classes:** Class Functionalities is defined as a pure virtual class in order to easily allow extensibilty of new game feature classes, prevents the developer from accidentaly creating a functionality object that does nothing, enables the path to polymorphism.
    - **Inheritance:** Classes like Hit, Stand, DoubleDown all inherit from base class Functionalities, but each have different logic-implementation;
    - **Polymorphism:** With polymorphism we can use the action pointer that acts as a universal controller, making main() look much cleaner and less entangled;
**Standard Template Library (STL):** Game uses a set of libraries in order to implement the core logic:
    - **Containers:** Game uses containers like vectors/strings for text manipulation and general data storage;
    - **The "Random" library and Algorithms:** Game uses this library in order to implement the rng for the deck shuffling;
    - **Input/Output Stream:** Standard streams such as cin/cout are used for terminal interaction;
    - **Limits:** Handles cases in which the player types invalid answers preventing infinite loops;
    - **Error Handling:** Handles errors like: trying to draw from an empty deck;

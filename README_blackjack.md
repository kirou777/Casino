# Blackjack Console Game (C++)

This is a console-based Blackjack game written in C++. The player competes against a dealer using a standard deck of cards.

The project focuses on basic game logic, card handling, randomization, and simple decision-making mechanics.

---

## Features

- Multiple decks support (default: 6 decks)
- Basic Blackjack rules
- Dealer AI (hits until 17 or more)
- Ace handling (counts as 11 or 1)
- Simple hit/stand system

---

## How it works

The game simulates a simplified Blackjack round between a player and a dealer.

1. Deck creation  
   A shoe of multiple decks is generated using `createDeck(int numDecks)`.  
   Each card has a rank and a numerical value used for scoring.

2. Shuffling  
   The deck is shuffled using a Mersenne Twister random engine to ensure unpredictability.

3. Dealing cards  
   Both player and dealer receive initial cards using `drawCard()`.

4. Player turn  
   The player decides whether to:
   - hit (draw another card)
   - stand (end their turn)

   The loop continues until the player stands or busts (>21).

5. Dealer turn  
   The dealer automatically draws cards until reaching at least 17 points.

6. Score calculation  
   The score is calculated using `calculateScore()`:
   - Aces count as 11 or 1 depending on hand value
   - Face cards count as 10

7. Game result  
   The winner is decided by comparing final scores:
   - Bust (>21) loses automatically
   - Higher score wins
   - Equal score results in a draw


## Requirements

- Windows OS (uses `windows.h` and `conio.h`)
- C++ compiler (e.g. MinGW, MSVC)

## How to Compile

Using g++ (MinGW):

```bash
g++ main.cpp -o blackjack
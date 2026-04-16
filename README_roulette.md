# Roulette Console Game (C++)

This is a simple console-based roulette game written in C++. The player starts with a fixed balance and can place different types of bets on randomly generated roulette outcomes.

The game is designed to demonstrate basic programming concepts such as functions, enums, input handling, and simple game logic separation.

---

## Features

The player can place three types of bets:

- Bet on a specific number (0–36)
- Bet on color (red or black)
- Bet on parity (even or odd)

A random number is generated each round, and the result is evaluated against the player's bet.

---

## How it works

The game simulates a simplified roulette system where each round consists of a bet phase and a result phase.

1. Game initialization  
   The player starts with a fixed balance.

2. Betting phase  
   The player chooses:
   - bet amount (deducted immediately from balance)
   - bet type:
     - number (0–36)
     - color (red or black)
     - parity (even or odd)

3. Input validation  
   The program checks if:
   - bet amount does not exceed balance
   - selected number/color/parity is valid

4. Spin phase  
   A random number between 0 and 36 is generated using a pseudo-random function.

5. Result evaluation  
   The outcome is compared with the player’s bet:
   - number bet requires an exact match
   - color is determined based on roulette rules
   - parity ignores 0 (house zero rule)

6. Payout calculation  
   Winnings depend on bet type:
   - number: 35x multiplier
   - color/parity: 2x multiplier

7. Balance update  
   If the player wins, winnings are added to the balance. Otherwise, the bet is lost.

8. Repeat loop  
   The game continues until the player chooses to stop or runs out of money.

## Requirements

- Windows OS (uses `windows.h` and `conio.h`)
- C++ compiler (e.g. MinGW, MSVC)

## How to Compile

Using g++ (MinGW):

```bash
g++ main.cpp -o roulette
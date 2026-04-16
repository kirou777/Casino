#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <cstdlib>
#include <algorithm>
#include <chrono>

using namespace std;

struct Card {
    string rank; // "2", "K", "A"
    string suit; // "Hearts", itd.
    int value;
};

vector<Card> createDeck(int numDecks) {
    vector<Card> deck;
    string ranks[] = {"2","3","4","5","6","7","8","9","10","J","Q","K","A"};
    int values[] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

	for (int d = 0; d < numDecks; d++) {
	    for (int i = 0; i < 13; i++) {
	        for (int j = 0; j < 4; j++) {
	            deck.push_back({ranks[i], "X", values[i]});
	        }
	    }
	}

    return deck;
}

mt19937& rng() {
    static mt19937 g([]{
        random_device rd;
        if (rd.entropy() > 0)
            return mt19937(rd());

        return mt19937(
            chrono::steady_clock::now().time_since_epoch().count()
        );
    }());
    return g;
}

void shuffleDeck(vector<Card>& deck) {
    shuffle(deck.begin(), deck.end(), rng());
}

int calculateScore(vector<Card>& hand) {
    int sum = 0;
    int aces = 0;

    for (auto& card : hand) {
        sum += card.value;
        if (card.rank == "A") aces++;
    }

    while (sum > 21 && aces > 0) {
        sum -= 10;
        aces--;
    }

    return sum;
}

Card drawCard(vector<Card>& deck) {
	if (deck.empty()) {
    cout << "Brak kart w talii!" << endl;
    exit(1);
	}
	
	Card card = deck.back();
	deck.pop_back();
	return card;
}

enum Move { HIT, STAND };

Move playerMove() {
    char decision;

    while (true) {
        cout << "Co robisz? Dobierasz czy stoisz? (h/s): ";
        cin >> decision;

        if (decision == 'h') return HIT;
        if (decision == 's') return STAND;

        cout << "Niepoprawny wybor, sprobuj jeszcze raz.\n";
    }
}

Move dealerMove() {
	return HIT;
}

void showCards(vector<Card>& hand) {
	for (auto& card : hand) {
		cout << card.rank << " ";
	}
	cout << "daje wynik " << calculateScore(hand) << endl;
}

void currentState(vector<Card>& playerHand, vector<Card>& dealerHand) {
	cout << "Gracz: ";
	showCards(playerHand);
	cout << "Krupier: ";
	showCards(dealerHand);
}

int game() {
	
	vector<Card> deck = createDeck(6);
	shuffleDeck(deck);
	bool playerTurn = true;
	
	vector<Card> playerHand, dealerHand;
	
	playerHand.push_back(drawCard(deck));
	dealerHand.push_back(drawCard(deck));
	playerHand.push_back(drawCard(deck));
	
	if (calculateScore(playerHand) == 21) {
		dealerHand.push_back(drawCard(deck));
		currentState(playerHand, dealerHand);
		if(calculateScore(dealerHand) == 21) cout << "Remis!\n";
		else cout << "Blackjack!!! Wygrywa gracz!\n";
		} else {
			currentState(playerHand, dealerHand);
			while (playerTurn) {
				if(playerMove() == HIT) {
					playerHand.push_back(drawCard(deck));
					currentState(playerHand, dealerHand);
				} else {
					playerTurn = false;
				}
			}
			
			while (calculateScore(dealerHand) < 17) {
				dealerHand.push_back(drawCard(deck));
				currentState(playerHand, dealerHand);
			}
			
			if (calculateScore(dealerHand) > 21 || calculateScore(dealerHand) < calculateScore(playerHand)) cout << "Wygrywa gracz!\n";
			else if (calculateScore(dealerHand) == calculateScore(playerHand)) cout << "Remis!\n";
			else cout << "Wygrywa krupier!\n";
		}
	
	return 0;
}

int main() {
	char again = 't';
	
	while (again == 't') {
		game();
		cout << "Gramy dalej? (t/n)" << endl;
		cin >> again;
	}
	
	return 0;
}

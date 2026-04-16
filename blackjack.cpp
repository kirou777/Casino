#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <cstdlib>
#include <algorithm>
#include <chrono>

using namespace std;

// reprezentacja karty
struct Card {
    string rank; // "2", "K", "A"
    string suit; // "Hearts", itd.
    int value;
};

// tworzenie talii kart (numDecks - liczba talii)
vector<Card> createDeck(int numDecks) {
    vector<Card> deck;
    
    string ranks[] = {"2","3","4","5","6","7","8","9","10","J","Q","K","A"};
    int values[] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

	for (int d = 0; d < numDecks; d++) {
	    for (int i = 0; i < 13; i++) {
	        for (int j = 0; j < 4; j++) {
	            deck.push_back({ranks[i], "X", values[i]}); // niedokoñczone - X zamiast faktycznych kolorów
	        }
	    }
	}

    return deck;
}

/*
generator losowoœci (Mersenne Twister)
robiony raz i trzymany statycznie, ¿eby nie resetowa³ siê co wywo³anie
*/
mt19937& rng() {
    static mt19937 g([]{
        random_device rd;
        
        // jeœli system daje sensown¹ entropiê to jej u¿ywamy
        if (rd.entropy() > 0)
            return mt19937(rd());
            
		// czas systemowy w przypadku "udawania losowoœci"
        return mt19937(
            chrono::steady_clock::now().time_since_epoch().count()
        );
    }());
    return g;
}

// tasowanie talii (Fisher-Yates)
void shuffleDeck(vector<Card>& deck) {
    shuffle(deck.begin(), deck.end(), rng());
}

// liczenie wyniku rêki
int calculateScore(vector<Card>& hand) {
    int sum = 0;
    int aces = 0;

	// sprawdzenie liczby asów
    for (auto& card : hand) {
        sum += card.value;
        if (card.rank == "A") aces++;
    }

	// przekroczenie 21, zmiana wartoœci asa na 1
    while (sum > 21 && aces > 0) {
        sum -= 10;
        aces--;
    }

    return sum;
}

// dobieranie karty
Card drawCard(vector<Card>& deck) {
	if (deck.empty()) {
    cout << "Brak kart w talii!" << endl;
    exit(1);
	}
	
	Card card = deck.back();
	deck.pop_back();
	return card;
}

// mo¿liwe ruchy gracza (do dodania reszta mwyborów - split, double etc)
enum Move { HIT, STAND };

// ruch gracza
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

// ruch krupiera - zawsze HIT
Move dealerMove() {
	return HIT;
}

// wyœwietlanie rêki
void showCards(vector<Card>& hand) {
	for (auto& card : hand) {
		cout << card.rank << " ";
	}
	cout << "daje wynik " << calculateScore(hand) << endl;
}

// aktualny stan gry
void currentState(vector<Card>& playerHand, vector<Card>& dealerHand) {
	cout << "Gracz: ";
	showCards(playerHand);
	cout << "Krupier: ";
	showCards(dealerHand);
}

// g³ówna logika (w pó¿niejszym etapie do rozbicia)
int game() {
	
	vector<Card> deck = createDeck(6);
	shuffleDeck(deck);
	bool playerTurn = true, bust = false;
	
	vector<Card> playerHand, dealerHand;
	
	// startowe rozdanie
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
					if(calculateScore(playerHand) >= 21) {
						playerTurn = false;
						bust = true;
					}
					
				} else {
					playerTurn = false;
				}
			}
			
			// tura krupiera - dobiera do 17
			while (!bust && calculateScore(dealerHand) < 17) {
				dealerHand.push_back(drawCard(deck));
				currentState(playerHand, dealerHand);
			}
			
			// sprawdzenie wyników
			if (calculateScore(dealerHand) > 21 || calculateScore(dealerHand) < calculateScore(playerHand) && !bust) cout << "Wygrywa gracz!\n";
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

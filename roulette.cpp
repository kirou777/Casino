#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

enum BetType { NUMBER, COLOR, EVEN_ODD }; // typ zak³adu

// losowanie liczby (0-36)
int spinWheel() {
    return rand() % 37;  
}

// sprawdzenie koloru wylosowanej liczby
string getColor(int number) {
    if (number == 0) return "Zielony";
    if ((number >= 1 && number <= 10) || (number >= 19 && number <= 28)) return (number % 2 == 0) ? "Czarny" : "Czerwony";
    else return (number % 2 == 0) ? "Czerwony" : "Czarny";
}

// funkcja zmieniająca litery w stringu na małe
string lowerCase(string text) {
	for (auto& x : text) x = tolower(x);
	return text;
}

// sprawdza czy zakład na liczbę wygrał
bool checkNumberBet(int chosen, int result) {
    return chosen == result;
}

// sprawdza zakład na kolor
bool checkColorBet(string chosen, string result) {
    return lowerCase(chosen) == result;
}

// sprawdza zakład parzyste / nieparzyste
bool checkEvenOdd(bool chosenEven, int result) {
    if (result == 0) return false;
    return (result % 2 == 0) == chosenEven;
}

// oblicza wypłatę
int calculatePayout(BetType type, int bet) {
    if (type == NUMBER) return bet * 35;
    return bet * 2;
}

int main() {
	setlocale(LC_CTYPE, "Polish");
    srand(time(0));
    
    int balance = 1000;
    char playAgain = 't';

    while (playAgain == 't') {
        cout << "\n=== RULETKA ===\nSaldo: $" << balance << endl;
        
        // pobranie zakładu
        int betAmount;
        cout << "Za jak¹ kwotê chcesz zagraæ: ";
        cin >> betAmount;

        if (betAmount > balance || betAmount <= 0) {
            cout << "Nielegalny zak³ad!\n" << endl;
            continue;
        }
        
        balance -= betAmount;

        // wybranie rodzaju zakładu
        cout << "\nTyp zak³adu:\n1 - Liczba\n2 - Kolor\n3 - Parzyste/Nieparzyste\n> ";
        int betType;
        cin >> betType;

        BetType chosenBet = static_cast<BetType>(betType - 1);
        
        int chosenNumber = -1;
        string chosenColor;
        bool chosenEven = false;

		// pobranie danych dotyczących zakładu
        switch (chosenBet) {
            case NUMBER:
                cout << "Wybierz liczbê od 0 do 36: ";
                cin >> chosenNumber;
                cout << endl;
                if (chosenNumber < 0 || chosenNumber > 36) {
                    cout << "Niepoprawna liczba!" << endl;
                    continue;
                }
                break;
            case COLOR:
                cout << "Wybierz Kolor (Czerwony/Czarny): ";
                cin >> chosenColor;
                cout << endl;
                if (lowerCase(chosenColor) != "czerwony" && lowerCase(chosenColor) != "czarny") {
                    cout << "Niepoprawny kolor!" << endl;
                    continue;
                }
                break;
            case EVEN_ODD:
                char eoChoice;
                cout << "Parzyste czy nieparzyste (p/n): ";
                cin >> eoChoice;
                cout << endl;
                if (eoChoice != 'p' && eoChoice != 'n') {
                    cout << "Niepoprawna wartoœæ!" << endl;
                    continue;
                }
                chosenEven = (eoChoice == 'p');
                break;
        }

        // losowanie liczby
        int result = spinWheel();
        string resultColor = lowerCase(getColor(result));
        bool resultEven = (result % 2 == 0);

        cout << "Wylosowano: " << result << " (" << resultColor << ")\n" << endl;

        bool win = false;
        
        if (chosenBet == NUMBER && checkNumberBet(chosenNumber, result)) {
            win = true;
        }

        if (chosenBet == COLOR && checkColorBet(chosenColor, resultColor)) {
            win = true;
        }

        if (chosenBet == EVEN_ODD && checkEvenOdd(chosenEven, result)) {
            win = true;
        }

		// sprawdzenie wygranej
        if (win) {
        	int winAmount = calculatePayout(chosenBet, betAmount);
            balance += winAmount;
            cout << "Wygra³eœ " << winAmount << "! Posiadasz teraz $" << balance << endl;
        } else cout << "Przegrana. Posiadasz teraz $" << balance << endl;
        
        if (balance <= 0) {
        	cout << "Koniec œrodków.\n";
        	break;
		}

        cout << "Chcesz zagraæ jeszcze raz? (t/n): ";
        cin >> playAgain;
    }

    cout << "Dziêkujemy za grê!" << endl;
    return 0;
}

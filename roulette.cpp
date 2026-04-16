#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

enum BetType { NUMBER, COLOR, EVEN_ODD };

// Losowanie
int spinWheel() {
    return rand() % 37;  
}

// Sprawdzenie koloru wylosowanej liczby
string getColor(int number) {
    if (number == 0) return "Zielony";
    if ((number >= 1 && number <= 10) || (number >= 19 && number <= 28)) return (number % 2 == 0) ? "Czarny" : "Czerwony";
    else return (number % 2 == 0) ? "Czerwony" : "Czarny";
}

// Funkcja zmieniaj¹ca litery w stringu na ma³e
string lowerCase(string text) {
	for (auto& x : text) x = tolower(x);
	return text;
}

int main() {
	setlocale(LC_CTYPE, "Polish");
    srand(time(0));
    int balance = 1000;
    char playAgain = 't';

    while (playAgain == 't') {
        cout << "************Witaj w naszej ruletce!************\n Posiadasz $" << balance << endl;
        
        // Pobranie zak³adu
        int betAmount;
        cout << "Za jak¹ kwotê chcesz zagraæ: ";
        cin >> betAmount;
        cout << endl;

        if (betAmount > balance) {
            cout << "Brak œrodków!" << endl;
            continue;
        }
        
        balance -= betAmount;

        // Wybranie rodzaju zak³adu
        cout << "Wybierz rodzaj zak³adu (1: Liczba, 2: Kolor, 3: Parzyste/Nieparzyste): ";
        int betType;
        cin >> betType;
        cout << endl;

        BetType chosenBet = static_cast<BetType>(betType - 1);
        int chosenNumber = 0;
        string chosenColor;
        bool chosenEven = false;

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

        // Losowanie liczby
        int result = spinWheel();
        string resultColor = lowerCase(getColor(result));
        bool resultEven = (result % 2 == 0);

        cout << "Wylosowano: " << result << " (" << resultColor << ")\n" << endl;

        bool win = false;
        switch (chosenBet) {
            case NUMBER:
                if (result == chosenNumber) {
                    win = true;
                    betAmount *= 35;  // Wygrana w przypadku trafienia liczby
                }
                break;
            case COLOR:
                if (resultColor == chosenColor) {
                    win = true;
                    betAmount *= 2;  // Wygrana w przypadku trafienia koloru
                }
                break;
            case EVEN_ODD:
                if (result != 0 && resultEven == chosenEven) {
                    win = true;
                    betAmount *= 2;  // Wygrana za wskazanie czy liczba bêdzie parzysta/nieparzysta
                }
                break;
        }

        if (win) {
            balance += betAmount;
            cout << "Wygra³eœ " << betAmount << "! Posiadasz teraz $" << balance << endl;
        } else if (balance <= 0) {
            cout << "Skoñczy³y Ci siê pieni¹dze." << endl;
            break;
        } else {
        	cout << "Niestety przegra³eœ. Posiadasz teraz $" << balance << endl;
		}

        cout << "Chcesz zagraæ jeszcze raz? (t/n): ";
        cin >> playAgain;
        cout << endl;
    }

    cout << "Dziêkujemy za grê!" << endl;
    return 0;
}

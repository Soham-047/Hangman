
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <map>

#define MAX_ATTEMPTS 6

using namespace std;

class HangmanGame {
public:
    HangmanGame() {
        srand(static_cast<unsigned int>(time(nullptr)));
        initializeCategories();
        selectCategory();
        secretWord = getRandomWord();
        currentWord = string(secretWord.length(), '_');
        attemptsLeft = MAX_ATTEMPTS;
    }

    void play() {
        cout << "\nYou have " << attemptsLeft << " attempts to guess the word." << endl;

        while (attemptsLeft > 0) {
            displayGameInfo();
            char guess;
            cout << "Guess a letter: ";
            cin >> guess;

            if (isalpha(guess)) {
                guess = tolower(guess);

                if (alreadyGuessed(guess)) {
                    cout << "You've already guessed that letter." << endl;
                } else {
                    bool correct = updateCurrentWord(guess);

                    if (correct) {
                        cout << "Good guess!" << endl;

                        if (currentWord == secretWord) {
                            displayGameInfo();
                            cout << "Congratulations! You guessed the word: " << secretWord << endl;
                            return;
                        }
                    } else {
                        cout << "Incorrect guess." << endl;
                        attemptsLeft--;
                        drawHangman(attemptsLeft);
                    }
                }
            } else {
                cout << "Please enter a valid letter." << endl;
            }
        }

        cout << "\nYou've run out of attempts. The word was: " << secretWord << endl;
    }

private:
    map<string, vector<string>> categories;
    string selectedCategory;
    string secretWord;
    string currentWord;
    int attemptsLeft;
    vector<char> guessedLetters;

    void initializeCategories() {
        categories["Fruits"]   = { "apple", "banana", "cherry", "grape", "kiwi" };
        categories["Animals"]  = { "tiger", "zebra", "lion", "rabbit", "giraffe" };
        categories["Countries"] = { "india", "canada", "brazil", "france", "japan" };
    }

    void selectCategory() {
        cout << "Welcome to Hangman!" << endl;
        cout << "Select a category:" << endl;

        int index = 1;
        vector<string> keys;
        for (const auto& pair : categories) {
            cout << index << ". " << pair.first << endl;
            keys.push_back(pair.first);
            index++;
        }

        int choice;
        do {
            cout << "Enter your choice (1-" << keys.size() << "): ";
            cin >> choice;
        } while (choice < 1 || choice > keys.size());

        selectedCategory = keys[choice - 1];
        cout << "\nCategory selected: " << selectedCategory << endl;
    }

    string getRandomWord() {
        const vector<string>& words = categories[selectedCategory];
        return words[rand() % words.size()];
    }

    bool alreadyGuessed(char letter) {
        return find(guessedLetters.begin(), guessedLetters.end(), letter) != guessedLetters.end();
    }

    bool updateCurrentWord(char letter) {
        bool correct = false;
        for (int i = 0; i < secretWord.length(); i++) {
            if (secretWord[i] == letter) {
                currentWord[i] = letter;
                correct = true;
            }
        }
        guessedLetters.push_back(letter);
        return correct;
    }

    void displayGameInfo() {
        cout << "\nWord: " << currentWord << endl;
        cout << "Attempts left: " << attemptsLeft << endl;
        cout << "Guessed letters: ";
        for (char letter : guessedLetters) {
            cout << letter << " ";
        }
        cout << endl;
    }

    void drawHangman(int attemptsLeft) {
        if (attemptsLeft == 5) {
            cout << "   _____\n  |     |\n  |     O\n  |\n  |\n  |\n  |\n";
        } else if (attemptsLeft == 4) {
            cout << "   _____\n  |     |\n  |     O\n  |     |\n  |\n  |\n  |\n";
        } else if (attemptsLeft == 3) {
            cout << "   _____\n  |     |\n  |     O\n  |    /|\n  |\n  |\n  |\n";
        } else if (attemptsLeft == 2) {
            cout << "   _____\n  |     |\n  |     O\n  |    /|\\\n  |\n  |\n  |\n";
        } else if (attemptsLeft == 1) {
            cout << "   _____\n  |     |\n  |     O\n  |    /|\\\n  |    /\n  |\n  |\n";
        } else if (attemptsLeft == 0) {
            cout << "   _____\n  |     |\n  |     O\n  |    /|\\\n  |    / \\\n  |\n  |\n";
        }
    }
};

int main() {
    HangmanGame game;
    game.play();
    return 0;
}

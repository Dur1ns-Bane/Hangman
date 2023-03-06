/*
Hangman game:    

Play game:
    -Randomly pick 1 word from txt file
    -Also make sure that no word is picked twice
    -Need to output underscores for each letter of that word
    -also need a post for the hangman
    -each wrong guess add a part to the hangman
    -add incorrect guessed letters to the hangman
    -if user guesses letter right add that letter to underscore
    -if input is not a letter then add part to hangman
    -if hangman fully completed add loss to user score, if user gets right add win to score
    -when user wins/losers do press enter to continue and go to menu screen


*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>
#include <vector>
#include <string>

using namespace std;

void displayMenu();
int getOption();
void playGame(vector<string>&, vector<bool>&);
void displayWord(string);
void getGuess(string);
void addWord(vector<string>&, vector<bool>&);
void listWords();
bool containsNum(string);

int main() {

    int option;
    string word;

    //Creates Words file since it doesn't exist
    ofstream create;
    create.open("Words");
    fstream words;
    words.open("Words");

    //Vector for words. Words listed are default for game
    //Vector isUsed checks to see if the words have been used in game
    vector<string> list = {"banana", "orange", "pudding", "dinosaur", "minecraft"};
    vector<bool> isUsed; 

    //Sets size of isUsed to size of list and sets all isUsed values to 0 (false)
    isUsed.resize(list.size(), 0);

    for (int i = 0; i < list.size(); i++) {
        words << list[i] << endl;
    }

    do {
    
        displayMenu();
        option = getOption();
        
        switch (option) {
            case 1:
                playGame(list, isUsed);
                break;

            case 2:
                addWord(list, isUsed);
                break;

            case 3:
                listWords();
                break;

            case 4:
                return 0;
                break;

            default:
                cout << "Please enter an option from 1 - 3: ";
        }
    

    } while (option != 4);

}

void displayMenu() {

    cout << "\n\n\t\tWelcome to the hangman game!\n\n";
    cout << "Options:\n";
    cout << "1. Play hangman\n";
    cout << "2. Add a word\n";
    cout << "3. List words\n";
    cout << "4. Exit game\n\n";
    cout << "Please enter an option number: ";

}

int getOption() {
    int option;

    cin >> option;

    return option;
}

void playGame(vector<string>& list, vector<bool>& isUsed) {

    //Picks random number from 1 to size of the word list vector
    random_device rd;
    uniform_int_distribution<int> rand(1, list.size() - 1);
    int randnum = rand(rd);

    string currentword;
    bool allUsed = true;
    
    //Checks to see if all words are used
    for (int i = 0; i < isUsed.size(); i++) {
        if (isUsed[i] == false) {
            allUsed = false;
            break;
        }
    }

    //Executes inner code if all words not used
    if (!allUsed) {
        //Changes randnum until finds unused word index
        while (isUsed[randnum] == 1) {
            randnum = rand(rd);
        }
    }  

    currentword = list[randnum];

    displayWord(currentword);

}

/*
what need to do:
first display any correctly guessed letters if any
then display underscores under each letter in the current word
any correctly guessed letters display above respoective underscore
display currently guessed letters in one area
under that display incorrect guesses
then prompt the user to input a letter to guess
repeat until hangman complete OR if word is currently guessed
*/

void displayWord(string currentword) {

    for (int i = 0; i < currentword.length(); i++) {
        cout << currentword[i] << " ";
    }

    cout << endl;

    for (int i = 0; i < currentword.length(); i++) {
        if (currentword[i] != ' ') {
            cout << "_ ";
        }
        else {
            cout << "  ";
        }
    }

}

void addWord(vector<string> &list, vector<bool> &isUsed) {
    string input;

    ofstream words;
    words.open("Words");

    cin.ignore();

    do {
        cout << "Enter in a word: ";
        getline(cin, input);
        
        while (containsNum(input) || input.length() < 3) {
            cout << "Enter in a valid word over 3 characters long: ";
            getline(cin, input);
        }

        for (int i = 0; i < input.size(); i++) {
            input[i] = tolower(input[i]);
        }

        if (input == "quit") {
            break;
        }

        list.push_back(input);
        isUsed.push_back(0);

    } while (input != "quit");

    for (int i = 0; i < list.size(); i++) {
        words << list[i];
    }
}

bool containsNum(string input) {

    for (int i = 0; i < input.length(); i++) {
        if (isdigit(input[i])) {
            return true;
        }
    }

    return false;
}

void listWords() {
    ifstream words;
    words.open("Words");
    string input;

    cout << endl;

    while (words >> input) {
        cout << input << endl;
    }

    cout << "\nPress enter to continue";

    cin.ignore();
    cin.get();
}




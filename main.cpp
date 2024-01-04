#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <map>
#include <fstream>
using namespace std;

class game {
private:
    int seed = 1;
    vector<string> suit = {"Hearts", "Clubs", "Diamonds", "Spades"};
    vector<int> rank = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13}; //Ace = 1, Jack = 11, Queen = 12, King = 13
    vector<vector<string>> deck;
    vector<string> temp;
    vector<string> win1Suits;
    map<int, string> coinResult;
    bool coin = false;
    int die = 0;
    int spinner = 0;
    int spunRoll;
    bool win1 = false;
    bool win2 = false;
    bool win2a = false;
    bool win2b = false;
    int suits = 0;
    int runs = 0;
    ofstream Obj1;
    ofstream Obj2;
    ofstream Obj3;
    ofstream Obj4;

public:
    game() {
        initializeDeck();
        shuffleDeck();
        coin = false;
        die = 0;
        spinner = 0;
        win1 = false;
        win2 = false;
        coinResult.insert({0, "Tails" });
        coinResult.insert({1, "Heads" });
        Obj1.open("Coin Results.txt");
        Obj2.open("Die Result.txt");
        Obj3.open("Spinner Result.txt");
        Obj4.open("Card Draw.txt");
        
    }

    void flipCoin() {
        coin = (rand() % 2 == 0);
        cout<<"You Flipped a "<<coinResult[coin]<<endl;
        Obj1<<coin<<endl;
    }

    void rollDie() {
        die = 1 + (rand() % 6);
        cout<<"You rolled a "<<die<<endl;
        Obj2<<die<<endl;
    }

    void spinSpinner() {
        spinner = 3 + (rand() % 8);
        cout<<"You spun a "<<spinner<<endl;
        Obj3<<spinner<<endl;
    }

    void initializeDeck() {
        int index = 0;
        for (int i = 0; i < suit.size(); i++) {
            for (int j = 0; j < rank.size(); j++) {
                vector<string> card = {suit[i], to_string(rank[j])};
                deck.push_back(card);
            }
        }
    }

    void shuffleDeck() {
        shuffle(deck.begin(), deck.end(), default_random_engine(seed));
    }

    void drawCard() {
        temp = {deck.back()[0], deck.back()[1]};
        deck.pop_back();
        cout<<temp[0]<<" "<<temp[1]<<endl;
        Obj4<<temp[0]<<" "<<temp[1]<<endl;
    }

    void play(int choice) {
        cout<<"Let's Play a Game"<<endl;

        if (choice == 1) {
            while (runs<=10) {
                runs++;
                flipCoin();
                if (coin) {
                    rollDie();
                }
                else {
                    spinSpinner();
                }
                drawCard();
                if (stoi(temp[1]) == 11 || stoi(temp[1]) == 12 || stoi(temp[1]) == 13) {
                    if (find(win1Suits.begin(), win1Suits.end(), temp[0]) == win1Suits.end()) {
                        cout<<"You used the "<<temp[0]<<" suit for the treasure hunt win"<<endl;
                        suits++;
                        win1Suits.push_back(temp[0]);
                    }
                    else {
                        cout<<"You have already used the "<<temp[0]<<" suit"<<endl;
                    }
                }
                else {
                    cout<<"You drew a "<<temp[1]<<", you can't use this for your chosen win condition"<<endl;
                }
                if (suits == 4) {
                    cout<<"You collected all 4 suits and completed the treasure hunt"<<endl;
                    win1 = true;
                    cout<<"This took "<<runs<<" attempts"<<endl;
                    break;
                }
            }
        }
    else if (choice == 2) {
        while (runs<=10) {
            runs++;
            flipCoin();
            if (coin) {
                rollDie();
                spunRoll = die;
            }
            else {
                spinSpinner();
                spunRoll = spinner;
            }
            drawCard();

            int cardValue = stoi(temp[1]);
            if (spunRoll >= cardValue && cardValue > 3 && !win2a) {
                cout << "You can use this card for the escape the island win (Number > 3)" << endl;
                win2a = true;
            }
            else if ((cardValue == 11 || cardValue == 12 || cardValue == 13) && !win2b) {
                cout << "You Can use this card " << temp[0] << " " << temp[1] << " for the escape the island win" << endl;
                win2b = true;
            }

            if (win2a && win2b) {
                cout << "Congratulations you Escaped the Island" << endl;
                win2 = true;
                cout<<"It took "<<runs<<" attempts";
                break;
            }
        }
    }
}
};
int main() 
{
    int choice;
    //cout<<"Enter Win Condition Choice (1 or 2): ";
    //cin >> choice;

    game playGame;
    playGame.play(2);
}
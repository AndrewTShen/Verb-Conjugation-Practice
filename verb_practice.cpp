#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <set>
#include <queue>
#include <unordered_map>
#include <random>

using namespace std;

void quizer (vector<pair<string, string> > dataSet, vector<bool> &finishedWords, int &numFinished, int numQuestions, bool repeat) {
    if (numQuestions > dataSet.size()) {
        cout << "Cannot do this many quesitons." << endl;
        return;
    }

    //Quizer
    for (int i = 0; i < numQuestions; i++) {
        if (!repeat) cout << endl << "Question #" << i+1 << "." << endl;
        if (numFinished == dataSet.size()) break;
        if (!(finishedWords[i])) {
            if (repeat) cout << endl << "Repeat for Practice!" << endl;
            string guess;
            cout << dataSet[i].first << endl;
            cout << "Your answer: ";
            cin >> guess;
            if (guess == dataSet[i].second) {

                cout << "Correct!" << endl;
                finishedWords[i] = true;
                numFinished++;
            }
            else {
                cout << "Incorrect :(, the correct answer was: " << dataSet[i].second << endl;
                bool yn = true;
                
                while (yn) {
                    cout << "Type the correct answer: " << endl;
                    cin >> guess;
                    if (guess == dataSet[i].second) yn = false;
                }
            }
        }
    }
}

void menu (vector<pair<string, string> > dataSet) {
    bool another_test = true;
    while (another_test) {
        int option;
        cout << endl << endl;
        cout << "-----------------------MENU-----------------------" << endl;
        cout << "|Select Desired Option:                           | " << endl;
        cout << "|0. Exit                                          |" << endl;
        cout << "|1. Test (Choose number of questions)             |" << endl;
        cout << "|2. Test (All questions)                          |" << endl;
        cout << "|-------------------------------------------------" << endl;
        cout << "|Note #1: if program ever goes into an infinite   |" << endl;
        cout << "|loop use Ctrl+C to escape or close window.       |" << endl;
        cout << "|Note #2: denote a space with an underscore.      |" << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Option: ";
        cin >> option;

        if (option == 0) return;
        else if (option == 1 or option == 2) {
            int numQuestions;
            if (option == 1) {
                cout << "Number of Questions in Test: " << endl;
                cin >> numQuestions;    
            } else if (option == 2) {
                numQuestions = dataSet.size();
            }
            
            random_device rd;
            mt19937 g(rd());
            shuffle(dataSet.begin(), dataSet.end(), g);

            //Exculsion
            vector<bool> finishedWords (dataSet.size(), false);
            int numFinished = 0;
            int repeatCounter = 0;
            while (numFinished != numQuestions) { 
                if (repeatCounter == 0) quizer (dataSet, finishedWords, numFinished, numQuestions, false);
                else quizer (dataSet, finishedWords, numFinished, numQuestions, true);
                repeatCounter++;
            }
        } else {
            cout << "You did not submit a real option!"  << endl;
        }
    }
}

int main() {
    //file input
    string filename;
    cout << "enter set to test: ";
    cin >> filename;
    // filename = "verbs.txt";
    cout << "loading test set ..." << endl;
    cout << "file name: " << filename << endl;
    vector<pair<string, string> > dataSet;

    //Read in File
    ifstream inFile (filename.c_str());  
    if (inFile.fail()) {
        cout << "input failed" << endl;
        return 0;
    }
    while (true) {
        string x, y;
        inFile >> x >> y;

        dataSet.push_back(make_pair(x,y));
        if( inFile.eof() ) break;
    }
    inFile.close();

    menu(dataSet);

    return 0;
    
}


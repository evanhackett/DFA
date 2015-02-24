// Evan Hackett
// Lab 1
// DFA Simulation / Regular Language Recognizer
// DFA.cpp : Defines the entry point for the console application.
// Read the ReadMe file for a description of this program

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>

using namespace std;

void tokenize(string str, vector<string> &tokens);

int _tmain(int argc, _TCHAR* argv[])
{

	string line;
	string token;
	vector<string> finalStates;
	vector<string> alphabet;
	vector<map<string, string>> transitions;
	vector<string> transitionTokens;
	string start;
	string alpha;
	string from;
	string to;
	int index;
	string input;

	cout << "Enter an input file name: ";
	cin >> input;

	ifstream myfile(input);

	if (myfile.is_open()) {
		
		getline(myfile, start);
		cout << "Start state: " << start << endl;

		getline(myfile, line);
		tokenize(line, finalStates);
		cout << "Number of final states: " << finalStates.size() << endl;


		getline(myfile, line);
		tokenize(line, alphabet);
		cout << "Alphabet size: " << alphabet.size() << endl;
		transitions.resize(alphabet.size());
		
		
		while (getline(myfile, line)) {
			transitionTokens.clear();
			tokenize(line, transitionTokens);
			from = transitionTokens[0];
			alpha = transitionTokens[1];
			to = transitionTokens[2];

			// find which index contains "alpha" in the vector "alphabet"
			for (unsigned int i = 0; i < alphabet.size(); ++i) {
				if (alphabet[i] == alpha) {
					index = i;
					break;
				}
			}

			// then map the string "from" to "to", in the map at index "index" in vector "transitions".
			transitions[index].insert(pair<string,string>(from, to));
		}


		myfile.close();
	} else {
		cout << "Unable to open file"; 
	}

	string word;
	bool valid = true;

	while (word != "quit") {
		string currentState = start;
		index = 0;
		cout << endl << "Enter a word (enter 'quit' to exit): ";
		cin >> word;
		

		for (unsigned int i = 0; i < word.length(); ++i) {
			vector<string>::iterator it = find(alphabet.begin(), alphabet.end(), string(1, word[i]));
			if (it != alphabet.end()) {
				index = it - alphabet.begin();
				if (transitions[index].find(currentState) != transitions[index].end()) {
					currentState = transitions[index].at(currentState);
				} else {
					valid = false;
				}

			}
			else {
				cout << word[i] << " is not in the alphabet" << endl;
				valid = false;
			}
		}

		if (valid) {
			// if current state is a final state, word was valid
			vector<string>::iterator it2 = find(finalStates.begin(), finalStates.end(), currentState);
			if (it2 != finalStates.end()) {
				cout << word << " is a valid word!" << endl;
			} else {
				cout << word << " is not a valid word." << endl;
			}

		} else {
			cout << word << " is not a valid word." << endl;
		}

		valid = true; // reset valid
	}

	return 0;
}


void tokenize(string str, vector<string> &tokens) {
	istringstream ss(str);
	while (!ss.eof()) {
	  string x;
	  getline( ss, x, ' ' );
	  tokens.push_back(x);
	}
}

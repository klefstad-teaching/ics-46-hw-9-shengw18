#include "ladder.h"
#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <start_word> <end_word> <word_file>" << endl;
        return 1;
    }

    string start_word = argv[1];
    string end_word = argv[2];
    string word_file = argv[3];

    set<string> word_list;
    try {
        load_words(word_list, word_file);
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    if (start_word == end_word) {
        cerr << "Error: Start and end words must be different." << endl;
        return 1;
    }

    vector<string> ladder = generate_word_ladder(start_word, end_word, word_list);

    if (ladder.empty()) {
        cout << "No word ladder found from " << start_word << " to " << end_word << "." << endl;
    } else {
        cout << "Word ladder from " << start_word << " to " << end_word << ":" << endl;
        print_word_ladder(ladder);
    }

    return 0;
}
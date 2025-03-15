#include "ladder.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " (" << word1 << " -> " << word2 << ")" << endl;
    exit(1);
}

bool is_adjacent(const string& word1, const string& word2) {
    int len1 = word1.size(), len2 = word2.size();
    if (abs(len1 - len2) > 1) return false;

    int i = 0, j = 0, diff_count = 0;
    while (i < len1 && j < len2) {
        if (word1[i] != word2[j]) {
            if (++diff_count > 1) return false;
            if (len1 > len2) i++;
            else if (len1 < len2) j++;
            else { i++; j++; }
        } else {
            i++; j++;
        }
    }
    return true;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    
    set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();

        for (const string& word : word_list) {
            if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
                visited.insert(word);
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);

                if (word == end_word) {
                    return new_ladder;
                }
                
                ladder_queue.push(new_ladder);
            }
        }
    }
    return {}; 
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file) {
        cerr << "Error: Cannot open file " << file_name << endl;
        exit(1);
    }
    string word;
    while (file >> word) {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        word_list.insert(word);
    }
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int len1 = str1.size(), len2 = str2.size();
    if (abs(len1 - len2) > d) return false;

    int i = 0, j = 0, diff_count = 0;
    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            if (++diff_count > d) {
                return false};
            if (len1 > len2) {
                i++;}
            else if (len1 < len2) {
                j++;}
            else {
                i++; j++;}
        } else {
            i++; j++;
        }
    }
    return diff_count + abs(len1 - i - (len2 - j)) <= d;
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
    } else {
        for (size_t i = 0; i < ladder.size(); i++) {
            if (i > 0) cout << " -> ";
            cout << ladder[i];
        }
        cout << endl;
    }
}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");

    vector<string> ladder1 = generate_word_ladder("cat", "dog", word_list);
    cout << "Test 1: "; print_word_ladder(ladder1);

    vector<string> ladder2 = generate_word_ladder("marty", "curls", word_list);
    cout << "Test 2: "; print_word_ladder(ladder2);
}
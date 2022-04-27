#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

string ReadLine() {
    string s;
    getline(cin, s);
    return s;
}

int ReadLineWithNumber() {
    int result = 0;
    cin >> result;
    ReadLine();
    return result;
}

vector<string> SplitIntoWords(const string &text) {
    vector<string> words;
    string word;
    for (const char c: text) {
        if (c == ' ') {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        } else {
            word += c;
        }
    }
    if (!word.empty()) {
        words.push_back(word);
    }

    return words;
}

set<string> ParseStopWords(const string &text) {
    set<string> stop_words;
    for (const string &word: SplitIntoWords(text)) {
        stop_words.insert(word);
    }
    return stop_words;
}

vector<string> SplitIntoWordsNoStop(const string &text, const set<string> &stop_words) {
    vector<string> words;
    for (const string &word: SplitIntoWords(text)) {
        if (stop_words.count(word) == 0) {
            words.push_back(word);
        }
    }
    return words;
}

void AddDocument(vector<vector<string>> &documents, const set<string> &stop_words,
                 const string &document) {
    const vector<string> words = SplitIntoWordsNoStop(document, stop_words);
    documents.push_back(words);
}

set<string> ParseQuery(const string &text, const set<string> &stop_words) {
    vector<string> tmp = SplitIntoWordsNoStop(text, stop_words);
    set<string> query_words(tmp.begin(), tmp.end());
    return query_words;
}

bool MatchDocument(const vector<string> &document_words, const set<string> &query_words) {
    for (auto &tmp: document_words) {
        if (query_words.count(tmp) != 0) {
            return true;
        }
    }
    return false;
}

vector<int> FindDocuments(const vector<vector<string>> &documents, const set<string> &stop_words,
                          const string &query) {
    vector<int> matched_documents;
    set<string> parsed_query = ParseQuery(query, stop_words);
    int tmp = documents.size();
    for (int i = 0; i < tmp; ++i) {
        if (MatchDocument(documents[i], parsed_query)) {
            matched_documents.push_back(i);
        }
    }
    return matched_documents;
}

int main() {
    const string stop_words_joined = ReadLine();
    const set<string> stop_words = ParseStopWords(stop_words_joined);

    vector<vector<string>> documents;
    const int document_count = ReadLineWithNumber();
    for (int document_id = 0; document_id < document_count; ++document_id) {
        AddDocument(documents, stop_words, ReadLine());
    }

    const string query = ReadLine();
    for (const int document_id: FindDocuments(documents, stop_words, query)) {
        cout << "{ document_id = "s << document_id << " }"s << endl;
    }
}

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm> // jeśli potrzebujesz funkcji do algorytmów np. sortowanie
#include <sstream> // Dodane do obsługi strumieni
using namespace std;

void printTable(const vector<vector<char>>& table) {
    for (const auto& row : table) {
        for (char c : row) {
            cout << c;
        }
        cout << '\n';
    }
}

void printPolecenie(const vector<char>& table) {

    for (char c : table) {
        cout << c;
    }
    cout << '\n';
}

void printPolecenie(const vector<string>& table) {

    for (string c : table) {
        cout << c;
    }
    cout << '\n';
}

void moveRowRight(vector<vector<char>>& table, int row, int shift) {
    int n = table[row].size();
    vector<char> newRow(n);
    for (int i = 0; i < n; ++i) {
        newRow[(i + shift) % n] = table[row][i];
    }
    table[row] = newRow;
}

// Funkcja do przesuwania kolumny w dół
void moveColumnDown(vector<vector<char>>& table, int col, int shift) {
    int m = table.size();
    vector<char> newCol(m);
    for (int i = 0; i < m; ++i) {
        newCol[(i + shift) % m] = table[i][col];
    }
    for (int i = 0; i < m; ++i) {
        table[i][col] = newCol[i];
    }
}

// Funkcja do wczytania tablicy z pliku
vector<vector<vector<char>>> loadTableFromFile(const string& filename) {
    ifstream file(filename);
    vector<vector<char>> table;
    vector<vector<char>> questions;
    string line;

    bool dupa=false;
    while (getline(file, line)) {
        if(line.size()<4){
            dupa = true;
            continue;
        }
        vector<char> row(line.begin(), line.end());

        if (!dupa)
        {
            while(row.size()!=92)
            {
                row.push_back(' ');
            }
            table.push_back(row);
        }
        if(dupa) questions.push_back(row);
    }
    vector<vector<vector<char>>> ans;
    ans.push_back(table);
    ans.push_back(questions);
    return ans;
}

//Odwracanie tabeli
vector<vector<char>> rotateTable90(const vector<vector<char>>& table) {
    int m = table.size();    // liczba wierszy
    int n = table[0].size(); // liczba kolumn

    // Tworzymy nową tablicę o wymiarach n x m
    vector<vector<char>> rotated(n, vector<char>(m));

    // Obracamy tablicę
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            rotated[j][m - i - 1] = table[i][j];
        }
    }

    return rotated;
}
//Wczytywanie pojedynczej linii
vector<char> getSingleQuestion(const vector<vector<char>>& data, size_t index) {
    if (index < data.size()) {
        return data[index];  // Zwraca pojedynczą linijkę z questions
    }
    else {
        return {};  // Zwraca pusty wektor, jeśli indeks jest poza zakresem
    }
}

vector<string> splitLineIntoWords(const vector<char>& line) {
    stringstream ss(string(line.begin(), line.end())); // Tworzymy strumień z linii
    string word;
    vector<string> words;

    while (ss >> word) { // Dzielimy strumień na wyrazy
        words.push_back(word);
    }

    return words;
}



int main() {
    // Wczytaj tablicę z pliku
    vector<vector<vector<char>>>  ans = loadTableFromFile("C:\\Users\\radek\\CLionProjects\\hackerrank\\task.txt");
    vector<vector<char>> table = ans[0];
    vector<vector<char>> questions = ans[1];

    for(auto question:questions){
        auto polecenie = splitLineIntoWords(question);
        for(auto it:polecenie) cout<<it<<" ";
        cout<<"\n\n";
        if(polecenie.size()==4 && polecenie[0]=="replace"){
            for(int i=0; i<table.size(); i++){
                for(int j=0; j<table[0].size(); j++){
                    if(table[i][j]==polecenie[1][0]) table[i][j] = polecenie[3][0];
                }
            }
        }
        if(polecenie.size()==3 && polecenie[0]=="clear"){
            if(polecenie[1]=="column"){
                for(int i=0; i<table.size(); i++){
                    table[i].erase(table[i].begin()+ stoi(polecenie[2]));
                }
            }
            if(polecenie[1]=="row"){
                table.erase(table.begin() + stoi(polecenie[2]));
            }
        }
        if(polecenie.size()==3 && polecenie[0]=="mirror"){
            if(polecenie[1]=="column"){
                vector<char> sol;
                for(int i=0; i<table.size(); i++){
                    sol.push_back(table[i][stoi(polecenie[2])]);
                }
                int j=0;
                for(int i=sol.size()-1; i>=0; i--){
                    table[j][stoi(polecenie[2])]= sol[i];
                    j++;
                }
                for(auto it:sol) cout<<it;
            }
            if(polecenie[1]=="row"){
                vector<char> sol;
                for(int i=0; i<table[0].size(); i++){
                    sol.push_back(table[stoi(polecenie[2])][i]);
                }
                int j=0;
                for(int i=sol.size()-1; i>=0; i--){
                    table[stoi(polecenie[2])][j]= sol[i];
                    j++;
                }
                for(auto it:sol) cout<<it;
            }
        }
        if (polecenie.size() == 6)
        {
            if (polecenie[0] == "move" && polecenie[1] == "column")
            {
                if (polecenie[3] == "down")
                {
                    moveColumnDown(table, std::stoi(polecenie[2]), std::stoi(polecenie[5]) % table.size());
                }
                else
                {
                    moveColumnDown(table, std::stoi(polecenie[2]), table.size() - (std::stoi(polecenie[5]) % table.size()));
                }
            }

            if (polecenie[0] == "move" && polecenie[1] == "row")
            {
                if (polecenie[3] == "right")
                {
                    moveRowRight(table, std::stoi(polecenie[2]), std::stoi(polecenie[5]) % table[0].size());
                }
                else
                {
                    moveRowRight(table, std::stoi(polecenie[2]), table[0].size() - (std::stoi(polecenie[5]) % table[0].size()));
                }
            }
        }
        if (polecenie.size() == 2)
        {
            if (polecenie[0] == "rotate")
            {
                if (polecenie[1] == "cw")
                {

                    table=rotateTable90(table);
                }
                if (polecenie[1] == "ccw")
                {

                    table=rotateTable90(rotateTable90(rotateTable90(table)));
                }
            }
        }
        printTable(table);
        cout<<"\n\n";
    }


    return 0;
}

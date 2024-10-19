#include <bits/stdc++.h>
using namespace std;

void printTable(const vector<vector<char>>& table) {
    for (const auto& row : table) {
        for (char c : row) {
            cout << c;
        }
        cout << '\n';
    }
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

    bool dupa = false;
    while (getline(file, line)) {
        if (line.size() < 4) {
            dupa = true;
            continue;
        }
        vector<char> row(line.begin(), line.end());
        if (!dupa) table.push_back(row);
        if (dupa) questions.push_back(row);
    }
    vector<vector<vector<char>>> ans;
    ans.push_back(table);
    ans.push_back(questions);
    return ans;
}

int main() {
    // Wczytaj tablicę z pliku
    vector<vector<vector<char>>>  ans = loadTableFromFile("./task.txt");
    vector<vector<char>> table = ans[0];
    vector<vector<char>> questions = ans[1];

    // Przykładowe operacje
//    moveRowRight(table, 0, 5);   // Przesuń wiersz 0 w prawo o 5
//    moveColumnDown(table, 3, 3); // Przesuń kolumnę 3 w dół o 3

    // Wyświetl tablicę po przekształceniach
    printTable(questions);

    return 0;
}

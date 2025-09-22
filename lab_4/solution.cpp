
#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <numeric> // needed for accumulate in compute_score
#include <random>
using namespace std;

void write_board_csv(const vector<vector<int>>& board, bool first) {
    ios_base::openmode mode = ios::app;
    if (first) mode = ios::trunc;
    ofstream fout("game_output.csv", mode);
    if (!fout) return;
    for (int r=0;r<4;r++){
        for (int c=0;c<4;c++){
            fout<<board[r][c];
            if (!(r==3 && c==3)) fout<<",";
        }
    }
    fout<<"\n";
}

void print_board(const vector<vector<int>>& board, bool first) {
    for (const auto &row : board) {
        for (auto val : row) {
            if (val == 0) cout << ".\t";
            else cout << val << "\t";
        }
        cout << "\n";
    }
    cout << endl;
    write_board_csv(board, first);
}


void spawn_tile(std::vector<std::vector<int>>& board) {
    std::vector<int> rows;
    std::vector<int> cols;

    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            if (board[r][c] == 0) {
                rows.push_back(r);
                cols.push_back(c);
            }
        }
    }
    if (rows.empty()) return;

    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<> cellDist(0, rows.size() - 1);
    int idx = cellDist(gen);
    int row = rows[idx];
    int col = cols[idx];

    std::uniform_int_distribution<> tileDist(1, 10);
    int value = (tileDist(gen) == 1) ? 4 : 2;

    board[row][col] = value;
}


// TODO: implement using STL algorithms
bool move_left(vector<vector<int>>& board){
    bool moved = false;
    for (int r = 0; r < 4; ++r) {
        // extract non-zero values
        vector<int> vals;
        for (int c = 0; c < 4; ++c) if (board[r][c] != 0) vals.push_back(board[r][c]);

        // merge
        vector<int> merged;
        for (size_t i = 0; i < vals.size(); ) {
            if (i + 1 < vals.size() && vals[i] == vals[i+1]) {
                merged.push_back(vals[i] * 2);
                i += 2;
            } else {
                merged.push_back(vals[i]);
                i += 1;
            }
        }

        // write back and pad with zeros
        vector<int> newrow(4, 0);
        for (size_t c = 0; c < merged.size() && c < 4; ++c) newrow[c] = merged[c];

        if (newrow != board[r]) {
            board[r] = newrow;
            moved = true;
        }
    }
    return moved;
}

bool move_right(vector<vector<int>>& board){
    bool moved = false;
    for (int r = 0; r < 4; ++r) {
        // extract non-zero values from right to left
        vector<int> vals;
        for (int c = 3; c >= 0; --c) if (board[r][c] != 0) vals.push_back(board[r][c]);

        // merge (toward right, i.e., merging adjacent equal values in vals)
        vector<int> merged;
        for (size_t i = 0; i < vals.size(); ) {
            if (i + 1 < vals.size() && vals[i] == vals[i+1]) {
                merged.push_back(vals[i] * 2);
                i += 2;
            } else {
                merged.push_back(vals[i]);
                i += 1;
            }
        }

        // write back reversed (fill from right)
        vector<int> newrow(4, 0);
        for (size_t idx = 0; idx < merged.size() && idx < 4; ++idx) {
            newrow[3 - idx] = merged[idx];
        }

        if (newrow != board[r]) {
            board[r] = newrow;
            moved = true;
        }
    }
    return moved;
}

bool move_up(vector<vector<int>>& board){
    bool moved = false;
    for (int c = 0; c < 4; ++c) {
        // collect column top->bottom
        vector<int> vals;
        for (int r = 0; r < 4; ++r) if (board[r][c] != 0) vals.push_back(board[r][c]);

        // merge toward top
        vector<int> merged;
        for (size_t i = 0; i < vals.size(); ) {
            if (i + 1 < vals.size() && vals[i] == vals[i+1]) {
                merged.push_back(vals[i] * 2);
                i += 2;
            } else {
                merged.push_back(vals[i]);
                i += 1;
            }
        }

        // write back and pad with zeros
        for (int r = 0; r < 4; ++r) {
            int newval = (r < (int)merged.size()) ? merged[r] : 0;
            if (board[r][c] != newval) {
                board[r][c] = newval;
                moved = true;
            }
        }
    }
    return moved;
}

bool move_down(vector<vector<int>>& board){
    bool moved = false;
    for (int c = 0; c < 4; ++c) {
        // collect column bottom->top
        vector<int> vals;
        for (int r = 3; r >= 0; --r) if (board[r][c] != 0) vals.push_back(board[r][c]);

        // merge toward bottom
        vector<int> merged;
        for (size_t i = 0; i < vals.size(); ) {
            if (i + 1 < vals.size() && vals[i] == vals[i+1]) {
                merged.push_back(vals[i] * 2);
                i += 2;
            } else {
                merged.push_back(vals[i]);
                i += 1;
            }
        }

        // write back reversed (fill from bottom)
        for (int r = 3; r >= 0; --r) {
            int idx = 3 - r; // 0 for r=3, 1 for r=2...
            int newval = (idx < (int)merged.size()) ? merged[idx] : 0;
            if (board[r][c] != newval) {
                board[r][c] = newval;
                moved = true;
            }
        }
    }
    return moved;
}

// TODO: compute score by summing board values
int compute_score(const vector<vector<int>>& board) {
    int sum = 0;
        for (const auto& row : board)
            for (int v : row) 
                sum += v;
    return sum;
}

int main(){
    srand(time(nullptr));
    vector<vector<int>> board(4, vector<int>(4,0));
    spawn_tile(board);
    spawn_tile(board);

    stack<vector<vector<int>>> history;
    bool first=true;

    while(true){
        print_board(board, first);
        first=false;
        cout << "Score: " << compute_score(board) << "\n";
        cout<<"Move (w=up, a=left, s=down, d=right), u=undo, q=quit: ";
        char cmd;
        if (!(cin>>cmd)) break;
        if (cmd=='q') break;

        if (cmd=='u') {
            // TODO: Implement undo handling here using the history stack
            if (history.empty()) {
                cout << "Nothing to undo\n";
            } else {
                board = history.top();
                history.pop();
            }
            print_board(board,false);
            continue;
        }

        vector<vector<int>> prev = board;
        bool moved=false;
        if (cmd=='a') moved=move_left(board);
        else if (cmd=='d') moved=move_right(board);
        else if (cmd=='w') moved=move_up(board);
        else if (cmd=='s') moved=move_down(board);

        if (moved) {
            // TODO: push prev to history stack for undo
            history.push(prev);
            spawn_tile(board);
        }
    }
    return 0;
}

#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>

using namespace std;

// Forward declaration
int compute_score(const std::vector<std::vector<int>>& board);

#include <iterator>

// TODO: Compress a row: remove zeros, pad with zeros at the end
std::vector<int> compress_row(const std::vector<int>& row) {
    std::vector<int> out;
    out.reserve(4);
    for (int v : row) if (v != 0) out.push_back(v);
    while ((int)out.size() < 4) out.push_back(0);
    return out;
}

// TODO: Merge a row (assumes already compressed)
std::vector<int> merge_row(std::vector<int> row) {
    std::vector<int> out;
    out.reserve(4);
    for (size_t i = 0; i < row.size(); ) {
        if (i + 1 < row.size() && row[i] == row[i+1] && row[i] != 0) {
            out.push_back(row[i] * 2);
            i += 2;
        } else if (row[i] != 0) {
            out.push_back(row[i]);
            i += 1;
        } else {
            // shouldn't hit zeros if row is compressed, but guard
            i += 1;
        }
    }
    while ((int)out.size() < 4) out.push_back(0);
    return out;
}




void write_board_csv(const vector<vector<int>>& board, bool first, const string& stage) {
    ios_base::openmode mode = ios::app;
    if (first) mode = ios::trunc;
    ofstream fout("game_output.csv", mode);
    if (!fout) return;

    // Write stage identifier
    fout << stage << ",";

    // Write board data
    for (int r=0;r<4;r++){
        for (int c=0;c<4;c++){
            fout<<board[r][c];
            if (!(r==3 && c==3)) fout<<",";
        }
    }
    fout<<"\n";
}

void read_board_csv(vector<vector<int>>& board) {
    ifstream fin("game_input.csv");

    string line;
    int r = 0;
    while (getline(fin, line) && r < 4) {
        stringstream ss(line);
        string cell;
        int c = 0;
        while (getline(ss, cell, ',') && c < 4) {
            try {
                board[r][c] = stoi(cell);
            } catch (...) {
                board[r][c] = 0;  // Default to 0 for invalid input
            }
            c++;
        }
        r++;
    }
}

void print_board(const vector<vector<int>>& board) {
    for (const auto &row : board) {
        for (auto val : row) {
            if (val == 0) cout << ".\t";
            else cout << val << "\t";
        }
        cout << "\n";
    }
    cout << "\n";
    cout << "Score: " << compute_score(board) << "\n";
}

void spawn_tile(std::vector<std::vector<int>>& board) {
    std::vector<std::pair<int,int>> empty;
    for (int r = 0; r < 4; r++)
        for (int c = 0; c < 4; c++)
            if (board[r][c] == 0) empty.emplace_back(r,c);

    if (empty.empty()) return;

    static std::mt19937 gen(42);  // Fixed seed for deterministic behavior
    std::uniform_int_distribution<> pos_dist(0, empty.size()-1);
    std::uniform_int_distribution<> val_dist(1, 10);

    auto [r, c] = empty[pos_dist(gen)];
    board[r][c] = (val_dist(gen) == 1 ? 4 : 2); // 10% chance of 4
}

// TODO: Implement move_left using compress_row and merge_row
bool move_left(std::vector<std::vector<int>>& board) {
    bool moved = false;
    // TODO: For each row:
    //   1. Compress the row (remove zeros)
    //   2. Merge adjacent equal tiles
    //   3. Check if the row changed
    for (int r = 0; r < 4; ++r) {
        std::vector<int> compressed = compress_row(board[r]);
        std::vector<int> merged = merge_row(compressed);
        if (merged != board[r]) {
            board[r] = merged;
            moved = true;
        }
    }
    return moved;
}

// TODO: Implement move_right (hint: reverse, compress, merge, reverse)
bool move_right(std::vector<std::vector<int>>& board) {
    bool moved = false;
    // TODO: Similar to move_left but with reversal
    for (int r = 0; r < 4; ++r) {
        std::vector<int> row = board[r];
        std::reverse(row.begin(), row.end());
        std::vector<int> compressed = compress_row(row);
        std::vector<int> merged = merge_row(compressed);
        std::reverse(merged.begin(), merged.end());
        if (merged != board[r]) {
            board[r] = merged;
            moved = true;
        }
    }
    return moved;
}

// TODO: Implement move_up (work with columns)
bool move_up(std::vector<std::vector<int>>& board) {
    bool moved = false;
    // TODO: Extract column, compress, merge, write back
    for (int c = 0; c < 4; ++c) {
        std::vector<int> col(4);
        for (int r = 0; r < 4; ++r) col[r] = board[r][c];
        std::vector<int> compressed = compress_row(col);
        std::vector<int> merged = merge_row(compressed);
        for (int r = 0; r < 4; ++r) {
            if (board[r][c] != merged[r]) {
                board[r][c] = merged[r];
                moved = true;
            }
        }
    }
    return moved;
}

// TODO: Implement move_down (columns with reversal)
bool move_down(std::vector<std::vector<int>>& board) {
    bool moved = false;
    // TODO: Similar to move_up but with reversal
    for (int c = 0; c < 4; ++c) {
        std::vector<int> col(4);
        for (int r = 0; r < 4; ++r) col[r] = board[r][c];
        std::reverse(col.begin(), col.end());
        std::vector<int> compressed = compress_row(col);
        std::vector<int> merged = merge_row(compressed);
        std::reverse(merged.begin(), merged.end());
        for (int r = 0; r < 4; ++r) {
            if (board[r][c] != merged[r]) {
                board[r][c] = merged[r];
                moved = true;
            }
        }
    }
    return moved;
}



int compute_score(const std::vector<std::vector<int>>& board) {
    int score = 0;
    for (const auto& row : board)
        for (int val : row)
            score += val;
    return score;
}


int main(){
    vector<vector<int>> board(4, vector<int>(4,0));

    // Read initial board from CSV
    read_board_csv(board);

    stack<vector<vector<int>>> history;
    bool first=true;

    while(true){
        print_board(board);
        if (first) {
            write_board_csv(board, true, "initial");
            first = false;
        }

        cout<<"Move (w=up, a=left, s=down, d=right), u=undo, q=quit: ";
        char cmd;
        if (!(cin>>cmd)) break;
        if (cmd=='q') break;

        if (cmd=='u') {
            if (history.empty()) {
                // nothing to undo
                write_board_csv(board, false, "invalid");
            } else {
                board = history.top();
                history.pop();
                print_board(board);
                write_board_csv(board, false, "undo");
            }
            continue;
        }

        vector<vector<int>> prev = board;
        // compute the effect of the move on a temporary board
        vector<vector<int>> tmp = board;
        bool moved = false;
        if (cmd=='a') moved = move_left(tmp);
        else if (cmd=='d') moved = move_right(tmp);
        else if (cmd=='w') moved = move_up(tmp);
        else if (cmd=='s') moved = move_down(tmp);

        if (!moved) {
            // invalid move, log and do not spawn
            write_board_csv(board, false, "invalid");
        } else {
            // valid move: log the merge board (tmp), then spawn and log spawn
            write_board_csv(tmp, false, "merge");
            history.push(prev);
            spawn_tile(tmp);
            write_board_csv(tmp, false, "spawn");
            board = tmp;
        }
    }
    return 0;
}

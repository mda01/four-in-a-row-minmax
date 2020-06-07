#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-signed-bitwise"

#include "Board.h"

Board::Board() : Board(black) {}

Board::Board(Color playerColor) : player(playerColor), enemy(otherColor(player)) {
    turn = black;
    board[0] = 0;
    board[1] = 0;
    winner = none;
}

void Board::askMove() {
    int col = -1;
    while (!playOnce(col - 1))
        cin >> col;
}

bool Board::playOnce(int col) {
    if (col < 0 || col >= WIDTH)
        return false;
    uint64_t boardC = board[turn];
    uint64_t boardO = board[otherColor(turn)];
    for (int i = col * WIDTH; i < col * WIDTH + HEIGHT; i++) {
        if (((boardC >> i) & 1) == 0 && ((boardO >> i) & 1) == 0) {
            uint64_t place = 1;
            board[turn] |= (place << i);
            changeTurn();
            return true;
        }
    }
    return false;

}


void Board::changeTurn() {
    turn = otherColor(turn);
}

bool Board::isOver() {
    if (hasWon(black) || hasWon(white))
        return true;
    uint64_t full = board[white] | board[black];
    for (int row = HEIGHT - 1; row >= 0; row--) {
        for (int col = 0; col < WIDTH; col++) {
            if (((full >> (col * WIDTH + row)) & 1) == 0) {
                return false;
            }
        }
    }
    return true;
}

int Board::heuristic(const Color color) const {
    // TODO
    return score(color);
}

int Board::heuristic() const {
    return heuristic(turn);
}

int Board::score(const Color color) const {
    switch (winner) {
        case none:
            return 0;
        case white:
            return color == white ? 100 : -100;
        case black:
            return color == black ? 100 : -100;
        default:
            cout << "Invalid color" << endl;
            exit(100);
    }
}

int Board::score() const {
    return score(turn);
}

bool Board::hasWon(Color color) {
    uint64_t boardC = board[color];
    uint64_t y = boardC & (boardC >> HEIGHT);
    if ((y & (y >> 2 * HEIGHT)) != 0) {
        winner = color;
        return true;
    }
    y = boardC & (boardC >> H1);
    if ((y & (y >> 2 * H1)) != 0) {
        winner = color;
        return true;
    }
    y = boardC & (boardC >> H2);
    if ((y & (y >> 2 * H2)) != 0) {
        winner = color;
        return true;
    }
    y = boardC & (boardC >> 1);
    if ((y & (y >> 2)) != 0) {
        winner = color;
        return true;
    }
    return false;
}

Color Board::getPlayer() const {
    return player;
}

Color Board::getTurn() const {
    return turn;
}


vector<Node> Board::children() const {
    vector<Node> res;
    for (int i = 0; i < WIDTH; i++) {
        Board b = clone();
        if (b.playOnce(i)) {
            Node node{b, i};
            res.push_back(node);
        }
    }
    return res;
}

void Board::printBoard() const {
    for (int i = 1; i <= WIDTH; i++) {
        cout << i << "\t";
    }
    cout << endl;

    uint64_t whiteB = board[white];
    uint64_t blackB = board[black];
    for (int row = HEIGHT - 1; row >= 0; row--) {
        for (int col = 0; col < WIDTH; col++) {
            if (((whiteB >> (col * WIDTH + row)) & 1) == 1) {
                cout << "W";
            } else if (((blackB >> (col * WIDTH + row)) & 1)) {
                cout << "B";
            } else cout << ".";
            cout << "\t";
        }
        cout << endl;
    }
    for (int i = 1; i <= WIDTH; i++) {
        cout << i << "\t";
    }
    cout << endl;
}


Board Board::clone() const {
    Board b(player);
    b.board[0] = board[0];
    b.board[1] = board[1];
    b.turn = turn;
    b.winner = winner;
    return b;
}

#pragma clang diagnostic pop
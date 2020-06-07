#include "Board.h"
#include "MinMax.h"

int main() {
    Board b(black);
    MinMax m(white);
    vector<int> actions{};
    b.printBoard();
    while (!b.isOver()) {
        if (b.getPlayer() == b.getTurn()) {
            b.askMove();
            b.printBoard();
        } else {
            int conf = m.alpha_beta(b, actions);
            b.playOnce(actions.front());
            cout << "conf: " << conf << " col: " << (actions.front() + 1) << endl;
            actions.erase(actions.begin());
            for (auto act : actions) {
                cout << (act + 1) << " ";
            }
            cout << endl;
            b.printBoard();
        }
    }
    if (b.hasWon(white)) {
        cout << "Winner: white";
    } else if (b.hasWon(black)) {
        cout << "Winner: black";
    } else {
        cout << "Tie";
    }
    cout << endl;
    return 0;
}

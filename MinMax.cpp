#include "MinMax.h"

MinMax::MinMax(Color color) {
    aiColor = color;

    for (auto &randomNumber : randomNumbers) {
        for (long &j : randomNumber) {
            j = random();
        }
    }
}

int MinMax::alpha_beta(Board state, vector<int> &actions) {
    actions.clear();
    return negamax(state, MAX_DEPTH, INT32_MIN, INT32_MAX, actions, aiColor);
}

int MinMax::negamax(Board state, const int depth, int alpha, int beta, vector<int> &actions, const Color color) {
    const long hash = zobristHash(state);
    const int alphaOrig = alpha;
    const auto iterator = transpositionTable.find(hash);
    int hDepth = 10000;
    if (iterator != transpositionTable.end()) {
        Entry entry = iterator->second;
        hDepth = entry.depth;
        if (entry.depth >= depth) {
            if (entry.flag == EXACT)
                return entry.value;
            else if (entry.flag == LOW)
                alpha = max(alpha, entry.value);
            else if (entry.flag == HIGH)
                beta = min(beta, entry.value);

            if (alpha >= beta)
                return entry.value;
        }
    }

    if (state.isOver()) return state.score();
    if (depth == 0) return state.heuristic();
    const auto children = state.children();
    int v = -10000;
    for (Node s : children) {
        vector<int> tmp;
        const int v_prime = -negamax(s.board, depth - 1, -beta, -alpha, tmp, otherColor(color));
        if (v_prime > v) {
            v = v_prime;
            actions = tmp;
            actions.insert(actions.begin(), s.nextAction);
        }
        alpha = max(alpha, v);
        if (alpha >= beta)
            break;
    }
    if (depth > hDepth) {
        Entry e{};
        e.value = v;
        if (v <= alphaOrig)
            e.flag = HIGH;
        else if (v >= beta)
            e.flag = LOW;
        else
            e.flag = EXACT;
        e.depth = depth;
        transpositionTable.insert({hash, e});
    }
    return v;
}

long MinMax::zobristHash(const Board &state) const {
    long res = 0;
    uint64_t blackB = state.board[0];
    uint64_t whiteB = state.board[1];
    for (int i = 0; i < 48; i++) {
        if (((blackB >> i) & 1) == 1) {
            res ^= randomNumbers[0][i];
        }
        if (((whiteB >> i) & 1) == 1) {
            res ^= randomNumbers[1][i];
        }
    }
    return res;
}

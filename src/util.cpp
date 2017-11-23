#include "util.h"

void magic_insert(int score, string player, vector<int>& scores, vector<string>& players) {
    for (string::size_type i = 0; i < scores.size(); ++i) {
        if (scores.at(i) <= score) {
            for (string::size_type j = scores.size() - 1; j > i; --j) {
                scores.at(j) = scores.at(j - 1);
                players.at(j) = players.at(j - 1);
            }
            scores.at(i) = score;
            players.at(i) = player;
            break;
        }
    }
}

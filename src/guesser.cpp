#include "guesser.h"

#include <cstdint>

int Guesser::getGuessCount() { return this->ctx.guess_count; }

ReturnType Guesser::check_coordinates(size_t x, size_t y, Board &board) {
    const int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    auto grid = board.get_grid();
    auto rows = grid->size();
    auto cols = grid->at(0)->size();

    if (x >= rows || y >= cols) {
        return ReturnType::bad_guess;
    }

    if (grid->at(x)->at(y) == 1) {
        return ReturnType::hit;
    }

    for (const auto &dir : directions) {
        size_t adjX = x + dir[0];
        size_t adjY = y + dir[1];

        if (adjX > 0 && adjX < rows &&
            adjY > 0 && adjY < cols) {
            if ((*grid)[adjX]->at(adjY) == 1) {
                return ReturnType::near_miss;
            }
        }
    }
    return ReturnType::miss;
}

ReturnType Guesser::guess(size_t x, size_t y, Board &board) {
    this->ctx.guess_count += 1;
    return this->check_coordinates(x, y, board);
}

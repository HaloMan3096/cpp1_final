#include <iostream>
#include <stdexcept>

#include "solver.h"

class ExampleSolver : public Solver {
   public:
    void solve(Board &board) override;
};

// Sample Implemeneation
void ExampleSolver::solve(Board &board) {
    for (size_t i = 0; i < board.getX(); i++) {
        for (size_t j = 0; j < board.getY(); j++) {
            guess(i, j, board);
        }
    }
}

class UserSolver : public Solver {
   public:
    void solve(Board &board) override;
};

void UserSolver::solve(Board &board) {
    // Your Implementation goes here
    int counter = 0, nearCount = 0, hitCount = 0;
    for (size_t i = 0; i < board.getX(); i += 3) {
        for (size_t j = 0; j < board.getY(); j++) {
            ReturnType t = guess(i, j, board);
            switch (t) {
                case bad_guess: // Bad Guess (Out of Bounds)
                    throw std::invalid_argument("Out of bounds");
                case hit:
                    std::cout << "Hit at X: " << i << " Y: " << j << std::endl;
                hitCount++;
                break;
                case miss:
                    counter++;
                break;
                case near_miss: // (One is nearby)
                    nearCount++;
                auto g1 = guess(i + 1, j, board);
                auto g2 = guess(i - 1, j, board);
                if (g1 == hit) {
                    std::cout << "Hit From right near miss at X: " << i + 1 << " Y: " << j << std::endl;
                    hitCount++;
                }
                if (g2 == hit) {
                    std::cout << "Hit From left near miss at X: " << i - 1 << " Y: " << j << std::endl;
                    hitCount++;
                }
                break;
            }
        }
    }
    std::cout << "Hit: " << hitCount << std::endl;
    std::cout << "Miss: " << counter << std::endl;
    std::cout << "Near Miss: " << nearCount << std::endl;
}

int main() {
    Board b = Board(1000, 1000, 5);

    ExampleSolver es;
    es.solve(b);

    UserSolver us;
    us.solve(b);

    if (es.score() < us.score()) {
        throw std::runtime_error("Not Efficient Enough");
    }
}

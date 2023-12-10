#include "BlockFall.h"
#include "GameController.h"
#include <iostream>

int main(int argc, char **argv) {
    // Create a BlockFall instance

    string gravity_mode("GRAVITY_ON"); //argv[4]
    BlockFall game("grid.dat", "blocks.dat", (gravity_mode == "GRAVITY_ON"), "leaderboard.txt", "Deneme1");
    //BlockFall game(argv[1], argv[2], (gravity_mode == "GRAVITY_ON"), argv[5], argv[6]);

    // Create a GameController instance
    GameController controller;

    // Play
    controller.play(game, "commands.dat"); //argv[3]

    return 0;
}

//   g++ -std=c++11 main.cpp Block.h BlockFall.h BlockFall.cpp GameController.h GameController.cpp LeaderboardEntry.h LeaderboardEntry.cpp Leaderboard.h Leaderboard.cpp -o blockfall
//   ./blockfall grid.dat blocks.dat commands.dat GRAVITY_ON leaderboard.txt BlockBuster
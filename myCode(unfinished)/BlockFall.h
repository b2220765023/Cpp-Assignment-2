#ifndef BLOCKFALL_H
#define BLOCKFALL_H

#define occupiedCellChar "██"
#define unoccupiedCellChar "▒▒"

#include <vector>
#include <string>

#include "Block.h"
#include "LeaderboardEntry.h"
#include "Leaderboard.h"

using namespace std;

class BlockFall {
public:
    BlockFall(std::string grid_file_name, std::string blocks_file_name, bool gravity_mode_on, const std::string &leaderboard_file_name,
              const std::string &player_name);
    ~BlockFall();

    int rows;
    int cols;
    std::vector<std::vector<int>> grid;
    std::vector<std::vector<bool>> power_up;
    Block* initial_block = nullptr;
    Block* active_rotation = nullptr;
    bool gravity_mode_on = false;
    unsigned long current_score = 0;
    std::string leaderboard_file_name;
    std::string player_name;
    Leaderboard leaderboard;

    void initialize_grid(const std::string & input_file);
    void read_blocks(const std::string & input_file);
    void link_rotations(Block* originalBlock);
    std::vector<std::vector<bool>> rotateClockwise(const std::vector<std::vector<bool>>& original);
    std::vector<std::vector<bool>> rotateCounterClockwise(const std::vector<std::vector<bool>>& original);

};


#endif // BLOCKFALL_H

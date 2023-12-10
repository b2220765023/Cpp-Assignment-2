#ifndef PA2_BLOCK_H
#define PA2_BLOCK_H

#include <vector>

using namespace std;

class Block {
public:
    std::vector<std::vector<bool>> shape;
    Block* right_rotation = nullptr;
    Block* left_rotation = nullptr;
    Block* next_block = nullptr;

    bool operator==(const Block& other) const {
        return shape == other.shape;
    }

    bool operator!=(const Block& other) const {
        return shape != other.shape;
    }
};

#endif //PA2_BLOCK_H
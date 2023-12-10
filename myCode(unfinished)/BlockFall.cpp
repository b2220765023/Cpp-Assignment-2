// BlockFall.cpp

#include "BlockFall.h"
#include <fstream>
#include <sstream>
#include <iostream>



BlockFall::BlockFall(std::string grid_file_name, std::string blocks_file_name, bool gravity_mode_on, const std::string &leaderboard_file_name,
                     const std::string &player_name)
        : gravity_mode_on(gravity_mode_on), leaderboard_file_name(leaderboard_file_name), player_name(player_name) {
    initialize_grid(grid_file_name);
    read_blocks(blocks_file_name);
}

void BlockFall::initialize_grid(const std::string &input_file) {
    std::ifstream inputFile(input_file);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << input_file << std::endl;
        return;
    }
    std::string line;
    while (getline(inputFile, line)) {
        if (line.empty()) {
            continue;
        }
        std::vector<int> row;
        int num;
        std::istringstream iss(line);
        while (iss >> num) {
            row.push_back(num);
        }
        grid.push_back(row);
    }
    inputFile.close();
}

std::vector<std::vector<bool>> BlockFall::rotateClockwise(const std::vector<std::vector<bool>>& original) {
    if (original.empty() || original[0].empty()) {
        return original;
    }

    size_t rows = original.size();
    size_t cols = original[0].size();
    std::vector<std::vector<bool>> rotated(cols, std::vector<bool>(rows, false));

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            rotated[j][rows - 1 - i] = original[i][j];
        }
    }
    return rotated;
}

std::vector<std::vector<bool>> BlockFall::rotateCounterClockwise(const std::vector<std::vector<bool>>& original) {
    if (original.empty() || original[0].empty()) {
        return original;
    }

    size_t rows = original.size();
    size_t cols = original[0].size();
    std::vector<std::vector<bool>> rotated(cols, std::vector<bool>(rows, false));

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            rotated[cols - 1 - j][i] = original[i][j];
        }
    }

    return rotated;
}

void BlockFall::link_rotations(Block* originalBlock) {
    // Create clockwise rotations
    Block* currentRotation = originalBlock;
    for (int i = 0; i < 3; ++i) {
        currentRotation->right_rotation = new Block();
        currentRotation->right_rotation->shape = rotateClockwise(currentRotation->shape);
        currentRotation->right_rotation->left_rotation = currentRotation;
        currentRotation->right_rotation->next_block = originalBlock;

        currentRotation = currentRotation->right_rotation;
    }

    // Create counterclockwise rotations
    currentRotation = originalBlock;
    for (int i = 0; i < 3; ++i) {
        currentRotation->left_rotation = new Block();
        currentRotation->left_rotation->shape = rotateCounterClockwise(currentRotation->shape);
        currentRotation->left_rotation->right_rotation = currentRotation;
        currentRotation->left_rotation->next_block = originalBlock;

        currentRotation = currentRotation->left_rotation;
    }
}

void BlockFall::read_blocks(const std::string &input_file) {
    std::vector<std::vector<int>> matrices;
    std::vector<std::vector<std::vector<int>>> blockVector;
    std::ifstream inputFile(input_file);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << input_file << std::endl;
        return;
    }

    std::string line;
    while (getline(inputFile, line)) {
        if (line.empty()) {
            // Check if matrices is not empty before adding it to blockVector
            if (!matrices.empty()) {
                blockVector.push_back(matrices);
                matrices.clear();
            }
            continue;
        }

        std::vector<int> matrixRow;
        std::istringstream iss(line);

        for (char c : line) {
            if (isdigit(c)) {
                matrixRow.push_back(c - '0');
            }
        }
        matrices.push_back(matrixRow);
    }
    inputFile.close();

    // Check if there are matrices after the last empty line
    if (!matrices.empty()) {
        blockVector.push_back(matrices);
    }

    for (int i = 0; i < blockVector.size(); i++) {
        Block* newBlock = new Block();
        newBlock->shape.clear();  // Clear the existing shape vector

        for (const auto& row : blockVector[i]) {
            std::vector<bool> boolRow;
            for (int value : row) {
                boolRow.push_back(value != 0);  // Convert 0 to false, non-zero to true
            }
            newBlock->shape.push_back(boolRow);
        }

        // Link rotations
        link_rotations(newBlock);

        if (initial_block == nullptr) {
            initial_block = newBlock;
            active_rotation = newBlock;
        } else {
            Block* lastBlock = initial_block;
            while (lastBlock->next_block != nullptr) {
                lastBlock = lastBlock->next_block;
            }
            lastBlock->next_block = newBlock;
        }
    }

    // Set power_up to the shape of the last block
    if (initial_block != nullptr) {
        Block* lastBlock = initial_block;
        while (lastBlock->next_block != nullptr) {
            lastBlock = lastBlock->next_block;
        }
        power_up = lastBlock->shape;
    }
}






BlockFall::~BlockFall() {
    // Free dynamically allocated memory used for storing game blocks
    Block* currentBlock = initial_block;
    while (currentBlock != nullptr) {
        Block* nextBlock = currentBlock->next_block;

        // Free memory for each rotation
        Block* rotation = currentBlock->right_rotation;
        while (rotation != nullptr && rotation != currentBlock) {
            Block* nextRotation = rotation->right_rotation;
            delete rotation;
            rotation = nextRotation;
        }

        delete currentBlock;  // Free memory for the original block

        currentBlock = nextBlock;
    }
}


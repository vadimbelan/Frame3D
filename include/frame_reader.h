#ifndef FRAME_READER_H
#define FRAME_READER_H

#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <regex>
#include <algorithm>

namespace fs = std::filesystem;

struct Frame {
    int number;
    std::string filename;
    int read_order;
};

std::vector<Frame> read_frames(const fs::path& frames_dir);
void print_frames(const std::vector<Frame>& frames);
std::vector<int> find_missing_frames(const std::vector<Frame>& frames);

#endif // FRAME_READER_H

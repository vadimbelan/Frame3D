#include "frame_reader.h"

std::vector<Frame> read_frames(const fs::path& frames_dir) {
    std::regex frame_regex(R"(frame_(\d+)\.\w+)", std::regex::icase);
    std::vector<Frame> frames;

    try {
        for (const auto& entry : fs::directory_iterator(frames_dir)) {
            if (entry.is_regular_file()) {
                std::string filename = entry.path().filename().string();
                std::smatch match;
                if (std::regex_match(filename, match, frame_regex)) {
                    if (match.size() == 2) {
                        int number = std::stoi(match[1]);
                        frames.push_back(Frame{number, filename, 0});
                    }
                }
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Ошибка при доступе к файловой системе: " << e.what() << std::endl;
    }

    return frames;
}

void print_frames(const std::vector<Frame>& frames) {
    std::cout << "Прочитанные фреймы:" << std::endl;
    for (const auto& frame : frames) {
        std::cout << frame.filename << " (прочитан " << frame.read_order << "-м)" << std::endl;
    }
}

std::vector<int> find_missing_frames(const std::vector<Frame>& frames) {
    if (frames.empty()) return {};

    int min_frame = frames.front().number;
    int max_frame = frames.back().number;

    std::vector<int> existing_frames;
    for (const auto& frame : frames) {
        existing_frames.push_back(frame.number);
    }

    std::sort(existing_frames.begin(), existing_frames.end());

    std::vector<int> missing_frames;
    for (int i = min_frame; i <= max_frame; ++i) {
        if (!std::binary_search(existing_frames.begin(), existing_frames.end(), i)) {
            missing_frames.push_back(i);
        }
    }

    return missing_frames;
}

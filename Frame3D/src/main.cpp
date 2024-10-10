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

int main() {
    fs::path frames_dir = fs::current_path().parent_path() / "frames";

    if (!fs::exists(frames_dir) || !fs::is_directory(frames_dir)) {
        std::cerr << "Папка 'frames' не найдена в директории: " << fs::current_path() << std::endl;
        return 1;
    }

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
        return 1;
    }

    if (frames.empty()) {
        std::cout << "Нет файлов, соответствующих шаблону 'frame_<number>.<extension>' в папке 'frames'." << std::endl;
        return 0;
    }

    std::sort(frames.begin(), frames.end(), [](const Frame& a, const Frame& b) {
        return a.number < b.number;
    });

    for (size_t i = 0; i < frames.size(); ++i) {
        frames[i].read_order = static_cast<int>(i + 1);
    }

    std::cout << "Прочитанные фреймы:" << std::endl;
    for (const auto& frame : frames) {
        std::cout << frame.filename << " (прочитан " << frame.read_order << "-м)" << std::endl;
    }

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

    if (!missing_frames.empty()) {
        std::cout << "\nПропущенные фреймы:" << std::endl;
        for (const auto& num : missing_frames) {
            std::cout << "frame_" << num << std::endl;
        }
    } else {
        std::cout << "\nНет пропущенных фреймов." << std::endl;
    }

    return 0;
}

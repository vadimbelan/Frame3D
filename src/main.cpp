#include "frame_reader.h"
#include "video_frame_saver.h"
#include <iostream>

int main() {
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    std::string videoPath;
    std::cout << "Введите путь к видео (или нажмите Enter для пропуска): ";
    std::getline(std::cin, videoPath);

    std::string outputDir = "frames";

    if (!videoPath.empty()) {
        VideoFrameExtractor extractor(videoPath, outputDir);
        extractor.extractFrames();
    } else {
        std::cout << "Пропускаем извлечение кадров." << std::endl;
    }

    std::filesystem::path frames_dir = std::filesystem::current_path() / outputDir;

    if (!std::filesystem::exists(frames_dir) || !std::filesystem::is_directory(frames_dir)) {
        std::cerr << "Папка 'frames' не найдена в директории: " << std::filesystem::current_path() << std::endl;
        return 1;
    }

    std::vector<Frame> frames = read_frames(frames_dir);

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

    print_frames(frames);

    std::vector<int> missing_frames = find_missing_frames(frames);

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

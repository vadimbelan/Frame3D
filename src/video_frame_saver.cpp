#include "video_frame_saver.h"

VideoFrameExtractor::VideoFrameExtractor(const std::string& videoPath, const std::string& outputDir)
    : videoPath(videoPath), outputDir(outputDir) {
    setlocale(LC_ALL, "ru_RU.UTF-8");
}

void VideoFrameExtractor::extractFrames() {
    cv::VideoCapture cap(videoPath);

    if (!cap.isOpened()) {
        std::cerr << "Ошибка: Не удалось открыть видеофайл." << std::endl;
        return;
    }

    std::filesystem::create_directory(outputDir);
    cv::Mat frame;
    int frameCount = 0;

    while (true) {
        cap >> frame;
        if (frame.empty()) {
            break;
        }

        std::string frameFileName = outputDir + "/frame_" + std::to_string(frameCount) + ".png"; // Измените на .png
        cv::imwrite(frameFileName, frame);

        std::cout << "Сохранено: " << frameFileName << std::endl;

        frameCount++;
    }

    cap.release();
    std::cout << "Всего сохранено кадров: " << frameCount << std::endl;
}

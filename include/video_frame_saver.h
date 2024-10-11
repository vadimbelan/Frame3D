#ifndef VIDEO_FRAME_SAVER_H
#define VIDEO_FRAME_SAVER_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>
#include <locale>

class VideFrameSaver {
public:
    VideFrameSaver(const std::string& videoPath, const std::string& outputDir);
    void saveFrames();

private:
    std::string videoPath;
    std::string outputDir;
};

#endif // VIDEO_FRAME_SAVER_H

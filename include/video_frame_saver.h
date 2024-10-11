#ifndef VIDEO_FRAME_EXTRACTOR_H
#define VIDEO_FRAME_EXTRACTOR_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>
#include <locale>

class VideoFrameExtractor {
public:
    VideoFrameExtractor(const std::string& videoPath, const std::string& outputDir);
    void extractFrames();

private:
    std::string videoPath;
    std::string outputDir;
};

#endif // VIDEO_FRAME_EXTRACTOR_H

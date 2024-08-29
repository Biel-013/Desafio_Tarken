#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/utils/logger.hpp>

int main(int argc, char **argv)
{
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);

    std::string imagePATH = "meteor_challenge_01.png";
    int Star_cont = 0;
    int Meteor_cont = 0;
    int lines = 0;
    cv::Mat image = cv::imread(imagePATH, cv::IMREAD_COLOR);

    if (image.empty())
    {
        std::cerr << "Erro ao carregar a imagem!" << std::endl;
        return -1;
    }

    cv::Vec3b pixelWhite(255, 255, 255);
    cv::Vec3b pixelRed(0, 0, 255);
    cv::Vec3b pixelBlue(255, 0, 0);
    cv::Vec3b pixelYellow(0, 255, 255);
    cv::Vec3b pixelBackground(189, 119, 2);
    cv::Mat image_test(352, 704, CV_8UC3, pixelBackground);

    // Vetor para armazenar cores únicas detectadas
    std::vector<int> binari;
    for (int y = 0; y < 222; y++)
    {
        for (int x = 0; x < image.cols; x++)
        {
            // Criar a cor correspondente
            cv::Vec3b detectedColor = image.at<cv::Vec3b>(y, x);

            if (detectedColor == pixelRed)
            {
                image_test.at<cv::Vec3b>(y, x) = pixelRed;
                binari.push_back(1);
                binari.push_back(0);
                binari.push_back(0);
            }

            if (detectedColor == pixelWhite)
            {
                image_test.at<cv::Vec3b>(y, x) = pixelWhite;
                binari.push_back(1);
                binari.push_back(1);
                binari.push_back(1);
            }
        }
    }

    char phase[175] = {0};
    for (int i = 0; i < (binari.size() / 8); i++)
    {
        phase[i] = (binari[i * 8] << 0) + (binari[i * 8 + 1] << 1) + (binari[i * 8 + 2] << 2) + (binari[i * 8 + 3] << 3) + (binari[i * 8 + 4] << 4) + (binari[i * 8 + 5] << 5) + (binari[i * 8 + 6] << 6) + (binari[i * 8 + 7] << 7);
    }
    // phase[binari.size()] = '\0';
    std::cout << phase << std::endl;
    return 0;
}
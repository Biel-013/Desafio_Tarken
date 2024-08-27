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
    int i = 0;
    for (int y = 0; y < 352; y++)
    {
        i = 0;
        for (int x = 0; x < image.cols; x++)
        {
            // Criar a cor correspondente
            cv::Vec3b detectedColor = image.at<cv::Vec3b>(y, x);

            if (image.at<cv::Vec3b>(y, x)[0] == pixelRed[0] && // Componente B
                image.at<cv::Vec3b>(y, x)[1] == pixelRed[1] && // Componente G
                image.at<cv::Vec3b>(y, x)[2] == pixelRed[2])
            {
                image_test.at<cv::Vec3b>(y, x) = pixelRed;
            }

            if (image.at<cv::Vec3b>(y, x)[0] == pixelWhite[0] && // Componente B
                image.at<cv::Vec3b>(y, x)[1] == pixelWhite[1] && // Componente G
                image.at<cv::Vec3b>(y, x)[2] == pixelWhite[2])
            {
                image_test.at<cv::Vec3b>(y, x) = pixelWhite;
            }
        }
    }
    for (auto& binario : binari)
    {
    std::cout << binario;
    }
    std::cout << std::endl;
    // Exibir as imagens se necessário
    // cv::imshow("Image", image);
    // cv::imshow("Image test", image_test);
    cv::imwrite("Image_test.png", image_test);
    // cv::waitKey(0);

    return 0;
}
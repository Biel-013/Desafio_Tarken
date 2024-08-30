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

    cv::Mat image_filter(500, 500, CV_8UC3, cv::Scalar(0, 0, 0));
    cv::Mat image_color(520, 500, CV_8UC3, cv::Scalar(0, 0, 0));

    // Vetor para armazenar cores únicas detectadas
    std::vector<int> binari;
    int pixels = 0;
    binari.clear();
    for (int row = 0; row < 350; row++)
    {
        for (int col = 0; col < image.cols; col++)
        {
            /* Variável para armazenamento do valor do píxel*/
            cv::Vec3b detectColor = image.at<cv::Vec3b>(row, col);

            /* Essa variável armazena se o meteoro caiu ou não na água*/
            bool inOcean = false;

            if (detectColor == pixelWhite)
                std::cout << 1;

            /* Se um píxel vermelho for detectado, percorre um caminho
            perpendicular até a água para verificar se o meteoro irá cair
            no oceano ou não*/
            if (detectColor == pixelRed)
            {
                for (int pathway = row; pathway < image.rows; pathway++)
                {
                    detectColor = image.at<cv::Vec3b>(pathway, col);

                    if (detectColor == pixelBlue)
                    {
                        std::cout << 0;
                        break;
                    }
                }

                /* Caso o meteoro caia no oceano, esse novo laço irá desenhar um
                caminho verde até o mar*/
                // if (inOcean)
                //     std::cout << 0;
                /* Caso contrário, irá desenhar um caminho vermelho*/
            }
        }
        std::cout << std::endl;
    }
    // for (int i = 0; i < binari.size(); i++)
    // {
    //     std::cout << binari[i];
    //     if ((i % 20) == 19)
    //         std::cout << std::endl;
    // }
    std::cout << std::endl;

    // cv::imshow("image_color", image_color);
    // cv::waitKey(0);
    return 0;
}

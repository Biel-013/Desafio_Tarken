#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char **argv)
{
    std::string imagePATH = "meteor_challenge_01.png";
    int Star_cont = 0;
    int Meteor_cont = 0;
    cv::Mat image = cv::imread(imagePATH, cv::IMREAD_COLOR);

    if (image.empty())
    {
        std::cerr << "Erro ao carregar a imagem!" << std::endl;
        return -1;
    }

    cv::Vec3b pixelWhite(255, 255, 255);
    cv::Vec3b pixelRed(0, 0, 255);

    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            
            if (image.at<cv::Vec3b>(i, j)[0] == pixelWhite[0] && // Componente B
                image.at<cv::Vec3b>(i, j)[1] == pixelWhite[1] && // Componente G
                image.at<cv::Vec3b>(i, j)[2] == pixelWhite[2])
            { 

                std::cout << "Estrela encontrado em (" << i << ", " << j << ")" << std::endl;
                image.at<cv::Vec3b>(i, j) = cv::Vec3b(0, 255, 0); // B=255, G=0, R=0
                Star_cont++;
            }

            if (image.at<cv::Vec3b>(i, j)[0] == pixelRed[0] &&
                image.at<cv::Vec3b>(i, j)[1] == pixelRed[1] && 
                image.at<cv::Vec3b>(i, j)[2] == pixelRed[2])
            {

                std::cout << "Meteoro encontrado em (" << i << ", " << j << ")" << std::endl;
                Meteor_cont++;
            }
        }
    }
    std::cout << "O numero de meteoros e: " << Meteor_cont << "\nE o numero de estrelas e: " << Star_cont << std::endl;
    // cv::imwrite("imagem_alterada.png", image);
    // cv::imshow("image window", image);
    // cv::waitKey(0);
    return 0;
}
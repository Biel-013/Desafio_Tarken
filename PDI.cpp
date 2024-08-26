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
    /************************Clean image**************************/
    cv::Vec3b pixelWhite(255, 255, 255);
    for (int y = 0; y < image.rows; y++)
    {
        for (int x = 0; x < image.cols; x++)
        {
            if (image.at<cv::Vec3b>(y, x)[0] == pixelWhite[0] &&
                image.at<cv::Vec3b>(y, x)[1] == pixelWhite[1] &&
                image.at<cv::Vec3b>(y, x)[2] == pixelWhite[2])
            {
                image.at<cv::Vec3b>(y, x) = cv::Vec3b(189, 119, 2);
            }
        }
    }
    cv::imwrite("Clean_image.png", image);
    /************************Clean image**************************/
    cv::Vec3b pixelRed(0, 0, 255);
    cv::Vec3b pixelBlue(255, 0, 0);
    cv::Vec3b pixelYellow(0, 255, 255);

    for (int y = 0; y < image.rows; y++)
    {
        for (int x = 0; x < image.cols; x++)
        {
            if (image.at<cv::Vec3b>(y, x)[0] == pixelRed[0] &&
                image.at<cv::Vec3b>(y, x)[1] == pixelRed[1] &&
                image.at<cv::Vec3b>(y, x)[2] == pixelRed[2])
            {
                for (int i = y; i < image.rows; i++)
                {
                    image.at<cv::Vec3b>(y, x) = cv::Vec3b(255, 255, 255);
                    if (image.at<cv::Vec3b>(i, x)[0] == pixelBlue[0] &&
                        image.at<cv::Vec3b>(i, x)[1] == pixelBlue[1] &&
                        image.at<cv::Vec3b>(i, x)[2] == pixelBlue[2])
                    {
                        Meteor_cont++;
                        image.at<cv::Vec3b>(y, x) = cv::Vec3b(0, 255, 255);
                        break;
                    }
                }
            }
        }
    }

    for (int y = 0; y < image.rows; y++)
    {
        for (int x = 0; x < image.cols; x++)
        {
            if (image.at<cv::Vec3b>(y, x)[0] == pixelWhite[0] &&
                image.at<cv::Vec3b>(y, x)[1] == pixelWhite[1] &&
                image.at<cv::Vec3b>(y, x)[2] == pixelWhite[2])
            {
                for (int i = y; i < image.rows; i++)
                {
                    image.at<cv::Vec3b>(i, x) = cv::Vec3b(0, 0, 255);
                }
            }
            if (image.at<cv::Vec3b>(y, x)[0] == pixelYellow[0] &&
                image.at<cv::Vec3b>(y, x)[1] == pixelYellow[1] &&
                image.at<cv::Vec3b>(y, x)[2] == pixelYellow[2])
            {
                for (int i = y; i < image.rows; i++)
                {
                    image.at<cv::Vec3b>(i, x) = cv::Vec3b(0, 255, 0);
                }
            }
        }
    }
    std::cout << "O numero de meteoros na agua e: " << Meteor_cont << std::endl;
    cv::imwrite("caminho_meteor.png", image);
    // cv::imshow("image window", image);
    // cv::waitKey(0);
    return 0;
}
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

    cv::Mat Image_grey;
    cv::Mat Image_mask;

    // Converter a imagem para escala de cinza
    cv::cvtColor(image, Image_grey, cv::COLOR_BGR2GRAY);

    // Definir os limites para a máscara
    uchar lowerThreshold = 80;  // Valor mínimo
    uchar upperThreshold = 150; // Valor máximo

    // Criar a máscara usando a escala de cinza
    cv::inRange(Image_grey, lowerThreshold, upperThreshold, Image_mask);

    // Vetor para armazenar cores únicas detectadas
    std::vector<cv::Vec3b> cores;

    for (int y = 0; y < Image_grey.rows; y++)
    {
        for (int x = 0; x < Image_grey.cols; x++)
        {
            uchar pixelValue = Image_grey.at<uchar>(y, x);

            // Verificar se o pixel está na faixa da máscara
            if (Image_mask.at<uchar>(y, x) == 255)
            {
                // Criar a cor correspondente
                cv::Vec3b detectedColor = image.at<cv::Vec3b>(y, x);

                // Verificar se a cor já está na lista
                bool found = false;
                for (const auto& color : cores)
                {
                    if (color == detectedColor)
                    {
                        found = true;
                        break;
                    }
                }

                // Se a cor não estiver na lista, adicione-a
                if (!found)
                {
                    cores.push_back(detectedColor);
                    std::cout << "Cor detectada:\n B: " << (int) detectedColor[0]
                              << " G: " << (int) detectedColor[1]
                              << " R: " << (int) detectedColor[2] << std::endl;
                }
            }
        }
    }

    // Exibir as imagens se necessário
    // cv::imshow("Image", image);
    cv::imshow("Image Grey", Image_grey);
    cv::imshow("Image Mask", Image_mask);
    cv::waitKey(0);

    return 0;
}

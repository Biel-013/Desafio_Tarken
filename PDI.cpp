#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/utils/logger.hpp>

int main(int argc, char **argv)
{
    /* Silencia as mensagens de retorno do OpenCV*/
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);

    /* Cria os contadores para armazenar o numero máximo de estrelas e meteoros*/
    int Star_cont = 0;
    int Meteor_cont = 0;

    /* Cria o objeto "image", que será basicamente uma matrix onde cada índice apresenta um valor BGR*/
    std::string imagePATH = "meteor_challenge_01.png";
    cv::Mat image = cv::imread(imagePATH, cv::IMREAD_COLOR);

    /* Verifica se não houve erro na instanciação do objeto*/
    if (image.empty())
    {
        std::cerr << "Erro ao carregar a imagem!" << std::endl;
        return -1;
    }

    /* Variáveis que armazenam o valor dos pixels da estrela (Branco) e meteoro (Vermelho)*/
    cv::Vec3b pixelWhite(255, 255, 255); // BGR: Blue(255), Green(255), Red(255)
    cv::Vec3b pixelRed(0, 0, 255); // BGR: Blue(0), Green(0), Red(255)

    /* Laço duplo for para percorrer todos os índices da imagem*/
    for (int row = 0; row < image.rows; row++)
    {
        for (int col = 0; col < image.cols; col++)
        {
            /* Para cada pixel, a cor será armazenada e logo após comparada, para verificar 
            se é um meteoro ou uma estrela */
            cv::Vec3b detectColor = image.at<cv::Vec3b>(row, col);

            if (detectColor == pixelWhite)
                Star_cont++;

            if (detectColor == pixelRed)
                Meteor_cont++;
        }
    }

    /* Exibe o valor da contagem de estrelas e meteoros*/
    std::cout << "O numero de estrelas e: " << Star_cont << "\nE o numero de meteoros e: " << Meteor_cont << std::endl;
    return 0;
}
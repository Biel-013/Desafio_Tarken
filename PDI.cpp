#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/utils/logger.hpp>

int main(int argc, char **argv)
{
    /* Silencia as mensagens de retorno do OpenCV*/
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);

    /* Cria o contador para armazenar o numero de meteoros na agua*/
    int Meteor_cont = 0;

    /* Cria o objeto "image", que será basicamente uma matrix onde cada
    índice apresenta um valor BGR*/
    std::string imagePATH = "meteor_challenge_01.png";
    cv::Mat image = cv::imread(imagePATH, cv::IMREAD_COLOR);

    /* Verifica se não houve erro na instanciação do objeto*/
    if (image.empty())
    {
        std::cerr << "Erro ao carregar a imagem!" << std::endl;
        return -1;
    }

    /* Variáveis que armazenam o valor dos pixels Vermelho, Azul e Verde */
    cv::Vec3b pixelRed(0, 0, 255);   // BGR: Blue(0), Green(0), Red(255)
    cv::Vec3b pixelBlue(255, 0, 0);  // BGR: Blue(255), Green(0), Red(0)
    cv::Vec3b pixelGreen(0, 255, 0); // BGR: Blue(0), Green(255), Red(0)

    /* Laço duplo for para percorrer todos os índices da imagem*/
    for (int row = image.rows - 1; row >= 0; row--)
        for (int col = 0; col < image.cols; col++)
        {
            /* Variável para armazenamento do valor do píxel*/
            cv::Vec3b detectColor = image.at<cv::Vec3b>(row, col);

            /* Essa variável armazena se o meteoro caiu ou não na água*/
            bool inOcean = false;

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
                        Meteor_cont++;
                        inOcean = true;
                        break;
                    }
                }

                /* Caso o meteoro caia no oceano, esse novo laço irá desenhar um
                caminho verde até o mar*/
                if (inOcean)
                    for (int pathway = row; pathway < image.rows; pathway++)
                    {

                        detectColor = image.at<cv::Vec3b>(pathway, col);

                        if (detectColor == pixelBlue)
                            break;
                        image.at<cv::Vec3b>(pathway, col) = pixelGreen;
                    }
                /* Caso contrário, irá desenhar um caminho vermelho*/
                else
                    for (int pathway = row; pathway < image.rows; pathway++)
                        image.at<cv::Vec3b>(pathway, col) = pixelRed;
            }
        }

    /* Armazena a nova imagem adquirida e exibe o número de meteoros no
    mar no terminal*/
    cv::imwrite("caminho_meteor.png", image);
    std::cout << "O numero de meteoros na agua e: " << Meteor_cont << std::endl;
    return 0;
}
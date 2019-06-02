#include <opencv2/dnn/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace dnn;


std::string keys =
    "{ help  h     |        |  Print help message. }"
    "{ weights w   | <none> |  Path to the weights file. }"
;


int main(int argc, char ** argv)
{
    CommandLineParser parser(argc, argv, keys);

    if (argc == 1 || parser.has("help"))
    {
        parser.printMessage();
        return 0;
    }

    const std::string weightsFile = parser.get<std::string>("weights");

    Model model(weightsFile);

}
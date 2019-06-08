/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
//
//                           License Agreement
//                For Open Source Computer Vision Library
//
// Copyright (C) 2013, OpenCV Foundation, all rights reserved.
// Third party copyrights are property of their respective owners.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   * Redistribution's of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//   * Redistribution's in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//   * The name of the copyright holders may not be used to endorse or promote products
//     derived from this software without specific prior written permission.
//
// This software is provided by the copyright holders and contributors "as is" and
// any express or implied warranties, including, but not limited to, the implied
// warranties of merchantability and fitness for a particular purpose are disclaimed.
// In no event shall the Intel Corporation or contributors be liable for any direct,
// indirect, incidental, special, exemplary, or consequential damages
// (including, but not limited to, procurement of substitute goods or services;
// loss of use, data, or profits; or business interruption) however caused
// and on any theory of liability, whether in contract, strict liability,
// or tort (including negligence or otherwise) arising in any way out of
// the use of this software, even if advised of the possibility of such damage.
//
//M*/

#ifndef OPENCV_MODEL_HPP
#define OPENCV_MODEL_HPP

#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#ifdef CV_CXX11
#include <future>
#endif

#include "version.hpp"
#include "dnn.hpp"


/* todo SK roadmap

see object_detection.cpp

- setup the preprocessing function, use yaml?
- get a working model running in parent class
TARGET: 6/12

- add a queue class that stores images and results using mutex
TARGET: 6/15 

- Multithread the processing
- Multithread the frame acuisation if async is true

--- By here, detection should be working ---
TARGET: 6/19

- add segmentation coloring capability
- add classification capability
TARGET: 6/23

- test with a couple of examples

--- get feedback here ----
TARGET: 6/26

- incorporate any feedback
TARGET: 7/7

- clean up code
- PR
TARGET: 7/14

*/


namespace cv {
namespace dnn {
CV__DNN_INLINE_NS_BEGIN
//! @addtogroup dnn
//! @{


class CV_EXPORTS_W_SIMPLE Model : public Net
{
public:
    /**
     * @brief Construct a new Model object. This argument will initialize a
     * dnn::Net object by automatically detecting which type of weights file
     * is passed in
     * 
     * @param weightsFile Weights in a supported format. See Model::BACKEND
     * @param config Optional config file to optimize loading the model 
     * @param width Input image width
     * @param height Input image height
     * @param mean Value to subtract from each pixel
     * @param scale Scale factor for each pixel
     */
    Model(const std::string &weightsFile, const std::string &config = "", int width = -1, int height = -1, Scalar mean = Scalar(), float scale = 1.0);
    /**
     * @brief Set the Video Capture object. This will provide a source to input
     * images from
     * 
     * @param cap the video capture device
     * @param async Capture frames asynchronously 
     */
    void setVideoCapture(VideoCapture &cap, bool async = true);

    /**
     * @brief Get the next available Frame, which will be annotated with outputs
     * 
     * @param[out] frame 
     */
    void getFrame(Mat &frame);

    ~Model();    
private:
    enum class BACKEND {
        TENSORFLOW,
        TORCH,
        DARKNET,
        CAFFE,
        UNDEF
    };

    std::vector<std::string> m_classes;
    int m_width;
    int m_height;
    Scalar m_mean;
    float m_scale;
    VideoCapture m_inputVideo;
    bool m_async;

    Mat preprocess(Mat &frame);
    void postprocess(Mat &frame);

    void drawBB(int classId, float conf, int left, int top, int right,
        int bottom, Mat& frame);
};
//! @}
CV__DNN_INLINE_NS_END
}
}


#endif // OPENCV_MODEL_HPP
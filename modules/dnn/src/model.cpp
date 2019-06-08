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

#include <stdio.h>

#include <opencv2/dnn/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/utils/configuration.private.hpp>
#include <opencv2/core/utils/logger.hpp>

namespace cv {
namespace dnn {
CV__DNN_INLINE_NS_BEGIN
Model::Model(const std::string &weightsFile, const std::string &config, int width, int height, Scalar mean, float scale) :
    Net(),
    m_width(width),
    m_height(height),
    m_mean(mean),
    m_scale(scale)

{
    std::cout << weightsFile << "\n";
    // readNet(weightsFile);
}
Model::~Model(){}


void Model::setVideoCapture(VideoCapture &cap, bool async)
{
    if(!cap.isOpened())  // check if it is open
    {
        CV_Error(Error::StsAssert, "Could not open video capture");
    }
    m_inputVideo = cap;
    m_async = async;
}

void Model::getFrame(Mat &frame)
{
    // get frame from source 
    // todo SK: make this dynamic, could be from file
    m_inputVideo >> frame;
    Mat blob = preprocess(frame);
    // add frame, blob to pre- queue
    // get frame, blob from pre- queue
    // run net
    // get frame, output from post- queue
    // annotate frame
    // todo SK: this frame should come from queue, could be different
    postprocess(frame);
}


Mat Model::preprocess(Mat &frame)
{
    return Mat();
}

void Model::postprocess(Mat &frame)
{
    Scalar color(0,255,0);
    drawBB(0, 1, 100, 100, 200, 200, frame);
}

void Model::drawBB(int classId, float conf, int left, int top, int right, int bottom, 
    Mat& frame)
{
    rectangle(frame, Point(left, top), Point(right, bottom), Scalar(0, 255, 0));

    std::string label = format("%.2f", conf);
    if (!m_classes.empty())
    {
        CV_Assert(classId < (int)m_classes.size());
        label = m_classes[classId] + ": " + label;
    }
    else
    {
        // for now
        label = "Test";
    }

    // add a label with the text
    int baseLine;
    Size labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
    top = max(top, labelSize.height);
    rectangle(frame, Point(left, top - labelSize.height),
              Point(left + labelSize.width, top + baseLine), Scalar(0, 255, 0), FILLED);
    putText(frame, label, Point(left, top), FONT_HERSHEY_SIMPLEX, 0.5, Scalar());
}


CV__DNN_INLINE_NS_END
}
}
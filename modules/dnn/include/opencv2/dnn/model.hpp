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
#ifdef CV_CXX11
#include <future>
#endif

#include "version.hpp"
#include "dnn.hpp"


namespace cv {
namespace dnn {
CV__DNN_INLINE_NS_BEGIN
//! @addtogroup dnn
//! @{

class CV_EXPORTS_W_SIMPLE Model : public Net
{
public:
    Model(const std::string &weightsFile, const std::string &config = "", int width = -1, int height = -1, Scalar mean = Scalar(), float scale = 1.0);
    ~Model();    
private:
};
//! @}
CV__DNN_INLINE_NS_END
}
}


#endif // OPENCV_MODEL_HPP
/**
 * DeepDetect
 * Copyright (c) 2021 Jolibrain
 * Author: Louis Jean <louis.jean@jolibrain.com>
 *
 * This file is part of deepdetect.
 *
 * deepdetect is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * deepdetect is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with deepdetect.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DD_UTILS_CVUTILS_HPP
#define DD_UTILS_CVUTILS_HPP

#include <vector>
#include <opencv2/opencv.hpp>
#include "ext/base64/base64.h"

namespace dd
{
  namespace cv_utils
  {
    /** Convert an int fourcc (from a video) to string format */
    inline std::string fourcc_to_string(int fourcc)
    {
      union
      {
        int u32;
        unsigned char c[4];
      } i32_c;
      i32_c.u32 = fourcc;
      return cv::format(
          "%c%c%c%c",
          (i32_c.c[0] >= ' ' && i32_c.c[0] < 128) ? i32_c.c[0] : '?',
          (i32_c.c[1] >= ' ' && i32_c.c[1] < 128) ? i32_c.c[1] : '?',
          (i32_c.c[2] >= ' ' && i32_c.c[2] < 128) ? i32_c.c[2] : '?',
          (i32_c.c[3] >= ' ' && i32_c.c[3] < 128) ? i32_c.c[3] : '?');
    }

    inline cv::Mat base64_to_image(const std::string &str_base64)
    {
      std::string img_str;
      if (!Base64::Decode(str_base64, &img_str))
        throw std::runtime_error("Image could not be decoded");

      std::vector<unsigned char> vdat(img_str.begin(), img_str.end());
      cv::Mat img
          = cv::Mat(cv::imdecode(cv::Mat(vdat, false), cv::IMREAD_UNCHANGED));
      return img;
    }

    /** Convert image to base64 string */
    inline std::string image_to_base64(const cv::Mat &mat,
                                       const std::string &ext)
    {
      std::vector<uint8_t> buffer;
      cv::imencode(ext, mat, buffer);

      // encode to base64
      std::string byte_str(buffer.begin(), buffer.end());
      std::string encoded;
      if (!Base64::Encode(byte_str, &encoded))
        throw std::runtime_error("Image could not be encoded");
      return encoded;
    }
  }
}

#endif // DD_UTILS_CVUTILS_HPP

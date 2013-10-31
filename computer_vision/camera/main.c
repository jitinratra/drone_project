#include <stdio.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;

void readme();

/** @function main */
int main( int argc, char** argv )
{
  VideoCapture cap(0);
  Mat camera_frame;




  while(1)
  {
    cap.read(camera_frame);
    imshow("Keypoints 1", camera_frame );
    waitKey(30);
  }

  return 0;
  }

  /** @function readme */
  void readme()
  { std::cout << " Usage: ./SURF_detector <img1>" << std::endl; }

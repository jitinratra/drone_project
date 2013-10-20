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

  int i;
  // Load the base image
  Mat base_image = imread(argv[1], CV_LOAD_IMAGE_UNCHANGED), base_descriptor;
  std::vector<KeyPoint> base_keypoints;
  Mat tmp_image;
  int minHessian = 400;
  std::vector<Mat> image_vector;
  std::vector< std::vector<KeyPoint> > keypoints_vector;
  std::vector<Mat> descriptors_vector;
  std::vector< std::vector< DMatch > > matches_vector;
  SurfFeatureDetector detector( minHessian );
  int image_count = argc - 2;

  // Computes the base_image descriptor
  SurfDescriptorExtractor extractor;
  detector.detect( base_image, base_keypoints);
  extractor.compute( base_image, base_keypoints, base_descriptor );


  image_vector.resize(image_count);
  keypoints_vector.resize(image_count);
  descriptors_vector.resize(image_count);
  matches_vector.resize(image_count);

  for(i=0; i<image_count; i++)
  {
    std::cout << "Image " << i+1 << std::endl;
    tmp_image = imread(argv[2+i]);
    if( !tmp_image.data)
    { 
      std::cout<< " --(!) Error reading images " << std::endl; 
      return -1; 
    }
    image_vector.push_back(tmp_image);
    detector.detect( tmp_image, keypoints_vector[i]);
    extractor.compute( tmp_image, keypoints_vector[i], descriptors_vector[i] );

    //-- Step 3: Matching descriptor vectors with a brute force matcher
    BFMatcher matcher(NORM_L2);
    std::vector< DMatch > matches;
    matcher.match( base_descriptor, descriptors_vector[i], matches );

    Mat img_matches;
    drawMatches( tmp_image, keypoints_vector[i], base_image, base_keypoints,
               matches, img_matches, Scalar::all(-1), Scalar::all(-1),
               vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
    imshow("Test", img_matches);
    
    waitKey(2000);
  }

  return 0;
}


#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <string>

#include "camera.h"
#include "utility.h"

#include "Calibrator.h"

using namespace std;
using namespace mynteye;

int main(int argc, char const *argv[])
{
	Calibrator calib(752, 480, 8, 6, 20, 35.1, 
			"mynteye_camera_calib2_paras.xml", 1);
	calib.setImageNames();
	double avgError = calib.calcCameraParas("./mynteye_images2/");
	calib.saveCameraParas(avgError);
	calib.printCameraParas();

	cv::Mat image1, image2;
	image1 = cv::imread("./mynteye_images2/img1_07.jpg", -1);
	image2 = cv::imread("./mynteye_images2/img2_07.jpg", -1);
	int stereoParas[11] = {-64, 128, 11, 100, 1000,
						32, 0, 15, 1000, 16, cv::StereoSGBM::MODE_HH};
	calib.showRectified(image1, image2, stereoParas);

	cv::FileStorage fs("stereoRectifiedParas.xml", cv::FileStorage::READ);
	cv::Mat disp, Q, Img3d;
	fs["disparity"] >> disp;
	fs["Q"] >> Q;

	cout << disp << endl;
	/*
	cv::reprojectImageTo3D(disp, Img3d, Q, false, -1);
	imshow("3D Image", Img3d);
	cv::waitKey(0);
	*/
	return 0;
}

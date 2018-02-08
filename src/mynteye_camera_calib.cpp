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
	// Initialize a Calibrator constructor.
	// Calibrated parameters are stored in file "mynteye_camera_calib_paras.xml".
	// More information about Calibrator to review Calibrator.h and Calibrator.cpp
	Calibrator calib(752, 480, 8, 6, 20, 35.1, 
			"mynteye_camera_calib_paras.xml", 1);
	// It's necessary if you calibrate your camera(s) firstly.
	// It helps to create string* variables for saved images.
	calib.setImageNames();

	// Class Camera is from mynteye packages
	Camera cam;
	InitParameters params("0"); // modifiable the serial number by your own camera
	cam.Open(params);
	if(!cam.IsOpened())
	{
		cerr << "\033\n\n[0;32mERROR: Fail to open cameras.\033[0m\n";
		exit(0);
	}

	cout << "\033[0;32mPress ESC to quit.\n"
		<< "Press SPACE to save images and calibrate then.\033[0m\n\n";
	
	// n_boards is the same to your parameter for created Calibrator object.
	// And you can get it use function getnBoards() in Class Calibrator, imageSize too.
	int n_boards = calib.getnBoards();
	cv::Size imageSize = calib.getImageSize();

	char keyCode;
	int frameNumber = 0;
	ErrorCode code;
	cv::Mat image1, image2;
	while(frameNumber < calib.getnBoards())
	{
		code = cam.Grab();
		if(code != ErrorCode::SUCCESS) continue;
		if(cam.RetrieveImage(image1, View::VIEW_LEFT_UNRECTIFIED) == ErrorCode::SUCCESS &&
				cam.RetrieveImage(image2, View::VIEW_RIGHT_UNRECTIFIED) == ErrorCode::SUCCESS)
		{
			// Resize your images according to your preference
			resize(image1, image1, imageSize, 1.0, 1.0, cv::INTER_LINEAR);
			resize(image2, image2, imageSize, 1.0, 1.0, cv::INTER_LINEAR);
			cv::imshow("camera1", image1);
			cv::imshow("camera2", image2);
			
			keyCode = cv::waitKey(10);
			if(keyCode == 27)
			{
				cout << "\033[0;32mQuit calibrating.\033[0m\n" << endl;
				exit(0);
			}
			if(keyCode == 32)
			{
				calib.saveImages(frameNumber, "./mynteye_images/", image1, image2);
				frameNumber++;
			}
			else 
				continue;
		}
	}

	double avgError = calib.calcCameraParas("./mynteye_images/");
	calib.saveCameraParas(avgError);
	calib.printCameraParas();

	return 0;
}

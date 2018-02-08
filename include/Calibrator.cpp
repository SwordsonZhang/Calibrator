#include "Calibrator.h"

#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>

// Constructors
// initializing
Calibrator::Calibrator()
{
	imageWidth = 0;
	imageHeight = 0;
	board_w = 0;
	board_h = 0;
	n_boards = 0;
	squareWidth = 0.f;
	flag = 0;
	filename = "";
	imageNames = NULL;
	imageNames1 = NULL;
	imageNames2 = NULL;
	imageSize = cv::Size();
	board_sz = cv::Size();
}

Calibrator::Calibrator(int imageWidth, int imageHeight,
				int board_w, int board_h, 
				int n_boards, float squareWidth, 
				string filename, int flag)
{
	this->imageWidth = imageWidth;
	this->imageHeight = imageHeight;
	this->board_w = board_w;
	this->board_h = board_h;
	this->n_boards = n_boards;
	this->squareWidth = squareWidth;
	this->flag = flag;
	this->filename = filename;
	imageNames = NULL;
	imageNames1 = NULL;
	imageNames2 = NULL;
	imageSize = cv::Size(imageWidth, imageHeight);
	board_sz = cv::Size(board_w, board_h);
	board_n = board_w * board_h;
}

Calibrator::Calibrator(string filename)
{
	imageWidth = 0;
	imageHeight = 0;
	board_w = 0;
	board_h = 0;
	n_boards = 0;
	squareWidth = 0.f;
	flag = 0;
	this->filename = filename;
	imageNames = NULL;
	imageNames1 = NULL;
	imageNames2 = NULL;
	imageSize = cv::Size();
	board_sz = cv::Size();
}

// class destructor
Calibrator::~Calibrator()
{
	delete [] imageNames;
	delete [] imageNames1;
	delete [] imageNames2;
}

// methods
// set calibrating parameters according your conditions
void Calibrator::setCalibParas(int imageWidth, int imageHeight, 
				int board_w, int board_h, int n_boards,
				float squareWidth, string filename, int flag)
{
	this->imageWidth = imageWidth;
	this->imageHeight = imageHeight;
	this->board_w = board_w;
	this->board_h = board_h;
	this->n_boards = n_boards;
	this->squareWidth = squareWidth;
	this->flag = flag;
	this->filename = filename;
	imageSize = cv::Size(imageWidth, imageHeight);
	board_sz = cv::Size(board_w, board_h);
	board_n = board_w * board_h;
}

// set names of calibrated images
// naming rules: 
// img_0i if 1 <= i < 9 and img_i if i >= 10 when flag = 0;
// img1_0i or img2_0i if 1 <= i < 9 and img1_i or img2_i if i >= 10 when flag = 1;
void Calibrator::setImageNames()
{
	stringstream ss;
	if(flag == FLAG_SINGLE_CAMERA)
	{
		imageNames = new string[n_boards];  
		for(int i = 0; i < n_boards; i++)
		{
			ss.str("");  // clear ss
			if(i < 9)
			{
				ss << "img_0" << (i + 1) << ".jpg";
				imageNames[i] = ss.str();
			}
			else
			{
				ss << "img_" << (i + 1) << ".jpg";
				imageNames[i] = ss.str();
			}
		}
	}

	if(flag == FLAG_DOUBLE_CAMERAS)
	{
		imageNames1 = new string[n_boards];
		imageNames2 = new string[n_boards];
		for(int i = 0; i < n_boards; i++)
		{
			ss.str("");
			if(i < 9)
			{
				ss << "img1_0" << (i + 1) << ".jpg";
				imageNames1[i] = ss.str();
				ss.str("");
				ss << "img2_0" << (i + 1) << ".jpg";
				imageNames2[i] = ss.str();
			}
			else
			{
				ss << "img1_" << (i + 1) << ".jpg";
				imageNames1[i] = ss.str();
				ss.str("");
				ss << "img2_" << (i + 1) << ".jpg";
				imageNames2[i] = ss.str();
			}
		}
	}
	ss.clear();
}

// save framenumber-th images into indicated directory
// image names comes from imageNames if flag = 0 
// or imageNames1 and imageNames2 if flag = 1 
// frame1: captured images by one camera or camera1 of DCM
// frame2: captured images by camera2 of DCM, default value is cv::Mat() if flag = 0
void Calibrator::saveImages(int frameNumber, string directory,
		cv::Mat frame1, cv::Mat frame2)
{
	cout << "\033[0;32mContinue capturing pictures\033[0m\n";
	cout << "\033[0;32mSave \033[0m" << (frameNumber + 1) << " \033[0;32mpicture(s).\033[0m\n\n";

	if(flag == FLAG_SINGLE_CAMERA)
		cv::imwrite(directory + imageNames[frameNumber], frame1);

	if(flag == FLAG_DOUBLE_CAMERAS)
	{
		cv::imwrite(directory + imageNames1[frameNumber], frame1);
		cv::imwrite(directory + imageNames2[frameNumber], frame2);
	}
}

// store cordinates or inner corners in a vector<cv::Point3f>
vector<cv::Point3f> Calibrator::setBoardModel()
{
	vector<cv::Point3f> opts;
	opts.resize(board_n);
	for(int j = 0; j < board_n; j++)
	{
		opts[j] = cv::Point3f((float)(j / board_w * squareWidth),
				(float)((j % board_w) * squareWidth), 0.f);
	}
	return opts;
}

// store camera parameters into filename(.xml or .yml) after calibrating
// please notice names of variables in the file 
// avgError: the average distance between points in one image and epiline in another image
//           its default value is 0.
void Calibrator::saveCameraParas(double avgError)
{
	this->filename = filename;
	cout << "\n\033[0;32mStoring calibrated parameters in \033[0m" << filename << endl;
	cv::FileStorage fs(filename, cv::FileStorage::WRITE);

	if(flag == FLAG_SINGLE_CAMERA)
	{
		fs << "image_width" << imageWidth
			<< "image_height" << imageHeight
			<< "camera_matrix" << cameraMatrix1
			<< "distortion_coefficients" << distCoeffs1;
	}
	
	if(flag == FLAG_DOUBLE_CAMERAS)
	{
		fs << "camera1_width" << imageWidth
			<< "camera1_height" << imageHeight
			<< "camera1_intrinsics" << cameraMatrix1
			<< "camera1_distortion_coeffs" << distCoeffs1
			<< "camera2_width" << imageWidth
			<< "camera2_height" << imageHeight
			<< "camera2_intrinsics" << cameraMatrix2
			<< "camera2_distortion_coeffs" << distCoeffs2
			<< "camera2_to_camera1_rotation" << R
			<< "camera2_to_camera1_translation" << T
			<< "assess_error" << avgError;
	}
	fs.release();
}

// calculate camera parameters
double Calibrator::calcCameraParas(string directory)
{
	cout << "\n\033[0;32m********** Calculate Camera(s) Parameters **********\033[0m\n";
	vector<vector<cv::Point3f> > objectPoints;	
	vector<cv::Point3f> boardModel = setBoardModel();
	
	// calculate camera parameters with one camera
	if(flag == FLAG_SINGLE_CAMERA)
	{
		cv::Mat image;
		vector<vector<cv::Point2f> > imagePoints;
		
		for(int i = 0; i < n_boards; i++)
		{
			image = cv::imread(directory + imageNames[i], -1);
			vector<cv::Point2f> corners;

			bool found = cv::findChessboardCorners(image, board_sz, corners);
			cout << "\n\033[0;32mfindChessboardCorners state: \033[0m" << found << endl;
			if(image.channels() != 1)
			{
				cv::cvtColor(image, image, CV_RGB2GRAY);
			}
			cornerSubPix(image, corners,cv::Size(11, 11), cv::Size(-1, -1),
					cv::TermCriteria(CV_TERMCRIT_ITER + CV_TERMCRIT_EPS, 300, 0.01));
			drawChessboardCorners(image, board_sz, corners, found);
			imagePoints.push_back(corners);
			objectPoints.push_back(boardModel);

			cout << "\033[0;32mCollected our \033[0m" << (int)imagePoints.size() 
				<< "\033[0;32m of \033[0m" << n_boards
				<< "\033[0;32m needed chessboard images \033[0m\n" << endl;
			cv::imshow("Calibration", image);
			
			if(cv::waitKey(1000) == 27)
				exit(0);
		}
		cv::destroyWindow("Calibration");

		double err = cv::calibrateCamera(objectPoints, 
			imagePoints, 
			imageSize, 
			cameraMatrix1, 
			distCoeffs1,
			cv::noArray(),
			cv::noArray(),
			cv::CALIB_FIX_PRINCIPAL_POINT
			);
		return 0;
	}
	
	// calculate camera parameters with DCM
	if(flag == FLAG_DOUBLE_CAMERAS)
	{
		cv::Mat image1, image2;
		vector<vector<cv::Point2f> > imagePoints1;
		vector<vector<cv::Point2f> > imagePoints2;
		
		for(int i = 0; i < n_boards; i++)
		{
			image1 = cv::imread(directory + imageNames1[i], -1);
			image2 = cv::imread(directory + imageNames2[i], -1);
			vector<cv::Point2f> corners1, corners2;

			bool found1 = cv::findChessboardCorners(image1, board_sz, corners1);
			cout << "\n\033[0;32mfindChessboardCorners state (camera1): \033[0m" << found1;
			bool found2 = cv::findChessboardCorners(image2, board_sz, corners2);
			cout << "\n\033[0;32mfindChessboardCorners state (camera2): \033[0m" << found2 << endl;

			if(image1.channels() != 1)
			{
				cv::cvtColor(image1, image1, CV_RGB2GRAY);
			}
			if(image2.channels() != 1)
			{
				cv::cvtColor(image2, image2, CV_RGB2GRAY);
			}
			cornerSubPix(image1, corners1,cv::Size(11, 11), cv::Size(-1, -1),
					cv::TermCriteria(CV_TERMCRIT_ITER + CV_TERMCRIT_EPS, 300, 0.01));
			cornerSubPix(image2, corners2,cv::Size(11, 11), cv::Size(-1, -1),
					cv::TermCriteria(CV_TERMCRIT_ITER + CV_TERMCRIT_EPS, 300, 0.01));
			drawChessboardCorners(image1, board_sz, corners1, found1);
			drawChessboardCorners(image2, board_sz, corners2, found2);

			imagePoints1.push_back(corners1);
			imagePoints2.push_back(corners2);
			objectPoints.push_back(boardModel);

			cout << "\033[0;32mCollected our \033[0m" << (int)imagePoints1.size() 
				<< "\033[0;32m of \033[0m" << n_boards
				<< "\033[0;32m needed chessboard images \033[0m\n" << endl;
			cv::imshow("Calibration (camera1)", image1);
			cv::imshow("Calibration (camera2)", image2);
			
			if(cv::waitKey(1000) == 27)
				exit(0);
		}
		cv::destroyAllWindows();

		double err1 = cv::calibrateCamera(objectPoints, 
			imagePoints1, 
			imageSize, 
			cameraMatrix1, 
			distCoeffs1,
			cv::noArray(),
			cv::noArray(),
			cv::CALIB_FIX_PRINCIPAL_POINT
			);
		double err2 = cv::calibrateCamera(objectPoints, 
			imagePoints2, 
			imageSize, 
			cameraMatrix2, 
			distCoeffs2,
			cv::noArray(),
			cv::noArray(),
			cv::CALIB_FIX_PRINCIPAL_POINT
			);

		cv::Mat E;
		double err_relative = cv::stereoCalibrate(objectPoints,
			imagePoints1, imagePoints2,
			cameraMatrix1, distCoeffs1,
			cameraMatrix2, distCoeffs2,
			imageSize, R, T, E, F, cv::CALIB_FIX_INTRINSIC,
			cv::TermCriteria(CV_TERMCRIT_ITER+CV_TERMCRIT_EPS, 100, 1e-5));

		double avgError = assessError(imagePoints1, imagePoints2);
		return avgError;
	}
}

// print camera parameters after calibrating
// it reads data from filename
void Calibrator::printCameraParas()
{
	cv::FileStorage fs(filename, cv::FileStorage::READ);
	if(fs.isOpened())
	{
		if(flag == FLAG_SINGLE_CAMERA)
		{
			cout << "\033[0;32m******** Calibrated Parameters ********\033[0m";
			cout << "\n\033[0;32mimage width: \033[0m" << (int)fs["image_width"];
			cout << "\n\033[0;32mimage height: \033[0m" << (int)fs["image_height"];
		
			cv::Mat intrinsic_matrix_loaded, distortion_coeffs_loaded;
			fs["camera_matrix"] >> intrinsic_matrix_loaded;
			fs["distortion_coefficients"] >> distortion_coeffs_loaded;
			cout << "\n\033[0;32mintrinsic matrix: \033[0m" << intrinsic_matrix_loaded;
			cout << "\n\033[0;32mdistortion coefficients: \033[0m" << distortion_coeffs_loaded;
			cout << "\n\n\033[0;32mDone!\033[0m\n";
		}

		if(flag == FLAG_DOUBLE_CAMERAS)
		{
			cv::Mat camera1_intrinsics_matrix, camera1_distortion_coeffs_matrix;
			cv::Mat camera2_intrinsics_matrix, camera2_distortion_coeffs_matrix;
			cv::Mat camera2_to_camera1_R, camera2_to_camera1_T;
			fs["camera1_intrinsics"] >> camera1_intrinsics_matrix;
			fs["camera1_distortion_coeffs"] >> camera1_distortion_coeffs_matrix;
			fs["camera2_intrinsics"] >> camera2_intrinsics_matrix;
			fs["camera2_distortion_coeffs"] >> camera2_distortion_coeffs_matrix;
			fs["camera2_to_camera1_rotation"] >> camera2_to_camera1_R;
			fs["camera2_to_camera1_translation"] >> camera2_to_camera1_T;
		
			cout << "\n\033[0;32m--------------- camera1 ---------------\033[0m\n";
			cout << "\033[0;32mwidth * height: \033[0m" << (int)fs["camera1_width"] 
				<< " * " << (int)fs["camera1_height"];
			cout << "\n\033[0;32mintrinsic matrix: \033[0m" << camera1_intrinsics_matrix;
			cout << "\n\033[0;32mdistortion coefficients: \033[0m" 
				<< camera1_distortion_coeffs_matrix;
			cout << endl;

			cout << "\n\033[0;32m--------------- camera2 ---------------\033[0m\n";
			cout << "\033[0;32mwidth * height: \033[0m" << (int)fs["camera2_width"]
				<< " * " << (int)fs["camera2_height"];
			cout << "\n\033[0;32mintrinsic matrix: \033[0m" << camera2_intrinsics_matrix;
			cout << "\n\033[0;32mdistortion coefficients: \033[0m" 
				<< camera2_distortion_coeffs_matrix;
			cout << endl;

			cout << "\n\033[0;32m---------------- camera2 to camera1 ---------------\033[0m\n";
			cout << "\033[0;32mRotation matrix: \033[0m" << camera2_to_camera1_R;
			cout << "\n\033[0;32mTranslation matrix: \033[0m" << camera2_to_camera1_T;
			cout << endl;

			cout << "\n\033[0;32mAssess Error: \033[0m" << (double)fs["assess_error"];
			cout << endl;

			cout << "\n\033[0;32mDone!\033[0m" << endl;
		}
	}
	else
	{
		cerr << "\033[0;32mERROR: Fail to open\033[0m\n" << filename << endl;
		exit(0);
	}
	fs.release();
}

// assess results after calibrating DCM, and it is contained in function calcCameraParas(),
// so generally you don't use it alone.
// src1: imagePoints1
// src2: imagePoints2
// Before using it, you need to know cameraMatrix1, distCoeffs1, cameraMatrix2, distCoeffs2, F;
// or you can set them with functions as follows:
/* 
	void setCameraMatrix1(cv::Mat M1);
	void setDistCoeffs1(cv::Mat D1);
	void setCameraMatrix2(cv::Mat M2);
	void setDistCoeffs2(cv::Mat D2);
	void setF(cv::Mat F);
*/
double Calibrator::assessError(vector<vector<cv::Point2f> > src1, 
		vector<vector<cv::Point2f> > src2)
{
	double avgError = 0;
	vector<cv::Point3f> lines[2];

	for(int i = 0; i < n_boards; i++)
	{
		vector<cv::Point2f>& pt0 = src1[i];
		vector<cv::Point2f>& pt1 = src2[i];

		cv::undistortPoints(pt0, pt0, cameraMatrix1, distCoeffs1, cv::Mat(), cameraMatrix1);
		cv::undistortPoints(pt1, pt1, cameraMatrix2, distCoeffs2, cv::Mat(), cameraMatrix2);
		cv::computeCorrespondEpilines(pt0, 1, F, lines[0]);
		cv::computeCorrespondEpilines(pt1, 2, F, lines[1]);
		
		for(int j = 0; j < board_n; j++)
		{
			double error = fabs(pt0[j].x * lines[1][j].x + pt0[j].y * lines[1][j].y 
					+ lines[1][j].z) + fabs(pt1[j].x * lines[0][j].x + pt1[j].y * lines[0][j].y
						+ lines[0][j].z);
			avgError += error;
		}
	}
	avgError = avgError / (n_boards * board_n);

	return avgError;
}

// show rectified images with SGBM algorithm
void Calibrator::showRectified(cv::Mat image1, cv::Mat image2, int* stereoSGBMParas)
{
	cout << "\n\033[0;32m********** Stereo Rectify **********\033[0m\n";
	cv::Mat R1, R2, P1, P2, Q, map11, map12, map21, map22;
	cv::stereoRectify(cameraMatrix1, distCoeffs1, cameraMatrix2, distCoeffs2,
			imageSize, R, T, R1, R2, P1, P2, Q, 0);
	bool isVerticalStereo = fabs(P2.at<double>(1, 3)) > fabs(P2.at<double>(0, 3));

	cv::initUndistortRectifyMap(cameraMatrix1, distCoeffs1, R1, P1, imageSize,
			CV_16SC2, map11, map12);
	cv::initUndistortRectifyMap(cameraMatrix2, distCoeffs2, R2, P2, imageSize,
			CV_16SC2, map21, map22);

	cv::Mat pair;
	if(!isVerticalStereo)
		pair.create(imageHeight, imageWidth * 2, CV_8UC3);
	else
		pair.create(imageHeight * 2, imageWidth, CV_8UC3);

	cv::Ptr<cv::StereoSGBM> stereo = cv::StereoSGBM::create(stereoSGBMParas[0],
			stereoSGBMParas[1], stereoSGBMParas[2], stereoSGBMParas[3],
			stereoSGBMParas[4], stereoSGBMParas[5], stereoSGBMParas[6],
			stereoSGBMParas[7], stereoSGBMParas[8], stereoSGBMParas[9],
			stereoSGBMParas[10]);
	
	cv::Mat img1r, img2r, disp, vdisp;
	cv::remap(image1, img1r, map11, map12, cv::INTER_LINEAR);
	cv::remap(image2, img2r, map21, map22, cv::INTER_LINEAR);
	
	if(!isVerticalStereo)
	{
		stereo->compute(img1r, img2r, disp);
		cv::normalize(disp, vdisp, 0, 256, cv::NORM_MINMAX, CV_8U);

		cv::Mat part = pair.colRange(0, imageWidth);
		cvtColor(img1r, part, CV_GRAY2BGR);
		part = pair.colRange(imageWidth, imageWidth * 2);
		cvtColor(img2r, part, CV_GRAY2BGR);
		
		for(int j = 0; j < imageHeight; j += 16)
			cv::line(pair, cv::Point(0, j), cv::Point(imageWidth * 2, j),
					cv::Scalar(0, 255, 0));
		
		cv::imshow("disparity", vdisp);
	}
	else
	{
		cv::Mat part = pair.rowRange(0, imageHeight);
		cv::cvtColor(img1r, part, CV_GRAY2BGR);
		part = pair.rowRange(imageHeight, imageHeight * 2);
		cv::cvtColor(img2r, part, CV_GRAY2BGR);

		for(int j = 0; j < imageWidth; j += 16)
			cv::line(pair, cv::Point(0, j), cv::Point(imageHeight * 2),
					cv::Scalar(0, 255, 0));
	}

	cv::FileStorage fs("stereoRectifiedParas.xml", cv::FileStorage::WRITE);
	fs << "disparity" << vdisp
		<< "R1" << R1
		<< "R2" << R2
		<< "P1" << P1
		<< "P2" << P2
		<< "Q" << Q;
	fs.release();
		
	cv::imshow("rectified", pair);
	if((cv::waitKey() & 255) == 27)
		return;
}

// get elements' values
string Calibrator::getFilename()
{
	return filename;
}

int Calibrator::getnBoards()
{
	return n_boards;
}

cv::Size Calibrator::getImageSize()
{
	return imageSize;
}

cv::Mat Calibrator::getCameraMatrix1()
{
	return cameraMatrix1;
}

cv::Mat Calibrator::getDistCoeffs1()
{
	return distCoeffs1;
}

cv::Mat Calibrator::getCameraMatrix2()
{
	return cameraMatrix2;
}

cv::Mat Calibrator::getDistCoeffs2()
{
	return distCoeffs2;
}

cv::Mat Calibrator::getR()
{
	return R;
}

cv::Mat Calibrator::getT()
{
	return T;
}

cv::Mat Calibrator::getF()
{
	return F;
}

// set elements' values
void Calibrator::setFilename(string filename)
{
	this->filename = filename;
}

void Calibrator::setCameraMatrix1(cv::Mat M1)
{
	cameraMatrix1 = M1;
}

void Calibrator::setDistCoeffs1(cv::Mat D1)
{
	distCoeffs1 = D1;
}

void Calibrator::setCameraMatrix2(cv::Mat M2)
{
	cameraMatrix2 = M2;
}

void Calibrator::setDistCoeffs2(cv::Mat D2)
{
	distCoeffs2 = D2;
}

void Calibrator::setR(cv::Mat R)
{
	this->R = R;
}

void Calibrator::setT(cv::Mat T)
{
	this->T = T;
}

void Calibrator::setF(cv::Mat F)
{
	this->F = F;
}

void Calibrator::setCameraMatrices(cv::Mat M1, cv::Mat D1,
		cv::Mat M2, cv::Mat D2, cv::Mat R,
		cv::Mat T, cv::Mat F)
{
	cameraMatrix1 = M1;
	distCoeffs1 = D1;
	cameraMatrix2 = M2;
	distCoeffs2 = D2;
	this->R = R;
	this->T = T;
	this->F = F;
}














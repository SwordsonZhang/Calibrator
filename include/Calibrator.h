#ifndef CALIBRATOR_H_
#define CALIBRATOR_H_

#include <string>
#include <opencv2/core/core.hpp>

using namespace std;

enum {FLAG_SINGLE_CAMERA = 0, FLAG_DOUBLE_CAMERAS = 1};

class Calibrator
{
	private:
		int imageWidth;           // width of image size
		int imageHeight;          // height of image size
		int board_w;              // inner corners of a row on your chessboard
		int board_h;              // inner corners of a column on your chessboard
		int n_boards;             // number of calibrated images 
		int board_n;              // number of inner corners on your chessboard
		float squareWidth;        // side length of a square on your chessboard
		int flag;                 // symbol to calibrate one camera or double-camera module(DCM)
		string filename;          // filename storing your results
		string* imageNames;       // names of calibrated images with a single camera
		string* imageNames1;      // names of calibrated images with camera1 of DCM
		string* imageNames2;      // names of calibrated images with camera2 of DCM
		cv::Size imageSize;       // image size
		cv::Size board_sz;        // size of inner corners
		cv::Mat cameraMatrix1;    // intrinsic parameters of one camera or camera1 of DCM
		cv::Mat distCoeffs1;      // distortion coefficients of one camera or camera1 of DCM
		cv::Mat cameraMatrix2;    // intrinsic parameters of camera2 of DCM
		cv::Mat distCoeffs2;      // distortion coefficients of camera2 of DCM
		cv::Mat R;                // rotation matrix from camera2 to camera1
		cv::Mat T;                // transformation matrix from camera2 to camera1
		cv::Mat F;                // fundermental matrix from camera2 to camera1
	
	public:
		Calibrator();
		Calibrator(int imageWidth, int imageHeight,
			int board_w, int board_h, 
			int n_boards, float squareWidth, 
			string filename, int flag);
		Calibrator(string filename);
		~Calibrator();
		void setCalibParas(int imageWidth, int imageHeight, 
				int board_w, int board_h, int n_boards,
				float squareWidth, string filename,
				int flag);
		void setImageNames();
		void saveImages(int frameNumber, string directory,
				cv::Mat frame1, cv::Mat frame2 = cv::Mat());
		vector<cv::Point3f> setBoardModel();
		double calcCameraParas(string directory = "");	
		void saveCameraParas(double avgError = 0);
		void printCameraParas();
		double assessError(vector<vector<cv::Point2f> > src1,
					vector<vector<cv::Point2f> > src2);
		void showRectified(cv::Mat image1, cv::Mat image2, int* stereoSGBMParas);
		
		// get elements' values of Calibrator
		string getFilename();
		int getnBoards();
        cv::Size getImageSize();
		cv::Mat getCameraMatrix1();
		cv::Mat getDistCoeffs1();
		cv::Mat getCameraMatrix2();
		cv::Mat getDistCoeffs2();
		cv::Mat getR();
		cv::Mat getT();
		cv::Mat getF();
		
		// set elements' values of Calibrator 
		void setFilename(string filename);
		void setCameraMatrix1(cv::Mat M1);
		void setDistCoeffs1(cv::Mat D1);
		void setCameraMatrix2(cv::Mat M2);
		void setDistCoeffs2(cv::Mat D2);
		void setR(cv::Mat R);
		void setT(cv::Mat T);
		void setF(cv::Mat F);
		void setCameraMatrices(cv::Mat M1, cv::Mat D1, 
				cv::Mat M2 = cv::Mat(), cv::Mat D2 = cv::Mat(),
				cv::Mat R = cv::Mat(), cv::Mat T = cv::Mat(), 
				cv::Mat F = cv::Mat());
};

#endif

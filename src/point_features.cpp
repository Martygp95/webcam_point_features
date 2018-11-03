
//OpenCV
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"

//std
#include <iostream>
#include <cstdlib>
#include <vector>

//consts
const unsigned int MIN_NUM_FEATURES = 10; //minimum number of point fetaures

int main(int argc, char *argv[])
{
    cv::VideoCapture camera; //OpenCV video capture object
    cv::Mat image; //OpenCV image object
    cv:: Mat mask;
    int h_divisions = 4;
    int v_divisions = 3; 
    int n_cols = image.rows;
    int n_rows = image.cols;
    int h_ws,v_ws,i,j,k,l,Px,Py;
    int cam_id; //camera id . Associated to device number in /dev/videoX
    cv::Ptr<cv::ORB> orb_detector = cv::ORB::create(); //ORB point feature detector
    orb_detector->setMaxFeatures(MIN_NUM_FEATURES);
    std::vector<cv::KeyPoint> point_set; //set of point features
    cv::Mat descriptor_set; //set of descriptors, for each feature there is an associated descriptor

	//check user args
	switch(argc)
	{
		case 1: //no argument provided, so try /dev/video0
			cam_id = 0;
			break;
		case 2: //an argument is provided. Get it and set cam_id
			cam_id = atoi(argv[1]);
			break;
		default:
			std::cout << "Invalid number of arguments. Call program as: webcam_capture [video_device_id]. " << std::endl;
			std::cout << "EXIT program." << std::endl;
			break;
	}

	//advertising to the user
	std::cout << "Opening video device " << cam_id << std::endl;

    //open the video stream and make sure it's opened
    if( !camera.open(cam_id) )
	{
        std::cout << "Error opening the camera. May be invalid device id. EXIT program." << std::endl;
        return -1;
    }

    //Process loop. Capture and point feature extraction. User can quit pressing a key
    while(1)
	{
		//Read image and check it. Blocking call up to a new image arrives from camera.
        if(!camera.read(image))
		{
            std::cout << "No image" << std::endl;
            cv::waitKey();
        }
	

    //**************** Find ORB point fetaures and descriptors ****************************

        //clear previous points
        point_set.clear();
	cv::Mat mask = cv::Mat::zeros(cv::Size(image.rows, image.cols), CV_8UC1);
	//std::cout << "Màscara = " << std::endl << " " << h_divisions << std::endl << std::endl;
	//cv::waitKey(10000);

        h_ws = mask.cols/h_divisions;    // =h_window_size
	v_ws = mask.rows/v_divisions;   // =v_window_size


	for(int i=0; i < h_divisions; i++)
	{
		for (int j=0; j < v_divisions ; j++)
		{
			for (k=0; k<h_ws; k++)
			{
				for (l=0; l<v_ws; l++)
				{

				Px = (i*h_ws)+k; 
				Py = (j*v_ws)+l;	

			        mask.at<cv::Vec3b>(Px,Py)[0] = 255;
			       // mask.at<cv::Vec3b>(Px,Py)[1] = 255;  
			       //mask.at<cv::Vec3b>(Px,Py)[2] = 255;  

				}
			}

		//detect and compute(extract) features
	 	orb_detector->detectAndCompute(image, mask, point_set, descriptor_set);
		//draw points on the image
	 	cv::drawKeypoints(image, point_set, image, 255, cv::DrawMatchesFlags::DEFAULT);
		//show image
		cv::imshow("Output Window", image);
		cv::waitKey(10);	
	 	cv::Mat mask = cv::Mat::zeros(cv::Size(image.rows, image.cols), CV_8UC1);
		}	
	} 
	
//********************************************************************     

		//Waits 30 millisecond to check if 'q' key has been pressed. If so, breaks the loop. Otherwise continues.
    	if( (unsigned char)(cv::waitKey(30) & 0xff) == 'q' ) break;
    }   
}

//includes for python
//#include "C:\Python27\include\Python.h"
#include "stdafx.h"
#include "C:\Users\Conference Room\Downloads\boost_1_62_0\boost\python\detail\wrap_python.hpp"//to avoid the 'cannot open python_d.lib' error
#include "C:\Python27\Lib\site-packages\numpy\core\include\numpy\arrayobject.h"
#include <sstream>
#include <string.h>
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION

//includes for opencv
#include "C:\opencv\build\include\opencv2\core\core.hpp"
#include "C:\opencv\build\include\opencv2\highgui\highgui.hpp"
#include "C:\opencv\build\include\opencv2\imgproc\imgproc.hpp"
#include "C:\opencv\build\include\opencv\cv.h"
#include "C:\opencv\build\include\opencv\highgui.h"
#include "C:\opencv\build\include\opencv2\core\core_c.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fstream>
#include "windows.h"
#include "ROI_Array.h"

using namespace cv;
using namespace std;

void init_numpy() {import_array()};
//static PyObject *new_arr();
//CV_EXPORTS_W void mouse_call(int event,int x,int y,int,void*);
void mouse_call(int event, int x, int y, int, void*);
void getROI(int HEIGHT, int WIDTH, double py_return[][12], PyObject *pFunc);
void callPython(int HEIGHT, int WIDTH, double py_return[][12], PyObject *pFunc);
//CV_EXPORTS_W static PyObject *roi_array(PyObject *narray);

bool leftDown=false,leftup=false;
Mat image;
Point cor1,cor2;
Rect box;

void importPyModule(PyObject *pFunc) {
	Py_Initialize();
	import_array();	

	//import module
	const char *module_name = "loadROI";
	PyObject *pName = PyUnicode_FromString(module_name);
	PyObject *pModule = PyImport_Import(pName);
	Py_DECREF(pName);
	
	//import function
	const char *func_name = "npReturn";
	pFunc = PyObject_GetAttrString(pModule, func_name);

	Py_Finalize();
}

void getROI(int HEIGHT, int WIDTH, double py_return[][12], PyObject *pFunc) {
	Py_Initialize();
	import_array();
	
	image = imread("TestIn.bmp", CV_LOAD_IMAGE_COLOR);

	if(!image.data) {
		cout << "Could not open or find the image" << endl;
		std::cin.get();
	}

	cvNamedWindow("Original", CV_WINDOW_NORMAL);
	cv::resizeWindow("Original", 1200, 700); //1200 = width, 700 = height
	imshow("Original", image);

	setMouseCallback("Original",mouse_call); //setting the mouse callback for selecting the region with mouse

	printf("\n===============================================\n");
	printf("\t       **ROI Selection**\n");
	printf("\nUse the mouse to select a region of interest.\n");
	printf(" Press S to save an image.\n");
	printf(" Press C to convert to a c++ array.\n");
	printf(" Press Q to exit ROI selection.\n");		

	/*//import module
	const char *module_name = "loadROI";
	PyObject *pName = PyUnicode_FromString(module_name);
	PyObject *pModule = PyImport_Import(pName);
	Py_DECREF(pName);
	
	//import function
	const char *func_name = "npReturn";
	PyObject *pFunc = PyObject_GetAttrString(pModule, func_name);*/

	while(char(waitKey(0)!='q')) //waiting for the 'q' key to finish the execution
	{		
		int runMod = 0;
		int saved = 1;		

		cout.flush();
		char s = waitKey(0);
		//s == 115
		if (s == 115)
        {
            //cvSetImageROI(image, box);
			cv::Mat ROI = image(box);

            //Convert image to grayscale
			//cv::Mat grayImage = cv::cvarrToMat(img, true);
			cv::Mat grayImage;
			//cvtColor(ROI, grayImage, CV_BGR2GRAY);
			//cv::Mat grayImage = image;
			//IplImage* grayImage = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
			cvtColor(ROI, grayImage, CV_BGR2GRAY);

			//Apply thresholding to make a binary
			cv::Mat binaryImage(grayImage.size(), grayImage.type());
			threshold(grayImage, binaryImage, 0, 255, 3);//set threshold type to 3(
			//IplImage* binary = cvCloneImage(grayImage);
			//cvThreshold(grayImage, binary, 128, 255, CV_THRESH_BINARY);
			
			//Open the file in write mode
			std::ofstream outputFile;
			outputFile.open("C:/Users/Conference Room/Documents/C++ to Python/ROI/ROI/ROI_Binary.txt");

			//double (*c_arr)[SIZE] = {new double [binaryImage.cols][binaryImage.rows]};

			//Iterate through pixels
			for (int r = 0; r < binaryImage.rows; r++)
			{
				for (int c = 0; c < binaryImage.cols; c++)
				{
					/*Vec3b pixel = ROI.at<Vec3b>(r,c);
					for(int k = 0; k < ROI.channels(); k++) {
						uchar value = pixel.val[k];
						c_arr[r][c] = value;
					}*/
					//pixel >> c_arr[c][r];
					double pixel = binaryImage.at<uchar>(r,c);
					outputFile << pixel << ' ';
					//int value = pixel;
  					//c_arr[r][c] << pixel << ' ';
					//std::cin >> pixel >> c_arr[r][c];
					//std:: cout << c_arr[r][c] << pixel << ' ';
					//c_arr[r][c] = pixel;
				}
				//std::cout << c_arr << std::endl;
				outputFile << endl;
			}

			/*for(int y = 0; y < ROI.rows; y++) {
				for(int x = 0; x < ROI.cols; x++) {
					int pixel = ROI.at<uchar>(y,x);
					c_arr[y][x] = pixel;
					//std::cin >> pixel >> c_arr[y][x];
				}				
			}*/

			//close the file
			outputFile.close();

            //char *name = new char[100];
            //sprintf(name, "C:/Users/Conference Room/Documents/C++ to Python/interface/interface/ROI_%d.jpg", saved);
            //cvSaveImage(name, ROI);
			//imwrite("C:/Users/Conference Room/Documents/C++ to Python/ROI/ROI/ROI.jpg", ROI);
            //cvResetImageROI(ROI);
            saved += 1;
			MessageBox( nullptr, TEXT( "Image saved." ), TEXT( "Message" ), MB_OK );
            printf("saved\n");
			cvDestroyWindow("Cropped Image");

			/*for(int i = 0; i < HEIGHT; i++) {
				for(int j = 0; j < WIDTH; j++) {
					std::cout << c_arr[i][j] << ' '; 
				}
				std::cout << std::endl;
			}*/
        }
		else if(s == 99) {				

			callPython(HEIGHT, WIDTH, py_return, pFunc);
			//Py_DECREF(pModule);
			
			printf("\n===============================================\n");
			printf("\t       **ROI Selection**\n");
			printf("\nUse the mouse to select a region of interest.\n");
			printf(" Press S to save an image.\n");
			printf(" Press C to convert to a c++ array.\n");
			printf(" Press Q to exit ROI selection.\n");
		}
		
	}
	//Py_Finalize();
	cvDestroyWindow("Original");
}

//method to record input from the mouse
void mouse_call(int event,int x,int y,int,void*)
{
	if(event==EVENT_LBUTTONDOWN)
	{
	leftDown=true;
	cor1.x=x;
	cor1.y=y;
	cout <<"Corner 1: "<<cor1<<endl;
	}
	
	if(event==EVENT_LBUTTONUP)
	{
		if(abs(x-cor1.x)>20&&abs(y-cor1.y)>20) //checking whether the region is too small
		{
			leftup=true;
			cor2.x=x;
			cor2.y=y;
			cout<<"Corner 2: "<<cor2<<endl;
		}
		else
		{
			cout<<"Select a region more than 20 pixels"<<endl;
		}
	}

	if(leftDown==true&&leftup==false) //when the left button is down
	{
		Point pt;
		pt.x=x;
		pt.y=y;
		Mat temp_img=image.clone();
		rectangle(temp_img,cor1,pt,Scalar(0,0,255)); //drawing a rectangle continuously
		imshow("Original",temp_img);

	}
	if(leftDown==true&&leftup==true) //when the selection is done
	{

		box.width=abs(cor1.x-cor2.x);
		box.height=abs(cor1.y-cor2.y);
		box.x=min(cor1.x,cor2.x);
		box.y=min(cor1.y,cor2.y);
		Mat crop(image,box); //Selecting a ROI from the original pic
		namedWindow("Cropped Image");
		imshow("Cropped Image",crop); //showing the cropped image
		leftDown=false;
		leftup=false;	
	}
}

void draw_box(IplImage* img, CvRect rect ){
    cvRectangle( img, cvPoint(box.x, box.y), cvPoint(box.x+box.width,box.y+box.height),
                cvScalar(0,0,255),2 );
}

void callPython(int HEIGHT, int WIDTH, double py_return[][12], PyObject *pFunc) 
{

	/*const int ND = 2;
	npy_intp dims[2] = {2,12};
	PyObject *pArray = PyArray_SimpleNewFromData(ND, dims, NPY_LONGDOUBLE, reinterpret_cast<void*>(py_return));*/
		
	//set return PyObject variable
	PyObject *pReturn = PyObject_CallFunctionObjArgs(pFunc, NULL);//call the function stored in pFunc
	PyArrayObject *np_ret = reinterpret_cast<PyArrayObject*>(pReturn);//return an array	

	int len = PyArray_SHAPE(np_ret)[0];
	double* c_out = reinterpret_cast<double*>(PyArray_DATA(np_ret));

	for(int i = 0; i < HEIGHT; i++) {
		for(int j = 0; j < WIDTH; j++) {
			py_return[i][j] = *c_out;
		}
	}
	//fill array
	int i, j = 0;
	for (int i = 0; i < 24; i++)
		/*if (i == 12) 
			py_return[1][i] = c_out[i];*/
		//else 
		py_return[0][i] = c_out[i];
			//std::cout << c_out[i] << ' ';

		//std::cout << std::endl;
	//print array
	printf("\n\n");
	std::cout << "C++ array: " << std::endl;
	for(int i = 0; i < HEIGHT; i++) {		
		printf(" [");
		for(int j = 0; j < WIDTH; j++) {			
			cout << py_return[i][j] << ',' << ' ';
		}
		printf("\b\b]\n");
	}
	cout << endl;
	
	//write to file for gnuplot
	std::ofstream outputFile;
	outputFile.open("C:/Users/Conference Room/Documents/C++ to Python/ROI/ROI/py_return_plot.dat");

	int count = 1;
	for(int i = 0; i < 2; i++) {
		for(int j = 0; j < 12; j++) {
			if(count % 2 == 0) {
				outputFile << py_return[i][j] << endl;
			}else {
				outputFile << py_return[i][j] << " ";
			}
			count++;
		}
	}
	outputFile.close();

	//Py_DECREF(pFunc);
    //Py_DECREF(pModule);
    //Py_DECREF(np_arg);
    //Py_DECREF(np_ret);
	//Py_DECREF(pReturn);
	//Py_DECREF(pName);
	//Py_Finalize();		
}
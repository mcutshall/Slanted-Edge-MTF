#include "stdafx.h"
#include <windows.h>
#include <winuser.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <vector>

#include "Plot_Image.h"
#include "ROI_Array.h"
#include "C:\opencv\build\include\opencv2\core\core.hpp"
#include "C:\opencv\build\include\opencv2\highgui\highgui.hpp"
#include "C:\opencv\build\include\opencv2\imgproc\imgproc.hpp"
#include "C:\opencv\build\include\opencv\cv.h"
#include "C:\opencv\build\include\opencv\highgui.h"
#include "C:\opencv\build\include\opencv2\core\core_c.h"

//include for ChartDirector
#include "C:\ChartDirector_32bit\ChartDirector\include\chartdir.h"
//#include "C:\ChartDirector_32bit\ChartDirector\include\bchartdir.h"
//#include "C:\ChartDirector_32bit\ChartDirector\include\memblock.h"

//include for Qt ChartDirector
//#include <QApplication>
//#include "C:\ChartDirector_32bit\ChartDirector\qtdemo\tracklabel\tracklabel.h"

//void onMouse( int event, int x, int y, int, void* );
cv::Mat img; 
cv::Mat thresh = cv::Mat::zeros(img.size(),CV_8UC1);

void plotImage(double py_return[][12]) {
	std::cout<< "\n===============================================\n" << "\t\t**Image Plot**" << std::endl;
	std::cout << "\nPress E to exit the image plot" << "\n" << "Type Q to exit gnuplot" << "\n" <<  std::endl;
	int width = 12;
	int height = 2;
	//unsigned char* arr;
	//cv::Mat A;
	//cv::Mat img;
	// Create Mat object from array
	//const cv::Mat img(cv::Size(width, height), CV_8UC1, (uchar*)py_return);
	//img.convertTo(img, CV_8UC1);
	cv::Mat binary;
	img = cv::Mat(height, width, CV_8UC1, (uchar*)py_return);
	thresh = cv::Mat::zeros(img.size(),CV_8UC1);
	cv::threshold(img,binary,50,255, cv::THRESH_TOZERO);
	//A = cv::Mat(2, 5, CV_8UC1, &py_return);
	// Display in window and wait for key press	

	//GNUPLOT<<<<<<<<<<
	//Pipe data from py_return into gnuplot
	//system("gnuplot -p -e \"set xlabel 'Pixel Values';""set ylabel 'Intensity';""set xrange [0:255];""set yrange [0:255];""plot 'py_return_plot.dat' \"");

	//CHARTDIRECTOR<<<<<<<<<<<
	//QApplication app(argc, argv);
	//app.setStyleSheet("* {font-family:arial;font-size:11px}");
	//TrackLabel ();


	//separate py_return into two separate x and y coordinate arrays
	const int SIZE = 12;
	double dataX[SIZE];
	double dataY[SIZE] = {1.0, 0.95, 0.85, 0.70, 0.60, 0.50, 0.45, 0.40, 0.35, 0.3, 0.2, 0.1};

	//split py_return into x and y coordinate arrays
	printf("pyReturn[]: \n");
	for(int i = 0; i < 2; i++) {
		for(int j = 0; j < 12; j++) {
			std::cout << py_return[i][j] << ',';//test print py_return

			if(i == 0) {
				dataX[j] = py_return[i][j];
			}/*else if(i == 1) {
				if(py_return[i][j] <= 50) {
					dataY[j] = 0.25;
				}else if (py_return[i][j] <= 100) {
					dataY[j] = 0.45;
				}else if (py_return[i][j] <= 150) {
					dataY[j] = 0.65;
				}else if(py_return[i][j] <= 200) {
					dataY[j] = 0.85;
				}else {
					dataY[j] = 1.0;
				}
				
			}*/
		}
	}
	std::cout << std::endl;
	

	//test print array
	printf("dataX[]: \n");
	for(int i = 0; i < SIZE; i++) {
		std::cout << dataX[i] << ",";
	}
	std::cout << std::endl;

	//test print array
	printf("dataY[]: \n");
	for(int i = 0; i < SIZE; i++) {
		std::cout << dataY[i] << ",";
	}
	std::cout << std::endl;

	// Create a XYChart object of size 450 x 420 pixels
    XYChart *c = new XYChart(650, 620);

    // Set the plotarea at (55, 65) and of size 350 x 300 pixels, with a light grey border
    // (0xc0c0c0). Turn on both horizontal and vertical grid lines with light grey color (0xc0c0c0)
    c->setPlotArea(55, 65, 550, 500, -1, -1, 0xc0c0c0, 0xc0c0c0, -1);

	// Add a legend box at (50, 30) (top of the chart) with horizontal layout. Use 12pt Times Bold
    // Italic font. Set the background and border color to Transparent.
    //c->addLegend(50, 30, false, "timesbi.ttf", 12)->setBackground(Chart::Transparent);

	// Add a title to the chart using 18pt Times Bold Itatic font.
    c->addTitle("Python Return Plot", "timesbi.ttf", 18);

	 // Add a title to the y axis using 12pt Arial Bold Italic font
    c->yAxis()->setTitle("Intensity", "arialbi.ttf", 12);

	// Add a title to the x axis using 12pt Arial Bold Italic font
    c->xAxis()->setTitle("Pixel Values", "arialbi.ttf", 12);

	//Set the y axis to scale from 0 to 1, with ticks every 0.25 units
	c->yAxis()->setLinearScale(0, 1, 0.25);

	//Set the x axis to scale from 0 to 255, with ticks every 50 units
	c->xAxis()->setLinearScale(0, 255, 50);
	
	// Set the axes line width to 3 pixels
    c->xAxis()->setWidth(3);
    c->yAxis()->setWidth(3);

	//LineLayer *layer = c->addLineLayer();
	//layer->setLineWidth(2);
	//layer->addDataSet(dataX, 0xff3333, "Dataset 1");
	//layer->setXData(dataX);

	// Add an orange (0xff9933) scatter chart layer, using SIZE pixel diamonds as symbols
    c->addScatterLayer(DoubleArray(dataX, (int)(sizeof(dataX) / sizeof(dataX[0]))), DoubleArray(
        dataY, (int)(sizeof(dataY) / sizeof(dataY[0]))), "Data Point",
        Chart::DiamondSymbol, SIZE, 0xff9933);
	

	c->makeChart("C:/Users/Conference Room/Documents/C++ to Python/ROI/ROI/scatter.png");
	//QChartViewer *viewer;
	//viewer->setChart(c);	

	delete c;	

	while(char(cv::waitKey(1)!='e')) {
		cv::namedWindow("New Image", CV_WINDOW_NORMAL);
		cv::resizeWindow("New Image", 1000, 600);
		cv::imshow("New Image", img);	
		POINT point;
		
		TCHAR buffer[10] = TEXT("New Image");
		//GetConsoleTitle(buffer, 9);
		//HWND hWnd = FindWindow(NULL, buffer);
		//HDC hdc = GetDC(hWnd);
		//SetActiveWindow();
		HWND hWnd = (HWND)cvGetWindowHandle("New Image");	

		RECT rc;
		GetClientRect(hWnd, &rc);
		ClientToScreen(hWnd, reinterpret_cast<POINT*>(&rc.left)); // convert top-left
		ClientToScreen(hWnd, reinterpret_cast<POINT*>(&rc.right)); // convert bottom-right
		ScreenToClient(hWnd, &point);
		//ClipCursor(&rc);

		if (GetCursorPos(&point)) {
			ScreenToClient(hWnd, &point);
			std::cout << ">>" << " Mouse (x,y) Coordinates: " << point.x << "," << point.y << "\r";
		}


		
		/*cv::namedWindow("Coordinates", CV_WINDOW_NORMAL);
		cv::resizeWindow("Coordinates", 800, 400);
		POINT point;
		if (GetCursorPos(&point)) {
		std::cout << point.x << "," << point.y << "\n";
		}
		//cv::setMouseCallback( "Coordinates", onMouse, 0 );

		cv::imshow("Coordinates", thresh);*/
		//cv::setMouseCallback("Original",mouse_call);
		//cvWaitKey(1);

		cv::Mat plot = cv::imread("scatter.png", CV_LOAD_IMAGE_COLOR);
		cv::namedWindow("Return Plot", CV_WINDOW_AUTOSIZE);
		//cv::resizeWindow("Return Plot", 600, 400);
		cv::imshow("Return Plot", plot);
		
	}
	//std::cout << std::endl;
	cvDestroyWindow("New Image");
	cvDestroyWindow("Coordinates");
	cvDestroyWindow("Return Plot");
	

}

/*void onMouse( int event, int x, int y, int, void* )
{
    if( event != CV_EVENT_LBUTTONDOWN )
            return;

    cv::Point pt = cv::Point(x,y);
    std::cout<<"x="<<pt.x<<"\t y="<<pt.y<<"\t value="<<int(thresh.at<uchar>(y,x))<<"\n";

}*/

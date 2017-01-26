//includes for python
//#include "C:\Python27\include\Python.h"
#include "stdafx.h"
#include "C:\Users\Conference Room\Downloads\boost_1_62_0\boost\python\detail\wrap_python.hpp"//to avoid the 'cannot open python_d.lib' error
#include "C:\Python27\Lib\site-packages\numpy\core\include\numpy\arrayobject.h"
#include <sstream>
#include <string.h>
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION

//includes for opencv
/*#include "C:\opencv\build\include\opencv2\core\core.hpp"*/
#include "C:\opencv\build\include\opencv2\highgui\highgui.hpp"
/*#include "C:\opencv\build\include\opencv2\imgproc\imgproc.hpp"
#include "C:\opencv\build\include\opencv\cv.h"
#include "C:\opencv\build\include\opencv\highgui.h"
#include "C:\opencv\build\include\opencv2\core\core_c.h"*/
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fstream>
#include "windows.h"
#include "ROI_Array.h"
#include "Plot_Image.h"
#include "Menu.h"

using namespace std;

int main()
{	
	//create 2 dimensional array
	const int HEIGHT = 2;//rows
	const int WIDTH = 12;//cols
	const int SIZE = 12;	
	double (*py_return)[SIZE] = {new double [HEIGHT][WIDTH]};

	//initialize the python interpreter
	Py_Initialize();	

	//import python module
	const char *module_name = "loadROI";
	PyObject *pName = PyUnicode_FromString(module_name);
	PyObject *pModule = PyImport_Import(pName);
	Py_DECREF(pName);
	
	//import function
	const char *func_name = "npReturn";
	PyObject *pFunc = PyObject_GetAttrString(pModule, func_name);

	showMenu(HEIGHT, WIDTH, py_return, pFunc);

	Py_Finalize();
	return 0;
} 
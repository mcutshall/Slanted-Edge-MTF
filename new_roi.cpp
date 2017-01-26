/*==============================================================================================================================

This .h file is called by loadROI.py to convert the pixel values stored in ROI_Binary.txt into a 2d NumPy array.
The reason this file is not included in ROI.cpp is that the python script setupROI.py would not compile with the 
opencv headers included in ROI.cpp. This source code is separate from the opencv headers and is therefore able
to compile and retrieve pixel values from a saved binary file.


*///============================================================================================================================

#include "stdafx.h"
#include "C:\Python27\include\Python.h"
#include "C:\Python27\Lib\site-packages\numpy\core\include\numpy\arrayobject.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#define NPY_NO_DEPRECATED_API NPY_1_9_API_VERSION


//function prototype
void init_numpy() {import_array()};
static PyObject *new_roi();


static PyObject *new_roi() {  
  // create the array in C++ on the heap
	Py_Initialize();//initialize the Python interpreter
	init_numpy();	
	
	const int HEIGHT = 200;//rows
	const int WIDTH = 200;//cols
	const int SIZE = 200;	
	const int ND = 2;
	double (*c_arr)[SIZE] = {new double [HEIGHT][WIDTH]};
		
	//std::cout << "Two dimensional C++ array created.\n" << std::endl;

	//std::cout << "Populating C++ array with values from 'ROI_Binary.txt'...\n" << std::endl;
	std::ifstream infile;
	infile.open("ROI_Binary.txt");
	if(!infile) {
		std::cout << "Error opening file.\n" << std::endl;
	}	
	if(infile.is_open()) {
		//std::cout << "File opened successfully.\n" << std::endl;
		/*while(infile >> temp) {
			roi_vector.push_back(temp);
		}*/
		
		while(!infile.eof()) {
			for(int i = 0; i < HEIGHT; i++) {
				for(int j = 0; j < WIDTH; j++) {
					infile >> c_arr[i][j];					
				}
			}
		}	
	}
	//std::cout << "Done.\n" << std::endl;

	/*for(int i = 0; i < HEIGHT; i++) {
		for(int j = 0; j < WIDTH; j++) {
			std::cout << c_arr[i][j] << ' '; 
		}
		std::cout << std::endl;
	}*/	   

	// return the array as a numpy array (numpy will free it later)
	//npy_intp dims[1] = {n};
	npy_intp dims[2] = {HEIGHT, WIDTH};	
	PyObject *narray = PyArray_SimpleNewFromData(ND, dims, NPY_DOUBLE, reinterpret_cast<void*>(c_arr));

	//tell numpy it has to free the data
	PyArray_ENABLEFLAGS((PyArrayObject*)narray, NPY_ARRAY_OWNDATA); 

	return narray;  
}

static PyMethodDef module_methods[] = {
  {"new_roi", (PyCFunction)new_roi, METH_NOARGS},
  {NULL, NULL, 0, NULL}};

PyMODINIT_FUNC initnew_roi() {
	(void) Py_InitModule("new_roi", module_methods);  
}
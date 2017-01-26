#include "stdafx.h"
#include "Menu.h"
#include "Plot_Image.h"
#include "ROI_Array.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include "C:\Users\Conference Room\Downloads\boost_1_62_0\boost\python\detail\wrap_python.hpp"

using namespace std;

void showMenu(int HEIGHT, int WIDTH, double py_return[][12], PyObject *pFunc) {
	char input;
	printf("===============================================\n");
	printf("\t\t**Main Menu**\n\n");
	printf("Choose an Option from the list below: \n Press G to select an ROI\n Press P to plot an image returned from Python \n"
			" Press Q to exit the program\n");
	printf(">>");

	scanf(" %c", &input);
	while(tolower(input) != 'g' && tolower(input) !='p' && tolower(input) !='q') {
		printf("Not a valid entry. Please try again\n");
		scanf(" %c", &input);
	}

	switch(tolower(input)) {
	case 'g':
		getROI(HEIGHT, WIDTH, py_return, pFunc);
		break;
	
	case 'p': 
		plotImage(py_return);
		break;

	case 'q': 
		exit(0);
	}
	showMenu(HEIGHT, WIDTH, py_return, pFunc);
}



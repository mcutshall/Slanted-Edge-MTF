#include "stdafx.h"
#include "C:\Users\Conference Room\Downloads\boost_1_62_0\boost\python\detail\wrap_python.hpp"//to avoid the 'cannot open python_d.lib' error
#include "C:\Python27\Lib\site-packages\numpy\core\include\numpy\arrayobject.h"

void getROI(int HEIGHT, int WIDTH, double py_return[][12], PyObject *pFunc);
void callPython(int HEIGHT, int WIDTH, double py_return[][12], PyObject *pFunc);
void mouse_call(int event,int x,int y,int,void*);
void importPyModule(PyObject pFunc);
//static PyObject *roi_array(PyObject *narray);
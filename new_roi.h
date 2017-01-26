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

void init_numpy() {import_array()};
static PyObject *new_roi();
from distutils.core import setup, Extension
#import cv

#include_dirs = ['C:\opencv\build\include'],
#libraries = ['opencv_core2411.lib', 'opencv_highgui2411.lib, opencv_imgproc2411.lib'],
#library_dirs = ['C:\opencv\build\x86\vc11\lib'],

module1 = Extension('new_roi', sources = ['new_roi.cpp'])

setup(name = "new_roi", version = '2.0', description = 'Create C++ numpy array',
      ext_modules = [module1])

print "Module Name: ", module1.name
print "Source File: ", module1.sources

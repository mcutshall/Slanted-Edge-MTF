# Slanted-Edge-MTF
Program developed for Ruda-Cardinal. Based on C++ and calls Python for data processing. 

This program was designed to interface with an Imperx Bobcat 2.0 CCD camera to analyze video image data, perform calculations, and plot results. The program is currently unfinished, and still requires a complete plotting function. For the purpose of testing, the program uses a static image instead of live video feed. This program is still a work in progress, and any feedback is appreciated. 

The program begins by accessing and initializing the camera feed. A 2-dimensional array is created for later user defined input. At this point the user is able to select a region of interest(ROI) using mouse input over the static slanted-edge image. The pixel values contained within the user defined ROI are then stored in the two dimensional array, which is then converted to a python object. C++ then calls a python script which accepts the filled c++ array and converts it to a numpy array for data processing. Another python script would then be used to perform other MTF calcutlations using the data contained within the numpy array. The array is then sent back to c++ and converted back to a c++ array. This process can be performed indefinitely, as a new ROI selection will overwrite the current selection. 

After an ROI has been selected, manipulated and sent back to c++, the image data is then sent to the plotting function. The plotting function shows intensity over a range of x-coordinate values, with intensity on the y-axis and x-coordinates on the x-axis. Within this plot is the ability to mouse-over the plot and have (x,y) data points displayed in a status bar at the bottom left of the plot window. 

The GUI is composed of a main menu with two sub menus. The main menu allows the user to select and ROI, plot and image, or exit the program. The ROI sub menu allows the user to save a selected ROI, convert an ROI to a numpy array, and exit back to the main menu. The plotting sub menu allows the user to plot an image (returned from python), and exit back to the main menu. 

The slanted-edge image is called 'TestIn.bmp'. A python setup script 'setupROI.py' is used to import the c++ module 'new_roi' from 'new_roi.cpp'. The python script 'loadROI.py' is used to call the module 'new_roi' to import the filled c++ array and convert it to a numpy array. 

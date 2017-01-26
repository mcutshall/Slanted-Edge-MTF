import numpy as np
#import cv2
from new_roi import *
#import roi_array

#ROI = np.array(new_roi())
#ROI.astype(np.int64)

#print ""
#print type(ROI)
#print ROI.shape
#print ""
#print ROI    
    

#nd_return = np.array(ROI)
#nd_return.resize((2,12))

def npReturn(): 
    ROI = np.array(new_roi())
    #ROI.astype(np.int64)

    print ""
    print type(ROI)
    print ROI.shape
    print ""
    print ROI 
    
    #ROI = np.array(new_roi())
    nd_return = np.array(ROI)
    nd_return.resize((2,12))
    
    print ""
    print "Return array shape: "
    print nd_return.shape
    print ""
    print nd_return
    return nd_return
    


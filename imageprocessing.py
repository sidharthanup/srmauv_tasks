#!/bin/python3


import numpy as np
import cv2

max_area_circle=0
contour_max=[]

def shape_detect(c):            #this function compares all the areas of the figures bounded by the contours
    global max_area_circle      #based on the maximum area the value of contour_max is updated
    global contour_max
    area=cv2.contourArea(c)
    if area>max_area_circle:
        max_area_circle=area
        contour_max=c
    return

def contourplotAndcentroid(contour_max):
    cv2.drawContours(buoy_img,[contour_max],0,(0,255,0),2)      #plots the contour outline
    M=cv2.moments(contour_max)                                  #calculates the moments pertaining to the contours
    cX=int(M["m10"]/M["m00"])                                   #cX is the X coordinate of the centroid,cY is the Y coordinate
    cY=int(M["m01"]/M["m00"])
    centroid=(cX,cY)
    cv2.circle(buoy_img,centroid,1,(255,0,0),2);                #plot the centroid
    return (cX,cY)



def red_buoy():
    global contour_max
    global max_area_circle
    
    buoy_img_temp1 = cv2.imread("/home/sidharthanup/buoysf.jpg")
    lower_red = np.array([0,150,200])
    upper_red = np.array([15,255,255])
    mask = cv2.inRange(hsv,lower_red,upper_red)             #creates a mask between the ranges lower_red and upper_red
    res = cv2.bitwise_and( buoy_img_temp1, buoy_img_temp1, mask=mask)      

    (flags,contours,h) = cv2.findContours(mask,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)   #finds the contours 

    for c in contours:
        shape_detect(c)

    max_area_circle=0
    (X,Y)=contourplotAndcentroid(contour_max)
    print("The centroid of the red buoy is at a coordinate",(X,Y))
    return

def green_buoy():

    global contour_max
    global max_area_circle

    buoy_img_temp2 = cv2.imread("/home/sidharthanup/buoysf.jpg")
    lower_green = np.array([55,200,120])
    upper_green = np.array([80,255,255])
 
    
    mask = cv2.inRange(hsv,lower_green,upper_green)
    res = cv2.bitwise_and( buoy_img_temp2, buoy_img_temp2, mask=mask)

    (flags,contours,h) = cv2.findContours(mask,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)

    for c in contours:
        shape_detect(c)
    max_area_circle=0
    (X,Y)=contourplotAndcentroid(contour_max)
    print("The centroid of the green buoy is at a coordinate",(X,Y))
    return

def yellow_buoy():
    global contour_max
    global max_area_circle

    buoy_img_temp3 = cv2.imread("/home/sidharthanup/buoysf.jpg")
    lower_yellow = np.array([20,70,180])
    upper_yellow = np.array([40,255,255])

    
    mask = cv2.inRange(hsv,lower_yellow,upper_yellow)
    res = cv2.bitwise_and( buoy_img_temp3, buoy_img_temp3, mask=mask)

    (flags,contours,h) = cv2.findContours(mask,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)

    for c in contours:
        shape_detect(c)
    max_area_circle=0
    (X,Y)=contourplotAndcentroid(contour_max)
    print("The centroid of the yellow buoy is at coordinate",(X,Y))
    return

buoy_img = cv2.imread("/home/sidharthanup/buoysf.jpg")

hsv = cv2.cvtColor(buoy_img,cv2.COLOR_BGR2HSV)

red_buoy()
green_buoy()
yellow_buoy()


cv2.imshow('image', buoy_img)


k=cv2.waitKey(0);
cv2.destroyAllWindows()

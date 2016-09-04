# srmauv_tasks
Repo consists of the task 1(image processing) and task3(PID control) and algorithm/coding assignments

#1)Image Processing Task
      This task is implemented in python with opencv and numpy libraries imported.The brief algorithm is as follows:
         
          *The image "buoysf.jpg" is read and its color scheme is changed from rgb to hsv.This is because it is easier to work with the hsv color scheme.
          *The red_buoy() function is called.Two numpy arrays lower_red and upper_red are initialised(Their values are manually tuned). A mask is created from the range lower_red to upper_red on the hsv image. The isolated image in the mask region is obtained by the bitwise "and" of original image with itself restricted within the mask(the white region of the mask).
          *The findContours() function is used to return the contours of the white region of the mask.For all the contours returned the area it bounds is calculated and the contour with the highest area is saved to the variable contour_max.
          *The conourplotAndcentroid() function calculates plots and returns the centroid of the body represented by contour_max
           and also plots the contour ie contour_max.
          *The green_buoy() and yellow_buoy() functions does the same for the green and yellow buoy respectively.
          *The lower and upper numpy arrays are set by running the program for one color buoy and then adjusting the array values such that only the buoy is white in the mask image and the background is barely visible(i.e almost black).
          
          
#2)PID Controller Task
      This task is implemented in C++.The brief algorithm is as follows:
            
          *The current depth is returned by calling the function analog_read_currentdepth(). The depth value returned by the depth sensor(measured from the bottom/ocean bed) is assumed to be stored in the text file "analog_input_current.txt" and the value is read from this file and returned
          *Next the required depth is returned by calling analog_read_requireddepth(). This function reads the depth value stord in text file "analog_input_required.txt"
          *gettuningparams() function then sets the tuninng parameters by reading the file "tuning_parameters.txt"
          *the pid_correction() function is then called with the tuning parameters as arguments.The error is calculated as the difference absolute value of the difference between current and required depths. Also the thruster state is determined to be up or down. If the auv is at a higher depth than the setpoint(required depth),the thruster state is set as down and vice versa.The corresponding proportional,integral and derivative terms are calculated and summed to obtain the output pwm value.Before sending this value,a checking is done to see if the output pwm is below 255 and if it is found to be greater,it is set as 255.
          *This pwm value is then written to a text file analog_output.txt by invoking the function analog_write_pwm().
    
#3)Algorithm Task 1 (Heading Averager)
      This task is implemented in C++. The brief algorithm is as follows:
          
          *Upon user input the heading_averager() function gets called
          *This function reads 10 compass values from the text file compass_values.txt and then computes the sum and returns the average value on dividing by 10.
          
#4)Algorithm Task 2 (Storage Algorithm for Sensor Values)
      This task is implemented in C++. The assumption made here is that the sensor values keep on overwriting each other in the text file i.e only one value(line) exists and after 0.1 seconds,a new value is overwritten. The brief algorithm is as follows:
      
          *A double-ended queue(deque) data structure is initialed with size 64.
          *The time_diff() function is used to calculate the time difference between the two function arguments.When this time reaches 0.1, the file "sensor_values.txt" is read and the sensor value is pushed (stored) in the front of the deque.A size check is done before this to make sure that the buffer deque is not full. If the deque is indeed full i.e the size is 64,then the back of the deque is popped to make room for the new value which is then pushed to the front.

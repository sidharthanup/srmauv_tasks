#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<string>
#include<ctime>
#include<math.h>

#define DOWN 0
#define UP 1

bool thruster_state;
int curr_depth,req_depth,pwm_val,outMax=255;
clock_t last_time;
float integral_sum,last_error;
float kp,kd,ki;

int gettuningparams(){								//this function obtains the tuning parameters from the file tuning_parameters.txt
	std::string line1,line2,line3;
	
	std::ifstream myfile("tuning_parameters.txt");
	if(myfile.is_open()){
		while(!myfile.eof()){
			getline(myfile,line1);
			getline(myfile,line2);
			getline(myfile,line3);
		}
		myfile.close();
		kp=std::stof(line1);
		ki=std::stof(line2);
		kd=std::stof(line3);
	}
	else
		std::cout<<"Unable to open file";

}

double time_diff(clock_t clock1, clock_t clock2){   //returns time in millis
	double clock_diff = clock1 - clock2;
	double diffms = clock_diff / (CLOCKS_PER_SEC/1000);
	return diffms;
}

int analog_read_currentdepth(){ 	//this function reads the current depth
	std::string line;
	float depth; 
	std::ifstream myfile("analog_input_current.txt");
	if(myfile.is_open()){
		while( getline(myfile,line) ){
			depth=std::stof( line );
			}
		myfile.close();
		return depth;
		}
	else
		std::cout<<"Unable to open file";
	
}

int analog_read_requireddepth(){	//this function reads the required depth
	std::string line;
	float depth; 
	std::ifstream myfile("analog_input_required.txt");
	if(myfile.is_open()){
		while( getline(myfile,line) ){
			depth=std::stof( line );
			}
		myfile.close();
		return depth;
		}
	else
		std::cout<<"Unable to open file";
	
}

int analog_write_pwm(float pwm_out){ 	//this functions writes the pwm value to the file	
	std::string line=std::to_string(pwm_out);
	std::ofstream myfile("analog_output.txt");
	if(myfile.is_open())
	{
		myfile<<line;
	}
	else
		std::cout<<"Unable to open file";
}

int pid_correction(float kp, float ki, float kd)
{
	float d_error;
	clock_t now=clock();
	double timechange;
	timechange=time_diff(now,last_time);
	float output;
	float error=abs(curr_depth-req_depth);
	if(curr_depth-req_depth<0){
		thruster_state=UP;
	}

	else if(curr_depth-req_depth>0){
		thruster_state=DOWN;
	}
	else if(curr_depth-req_depth==0){
	
		return -1; 
	}
		
	integral_sum+=(error*timechange);
	if(integral_sum> outMax) integral_sum= outMax;

	d_error=(error-last_error)/timechange;
	
	output=(kp*error) + (ki*integral_sum) + (kd*d_error);

	if(output> outMax) output=outMax;
	analog_write_pwm(output);
	
	last_error=error;
	last_time=now;

	return 0;

}

int main()
{
	
	while(1){

	//the sensor calculates and returns the depth
	//assuming the depth is measured from the bottom(ocean bed)
	//this depth is stored in the file analog_input.txt
		curr_depth=analog_read_currentdepth();
		req_depth=analog_read_requireddepth();
		gettuningparams();
		pid_correction(kp,ki,kd);
	}
}

	
	

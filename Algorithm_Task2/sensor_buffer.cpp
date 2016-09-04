#include<iostream>
#include<stdlib.h>
#include<deque>
#include<algorithm>
#include<iterator>
#include<fstream>
#include<string>



double time_diff(clock_t clock1, clock_t clock2){   //returns time in seconds
	double clock_diff = clock1 - clock2;
	double diff = clock_diff / (CLOCKS_PER_SEC);
	return diff;
}
			

int main(){
	
	std::deque<double> buff(64);	//create a double-ended queue of size 64
	clock_t start=clock();
	clock_t elapsed;
	std::ifstream myfile;
	std::string line;
	
	while(1){
		if(time_diff(elapsed,start)>=0.1){		//this time check checks whether the time difference has reached 0.1 ie just to make it regular
			myfile.open("sensor_values.txt",std::ios::in);   //assuming the sensor sends a double value to this file and each time a new value is 
			if(myfile.is_open()){                            //sent,it overwrites the previous value
				getline(myfile,line);
				start=clock();
				double sensed_val=std::stod(line);
				if(buff.size()== 64){           //checks if the buffer size is full
					buff.pop_back();			//if yes,then pop a value from the back
				}
				buff.push_front(sensed_val);	//a new value is inserted at the front
			}

			else
				std::cout<<"Unable to open file";
		}
		elapsed=clock();
	}
	return 0;
}

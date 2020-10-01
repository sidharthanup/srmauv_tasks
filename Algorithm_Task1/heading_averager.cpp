#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<string>

int heading_averager(){
	std::string line;
	int i=0;
	int heading_val[10];
	std::ifstream myfile;
	myfile.open("compass_values.txt",std::ios::in);	 
	if(myfile.is_open()){
		while(!myfile.eof() && i<10){			//reads 10 values from the text file 
			getline(myfile,line);
			heading_val[i]=std::stoi(line);
			i+=1;
		}
		
		myfile.close();
	}
	else 
		std::cout<<"Unable to open file";

	int sum=0;
	for(int i=0;i<10;i++){
		sum+=heading_val[i];		//calculates and returns the average
		}

	return sum/10;
}
int main(){
	while(1){
		int average_heading;
		char conf;
		std::cout<<"Do you want the compass value?(y/n)"<<endl;
		std::cin>>conf;
		if(conf=='y')
		{
			average_heading=heading_averager();
			std::cout<<"the compass reading is "<<average_heading<<endl;
		}
		
	}
	return 0;
}

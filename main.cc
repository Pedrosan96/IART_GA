#include"MyGA.h"
#include"MyGA.cc"

//The original function of data file is 30x^3+20x^2+10x+5 from 0 to 100 but with some noise



int main(){
	GA ga1;
	int i=0;
	std::vector<unsigned long> Fo;                                // empty vector of ints
	std::string data;
	std::fstream dataFile("data.txt");
	if(!dataFile.is_open()){
		dataFile.open("data.txt", std::ios::in);
	}

	while(dataFile.good())
  {
    getline(dataFile,data,',');
    Fo.push_back(std::stoul(data,nullptr,0));
  }

	while(ga1.reproduction(Fo))
	// 


	return 0;
}

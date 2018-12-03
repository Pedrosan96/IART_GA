#include"MyGA.h"
#include"MyGA.cc"

using namespace std;
//The original function of data file is 30x^3+20x^2+10x+5 from 0 to 100 but with some noise

int main(){
	GA ga1;
	int i=0;
	int Fo[101];                                // empty vector of ints
	std::string data;
	fstream datafile("data.txt");
	if(!datafile.is_open()){
		datafile.open("data.txt", ios::in);
	}
	while(getline(datafile, data)){
		Fo[i] = stoi(data);
		i++;
	}
	//MyReadFile();
	ga1.reproduction(Fo);
	// 


	return 0;
}

#ifndef MYGA_H_
#define MYGA_H_

#include<iostream>
#include<cmath>
#include<random>
#include<ctime>
#include<cstdlib>
#include<fstream>
#include<string>
#include<vector>


#define num_bits 64
#define maxs_gens 100
#define parent_size 30
#define child_size  40
#define p_crossover 0.98
#define p_mutation 1/64
#define Funct(x, X0, X1, X2, X3)	X3*x*x*x+X2*x*x+X1*x+X0

std::default_random_engine generator;
std::uniform_real_distribution<double> distribution(0.0,1.0); 


class GA{
public:
	GA();
	~GA(){
	if (this->chromosomes != NULL) delete [] this->chromosomes;
		if (this->parent1 != NULL) delete [] this->parent1;
		if (this->parent2 != NULL) delete [] this->parent2;
	if (this->child != NULL) delete [] this->child; 
	}
	bool reproduction(std::vector<unsigned long> Fo);
	void mutation();
	void crossover();
	void selection();
	bool Error(std::vector<unsigned long> Fo, unsigned long long int solu, int index);
	
private:
	unsigned long long int *chromosomes = new unsigned long long int[maxs_gens];
	unsigned long long int *parent1 = new unsigned long long int[parent_size];
	unsigned long long int *parent2 = new unsigned long long int[parent_size];
	unsigned long long int *child = new unsigned long long int[child_size];
	double *Err = new double[maxs_gens];
	int iter;
};

#endif

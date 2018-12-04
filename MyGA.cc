#include"MyGA.h"
/*
long int solucion=x3(16bits)+x2(16bits)+x1(16bits)+x0(16bits)
*/


GA::GA(){
	iter=0;
	for (int i = 0; i < parent_size; i++){	//Initialization of parents and child
		parent1[i]=0;
		parent2[i]=0;
	}
	for (int j = 0; j < child_size; j++){
		child[j]=0;
	}
	for (int k = 0; k < maxs_gens; k++){	//Initialization of chromosomes
		srand( time( NULL ) );
		unsigned long long int ran1 = rand();
		chromosomes[k] = ran1*ran1*ran1*ran1;
	}
}

bool GA::reproduction(std::vector<unsigned long> Fo){
	bool flag;
	for (int i = 0; i < maxs_gens; i++){
		flag=Error(Fo, chromosomes[i], i);
		if (!flag){
			return flag;
		}
	} 
	 	selection();
	 	iter++;			//adding an iteration

	crossover();
	mutation();
	

}
void GA::mutation(){
	double rate = 1.0/child_size;		//mutation of each bit
	double r2 =0.0;
	for (int j = 0; j < child_size; j++){
		for (int i = 1; i <= num_bits; i++){
		r2 = distribution(generator);
		((r2<rate)? ~(child[j]&(1<<i)): (child[j]&(1<<i)));	
		}
	}
	
}
void GA::crossover(){
	double RandNum = distribution(generator);//Generate the partition of parent1 for the child
	srand( time( NULL ) );
	int point = 10 + (rand() % 30);// Parents are of length 30

	if (RandNum>=p_crossover){	//If the mutation rate is too small doesnt change
		for (int i = 0; i < 30; i++){
			child[i] = parent1[i];
		}
		for (int j = 30; j < 40; j++){
			child[j] = parent2[j-30];
		}
		return;
	}

	for (int i = 0; i < point; i++){
		child[i] = parent1[i];
	}
	for (int j = point; j < 40; j++){
		child[j] = parent2[j];
	}


}
void GA::selection(){
	long double min=10e10;
	
	for (int j = 0; j < maxs_gens; j++){	//Selection of elements with smaller errors
	 	if (Err[j]<min){
	 		min=Err[j];
 			for (int k = 29; k >=1; k--){	//The value in the parents is updated
 				parent2[k]=parent2[k-1];
 			}
	 		parent2[0]=parent1[29];
 			for (int h = 29; h >=1; h--){
			parent1[h]=parent1[h-1];
 			}
 			parent1[0]=min; 			
 		}	
	}
	return;
}

bool GA::Error(std::vector<unsigned long> Fo, unsigned long long int solu, int index){
	unsigned long int aux1 = (unsigned long long int)(solu >> 32);	//Separation of bits for the coeficients
	unsigned long int aux2 = solu & 0xFFFFFFFF;
	unsigned short x3 = (unsigned long long int)(aux1 >> 16);		//Bits for the coeficient x3
	unsigned short x2 = aux1 & (unsigned long long int)(~0U) >> 16; //Bits for the coeficient x2
	unsigned short x1 = (unsigned long long int)(aux2 >> 16);		//Bits for the coeficient x1
	unsigned short x0 = aux2 & (unsigned long long int)(~0U) >> 16; //Bits for the coeficient x0
	long double Dif=0, Suma=0;

	for (int i = 0; i < maxs_gens; i++)								//Error evaluation
	{
		Suma +=labs(Fo[i]-Funct(i, x0, x1, x2, x3));					
		Suma/=maxs_gens;
	}
	Err[index]=Suma;
	if ((Err[index]>0.01) && iter<1000)		//Condition to continue
	{
		std::cout<<"////////////////////////////////////////"<<std::endl;
		std::cout<<"Iter: "<<iter<<" Error: "<<Err[index]<<std::endl;
	 	std::cout<<"Valores: X3="<<x3<<" X2="<<x2<<" X1="<<x1<<" X0="<<x0<<std::endl;
	 	return true;
	}
		std::cout<<"////////////////////////////////////////"<<std::endl;
		std::cout<<"Iter: "<<iter<<" Error: "<<Err[index]<<std::endl;
	 	std::cout<<"Valores: X3="<<x3<<" X2="<<x2<<" X1="<<x1<<" X0="<<x0<<std::endl;
	return false;
}
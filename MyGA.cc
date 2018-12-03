#include"MyGA.h"
/*
long int solucion=x3(16bits)+x2(16bits)+x1(16bits)+x0(16bits)
*/


GA::GA(){
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

void GA::reproduction(int *Fo){
	for (int i = 0; i < maxs_gens; i++){
	 	selection(Fo, chromosomes[i]);
	} 
	crossover();
	for (int j = 0; j < child_size; j++)
	{
		mutation(child[j]);
	}

}
void GA::mutation(unsigned long long int valor){
	double rate = 1.0/child_size;		//mutation of each bit
	double r2 =0.0;
	for (int i = 1; i <= num_bits; i++){
		r2 = distribution(generator);
		((r2<rate)? ~(valor&(1<<i)): (valor&(1<<i)));	
	}
}
void GA::crossover(){
	double RandNum = distribution(generator);//Generate the partition of parent1 for the child
	srand( time( NULL ) );
	int point = 10 + (rand() % 30);// Parents are of length 30

	if (RandNum>=p_crossover){	//If the mutation rate is too small doesnt change
		child=parent1;
		return;
	}
	for (int i = 0; i < point; i++){
		child[i] = parent1[i];
	}
	for (int j = point; j < 40; j++){
		child[j] = parent2[j];
	}


}
void GA::selection(int *Fo, unsigned long long int solu){
	double min=10000.0;
	for (int i = 0; i < maxs_gens; i++){
		Error(Fo, chromosomes[i], i);
	}

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
}

void GA::Error(int *Fo, unsigned long long int solu, int index){
	unsigned long int aux1 = (unsigned long long int)(solu >> 32);	//Separation of bits for the coeficients
	unsigned long int aux2 = solu & 0xFFFFFFFF;
	unsigned short x3 = (unsigned long long int)(aux1 >> 16);		//Bits for the coeficient x3
	unsigned short x2 = aux1 & (unsigned long long int)(~0U) >> 16; //Bits for the coeficient x2
	unsigned short x1 = (unsigned long long int)(aux2 >> 16);		//Bits for the coeficient x1
	unsigned short x0 = aux2 & (unsigned long long int)(~0U) >> 16; //Bits for the coeficient x0
	int Dif=0, Suma=0;

	for (int i = 0; i < maxs_gens; i++)								//Error evaluation
	{
		Suma +=abs(Fo[i]-Funct(i, x0, x1, x2, x3));					
		
	}
	Err[index]=Suma/maxs_gens;
}
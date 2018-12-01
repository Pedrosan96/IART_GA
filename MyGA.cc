#include"MyGA.h"
/*
long int solucion=x3(16bits)+x2(16bits)+x1(16bits)+x0(16bits)
*/


GA::GA(){

}

unsigned long long int GA::reproduction(){

}
unsigned long long int GA::mutation(){

}
void GA::crossover(){
	double RandNum = distribution(generator);
	srand( time( NULL ) );
	int point = 1 + (rand() % 30);

if (RandNum>=p_crossover){
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
	double min=0, indexes[]={0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, aux=0.0;
	for (int i = 0; i < maxs_gens; i++)
	{
		Error(Fo, chromosomes[i], i);
	}

	for (int j = 0; j < maxs_gens; j++)
	{
	 	if (Err[j]<min){
	 			min=Err[j];
	 			
	 			for (int k = 29; k =1; k--)
	 			{
	 				indexes[k]=indexes[k-1];
	 			}
	 			indexes[0]=min;
	 		}	
	}
	if (min<=1)
	{
		/* code */
	}
}

unsigned long long int GA::Error(int *Fo, unsigned long long int solu, int index){
	unsigned long int aux1 = (unsigned long long int)(solu >> 32);
	unsigned long int aux2 = solu & 0xFFFFFFFF;
	unsigned short x3 = (unsigned long long int)(aux1 >> 16);
	unsigned short x2 = aux1 & (unsigned long long int)(~0U) >> 16;
	unsigned short x1 = (unsigned long long int)(aux2 >> 16);
	unsigned short x0 = aux2 & (unsigned long long int)(~0U) >> 16;
	int Dif=0, Suma=0;

	for (int i = 0; i < maxs_gens; i++)
	{
		Suma +=abs(Fo[i]-Funct(i, x0, x1, x2, x3));
		
	}
	Err[index]=Suma/maxs_gens;
}

GA::~GA(){
	if (this->chromosomes != NULL) delete [] this->chromosomes;
		if (this->parent1 != NULL) delete [] this->parent1;
		if (this->parent2 != NULL) delete [] this->parent2;
	if (this->child != NULL) delete [] this->child; 
}
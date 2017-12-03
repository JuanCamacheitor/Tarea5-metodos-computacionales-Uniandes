#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include <time.h>

float compute_likelihood(float *R, float *V, float Mb,  float Md,  float Mh);
float funcrandom(float min, float max);

int main(void)
{
	
    float likerel;
	int i;
	char  strd[300];
	int test;
	FILE *in = fopen("RadialVelocities.dat", "r");
	float *R = malloc(300*sizeof(float));	
	float *V = malloc(300*sizeof(float));


	test = fscanf(in, "%s %s\n", strd, strd);
	for (i = 0; i < 300; i++)
	{
		fscanf(in, "%f %f\n", &R[i], &V[i]);
	}
	fclose(in);


	float iniMb=3000.0; 
    float iniMd=2000.0; 
    float iniMh=1000.0;
	float Mb; 
    float Md; 
    float Mh;
	float likelihoodant;
    likelihoodant = compute_likelihood(R, V,  iniMb,  iniMd,  iniMh);
	float likelihoodfut;
	srand(time(NULL));

	FILE *salida = fopen("salidat2", "w");
	fprintf(salida, "%f,%f,%f,%f\n", iniMb,iniMd,iniMh,likelihoodant);
	

	for ( i = 0; i < 50000; i++)
	{
        Mb=funcrandom(iniMb-10.0,iniMb+10.0);
        Mb=iniMb+Mb;
        Md=funcrandom(iniMd-4.0,iniMd+4.0);
        Md=iniMd+Md;
        Mh=funcrandom(iniMh-4.0,iniMh+4.0);
        Mh=iniMh+Mh;
		likelihoodfut = compute_likelihood(R, V,  Mb,  Md,  Mh);

        likerel=likelihoodfut/likelihoodant;

		if (likerel<1)
		{
			likelihoodant = likelihoodfut;
            iniMb = Mb;
			iniMd = Md;
			iniMh = Mh;
		}
        
		fprintf(salida, "%f,%f,%f,%f\n", iniMb,iniMd,iniMh,likelihoodant);
		
		if (i==50000-1)
		{
			printf("\nMb \t\t Md \t\t Mh\n%f \t %f \t %f\n\n\n", iniMb, iniMd, iniMh);
		}
		
	}
	
	return 0;


}



float compute_likelihood(float *R, float *V,  float Mb,  float Md,   float Mh)
{
	float likelihood=0;
	float v_modelo;
	float l;
    int i;
	for ( i = 0; i < 300; i++)
	{
		v_modelo = pow(Mb,0.5)*R[i]/pow(pow(R[i],2)+pow(0.2497,2),0.75) + (pow(Md,0.5)*R[i]/pow( pow(R[i],2)+pow(5.16+0.3105,2) ,0.75)) + (pow(Mh,0.5)/pow(pow(R[i],2)+pow(64.3,2),0.25));
		l = pow(pow(v_modelo  - V[i],2),0.5);
		likelihood = likelihood + l;
	}

	return likelihood;

}

float funcrandom(float inferior, float superior)
{
	float numero_aleatorio;
	float delta = superior-inferior;
	numero_aleatorio = (float)rand()/RAND_MAX;

	numero_aleatorio = delta - numero_aleatorio*2.0*delta;

	return numero_aleatorio;

}

#include <stdio.h>
#include <stdlib.h>


#include "ConjugateGradient.h"
#include "ConjugateGradientSolver.h"

int ConjugateGradient(int argc, char *argv[]) {
//Options: InputMatrixFile InputVectorFile

	
	//int i;
	int ret_code;
	
	unsigned long *I;
	unsigned long *J;
	double *A;
	
	unsigned long M;
	unsigned long N;
	unsigned long long nz;
	
	
	double *b;
	unsigned long M_Vector;
	unsigned long N_Vector;
	unsigned long long nz_vector;
	
	
	if (argc < 3)
	{
		fprintf(stderr, "[%s] Usage: %s [input-matrix-file] [input-vector-file]\n",__func__, argv[0]);
		return 0;
	}
	
	//Read matrix
	if(!readDenseCoordinateMatrix(argv[1],&I,&J,&A,&M,&N,&nz)){
		fprintf(stderr, "[%s] Can not read Matrix\n",__func__);
		return 0;
	}
	
	//Read vector
	if(!readDenseVector(argv[2], &b,&M_Vector,&N_Vector,&nz_vector)){
		fprintf(stderr, "[%s] Can not read Vector\n",__func__);
		return 0;
	}
	
	
        
        //double *y=(double *) malloc(nz_vector * sizeof(double));
        
	int ret_value = ConjugateGradientSolver(I,J,A,M,N,nz,b,M_Vector,N_Vector,nz_vector);
	
	if(ret_value){
		writeDenseVector("stdout", b,M_Vector,N_Vector,nz_vector);
		//fprintf(stderr, "[%s] Number of iterations %lu\n",__func__,k);
	}
	else{
		printf(stderr,"[%s] Error executing ConjugateGradientSolver\n",__func__);
	
	}
	return ret_value;
}


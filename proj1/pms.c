#include <mpi.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define TAG 0
#define MAX_C 255

int main(int argc, char *argv[])
{
	int numprocs;               //pocet procesoru
	int myid;                   //muj rank
	int neighnumber;            //hodnota souseda
	unsigned char mynumber;               //moje hodnota
	MPI_Status stat;            //struct- obsahuje kod- source, tag, error

	//MPI INIT
	MPI_Init(&argc,&argv);                          // inicializace MPI 
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);       // zjistíme, kolik procesů běží 
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);           // zjistíme id svého procesu 

	int filesize = atoi(argv[1]);
	if(((numprocs-1)*(numprocs-1))!=filesize)
	{
		printf("špatný počet procesorů %d, mělo by být log%d +1\n",numprocs,filesize);
		return 1;
	}

	if(myid == 0){
		char *input= "numbers";                          	//jmeno souboru    
		int number;                                     	//hodnota pri nacitani souboru
		FILE *fileptr;		                              	//cteni ze souboru
		int filesize = atoi(argv[1]);
		//char buffer[filesize];
		
		fileptr = fopen(input,"rb");
		for(int i = 0; i < filesize; i++) {
			fread(&mynumber, 1, 1, fileptr);
			printf("%d ",mynumber);
			MPI_Send(&mynumber, 1, MPI_BYTE, (myid+1)%numprocs, TAG, MPI_COMM_WORLD);
		}
		printf("\n");
		fclose(fileptr);
		for(int i = 0; i < filesize; i++)
		{
			MPI_Recv(&mynumber, 1, MPI_BYTE, numprocs-1, TAG, MPI_COMM_WORLD, &stat);	
			printf("%d\n",mynumber);
		}
	} else if(myid == 1){
		
				
		int j = 0;
		int dimension = 2;
		int start = 0;
		
		unsigned char mynumber_ques[2][dimension];	//que,item
		memset(mynumber_ques,MAX_C,2*(dimension));
		
		
		int tops[2] = {-1,-1};
		int bottom[2] = {0,0};
		
		int left = 0;
		for(int k = 0; k < filesize;)
		{
			for(int d = 0; d < dimension; d++)
			{
				MPI_Recv(&mynumber_ques[j%2][(++tops[j%2])%(dimension)], 1, MPI_BYTE, (myid-1), TAG, MPI_COMM_WORLD, &stat);
				if(!start){
					if(d>0)
						start=1;
				}
				if(start){
					if(left==-1 || (left!=1 && mynumber_ques[0][bottom[0]] <= mynumber_ques[1][bottom[1]])){
						MPI_Send(&mynumber_ques[0][bottom[0]], 1, MPI_BYTE, (myid+1)%numprocs, TAG, MPI_COMM_WORLD);
// printf("PR. 1: 1sent:%d\n",mynumber_ques[0][bottom[0]]);
						mynumber_ques[0][bottom[0]]=MAX_C;
						bottom[0] = (bottom[0]+1)%(dimension);
						left++;
					}else{
						MPI_Send(&mynumber_ques[1][bottom[1]], 1, MPI_BYTE, (myid+1)%numprocs, TAG, MPI_COMM_WORLD);
// printf("PR. 1: 2sent:%d\n",mynumber_ques[1][bottom[1]]);
						mynumber_ques[1][bottom[1]]=MAX_C;
						bottom[1] = (bottom[1]+1)%(dimension);
						left--;
					}
				}
				j++;
			}
			k+=dimension;
		}
		if(left==-1 || (left!=1 && mynumber_ques[0][bottom[0]] <= mynumber_ques[1][bottom[1]])){
			MPI_Send(&mynumber_ques[0][bottom[0]], 1, MPI_BYTE, (myid+1)%numprocs, TAG, MPI_COMM_WORLD);
// printf("PR. 1: 1sent:%d\n",mynumber_ques[0][bottom[0]]);
			mynumber_ques[0][bottom[0]]=MAX_C;
			bottom[0] = (bottom[0]+1)%(dimension);
			left++;
		}else{
			MPI_Send(&mynumber_ques[1][bottom[1]], 1, MPI_BYTE, (myid+1)%numprocs, TAG, MPI_COMM_WORLD);
// printf("PR. 1: 2sent:%d\n",mynumber_ques[1][bottom[1]]);
			mynumber_ques[1][bottom[1]]=MAX_C;
			bottom[1] = (bottom[1]+1)%(dimension);
			left--;
		}
		
		
		
	} else{
		int j = 0;
		int dimension = 2;
		int start = 0;
		
		for(int i = 2; i < myid; i++)
		{
			dimension = dimension*2;
		}
		
		unsigned char mynumber_ques[2][dimension+1];	//que,item
		memset(mynumber_ques,MAX_C,2*(dimension+1));
		
		
		int tops[2] = {-1,-1};
		int bottom[2] = {0,0};
		
		int left = 0;
		int right = 0;
		for(int k = 0; k < filesize;)
		{
			for(int d = 0; d < dimension; d++)
			{							
				MPI_Recv(&mynumber_ques[j%2][(++tops[j%2])%(dimension+1)], 1, MPI_BYTE, (myid-1), TAG, MPI_COMM_WORLD, &stat);
				if(!start){
					if(tops[0]+1==dimension && tops[1]==0)
					{
						start=1;
						// printf("pr %d starting with dim %d\n",myid, dimension);
					}
				}
				if(start){
					if(right==-dimension || (left!=dimension && mynumber_ques[0][bottom[0]] <= mynumber_ques[1][bottom[1]])){
						MPI_Send(&mynumber_ques[0][bottom[0]], 1, MPI_BYTE, (myid+1)%numprocs, TAG, MPI_COMM_WORLD);
// printf("PR. 2: 1sent:%d\n",mynumber_ques[0][bottom[0]]);
						mynumber_ques[0][bottom[0]]=MAX_C;
						bottom[0] = (bottom[0]+1)%(dimension+1);
						left++;
					}else{
						MPI_Send(&mynumber_ques[1][bottom[1]], 1, MPI_BYTE, (myid+1)%numprocs, TAG, MPI_COMM_WORLD);
// printf("PR. 2: 2sent:%d\n",mynumber_ques[1][bottom[1]]);
						mynumber_ques[1][bottom[1]]=MAX_C;
						bottom[1] = (bottom[1]+1)%(dimension+1);
						right--;
					}
					if(right+left==0 && left==dimension)
					{
						right=0;
						left=0;
					}
				}
			}
			j++;
			k+=dimension;
		}		
		for(int d = 0; d < dimension; d++)
		{	
			if(right==-dimension || (left!=dimension && mynumber_ques[0][bottom[0]] <= mynumber_ques[1][bottom[1]])){
				MPI_Send(&mynumber_ques[0][bottom[0]], 1, MPI_BYTE, (myid+1)%numprocs, TAG, MPI_COMM_WORLD);
// printf("PR. 2: 1sent:%d\n",mynumber_ques[0][bottom[0]]);
				mynumber_ques[0][bottom[0]]=MAX_C;
				bottom[0] = (bottom[0]+1)%(dimension+1);
				left++;
			}else{
				MPI_Send(&mynumber_ques[1][bottom[1]], 1, MPI_BYTE, (myid+1)%numprocs, TAG, MPI_COMM_WORLD);
// printf("PR. 2: 2sent:%d\n",mynumber_ques[1][bottom[1]]);
				mynumber_ques[1][bottom[1]]=MAX_C;
				bottom[1] = (bottom[1]+1)%(dimension+1);
				right--;
			}
			if(right+left==0 && left==dimension)
			{
				right=0;
				left=0;
			}
		}
	}


	MPI_Finalize(); 
	return 0;

}
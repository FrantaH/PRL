// František Horázný
// xhoraz02
// mesh multiplication


#include <mpi.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unistd.h>

#include <chrono>

using namespace std;

#define TAG1 0
#define TAG2 1
#define ROOT_PROC numprocs-1
#define TEST_COUNT 1	//1 = normální běh, 0 jeden běh měření času, víc jak 1 testování výpočetního času

int almost_main(double* ret_timec,double* ret_timempi);

int main(int argc, char *argv[])
{
	double timec;
	double timem;
	
	MPI_Init(&argc,&argv);                          // inicializace MPI 
	
	if(TEST_COUNT > 1){
		double time1 = 0;
		double time2 = 0;
		for(int i=0;i<TEST_COUNT;i++)
		{
			almost_main(&timec, &timem);
			time1 += timec;
			time2 += timem;
		}
		time1 = time1/TEST_COUNT;
		time2 = time2/TEST_COUNT;
		if(time1!=0)
			cout << "average time: " << time1 << " or " << time2 << endl;
	} else {
		almost_main(&timec, &timem);
	}
	
	MPI_Finalize(); 
	return 0;
}

// pomocná funkce přidaná pro cyklické spuštění
// cyklické spouštění se ukázalo být problematické - při prvním spuštění je čas několikanásobně delší
// než při dalších. Ve grafech v dokumentaci jsou použity časy ze spouštění s TEST_COUNT == 0
int almost_main(double* ret_timec,double* ret_timempi){
	
	int numprocs;               //pocet procesoru
	int myid;                   //muj rank
	MPI_Status stat;            //struct- obsahuje kod- source, tag, error

	//MPI INIT
	
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);       // zjistíme, kolik procesů běží 
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);           // zjistíme id svého procesu 

	
	chrono::high_resolution_clock::time_point start, end;
	double start2, end2;

	// cout<<"im a "<< myid <<"/"<< numprocs << " thats how it is"<<endl;

	int shared_dim = 0;
	int res_cols;
	int res_rows;
	
	if(myid == ROOT_PROC){
		MPI_Request request = MPI_REQUEST_NULL;
		char input_mat1[]= "mat1";                          //jmeno souboru    
		char input_mat2[]= "mat2";                          //jmeno souboru    
		
		// zjištění počtu řádků v mat2 (společný rozměr)
		ifstream tmp_lines(input_mat2);
		string xxx;
		while(getline(tmp_lines,xxx))
		{
			shared_dim++;
		}
		shared_dim--;
		
		
		ifstream mat2(input_mat2);
		ifstream mat1(input_mat1);
		
		
		
		// načtení druhé matice a rozeslání
		string line;
		if(!getline(mat2,line))
			return 1;
		res_cols = stoi(line);
		int numbers2[shared_dim][res_cols];
		for(int j = 0;getline(mat2,line);j++)
		{
			istringstream iss(line);
			for(int i=0;i<res_cols;i++)
			{
				iss >> numbers2[j][i];
				MPI_Isend(&numbers2[j][i], 1, MPI_INT, i, TAG1, MPI_COMM_WORLD, &request);
				// cout << numbers2[j][i] << " ";
			}
			// cout << endl;
		}
		// cout << shared_dim << ":" << res_cols << endl;
		
		// MPI_Bcast(&shared_dim, 1, MPI_INT, ROOT_PROC, MPI_COMM_WORLD);
		// MPI_Bcast(&res_cols, 1, MPI_INT, ROOT_PROC, MPI_COMM_WORLD);
		// start = chrono::high_resolution_clock::now();
		
		// načtení první matice a rozeslání
		if(!getline(mat1,line))
			return 1;
		res_rows = stoi(line);
		int numbers1[res_rows][shared_dim];
		for(int j=0;getline(mat1,line);j++)
		{
			istringstream iss(line);
			for(int i=0;i<shared_dim;i++)
			{
				iss >> numbers1[j][i];
				MPI_Isend(&numbers1[j][i], 1, MPI_INT, j*res_cols, TAG2, MPI_COMM_WORLD, &request);
				// cout << numbers1[j][i] << " ";
			}
			// cout << endl;
		}
	}
	// if(myid!=ROOT_PROC){
		// MPI_Bcast(&shared_dim, 1, MPI_INT, ROOT_PROC, MPI_COMM_WORLD);
		// MPI_Bcast(&res_cols, 1, MPI_INT, ROOT_PROC, MPI_COMM_WORLD);
	// }
	
	// informování procesorů o jejich okolí (jak vypadá matice procesorů)
	MPI_Bcast(&shared_dim, 1, MPI_INT, ROOT_PROC, MPI_COMM_WORLD);
	MPI_Bcast(&res_cols, 1, MPI_INT, ROOT_PROC, MPI_COMM_WORLD);
	
	// spuštění měření doby výpočtu
	if(myid==ROOT_PROC){		
		start = chrono::high_resolution_clock::now();
		start2 = MPI_Wtime();
	}	
	
	// výpočet ranků sousedů, pokud rank souseda==myid -> nemá souseda
	int upper_neigh = myid-res_cols;
	if (myid<res_cols)
		upper_neigh=ROOT_PROC;
	
	int left_neigh = myid-1;
	if(myid%res_cols==0)
		left_neigh=ROOT_PROC;
	
	int right_neigh = myid+1;
	if((myid+1)%res_cols==0)
		right_neigh=myid;
	
	int lower_neigh = myid+res_cols;
	if((myid+1)>(numprocs-res_cols))
		lower_neigh = myid;


	
	int result = 0;
	int num1;
	int num2;
	// výpočet výsledku - přijme dvoje data, upraví mezivýsledek, odešle data sousedům
	for(int i = 0;i<shared_dim;i++)
	{
		MPI_Recv(&num1, 1, MPI_INT, upper_neigh, TAG1, MPI_COMM_WORLD, &stat);
		MPI_Recv(&num2, 1, MPI_INT, left_neigh, TAG2, MPI_COMM_WORLD, &stat);
		result = result + (num1*num2);
		
		if(lower_neigh!=myid)
			MPI_Send(&num1, 1, MPI_INT, lower_neigh, TAG1, MPI_COMM_WORLD);
		if(right_neigh!=myid)
			MPI_Send(&num2, 1, MPI_INT, right_neigh, TAG2, MPI_COMM_WORLD);
		
	}
	
	// procesory pošlou svá data kořenovému procesoru (sám kořenový procesor neposílá, už je má)
	if(myid != ROOT_PROC)
		MPI_Send(&result, 1, MPI_INT, ROOT_PROC, TAG1, MPI_COMM_WORLD);

	
	if(myid==ROOT_PROC)
	{
		int results[numprocs];
		
		// posbírání výsledků z procesorů
		for(int i=0;i<numprocs-1;i++)
		{
			MPI_Recv(&results[i], 1, MPI_INT, i, TAG1, MPI_COMM_WORLD, &stat);
		}
		results[numprocs-1] = result;
		
		// STOP CLOCK
		end = chrono::high_resolution_clock::now();
		end2 = MPI_Wtime();
		
		// vypsání výsledné matice
		if(TEST_COUNT==1)
		{
			cout << res_rows << ":" << res_cols << endl;
			for (int i = 0; i<numprocs/res_cols; i++)
			{
				for(int j = 0; j<res_cols;j++)
				{
					cout << results[j+i*res_cols] << " ";				
				}
				cout << endl;
			}
		}
		
		// výpočet doby běhu
		chrono::duration<double, std::milli> ms_double = end - start;
		double timeMPI = (end2 - start2)*1000;
		
		*ret_timec = ms_double.count();
		*ret_timempi = timeMPI;
		if(TEST_COUNT == 0)
			cout << ms_double.count() << endl;
		// cout << "time spent: " << ms_double.count() << "ms and MPI: " << timeMPI << endl;
	} else {
		*ret_timec = 0;
		*ret_timempi = 0;
	}

	return 0;

}//main
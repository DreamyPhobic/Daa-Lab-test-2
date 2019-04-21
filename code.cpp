// C++ implementation of the approach 
#include <bits/stdc++.h> 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include <omp.h>
#include <math.h>
using namespace std; 
  
// Function to return the minimum cells that are 
// connected via the minimum length path 
int seq_Minimum_Cells(vector<pair<int, int> > v) 
{ 
    int col[3], i, j; 
    for (i = 0; i < 3; i++) { 
        int column_number = v[i].second; 
  
        // Array to store column number 
        // of the given cells 
        col[i] = column_number; 
    } 
  
    sort(col, col + 3); 
  
    // Sort cells in ascending 
    // order of row number 
    sort(v.begin(), v.end()); 
  
    // Middle row number 
    int MidRow = v[1].first; 
  
    // Set pair to store required cells 
    set<pair<int, int> > s; 
  
    // Range of column number 
    int Maxcol = col[2], MinCol = col[0]; 
  
    // Store all cells of middle row 
    // within column number range 
    for (i = MinCol; i <= Maxcol; i++) { 
        s.insert({ MidRow, i }); 
    } 
  
    for (i = 0; i < 3; i++) { 
        if (v[i].first == MidRow) 
            continue; 
  
        // Final step to store all the column number 
        // of 1st and 3rd cell upto MidRow 
        for (j = min(v[i].first, MidRow); 
             j <= max(v[i].first, MidRow); j++) { 
            s.insert({ j, v[i].second }); 
        } 
    } 
  
    return s.size(); 
} 



void AlgorithmTest(int dimension,int iterations,vector<pair<int, int> > v){
    FILE* fp;
    fp = fopen("AlgorithmTest.txt", "a+");

    // Console write
    printf("----------------------------------\n");
    printf("Test :   Algorithm       \n");
    printf("----------------------------------\n");
    printf("Dimension : %d\n", dimension);
    printf("Co-ordinates: (x1,y1)=(%d,%d); (x2,y2)=(%d,%d); (x3,y3)=(%d,%d)\n",v[0].first,v[0].second,v[1].first,v[1].second,v[2].first,v[2].second);
    printf("..................................\n");
    
    // File write
    fprintf(fp, "----------------------------------\n");
    fprintf(fp, "Test :  Algorithm        \n");
    fprintf(fp, "----------------------------------\n");
    fprintf(fp, "Dimension : %d\n", dimension);
    fprintf(fp,"Co-ordinates: (x1,y1)=(%d,%d); (x2,y2)=(%d,%d); (x3,y3)=(%d,%d)\n",v[0].first,v[0].second,v[1].first,v[1].second,v[2].first,v[2].second);
    fprintf(fp, "..................................\n");

    double* opmLatency = (double *)malloc(iterations * sizeof(double));
    int result;
    for(int i=0; i<iterations; i++){
         
        struct timeval t0, t1;
        gettimeofday(&t0, 0);
        result = seq_Minimum_Cells(v);
        gettimeofday(&t1, 0);
        double elapsed = (t1.tv_sec-t0.tv_sec) * 1.0f + (t1.tv_usec - t0.tv_usec) / 1000000.0f;
        opmLatency[i] = elapsed;

        // Console write
        printf("%d.\t%f\n", i+1, opmLatency[i]);

        // File write
        fprintf(fp, "%d.\t%f\n", i+1, opmLatency[i]);
    }
    printf("Minimum Cells that are connected is: %d\n",result);
    fprintf(fp,"Minimum Cells that are connected is: %d\n",result);
       

    // Console write
    printf("\n");
    printf("----------------------------------\n");
    printf("Analyze Measurements              \n");
    printf("----------------------------------\n");

    // File write
    fprintf(fp, "\n");
    fprintf(fp, "----------------------------------\n");
    fprintf(fp, "Analyze Measurements              \n");
    fprintf(fp, "----------------------------------\n");

    double sum = 0.0;
    double sumSquared = 0.0;

    // Statistical analyze
    for(int i=0; i<iterations; i++){
        sum += opmLatency[i];
        sumSquared += pow(opmLatency[i], 2.0);
    }

    double mean = sum / iterations;
    double squareMean = sumSquared / iterations;
    double standardDeviation = sqrt(squareMean - pow(mean, 2.0));

    // Console write
    printf("Mean               : %f\n", mean);
    printf("Standard Deviation : %f\n", standardDeviation);
    printf("----------------------------------\n");

    //File write
    fprintf(fp, "Mean               : %f\n", mean);
    fprintf(fp, "Standard Deviation : %f\n", standardDeviation);
    fprintf(fp, "----------------------------------\n");

    // Releasing memory
    fclose(fp);
    free(opmLatency);
}


  
// Driver Function 
int main(int argc, char* argv[]) 
{ 
    

    int iterations = strtol(argv[1], NULL, 10);
    //creating file
    FILE* fp;
    fp = fopen("AlgorithmTest.txt", "w+");
    fclose(fp);
    for(int dim = 2000; dim<20000;dim+=2000){
        // vector pair to store X, Y, Z 
        vector<pair<int, int> > v;
        // Generating Random points
        for(int j=0;j<3;j++){
            srandom(time(0)+clock()+random());
            v.push_back(make_pair(rand() % dim,rand() % dim));

        }
        AlgorithmTest(dim,iterations,v);
        
    }
  
    return 0; 
} 
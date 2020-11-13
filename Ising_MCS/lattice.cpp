#include<iostream>
#include<cstdlib>
#include<cmath>
#include<ctime>
#include<cstring>

using namespace std;

const double T = 4.0;
const int N = 100;
const long n = 20000000;
int **s = new int*[N];

int *nb = new int[4];

void get_neighbor(int *nb, long i, long j){
    int top, bottom, left, right;
    if (i==0){
        top = s[N-1][j];
    }
    else{
        top = s[i-1][j];
    }

    if (i==N-1){
        bottom = s[0][j];
    }
    else{
        bottom = s[i+1][j];
    }

    if (j==0){
        left = s[i][N-1];
    }
    else{
        left = s[i][j-1];
    }
    
    if (j==N-1){
        right = s[i][0];
    }
    else{
        right = s[i][j+1];
    }
    nb[0] = top;
    nb[1] = bottom;
    nb[2] = left;
    nb[3] = right;
}

long dU(long i,long j){
    get_neighbor(nb, i, j);
    return 2*s[i][j]*(nb[0]+nb[1]+nb[2]+nb[3]);
}

void init(){
    for (int i=0;i<N;i++){
        s[i] = new int[N];
    }
    
    srand(time(0));
    
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            s[i][j] = 2 * (rand()%2) - 1;
        }
    }
}

void change(){
    int i = rand()%N;
    int j = rand()%N;
    int dE = dU(i,j);
    if ( dE <= 0){
        s[i][j] = - s[i][j];
    }
    else{
        double r = double(rand()%RAND_MAX) / RAND_MAX;
        if (exp(-dE/T) > r){
            s[i][j] = - s[i][j];
        }
    }
}


int main(){
    init();
    
    for (int k=0;k<n;k++){
        change();
    }
    
    FILE *file;
    file = fopen("lattice.txt", "w");
    
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            char str;
            int p = (1-s[i][j])/2;
            sprintf(&str, "%d", p);
            fprintf(file, &str);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    
    
    for (int i=0;i<N;i++){
        delete[] s[i];
    }
    delete[] s;
    delete[] nb;
    
    return 0;
}

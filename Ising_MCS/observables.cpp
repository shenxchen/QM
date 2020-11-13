#include<iostream>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<cstring>

using namespace std;

const double T0 = 1.2;
const double dT=0.05;
const int nT = 61;
const long N = 10;
const long n1 = 200000;
const long n2 = 200000;

static int **s = new int*[N];

int *nb = new int[4];

void neighbor(int *nb, long i, long j){
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
    neighbor(nb, i, j);
    return 2*s[i][j]*(nb[0]+nb[1]+nb[2]+nb[3]);
}

void init(){
    for (long i=0;i<N;i++){
        s[i] = new int[N];
    }
    
    srand(time(0));
    
    for (long i=0;i<N;i++){
        for (long j=0;j<N;j++){
            s[i][j] = 2 * (rand()%2) - 1;
        }
    }
}

void change(double T){
    long i = rand()%N;
    long j = rand()%N;
    long dE = dU(i,j);
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

double calMagUnit(int **s){
    long sum = 0;
    for (long i=0;i<N;i++){
        for (long j=0;j<N;j++){
            sum += s[i][j];
        }   
    }
    return double(abs(sum))/(N*N);
}

double calEneUnit(int **s){
    long sum = 0;
    for (long i=0;i<N;i++){
        for (long j=0;j<N;j++){
            neighbor(nb, i, j);
            sum += -s[i][j] * (nb[0]+nb[1]+nb[2]+nb[3]);
        }
    }
    return double(sum)/4/(N*N);
}

int main(){
    FILE *file;
    file = fopen("observables.csv", "w");

    for (int j=0;j<nT;j++){
        double T = T0 + j*dT;
        init();
        
        for (long k=0;k<n1;k++){
            change(T);
        }
        
        double M_sum = 0;
        double M2_sum = 0;
        double E_sum = 0;
        double E2_sum = 0;
        for (long k=0;k<n2;k++){
            change(T);
        
            double MagUnit = calMagUnit(s);
            double MagUnit2 = MagUnit*MagUnit;
            double EneUnit = calEneUnit(s);
            double EneUnit2 = EneUnit*EneUnit;
        
            M_sum += MagUnit;
            M2_sum += MagUnit2;
            E_sum += EneUnit;
            E2_sum += EneUnit2;
            
        
        }
    
    
    
        double M = M_sum/n2;
        double X = (M2_sum*pow(N,4)/n2 - pow(M_sum*N*N/n2,2))/T/(N*N);
        double E = E_sum/n2;
        double C = (E2_sum*pow(N,4)/n2 - pow(E_sum*N*N/n2,2))/(T*T)/(N*N);
    
        
        char T_string[16];
        char M_string[16];
        char E_string[16];
        char X_string[16];
        char C_string[16];
        strcpy(T_string, to_string(T).data());
        strcpy(M_string, to_string(M).data());
        strcpy(E_string, to_string(E).data());
        strcpy(X_string, to_string(X).data());
        strcpy(C_string, to_string(C).data());
        
        fprintf(file, T_string);
        fprintf(file, " ");
        fprintf(file, M_string);
        fprintf(file, " ");
        fprintf(file, E_string);
        fprintf(file, " ");
        fprintf(file, X_string);
        fprintf(file, " ");
        fprintf(file, C_string);
        fprintf(file, "\n");
    
        cout<<"T="<<T<<" finished"<<endl;
    }
    fclose(file);
    
    //delete
    for (long i=0;i<N;i++){
        delete[] s[i];
    }
    delete[] s;
    delete[] nb;
    
    return 0;
}

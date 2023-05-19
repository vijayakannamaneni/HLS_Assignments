
#include<iostream>
#include <complex>
using namespace std;
#define N 4

typedef std::complex<double >cmpx;

void fir_filter(cmpx x[N] ,cmpx h[N],cmpx y[N+N-1]);

int main ()
{

    cmpx x[N]={{1,1},{2,1},{3,1},{4,1}};
    cmpx h[N]={{1,1},{2,1},{3,1},{4,1}};
    cmpx y[N+N-1];
    fir_filter(x,h,y);
    for(int i=0;i<N+N-1;i++)
        {
               std::cout << y[i] << " ";
        }


return 0 ;
}


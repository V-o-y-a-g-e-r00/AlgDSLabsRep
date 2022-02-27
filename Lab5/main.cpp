#include <iostream>

#include <math.h>
#include <vector>
#include <fstream>
#include <iomanip> //setprecision

#define RADIUS 40
struct point
{
    int VertIndex=0;
    double x=0;
    double y=0;
};

void SetVertCoord(int N, int CenterX=0, int CenterY=0, const char* fname="pnts.dat")
{
    double r=RADIUS;
    double alpha=0;
    double dalpha=2*M_PI/N;
    
    double x, y;
    int CurrVertIndex=0;
    std::vector<point> pnts(N); 

    std::vector<point>::iterator iter;
    for(int i=0; i<N; i++)
    {
        //(i%2==0) ? r/=1.5 : r*=1.5;
        
        pnts.at(i).VertIndex=CurrVertIndex;
        pnts.at(i).x=cos(alpha)*r;
        pnts.at(i).y=sin(alpha)*r;
        
        if(i%8<4) r-=RADIUS*0.15;
        else r+=RADIUS*0.15;

        CurrVertIndex++;
        alpha+=dalpha;
    }
    iter=pnts.begin();

    while(iter!=pnts.end())
    {
        std::cout<< "pnts element:"<< std::distance(pnts.begin(),iter)<<" :VertIndex="<< iter->VertIndex<< "; x="<<iter->x<<"; y="<<iter->y<<std::endl;
        iter++;
    }

    std::ofstream fd(fname, std::ios_base::out|std::ios_base::trunc);
    iter=pnts.begin();
    while(iter!=pnts.end())
    {
        fd<< std::fixed <<std::setprecision(3)<<iter->VertIndex<< "\t"<<iter->x<<"\t"<<iter->y<<std::endl;
        iter++;
    }
    fd.close();
}


int main(int, char**) {
    std::cout << "Hello, world!\n";
    SetVertCoord(50);
    system("./PlotGraph.gpi");
}

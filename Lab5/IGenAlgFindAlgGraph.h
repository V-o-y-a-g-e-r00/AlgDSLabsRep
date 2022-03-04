#ifndef IGENALGFINDALGGRAPH_H
#define IGENALGFINDALGGRAPH_H

#include "random"
#include "Graph.h"

class IGenAlgFindAlgGraph: public Graph  //интерфейс для статистики. В данном интерфейсе генерация должна совершаться по заданным n m(которые будет передавать интерфейсу класс статистики). Для других способов генерации нужен отдельный интерфейс и отдельный класс статистики.
{
public:
    virtual void Generate(int N, int m, int WeightMax, std::default_random_engine& generator)=0;
    virtual void Find()=0;
};

#endif /* IGENALGFINDALGGRAPH_H */

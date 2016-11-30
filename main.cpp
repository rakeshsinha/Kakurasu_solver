#include <chrono>

#include "kakurasu.h"

using namespace std;

int main(int argc, char *argv[])
{
    auto startTime = std::chrono::high_resolution_clock::now();
    Kakurasu *kakurasu;
    if(argc == 2)
    {
        kakurasu = new Kakurasu(argv[1]);
    }
    else
    {
        cout<<"Exceeds or needs Parameter\n";
        cout<<"Usage : ./kakurasu <filename>\n"
                "Make sure there is no space in the filename\n";
        return 0;
    }

    kakurasu->printSolMatrix();
    kakurasu->getAllCombinations();
    kakurasu->ACAlgorithm((kakurasu->rowVector), (kakurasu->columnVector), kakurasu->checkMatrix);
    kakurasu -> unIdentified = kakurasu->unidentifiedVariables(kakurasu->checkMatrix, kakurasu->fMatrix);
    cout<<"\n\n In main : number of Unidentified Variables are : "<<kakurasu -> unIdentified <<"\n\n";
    if(kakurasu->unIdentified == 0)
    {
        cout<<"\n Problem is Solved Using AC Algorithm";
    }
    else
    {
        kakurasu->stm(kakurasu->fValueList, kakurasu->checkMatrix, kakurasu->fMatrix);
        fflush(stdout);
        kakurasu->searchalgorithm(kakurasu->rowVector, kakurasu->columnVector, kakurasu->checkMatrix, kakurasu->fMatrix, kakurasu->fValueList);
    }


    cout<<"\n Final Solution in Main Function : check Matrix : \n";
    for(int i =1; i<=kakurasu->length; i++)
    {
        cout<<"\n";
        for(int j = 1; j<=kakurasu->length; j++)
        {
            cout<<"\t"<<kakurasu->checkMatrix[i][j];
        }
    }
    auto finishTime = std::chrono::high_resolution_clock::now();
    cout << "\n"<<std::chrono::duration_cast<std::chrono::nanoseconds>(finishTime-startTime).count() << "ns\n";
    return 0;
}

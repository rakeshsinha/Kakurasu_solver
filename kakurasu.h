#ifndef KAKURASU_H
#define KAKURASU_H

#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include <set>
#include <list>
#include <sstream>
#include <algorithm>

using namespace std;
struct elementId { int indices[2];};
struct bits { bitset<9> e;};

inline bool operator<(const bits & e1, const bits& e2)
{
    bitset<9> tp1 = e1.e;
    bitset<9> tp2 = e2.e;
    return ((int)tp1.to_ulong() < (int)tp2.to_ulong());
}

inline bool operator<(const elementId& e1, const elementId& e2)
{
    if(e1.indices[0] == e2.indices[0])
        return e1.indices[1]<e2.indices[1];
    return e1.indices[0]<e2.indices[0];
}

struct fValue
{
    int rindex;
    int cindex;
    float scoreValue;
};
//October 19 - Easy 8 x 8

class Kakurasu
{
public:
    Kakurasu(char *fileName)
    {
        solutionFound = false;
        string line, token;
        stringstream ss;
        unIdentified = 0;
        ifstream in(fileName);
        if (in.is_open())
        {
            getline(in, line);
            line.erase(remove(line.begin(), line.end(), ' '), line.end());
            length = atoi(line.c_str());

            solMatrix = new bool*[length + 1];
            for(int i = 1; i <= length; i++)
                solMatrix[i] = new bool[length + 1];

            for(int i = 1; i <= length; i++)
                for(int j = 1; j <= length; j++)
                    solMatrix[i][j] = false;

            rowSum = new int[length + 1];
            columnSum = new int[length + 1];
            rowCount = new int[length+1];
            columnCount = new int[length+1];
            rSortedIndex = new int[length+1];
            cSortedIndex = new int[length+1];
            for(int i = 1; i <= length; i++)
            {
                rowCount[i] = 0;
                columnCount[i] = 0;
                rSortedIndex[i] = i;
                cSortedIndex[i] = i;

            }
            checkMatrix = new int* [length+1];
            fMatrix = new int* [length+1];
            for(int i = 0; i<=length; i++)
            {
                checkMatrix[i] = new int[length+1];
                fMatrix[i] = new int[length+1];
            }
            for(int i = 0; i<=length; i++)
            {
                for(int j = 0; j<=length; j++)
                {
                    checkMatrix[i][j] = -1;
                }
            }
            int count = 0;
            while(getline(in, line))
            {
                if(count > length)
                {
                    cout<<"\nArguments more than the size of the matrix";
                    break;
                }
                else
                {
                    ss.str("");
                    ss.clear();
                    ss.str(line);
                    string str[2];
                    int i=0;
                    while(getline(ss, token, ','))
                        str[i++] = token;

                    if(atoi(str[0].c_str()) == -1 && atoi(str[1].c_str()) != -1)
                    {
                        rowSum[++count] = -1;
                        columnSum[count] = atoi(str[1].c_str());
                    }
                    else if(atoi(str[1].c_str()) == -1 && atoi(str[0].c_str()) != -1)
                    {
                        rowSum[++count] = atoi(str[0].c_str());
                        columnSum[count] = -1;
                    }
                    else if(atoi(str[1].c_str()) == -1 && atoi(str[0].c_str()) == -1)
                    {
                        rowSum[++count] = -1;
                        columnSum[count] = -1;
                    }
                    else
                    {
                        rowSum[++count] = atoi(str[0].c_str());
                        columnSum[count] = atoi(str[1].c_str());
                    }
                }
            }
        }
        in.close();

        rowVector = new vector<vector<bitset<9>>*>;
        columnVector = new vector<vector<bitset<9>>*>;
        for(int i = 0; i<=length - 1; i++)
        {
            rowVector->push_back((new vector<bitset<9>>));
            columnVector->push_back((new vector<bitset<9>>));
        }
    }

    void getAllCombinations();
    void printSolMatrix();
    int length;
    int unIdentified;
    bool **solMatrix;
    int *rowSum;
    int *columnSum;
    vector<vector<bitset<9>>*> *rowVector;
    vector<vector<bitset<9>>*> *columnVector;
    int *rowCount;
    int *columnCount;
    int *rSortedIndex;
    int *cSortedIndex;
    void sortIndex(int *, int *);
    int **checkMatrix;
    void ACAlgorithm(vector<vector<bitset<9>>*> *, vector<vector<bitset<9>>*> *, int **);
    set<elementId> priorityQueue;
    set<elementId> listOfVariables;
    int **fMatrix;
    int unidentifiedVariables(int **, int **);
    list<fValue> fValueList;
    void stm(list<fValue>& , int **, int **);
    float FValueCalculate(int, int, list<fValue>);
    set<elementId> elementsToCheck;
    list<int> col_position;
    list<int> row_position;
    set<bits> colVariableCombinations;
    set<bits> colVariableCombinations1;
    set<bits> rowVariableCombinations;
    set<bits> rowVariableCombinations1;
    void searchalgorithm(vector<vector<bitset<9>>*> *, vector<vector<bitset<9>>*> *, int **, int ** , list<fValue>);
    void printCheckMatrix(int **);
    void printfMatrix(int **);
    bool solutionFound;
};

#endif // KAKURASU_H

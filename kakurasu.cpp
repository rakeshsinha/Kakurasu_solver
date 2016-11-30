#include <math.h>
#include <stdio.h>
#include <iterator>
#include "kakurasu.h"


void Kakurasu::printSolMatrix()
{
    for(int i = 1; i <= length; i++)
    {
        cout<<"\n";
        for(int j = 1; j <= length; j++)
            cout<<"\t"<<solMatrix[i][j];
        cout<<"\t"<<rowSum[i];
    }
    cout<<"\n";
    for(int i = 1; i <= length; i++)
        cout<<"\t"<<columnSum[i];

}


void Kakurasu::getAllCombinations()
{
    int sum = 0;
    for(long int i = 1; i<=(pow(2,length) - 1); i++)
    {
        sum = 0;
        bitset<9> set(i);

        for(int j = 1; j<=length; j++)
        {
            sum = sum + set[j - 1] * j;
        }
        for(int j = 1; j<=length; j++)
        {
            if(sum == rowSum[j])
            {
                rowVector->at(j - 1)->push_back(set);
                rowCount[j]+=1;
            }
            if(sum == columnSum[j])
            {
                columnVector->at(j - 1)->push_back(set);
                columnCount[j]+=1;
            }
            if(rowSum[j] == -1)
            {
                rowVector->at(j - 1)->push_back(set);
                rowCount[j]+=1;
            }
            if(columnSum[j] == -1)
            {
                columnVector->at(j - 1)->push_back(set);
                columnCount[j]+=1;
            }
        }
    }
    cout<<"\n-------------- Initial Combinations:----------------- \n";
    cout<<"\nFor all rows\n";
    int count = 0;
    for(vector<vector<bitset<9>>*>::iterator it = rowVector->begin() ; it != rowVector->end(); ++it)
    {
        cout<<"\nFor row : "<<++count<<"\n";
        for(vector<bitset<9>>::iterator itIn = (*it)->begin() ; itIn != (*it)->end(); ++itIn)
            cout<<*itIn<<"\t";
    }

    cout<<"\nFor all columns\n";
    count = 0;
    for(vector<vector<bitset<9>>*>::iterator it = columnVector->begin() ; it != columnVector->end(); ++it)
    {
        cout<<"\nFor column : "<<++count<<"\n";
        for(vector<bitset<9>>::iterator itIn = (*it)->begin() ; itIn != (*it)->end(); ++itIn)
            cout<<*itIn<<"\t";
    }
   /* cout<<"\n row assignment count : \n";
    for(int i = 1; i<=sizeOfTheProblem; i++)
    {
        cout<<"\nFor Row "<<i<<" total assignments are :"<<rowAssignmentCount[i];
    }
    cout<<"\n Column assignment count : \n";
    for(int i = 1; i<=sizeOfTheProblem; i++)
    {
        cout<<"\nFor Column "<<i<<" total assignments are :"<<colAssignmentCount[i];
    }
    sortIndex(rowAssignmentCount, rowSortedIndex);
    sortIndex(colAssignmentCount, colSortedIndex);

    cout<<"\n array rowSortedIndex: \n";
    for(int i = 1; i<=sizeOfTheProblem; i++)
    cout<<"\t"<<rowSortedIndex[i];
    cout<<"\n array colSortedIndex: \n";
    for(int i = 1; i<=sizeOfTheProblem; i++)
    cout<<"\t"<<colSortedIndex[i];*/
}


void Kakurasu :: ACAlgorithm(vector<vector<bitset<9>>*> *temprow , vector<vector<bitset<9>>*> *tempcol, int **tempMatrix)
{

    cout<<"\n ---------------AC Algorithm Begins----------------------------\n";
    for(int i = 0; i<length; i++)
    {

        bitset<9> temp(0), temp1(pow(2,9)-1);
        for(vector<bitset<9>>::iterator itIn = temprow->at(i)->begin() ; itIn != temprow->at(i)->end(); ++itIn)
        {
            temp|=(*itIn);
            temp1&=(*itIn);
        }
        for(int j=length-1; j>=0; j--)
        {
            if(temp[j]==0)
            {
                if(tempMatrix[i+1][j+1] == -1)
                {
                    struct elementId e1;
                    e1.indices[0] = i+1;
                    e1.indices[1] = j+1;
                    priorityQueue.insert(e1);
                    tempMatrix[i+1][j+1] = 0;
                }
            }
            if(temp1[j] == 1)
            {
                if(tempMatrix[i+1][j+1] == -1)
                {
                    struct elementId e1;
                    e1.indices[0] = i+1;
                    e1.indices[1] = j+1;
                    priorityQueue.insert(e1);
                    tempMatrix[i+1][j+1] = 1;
                }
            }
        }
        if(temprow->at(i)->size() == 1)
        {
            for(int j=length-1; j>=0; j--)
            {
                if(temp[j]==1 and tempMatrix[i+1][j+1]==-1)
                {
                    struct elementId e;
                    e.indices[0] = i+1;
                    e.indices[1] = j+1;
                    priorityQueue.insert(e);
                    tempMatrix[i+1][j+1]=1;

                }
                if(temp[j]==0 and tempMatrix[i+1][j+1]==-1)
                {
                    struct elementId e;
                    e.indices[0] = i+1;
                    e.indices[1] = j+1;
                    priorityQueue.insert(e);
                    tempMatrix[i+1][j+1]=0;

                }
            }
        }
    }
    for(int i = 0; i<length; i++)
    {
        bitset<9> temp(0), temp1(pow(2,9)-1);
        for(vector<bitset<9>>::iterator itIn = tempcol->at(i)->begin() ; itIn != tempcol->at(i)->end(); ++itIn)
        {
            temp|=(*itIn);
            temp1&=(*itIn);
        }
        for(int j=length-1; j>=0; j--)
        {
            if(temp[j]==0)
            {
                if(tempMatrix[j+1][i+1] == -1)
                {
                    struct elementId e1;
                    e1.indices[0] = j+1;
                    e1.indices[1] = i+1;
                    priorityQueue.insert(e1);
                    tempMatrix[j+1][i+1] = 0;
                }
            }
            if(temp1[j]==1)
            {
                if(tempMatrix[j+1][i+1] == -1)
                {
                    struct elementId e1;
                    e1.indices[0] = j+1;
                    e1.indices[1] = i+1;
                    priorityQueue.insert(e1);
                    tempMatrix[j+1][i+1] = 1;
                }
            }
        }
        if(tempcol->at(i)->size() == 1)
        {
            for(int j=length-1; j>=0; j--)
            {
                if(temp[j]==1 and tempMatrix[j+1][i+1]==-1)
                {
                    struct elementId e;
                    e.indices[0] = j+1;
                    e.indices[1] = i+1;
                    priorityQueue.insert(e);
                    tempMatrix[j+1][i+1]=1;
                }
                if(temp[j]==0 and tempMatrix[j+1][i+1]==-1)
                {
                    struct elementId e;
                    e.indices[0] = j+1;
                    e.indices[1] = i+1;
                    priorityQueue.insert(e);
                    tempMatrix[j+1][i+1]=0;
                }
            }
        }
    }

/********
 * pop each element from Queue and check for the respective temprow and tempcol, if any non-essentials or essentials assignments available
 */

    cout<<"\n-------------------- Initial Queue Elements :---------------------------\n";
    for (std::set<elementId>::iterator itpQueue=priorityQueue.begin(); itpQueue!=priorityQueue.end(); ++itpQueue)
            cout<<"\n\nqueue elements  : "<<(*itpQueue).indices[0]<<" and , "<<(*itpQueue).indices[1]<<"\n";

    //for (std::set<elementId>::iterator itSet = pQueue.begin(); itSet != pQueue.end(); itSet++)
    while(!priorityQueue.empty())
    {
        std::set<elementId>::iterator itSet = priorityQueue.begin();
        struct elementId e1;
        e1.indices[0] = (*itSet).indices[0];
        e1.indices[1] = (*itSet).indices[1];

        priorityQueue.erase(itSet);
        cout<<"\n popped element from queue is : "<<e1.indices[0]<<" , "<<e1.indices[1];



//ac for temprow
        if(tempMatrix[e1.indices[0]][e1.indices[1]]==0)
        {
            for(vector<bitset<9>>::iterator itIn = temprow->at(e1.indices[0]-1)->begin() ; itIn != temprow->at(e1.indices[0]-1)->end(); ++itIn)
            {
                if((*itIn)[e1.indices[1]-1]==1)
                {
                    cout<<"\n removed assignment is "<<(*itIn);
                    itIn=temprow->at(e1.indices[0]-1)->erase(itIn);
                    itIn--;
                    rowCount[e1.indices[0]]--;
                }

            }
            bitset<9> temp(0), temp1(pow(2,9)-1);
            for(vector<bitset<9>>::iterator itIn = temprow->at(e1.indices[0]-1)->begin() ; itIn != temprow->at(e1.indices[0]-1)->end(); ++itIn)
            {
                temp|=(*itIn);
                temp1&=(*itIn);
            }
            for(int j=length-1; j>=0; j--)
            {
                if(temp[j]==0)
                {
                    struct elementId e2;
                    e2.indices[0] = e1.indices[0];
                    e2.indices[1] = j+1;
                    if(tempMatrix[e1.indices[0]][j+1]==-1)
                    {
                        priorityQueue.insert(e2);
                        tempMatrix[e1.indices[0]][j+1] = 0;
                        cout<<"\n Index number : "<<e1.indices[0] <<", "<<j+1<<" = 0\n";
                        printCheckMatrix(tempMatrix);
                    }
                }
                if(temp1[j]==1)
                {
                    struct elementId e2;
                    e2.indices[0] = e1.indices[0];
                    e2.indices[1] = j+1;
                    if(tempMatrix[e1.indices[0]][j+1]==-1)
                    {
                        priorityQueue.insert(e2);
                        tempMatrix[e1.indices[0]][j+1] = 1;
                    }
                }
            }
            if(temprow->at(e1.indices[0]-1)->size() == 1)
            {
                for(int j=length-1; j>=0; j--)
                {
                    if(temp[j]==1 and tempMatrix[e1.indices[0]][j+1]==-1)
                    {
                        struct elementId e;
                        e.indices[0] = e1.indices[0];
                        e.indices[1] = j+1;
                        priorityQueue.insert(e);
                        tempMatrix[e1.indices[0]][j+1]=1;
                    }
                    if(temp[j]==0 and tempMatrix[e1.indices[0]][j+1]==-1)
                    {
                        struct elementId e;
                        e.indices[0] = e1.indices[0];
                        e.indices[1] = j+1;
                        priorityQueue.insert(e);
                        tempMatrix[e1.indices[0]][j+1]=0;
                    }

                }
            }


//// ac for tempcol

            for(vector<bitset<9>>::iterator itIn = tempcol->at(e1.indices[1]-1)->begin() ; itIn != tempcol->at(e1.indices[1]-1)->end(); ++itIn)
            {
                if((*itIn)[e1.indices[0]-1]==1)
                {
                    cout<<"\n removed assignment is "<<(*itIn);
                    itIn = tempcol->at(e1.indices[1]-1)->erase(itIn);
                    itIn--;
                    columnCount[e1.indices[1]]--;
                }
            }
            temp = 0; temp1 = (pow(2,9)-1);
            cout<<"\n \n temp1 = "<<temp1<<"\n";
            for(vector<bitset<9>>::iterator itIn = tempcol->at(e1.indices[1]-1)->begin() ; itIn != tempcol->at(e1.indices[1]-1)->end(); ++itIn)
            {
                temp|=(*itIn);
                temp1&=(*itIn);
            }
            for(int j=length-1; j>=0; j--)
            {
                if(temp[j]==0)
                {
                    struct elementId e3;
                    e3.indices[0] = j+1;
                    e3.indices[1] = e1.indices[1];
                    if(tempMatrix[j+1][e1.indices[1]]==-1)
                    {
                        priorityQueue.insert(e3);
                        tempMatrix[j+1][e1.indices[1]] = 0;
                    }
                }
                if(temp1[j]==1)
                {
                    struct elementId e3;
                    e3.indices[0] = j+1;
                    e3.indices[1] = e1.indices[1];
                    if(tempMatrix[j+1][e1.indices[1]]==-1)
                    {
                        priorityQueue.insert(e3);
                        tempMatrix[j+1][e1.indices[1]] = 1;
                    }
                }
            }
            if(tempcol->at(e1.indices[1]-1)->size() == 1)
            {
                for(int j=length-1; j>=0; j--)
                {
                    if(temp[j]==1 and tempMatrix[j+1][e1.indices[1]]==-1)
                    {
                        struct elementId e;
                        e.indices[0] = j+1;
                        e.indices[1] = e1.indices[1];
                        priorityQueue.insert(e);
                        tempMatrix[j+1][e1.indices[1]]=1;
                    }
                    if(temp[j]==0 and tempMatrix[j+1][e1.indices[1]]==-1)
                    {
                        struct elementId e;
                        e.indices[0] = j+1;
                        e.indices[1] = e1.indices[1];
                        priorityQueue.insert(e);
                        tempMatrix[j+1][e1.indices[1]]=0;
                    }
                }
            }

        }
        else if(tempMatrix[e1.indices[0]][e1.indices[1]]==1)
        {
            for(vector<bitset<9>>::iterator itIn = temprow->at(e1.indices[0]-1)->begin() ; itIn != temprow->at(e1.indices[0]-1)->end(); ++itIn)
            {
                if((*itIn)[e1.indices[1]-1]==0)
                {
                    cout<<"\n removed assignment is "<<(*itIn);
                    itIn=temprow->at(e1.indices[0]-1)->erase(itIn);
                    itIn--;
                    rowCount[e1.indices[0]]--;
                }

            }
            bitset<9> temp(0), temp1(pow(2,9)-1);
            for(vector<bitset<9>>::iterator itIn = temprow->at(e1.indices[0]-1)->begin() ; itIn != temprow->at(e1.indices[0]-1)->end(); ++itIn)
            {
                temp|=(*itIn);
                temp1&=(*itIn);
            }
            for(int j=length-1; j>=0; j--)
            {
                if(temp[j]==0)
                {
                    struct elementId e2;
                    e2.indices[0] = e1.indices[0];
                    e2.indices[1] = j+1;
                    if(tempMatrix[e1.indices[0]][j+1]==-1)
                    {
                        priorityQueue.insert(e2);
                        tempMatrix[e1.indices[0]][j+1] = 0;
                    }
                }
                if(temp1[j]==1)
                {
                    struct elementId e2;
                    e2.indices[0] = e1.indices[0];
                    e2.indices[1] = j+1;
                    if(tempMatrix[e1.indices[0]][j+1]==-1)
                    {
                        priorityQueue.insert(e2);
                        tempMatrix[e1.indices[0]][j+1] = 1;
                    }
                }
            }
            if(temprow->at(e1.indices[0]-1)->size() == 1)
            {
                for(int j=length-1; j>=0; j--)
                {
                    if(temp[j]==1 and tempMatrix[e1.indices[0]][j+1]==-1)
                    {
                        struct elementId e;
                        e.indices[0] = e1.indices[0];
                        e.indices[1] = j+1;
                        priorityQueue.insert(e);
                        tempMatrix[e1.indices[0]][j+1]=1;
                    }
                    if(temp[j]==0 and tempMatrix[e1.indices[0]][j+1]==-1)
                    {
                        struct elementId e;
                        e.indices[0] = e1.indices[0];
                        e.indices[1] = j+1;
                        priorityQueue.insert(e);
                        tempMatrix[e1.indices[0]][j+1]=0;
                    }

                }
            }

            /*cout<<"\n Remaining assignment of Row "<<e1.indices[0];
            for(vector<bitset<9>>::iterator itIn = temprow->at(e1.indices[0]-1)->begin() ; itIn != temprow->at(e1.indices[0]-1)->end(); ++itIn)
            {
                cout<<"\t"<<(*itIn);
            }

            cout<<"\n check Matrix : \n";
            for(int i =1; i<=sizeOfTheProblem; i++)
            {
                cout<<"\n";
                for(int j = 1; j<=sizeOfTheProblem; j++)
                {
                    cout<<"\t"<<tempMatrix[i][j];
                }
            }
            cout<<"\n\n";*/


            //// ac for tempcol

            for(vector<bitset<9>>::iterator itIn = tempcol->at(e1.indices[1]-1)->begin() ; itIn != tempcol->at(e1.indices[1]-1)->end(); ++itIn)
            {
                if((*itIn)[e1.indices[0]-1]==0)
                {
                    cout<<"\n removed assignment is "<<(*itIn);
                    itIn = tempcol->at(e1.indices[1]-1)->erase(itIn);
                    itIn--;
                    columnCount[e1.indices[1]]--;
                }
            }
            temp = 0; temp1 = pow(2,9)-1;
            for(vector<bitset<9>>::iterator itIn = tempcol->at(e1.indices[1]-1)->begin() ; itIn != tempcol->at(e1.indices[1]-1)->end(); ++itIn)
            {
                temp|=(*itIn);
                temp1&=(*itIn);
            }
            for(int j=length-1; j>=0; j--)
            {
                if(temp[j]==0)
                {
                    struct elementId e3;
                    e3.indices[0] = j+1;
                    e3.indices[1] = e1.indices[1];
                    if(tempMatrix[j+1][e1.indices[1]]==-1)
                    {
                        priorityQueue.insert(e3);
                        tempMatrix[j+1][e1.indices[1]] = 0;
                    }

                }
                if(temp1[j]==1)
                {
                    struct elementId e3;
                    e3.indices[0] = j+1;
                    e3.indices[1] = e1.indices[1];
                    if(tempMatrix[j+1][e1.indices[1]]==-1)
                    {
                        priorityQueue.insert(e3);
                        tempMatrix[j+1][e1.indices[1]] = 1;
                    }

                }
            }
            if(tempcol->at(e1.indices[1]-1)->size() == 1)
            {
                for(int j=length-1; j>=0; j--)
                {
                    if(temp[j]==1 and tempMatrix[j+1][e1.indices[1]]==-1)
                    {
                        struct elementId e;
                        e.indices[0] = j+1;
                        e.indices[1] = e1.indices[1];
                        priorityQueue.insert(e);
                        tempMatrix[j+1][e1.indices[1]]=1;
                    }
                    if(temp[j]==0 and tempMatrix[j+1][e1.indices[1]]==-1)
                    {
                        struct elementId e;
                        e.indices[0] = j+1;
                        e.indices[1] = e1.indices[1];
                        priorityQueue.insert(e);
                        tempMatrix[j+1][e1.indices[1]]=0;
                    }
                }
            }

            /*cout<<"\n check Matrix : \n";
            for(int i =1; i<=sizeOfTheProblem; i++)
            {
                cout<<"\n";
                for(int j = 1; j<=sizeOfTheProblem; j++)
                {
                    cout<<"\t"<<tempMatrix[i][j];
                }
            }
            cout<<"\n\n";*/
        }
    }


    cout<<"\n\n\n\n\n---------------------After AC Algorithm---------------------------------------------\n\n\n";

    /*for (std::set<elementId>::iterator itpQueue=pQueue.begin(); itpQueue!=pQueue.end(); ++itpQueue)
        cout<<"\n\n queue elements  : "<<(*itpQueue).indices[0]<<" and , "<<(*itpQueue).indices[1]<<"\n";
*/
    cout<<"\n check Matrix : \n";
    for(int i =1; i<=length; i++)
    {
        cout<<"\n";
        for(int j = 1; j<=length; j++)
        {
            cout<<"\t"<<tempMatrix[i][j];
        }
    }
    int count = 0;
    for(vector<vector<bitset<9>>*>::iterator it = temprow->begin() ; it != temprow->end(); ++it)
    {
        cout<<"\nFor row : "<<++count<<"\n";
        for(vector<bitset<9>>::iterator itIn = (*it)->begin() ; itIn != (*it)->end(); ++itIn)
            cout<<*itIn<<"\t";
    }

    cout<<"\nFor all tempcol\n";
    count = 0;
    for(vector<vector<bitset<9>>*>::iterator it = tempcol->begin() ; it != tempcol->end(); ++it)
    {
        cout<<"\nFor column : "<<++count<<"\n";
        for(vector<bitset<9>>::iterator itIn = (*it)->begin() ; itIn != (*it)->end(); ++itIn)
            cout<<*itIn<<"\t";
    }
}

void Kakurasu :: printCheckMatrix(int **tempCM)
{
    cout<<"\n check Matrix : \n";
    for(int i =1; i<=length; i++)
    {
        cout<<"\n";
        for(int j = 1; j<=length; j++)
        {
            cout<<"\t"<<tempCM[i][j];
        }
    }
}

void Kakurasu :: printfMatrix(int **tempFM)
{
    cout<<"\n F Matrix is  : \n";
        for(int i =1; i<=length; i++)
        {
            cout<<"\n";
            for(int j = 1; j<=length; j++)
            {
                cout<<"\t"<<tempFM[i][j];
            }
        }
}



int Kakurasu :: unidentifiedVariables(int **tempMat, int **ftempMatrix)
{
    int temp = 0;
    for(int i =1; i<=length; i++)
    {
        for(int j = 1; j<= length; j++)
        {
            if(tempMat[i][j] == -1)
            {
                ftempMatrix[i][j] = tempMat[i][j];
                temp+=1;
            }
            else
            {
                ftempMatrix[i][j] = 1;
            }
        }
    }
    return temp;
}

void Kakurasu :: stm(list<fValue> &fList, int **tempMat, int **ftempMatrix)
{
    cout<<"\n\n\n-----------STM Starts---------------- \n\n\n";
    bool flag = false;
    for(int i = 1; i<= length; i++)
    {
        for(int j = 1; j<=length; j++)
        {
            if(tempMat[i][j] == -1)
            {
                struct fValue v1;
                v1.rindex = i;
                v1.cindex = j;
                v1.scoreValue = 2*FValueCalculate(i,j,fList);
                fList.push_back(v1);
                ftempMatrix[i][j] = 1;
                flag = true;
                break;
            }
        }
        if(flag == true)
        {
            break;
        }
    }
    int next_row_index, next_col_index, nextfValue;
    float minScore,score;
    for(int i = 1; i<=unIdentified; i++)
    {
        for(list<fValue>::iterator it = fList.begin(); it != fList.end(); it++)
        {
            int row_number = (*it).rindex;
            int col_number = (*it).cindex;
            for(int j = 1; j<=length; j++)
            {
                if(ftempMatrix[row_number][j] == -1)
                {
                    struct elementId e;
                    e.indices[0] = row_number;
                    e.indices[1] = j;
                    elementsToCheck.insert(e);
                }
            }
            for(int j = 1; j<=length; j++)
            {
                if(ftempMatrix[j][col_number] == -1)
                {
                    struct elementId e;
                    e.indices[0] = j;
                    e.indices[1] = col_number;
                    elementsToCheck.insert(e);
                }
            }
        }
        cout<<"\n\n\n ---Elements in the :elementsToCheck: list :----\n\n";
        for(set<elementId>:: iterator itIn = elementsToCheck.begin(); itIn != elementsToCheck.end(); itIn++)
        {
            int row_index = (*itIn).indices[0];
            int col_index = (*itIn).indices[1];
            cout<<"("<<row_index<<" , "<<col_index<<")\n";
        }
        minScore = 9999.0;
        for(set<elementId>:: iterator itIn = elementsToCheck.begin(); itIn != elementsToCheck.end(); itIn++)
        {
            int row_index = (*itIn).indices[0];
            int col_index = (*itIn).indices[1];
            score = 2.0 * FValueCalculate(row_index, col_index, fList);

            if(score < minScore)
            {
                minScore = score;
                next_row_index = row_index;
                next_col_index = col_index;
                nextfValue = minScore;
            }
        }
        if(!elementsToCheck.empty())
        {
            struct fValue v1;
            v1.cindex = next_col_index;
            v1.rindex = next_row_index;
            v1.scoreValue = nextfValue;
            cout<<"\n\n minimum score value among above values is : \n";
            cout<<"("<<v1.rindex<<" , "<<v1.cindex<<" , "<<v1.scoreValue<<")\n";
            fList.push_back(v1);
            ftempMatrix[next_row_index][next_col_index] = 1;
        }
        while(!elementsToCheck.empty())
        {
            elementsToCheck.clear();
        }
        cout<<"\nF values are : \n";
        for(list<fValue>::iterator it = fList.begin(); it != fList.end(); it++)
        {
            cout<<"("<<(*it).rindex<<" , "<<(*it).cindex<<" , "<<(*it).scoreValue<<")\n";
        }
        fflush(stdout);
    }

    cout<<"\n ftempMatrix  is : \n";
    for(int i = 1; i<=length; i++)
    {
        for(int j = 1; j<=length; j++)
        {
            cout<<"\t"<<ftempMatrix[i][j];
        }
        cout<<"\n";
    }

    cout<<"\nF values are : \n";
    for(list<fValue>::iterator it = fList.begin(); it != fList.end(); it++)
    {
        cout<<"("<<(*it).rindex<<" , "<<(*it).cindex<<" , "<<(*it).scoreValue<<")\n";
    }

}

float Kakurasu :: FValueCalculate(int row, int col, list<fValue> fList)
{
    if(fList.empty())
    {
        return 1;
    }
    else
    {
/////F Value for row constraints
        for(list<fValue>::iterator it = fList.begin(); it != fList.end(); it++)
        {
            if((*it).rindex == row)
            {
                col_position.push_back((*it).cindex);
            }
        }
        const int t = col_position.size();
        for(vector<bitset<9>>::iterator itIn = rowVector->at(row-1)->begin() ; itIn != rowVector->at(row-1)->end(); ++itIn)
        {
            bitset<9> temp(0);
            list<int>::iterator it1;
            for(int i = 0; i<t; i++)
            {
                it1 = next(col_position.begin(), i);
                temp[i] = (*itIn)[(*it1)-1];
            }
            struct bits combination1;
            combination1.e = temp;
            colVariableCombinations.insert(combination1);
        }
        int sizeOfCombinationWithLessVariable = colVariableCombinations.size();
        col_position.push_back(col);
        //set<bitset<9>> colVariableCombinations1;
        const int t0 = col_position.size();
        for(vector<bitset<9>>::iterator itIn = rowVector->at(row-1)->begin() ; itIn != rowVector->at(row-1)->end(); ++itIn)
        {
            bitset<9> temp(0);
            list<int>::iterator it1;
            for(int i = 0; i<t0; i++)
            {
                it1 = next(col_position.begin(), i);
                temp[i] = (*itIn)[(*it1)-1];
            }
            struct bits combination2;
            combination2.e = temp;
            colVariableCombinations1.insert(combination2);
        }
        int sizeOfCombinationWithNextVariable = colVariableCombinations1.size();
        float f1 = (float)sizeOfCombinationWithNextVariable/sizeOfCombinationWithLessVariable;

/////F Value for column constraints
        for(list<fValue>::iterator it = fList.begin(); it != fList.end(); it++)
        {
            if((*it).cindex == col)
            {
                row_position.push_back((*it).rindex);
            }
        }
        //set<bitset<9>> rowVariableCombinations;
        const int t1 = row_position.size();
        for(vector<bitset<9>>::iterator itIn = columnVector->at(col-1)->begin() ; itIn != columnVector->at(col-1)->end(); ++itIn)
        {
            bitset<9> temp(0);
            list<int>::iterator it1;
            for(int i = 0; i<t1; i++)
            {
                it1 = next(row_position.begin(), i);
                temp[i] = (*itIn)[(*it1)-1];
            }
            struct bits combination3;
            combination3.e = temp;
            rowVariableCombinations.insert(combination3);
        }
        sizeOfCombinationWithLessVariable = rowVariableCombinations.size();
        row_position.push_back(row);
        //set<bitset<9>> rowVariableCombinations1;
        const int t2 = row_position.size();
        for(vector<bitset<9>>::iterator itIn = columnVector->at(col-1)->begin() ; itIn != columnVector->at(col-1)->end(); ++itIn)
        {
            bitset<9> temp(0);
            list<int>::iterator it1;
            for(int i = 0; i<t2; i++)
            {
                it1 = next(row_position.begin(), i);
                temp[i] = (*itIn)[(*it1)-1];
            }
            struct bits combination4;
            combination4.e = temp;
            rowVariableCombinations1.insert(combination4);
        }
        sizeOfCombinationWithNextVariable = rowVariableCombinations1.size();
        float f2 = (float)sizeOfCombinationWithNextVariable/sizeOfCombinationWithLessVariable;
        colVariableCombinations.clear();
        colVariableCombinations1.clear();
        rowVariableCombinations.clear();
        rowVariableCombinations1.clear();
        return (0.5*f1*f2);
    }
}


void Kakurasu :: searchalgorithm(vector<vector<bitset<9>>*> *temprow , vector<vector<bitset<9>>*> *tempcol, int **tempCM, int **tempFM, list<fValue> tempList)
{
    cout<<"\n\n-------------------Search Algorithm Begins---------------------------\n";


    int **tempCheckMatrix, **ftempMatrix;
    tempCheckMatrix = new int* [length+1];
    ftempMatrix = new int* [length+1];

    for(int i = 0; i<=length; i++)
    {
        tempCheckMatrix[i] = new int[length+1];
        ftempMatrix[i] = new int[length+1];
    }

    for(int i = 1; i<=length; i++)
    {
        for(int j = 1; j<=length; j++)
        {
            tempCheckMatrix[i][j] = tempCM[i][j];
            ftempMatrix[i][j] = tempFM[i][j];
        }
    }

    int unIdentify = unidentifiedVariables(tempCheckMatrix, ftempMatrix);

    cout<<"\n\n Inside Search Function : \n\n";
    printCheckMatrix(tempCM);
    printfMatrix(tempFM);


    fflush(stdout);

    unIdentify = unidentifiedVariables(tempCheckMatrix, ftempMatrix);


    while(unIdentify > 0)
    {
        vector<vector<bitset<9>>*> *tempRowAssignments, *tempRowAssignments1;
        vector<vector<bitset<9>>*> *tempColumnAssignments, *tempColumnAssignments1;


        tempRowAssignments = new vector<vector<bitset<9>>*>;
        tempColumnAssignments = new vector<vector<bitset<9>>*>;
        tempRowAssignments1 = new vector<vector<bitset<9>>*>;
        tempColumnAssignments1 = new vector<vector<bitset<9>>*>;
        for(int i = 0; i<=length - 1; i++)
        {
            tempRowAssignments->push_back((new vector<bitset<9>>));
            tempColumnAssignments->push_back((new vector<bitset<9>>));
            tempRowAssignments1->push_back((new vector<bitset<9>>));
            tempColumnAssignments1->push_back((new vector<bitset<9>>));
        }

        int count = 0;
        for(vector<vector<bitset<9>>*>::iterator it = temprow->begin() ; it != temprow->end(); ++it)
        {
            for(vector<bitset<9>>::iterator itIn = (*it)->begin() ; itIn != (*it)->end(); ++itIn)
            {
                tempRowAssignments->at(count)->push_back(*itIn);
                tempRowAssignments1->at(count)->push_back(*itIn);
            }
            count++;
        }

        count = 0;
        for(vector<vector<bitset<9>>*>::iterator it = tempcol->begin() ; it != tempcol->end(); ++it)
        {
            for(vector<bitset<9>>::iterator itIn = (*it)->begin() ; itIn != (*it)->end(); ++itIn)
            {
                tempColumnAssignments->at(count)->push_back(*itIn);
                tempColumnAssignments1->at(count)->push_back(*itIn);
            }
            count++;
        }

        list<fValue> fList;
        fList = tempList;

        cout<<"\n in Search function : fList is :\n";
        for(list<fValue>::iterator it = fList.begin(); it != fList.end(); it++)
        {
            cout<<"("<<(*it).rindex<<" , "<<(*it).cindex<<" , "<<(*it).scoreValue<<")\n";
        }

        fflush(stdout);

        struct fValue it1 = fList.front();
        int row_number = (it1).rindex;
        int col_number = (it1).cindex;
        cout<<"\n Row Number : "<<row_number<<"\t Column Number :"<<col_number<<"\n";
        fList.pop_front();
        fList.clear();

        cout<<"\n in Search function fList after clearing :\n";
        for(list<fValue>::iterator it = fList.begin(); it != fList.end(); it++)
        {
            if(fList.size() == 0)
            {
                cout<<"\n\n fList is empty because of clear fucntion  \n\n";
                break;
            }
            else
            {
                cout<<"("<<(*it).rindex<<" , "<<(*it).cindex<<" , "<<(*it).scoreValue<<")\n";
            }
        }

        if(tempCheckMatrix[row_number][col_number] == -1)
        {
            cout<<"\n\n\n\n\n--------------------------trying first undefined = 1----------------------------------------\n\n\n";
            tempCheckMatrix[row_number][col_number] = 1;
            ftempMatrix[row_number][col_number] = 1;
            cout<<"\n\n Check Matrix and F Matrix after assigning first undefined variable = 1 \n";
            printCheckMatrix(tempCheckMatrix);
            printfMatrix(ftempMatrix);
            for(vector<bitset<9>>::iterator itIn = tempRowAssignments->at(row_number-1)->begin() ; itIn != tempRowAssignments->at(row_number-1)->end(); ++itIn)
            {
                if((*itIn)[col_number-1]==0)
                {
                    cout<<"\n removed assignment from row  "<<row_number<<" is : "<<(*itIn);
                    itIn=tempRowAssignments->at(row_number-1)->erase(itIn);
                    itIn--;
                }
            }
            for(vector<bitset<9>>::iterator itIn = tempColumnAssignments->at(col_number-1)->begin() ; itIn != tempColumnAssignments->at(col_number-1)->end(); ++itIn)
            {
                if((*itIn)[row_number-1]==0)
                {
                    cout<<"\n removed assignment from Column "<<col_number<<" is : "<<(*itIn);
                    itIn=tempColumnAssignments->at(col_number-1)->erase(itIn);
                    itIn--;
                }
            }
            ACAlgorithm(tempRowAssignments, tempColumnAssignments, tempCheckMatrix);
            int flag1 = 0, flag2 = 0;
            for(int i = 0; i<length; i++)
            {
                if(tempRowAssignments->at(i)->size()==0)
                {
                    flag1 = 1;
                    break;
                }
            }
            for(int i = 0; i<length; i++)
            {
                if(tempColumnAssignments->at(i)->size()==0)
                {
                    flag2 = 1;
                    break;
                }
            }
            if(flag1 == 1 or flag2 == 1)
            {
                cout<<"\n \n\nSome of the constraints are not satisfied, so back tracking to the last assignments \n";
                cout<<"\n\n\n\n\n--------------------------trying first undefined = 0----------------------------------------\n\n\n";
                int count = 0;
                for(vector<vector<bitset<9>>*>::iterator it = tempRowAssignments1->begin() ; it != tempRowAssignments1->end(); ++it)
                {
                    cout<<"\nFor row : "<<++count<<"\n";
                    for(vector<bitset<9>>::iterator itIn = (*it)->begin() ; itIn != (*it)->end(); ++itIn)
                        cout<<*itIn<<"\t";
                }

                cout<<"\nFor all columns\n";
                count = 0;
                for(vector<vector<bitset<9>>*>::iterator it = tempColumnAssignments1->begin() ; it != tempColumnAssignments1->end(); ++it)
                {
                    cout<<"\nFor column : "<<++count<<"\n";
                    for(vector<bitset<9>>::iterator itIn = (*it)->begin() ; itIn != (*it)->end(); ++itIn)
                        cout<<*itIn<<"\t";
                }





                for(int i = 1; i<=length; i++)
                {
                    for(int j = 1; j<=length; j++)
                    {
                        tempCheckMatrix[i][j] = tempCM[i][j];
                        ftempMatrix[i][j] = tempFM[i][j];
                    }
                }
                unIdentify = unidentifiedVariables(tempCheckMatrix, ftempMatrix);
                tempCheckMatrix[row_number][col_number] = 0;
                ftempMatrix[row_number][col_number] = 1;
                for(vector<bitset<9>>::iterator itIn = tempRowAssignments1->at(row_number-1)->begin() ; itIn != tempRowAssignments1->at(row_number-1)->end(); ++itIn)
                {
                    if((*itIn)[col_number-1]==1)
                    {
                        cout<<"\n removed assignment from row  "<<row_number<<" is : "<<(*itIn);
                        itIn=tempRowAssignments1->at(row_number-1)->erase(itIn);
                        itIn--;
                    }
                }
                for(vector<bitset<9>>::iterator itIn = tempColumnAssignments1->at(col_number-1)->begin() ; itIn != tempColumnAssignments1->at(col_number-1)->end(); ++itIn)
                {
                    if((*itIn)[row_number-1]==1)
                    {
                        cout<<"\n removed assignment from Column "<<col_number<<" is : "<<(*itIn);
                        itIn=tempColumnAssignments1->at(col_number-1)->erase(itIn);
                        itIn--;
                    }
                }
                ACAlgorithm(tempRowAssignments1, tempColumnAssignments1, tempCheckMatrix);
                int flag3 = 0, flag4 = 0;
                for(int i = 0; i<length; i++)
                {
                    if(tempRowAssignments1->at(i)->size()==0)
                    {
                        flag3 = 1;
                        break;
                    }
                }
                for(int i = 0; i<length; i++)
                {
                    if(tempColumnAssignments1->at(i)->size()==0)
                    {
                        flag4 = 1;
                        break;
                    }
                }
                if(flag3 == 1 or flag4 == 1)
                {
                    cout<<"\n answer is not consistent please backtrack";
                    break;
                }
                else if(unidentifiedVariables(tempCheckMatrix, ftempMatrix) > 0)
                {
                    rowVector = tempRowAssignments1;
                    columnVector = tempColumnAssignments1;
                    unIdentify = unidentifiedVariables(tempCheckMatrix, ftempMatrix);
                    stm(fList,tempCheckMatrix, ftempMatrix);

                    cout<<"\n flag3,4 is not zero, unIdentify = "<<unIdentify<<"\n";
                    if(unIdentify > 0)
                    {
                        searchalgorithm(tempRowAssignments1, tempColumnAssignments1, tempCheckMatrix, ftempMatrix, fList);
                    }
                }

            }
            else if(unidentifiedVariables(tempCheckMatrix, ftempMatrix) > 0)
            {
                rowVector = tempRowAssignments;
                columnVector = tempColumnAssignments;
                unIdentify = unidentifiedVariables(tempCheckMatrix, ftempMatrix);
                stm(fList,tempCheckMatrix, ftempMatrix);

                cout<<"\n flag1,2 is not zero, unIdentify = "<<unIdentify<<"\n";
                if(unIdentify > 0)
                {
                    searchalgorithm(tempRowAssignments, tempColumnAssignments, tempCheckMatrix, ftempMatrix, fList);
                }
            }
        }
        cout<<"\n";
        if(solutionFound)
        {
            fflush(stdout);
            return;
        }
        else
        {
            cout<<"\n F and Check Matrices at the last of while loop : ";
            unIdentify = unidentifiedVariables(tempCheckMatrix, ftempMatrix);
            printCheckMatrix(tempCheckMatrix);
            printfMatrix(ftempMatrix);
            cout<<"\n unIdentify at the last in while loop = "<<unIdentify<<"\n";
        }
    }




    solutionFound = true;

    cout<<"\n\n Solution is : \n";

    cout<<"\n check Matrix : \n";
        for(int i =1; i<=length; i++)
        {
            cout<<"\n";
            for(int j = 1; j<=length; j++)
            {
                cout<<"\t"<<tempCheckMatrix[i][j];
            }
        }

    cout<<"\n";

    for(int i =1; i<=length; i++)
    {
        for(int j = 1; j<=length; j++)
        {
            if(tempCheckMatrix[i][j] == 1)
            {
                solMatrix[i][j] = true;
            }
            else
            {
                solMatrix[i][j] = false;
            }
        }
    }
    for(int i =1; i<=length; i++)
    {
        for(int j = 1; j<=length; j++)
        {
            checkMatrix[i][j] = tempCheckMatrix[i][j];
        }
    }

}



void Kakurasu :: sortIndex(int *a, int *b)
{
    int temp = 0;
      for(int i = 1; i<=length; i++)
      {
          for(int j = 1; j<length; j++)
          {
              if(a[b[j]]>a[b[j+1]])
              {
                  temp = b[j];
                  b[j] = b[j+1];
                  b[j+1] = temp;
              }
          }
      }
}

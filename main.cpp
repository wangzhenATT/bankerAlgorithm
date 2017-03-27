/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/24/2016 08:07:38 PM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  YOUR NAME (Mr wang), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>
using namespace std;

bool LittleOrEqual(const int *need, const int *work, int m)
{
    for(int i = 1; i <= m; i++)
    {
        if(need[i] > work[i])
            return false;
    }
    return true;
}
void Add(int *work, const int *allocation, int m)
{
    for(int i = 1; i <= m; i++)
        work[i] += allocation[i];
}
void Sub(int *des, const int *src, int m)
{
    for(int i = 1; i <= m; i++)
        des[i] -= src[i];
}
bool IsZero(const int *need, int m)
{
    for(int i = 1; i <= m; i++)
    {
        if(need[i] != 0)
            return false;
    }
    return true;
}
/*bool AllTrue(bool *finish, int n)
{
    for(int i = 1; i <= n; i++)
        if(finish[i] == false)
            return false;
    return true;
}*/
// BankerAlgrithm
bool SecurityDetection(int *&avaliable, int **allocation, int **&need, int m, int n)
{
    int i;
    int alltrue, find;
    
    int *work = new int[m+1];
    int *seq, end = 0;
    seq = new int[n];
    bool *finish;
    finish = new bool[n+1];
    for(i = 1; i <= n; i++)
        finish[i] = false;

    for(i = 1; i <= m; i++)    
        work[i] = avaliable[i];
    
    while(1)
    {
        find = 0;
        alltrue = 1;
        for(i = 1; i <= n; i++)
        {
            if(finish[i] == false)
            {
                if(IsZero(need[i], m))
                {
                    finish[i] = true;
                }
                else if(LittleOrEqual(need[i], work, m))
                {
                    for(int k = 1; k <= m; k++)
                        work[k] += allocation[i][k];
                    finish[i] = true;
                    find = 1;
                    seq[end++] = i;
                }
                else
                {
                    alltrue = 0;
                }
            }
        }
        if(alltrue == 1)
        {
            cout << "* Safe Status" << endl;
            cout << "* Safe Sequence : ";
            for(int k = 0; k < end; k++)
                cout << seq[k] << ' ';
            cout << endl;
            delete work;
            delete seq;
            delete finish;
            return true;
        }
        else if(find == 0)
        {
            cout << "* Unsafe Status" << endl;
            delete work;
            delete seq;
            delete finish;
            return false;
        }
    }

}
// Initial
void InitEnv(int *&avaliable, int **&max, int **&allocation, int **&need, int m, int n)
{
    int i;
    int j;
    try
    {
        avaliable = new int[m+1];
        max = new int*[n+1];
        allocation = new int*[n+1];
        need = new int*[n+1];
        for(i = 1; i <= n; i++)
        {
            max[i] = new int[m+1];
            allocation[i] = new int[m+1];
            need[i] = new int[m+1];
        }
    }
    catch(...)
    {
        cout << "Memory Error!" << endl;
        exit(0);
    }
    cout << "Initial avaliable number of " << m << " resources : " ;
    for(i = 1; i <= m; i++)
        cin >> avaliable[i];
    cout << "Initial maximum demand : " << endl;
    for(i = 1; i <= n; i++)
    {
        cout << "Process " << i << " : ";
        for(j = 1; j <= m; j++)
            cin >> max[i][j];
    }
    cout << "Initial allocation alreaday: " << endl;
    for(i = 1; i <= n; i++)
    {
        cout << "Process " << i << " : ";
        for(j = 1; j <= m; j++)
            cin >> allocation[i][j];
    }
    for(i = 1; i <= n; i++)
    {
        for(j = 1; j <= m; j++)
            need[i][j] = max[i][j] - allocation[i][j];
    }
    cout << "Initial over!" << endl;
}

// Print Status
void PrintStatus(int *avaliable, int **max, int **allocation, int **need, int m, int n)
{
    int i, j;
    cout << "Avaliable : ";
    for(i = 1; i <= m; i++)
        cout << avaliable[i] << ' ';
    cout << endl;
    //cout << "PROCESS    " << "    MAX    " << "    ALLOCATION    " << "    NEED    " << endl;
    for(i = 1; i <= n; i++)
    {
        cout << "PROCESS : " << i << "    ";
        cout << "MAX : ";
        for(j = 1; j <= m; j++)
            cout << max[i][j] <<' ';
        cout << "    ";
        cout << "ALLOCATION : ";
        for(j = 1; j <= m; j++)
            cout << allocation[i][j] << ' ';
        cout << "    ";
        cout << "NEED : ";
        for(j = 1; j <= m; j++)
            cout << need[i][j] << ' ';
        cout << endl;
    }
}
void Destroy(int *avaliable, int **max, int **allocation, int **need, int n)
{
    int i;
    delete avaliable;
    for(i = 0; i <= n; i++)
    {
        delete max[i];
        delete allocation[i];
        delete need[i];
    }
}
int main()
{
    int *avaliable;
    int **max, **allocation, **need;
    int m, n, i;
    int select;
    //bool torf;
    cout << "The kinds number of resource : ";    cin >> m;
    cout << "The number of process : ";     cin >> n;
    InitEnv(avaliable, max, allocation, need, m, n);
    if(SecurityDetection(avaliable, allocation, need, m, n))
        PrintStatus(avaliable, max, allocation, need, m, n);
    else 
       exit(1); 
    cout << "===========================================================================" << endl;
    cout << "Option 1 : Apply resource" << endl;
    cout << "Option 0 : exit" << endl;
    while(1)
    {
        int request[m+1];
        int proc;
        cout << "option : ";    cin >> select;
        if(select == 1)
        {
            cout << "Process : ";   cin >> proc;
            while(proc > n || proc < 0)
            {
                cout << "no process " << proc << endl;
                cout << "Process : ";   cin >> proc;
            }
            cout << m << " request resources : ";
            for(i = 1; i <=m; i++)
                cin >> request[i];

            if(LittleOrEqual(request, need[proc], m) && LittleOrEqual(request, avaliable, m))
            {
                Add(allocation[proc], request, m);
                Sub(need[proc], request, m);
                Sub(avaliable, request, m);
                if(IsZero(need[proc], m))
                {
                    cout << "Processing " << proc << " done" << endl;
                    Add(avaliable, allocation[proc], m);
                    Sub(allocation[proc], allocation[proc], m);
                }
                if(SecurityDetection(avaliable, allocation, need, m, n))
                {
                    PrintStatus(avaliable, max, allocation, need, m, n);
                }
                else
                {   
                    //cout << "*Error Status" << endl;
                    PrintStatus(avaliable, max, allocation, need, m, n);
                    cout << "Will recover a little......" << endl;
                    Sub(allocation[proc], request, m);
                    Add(need[proc], request, m);
                    Add(avaliable, request, m);
                    cout << "Recover Status :" << endl;
                    PrintStatus(avaliable, max, allocation, need, m, n);
                }
            }
            else
            {
                cout << "Request resource too much to allocate" << endl;
            }
        }
        else if(select == 0)
        {
            Destroy(avaliable, max, allocation, need, n);
            exit(0);
        }
        else
        {
            cout << "option error" << endl;
        }
    }
}

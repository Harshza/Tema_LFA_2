#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstring>
#include <algorithm>

using namespace std;
ifstream fin("Cerinta2.in");

int m, m2, n, n2, q0, q02, l, k, k2;
unordered_map<char, vector<int>> M[302], Mvect[302];
unordered_map<char, int>M2[302];
char alf[302], alf2[302];
bool F[302], F2[302];
vector<vector<int>> stari;



void NFA_to_DFA()
{
    m2 = m;
    q02 = 0;
    n2 = 1;
    strcpy(alf2, alf);
    stari.push_back({q0});
    for(int i = 0; i < m2; i++)
    {
        char a = alf2[i];
        Mvect[0][a] = M[q0][a];
        if(!Mvect[0][a].empty())
        {
            sort(Mvect[0][a].begin(), Mvect[0][a].end());
            bool g = false;
            for(int j = 0; j < n2 && !g; j++)
                if(Mvect[0][a] == stari[i])
                    g = true;
            if(!g)
            {
                n2++;
                stari.push_back(Mvect[0][a]);
            }
        }
    }

    for(int i = 1; i < n2; i++)
    {
        for(int j = 0; j < m2; j++)
        {
            char a = alf2[j];
            bool viz[302] = {false};

            for(int z : stari[i])
            {
                for(int y : M[z][a])
                    if(!viz[y])
                    {
                        Mvect[i][a].push_back(y);
                        viz[y] = true;
                    }
            }

            if(!Mvect[i][a].empty())
            {
                sort(Mvect[i][a].begin(), Mvect[i][a].end());
                bool g = false;
                for(int t = 0; t < n2 && !g; t++)
                    if(Mvect[i][a] == stari[t])
                        g = true;
                if(!g)
                {
                    n2++;
                    stari.push_back(Mvect[i][a]);
                }
            }
        }
    }

    for(int i = 0; i < n2; i++)
    {
        for(int j : stari[i])
            if(F[j])
            {
                F2[i] = true;
                k2++;
                break;
            }
    }

    for(int i = 0; i < n2; i++)
    {
        for(int j = 0; j < m2; j++)
        {
            char a = alf2[j];
            if(!Mvect[i][a].empty())
            {
                for(int y = 0; y < n2; y++)
                    if(Mvect[i][a] == stari[y])
                    {
                        M2[i][a] = y;
                        break;
                    }
            }
            else
                M2[i][a] = -1;
        }
    }

}

int main()
{
    int stare_finala;
    fin >> n;
    fin >> m;
    for(int i = 0; i < m; i++)
        fin >> alf[i];

    alf[m] = '\0';

    fin >> q0;

    fin >> k;

    for(int i = 0; i < k; i++)
    {
        fin >> stare_finala;
        F[stare_finala] = true;
    }

    fin >> l;
    for(int i = 1; i <= l; i++)
    {
        int x, y;
        char a;
        fin >> x >> a >> y;
        M[x][a].push_back(y);
    }

    NFA_to_DFA();

    cout << n2 << '\n' << m2 << '\n';

    for(int i = 0; i < m2; i++)
        cout << alf2[i] << ' ';

    cout << '\n' << q02 << '\n' << k2 << '\n';
    for(int i = 0; i < n2; i++)
        if(F2[i])
            cout << i << ' ';
    
    cout << '\n';

    for(int t = 0; t < n2; t++)
    {
        for(int i = 0; i < m2; i++)
        {
            char a = alf2[i];
            if(M2[t][a] != -1)
                cout << t << ' ' << a << ' ' << M2[t][a] << "\n";
        }
    }

    return 0;
}
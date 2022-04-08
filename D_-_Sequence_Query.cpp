#include "bits/stdc++.h"
#include <time.h>
#include <stdlib.h>
using namespace std;
struct DSU
{
    vector<int> parent, sze;
    void build(int n)
    {
        parent.resize(n, 0), sze.resize(n, -1);
        for (int k = 0; k < n; k++)
            parent[k] = k, sze[k] = 1;
    }
    int find(int v)
    {
        if (parent[v] == v)
            return v;
        else
            return parent[v] = find(parent[v]);
    }
    void unite(int a, int b)
    {
        a = find(a), b = find(b);
        if (a != b)
        {
            if (sze[a] < sze[b])
                swap(a, b);
            parent[b] = a, sze[a] += sze[b];
        }
    }
} dsu;

int32_t main()
{
    cin.tie(0)->sync_with_stdio(0);
    srand(time(0));
    auto AssignWeight = [&]() -> int
    {
        return rand() % 150;
    };
    auto printmaze = [](auto &m, int n) -> void
    {
        vector<vector<char>> p(2 * n + 1, vector<char>(2 * n + 1,' '));
        
        for(int i=0;i<n;i++)
        {
            for(int j = 0;j<n;j++) cout<<m[i][j];
            cout<<"\n";
        }
        cout<<"\n\n";
        for (int i = 0; i < 2*n+1; i+=2)
        {
            for (int j = 0; j < 2*n+1; j++)
            {
                if(j%2) p[i][j]='-';
                else p[i][j]='+';  
            }
        }
        for(int i=1;i<2*n+1;i+=2)
        {
            for(int j=0;j<2*n+1;j+=2) p[i][j]='|';
        }
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(i>0 && m[i-1][j]=='.' && m[i][j]=='.')
                {
                    p[2*i][2*j+1] = ' ';
                }
                if(j>0 && m[i][j-1]=='.' && m[i][j]=='.')
                {
                    p[2*i+1][2*j] = ' ';
                }
            }
        }
        for(int i=0;i<2*n+1;i++)
        {
            for(int j = 0;j<2*n+1;j++) cout<<p[i][j];
            cout<<"\n";
        }
    };
    set<array<int, 3>> edges, mst;
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int f = (i - 1) * n;
        for (int j = f + 1; j <= f + n; j++)
        {
            if (j < f + n)
            {
                int getWeight = AssignWeight();
                edges.insert({getWeight, j, j + 1});
            }
            if (j + n <= n * n)
            {

                int getWeight = AssignWeight();
                edges.insert({getWeight, j, j + n});
            }
        }
    }
    dsu.build(n * n + 1);
    for (auto [w, u, v] : edges)
    {
        if (dsu.find(u) != dsu.find(v))
        {
            dsu.unite(u, v);
            mst.insert({w, u, v});
        }
    }
    for (auto x : mst)
        edges.erase(x);
    set<pair<int, int>> cells;
    for (auto [w, u, v] : edges)
    {
        cells.insert({u, v});
    }
    vector<vector<char>> maze(2 * n + 1, vector<char>(2 * n + 1));
    for (int i = 0; i < 2 * n + 1; i++)
    {
        maze[0][i] = 'X';
        maze[2 * n][i] = 'X';
        maze[i][0] = 'X';
        maze[i][2 * n] = 'X';
    }
    for (int i = 1; i < 2 * n; i++)
    {
        for (int j = 1; j < 2 * n; j++)
        {
            maze[j][i] = '.';
        }
    }
    int cnt = 0;
    for (auto [u, v] : cells)
    {
        int i = (u / n) * 2 + 1, j = (u % n) ? (u % n) * 2 - 1 : 2 * n - 2;
        if (v == u + 1)
        {
            maze[i][j + 1] = 'X';
            maze[i - 1][j + 1] = 'X';
        }
        else
        {
            maze[i + 1][j] = 'X';
            maze[i + 1][j + 1] = 'X';
        }
    }
    printmaze(maze, 2 * n + 1);
}
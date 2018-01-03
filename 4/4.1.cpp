#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class Graph
{
public:
    int Edge;
    int Vertex;
    vector<vector<int>> adj;

    Graph(int V)
    {
        Vertex = V;
        Edge = 0;
        for (int v = 0; v < Vertex; v++)
        {
            adj.push_back(vector<int>());
        }
    }

    Graph(istream &in)
    {
        int i, v, w, e;
        in >> Vertex;
        in >> e;
        Edge = 0;
        for (int v = 0; v < Vertex; v++)
        {
            adj.push_back(vector<int>());
        }
        for (i = 0; i < e; i++)
        {
            in >> v >> w;
            addEdge(v, w);
        }
    }

    void addEdge(int v, int w)
    {
        adj[v].push_back(w);
        adj[w].push_back(v);
        Edge++;
    }
};

class UF
{
public:
    vector<int> id;
    vector<int> size;
    int count;

    UF(int n)
    {
        count = n;
        for (int i = 0; i < n; i++)
        {
            id.push_back(i);
            size.push_back(1);
        }
    }

    UF(Graph g) : UF(g.Vertex)
    {
        for (int i = 0; i < g.adj.size(); i++)
        {
            for (auto j = g.adj[i].begin(); j != g.adj[i].end(); j++)
            {
                u(i, *j);
            }
        }
    }

    bool connected(int v, int w)
    {return find(v) == find(w);}

    int find(int p)
    {
        while (p != id[p])
            p = id[p];
        return p;
    }

    void u(int v, int w)
    {
        int i = find(v);
        int j = find(w);
        if (i != j)
        {
            if (size[i] < size[j])
            {
                id[i] = j;
                size[j] += size[i];
            }
            else
            {
                id[j] = i;
                size[i] += size[j];
            }
            count--;
        }
    }
};

int main()
{
    ifstream input("largeG.txt");
    if (!input.is_open())
        return 0;
    Graph g(input);
    UF u(g);
    // int v, w;
    // while (1)
    // {
    //     cin >> v >> w;
    //     cout << boolalpha << u.connected(v, w) << endl;
    // }
}
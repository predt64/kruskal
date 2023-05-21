// C++ program for Kruskal's algorithm to find Minimum
// Spanning Tree of a given connected, undirected and
// weighted graph

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

typedef pair<int, int> iPair;

struct Graph
{
	int V;
	vector< pair<int, iPair> > edges;
	Graph(int V)
	{
		this->V = V;
	}
	void addEdge(int u, int v, int w)
	{
		edges.push_back({ w, {u, v} });
	}
	int kruskalMST();
};

struct DisjointSets
{
	int* parent, * rnk;
	int n;

	DisjointSets(int n)
	{
		this->n = n;
		parent = new int[n];
		rnk = new int[n];

		for (int i = 0; i < n; i++)
		{
			rnk[i] = 0;

			parent[i] = i;
		}
	}

	int find(int u)
	{
		if (u != parent[u])
			parent[u] = find(parent[u]);
		return parent[u];
	}

	void merge(int x, int y)
	{
		x = find(x), y = find(y);

		if (rnk[x] > rnk[y])
			parent[y] = x;
		else
			parent[x] = y;

		if (rnk[x] == rnk[y])
			rnk[y]++;
	}
};


int Graph::kruskalMST()
{
	int mst_wt = 0;

	sort(edges.begin(), edges.end());

	DisjointSets ds(V);

	vector< pair<int, iPair> >::iterator it;
	for (it = edges.begin(); it != edges.end(); it++)
	{
		int u = it->second.first;
		int v = it->second.second;

		int set_u = ds.find(u);
		int set_v = ds.find(v);

		
		if (set_u != set_v)
		{			
			cout << u << " - " << v << endl;

			mst_wt += it->first;

			ds.merge(set_u, set_v);
		}
	}

	return mst_wt;
}


int main()
{
	setlocale(LC_ALL, "rus");
	string str;
	string stroka;
	ifstream file("qwe.txt");
	int counter = 0;
	while (file.peek() != '\n')
	{
		file >> str;
		stroka += str;
		counter++;
	}
	Graph g(counter);

	for (int i = 0; i < counter; i++)
	{
		for (int j = 0; j < counter; j++)
		{
			int n;
			file>>n;
			if(n!=0)
				g.addEdge(i, j, n);
		}
	}
	cout << "рёбра: \n";
	int mst_wt = g.kruskalMST();

	cout << "\nсуммарный вес: " << mst_wt;

	return 0;
}
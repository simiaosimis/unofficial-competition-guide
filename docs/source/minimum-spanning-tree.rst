Minimum Spanning Tree
=====================

Kruskal's Algorithm
-------------------

.. note::

    Tested on: UVA11631, URI1152, URI1764

.. warning::

    You need the :doc:`union-find-disjoint-set` code for this algorithm

.. code-block:: cpp

    #include <vector>     // vector
    #include <algorithm>  // sort
    #include <utility>    // pair

    using namespace std;

    // Graph as an edge list with a cost
    // the elements are (weight, (node1, node2))
    vector< pair<int, pair<int, int> > > G;

    int kruskal_mst_cost(int N)
    {
        /*
            Complexity: O(E log V)
        */

        // !!! If the edges' weight lies in a small range, you can use counting
        // sort to speed up the process
        sort(G.begin(), G.end());

        int cost = 0;
        UFDS ufds(N);

        for(auto edge: G)
        {
            if(!ufds.same_set(edge.second.first, edge.second.second))
            {
                cost += edge.first;
                ufds.union_set(edge.second.first, edge.second.second);
            }
        }

        return cost;
    }


Prim's Algorithm
----------------

.. note::

    Tested on: UVA11747, URI1552

.. code-block:: cpp

    #include <queue>      // priority_queue
    #include <vector>     // vector
    #include <utility>    // pair
    #include <functional> // greater
    #include <cstring>    // memset

    using namespace std;

    #define MAX 510

    using ii = pair<int, int>;

    vector<ii> G[MAX]; // G of (weight, node)
    bool visited[MAX]; // memset to false

    int prim_mst_cost(int n_nodes)
    {
        /*
            Greedly picks the minimun edges that connects all nodes, forming the
            spanning tree

            Complexity: O(E log(V))
        */

        memset(visited, false, sizeof visited);

        priority_queue< ii, vector<ii>, greater<ii> > less_cost;

        int edges_taken_count = 0;
        int cost = 0;

        for(int vertex = 0; vertex < n_nodes; ++vertex)
        {
            if(visited[vertex]) continue;

            visited[vertex] = true;

            for(auto adjacent: G[vertex])
                if(!visited[adjacent.second])
                    // push all edges connected to the first node to the heap
                    less_cost.push(adjacent);

            while(!less_cost.empty())
            {
                auto node = less_cost.top(); // pops an edge with minimum cost
                less_cost.pop();

                // If one node of that edge was not visited yet, it is a valid edge
                if(!visited[node.second])
                {
                    visited[node.second] = true;

                    edges_taken_count++;
                    cost += node.first;

                    // n_nodes - 1 is the number of minimun edges that a graph
                    // needs to be connected
                    if(edges_taken_count == n_nodes - 1)
                        return cost;

                    for(auto adjacent: G[node.second])
                        if(!visited[adjacent.second])
                            less_cost.push(adjacent);
                }
            }
        }

        return cost;
    }

.. toctree::
   :maxdepth: 2

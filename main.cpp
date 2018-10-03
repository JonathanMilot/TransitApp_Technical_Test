#include <iostream>

#include "graph.h"

using namespace std;

void printCycle(vector<size_t>& cycle, Graph& g) {
    cout << "\""; 
    for(auto n : cycle) {
        cout << n << "->";
    }
    cout << "\""; 
    cout << endl; 
    cout << "Weight : " << g.getWeight(cycle) << endl;
    cout << endl; 
}

int main() {
    cout << "== Initialisation ==" << endl;

    Graph g(15);

    g.addEdge(0, 0, 5); 
    g.addEdge(1, 2, 1);
    g.addEdge(2, 3, 1); 
    g.addEdge(3, 4, 1);
    g.addEdge(3, 4, 5);
    g.addEdge(3, 4, 10);
    g.addEdge(3, 4, 1);
    g.addEdge(3, 5, 1); 
    g.addEdge(4, 9, 1); 
    g.addEdge(4, 6, 1); 
    g.addEdge(5, 6, -50);
    g.addEdge(5, 6, 50);
    g.addEdge(6, 7, 1); 
    g.addEdge(7, 1, 1); 

    g.addEdge(8, 9, 1); 
    g.addEdge(9, 10, 1); 

    cout << "== Invalid operation ==" << endl;
    g.addEdge(20, 5, -3); 
    g.addEdge(2, 15, 6); 
    g.addEdge(1, 5, -300); 
    g.addEdge(1, 5, 500); 


    cout << "== End ==" << endl << endl;

    vector<size_t> cycle = g.getCycle(0);
    cout << "Cycle from 0 :" << endl; 
    printCycle(cycle, g); 

    cycle = g.getCycle(2);
    cout << "Cycle from 2 :" << endl; 
    printCycle(cycle, g); 

    cout << "Negative cycle :" << endl; 
    cycle = g.getNegativeWeightCycle();
    printCycle(cycle, g); 

    cout << "No cycle from 8:" << endl; 
    cycle = g.getCycle(8);
    printCycle(cycle, g); 

    cout << "Max weight between 3 and 4" << endl; 
    cout << "Max weight:" << g.getMaxWeight(3, 4) << endl;

    return 0;
}
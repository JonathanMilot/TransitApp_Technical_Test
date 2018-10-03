
/**
 For each questions, unit test would be appreciated. No hard deadline but please send it within the next week. Code must be given in a public git repository. This test can be relatively long and we don't want to take too much of your time so please don't put more than 4 or 5 hours on it. It's ok to not answer every questions.
 
1. Create a C++ class for representing a directed graph with the following properties:
- each node is represented by a non-negative integer
- each directed edge has an integer weight in the range -100..100
- for each directed edge a → b, the difference between a and b is in the range -32000..32000
- loops (an edge from a node to itself) and parallel edges (multiple edges from the same two nodes) are allowed

The class must follow this api: 
*/

#include <vector>

class Graph {
    public:
        Graph(size_t numberOfNodes);
    
        void addEdge(size_t a, size_t b, int weight);
        float getMinWeight(size_t a, size_t b) const;
        float getMaxWeight(size_t a, size_t b) const;

        float getWeight(const std::vector<size_t>& nodes) const; 
        std::vector<size_t> getCycle(size_t startNode) const; 
        std::vector<size_t> getNegativeWeightCycle() const;

    private:
        // add whatever private methods or members you may need here

        struct Edge{
            int m_weight; 
            size_t m_toNodeId; 

            Edge(size_t b, int weight) : m_toNodeId(b), m_weight(weight) {}
        }; 

        struct Node{
            size_t m_id; 
            std::vector<Edge> m_edges; 

            Node(size_t id) : m_id(id) {}
        };

        std::vector<Node> m_nodes; 

        bool isValidNodeIndex(size_t n) const; 
        bool findCycle(size_t currentNodeId, bool visited[], std::vector<size_t>& cycle, size_t startNode) const;
        bool findCycleNegative(size_t currentNodeId, bool visited[], std::vector<size_t>& cycle, size_t startNode) const;
};

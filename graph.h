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

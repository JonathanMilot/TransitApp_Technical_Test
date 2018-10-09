#include <iostream>
#include <limits>

#include "graph.h"

Graph::Graph(size_t numberOfNodes){

    // Since the exact finale size of nodes is known, 
    // it is directly reserve to avoid reallocation. 
    m_nodes.reserve(numberOfNodes); 

    for(size_t i = 0; i < numberOfNodes; ++i){
        Node n(i); 
        m_nodes.push_back(n);
    }

    std::cout << "Created graph with " << m_nodes.size() << " nodes. " << std::endl; 
}

/**
* Helper function for checking node index validity
*/
bool Graph::isValidNodeIndex(size_t n) const{
    if(n >= m_nodes.size()){
        std::cerr << "Graph::isValidNodeIndex - Trying to access an invalid node : " << n << std::endl; 
        return false; 
    }
    return true; 
} 

/**
* Adds a directed edge a → b.
*/
void Graph::addEdge(size_t a, size_t b, int weight) {

    if(!isValidNodeIndex(a)
        || !isValidNodeIndex(b)) {
            return; 
    }

    if(weight > 100 
        || weight < -100) {
        std::cerr << "Graph::addEdge - Trying to add an edge with an invalid weight : " << weight << "." << std::endl; 
        std::cerr << "Should be in the range -100..100." << std::endl;
        return; 
    }

    Edge e(b, weight); 
    m_nodes[a].m_edges.push_back(e); 
    std::cout << "Added edge " << a << " -> " << b << std::endl; 
}

/**
* Returns the minimum weight of a directed edge a → b between both nodes.
* returns ∞ if no such edge exists
*/
float Graph::getMinWeight(size_t a, size_t b) const {
    float minWeight = std::numeric_limits<float>::infinity(); 

    const Node& n = m_nodes[a]; 

    for(const Edge& e : n.m_edges) {
        if(e.m_weight < minWeight) {
            minWeight = e.m_weight; 
        }
    }

    return minWeight; 
}

/**
* Returns the maximum weight of a directed edge a → b between both nodes.
* returns ∞ if no such edge exists
*/
float Graph::getMaxWeight(size_t a, size_t b) const {
    float maxWeight = std::numeric_limits<float>::lowest(); 

    const Node& n = m_nodes[a]; 

    for(const Edge& e : n.m_edges) {
        if(e.m_weight > maxWeight) {
            maxWeight = e.m_weight; 
        }
    }

    return maxWeight; 
}

/**
 * Helper recursive function for finding cycle.
 */ 

bool Graph::findCycle(size_t currentNodeId, bool visited[], std::vector<size_t>& cycle, size_t startNode) const { 
    if(!visited[currentNodeId]) { 

        // Mark the current node as visited and part of the current cycle 
        visited[currentNodeId] = true; 
        cycle.push_back(currentNodeId); 

        // Recursion on all the edges
        for(const Edge& e : m_nodes[currentNodeId].m_edges) { 
            if (e.m_toNodeId == startNode) {
                // Cycle found !
                return true; 
            }
            else if (!visited[e.m_toNodeId] 
                      && findCycle(e.m_toNodeId, visited, cycle, startNode) ) {
                // Continue to explore graph
                return true; 
            }
        } 
    } 
    cycle.pop_back(); // remove the node from cycle 
    return false; 
} 

/**
* Returns the list of nodes in a cycle that starts at the given node.
* The nodes are in the order that they appear in the cycle, starting with startNode and ending with the one immediately preceding it.
* If the node is not part of a cycle, the method returns an empty vector.
*/
std::vector<size_t> Graph::getCycle(size_t startNode) const {
    std::vector<size_t> cycle; 

    if(!isValidNodeIndex(startNode)) {
        return cycle; 
    }

    bool visited[m_nodes.size()]; 

    for(size_t i = 0; i < m_nodes.size(); ++i) { 
        visited[i] = false; 
    } 

    findCycle(startNode, visited, cycle, startNode);
    return cycle; 
}


/**
* Checks that a given list of nodes forms a cycle and returns its total weight.
* The weight of a cycle is the sum of the minimum weights of its edges.
* This method returns ∞ if the list of nodes does not form a cycle.
*/
float Graph::getWeight(const std::vector<size_t>& nodes) const {
    float totalWeight = 0; 

    for(size_t i = 0; i < nodes.size() - 1; ++i){
        float minWeight = getMinWeight(nodes[i], nodes[i+1]); 
        if(minWeight == std::numeric_limits<float>::infinity()){
            return minWeight; 
        } else {
            totalWeight += minWeight; 
        }
    }

    // Handle last edge of the cycle 
    float minWeight = getMinWeight(nodes.back(), nodes[0]); 
    if(minWeight == std::numeric_limits<float>::infinity()){
        return minWeight; 
    } else {
        totalWeight += minWeight; 
    }

    return totalWeight; 
}

/**
 * Helper recursive function for finding negative cycle.
 */ 
bool Graph::findCycleNegative(size_t currentNodeId, bool visited[], std::vector<size_t>& cycle, size_t startNode) const { 
    if(!visited[currentNodeId]) { 

        // Mark the current node as visited and part of the current cycle 
        visited[currentNodeId] = true; 
        cycle.push_back(currentNodeId);  

        // Recursion on all the edges
        for(const Edge& e : m_nodes[currentNodeId].m_edges) { 
            if ( !visited[e.m_toNodeId] 
                && findCycleNegative(e.m_toNodeId, visited, cycle, startNode)) {
                return true; 
            }
            else if (e.m_toNodeId == startNode
                    && getWeight(cycle) < 0) {
                return true; 
            }
        } 
  
    } 
    
    visited[currentNodeId] = false; 
    cycle.pop_back(); // remove the vertex from recursion stack 
    return false; 
} 

/**
* Returns a cycle with negative weight, if it exists in this graph.
* If no such cycle exists, this method returns an empty vector.
*/
std::vector<size_t> Graph::getNegativeWeightCycle() const {
    std::vector<size_t> cycle; 

    for(const Node& n : m_nodes) {
        size_t startNode = n.m_id; 

        if(!isValidNodeIndex(startNode)) {
            return cycle; 
        }

        cycle.clear(); 

        bool visited[m_nodes.size()]; 
        for(size_t i = 0; i < m_nodes.size(); ++i) { 
            visited[i] = false; 
        } 

        findCycleNegative(startNode, visited, cycle, startNode);

        // Be sure to actually have a cycle before returning. 
        // Else, try with an other node. 
        if(cycle.size() > 0) {
            return cycle; 
        }
    }

    return cycle; 
}
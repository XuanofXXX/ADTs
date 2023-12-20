#ifndef GRAPH_CPP
#define GRAPH_CPP

#include "DataStructure/src/LinkedList.cpp"

enum GraphInfo { DIRECTED, UNDIRECTED };

struct ArcInfo {
  /**
   * @brief The info of one node
   *
   */
  int weight;
  int ID;
  ArcInfo(int weight, int ID) : weight(weight), ID(ID) {}
};

struct ArcNode {
  int adjvex;
  ArcNode *next;
  ArcInfo *info;
  ArcNode(int adjvex) : adjvex(adjvex), next(nullptr) {}
};

struct VInfo {
  /**
   * @brief The info of one node
   *
   */
  int ID;
  VInfo(int ID) : ID(ID) {}
};

struct VNode {
  VInfo *info;
  ArcNode *arc;
};

class GraphMatrix {
private:
  /**
   * @brief We assume that the graph is directed.
   * TODO: support the undirected graph
   *
   */
  GraphInfo kind;
  int numVertices;
  int numArcs;
  LinkList<VNode*> *adjacencyList;
  LinkList<VNode*> *reverseAdjacencyList;

public:
  GraphMatrix() {}
  ~GraphMatrix() {
    delete adjacencyList;
    delete reverseAdjacencyList;
  }

  void addVertices(VInfo* node) {
    /**
     * @brief Add a node to the graph
     * TODO: complete this and addArc
     * 
     * @param node
     */
    VNode *newNode = new VNode();
    if (newNode == nullptr) {
      throw "Failed to allocate memory";
    }
    newNode->info = node;
    newNode->arc = nullptr;
    adjacencyList->append(newNode);
    numVertices++;
  }
};

class GraphList {
private:
  int numVertices;

public:
};

#endif

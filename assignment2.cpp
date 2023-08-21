// #include "common.h"
#include <stack>
#include <queue>
#ifndef _common_h_
#include "common.h"
#define _common_h_
#endif
#define INF 1000000000

int readFile(Graph &myGraph, char *filename)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL) // File not found or cannot read
        return 0;

    // Read the graph type and operation type from the file
    fscanf(f, "%d", &myGraph.nGraphType);
    fscanf(f, "%d", &myGraph.nOperation);

    // Read the number of vertices in the graph
    fscanf(f, "%d", &myGraph.nVertexNum);
    // Read the names of the vertices and populate the graph structure
    char strName[MAX_VERTEX];
    for (int i = 0; i < myGraph.nVertexNum; i++)
    {
        fscanf(f, "%s", strName);
        strcpy(myGraph.graph[i].vertex.strName, strName);
    }
    // Read the starting vertex for depth-first traversal
    char startVertexName[MAX_VERTEX];
    fscanf(f, "%s", startVertexName);
    for (int i = 0; i < myGraph.nVertexNum; i++)
    {
        if (strcmp(myGraph.graph[i].vertex.strName, startVertexName) == 0)
        {
            myGraph.startVertex = myGraph.graph[i].vertex;
            break;
        }
    }
    fscanf(f, "%d", &myGraph.nOrder);
    // Read the adjacency matrix and update the graph structure
    for (int i = 0; i < myGraph.nVertexNum; i++)
    {
        VertexType *temp = myGraph.graph[i].adjVertex;

        for (int j = 0; j < myGraph.nVertexNum; j++)
        {
            int edgeWeight;
            fscanf(f, "%d", &edgeWeight);
            if (edgeWeight != 0)
            {
                VertexType *tempHea = NULL;
                VertexType *newAdjVertex = new VertexType;
                strcpy(newAdjVertex->strName, myGraph.graph[j].vertex.strName);
                newAdjVertex->weight = edgeWeight;
                if (temp == NULL)
                {
                    myGraph.graph[i].adjVertex = newAdjVertex;
                    temp = newAdjVertex;
                }
                else
                {
                    temp->next = newAdjVertex;
                    temp = temp->next;
                }
                myGraph.graph[i].outdegree++;
                myGraph.graph[j].indegree++;
            }
        }
    }
    fclose(f);
    // Todo
    return 1;
}

string depthFirstTraversal(Graph &myGraph, VertexType startVertex)
{
    string result = "";
    stack<int> st;
    int count = 0;

    int startIndex = -1;
    for (int i = 0; i < myGraph.nVertexNum; i++)
    {
        if (strcmp(myGraph.graph[i].vertex.strName, startVertex.strName) == 0)
        {
            startIndex = i;
            break;
        }
    }

    if (startIndex == -1)
    {
        return result;
    }

    bool visited[MAX_VERTEX] = {false};
    visited[startIndex] = true;

    st.push(startIndex);

    while (!st.empty())
    {
        int currentIndex = st.top();
        st.pop();
        result += myGraph.graph[currentIndex].vertex.strName;
        count++;
        if (count != myGraph.nVertexNum)
            result += " ";

        // Collect adjacent vertices
        int adjIndices[MAX_VERTEX];
        int adjCount = 0;
        VertexType *adjVertex = myGraph.graph[currentIndex].adjVertex;

        while (adjVertex != NULL)
        {
            int adjIndex = -1;
            for (int i = 0; i < myGraph.nVertexNum; i++)
            {
                if (strcmp(myGraph.graph[i].vertex.strName, adjVertex->strName) == 0)
                {
                    adjIndex = i;
                    break;
                }
            }

            if (adjIndex != -1 && !visited[adjIndex])
            {
                adjIndices[adjCount++] = adjIndex;
                visited[adjIndex] = true;
            }
            adjVertex = adjVertex->next;
        }

        // Sort adjacent vertices based on nOrder
        for (int i = 0; i < adjCount - 1; i++)
        {
            for (int j = i + 1; j < adjCount; j++)
            {
                if ((myGraph.nOrder == INCREASINGORDER && strcmp(myGraph.graph[adjIndices[i]].vertex.strName, myGraph.graph[adjIndices[j]].vertex.strName) > 0) ||
                    (myGraph.nOrder == DECREASINGORDER && strcmp(myGraph.graph[adjIndices[i]].vertex.strName, myGraph.graph[adjIndices[j]].vertex.strName) < 0))
                {
                    int temp = adjIndices[i];
                    adjIndices[i] = adjIndices[j];
                    adjIndices[j] = temp;
                }
            }
        }
        // Push sorted adjacent vertices onto the stack
        for (int i = 0; i < adjCount; i++)
        {
            st.push(adjIndices[i]);
        }
    }

    return result;
}
string breadthFirstTraversal(Graph &myGraph, VertexType startVertex)
{
    string result = "";
    queue<int> q;
    int count = 0;
    int startIndex = -1;
    for (int i = 0; i < myGraph.nVertexNum; i++)

    {
        if (strcmp(myGraph.graph[i].vertex.strName, startVertex.strName) == 0)
        {
            startIndex = i;
            break;
        }
    }
    if (startIndex == -1)
    {
        return result;
    }
    bool visited[MAX_VERTEX] = {false};
    visited[startIndex] = true;

    q.push(startIndex);

    while (!q.empty())
    {
        int currentIndex = q.front();
        q.pop();
        result += myGraph.graph[currentIndex].vertex.strName;
        count++;
        if (count != myGraph.nVertexNum)
            result += " ";

        // Collect adjacent vertices
        int adjIndices[MAX_VERTEX];
        int adjCount = 0;
        VertexType *adjVertex = myGraph.graph[currentIndex].adjVertex;

        while (adjVertex != NULL)
        {
            int adjIndex = -1;
            for (int i = 0; i < myGraph.nVertexNum; i++)
            {
                if (strcmp(myGraph.graph[i].vertex.strName, adjVertex->strName) == 0)
                {
                    adjIndex = i;
                    break;
                }
            }

            if (adjIndex != -1 && !visited[adjIndex])
            {
                adjIndices[adjCount++] = adjIndex;
                visited[adjIndex] = true;
            }
            adjVertex = adjVertex->next;
        }

        // Sort adjacent vertices based on nOrder
        for (int i = 0; i < adjCount - 1; i++)
        {
            for (int j = i + 1; j < adjCount; j++)
            {
                if ((myGraph.nOrder == INCREASINGORDER && strcmp(myGraph.graph[adjIndices[i]].vertex.strName, myGraph.graph[adjIndices[j]].vertex.strName) > 0) ||
                    (myGraph.nOrder == DECREASINGORDER && strcmp(myGraph.graph[adjIndices[i]].vertex.strName, myGraph.graph[adjIndices[j]].vertex.strName) < 0))
                {
                    int temp = adjIndices[i];
                    adjIndices[i] = adjIndices[j];
                    adjIndices[j] = temp;
                }
            }
        }

        // Push sorted adjacent vertices onto the stack
        for (int i = 0; i < adjCount; i++)
        {
            q.push(adjIndices[i]);
        }
    }

    return result;
}
int FindVertexIndex(const string& vertexName, int nVertices) {
    for (int i = 0; i < nVertices; ++i) {
        if (myGraph.graph[i].vertex.strName == vertexName) {
            return i;
        }
    }
    return -1;
}

string depthTopoSort(Graph &myGraph) {
    // TODO
    stack<GraphNode *> topoStack;
    string result = "";
    int nodeIndices[MAX_VERTEX];
    int nodeCount = 0;
        for (int i = 0; i < myGraph.nVertexNum; ++i)
    {
        if (myGraph.graph[i].outdegree == 0)
        {
            nodeIndices[nodeCount++] = i;
        }
    }
        // Sorting nodes based on order type and name
    for (int i = 0; i < nodeCount - 1; i++) {
        for (int j = i + 1; j < nodeCount; j++) {
            if ((myGraph.nOrder == INCREASINGORDER && strcmp(myGraph.graph[nodeIndices[i]].vertex.strName, myGraph.graph[nodeIndices[j]].vertex.strName) > 0) ||
                (myGraph.nOrder == DECREASINGORDER && strcmp(myGraph.graph[nodeIndices[i]].vertex.strName, myGraph.graph[nodeIndices[j]].vertex.strName) < 0)) {
                int temp = nodeIndices[i];
                nodeIndices[i] = nodeIndices[j];
                nodeIndices[j] = temp;
            }
        }
    }
    
    // Pushing nodes onto the stack
    for (int i = 0; i < nodeCount; ++i) {
        myGraph.graph[nodeIndices[i]].isMarked = true;
        topoStack.push(&(myGraph.graph[nodeIndices[i]]));
    }
    while (!topoStack.empty())
    {
        GraphNode *currentVertex = topoStack.top();
        topoStack.pop();
        result += currentVertex->vertex.strName;
        result += " ";
        int nodeIndices[MAX_VERTEX];
        int nodeCount = 0;
        // travese all node in graph to find adjenden of current Vertex
        for (int i = 0; i < myGraph.nVertexNum; ++i)
        {
            VertexType *adj = myGraph.graph[i].adjVertex;
            while (adj != nullptr)
            {
                if (strcmp(adj->strName, currentVertex->vertex.strName) == 0)
                {
                    myGraph.graph[i].outdegree--;
                    if (myGraph.graph[i].outdegree == 0 && !myGraph.graph[i].isMarked)
                    {
                        nodeIndices[nodeCount++] = i;
                    }
                }
                adj = adj->next;
            }
        }
        // Sorting nodes based on order type and name
        for (int i = 0; i < nodeCount - 1; i++)
        {
            for (int j = i + 1; j < nodeCount; j++)
            {
                if ((myGraph.nOrder == INCREASINGORDER && strcmp(myGraph.graph[nodeIndices[i]].vertex.strName, myGraph.graph[nodeIndices[j]].vertex.strName) > 0) ||
                    (myGraph.nOrder == DECREASINGORDER && strcmp(myGraph.graph[nodeIndices[i]].vertex.strName, myGraph.graph[nodeIndices[j]].vertex.strName) < 0))
                {
                    int temp = nodeIndices[i];
                    nodeIndices[i] = nodeIndices[j];
                    nodeIndices[j] = temp;
                }
            }
        }
        for (int i = 0; i < nodeCount; ++i)
        {
            myGraph.graph[nodeIndices[i]].isMarked = true;
            topoStack.push(&(myGraph.graph[nodeIndices[i]]));
        }
    }
    if (!result.empty())
    {
        result.pop_back(); // Remove the last space
    }

    // return reverse of string
    string reverseResult = "";
    for (int i = result.length() - 1; i >= 0; i--)
    {
        reverseResult += result[i];
    }
    return reverseResult;
}

string breadthTopoSort(Graph &myGraph)
{
    queue<GraphNode *> topoQueue;
    string result="";
        int nodeIndices[MAX_VERTEX];
    int nodeCount = 0;
    for (int i = 0; i < myGraph.nVertexNum; ++i)
    {
        if (myGraph.graph[i].indegree == 0)
        {
            nodeIndices[nodeCount++] = i;
        }
    }
    for (int i = 0; i < nodeCount - 1; i++){
        for (int j = i + 1; j < nodeCount; j++){
            if ((myGraph.nOrder == INCREASINGORDER && strcmp(myGraph.graph[nodeIndices[i]].vertex.strName, myGraph.graph[nodeIndices[j]].vertex.strName) > 0) ||
                (myGraph.nOrder == DECREASINGORDER && strcmp(myGraph.graph[nodeIndices[i]].vertex.strName, myGraph.graph[nodeIndices[j]].vertex.strName) < 0))
            {
                int temp = nodeIndices[i];
                nodeIndices[i] = nodeIndices[j];
                nodeIndices[j] = temp;
            }
        }
    }
    for (int i = 0; i < nodeCount; ++i)
    {
        myGraph.graph[nodeIndices[i]].isMarked = true;
        topoQueue.push(&(myGraph.graph[nodeIndices[i]]));
    }

    while (!topoQueue.empty()) {
        GraphNode *currentVertex = topoQueue.front();
        topoQueue.pop();
        result += currentVertex->vertex.strName;
        result += " ";
        VertexType *adj = currentVertex->adjVertex;
        int nodeIndices[MAX_VERTEX];
        int nodeCount = 0;
        while (adj != nullptr) {
            int adjIndex = FindVertexIndex(adj->strName, myGraph.nVertexNum);
            if (adjIndex != -1) {
                myGraph.graph[adjIndex].indegree--;
                if (myGraph.graph[adjIndex].indegree == 0) {
                    nodeIndices[nodeCount++] = adjIndex;
                    // topoQueue.push(&(myGraph.graph[adjIndex]));
                }
            }
            adj = adj->next;
        }
        for (int i = 0; i < nodeCount - 1; i++)
        {
            for (int j = i + 1; j < nodeCount; j++)
            {
                if ((myGraph.nOrder == INCREASINGORDER && strcmp(myGraph.graph[nodeIndices[i]].vertex.strName, myGraph.graph[nodeIndices[j]].vertex.strName) > 0) ||
                    (myGraph.nOrder == DECREASINGORDER && strcmp(myGraph.graph[nodeIndices[i]].vertex.strName, myGraph.graph[nodeIndices[j]].vertex.strName) < 0))
                {
                    int temp = nodeIndices[i];
                    nodeIndices[i] = nodeIndices[j];
                    nodeIndices[j] = temp;
                }
            }
        }
            for (int i = 0; i < nodeCount; ++i)
            {
                myGraph.graph[nodeIndices[i]].isMarked = true;
                topoQueue.push(&(myGraph.graph[nodeIndices[i]]));
            }
    }

    if (!result.empty()) {
        result.pop_back(); // Remove the last space
    }

    return result;
}
int minKey(float key[], bool mstSet[], int nVertices)
{
    float min = INF;
    int minIndex = -1;

    for (int v = 0; v < nVertices; ++v)
    {
        if (!mstSet[v] && key[v] < min)
        {
            min = key[v];
            minIndex = v;
        }
    }

    return minIndex;
}
int FindVertexIndex(const char *vertexName, int nVertices)
{
    for (int i = 0; i < nVertices; ++i)
    {
        if (strcmp(myGraph.graph[i].vertex.strName, vertexName) == 0)
        {
            return i;
        }
    }
    return -1; // Return -1 if the vertex is not found
}
string minSpanTree(Graph &myGraph, VertexType startVertex)
{
    // Array to store constructed MST
    int parent[MAX_VERTEX];

    // Key values used to pick minimum weight edge in cut
    float key[MAX_VERTEX];

    // To represent set of vertices included in MST
    bool mstSet[MAX_VERTEX];

    // Initialize all keys as INFINITE
    for (int i = 0; i < myGraph.nVertexNum; i++)
    {
        key[i] = INF;
        mstSet[i] = false;
        parent[i] = -1;
    }

    // Find the index of the startVertex
    int startIdx = -1;
    for (int i = 0; i < myGraph.nVertexNum; i++)
    {
        if (strcmp(myGraph.graph[i].vertex.strName, startVertex.strName) == 0)
        {
            startIdx = i;
            break;
        }
    }

    if (startIdx == -1)
    {
        return "";
    }

    // First vertex is always the root of MST
    key[startIdx] = 0;
    parent[startIdx] = -1;

    // The MST will have nVertexNum vertices
    for (int count = 0; count < myGraph.nVertexNum - 1; count++)
    {
        // Pick the minimum key vertex from the set of vertices not yet included in MST
        int u = minKey(key, mstSet, myGraph.nVertexNum);

        // Add the picked vertex to the MST Set
        mstSet[u] = true;

        // Update key value and parent index of the adjacent vertices of the picked vertex.
        // Consider only those vertices which are not yet included in MST
        VertexType *adj = myGraph.graph[u].adjVertex;
        while (adj != NULL)
        {
            int v = FindVertexIndex(adj->strName, myGraph.nVertexNum);
            if (!mstSet[v] && adj->weight < key[v])
            {
                parent[v] = u;
                key[v] = adj->weight;
            }
            adj = adj->next;
        }
    }
        int totalSignificantSum = 0;
    // Construct the result string
    string result;
    for (int i = 0; i < myGraph.nVertexNum; i++)
    {
        if (parent[i] != -1)
        {
            char buffer[100];
            totalSignificantSum += static_cast<int>(key[i]); // Convert float to int
        }
    }
    result = to_string(totalSignificantSum);
    return result;
}

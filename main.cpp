// Ass1.cpp : Defines the entry point for the console application.
//
#ifndef _common_h_
#include "common.h"
#define _common_h_
#endif

#ifndef _assignment2_cpp_
#include "assignment2.cpp"
#define _assignment2_cpp_
#endif

void writeFile(char* filename, string str)
{
	char* file_name = filename;
	FILE* f = 0;

	f = fopen(file_name, "w");
	if (f == NULL)
		return;

    char    s[2000];

    strcpy(s, str.c_str());

	fwrite(s, strlen(s), 1, f);

	fclose(f);
}
void DisplayGraph(Graph &myGraph)
{
    // Todo
    for (int i = 0; i < myGraph.nVertexNum; i++)
    {
        cout << myGraph.graph[i].vertex.strName << ": ";

        VertexType *adjVertex = myGraph.graph[i].adjVertex;
        while (adjVertex != NULL)
        {
            cout << adjVertex->strName << " ";
            adjVertex = adjVertex->next;
        }
        cout << endl;
    }
}
int main()
{
    string  result;

    for(int i = 0; i<MAX_VERTEX; i++)
        strcpy(myGraph.graph[i].vertex.strName, "-1");
    string file = "duy";
    string fileInput= "./input/input" + file + ".txt";
    char *filePath = new char[fileInput.length() + 1];

    readFile(myGraph,strcpy(filePath,fileInput.c_str()));
    DisplayGraph(myGraph);
    switch(myGraph.nOperation)
    {
    case DEPTHFIRSTTRAVERSAL:{
        // OK
        string output = "output/" + file + "/DEPTHFIRSTTRAVERSAL.txt";
        char *filePath = new char[output.length() + 1];
        result = depthFirstTraversal(myGraph,myGraph.startVertex);
        cout<<"result:DEPTHFIRSTTRAVERSAL "<<result;
        writeFile(strcpy(filePath, output.c_str()), result);
        break;
    }
    case BREADTHFIRSTTRAVERSAL:{
        // OK
        string output = "output/" + file + "/BREADTHFIRSTTRAVERSAL.txt";
        cout<<"file"<<file;
        char *filePath = new char[output.length() + 1];
        result = breadthFirstTraversal(myGraph,myGraph.startVertex);
        cout<<"result:BREADTHFIRSTTRAVERSAL "<<result;
        writeFile(strcpy(filePath, output.c_str()), result);
        writeFile(strcpy(filePath, output.c_str()), result);
        break;
    }
    case DEPTHTOPOSORT:{
        string output = "output/" + file + "/DEPTHTOPOSORT.txt";
        char *filePath = new char[output.length() + 1];
        result = depthTopoSort(myGraph);
        cout<<"result:DEPTHTOPOSORT "<<result;
        writeFile(strcpy(filePath,output.c_str()), result);
        break;
    }
    case BREADTHTOPOSORT:
    {
        string output = "output/" + file + "/BREADTHTOPOSORT.txt";
        char *filePath = new char[output.length() + 1];
        result = breadthTopoSort(myGraph);
        cout << "result:BREADTHTOPOSORT " << result;
        writeFile(strcpy(filePath, output.c_str()), result);
        break;
    }
    case MINIMUMSPANTREE:{
        // OK
        string output = "output/" + file + "/MINIMUMSPANTREE.txt";
        char *filePath = new char[output.length() + 1];
        result = minSpanTree(myGraph, myGraph.startVertex);
        cout<<"result:MINIMUMSPANTREE "<<result;
        writeFile(strcpy(filePath, output.c_str()), result);
        break;
    }
    }

    return 0;
}
#include <iostream>
#include <cstring>
#include <limits.h> // included to be able to use "infinity" aka INT_MAX
using namespace std;

/*
 * Author | Sophia You
 * Date | 06/11/2024
 * Description |  This project, graph creator, is a program that creates
 * and displays graphs as adjacency matrices on the console. Within the 
 * program, the user can call on Dijkstra's algorithm to find the shortest
 * path.
 * Sources: https://pubs.opengroup.org/onlinepubs/009695399/basedefs/limits.h.html
 */

// NOTE: in this context, the terms "node" and "vertex" are interchangeable

void addVertex(int adjacency[][20], char* nodeList[20], char* label, int i);
void print(int adjacency[][20], char* nodeList[20]);
void addEdge(int adjacency[][20], char* nodeList[20], char* origin, char* destination, int weight);
void removeVertex(int adjacency[][20], char* nodeList[20], char* toRemove);
void removeEdge(int adjacency[][20], char* nodeList[20], char* origin, char* destination);
void shortestPath(int adjacency[][20], char* nodeList[20], int distance[20], char* start, char* end, int current);
int main()
{
  cout << "This algorithm allows you to create a graph and use " << endl;
  cout << "Dijkstra's algorithm to construct the shortest path." << endl;
  int max = 20; // maximum number of nodes
  int adjacency[max][20]; // adjacency matrix for the nodes
  char* nodeList[20]; // keep track of node names;
  int numNodes = 0; // keeps track of number of nodes
  bool wantToQuit = false;

  // clear the adjacency matrix by setting every value to -1
  for (int r = 0; r < max; r++) // r = row
    {
      for (int c = 0; c < max; c++) // c = column
	{
	  adjacency[r][c] = -1;
	}
    }
  for (int i = 0; i < max; i++) // clear the node list too
    {
      nodeList[i] = NULL;
    }
  while (!wantToQuit)
    {
      cout << "Enter a command (LOWERCASE ONLY!):" << endl;
      cout << "add vertex" << endl;
      cout << "add edge" << endl;
      cout << "remove vertex" << endl;
      cout << "remove edge" << endl;
      cout << "shortest path" << endl;
      cout << "print" << endl;
      cout << "quit" << endl;
      int length = 50;
      char* input = new char[length];
      cin.getline(input, length);
      if (strcmp(input, "add vertex") == 0)
	{
	  char* label = new char[length];
	  cout << "adding vertex" << endl;
	  cout << "Enter a label for your vertex: " << endl;
	  cin.getline(label, length);
	  addVertex(adjacency, nodeList, label, numNodes);
	  numNodes++;
	  print(adjacency, nodeList);
	}
      else if (strcmp(input, "add edge") == 0)
       	{
	  // prompt user for information
       	  cout << "adding edge" << endl;
	  char* origin = new char[length];
	  char* destination = new char[length];
	  int edgeWeight = 0;
	  cout << "Which node is the edge coming from?" << endl;
	  cin.getline(origin, max);
	  cout << "Which node is the edge pointing to?" << endl;
	  cin.getline(destination, max);
	  cout << "What is the weight of this edge?" << endl;
	  cin >> edgeWeight;
	  cin.ignore(max, '\n');
	  cout << "edgeweight: " << edgeWeight << endl;
	  addEdge(adjacency, nodeList, origin, destination, edgeWeight);
	  print(adjacency, nodeList); // visualize the graph
       	}
      else if (strcmp(input, "remove vertex") == 0)
        {
          char* toRemove = new char[length];
	  cout << "Which vertex would you like to remove?" << endl;
	  cin.getline(toRemove, max);
	  removeVertex(adjacency, nodeList, toRemove);
	  print(adjacency, nodeList);
        }
      else if (strcmp(input, "remove edge") == 0)
        {
	  char* origin = new char[max];
	  char* destination = new char[max];
	  cout << "What is the origin of the edge you are removing?" << endl;
	  cin.getline(origin, max);
	  cout << "What is the ending vertex of this edge?" << endl;
	  cin.getline(destination, max);
	  removeEdge(adjacency, nodeList, origin, destination);
	  print(adjacency, nodeList);
        }
      else if (strcmp(input, "shortest path") == 0)
	{
	  char* start = new char[max]; // starting vertex
	  char* end = new char[max]; // ending vertex
	  int distance[max]; // keeps track of the shortest distance between vertices
	  for (int i = 0; i < max - 1; i++)
	    {
	      distance[i] = INT_MAX;
	    }
	  cout << "The shortest path algorithm finds the shortest" << endl;
	  cout << "path from one node to the other. Please specify" << endl;
	  cout << "your starting and ending node." << endl;
	  cout << endl;
	  cout << "Start node: " << endl;
	  cin.getline(start, max);
	  cout << "End node: " << endl;
	  cin.getline(end, max);
	  shortestPath(adjacency, nodeList, distance, start, end, 0);
	}
      else if (strcmp(input, "print") == 0)
	{
	  cout << "printing" << endl;
	  print(adjacency, nodeList);

	}
      else if (strcmp(input, "quit") == 0)
	{
	  wantToQuit = true;
	}
      else
	{
	  cout << "Command not found. Maybe check your spelling?" << endl;
	}
      cout << endl;
    }
  cout << "Bye" << endl;
  
}

/**
 * This function adds a vertex to the graph.
 * @param adjacency is the adjacency matrix
 * @param nodeList is the list that keeps track of all vertices
 * @param label is what the user wants to name the new vertex
 * @param i indicates where this new vertex should be inserted
 */
void addVertex(int adjacency[][20], char* nodeList[20], char* label, int i)
{
  int max = 20;
  if (i < max && label)
    {
      /*cout << label << endl;
      //cout << nodeList[i] << endl;
      strcpy(nodeList[i], label);
      cout << "i'm alive!" << endl;*/
      nodeList[i] = label;
    }
  else
    {
      cout << "Maximum vertex capacity reached. You can only add 20 vertices.";
      cout << endl;
    }
}

/** 
 * This function creates an edge between two vertices on the graph.
 */
void addEdge(int adjacency[][20], char* nodeList[20], char* origin, char* destination, int weight)
{
  int max = 20;
  int a = -1; // index of the origin node
  int b = -1; // index of the destination node
  for (int i = 0; i < max; i++) // locate the indices of each node
    {
      if (nodeList[i] && strcmp(nodeList[i], origin) == 0)
	{
	  a = i;
	}
      else if (nodeList[i] && strcmp(nodeList[i], destination) == 0)
	{
	  b = i;
	}
    }
  if (a != -1 && b != -1)
    {
      adjacency[a][b] = weight;
    }
}

/**
 * This function removes a vertex, and its associated edges, from the graph.
 */
void removeVertex(int adjacency[][20], char* nodeList[20], char* toRemove)
{
  int max = 20;
  int index = -1; // index of the vertex to remove
  for (int i = 0; i < max; i++) // find the index of the vertex to remove
    {
      if (nodeList[i] && strcmp(nodeList[i], toRemove) == 0)
	{
	  index = i;
	}
    }
  if (index != -1)
    {
      // remove all edges!
      for (int i = 0; i < max; i++)
	{
	  if (i != index)
	    {
	      adjacency[index][i] = -1;
	      adjacency[i][index] = 0;
	    }
	}
      // remove the vertex itself
      nodeList[index] = NULL;
      delete toRemove;
    }
  else
    {
      cout << "Vertex not found." << endl;
    }
}

/**
 * This function removes the edge between two nodes.
 */
void removeEdge(int adjacency[][20], char* nodeList[20], char* origin, char* destination)
{
  int max = 20;
  int a = -1; // index of the origin node
  int b = -1; // index of the destination node      
  for (int i = 0; i < max; i++) // locate the indices of each node          
    {
      if (nodeList[i] && strcmp(nodeList[i], origin) == 0)
        {
          a = i;
        }
      else if (nodeList[i] && strcmp(nodeList[i], destination) == 0)
        {
          b = i;
        }
    }
  if (a != -1 && b != -1 && a != b)
    {
      adjacency[a][b] = -1;
    }

}

/**
 * This function uses Dijkstra's algorithm to find the shortest path
 * between two nodes.
 */
void shortestPath(int adjacency[][20], char* nodeList[20], int distance[20], char* start, char* end, int current)
{
  int max = 20;
  // this list keeps track of the previous vertex for the shortest path to a node
  char* previous[max];
  bool visited[max];
  char* unvisited[max];
  bool allVisited = false;
  int numVisited = 0; // tracks if each node has been visited
  int a = -1; // index of the start node
  int b = -1; // index of the end node
  for (int i = 0; i < max; i++) // locate the indices of each node
    {
      if (nodeList[i] && strcmp(nodeList[i], start) == 0)
        {
          a = i;
        }
      else if (nodeList[i] && strcmp(nodeList[i], end) == 0)
        {
          b = i;
        }
      visited[i] = false; // no vertices have been visited yet
      if (nodeList[i]) // if the current node exists, add it to the list of unvisited nodes
	{
	  unvisited[i] = nodeList[i];
	}
      else // when a node does not exist or it has been visited, we will change it to null
	{
	  unvisited[i] = NULL;
	}
    }
  distance[a] = 0; // the shortest path from a node to itself is always 0
  previous[a] = nodeList[a]; // the start node has no previous node 
  int cur = a; // index of the current node in the while loop
  while (!allVisited && unvisited[cur]) // while we have not visited every node
    {
      int minDist = INT_MAX;
      int minIndex = -1; // keeps track of the current node's closest neighbor
      // walk through a whole row of the adjacency matrix
      for (int c = 0; c < max; c++)
	{
	  if (adjacency[cur][c] != -1) // if an edge exists
	    {
	      int newdist = adjacency[cur][c] + distance[cur];
	      cout << "new distance of " << nodeList[c] << ": " << newdist << endl;
	      if (newdist < distance[c]) // if this measured distance < current distance
		{
		  distance[c] = newdist;
		  previous[c] = nodeList[cur];
		}
	      if (distance[c] < minDist) // if we have found a new shortest path
		{
		  minDist = distance[c];
		  minIndex = c;
		}
	      //unvisited[c] = NULL;
	    }
	}
      unvisited[cur] = NULL; // say we have visited current
      cur = minIndex;
      char* temp = NULL; // a temporary node that keeps track of the last vertex
      for (int i = 0; i < max; i++) // check the unvisited array
	{
	  if (unvisited[i])
	    {
	      temp = unvisited[i];
	    }
	}
      if (!temp) // if temp is still null, all nodes have been visited
	{
	  allVisited = true;
	}
      cout << "shortest distance" << endl;
      for (int i = 0; i < max; i++)
	{
	  if (nodeList[i] && previous[i] && distance[i] != INT_MAX)
	    {
	      cout << nodeList[i] << ": " << distance[i] << endl;
	    }
	}

    }
  /*while (numVisited < max)
    {
      int minDist = INT_MAX;
      int minIndex = -1; // keeps track of the closest neighbor
      for (int c = 0; c < max - 1; c++)
	{
	  if (adjacency[cur][c] != -1 &&
	      //cur != c &&
	      visited[cur] == false) // if the vertex has an unvisited neighbor
	    {
	      // total distance = distance from start vertex to this vertex + new dist
	      int newdist = adjacency[cur][c] + distance[cur];
	      cout << nodeList[c] << ": " << newdist << endl;
	      if (newdist < distance[c])
		{
		  // if the new distance to c is a shorter path, update the distance table
		  distance[c] = newdist;
		}
	      if (distance[c] < minDist)
		{
		  // find the neighbor with the shortest distance
		  minDist = distance[c];
		  minIndex = c; // we will visit this neighbor next
		  //previous[c] = nodeList[cur];
		}
	    }
	}
      visited[cur] = true;
      //previous[minIndex] = nodeList[cur];
      cur = minIndex;
      numVisited++;
      cout << endl;
      cout << "current shortest distance: " << endl;
      for (int i = 0; i < max - 1; i++)
	{
	  if (nodeList[i] && previous[i] && distance[i] != INT_MAX)
	    {
	      cout << nodeList[i] << ": " << distance[i] << "\tprevious: ";
	      //cout << previous[i]<< endl;
	      cout << endl;
	    }
	}
    }
  cout << endl;
  cout << "FINALLL shortest distance" << endl;
  for (int i = 0; i < max - 1; i++)
    {
      if (nodeList[i] && previous[i] && distance[i] != INT_MAX)
	{
	  cout << nodeList[i] << ": " << distance[i] << endl; //<< "\tprevious: " << previous[i] << endl;
	}
    }
  // while there are unvisited neighbors
  // if the shortest distance is the current node, go to all the neighbors and update
  // their shortest distances
  // otherwise
  // current node is the node we are working with
  // check for current node's neighbors and find the one with the shortest distance
  // you can check this by going across the row
  // add the current SHORTEST PATH DISTANCE (from a to the current node) to the new distance
  // if this NEW DISTANCE TOTAL is less than the SHORTEST DISTANCE for the new neighbor
  // update the shortest dstance
  // add current to the list of visited neighbors
  // set the previous vertex as current
  // do this for every node, then set current to the neighbor with the smallest distance
  /*
  for (int c = 0; c < max - 1; c++)
    {
      //if (unvisited[c] && adjacency[a][c] != -1) // if an edge to a vertex exists
      //{
	  
      //}
      }*/
}
/**
 * This function prints the adjacency matrix of the graph.
 * @param adjacency is the adjacency matrix
 * @param nodeList is the list that keeps track of all vertices
 */
void print(int adjacency[][20], char* nodeList[20])
{
  cout << endl;
  cout << "Across = destination of edge, down = origin" << endl;
  int max = 20;
  for (int r = 0; r < max; r++)
    {
      // print out the headers
      if (nodeList[r])
	{
	  cout << "\t" << nodeList[r];
	}
    }
  cout << endl;
  for (int r = 0; r < max; r++)
    {
      if (nodeList[r])
	{
	  cout << nodeList[r];
	  for (int c = 0; c < max - 1; c++)
	    {
	      if (nodeList[c] && nodeList[r])
		{
		  cout << "\t" << adjacency[r][c];
		}
	    }
	  cout << endl;
	}
    }
}

#include <iostream>
#include <cstring>
using namespace std;

/*
 * Author | Sophia You
 * Date | 06/11/2024
 * Description |  
 */
int main()
{
  cout << "This algorithm allows you to create a graph and use " << endl;
  cout << "Dijkstra's algorithm to construct the shortest path." << endl;
  int max = 20; // maximum number of nodes
  int adjacency[max][max]; // adjacency matrix for the nodes
  bool wantToQuit = false;

  while (!wantToQuit)
    {
      cout << "Enter a command (LOWERCASE ONLY!):" << endl;
      cout << "add vertex" << endl;
      cout << "add edge" << endl;
      cout << "remove vertex" << endl;
      cout << "remove edge" << endl;
      cout << "quit" << endl;
      int length = 50;
      char* input = new char[length];
      cin.getline(input, length);
      if (strcmp(input, "add vertex") == 0)
	{
	  cout << "adding vertex" << endl; 
	}
      else if (strcmp(input, "add edge") == 0)
       	{
       	  cout << "adding edge" << endl;
       	}
      else if (strcmp(input, "remove vertex") == 0)
        {
          cout << "removing vertex" << endl;
        }
      else if (strcmp(input, "remove edge") == 0)
        {
          cout << "removing edge" << endl;
        }
      else if (strcmp(input, "print") == 0)
	{
	  cout << "printing" << endl;
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

// CircleString.cpp : Defines the entry point for the console application.
/*
Given an array of strings A[ ], determine if the strings can be chained together to form a circle. A
string X can be chained together with another string Y if the last character of X is same as first
character of Y. If every string of the array can be chained, it will form a circle.

For eg for the array arr[] = {"for", "geek", "rig", "kaf"} the answer will be Yes as the given strings can
be chained as "for", "rig", "geek" and "kaf"
*/
/*................ALGO.........................
1. create nodes for all the alphbate characters
2. Insert an edge between the 1st and last char of each string.
3. for each node, incoming and outgoing nodes should be same
4. and Graph should be strongly connected i.e. one should be able visit all the nodes starting from any node
5. in step 4, ignore all the nodes which does not have any adjlist i.e. these are inactive nodes.

*/

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>

#define SIZE 26

using namespace std;

void DFS(int node, vector<vector<int> > &adjList, vector<bool> &visited)
{
	if (visited[node]) return;
	visited[node] = true;
	//now visits its adj nodes;
	vector<int> adjNodes = adjList[node];
	for (int i = 0; i < adjNodes.size(); i++)
	{
		DFS(adjNodes[i], adjList, visited);
	}
}

bool isCircleString(vector<string> &strArr)
{
	int n = strArr.size();
	if (n == 0) return true;
	//make each character a node and track incoming and outgoing nodes
	vector<int> InOutDegree(SIZE, 0);
	vector<vector<int> > adjList(SIZE);

	int startNode = -1;
	for (int i = 0; i < n; i++)
	{
		string curr_str = strArr[i];
		int f = curr_str[0] - 'a';
		int b = curr_str[curr_str.length()-1] - 'a';
		InOutDegree[f]++;
		InOutDegree[b]--;
		adjList[f].push_back(b);
		startNode = f;
	}
	
	//Now do DFS
	vector<bool> visited(SIZE, false);

	DFS(startNode, adjList, visited);

	for (int i = 0; i < SIZE; i++)
	{
		if (InOutDegree[i] != 0) return false;
		if (adjList[i].size() > 0 && !visited[i]) return false;
	}

	return true;
}

int main()
{
	int N;
	cin >> N;
	vector<string> strArr;
	string s;
	for (int i = 0; i < N; i++)
	{
		cin >> s;
		strArr.push_back(s);
	}

	cout << isCircleString(strArr) << endl;
    return 0;
}


/*

*/

#include <iostream>
#include <vector>



class Solution {

public:
	std::vector<int> riverSizes(std::vector<std::vector<int>> matrix);
	void traverseNode(int i, int j, std::vector<std::vector<int>> matrix, std::vector<std::vector<int>>& visited, std::vector<int>& results);
	std::vector<std::vector<int>> getUnivisitedNeighbors(int i, int j, std::vector<std::vector<int>> &matrix, std::vector<std::vector<int>>& visited);
};






std::vector<std::vector<int>> Solution::getUnivisitedNeighbors(int i, int j, std::vector<std::vector<int>>& matrix, std::vector<std::vector<int>>& visited) {
	//Create an empty 2D vector which will hold all of the unvisited node coordinates
	std::vector<std::vector<int>> unvisitedNeighbors = {};

	//This if statement checks the child/adjacent node directly above us
	// i>0 makes sure this only accounts for nodes at row 1 or more, because
	//there are no above neighbors at row 0
	//We also want to check the visited matrix to make sure it is not visited
	if (i > 0 && !visited[i - 1][j]) {

		//If this is true, we want to append this child in the unvisitedNeighbor vector
		unvisitedNeighbors.push_back({ i - 1,j });
	}

	//This statement checks the child/adjacent node directly below us
	//i < matrix.size() - 1 only accounts for nodes at row 3 since row 4
	//does not have any nodes below it,
	//We also want to check the visited matrix to make sure it is not visted
	if (i < matrix.size() - 1 && !visited[i + 1][j]) {

		//if this is true, append this child to the unvisitedNeighbor
		unvisitedNeighbors.push_back({ i + 1,j });

	}

	//Now we have to do the same for the left and right children of the node
	//We can start with the left

	//This statement checks the child/adjacent node directly to the left of us
	//j > 0 only accounts for nodes at column 1 since column 0 does not have any nodes
	//to the left of it, we also want to check the visited matrix to make sure its not visited
	if (j > 0 && !visited[i][j - 1]) {
		unvisitedNeighbors.push_back({ i,j - 1 });
	}

	//This statement checks the child/adjacent node directly to the right of us
	//j < matrix.size()-1 accounts for nodes at column 3 since colmun 4 does not have
	//any nodes to the right of it
	//We also want to check the visited matrix to make sure it is not visited
	if (j < matrix.size() - 1 && !visited[i][j + 1]) {
		unvisitedNeighbors.push_back({ i,j + 1 });
	}


	return unvisitedNeighbors;
}

void Solution::traverseNode(int i, int j, std::vector<std::vector<int>> matrix, std::vector<std::vector<int>>& visited, std::vector<int>& results) {

	//We want to initialize a current river size, to take the count of the river, if it is a river
	//Before we start we can say its 0
	int riverSize = 0;

	//Create a stack like structure using a 2D vector, that will have the x and y 
	//coordinates of each node we have to explore,
	//we want to insert the coordinates of i and j for the node we need to explore
	//nodesToExplore will also serve as a way to locate our children node and put them
	//in a stack to be visited
	std::vector<std::vector<int>> nodesToExplore = { {i,j} };

	//Now we need to iterate through nodesToExplore fully, so create a while
	//Loop to continue iterating until every node is explored
	//Remember we entered this helper function since this particular node has not been visited
	//We are trying to find out if its apart of a river, then use DFS/BSF to find other nodes apart of the same river
	while (nodesToExplore.size()) {

		//The current node that we want to explore is going to be the first value
		//within our NodesToExplore stack like 2D vector which gives us i and j
		std::vector<int> currentNode = nodesToExplore[0];

		//We need to retrieve the x and y coordinates from current Node
		int i = currentNode[0];
		int j = currentNode[1];

		//Even though we have entered traverseNode with a node that has not been visited yet,
		//That does not necessarily mean the children nodes have not been visited yet
		//So we explicitly have to check if the children nodes have been visited
		if (visited[i][j]) {
			continue;
		}

		//If it has not been visited, which should be true for the node that came to the
		//traverseNode method, we want to set the visited matrix to 1
		visited[i][j] = 1;

		//Now we can check if the node is a river(1) or land(0), if its land the move on
		if (matrix[i][j] == 0) {
			//pop it from the stack and the move on
			nodesToExplore.erase(nodesToExplore.begin());
			continue;
		}

		//Now we are dealing with a river node, that we have no visited yet
		//We can perform DFS/BFS
		//The first thing we can do is update the count of current river since we know its a river
		riverSize++;

		//Now we need to get all of othe unvisted neighbors of this river node
		//We can create another helper function to help us find this
		//This helper function should give us an array all of the unvisited neighbors to nodes to explore
		std::vector<std::vector<int>> unvisitedNeighbors = getUnivisitedNeighbors(i, j, matrix, visited);

		//Once we have all of the unvisited neighbors we want to append them into our
		//Nodes to explore matrix
		for (int z = 0; z < unvisitedNeighbors.size(); z++) {
			nodesToExplore.push_back(unvisitedNeighbors[z]);
		}

		//We need to pop the current node from the stack
		nodesToExplore.erase(nodesToExplore.begin());





	}
	//Then we can append the river size to our result matrix
	if (riverSize > 0) {
		results.push_back(riverSize);
	}


}


std::vector<int> Solution::riverSizes(std::vector<std::vector<int>> matrix) {
	//The first thing we want to do is declare a vector for our results
	//Which are the sizes of rivers that are within the matrix
	std::vector<int> results;


	//We need to create a identical 2D matrix that is initialized to all 0's
	//To represent that we have not visited any nodes yet
	std::vector<std::vector<int>> visited = matrix;

	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix.size(); j++) {

			visited[i][j] = 0;

		}
	}

	//Once visited is initialized to 0, we can start visiting the nodes inside
	//of the matrix 2D vector
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix.size(); j++) {

			//At every Node that we are at, we want to check if it has been visited
			if (visited[i][j]) {
				//we just want to continue, and skip it
				continue;
			}
			else {
				//if it has not been visited, then we call a helperFunction
				//to actually traverse the node
				//we want to pass in the indexes, the matrix, visited and result array
				traverseNode(i,j,matrix, visited, results);
			}

		}
	}

//Once we exit the loop we can just return the result array
	return results;

}


int main() {
	
	Solution solution;

	std::vector<std::vector<int>> matrix = { {1, 0, 0, 1, 0},{1, 0, 1, 0, 0},{0, 0, 1, 0, 1},{1, 0, 1, 0, 1},{1, 0, 1, 1, 0} };

	std::vector<int> results = solution.riverSizes(matrix);

	for (int x : results) {

		std::cout << x << ' ';
	}






	return 0;
}






















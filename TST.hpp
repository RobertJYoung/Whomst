/**
 * TST.hpp - a ternary trie that is used as a implementing data structure for 
 * an Autocomplete object to hold input data.
 * */
#ifndef TST_hpp
#define TST_hpp
#include <vector>
#include <string>
#include "TSTNode.hpp"

using namespace std;

class TST 
{
protected:

 /** Pointer to the root of the trie */
 TSTNode<char>* root;
 
 /** Size of the TST (number of unique items) */
 unsigned int uniqueSize;

 /** Size of the TST (includes repeats of unique items : node->freuency) */
 unsigned int totalSize;
 
 public :

 /** Constructor for TST - takes a vector of string objects and inputs them into the TST */
 TST(const vector<string> inputs) : root(0), uniqueSize(0), totalSize(0) {
	//If inputs is empty then do not do anything
	if(inputs.size() == 0) {
		return;
	}
	for(string data : inputs) {
		insert(data);
	}
 }
 
 /** Destructor for TST - frees memory in each node through an inorder traversal **/
 ~TST() {
	deleteAll(root);	
 }

 /** Searches for the particular input in the TST */

 TSTNode<char>* find(string input) { 
	// Pointer to the current TSTNode being traversed on starting from root
	TSTNode<char>* curr = root;
	// String to hold the chars of the traversal path
	string traversalString = "";
 	// Search the TST for the input going char by char
 	string::iterator inputIt = input.begin();
	string::iterator inputEnd = input.end();
	// Search the TST for the input going char by char	
 	while(inputIt != inputEnd) {
		// Keep traversing the TST until the next node has the data of the char being searched for
		while(curr->data != *inputIt) {
			// If the data of the char is less than the data of the current char and there is a left child
			if(*inputIt < curr->data && curr->left != 0) {
				// traverse to the left
				curr = curr->left;
			}
			// Else, the char is greater than the data of the current node, if there is a right node
			else if (*inputIt > curr->data && curr->right != 0) {
				// traverse to the right
				curr = curr->right;
			}
			// Char is either equal to this node OR there are no children to traverse to, exit loop
			else {
				break;
			}	
		}
		// If this node is equal to the char being searched for
		if(curr->data == *inputIt) {
			// This char was found add to traversalString
			traversalString += *inputIt;
			// Increment input
		//	++inputIt;
			//If this node has a middle child and there are still chars to input
			auto inputItNext = next(inputIt, sizeof(char));
			if(curr->middle != 0 && inputItNext != inputEnd)  {
				// Travel to middle node
				curr = curr->middle;
				++inputIt;
			}
			// This is a leaf node equal to the first value of input
			else {
				break;
			}
		}
		// There is no middle node to traverse to, this is the end of the tree following this input
		else {
			break;
		}
	}
	// If input is equal to the traversal string then the input has been found return the ending node
	// for the input	
	if(traversalString == input) {
			return curr;
	}
	// The ending node of the input was not found , return null
	else {
		return 0;
	}
}


 /** Takes a input and inserts it into the TST or updates the frequency if input has been inserted before
  *  return : the string representation of input */
 string insert(string & input) {
	// Pointer to the current TSTNode being traversed on starting from root
	TSTNode<char>* curr = root;
	// String to hold the chars of the traversal path
	string traversalString = "";
 	// Search the TST for the input going char by char
 	string::iterator inputIt = input.begin();
	string::iterator inputEnd = input.end();
	// Search the TST for the input going char by char
	
	/*** Special Case: this is the first input of the TST ***/
	if(totalSize == 0) {
		//Initialize root node with first char of input
		root = new TSTNode<char>(*inputIt);
		curr = root;
		++inputIt;
		//Proceed to add the rest of the chars in input to the middle node of each node until 
		//there are no more chars left
		while(inputIt != inputEnd) {
			//Create a new node
			curr->middle = new TSTNode<char>(*inputIt);
			//traverse to middle node
			curr = curr->middle;
			//Update iterator
			++inputIt; 
		}
		//Make the last node created the input node and update class variables
		curr->input = true;
		curr->frequency = 1;
		++uniqueSize;
		++totalSize; 
		return input;
	}

 	while(inputIt != inputEnd) {
		// Keep traversing the TST until the next node has the data of the char being searched for
		while(curr->data != *inputIt) {
			// If the data of the char is less than the data of the current char and there is a left child
			if(*inputIt < curr->data && curr->left != 0) {
				// traverse to the left
				curr = curr->left;
			}
			// Else, the char is greater than the data of the current node, if there is a right node
			else if (*inputIt > curr->data && curr->right != 0) {
				// traverse to the right
				curr = curr->right;
			}
			// Char is either equal to this node OR there are no children to traverse to, exit loop
			else {
				break;
			}	
		}
		// If this node is equal to the char being searched for
		if(curr->data == *inputIt) {
			// This char was found add to traversalString
			traversalString += *inputIt;
			// Increment input
		//	++inputIt;
			//If this node has a middle child and there are still chars to input
			auto inputItNext = next(inputIt, sizeof(char));
			if(curr->middle != 0 && inputItNext != inputEnd)  {
				// Travel to middle node
				curr = curr->middle;
				++inputIt;
			}
			// This is a leaf node equal to the first value of input
			else {
				break;
			}
		}
		// There is no middle node to traverse to, this is the end of the tree following this input
		else {
			break;
		}
	}
	//if stored string is equal to input then node was found, not found elsewise
	if(traversalString == input) {
	/******** Case 1 : path to represent input is complete ****************/
		//If the final node is an input node (this is a not a new input) 
		if(curr->input == true) {
			//Final node is the final node for input, update frequency
			++curr->frequency;
			//Update totalSize
			++totalSize;
			return input;
		}
		// Final node is not a input node (this is a new input)
		else {
			//Make curr a input node and update frequency
			curr->input = true;
			++curr->frequency;
			//Update uniqueSize and totalSize
			++uniqueSize;
			++totalSize;
			return input;
		}
	}
	else {
 		/***** Case 2 : path to represent input is incomplete *********/
 		/* create new nodes to establish a path to represent this new input */
		//put
 		//if this char is less than the value of the current node
		if(*inputIt < curr->data) {
			//create new node containing the data of the char pointed to by inputIt as the left node if the current node
			curr->left = new TSTNode<char>(*inputIt);
			//travel to this new node
			curr = curr->left;
			//Update inputIt
			++inputIt;
 			// while there are still chars left in the input
 			while(inputIt != inputEnd) {
				//create a middle child and traverse to it
				curr->middle = new TSTNode<char>(*inputIt);
				curr = curr->middle;
				++inputIt;
			}
		}
		//this char is greater than the value of the current node
		else if (*inputIt > curr->data) {
			//create new node containing the data of the char pointed to by inputIt as the right node if the current node
			curr->right = new TSTNode<char>(*inputIt);
			//travel to this new node
			curr = curr->right;
			//Update inputIt
			++inputIt;
 			// while there are still chars left in the input (up to the second to last char) that do not have a node
 			while(inputIt != inputEnd) {
			//create a middle child and traverse to it
				curr->middle = new TSTNode<char>(*inputIt);
				curr = curr->middle;
				++inputIt;
			}
 		}
		//this char is equal to the current node
		else {	
			//Update iterator
			++inputIt;
			//create new node containing the data of the char pointed to by inputIt as the right node if the current node
			curr->middle = new TSTNode<char>(*inputIt);
			//travel to this new node
			curr = curr->middle;
			//Update inputIt
			++inputIt;
 			// while there are still chars left in the input (up to the second to last char) that do not have a node
 			while(inputIt != inputEnd) {
			//create a middle child and traverse to it
				curr->middle = new TSTNode<char>(*inputIt);
				curr = curr->middle;
				++inputIt;
			}
		}
		// set the last node rf the input to be a end node and have frequency == 1
		curr->input = true;
		curr->frequency = 1;
		//Update totalSize and uniqueSize (this is a new input)
		++uniqueSize;
		++totalSize;
		return input;
	} 
 } /**** End of method "insert" ****/

 /** Returns the totalSize of the TST **/
 unsigned int size() const {
	return totalSize;
 }


 /** wholeInorder - performs an inorder traversal over all elements of the TST starting at the root node */
 void wholeInorder() {
	inorder(root);
 }
	
 /** inorder - method that performs an inorder traversal of the tst */
  void inorder(TSTNode<char>* n) const {
        if(n == 0) return;
        inorder(n->left);
        cout << *n << endl;
	inorder(n->middle);
        inorder(n->right);
  }
 
 private :

 /** deleteAll - deletes all nodes in the TST **/
 void deleteAll(TSTNode<char>* node) {
 	//perform a postorder traversal and delete nodes
 	if(node == 0) {	
		return;
 	}
	//traverse left
	deleteAll(node->left);
	//traverse middle
	deleteAll(node->middle);
	//traveerse right
	deleteAll(node->right);
	//delete node
	delete node;		
 }

}; //end of class TST

#endif //TST_hpp

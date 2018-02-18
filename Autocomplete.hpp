/**
 *  CSE 100 PA2 C++ Autocomplete
 *  Author: Jonathan Margoliash
 *  Modified from code authored by: Jor-el Briones, Christine Alvarado
 */

#ifndef AUTOCOMPLETE_HPP
#define AUTOCOMPLETE_HPP

//i added this (not sure if ok to do)
#include "TST.hpp"
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
using namespace std;


 /* Compares the frequencies of the pair objects */
 bool static compareFrequency(const pair<string, unsigned int> & pair1, const pair<string, unsigned int> & pair2) {
	// handles cases where two pairs have strings with the same frequency 
	if(pair1.second == pair2.second) {
		// returns true if the first string comes first lexicographically
		return pair1.first < pair2.first;
	}
 	 return pair1.second > pair2.second;
 }



/**
 *  You may implement this class as either a mulit-way trie
 *  or a ternary search trie.
 */
class Autocomplete
{
public:


 /* Compares the frequencies of the pair objects */
// bool compareFrequency(const pair<string, unsigned int> & pair1, const pair<string, unsigned int> & pair2) {
 // return pair1.second < pair2.second;
// }

  /*
  Create an Autocomplete object.
  This object should be trained on the words vector
  That is - the predictCompletions() function below should pull autocomplete
  suggestions from this vector

  Input: words. Must be all lowercase, with most  non-word characters removed (e.g. ',' ';' '%' etc.)
  In addition to alphabetic characters, words may contain digits, single apostrophes, dashes etc.
  */
  Autocomplete(const vector<string> words) {
    //TODO
  	  autocompleteTST = new TST(words);	
  }
	
  /**
  * Prints out the TST	
   * */
   void inorder() {
	autocompleteTST->wholeInorder();
   }

  /* Return up to 10 of the most frequent completions
   * of the prefix, such that the completions are words in the dictionary.
   * These completions should be listed from most frequent to least.
   * If there are fewer than num_completions legal completions, this
   * function returns a vector with as many completions as possible.
   * Otherwise, 10 completions should be returned.
   * If no completions exist, then the function returns a vector of size 0.
   * The prefix itself might be included in the returned words if the prefix
   * is a word (and is among the num_completions most frequent completions
   * of the prefix)
   * If you need to choose between two or more completions which have the same frequency,
   * choose the one that comes first in alphabetical order.
   *
   * Inputs: prefix. The prefix to be completed. Must be of length >= 1.
   * Return: the vector of completions
   */
  vector<string> predictCompletions(const string prefix) {
	//incorrect prefix input
	if(prefix.length() < 1) {
		cout << "Prefix is less then 1 character, exiting..." << endl;
		exit(1);
	}
	//process possibleInputs to a vector of strings
	vector<string> completions;	
	//Special Case : the TST is empty
	if(autocompleteTST->size() == 0) {
		return completions;
	}
   	// travel to the node containing the last char of the prefix
    	TSTNode<char>* endPrefixNode = autocompleteTST->find(prefix);
	//check to see of the prefix was found in the TST
	if(endPrefixNode == 0){
		//return a vector of size 0
		return completions;
	}	
   	// create a vector of pair<string, unsigned ints> to hold the most frequent inputs
	vector<pair<string, unsigned int>> possibleInputs;
   	// call DFS using this node as the root of the function call
   	// traversal string
	string traversalString = prefix;
	//special case : the prefix is itself a word
	if(endPrefixNode->input == true) {
		possibleInputs.push_back(pair<string, unsigned int>(traversalString , endPrefixNode->frequency));
	}
   	queryCompletions(endPrefixNode->middle, possibleInputs, traversalString);
   	// store all or the top 10 most frequent inputs from the TST into a vector
	vector<pair<string, unsigned int>>::iterator itbegin = possibleInputs.begin();
	vector<pair<string, unsigned int>>::iterator itend = possibleInputs.end();
	// sort the pairs 
  	sort(itbegin, itend, compareFrequency);
	// trim possibleInputs to 10 if larger than 10 elements
	if(possibleInputs.size() > 10) {
		possibleInputs.resize(10);
	}
	//process possibleInputs to a vector of strings
	itbegin = possibleInputs.begin();
	itend = possibleInputs.end();
	while(itbegin != itend) {
		completions.push_back(itbegin->first);
		++itbegin;
	}  
	return completions;
  }

  /* Destructor */
  ~Autocomplete() {
    //TODO
    delete autocompleteTST;
  }

  //You may add your own code here

private:

	//acts as the trie data structure for the class
	TST* autocompleteTST;

  //you may add your own code here
  /** queryCompletions - performs a modified DFS traversal that keeps track of current path traveled and adds to a vector of 
  *	pair<string, usigned> objects that contains the possible autocomplete strings and their frequency.
  *   Params:
  *   - rootNode : a pointer to a TSTNode<char> object that is passed to the method that serves as the current node being queried as a possible input node
  *   - possibleInputs : a vector of pair<string, unsigned int> ojects that stores the possible completions of the input based on the original starting node
  *   - traversalString : a string object that serves as a record of the current path of nodes traveled to since the original base call
  *     it is used to form the string to be added to possibleCompletions should rootNode be a input node
  *     NOTE: traversalString should have its initial value be the prefix of the indtended input subsets to be queried 
  */
  void queryCompletions(TSTNode<char>* rootNode, vector<pair<string, unsigned int>> & possibleInputs, string traversalString) {
	//base cases	
	// this is a null reference return
	if(rootNode == 0) {
		return;
	}
	//if rootNode is an input node
	if(rootNode->input == true) {	
		//add traversal string to possibleInputs
		// create a pair object with the first value being the string corresponding to the input
		possibleInputs.push_back(pair<string, unsigned int>(traversalString + rootNode->data , rootNode->frequency));
	}
	/***recursive cases***/
	//recurse left
	queryCompletions(rootNode->left, possibleInputs, traversalString);
	// add this nodes data to traversal string
	//recurse middle
	queryCompletions(rootNode->middle, possibleInputs, traversalString + rootNode->data);
	//recurse right
	queryCompletions(rootNode->right, possibleInputs, traversalString);
  }
	
};

#endif // AUTOCOMPLETE_HPP

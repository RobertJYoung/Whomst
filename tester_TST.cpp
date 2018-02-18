#include "TST.hpp"
#include "Autocomplete.hpp"
#include "AutocompleteUtils.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>

using namespace std;

/**
 * A simple test driver for the TST class template.
 **/
int main() {
	/*
	if(argc != 2) {
		cout << "incorrect function parameters!" << endl;
		return -1;
	}
	*/
	//create a vector of input objects from myTestFile.txt
//	vector<string> & testV = getWords("myTestFile.txt");
	
	//create iterators for testV
//	vector<string>::iterator startV = testV.begin();
//	vector<string>::iterator endV = testV.end();

	/********** TEST SUITE FOR TST::insert() *************/
	
	//Test 1
	//create a TST object
	TST tst(AutocompleteUtils::getWords("myTestFile.txt"));
	
	//Perform an inorder traversal of the TST
	tst.wholeInorder();
		
	/*
	// Test 2
	for( ; startV != endV; ++startV) {
		cout <<	tst.insert(*startV) << endl;
	} 
	*/	
	
	cout << "End of main" << endl;
}


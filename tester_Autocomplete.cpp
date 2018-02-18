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
 *  * A simple test driver for the TST class template.
 *   **/
int main() {

	/** Autocomplete TEST SUITE **/
	cout << "tester_Autocomplete START" << endl;
	//create Autocomplete object
	Autocomplete testAC(AutocompleteUtils::getWords("myTestFile.txt"));
	//test predictCompletions()
	string prefix = "Bad";
	cout << "enter prefix: "; cin >> prefix;
	vector<string>	predictedCompletions = testAC.predictCompletions(prefix);
	testAC.inorder();
	vector<string>::iterator it = predictedCompletions.begin();
	vector<string>::iterator end = predictedCompletions.end();
	while(it != end) {
		cout << *it << endl;
		++it;
	}
	cout << "END OF MAIN" << endl;
}

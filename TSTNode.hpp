/**
 * TSTNode - class to serve as the node object of a TST object holding
 * data containing a char and a marker to indicate if the node is a "input" node.
 * Author : Robert Young
 * Data : 2/5/2018
 */
#ifndef TSTNode_hpp
#define TSTNode_hpp
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

template <typename Data>
class TSTNode {

 public:
  
  /** Constructor for a TSTNode: set data to given input and set all pointers to null */
  TSTNode(const Data & d) : data(d), input(false), frequency(0) {
	left = right = middle = parent = 0;
  } 

  TSTNode<Data>* left;
  TSTNode<Data>* right;
  TSTNode<Data>* middle;
  TSTNode<Data>* parent;
  Data const data;   // the const Data in this node.
  bool input; 	//if the node is last char in an input string
  unsigned int frequency; // the number of times the node had been "inserted" (input input)

}; // end of TSTNode

 template <typename Data>
 /** Overload operator<< to print a TSTNode's fields to an ostream. */
 ostream & operator<<(ostream& stm, const TSTNode<Data> & n) {
  stm << '[';
  stm << setw(10) << &n;                 // address of the TSTNode
  stm << "; p:" << setw(10) << n.parent; // address of its parent
  stm << "; l:" << setw(10) << n.left;   // address of its left child
  stm << "; r:" << setw(10) << n.right;  // address of its right child
  stm << "; m:" << setw(10) << n.middle;  // address of its middle child
  stm << "; d:" << setw(10) << n.data;    // its data field
  stm << "; input:" << setw(10) << n.input; // input marker
  stm << "; frequency:" << setw(10) << n.frequency; // frequency of occurence on the trained data
  stm << ']';
  return stm;
 }

#endif // BSTNODE_HPP

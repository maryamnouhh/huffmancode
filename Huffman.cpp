//
//  Huffman.cpp
//  Coding
//
//  Created by Maryam Nouh on 12/22/20.
//
#pragma once
#include "Huffman.h"
#include <iomanip>
#include<iostream>

using namespace std;


//--- Definition of constructor
 BinaryTree::BinaryTree():
     myRoot(0)
 {}

//--- Definition of empty()
 bool BinaryTree::empty() const
{
    return myRoot == 0;
}

//--- Definition of generateCode()
 void BinaryTree::generateCode()
{
     if (empty()) {
         cerr << "The Tree is Empty" << endl;
         return;
     }
      generateCodeAux(myRoot, "");  
}

//--- Definition of graph()
 void BinaryTree::graph(ostream& out) const
{
    graphAux(out, 0, myRoot);
}


//--- Definition of HuffmanTree()
void BinaryTree::HuffmanTree(char data[], int freq[], int sz)
{
    BinaryTree::BinNodePointer root;
    // array of nodes with the same size of the arrays passed as parameters to the function
    BinaryTree::BinNodePointer arr = new BinNode[sz];
    // loops on nodes, copies data and its corresponding frequency in one array
    for (int i = 0; i < sz; i++) {
        if (*(freq+i) == 0)
            continue;
        arr[i].data = data[i];
        arr[i].freq = freq[i];
    }
    // loop while the array has more than one node
    while (sz != 1) {
        BinaryTree::BinNodePointer rl = NULL, rr =NULL;
        // create new nodes with the values given before
        rl = new BinNode(arr[0]);
        rr = new BinNode(arr[1]);
        // connect the first two nodes together in a new node called root
        root = new BinNode('#', rl->freq + rr->freq);
        // make the root's left the first node of the array
        root->left = rl;
        // make the root's right the second node of the array
        root->right = rr;
        // delete the first two nodes
        removeData(arr, sz);
        removeData(arr, sz);
        // insert the root node in the array based on its frequency while maintaining the ascending order
        insertionSort(root, arr, sz);

    }
    // make the root of the huffman tree the node remaining in the array
    myRoot = &arr[0];

}


//--- Definition of generateCodeAux()
void BinaryTree::generateCodeAux(BinNode* tree, string code)
{
    // no tree, hence return
    if (tree == NULL)
        return;
    // if the subtree at hand is a leaf node, print its data and its corresponding frequency
    if (tree->left == NULL && tree->right == NULL)
    {
        cout << "Leaf Found: " << tree->data << "\t" << code << endl;
    }
    // recursive call for its left subtree
    generateCodeAux(tree->left, code + "1");
    // recursive call for its right subtree
    generateCodeAux(tree->right, code + "0");
}

//--- Definition of graphAux()
void BinaryTree::graphAux(ostream& out, int indent,
    BinaryTree::BinNodePointer subtreeRoot) const
{
    if (subtreeRoot != 0)
    {
        graphAux(out, indent + 8, subtreeRoot->left);
        out << setw(indent) << " " << subtreeRoot->data << ":" << subtreeRoot->freq << endl;
        graphAux(out, indent + 8, subtreeRoot->right);
    }
}

//--- Definition of decode()
string BinaryTree::decode(string str) {
    int pos = 0;
    string s;
    char x='\n';
    BinaryTree::BinNodePointer ptr = myRoot;
    // loop on str using a variable pos
    while (pos < str.length()) {
        // loop on internal nodes and pos is still in the range of str's length
        while ( ptr->left != NULL && ptr->right != NULL && pos<str.length()) {
            // binary 1 means left branch of the tree
            if (str[pos] == '1') {
                // reposition the ptr
                ptr = ptr->left;
            }
            // binary 0 means right branch of the tree
            else if(str[pos] == '0') {
                // reposition the ptr
                ptr = ptr->right;
            }
            // integer other than 1 or 0 is entered, invalid
            else {
                return "--Error in Binary code entered-- ";
                
            }
            // increment position to move to next binary
            pos++;
        }
        // as long as ptr does not hold an internal node
        if (ptr->data != '#')
            // if it holds this character
            if (ptr->data == '^')
                // new line
                s += x;
            else
                // concatenate the character found
                s+= ptr->data;
        else {
            // internal node is never printed
            return " --Not Found-- ";
        }
        // restart loop from the root of the tree
        ptr = myRoot;
    }
    // return the full string
    return s;
}

//--- Definition of encode()
string BinaryTree::encode(string str) {
    string s="";
    // loop over the string to be encoded letter by letter
    for (int i = 0; i < str.length(); i++)
        //calls encodeAux() by passing the root of the tree, an empty string and the character to be encoded
        s += encodeAux(myRoot,"",str[i]);
    // return the concatenated string of characters
    return s;
}

//--- Definition of encodeAux()
string BinaryTree::encodeAux(BinNode* tree, string code,char key)
{
    string l,r;
    // tree is empty
    if (tree == NULL)
        return "";
    // stopping condition of the recursion, the key was found, return its binary code
    if (key == tree->data)
        return code;
    // search for the character in the descendants of the node
    else {
        // recursive call of the function for the left subtree
        l=encodeAux(tree->left, code + "1",key);
        // recursive call of the function for the right subtree
        r=encodeAux(tree->right, code + "0",key);
    }
    // key was not found in the left subtree
    if (l.empty())
        // return the other binary code found
        return r;
    else
        // return the first binary code
        return l;
}


void BinaryTree::insertionSort(BinNodePointer root, BinNodePointer arr, int& sz)
{
    // loop on the given array
    for (int i = 0; i < sz; i++) {
        // find the index where the node should be inserted (ascending order) based on the frequency
        if (root->freq < arr[i].freq) {
            // shifts left to right from the end of the array till we meet the index
            for (int j = sz; j > i; j--)
                arr[j] = arr[j-1];
            // insert the node at the index found
            arr[i] = *root;
            // increment size by 1 and return
            sz++;
            return;
        }
    }
    // the freqyency is larger than all other frequencies, no shifting needed
    arr[sz] = *root;
    // increments size by 1 and return
    sz++;
    return;
}

void BinaryTree::removeData(BinaryTree::BinNodePointer arr, int& sz) {
    // loops on size -1 to shift by 1, hence deleting the first node
    for (int i = 0; i < sz - 1; i++)
        // shifts right to left
        arr[i] = arr[i + 1];
    // decrements size by 1
    sz --;
}




//-- Definition of the output operator
ostream& operator<<(ostream& out, const BinaryTree& tree) {
    // operator overload
    tree.graph(out);
    return out;
}

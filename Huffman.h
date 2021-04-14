//
//  Huffman.hpp
//  Coding
//
//  Created by Maryam Nouh on 12/22/20.
//
#pragma once
#ifndef Huffman_h
#define Huffman_h

#include <stdio.h>
#include <string>
using namespace std;

class BinaryTree
{
public:
    /***** Function Members *****/
    BinaryTree();
    /*------------------------------------------------------------------------
     Construct a binary tree object.

     Precondition:  None.
     Postcondition: An empty binary tree has been constructed.
     -----------------------------------------------------------------------*/

    bool empty() const;
    /*------------------------------------------------------------------------
     Check if the binary tree is empty.

     Precondition:  None.
     Postcondition: Returns true if binary tree is empty and false otherwise.
     -----------------------------------------------------------------------*/

    void HuffmanTree(char data[], int freq[], int sz);
    /*------------------------------------------------------------------------
     Create the Huffman Tree.

     Precondition:  None.
     Postcondition: Creates the Huffman tree based on the frequency of the
     characters found in the given file.
     -----------------------------------------------------------------------*/

    void generateCode();
    /*------------------------------------------------------------------------
     Traverse the binary tree.

     Precondition:  None.
     Postcondition: Prints the character with its corresponding binary code
     from the binary tree.
     Note: generateCode() uses private auxiliary function generateCodeAux().
     -----------------------------------------------------------------------*/

    void graph(ostream& out) const;
    /*------------------------------------------------------------------------
     Graphic output of the binary tree.

     Precondition:  ostream out is open.
     Postcondition: Graphical representation of the binary tree has been output
     to out.
     Note: graph() uses private auxiliary function graphAux().
     ------------------------------------------------------------------------*/

    string decode(string str);
    /*------------------------------------------------------------------------
     Decodes from binary to characters according to the key.

     Precondition:  Tree is built.
     Postcondition: String of characters is returned.
     ------------------------------------------------------------------------*/
    string encode(string str);
    /*------------------------------------------------------------------------
     Encodes from characters to cinary according to key.

     Precondition:  Tree is built.
     Postcondition: String of binary numbers is returned.
     Note: encode() uses private auxiliary function encodeAux().
     ------------------------------------------------------------------------*/
private:
    /***** Node class *****/
    class BinNode
    {
    public:
        char data;
        int freq;
        BinNode* left;
        BinNode* right;

        // BinNode constructors
        // Default -- data part is default DataType value; both links are null.
        BinNode()
            : left(0), right(0),data(0),freq(0)
        {}

        // Explicit Value -- data part contains item; both links are null.
        BinNode(char item, int f)
            : data(item), freq(f), left(0), right(0)
        {}
        //Copy Constructor
        BinNode(BinNode& x) {
            data = x.data;
            freq = x.freq;
            if (x.left != NULL) {
                left = new BinNode(*(x.left));
            }
            else
                left = 0;
            if (x.right != NULL) {
                right = new BinNode(*(x.right));
            }
            else
                right = 0;
        }
    };// end of class BinNode declaration

    typedef BinNode* BinNodePointer;

    string encodeAux(BinNode* tree, string code,char key);
    /*------------------------------------------------------------------------
     Encodes from characters to cinary according to key auxillary function.

     Precondition:  Tree is built.
     Postcondition: String of binary numbers is returned.
     ------------------------------------------------------------------------*/
    /***** Private Function Members *****/
    void generateCodeAux(BinNode* tree, string code);
    /*------------------------------------------------------------------------
     Generate code auxiliary function.

     Precondition: None
     Postcondition: A binary code is generated for each character that resides
     in the tree.
     ------------------------------------------------------------------------*/

    void graphAux(ostream& out, int indent,
        BinNodePointer subtreeRoot) const;
    /*------------------------------------------------------------------------
     Graph auxiliary function.

     Precondition:  ostream out is open; subtreePtr points to a subtree
     of this binary tree.
     Postcondition: Graphical representation of subtree with root pointed
     to by subtreePtr has been output to out, indented indent spaces.
     ------------------------------------------------------------------------*/


    void insertionSort(BinNodePointer root, BinNodePointer arr, int& sz);
    /*------------------------------------------------------------------------
     Inserts root Node in a sorted array of nodes, called by HuffmanTree()

     Precondition:  None.
     Postcondition: Array of nodes is sorted.
     ------------------------------------------------------------------------*/
    void removeData(BinNodePointer arr, int& sz);
    /*------------------------------------------------------------------------
     Removes first node by shifting other nodes.

     Precondition:  None.
     Postcondition: First node is deleted from the array.
     ------------------------------------------------------------------------*/

     /***** Data Members *****/
    BinNodePointer myRoot;

}; // end of class template declaration

ostream& operator<<(ostream& out, const BinaryTree& tree);

#endif /* Huffman_hpp */


#include <iostream>
#include "Huffman.h"
#include <fstream>

using namespace std;

void sortArr(char data[], int freq[], int sz);
void fileRead(char data[], int freq[], int size);
int CountUniqueCharacters();
void decode(BinaryTree t);
void encode(BinaryTree t);

// right 0 ,, left 1
int main()
{
    // get size of unqiue characters for arrays data and freq
	int sz = CountUniqueCharacters();

    // dynamic arrays (data and freq) based on the text inputted by the user
	char* data = new char[sz];
	int* freq = new int[sz];
    // initialize the arrays to 0
	for (int i = 0; i < sz; i++) {
		data[i] = 0;
		freq[i] = 0;
	}
    // call function to read file
	fileRead(data, freq, sz);
    // call function to sort the arrays based on the freq
	sortArr(data, freq, sz);
    
    
	//--------------------------------------------------------------------------------------//
	BinaryTree tree;
	tree.HuffmanTree(data, freq ,sz);
	cout << tree;
	tree.generateCode();

	encode(tree);
	decode(tree);
	return 0;
}

void sortArr(char data[], int freq[],int sz) {
	int tempi;
	char tempc;
    // loop on the arrays using two for loops
	for (int i = 0; i < sz-1; i++) {
		for (int j = 0; j < sz-i-1; j++) {
            // swap to have data and frequencies in ascending order
			if (freq[j+1] < freq[j]) {
				tempc = data[j];
				tempi = freq[j];
				data[j] = data[j+1];
				data[j+1] = tempc;
				freq[j] = freq[j+1];
				freq[j+1] = tempi;
			}
		}
	}
}

int CountUniqueCharacters() {
	int count = 0,counter=0;
	bool line=false;
	string str,past;
	ifstream file("Text_files\\Text_to_build.txt");
	// read every line
    while(getline(file,str))
	{
        // concatenate all lines
		past += str;
        // count the lines
		counter++;
	}
    // compare the characters from start to i with the character i
    for (int i = 0; i < past.length(); i++) {
        bool appears = false;
        for (int j = 0; j < i; j++) {
            // if the character appeared before
            if (past[j] == past[i]) {
                appears = true;
                break;
            }
        }
        // increase count if the character did not appear before
        if (!appears) {
            count++;
        }
        
    }
	file.close();
    // if lines are greater than 1, add 1 to unique characters for the character "new line"
	if (counter > 1)
		return count + 1;
    // return number of unique characters
	return count;
}

void fileRead(char data[], int freq[], int sz) {
	ifstream file("Text_files\\Text_to_build.txt");
	string ch,past;
	int count=0,linecounter = 0;
	while(getline(file,ch)) {
        // concatenate all lines
		past += ch;
        // count the lines
		linecounter++;
	}

    // loop on teh concatenated array, character by character
    for (int j = 0; j < past.length(); j++) {
        bool added = false;
        // count -- indicates the first free spot in the arrays
        // loop again to compare each character with all previous ones
        for (int i = 0; i <= count; i++) {
            // character was found before
            if (data[i] == past[j]) {
                // increase freq and break
                freq[i]++;
                break;
            }
            // character was not registered in array "data" before
            else if (data[i] == NULL) {
                // add the character to the array (initialize this character)
                data[i] = past[j];
                // increment its freq
                freq[i]++;
                // hence it was added
                added = true;
                break;
            }
        }
        // if something new was added
        if (added)
            // increase the count, so that it tells us the next free location in the array
            count++;
    }
    // if we have more than one line
    if (linecounter > 1) {
        // add a character correspinding to "new line"
        data[sz - 1] = '^';
        // with a freq less than the linecounter by 1
        freq[sz - 1] = linecounter - 1;
    }
    // close the file
    file.close();
}


void decode(BinaryTree t) {
	ifstream input("Text_files\\Decode.txt");
	ofstream output("Text_files\\Decoded_Output.txt");
	string ch;
    // read from a file the string to be decoded
	getline(input, ch);
    // decode line by line
	do {
        // write on the file "Decoded_Output.txt" the returned string from the function decode
		output << "The decoded output is: "<<endl<<t.decode(ch);
        // get the next line in string ch
		getline(input, ch);
	} while (!(input.eof()));
    
    // close files
	output.close();
	input.close();
}


void encode(BinaryTree t) {
	ifstream input("Text_files\\Text_input.txt");
	ofstream output("Text_files\\Encoded_text.txt");
	string key,temp;
	int linecount = 0;
    
    // get first line from the file "Text_input.txt" and add it to the string temp
	while (getline(input, temp)) {
        // if this is the second line or more
		if (linecount >= 1)
            // concatenate the character that represents the new line
			key += '^';
        // concatenate string temp to string key
		key += temp;
        // increment line counter
		linecount++;
	}
    // write to file "Encoded_text.txt" the encoded string returned from function encode
	output<<t.encode(key);
    
    // close files
	input.close();
	output.close();
}

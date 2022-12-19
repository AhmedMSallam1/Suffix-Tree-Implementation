#include <iostream>
#include "cstring"

using namespace std;
/*
* Ahmed Mohamed Sallam 20210614
* Mohamed Gamal Abdelaziz 20201146
* Omar Walid 20201126
* Roaa Gamal Yousef 20210571
*/
// Suffix Tree Node Structures
class SuffixTreeNode {
public:
//The starting index (in the original string) of the characters on the edge going to this node.
    int indexEdge;
//The starting index (in the original string) of the suffix ending at this node (used for leaf nodes only, otherwise it should be -1).
    int indexLeaf = -1;
//Array of pointers to children nodes. The array size equals to the alphabet size.
    SuffixTreeNode *children[26];

// constructor to input the Data
    SuffixTreeNode(int indexEdge, int indexLeaf) {
        this->indexEdge = indexEdge;
        this->indexLeaf = indexLeaf;
// Clear children array
        for (auto &i: children) {
            i = NULL;
        }
    }
};

// Suffix Tree Structures
class SuffixTree {
private:
    SuffixTreeNode *root;
    int n; //size of input string
    char *copystring; // char array copy the coming string into it
public:
// constructor to input the String and start build the Suffix Tree
    SuffixTree(char *str) {
        copystring = str;
//calculate the length of string
        n = strlen(str);
// initialization the root node with -1,-1
        root = new SuffixTreeNode(-1, -1);
        for (int i = 0; i < n; ++i) {
// start build the tree
            construction(i, n);
        }
    }

// construction function to build the suffix tree
    void construction(int edge, int leaf) {
// initialization new node and assigment with root value
        SuffixTreeNode *currentnode = root;
// initialization i to loop on the string
        int i = 0;
// the loop must be in range leaf , edge (end , start)
        for (; i < (leaf - edge);) {
// index refer on first char and handle Ascii
            int point = copystring[i + edge] - 'a';
// check if the children node is empty or not
            if (currentnode->children[point] == nullptr) {
// if yes equal the value with edge start+i leaf and then break
                currentnode->children[point] = new SuffixTreeNode(edge + i, leaf);
                break;
            } else {
// check if children indexEdge at point not equal indexLeaf at same position
                if (currentnode->children[point]->indexEdge != currentnode->children[point]->indexLeaf) {
// equal children indexLeaf at point indexEdge
                    currentnode->children[point]->indexLeaf = currentnode->children[point]->indexEdge;
// make int to store index edge value
                    int st = currentnode->children[point]->indexEdge;
// make int to value to return if he in begins or in end of string his value always equal to 0 or n
                    int l = copystring[st + 1] - 'a';
// store the new node
                    currentnode->children[point]->children[l] = new SuffixTreeNode(st + 1, leaf);
                }
// change the current node value
                currentnode = currentnode->children[point];
// increase i
                ++i;
            }
        }
// check if i on leaf node
        if (i == leaf - edge) {
            currentnode->indexLeaf = leaf;
        }
// check if i on internal node and need to spilt
        if (i < leaf - edge) {
            int point = copystring[i + edge] - 'a';
            currentnode->children[point] = new SuffixTreeNode(edge + i, leaf);
        }
    }

// function to search for pattern substring
    void Search(const char *pattern) {
// int to check if the char found or not
        int check = 0;
// int to store subindex
        int subindex;
// calculate length
        int patternsize = strlen(pattern);
// loop on size of string
        for (int i = 0; i < n; ++i) {
// check the index of substring first char on the original string
            if (copystring[i] == pattern[0]) {
                subindex = i;
// if he found start loop on substring
                for (int j = 0; j < patternsize; ++j) {
// check common char
                    if (copystring[subindex] == pattern[j]) {
                        subindex++;
// if he found turn check to 1
                        check = 1;
                    }
                }
                if (check) {
// if he less than 10 print i
                    if (i < 10) {
                        cout << i << " ";
                    }
// if he more than 10 print modules i
                    else {
                        cout << i % 10 << " ";
                    }
                }
            }
        }
        cout << '\n';
    }

// destructor to delete the root node
    ~SuffixTree() {
        delete root;
    }
};


int main() {

    cout << "First Test Case " << '\n';
    SuffixTree t("bananabanaba$");
    t.Search("ana"); // Prints: 1 3 7
    t.Search("naba"); // Prints: 4 8
    t.Search("ban");// Prints: 0 6
    cout << "//////////////////////////////////" << '\n';
    cout << "Second Test Case " << '\n';
    SuffixTree t1("papatpaptpa$");
    t1.Search("ap"); // Prints: 1 6
    t1.Search("tpa"); // Prints: 4 8
    t1.Search("pap");// Prints: 0 5
    cout << "//////////////////////////////////" << '\n';
    cout << "Third Test Case " << '\n';
    SuffixTree t2("omaromar$");
    t2.Search("om"); // Prints: 0 4
    t2.Search("ar"); // Prints: 2 6
    t2.Search("mar");// Prints: 1 5
    cout << "//////////////////////////////////" << '\n';
    cout << "Fourth Test Case " << '\n';
    SuffixTree t3("omnmnmomnmom$");
    t3.Search("omn"); // Prints: 0 6
    t3.Search("mom"); // Prints: 5 9
    t3.Search("omnmo");// Prints: 6
    cout << "//////////////////////////////////" << '\n';
    cout << "FiFth Test Case " << '\n';
    SuffixTree t4("ahmedmohamedsallam$");
    t4.Search("hmed"); // Prints: 1
    t4.Search("am"); // Prints: 8 6
    t4.Search("med"); // Prints: 2 9
    cout << "//////////////////////////////////" << '\n';
    cout << "SIXTH Test Case " << '\n';
    SuffixTree t5("ababcababadb$");
    t5.Search("ab"); // Prints: 0 2 5 7
    t5.Search("db"); // Prints: 0
    t5.Search("bab"); // Prints: 1 6
    cout << "//////////////////////////////////" << '\n';
    cout << "Seventh Test Case " << '\n';
    SuffixTree t6("xoxoxoxoxxo$");
    t6.Search("xo"); // Prints: 0 2 4 6 9
    t6.Search("ox"); // Prints: 1 3 5 7
    t6.Search("xx"); // Prints: 8
    cout << "//////////////////////////////////" << '\n';
    cout << "Eighth Test Case " << '\n';
    SuffixTree t7("roaaelraawy$");
    t7.Search("aa"); // Prints: 2 7
    t7.Search("ro"); // Prints: 0
    t7.Search("wy"); // Prints: 9
    cout << "//////////////////////////////////" << '\n';
    cout << "NINTH Test Case " << '\n';
    SuffixTree t8("gemygemy$");
    t8.Search("em"); // Prints: 1 5
    t8.Search("gem"); // Prints: 0 4
    t8.Search("emy"); // Prints: 1 5
    cout << "//////////////////////////////////" << '\n';
    cout << "TENTH Test Case " << '\n';
    SuffixTree t9("finishfinish$");
    t9.Search("ini"); // Prints: 1 7
    t9.Search("ish$"); // Prints: 9
    t9.Search("fi"); // Prints: 0 6
    return 0;
}
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Node {
    public:
        int index = -1;
        int token;
        int token_sec = 0;
        vector <Node> children;
        int children_size = 0;
};

class Tree {
    public:
        Node root;
        int size = 0;
        void create_trie();
        void match_prefix(Node *current, int c1, int c2, FILE *input, FILE *output);
        bool get_sequence(Node *current, int n, int c1, int c2, int *code, int id, ostream &output);
};

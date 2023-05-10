#include <getopt.h>
#include <cstring>
#include "trie.hpp"
using namespace std;

void uso() {
    cout << "Erro na passagem de linha de comando!" << endl;
    cout << "-c < arquivo de entrada com a extensao txt para ser compactado >" << endl;
    cout << "-x < arquivo de entrada com a extensao z78 para ser descompactado >" << endl;
    cout << "-o < nome do arquivo de saida >" << endl;
    return;
}

int main(int argc, char **argv) {
    extern char *optarg;
    int c;
    FILE *input_txt;
    FILE *input_bin;
    char output_name[100];
    char input_name[100];
    bool c_pass = false;
    bool x_pass = false;
    bool o_pass = false;
    while ((c = getopt(argc, argv, "c:x:o:")) != EOF) {
        switch (c) {
            case 'c':
                strcpy(input_name, optarg);
                input_txt = fopen(optarg, "r");
                c_pass = true;
                break;
            case 'x':
                strcpy(input_name, optarg);
                input_bin = fopen(optarg, "rb");
                x_pass = true;
                break;
            case 'o':
                strcpy(output_name, optarg);
                o_pass = true;
                break;
            default:
                uso();
                exit(1);
        }
    }
    if (c_pass) {
        FILE *output;
        if (o_pass) {
            output = fopen(output_name, "wb");
        } else {
            input_name[strlen(input_name) - 1] = '8';
            input_name[strlen(input_name) - 2] = '7';
            input_name[strlen(input_name) - 3] = 'z';
            output = fopen(input_name, "wb");
        }
        Tree t;
        int c1 = 0;
        int c2 = 0;
        t.create_trie();
        while ((c1 = getc(input_txt)) != EOF) {
            if (c1 == 195) {
                c2 = getc(input_txt);
            }
            t.match_prefix(&t.root, c1, c2, input_txt, output);
            c2 = 0;
        }
        fclose(input_txt);
        fclose(output);
    } else if (x_pass) {
        ofstream output;
        if (o_pass) {
            output.open(output_name, ofstream::out);
        } else {
            input_name[strlen(input_name) - 1] = 't';
            input_name[strlen(input_name) - 2] = 'x';
            input_name[strlen(input_name) - 3] = 't';
            output.open(input_name, ofstream::out);
        }
        Tree t;
        int n;
        int c1 = 0;
        int c2 = 0;
        int *s = NULL;
        t.create_trie();
        while(fread(&n, sizeof(int), 1, input_bin)) {
            fread(&c1, sizeof(char), 1, input_bin);
            if (c1 == 195) {
                fread(&c2, sizeof(char), 1, input_bin);
            }
            t.get_sequence(&t.root, n, c1, c2, s, 0, output);
            c2 = 0;
        }
        cout << t.size << endl;
        fclose(input_bin);
        output.close();
    }
    return 0;
}

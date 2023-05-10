#include "trie.hpp"

void print_special(int c1, int c2, ostream &output) {
    if (c1 == 195) {
        switch (c2) {
            case 128:
                output << "À";
                break;
            case 129:
                output << "Á";
                break;
            case 130:
                output << "Â";
                break;
            case 131:
                output << "Ã";
                break;
            case 132:
                output << "Ä";
                break;
            case 160:
                output << "à";
                break;
            case 161:
                output << "á";
                break;
            case 162:
                output << "â";
                break;
            case 163:
                output << "ã";
                break;
            case 164:
                output << "ä";
                break;
//////////////////////
            case 136:
                output << "È";
                break;
            case 137:
                output << "É";
                break;
            case 138:
                output << "Ê";
                break;
            case 139:
                output << "Ë";
                break;
            case 168:
                output << "è";
                break;
            case 169:
                output << "é";
                break;
            case 170:
                output << "ê";
                break;
            case 171:
                output << "ë";
                break;
//////////////////////
            case 140:
                output << "Ì";
                break;
            case 141:
                output << "Í";
                break;
            case 142:
                output << "Î";
                break;
            case 143:
                output << "Ï";
                break;
            case 172:
                output << "ì";
                break;
            case 173:
                output << "í";
                break;
            case 174:
                output << "î";
                break;
            case 175:
                output << "ï";
                break;
//////////////////////
            case 146:
                output << "Ò";
                break;
            case 147:
                output << "Ó";
                break;
            case 148:
                output << "Ô";
                break;
            case 149:
                output << "Õ";
                break;
            case 150:
                output << "Ö";
                break;
            case 178:
                output << "ò";
                break;
            case 179:
                output << "ó";
                break;
            case 180:
                output << "ô";
                break;
            case 181:
                output << "õ";
                break;
            case 182:
                output << "ö";
                break;
//////////////////////
            case 153:
                output << "Ù";
                break;
            case 154:
                output << "Ú";
                break;
            case 155:
                output << "Û";
                break;
            case 156:
                output << "Ü";
                break;
            case 185:
                output << "ù";
                break;
            case 186:
                output << "ú";
                break;
            case 187:
                output << "û";
                break;
            case 188:
                output << "ü";
                break;
//////////////////////
            case 135:
                output << "Ç";
                break;
            case 167:
                output << "ç";
                break;
        }
    }
}

void Tree::create_trie() {
    root.index = 0;
    root.token = '\0';
    root.children_size = 0;
    size++;
}

void Tree::match_prefix(Node *current, int c1, int c2, FILE *input, FILE *output) {
    int next = 0;
    int next2 = 0;
    bool found = false;
    Node new_child;
    for (int i = 0; i < current->children_size; i++) {
        if (current->children[i].token == c1 && current->children[i].token_sec == c2) {
            found = true;
            next = getc(input);
            if (next == 195) {
                next2 = getc(input);
            }
            if (next != EOF) {
                match_prefix(&current->children[i], next, next2, input, output);
            } else {
                fwrite(&current->index, sizeof(int), 1, output);
            }
        }
    }
    if (!found) {
        fwrite(&current->index, sizeof(int), 1, output);
        fwrite(&c1, sizeof(char), 1, output);
        if (c2 != 0) {
            fwrite(&c2, sizeof(char), 1, output);
        }
        new_child.index = size;
        new_child.token = c1;
        new_child.token_sec = c2;
        size++;
        current->children.push_back(new_child);
        current->children_size++;
    }
}

bool Tree::get_sequence(Node *current, int n, int c1, int c2, int *code, int id, ostream &output) {
    if (current->index == n) {
        Node new_child;
        new_child.token = c1;
        new_child.token_sec = c2;
        new_child.index = size;
        size++;
        current->children.push_back(new_child);
        current->children_size++;
        for (int i = 0; i < id; i++) {
            if (code[i] != 195) {
                if (char(code[i]) != '\0') {
                    output << char(code[i]);
                }
            } else {
                print_special(code[i], code[i + 1], output);
                i++;
            }
        }
        if (current->token != 195) {
            if (char(current->token) != '\0') {
                output << char(current->token);
            }
        } else {
            print_special(current->token, current->token_sec, output);
        }
        if (c1 != 195) {
            if (char(c1) != '\0') {
                output << char(c1);
            }
        } else {
            print_special(c1, c2, output);
        }
        return true;
    } else {
        bool found = false;
        int sz = 0;
        if (current->token != 195) {
            sz = id + 1;
        } else {
            sz = id + 2;
        }
        int new_code[sz];
        int new_id = id;
        for (int i = 0; i < id; i++) {
            new_code[i] = code[i];
        }
        if (current->token != 195) {
            new_code[id] = current->token;
            new_id++;
        } else {
            new_code[id] = current->token;
            new_code[id + 1] = current->token_sec;
            new_id = new_id + 2;
        }
        for (int i = 0; i < current->children_size; i++) {
            found = get_sequence(&current->children[i], n, c1, c2, new_code, new_id, output);
            if (found) {
                break;
            }
        }
        return false;
    }
}

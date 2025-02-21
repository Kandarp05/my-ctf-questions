#include <iostream>
#include <string>
#include <unordered_map>
#include <random>
#include <algorithm>

using namespace std;

std::unordered_map<char, char> substitution_table = {
    {'_', 'E'}, {'}', 'S'}, {'{', 'I'}, {'9', '7'}, {'8', 'Z'},
    {'7', 'r'}, {'C', 'H'}, {'B', 'P'}, {'A', 'h'}, {'z', '}'},
    {'y', 'b'}, {'x', 't'}, {'w', 'v'}, {'v', 'f'}, {'u', '3'},
    {'t', 'w'}, {'s', 'W'}, {'r', 'F'}, {'q', 'x'}, {'6', 'B'},
    {'p', 'J'}, {'5', '5'}, {'o', 'Y'}, {'4', 'V'}, {'n', 's'},
    {'3', 'c'}, {'a', 'u'}, {'b', '{'}, {'c', 'M'}, {'d', '9'},
    {'e', 'y'}, {'f', 'k'}, {'g', 'l'}, {'h', 'R'}, {'i', '8'},
    {'j', 'G'}, {'k', 'C'}, {'0', '_'}, {'l', 'g'}, {'1', 'n'},
    {'m', 'j'}, {'2', 'X'}, {'D', 'U'}, {'E', '1'}, {'F', 'L'},
    {'G', 'm'}, {'H', '4'}, {'I', '0'}, {'J', 'i'}, {'K', 'D'},
    {'L', '6'}, {'M', 'o'}, {'N', 'a'}, {'O', 'N'}, {'P', 'Q'},
    {'Q', 'z'}, {'R', 'q'}, {'S', 'T'}, {'T', 'd'}, {'U', '2'},
    {'V', 'p'}, {'W', 'O'}, {'X', 'A'}, {'Y', 'e'}, {'Z', 'K'}
};

const int SEED = 42;

void substitute(char* flag_array, int size) {
    for(size_t i = 0; i < size; i++) {
        flag_array[i] = substitution_table[flag_array[i]];
    }
}

void insertDummies(char*& flag_array, int &size) {
    const string dummies = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_{}";
    mt19937 rng(SEED);
    uniform_int_distribution<size_t> dist(0, dummies.size() - 1);

    int index = 0;
    vector<char> result;
    while(index < size) {
        result.push_back(flag_array[index]);

        if(index++ % 3 == 0) {
            result.push_back(dummies[dist(rng)]);
        }
    }

    size = result.size();
    flag_array = new char[size + 1];
    copy(result.begin(), result.end(), flag_array);
    flag_array[size] = '\0';
}

void rotate(char *flag_array, int size) {
    for(size_t i = 0; i < size; i++) {
        flag_array[i] = flag_array[i] % 64;
    }
}

int main(int argc, char** argv) {
    string flag;
    if(argc == 2) {
        flag = argv[1];
    } else {
        cout << "Usage: " << argv[0] << " <flag>" << endl;
        return 1;
    }
    int flag_length = flag.length();

    char* flag_array = new char[flag_length + 1];
    copy(flag.begin(), flag.end(), flag_array);
    flag_array[flag_length] = '\0';

    substitute(flag_array, flag_length);
    insertDummies(flag_array, flag_length);
    rotate(flag_array, flag_length);

    for(size_t i = 0; i < flag_length; i++) {
        cout << int(flag_array[i]) << " ";
    }
    cout << endl;
}
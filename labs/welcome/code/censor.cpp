#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv) {

    if(argc == 2) {
        size_t reference = stoi(argv[1]);
        string line;
        getline(cin, line);
        size_t length = line.length();
        string result = "";
        string word = "";
        for(size_t i = 0; i < length; ++i) {
            if(line[i] != ' ' && line[i] != '\t') {
                word += line[i];
            }
            else {
                if(word.length() != reference && word.length() != 0) {
                    result += word;
                    result += ' ';
                    word = "";
                }
                word = "";
            }
            if(i == length - 1 && line[i] != ' ' && word.length() != reference) {
                result += word;
                result += ' ';
            }
        }
        string real = result.substr(0, result.length() - 1);
        cout << real << '\n';
    }

    else {
        cout << "USAGE: censor [length]" << '\n';
        return 1;
    }

    return 0;

}
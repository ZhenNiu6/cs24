#include <iostream>
#include <cctype>

int main(int argc, char** argv){
    if(argc != 2){
        std::cout << "USAGE: censor [length]\n";
        return 1;
    }
    size_t num = stoi(std::string(argv[1]));
    std::string line;
    std::getline(std::cin, line);
    std::string word = "";
    size_t count = 0;
    for(size_t i = 0; i < line.length(); i ++){
        if(!std::isspace(line[i])){
            word += line[i];
            continue;
        }
        if((word != "") && (word.length() != num)){
            if(count != 0){
                std::cout << " ";
            }
            std::cout << word;
            count ++;
        }
        word = "";
    }
    if((word != "") && (word.length() != num)){
        if(count != 0){
            std::cout << " ";
        }
        std::cout << word;
    }
    std::cout << '\n';
    return 0;

}
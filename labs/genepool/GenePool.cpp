#include "GenePool.h"

// GenePool Member Functions

GenePool::GenePool(std::istream& stream) {
    stream.seekg (0, stream.end);
    int length = stream.tellg();
    stream.seekg (0, stream.beg);
    char line[length];
    while(stream.getline(line, length)){
        if(line[0] == '#' || line[0] == '\0') {
            continue;
        }
        istringstream line_stream(line);
        string token;
        int line_index = 0;
        string line_name = "";
        string line_gender = "";
        string line_father = "";
        string line_mother = "";
        while(getline(line_stream, token, '\t')) {
            if(line_index == 0) {
                line_name = token;
            }
            else if(line_index == 1) {
                line_gender = token;
            }
            else if(line_index == 2) {
                line_mother = token;
            }
            else if(line_index == 3) {
                line_father = token;
            }
            line_index += 1;
        }
        // cout << line_name << ", " << line_gender << ", " << line_father << ", " << line_mother << '\n';
        Person* current_person = new Person();
        current_person->mName = line_name;
        if(line_gender == "male") {
            current_person->mGender = Gender::MALE;
        }
        else {
            current_person->mGender = Gender::FEMALE;
        }
        if(line_father == "???" || find(line_father) == nullptr) {
            current_person->mFather = nullptr;
        }
        else {
            current_person->mFather = find(line_father);
        }
        if(line_mother == "???" || find(line_mother) == nullptr) {
            current_person->mMother = nullptr;
        }
        else {
            current_person->mMother = find(line_mother);
        }

        if(line_father != "???") {
            current_person->mFather->mChild.insert(current_person);
        }
        if(line_mother != "???") {
            current_person->mMother->mChild.insert(current_person);
        }       
        tree[line_name] = current_person;
    }
}

GenePool::~GenePool() {
    for(auto& person:tree){
        delete person.second;
    }
    tree.clear();
}

std::set<Person*> GenePool::everyone() const {
    set<Person*> result;
    for(auto iter = tree.begin(); iter != tree.end(); ++iter) {
        result.insert(iter->second);
    }
    return result;
}

Person* GenePool::find(const std::string& name) const {
    auto iter = tree.find(name);
    if (iter != tree.end()) {
        return iter->second;
    } 
    else {
        return nullptr;
    }
}
#include "GenePool.h"
#include "Enums.h"
#include <iostream>
#include <sstream>

// GenePool Member Functions
GenePool::GenePool(std::istream& stream){
    // std::cout << "called" << '\n';
    pool = std::map<std::string, Person*>();
    std::string line;
    // while(std::getline(stream, line)){
    //     std::istringstream linestream(line);
    //     std::string word;
    //     std::getline(linestream, word, '\t');
    //     Person* person = new Person();
    //     pool[word] = person;
    // }  
    while (std::getline(stream, line)) {
        if((line[0] == '#') || (line.empty())){
            continue;
        }
        std::istringstream linestream(line);
        std::string name, gender_str, motherName, fatherName;

        // linestream >> name >> gender_str >> motherName >> fatherName;
        std::getline(linestream, name, '\t');
        std::getline(linestream, gender_str, '\t');
        std::getline(linestream, motherName, '\t');
        std::getline(linestream, fatherName, '\t');
        Gender gender;
        if(gender_str == "male"){
            gender = Gender::MALE;
        }
        else if(gender_str == "female"){
            gender = Gender::FEMALE;
        }
        else{
            gender = Gender::ANY;
        }
        Person* mother = nullptr;
        if(motherName != "???"){
            mother = pool[motherName];
        }
        Person* father = nullptr;
        if(fatherName != "???"){
            father = pool[fatherName];
        }
        // Create new Person object
        Person* person = new Person(name, gender, mother, father);
        pool[name] = person;
        if(mother){
            mother->add_child(person);
        }
        if(father){
            father->add_child(person);
        }
        // std::cout << person->name() << " " << person << '\n';
        // std::cout << person << '\n';
    }
    for(auto itr = pool.begin(); itr != pool.end();) {
        if(itr->second == nullptr) {
            itr = pool.erase(itr);
        } else {
            itr ++;
        }
    }
}

GenePool::~GenePool(){
    for(const auto& pair: pool){
        delete pair.second;
    }
    pool.clear();
}


std::set<Person*> GenePool::everyone() const{
    // std::cout << "called" << '\n';
    std::set<Person*> people;
    for(const auto& pair: pool){
        // std::cout << "here" << '\n';
        people.insert(pair.second);
        
    }
    return people;
}

Person* GenePool::find(const std::string& name) const{
    auto itr = pool.find(name);
    if(itr != pool.end()){
        return itr->second;
    }
    return nullptr;
}
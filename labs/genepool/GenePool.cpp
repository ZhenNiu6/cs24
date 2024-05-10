#include "GenePool.h"

// GenePool Member Functions
GenePool::GenePool(std::istream& stream){
    pool = std::map<std::string, Person*>();
}

GenePool::~GenePool(){
    for(const auto& pair: pool){
        delete pair.second;
    }
}


std::set<Person*> GenePool::everyone() const{
    std::set<Person*> people;
    for(const auto& pair: pool){
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
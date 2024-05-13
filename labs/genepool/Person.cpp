#include "Person.h"

// Person Member Functions
Person::Person(){
    mName = "";
    mGender = Gender::ANY;
    mMother = nullptr;
    mFather = nullptr;
    // mChildren = std::set<Person*>();
}

Person::Person(std::string name, Gender gender, Person* mother, Person* father){
    mName = name;
    mGender = gender;
    mMother = mother;
    mFather = father;
}

Person::~Person(){
    // delete mMother;
    // delete mFather;
    // for(auto child: mChildren){
    //     delete child;
    // }
}

const std::string& Person::name() const{
    return mName;
}

Gender Person::gender() const{
    return mGender;
}

Person* Person::mother(){
    return mMother;
}

Person* Person::father(){
    return mFather;
}

std::set<Person*> Person::ancestors(PMod pmod){
    std::set<Person*> x;
    return x;
}

std::set<Person*> Person::aunts(PMod pmod, SMod smod){
    std::set<Person*> x;
    return x;
}
std::set<Person*> Person::brothers(PMod pmod, SMod smod){
    std::set<Person*> x;
    return x;
}
std::set<Person*> Person::children(){
    std::set<Person*> x;
    return x;
}
std::set<Person*> Person::cousins(PMod pmod, SMod smod){
    std::set<Person*> x;
    return x;
}
std::set<Person*> Person::daughters(){
    std::set<Person*> x;
    return x;
}
std::set<Person*> Person::descendants(){
    std::set<Person*> x;
    return x;
}
std::set<Person*> Person::grandchildren(){
    std::set<Person*> x;
    return x;
}
std::set<Person*> Person::granddaughters(){
    std::set<Person*> x;
    return x;
}
std::set<Person*> Person::grandfathers(PMod pmod){
    std::set<Person*> x;
    return x;
}
std::set<Person*> Person::grandmothers(PMod pmod){
    std::set<Person*> x;
    return x;
}
std::set<Person*> Person::grandparents(PMod pmod){
    std::set<Person*> x;
    return x;
}
std::set<Person*> Person::grandsons(){
    std::set<Person*> x;
    return x;
}
std::set<Person*> Person::nephews(PMod pmod, SMod smod){
    std::set<Person*> x;
    return x;
}
std::set<Person*> Person::nieces(PMod pmod, SMod smod){
    std::set<Person*> x;
    return x;
}
std::set<Person*> Person::parents(PMod pmod){
    std::set<Person*> x;
    return x;
}
std::set<Person*> Person::siblings(PMod pmod, SMod smod){
    std::set<Person*> x;
    return x;
}
std::set<Person*> Person::sisters(PMod pmod, SMod smod){
    std::set<Person*> x;
    return x;
}
std::set<Person*> Person::sons(){
    std::set<Person*> x;
    return x;
}
std::set<Person*> Person::uncles(PMod pmod, SMod smod){
    std::set<Person*> x;
    return x;
}
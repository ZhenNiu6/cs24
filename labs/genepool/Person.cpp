#include "Person.h"

// Person Member Functions

Person::Person() {
    mName = "";
    mGender = Gender::ANY;
    mFather = nullptr;
    mMother = nullptr;
    set<Person*> child_set;
    mChild = child_set;
}

const std::string& Person::name() const {
    return mName;
}

Gender Person::gender() const {
    return mGender;
}

Person* Person::mother() {
    return mMother;
}

Person* Person::father() {
    return mFather;
}

void ancestors_helper(Person* current_person, set<Person*>& result) {
    if(current_person->mother() == nullptr && current_person->father() == nullptr) {
        result.insert(current_person);
    }
    else {
        if(current_person->mother() != nullptr) {
            ancestors_helper(current_person->mother(), result);
        }
        if(current_person->father() != nullptr) {
            ancestors_helper(current_person->father(), result);
        }
        result.insert(current_person);
    }
}

std::set<Person*> Person::ancestors(PMod pmod) {
    set<Person*> result;
    if(pmod == PMod::MATERNAL) {
        Person* mom = mother();
        ancestors_helper(mom, result);
    }
    else if(pmod == PMod::PATERNAL) {
        Person* dad = father();
        ancestors_helper(dad, result);
    }
    else {
        Person* mom = mother();
        ancestors_helper(mom, result);
        Person* dad = father();
        ancestors_helper(dad, result);
    }
    return result;
}

std::set<Person*> Person::aunts(PMod pmod, SMod smod) {
    set<Person*> result;
    if(pmod == PMod::MATERNAL) {
        Person* mom = mother();
        if(mom == nullptr) {
            return result;
        }
        if(smod == SMod::FULL) {
            result = mom->sisters(PMod::ANY, SMod::FULL);
        }
        else if(smod == SMod::HALF) {
            result = mom->sisters(PMod::ANY, SMod::HALF);
        }
        else {
            result = mom->sisters(PMod::ANY, SMod::ANY);
        }
    }
    else if(pmod == PMod::PATERNAL) {
        Person* dad = father();
        if(dad == nullptr) {
            return result;
        }
        if(smod == SMod::FULL) {
            result = dad->sisters(PMod::ANY, SMod::FULL);
        }
        else if(smod == SMod::HALF) {
            result = dad->sisters(PMod::ANY, SMod::HALF);
        }
        else {
            result = dad->sisters(PMod::ANY, SMod::ANY);
        }
    }
    else {
        Person* mom = mother();
        Person* dad = father();
        if(smod == SMod::FULL) {
            if(mom != nullptr) {
                result = mom->sisters(PMod::ANY, SMod::FULL);
            }
            if(dad != nullptr) {
                set<Person*> result1 = dad->sisters(PMod::ANY, SMod::FULL);
                set<Person*>::iterator itr;
                for(itr = result1.begin(); itr != result1.end(); ++itr) {
                    result.insert(*itr);
                }
            }
        }
        else if(smod == SMod::HALF) {
            if(mom != nullptr) {
                result = mom->sisters(PMod::ANY, SMod::HALF);
            }
            if(dad != nullptr) {
                    set<Person*> result1 = dad->sisters(PMod::ANY, SMod::HALF);
                set<Person*>::iterator itr;
                for(itr = result1.begin(); itr != result1.end(); ++itr) {
                    result.insert(*itr);
                }
            }
        }
        else {
            if(mom != nullptr) {
                result = mom->sisters(PMod::ANY, SMod::ANY);
            }
            if(dad != nullptr) {
                set<Person*> result1 = dad->sisters(PMod::ANY, SMod::ANY);
                set<Person*>::iterator itr;
                for(itr = result1.begin(); itr != result1.end(); ++itr) {
                    result.insert(*itr);
                }
            }
        }
    }
    return result;
}

std::set<Person*> Person::brothers(PMod pmod, SMod smod) {
    set<Person*> result;
    set<Person*> sib = siblings(pmod, smod);
    set<Person*>::iterator itr;
    for(itr = sib.begin(); itr != sib.end(); ++itr) {
        Person* mysib = *itr;
        if(mysib->mGender == Gender::MALE) {
            result.insert(mysib);
        }
    }
    return result;
}

std::set<Person*> Person::children() {
    set<Person*> result;
    set<Person*>::iterator itr;
    for(itr = mChild.begin(); itr != mChild.end(); ++itr) {
        result.insert(*itr);
    }
    return result;
}

std::set<Person*> Person::cousins(PMod pmod, SMod smod) {
    set<Person*> result;
    if(pmod == PMod::MATERNAL) {
        Person* mom = mother();
        if(mom != nullptr) {
            if(smod == SMod::FULL) {
                set<Person*> mom_aunt = aunts(PMod::MATERNAL, SMod::FULL);
                set<Person*> mom_uncle = uncles(PMod::MATERNAL, SMod::FULL);
                set<Person*>::iterator aunt_itr;
                set<Person*>::iterator uncle_itr;
                for(aunt_itr = mom_aunt.begin(); aunt_itr != mom_aunt.end(); ++aunt_itr) {
                    Person* myaunt = *aunt_itr;
                    set<Person*> aunt_child = myaunt->children();
                    set<Person*>::iterator aunt_child_itr;
                    for(aunt_child_itr = aunt_child.begin(); aunt_child_itr != aunt_child.end(); ++aunt_child_itr) {
                        result.insert(*aunt_child_itr);
                    }
                }
                for(uncle_itr = mom_uncle.begin(); uncle_itr != mom_uncle.end(); ++uncle_itr) {
                    Person* myuncle = *uncle_itr;
                    set<Person*> uncle_child = myuncle->children();
                    set<Person*>::iterator uncle_child_itr;
                    for(uncle_child_itr = uncle_child.begin(); uncle_child_itr != uncle_child.end(); ++uncle_child_itr) {
                        result.insert(*uncle_child_itr);
                    }
                }
            }
            else if(smod == SMod::HALF) {
                set<Person*> mom_aunt = aunts(PMod::MATERNAL, SMod::HALF);
                set<Person*> mom_uncle = uncles(PMod::MATERNAL, SMod::HALF);
                set<Person*>::iterator aunt_itr;
                set<Person*>::iterator uncle_itr;
                for(aunt_itr = mom_aunt.begin(); aunt_itr != mom_aunt.end(); ++aunt_itr) {
                    Person* myaunt = *aunt_itr;
                    set<Person*> aunt_child = myaunt->children();
                    set<Person*>::iterator aunt_child_itr;
                    for(aunt_child_itr = aunt_child.begin(); aunt_child_itr != aunt_child.end(); ++aunt_child_itr) {
                        result.insert(*aunt_child_itr);
                    }
                }
                for(uncle_itr = mom_uncle.begin(); uncle_itr != mom_uncle.end(); ++uncle_itr) {
                    Person* myuncle = *uncle_itr;
                    set<Person*> uncle_child = myuncle->children();
                    set<Person*>::iterator uncle_child_itr;
                    for(uncle_child_itr = uncle_child.begin(); uncle_child_itr != uncle_child.end(); ++uncle_child_itr) {
                        result.insert(*uncle_child_itr);
                    }
                }
            }
            else {
                set<Person*> mom_aunt = aunts(PMod::MATERNAL, SMod::ANY);
                set<Person*> mom_uncle = uncles(PMod::MATERNAL, SMod::ANY);
                set<Person*>::iterator aunt_itr;
                set<Person*>::iterator uncle_itr;
                for(aunt_itr = mom_aunt.begin(); aunt_itr != mom_aunt.end(); ++aunt_itr) {
                    Person* myaunt = *aunt_itr;
                    set<Person*> aunt_child = myaunt->children();
                    set<Person*>::iterator aunt_child_itr;
                    for(aunt_child_itr = aunt_child.begin(); aunt_child_itr != aunt_child.end(); ++aunt_child_itr) {
                        result.insert(*aunt_child_itr);
                    }
                }
                for(uncle_itr = mom_uncle.begin(); uncle_itr != mom_uncle.end(); ++uncle_itr) {
                    Person* myuncle = *uncle_itr;
                    set<Person*> uncle_child = myuncle->children();
                    set<Person*>::iterator uncle_child_itr;
                    for(uncle_child_itr = uncle_child.begin(); uncle_child_itr != uncle_child.end(); ++uncle_child_itr) {
                        result.insert(*uncle_child_itr);
                    }
                }
            }
        }
    }
    else if(pmod == PMod::PATERNAL) {
        Person* dad = father();
        if(dad != nullptr) {
            if(smod == SMod::FULL) {
                set<Person*> mom_aunt = aunts(PMod::PATERNAL, SMod::FULL);
                set<Person*> mom_uncle = uncles(PMod::PATERNAL, SMod::FULL);
                set<Person*>::iterator aunt_itr;
                set<Person*>::iterator uncle_itr;
                for(aunt_itr = mom_aunt.begin(); aunt_itr != mom_aunt.end(); ++aunt_itr) {
                    Person* myaunt = *aunt_itr;
                    set<Person*> aunt_child = myaunt->children();
                    set<Person*>::iterator aunt_child_itr;
                    for(aunt_child_itr = aunt_child.begin(); aunt_child_itr != aunt_child.end(); ++aunt_child_itr) {
                        result.insert(*aunt_child_itr);
                    }
                }
                for(uncle_itr = mom_uncle.begin(); uncle_itr != mom_uncle.end(); ++uncle_itr) {
                    Person* myuncle = *uncle_itr;
                    set<Person*> uncle_child = myuncle->children();
                    set<Person*>::iterator uncle_child_itr;
                    for(uncle_child_itr = uncle_child.begin(); uncle_child_itr != uncle_child.end(); ++uncle_child_itr) {
                        result.insert(*uncle_child_itr);
                    }
                }
            }
            else if(smod == SMod::HALF) {
                set<Person*> mom_aunt = aunts(PMod::PATERNAL, SMod::HALF);
                set<Person*> mom_uncle = uncles(PMod::PATERNAL, SMod::HALF);
                set<Person*>::iterator aunt_itr;
                set<Person*>::iterator uncle_itr;
                for(aunt_itr = mom_aunt.begin(); aunt_itr != mom_aunt.end(); ++aunt_itr) {
                    Person* myaunt = *aunt_itr;
                    set<Person*> aunt_child = myaunt->children();
                    set<Person*>::iterator aunt_child_itr;
                    for(aunt_child_itr = aunt_child.begin(); aunt_child_itr != aunt_child.end(); ++aunt_child_itr) {
                        result.insert(*aunt_child_itr);
                    }
                }
                for(uncle_itr = mom_uncle.begin(); uncle_itr != mom_uncle.end(); ++uncle_itr) {
                    Person* myuncle = *uncle_itr;
                    set<Person*> uncle_child = myuncle->children();
                    set<Person*>::iterator uncle_child_itr;
                    for(uncle_child_itr = uncle_child.begin(); uncle_child_itr != uncle_child.end(); ++uncle_child_itr) {
                        result.insert(*uncle_child_itr);
                    }
                }
            }
            else {
                set<Person*> mom_aunt = aunts(PMod::PATERNAL, SMod::ANY);
                set<Person*> mom_uncle = uncles(PMod::PATERNAL, SMod::ANY);
                set<Person*>::iterator aunt_itr;
                set<Person*>::iterator uncle_itr;
                for(aunt_itr = mom_aunt.begin(); aunt_itr != mom_aunt.end(); ++aunt_itr) {
                    Person* myaunt = *aunt_itr;
                    set<Person*> aunt_child = myaunt->children();
                    set<Person*>::iterator aunt_child_itr;
                    for(aunt_child_itr = aunt_child.begin(); aunt_child_itr != aunt_child.end(); ++aunt_child_itr) {
                        result.insert(*aunt_child_itr);
                    }
                }
                for(uncle_itr = mom_uncle.begin(); uncle_itr != mom_uncle.end(); ++uncle_itr) {
                    Person* myuncle = *uncle_itr;
                    set<Person*> uncle_child = myuncle->children();
                    set<Person*>::iterator uncle_child_itr;
                    for(uncle_child_itr = uncle_child.begin(); uncle_child_itr != uncle_child.end(); ++uncle_child_itr) {
                        result.insert(*uncle_child_itr);
                    }
                }
            }
        }
    }
    else {
        if(smod == SMod::FULL) {
            set<Person*> mom_aunt = aunts(PMod::ANY, SMod::FULL);
            set<Person*> mom_uncle = uncles(PMod::ANY, SMod::FULL);
            set<Person*>::iterator aunt_itr;
                set<Person*>::iterator uncle_itr;
                for(aunt_itr = mom_aunt.begin(); aunt_itr != mom_aunt.end(); ++aunt_itr) {
                    Person* myaunt = *aunt_itr;
                    set<Person*> aunt_child = myaunt->children();
                    set<Person*>::iterator aunt_child_itr;
                    for(aunt_child_itr = aunt_child.begin(); aunt_child_itr != aunt_child.end(); ++aunt_child_itr) {
                        result.insert(*aunt_child_itr);
                    }
                }
                for(uncle_itr = mom_uncle.begin(); uncle_itr != mom_uncle.end(); ++uncle_itr) {
                    Person* myuncle = *uncle_itr;
                    set<Person*> uncle_child = myuncle->children();
                    set<Person*>::iterator uncle_child_itr;
                    for(uncle_child_itr = uncle_child.begin(); uncle_child_itr != uncle_child.end(); ++uncle_child_itr) {
                        result.insert(*uncle_child_itr);
                    }
                }
        }
        else if(smod == SMod::HALF) {
            set<Person*> mom_aunt = aunts(PMod::ANY, SMod::HALF);
            set<Person*> mom_uncle = uncles(PMod::ANY, SMod::HALF);
            set<Person*>::iterator aunt_itr;
                set<Person*>::iterator uncle_itr;
                for(aunt_itr = mom_aunt.begin(); aunt_itr != mom_aunt.end(); ++aunt_itr) {
                    Person* myaunt = *aunt_itr;
                    set<Person*> aunt_child = myaunt->children();
                    set<Person*>::iterator aunt_child_itr;
                    for(aunt_child_itr = aunt_child.begin(); aunt_child_itr != aunt_child.end(); ++aunt_child_itr) {
                        result.insert(*aunt_child_itr);
                    }
                }
                for(uncle_itr = mom_uncle.begin(); uncle_itr != mom_uncle.end(); ++uncle_itr) {
                    Person* myuncle = *uncle_itr;
                    set<Person*> uncle_child = myuncle->children();
                    set<Person*>::iterator uncle_child_itr;
                    for(uncle_child_itr = uncle_child.begin(); uncle_child_itr != uncle_child.end(); ++uncle_child_itr) {
                        result.insert(*uncle_child_itr);
                    }
                }
        }
        else {
            set<Person*> mom_aunt = aunts(PMod::ANY, SMod::ANY);
            set<Person*> mom_uncle = uncles(PMod::ANY, SMod::ANY);
            set<Person*>::iterator aunt_itr;
                set<Person*>::iterator uncle_itr;
                for(aunt_itr = mom_aunt.begin(); aunt_itr != mom_aunt.end(); ++aunt_itr) {
                    Person* myaunt = *aunt_itr;
                    set<Person*> aunt_child = myaunt->children();
                    set<Person*>::iterator aunt_child_itr;
                    for(aunt_child_itr = aunt_child.begin(); aunt_child_itr != aunt_child.end(); ++aunt_child_itr) {
                        result.insert(*aunt_child_itr);
                    }
                }
                for(uncle_itr = mom_uncle.begin(); uncle_itr != mom_uncle.end(); ++uncle_itr) {
                    Person* myuncle = *uncle_itr;
                    set<Person*> uncle_child = myuncle->children();
                    set<Person*>::iterator uncle_child_itr;
                    for(uncle_child_itr = uncle_child.begin(); uncle_child_itr != uncle_child.end(); ++uncle_child_itr) {
                        result.insert(*uncle_child_itr);
                    }
                }
        }
    }
    return result;
}

std::set<Person*> Person::daughters() {
    set<Person*> result;
    set<Person*>::iterator itr;
    for(itr = mChild.begin(); itr != mChild.end(); ++itr) {
        Person* child = *itr;
        if(child->mGender == Gender::FEMALE) {
            result.insert(child);
        }
    }
    return result;
}

void descendants_helper(Person* current_person, set<Person*>& result) {
    if(current_person->mChild.size() == 0) {
        result.insert(current_person);
    }
    else {
        set<Person*>::iterator itr;
        for(itr = current_person->mChild.begin(); itr != current_person->mChild.end(); ++itr) {
            Person* child = *itr;
            descendants_helper(child, result);
        }
        result.insert(current_person);
    }
}

std::set<Person*> Person::descendants() {
    set<Person*> result;
    set<Person*>::iterator itr;
    for(itr = mChild.begin(); itr != mChild.end(); ++itr) {
        Person* child = *itr;
        descendants_helper(child, result);
    }
    return result;
}

std::set<Person*> Person::grandchildren() {
    set<Person*> result;
    set<Person*>::iterator itr;
    for(itr = mChild.begin(); itr != mChild.end(); ++itr) {
        Person* child = *itr;
        set<Person*>::iterator children_itr;
        for(children_itr = child->mChild.begin(); children_itr != child->mChild.end(); ++children_itr) {
            result.insert(*children_itr);
        }
    }
    return result;
}

std::set<Person*> Person::granddaughters() {
    set<Person*> result;
    set<Person*>::iterator itr;
    for(itr = mChild.begin(); itr != mChild.end(); ++itr) {
        Person* child = *itr;
        set<Person*>::iterator children_itr;
        for(children_itr = child->mChild.begin(); children_itr != child->mChild.end(); ++children_itr) {
            Person* grandchild = *children_itr;
            if(grandchild->mGender == Gender::FEMALE) {
                result.insert(grandchild);
            }
        }
    }
    return result;
}

std::set<Person*> Person::grandfathers(PMod pmod) {
    set<Person*> result;
    if(pmod == PMod::MATERNAL) {
        Person* mom = mother();
        if(mom != nullptr) {
            if(mom->father() != nullptr) {
                result.insert(mom->father());
            }
        }
    }
    else if(pmod == PMod::PATERNAL) {
        Person* dad = father();
        if(dad != nullptr) {
            if(dad->father() != nullptr) {
                result.insert(dad->father());
            }
        }
    }
    else {
        Person* mom = mother();
        if(mom != nullptr) {
            if(mom->father() != nullptr) {
                result.insert(mom->father());
            }
        }
        Person* dad = father();
        if(dad != nullptr) {
            if(dad->father() != nullptr) {
                result.insert(dad->father());
            }
        }
    }
    return result;
}

std::set<Person*> Person::grandmothers(PMod pmod) {
    set<Person*> result;
    if(pmod == PMod::MATERNAL) {
        Person* mom = mother();
        if(mom != nullptr) {
            if(mom->mother() != nullptr) {
                result.insert(mom->mother());
            }
        }
    }
    else if(pmod == PMod::PATERNAL) {
        Person* dad = father();
        if(dad != nullptr) {
            if(dad->mother() != nullptr) {
                result.insert(dad->mother());
            }
        }
    }
    else {
        Person* mom = mother();
        if(mom != nullptr) {
            if(mom->mother() != nullptr) {
                result.insert(mom->mother());
            }
        }
        Person* dad = father();
        if(dad != nullptr) {
            if(dad->mother() != nullptr) {
                result.insert(dad->mother());
            }
        }
    }
    return result;
}

std::set<Person*> Person::grandparents(PMod pmod) {
    set<Person*> result;
    if(pmod == PMod::MATERNAL) {
        Person* mom = mother();
        if(mom != nullptr) {
            if(mom->mother() != nullptr) {
                result.insert(mom->mother());
            }
            if(mom->father() != nullptr) {
                result.insert(mom->father());
            }
        }
    }
    else if(pmod == PMod::PATERNAL) {
        Person* dad = father();
        if(dad != nullptr) {
            if(dad->mother() != nullptr) {
                result.insert(dad->mother());
            }
            if(dad->father() != nullptr) {
                result.insert(dad->father());
            }
        }
    }
    else {
        Person* mom = mother();
        if(mom != nullptr) {
            if(mom->mother() != nullptr) {
                result.insert(mom->mother());
            }
            if(mom->father() != nullptr) {
                result.insert(mom->father());
            }
        }
        Person* dad = father();
        if(dad != nullptr) {
            if(dad->mother() != nullptr) {
                result.insert(dad->mother());
            }
            if(dad->father() != nullptr) {
                result.insert(dad->father());
            }
        }
    }
    return result;
}

std::set<Person*> Person::grandsons() {
    set<Person*> result;
    set<Person*>::iterator itr;
    for(itr = mChild.begin(); itr != mChild.end(); ++itr) {
        Person* child = *itr;
        set<Person*>::iterator children_itr;
        for(children_itr = child->mChild.begin(); children_itr != child->mChild.end(); ++children_itr) {
            Person* grandchild = *children_itr;
            if(grandchild->mGender == Gender::MALE) {
                result.insert(grandchild);
            }
        }
    }
    return result;
}

std::set<Person*> Person::nephews(PMod pmod, SMod smod) {
    set<Person*> result;
    set<Person*> sib = siblings(pmod, smod);
    set<Person*>::iterator itr;
    for(itr = sib.begin(); itr != sib.end(); ++itr) {
        Person* mysib = *itr;
        set<Person*> mysib_daughter = mysib->sons();
        set<Person*>::iterator mysib_itr;
        for(mysib_itr = mysib_daughter.begin(); mysib_itr != mysib_daughter.end(); ++mysib_itr) {
            Person* myniece = *mysib_itr;
            if(myniece->mGender == Gender::MALE) {
                result.insert(myniece);
            }
        }
    }
    return result;
}

std::set<Person*> Person::nieces(PMod pmod, SMod smod) {
    set<Person*> result;
    set<Person*> sib = siblings(pmod, smod);
    set<Person*>::iterator itr;
    for(itr = sib.begin(); itr != sib.end(); ++itr) {
        Person* mysib = *itr;
        set<Person*> mysib_daughter = mysib->daughters();
        set<Person*>::iterator mysib_itr;
        for(mysib_itr = mysib_daughter.begin(); mysib_itr != mysib_daughter.end(); ++mysib_itr) {
            Person* myniece = *mysib_itr;
            if(myniece->mGender == Gender::FEMALE) {
                result.insert(myniece);
            }
        }
    }
    return result;
}

std::set<Person*> Person::parents(PMod pmod) {
    set<Person*> result;
    if(pmod == PMod::MATERNAL) {
        if(mother() != nullptr) {
            result.insert(mother());
        }
    }
    else if(pmod == PMod::PATERNAL) {
        if(father() != nullptr) {
            result.insert(father());
        }
    }
    else {
        if(mother() != nullptr) {
            result.insert(mother());
        }
        if(father() != nullptr) {
            result.insert(father());
        }
    }
    return result;
}

std::set<Person*> Person::siblings(PMod pmod, SMod smod) {
    set<Person*> result;
    Person* mom = mother();
    Person* dad = father();
    if(mom != nullptr) {
        set<Person*>::iterator itr;
        for(itr = mom->mChild.begin(); itr != mom->mChild.end(); ++itr) {
            Person* sib = *itr;
            if(sib->father() != nullptr) {
                if(sib->father() == dad) {
                    if(smod != SMod::HALF) {
                        if(sib->mName != mName) {
                            result.insert(sib);
                        }
                    }
                    continue;
                }
                else {
                    if(pmod != PMod::PATERNAL && smod != SMod::FULL) {
                        if(sib->mName != mName) {
                            result.insert(sib);
                        }
                    }
                }
            }
            else {
                if(pmod != PMod::PATERNAL && smod != SMod::FULL){
                    if(sib->mName != mName) {
                        result.insert(sib);
                    }
                }
                continue;
            }
        }
    }
    if(dad != nullptr) {
        set<Person*>::iterator itr;
        for(itr = dad->mChild.begin(); itr != dad->mChild.end(); ++itr) {
            Person* sib = *itr;
            if(sib->mother() != nullptr) {
                if(sib->mother() == mom) {
                    if(smod != SMod::HALF) {
                        if(sib->mName != mName) {
                            result.insert(sib);
                        }
                    }
                    continue;
                }
                else {
                    if(pmod != PMod::MATERNAL && smod != SMod::FULL) {
                        if(sib->mName != mName) {
                            result.insert(sib);
                        }
                    }
                }
            }
            else {
                if(pmod != PMod::MATERNAL && smod != SMod::FULL){
                    if(sib->mName != mName) {
                        result.insert(sib);
                    }
                }
                continue;
            }
        }
    }
    return result;
}

std::set<Person*> Person::sisters(PMod pmod, SMod smod) {
    set<Person*> result;
    set<Person*> sib = siblings(pmod, smod);
    set<Person*>::iterator itr;
    for(itr = sib.begin(); itr != sib.end(); ++itr) {
        Person* mysib = *itr;
        if(mysib->mGender == Gender::FEMALE) {
            result.insert(mysib);
        }
    }
    return result;
}

std::set<Person*> Person::sons() {
    set<Person*> result;
    set<Person*>::iterator itr;
    for(itr = mChild.begin(); itr != mChild.end(); ++itr) {
        Person* child = *itr;
        if(child->mGender == Gender::MALE) {
            result.insert(child);
        }
    }
    return result;
}

std::set<Person*> Person::uncles(PMod pmod, SMod smod) {
    set<Person*> result;
    if(pmod == PMod::MATERNAL) {
        Person* mom = mother();
        if(mom == nullptr) {
            return result;
        }
        if(smod == SMod::FULL) {
            result = mom->brothers(PMod::ANY, SMod::FULL);
        }
        else if(smod == SMod::HALF) {
            result = mom->brothers(PMod::ANY, SMod::HALF);
        }
        else {
            result = mom->brothers(PMod::ANY, SMod::ANY);
        }
    }
    else if(pmod == PMod::PATERNAL) {
        Person* dad = father();
        if(dad == nullptr) {
            return result;
        }
        if(smod == SMod::FULL) {
            result = dad->brothers(PMod::ANY, SMod::FULL);
        }
        else if(smod == SMod::HALF) {
            result = dad->brothers(PMod::ANY, SMod::HALF);
        }
        else {
            result = dad->brothers(PMod::ANY, SMod::ANY);
        }
    }
    else {
        Person* mom = mother();
        Person* dad = father();
        if(smod == SMod::FULL) {
            if(mom != nullptr) {
                result = mom->brothers(PMod::ANY, SMod::FULL);
            }
            if(dad != nullptr) {
                set<Person*> result1 = dad->brothers(PMod::ANY, SMod::FULL);
                set<Person*>::iterator itr;
                for(itr = result1.begin(); itr != result1.end(); ++itr) {
                    result.insert(*itr);
                }
            }
        }
        else if(smod == SMod::HALF) {
            if(mom != nullptr) {
                result = mom->brothers(PMod::ANY, SMod::HALF);
            }
            if(dad != nullptr) {
                    set<Person*> result1 = dad->brothers(PMod::ANY, SMod::HALF);
                set<Person*>::iterator itr;
                for(itr = result1.begin(); itr != result1.end(); ++itr) {
                    result.insert(*itr);
                }
            }
        }
        else {
            if(mom != nullptr) {
                result = mom->brothers(PMod::ANY, SMod::ANY);
            }
            if(dad != nullptr) {
                set<Person*> result1 = dad->brothers(PMod::ANY, SMod::ANY);
                set<Person*>::iterator itr;
                for(itr = result1.begin(); itr != result1.end(); ++itr) {
                    result.insert(*itr);
                }
            }
        }
    }
    return result;
}
#include "Person.h"
#include <iostream>

// Person Member Functions
Person::Person(){
    mName = "";
    mGender = Gender::ANY;
    mMother = nullptr;
    mFather = nullptr;
    mChildren = std::set<Person*>();
}

void Person::add_child(Person* child){
    mChildren.insert(child);
}

Person::Person(std::string name, Gender gender, Person* mother, Person* father){
    mName = name;
    mGender = gender;
    mMother = mother;
    mFather = father;
}


Person::~Person(){
    // for(auto parent : {mMother, mFather}) {
    //     if(parent) {
    //         parent->mChildren.erase(this);
    //     }
    // }
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

// std::set<Person*> Person::get_children(){
//     return mChildren;
// }

std::set<Person*> Person::ancestors(PMod pmod){
    std::set<Person*> x;
    if(pmod == PMod::MATERNAL){
        if(mMother != nullptr){
            ancestors_helper(mMother, x);
        }
    }
    else if(pmod == PMod::PATERNAL){
        if(mFather != nullptr){
            ancestors_helper(mFather, x);
        }
    }
    else{
        if(mMother != nullptr){
            ancestors_helper(mMother, x);
        }
        if(mFather != nullptr){
            ancestors_helper(mFather, x);
        }
    }
    return x;
}

void Person::ancestors_helper(Person* person, std::set<Person*>& ancestors){
    if(person == nullptr){
        return;
    }
    ancestors.insert(person);
    ancestors_helper(person->mother(), ancestors);
    ancestors_helper(person->father(), ancestors);
}



std::set<Person*> Person::aunts(PMod pmod, SMod smod){
    std::set<Person*> x;
    if(smod == SMod::FULL){
        if(mMother != nullptr){
            for(auto sister: mMother->sisters(pmod, smod)){
                x.insert(sister);
            }
        }
        if(mFather != nullptr){
            for(auto sister: mFather->sisters(pmod, smod)){
                x.insert(sister);
            }
        }
    }
    else if(smod == SMod::HALF){
        if(pmod == PMod::MATERNAL){
            if(mMother != nullptr){
                // if(mMother->sisters(pmod, smod).size() != 0){
                    for(auto sister: mMother->sisters(pmod, smod)){
                        x.insert(sister);
                    }
                // }
                if(mMother->sisters(pmod = PMod::PATERNAL, smod).size() != 0){
                    for(auto sister: mMother->sisters(pmod = PMod::PATERNAL, smod)){
                        x.insert(sister);
                    }
                }
            }
        }
        else if(pmod == PMod::PATERNAL){
            if(mFather != nullptr){
                for(auto sister: mFather->sisters(pmod, smod)){
                    x.insert(sister);
                }
                for(auto sister: mFather->sisters(pmod = PMod::MATERNAL, smod)){
                    x.insert(sister);
                }
            }
        }
        else{
            if(mMother != nullptr){
                for(auto sister: mMother->sisters(pmod, smod)){
                    x.insert(sister);
                }
                for(auto sister: mMother->sisters(pmod = PMod::PATERNAL, smod)){
                    x.insert(sister);
                }
            }
            if(mFather != nullptr){
                for(auto sister: mFather->sisters(pmod, smod)){
                    x.insert(sister);
                }
                for(auto sister: mFather->sisters(pmod = PMod::MATERNAL, smod)){
                    x.insert(sister);
                }
            }
        }
    }
    else if(pmod == PMod::MATERNAL){
        if(mMother != nullptr){
            for(auto sister: mMother->sisters(pmod, smod)){
                x.insert(sister);
            }
            
            for(auto sister: mMother->sisters(pmod = PMod::PATERNAL, smod)){
                x.insert(sister);
            }
        }
    }
    else if(pmod == PMod::PATERNAL){
        if(mFather != nullptr){
            for(auto sister: mFather->sisters(pmod, smod)){
                x.insert(sister);
            }
            for(auto sister: mFather->sisters(pmod = PMod::MATERNAL, smod)){
                x.insert(sister);
            }
        }
    }
    else{
        if(mMother != nullptr){
            for(auto sister: mMother->sisters(pmod, smod)){
                x.insert(sister);
            }
            
            for(auto sister: mMother->sisters(pmod = PMod::PATERNAL, smod)){
                x.insert(sister);
            }
        }
        if(mFather != nullptr){
            for(auto sister: mFather->sisters(pmod, smod)){
                x.insert(sister);
            }
            for(auto sister: mFather->sisters(pmod = PMod::MATERNAL, smod)){
                x.insert(sister);
            }
        }
    }
    return x;
}
std::set<Person*> Person::brothers(PMod pmod, SMod smod){
    std::set<Person*> x;
    for(auto brother: siblings(pmod, smod)){
        if(brother->gender() == Gender::MALE){
            x.insert(brother);
        }
    }
    return x;
}
std::set<Person*> Person::children(){
    return mChildren;
}
std::set<Person*> Person::cousins(PMod pmod, SMod smod){
    std::set<Person*> x;
    if(smod != SMod::ANY){
        if(pmod == PMod::MATERNAL){
            if(mMother != nullptr){
                for(auto sibling: mMother->siblings(pmod = PMod::ANY, smod)){
                    for(auto cousin: sibling->children()){
                        x.insert(cousin);
                    }
                }
            }
        }
        if(pmod == PMod::PATERNAL){
            if(mFather != nullptr){
                for(auto sibling: mFather->siblings(pmod = PMod::ANY, smod)){
                    for(auto cousin: sibling->children()){
                        x.insert(cousin);
                    }
                }
            }
        }
    }
    else{
        if(pmod == PMod::MATERNAL){
            if(mMother != nullptr){
                for(auto sibling: mMother->siblings(pmod, smod)){
                    for(auto cousin: sibling->children()){
                        x.insert(cousin);
                    }
                }
            }
        }
        else if(pmod == PMod::PATERNAL){
            if(mFather != nullptr){
                for(auto sibling: mFather->siblings(pmod, smod)){
                    for(auto cousin: sibling->children()){
                        x.insert(cousin);
                    }
                }
            }
        }
        else{
            if(mMother != nullptr){
                for(auto sibling: mMother->siblings(pmod, smod)){
                    for(auto cousin: sibling->children()){
                        x.insert(cousin);
                    }
                }
            }
            if(mFather != nullptr){
                for(auto sibling: mFather->siblings(pmod, smod)){
                    for(auto cousin: sibling->children()){
                        x.insert(cousin);
                    }
                }
            }
        }
    }
    return x;
}
std::set<Person*> Person::daughters(){
    std::set<Person*> x;
    for(auto child: mChildren){
        if(child->gender() == Gender::FEMALE){
            x.insert(child);
        }
    }
    return x;
}
std::set<Person*> Person::descendants(){
    std::set<Person*> x;
    x.insert(this);
    descendants_helper(this, x);
    return x;
}

void Person::descendants_helper(Person* person, std::set<Person*>& descendants){
    if(person == nullptr){
        return;
    }
    descendants.insert(person);
    for(auto child: person->children()){
        descendants_helper(child, descendants);
    }
}
std::set<Person*> Person::grandchildren(){
    std::set<Person*> x;
    for(auto child: mChildren){
        if(child->children().size() != 0){
            for(auto grandchild: child->children()){
                x.insert(grandchild);
            }
        }
    }
    return x;
}
std::set<Person*> Person::granddaughters(){
    std::set<Person*> x;
    for(auto grandchild: grandchildren()){
        if(grandchild->gender() == Gender::FEMALE){
            x.insert(grandchild);
        }
    }
    return x;
}
std::set<Person*> Person::grandfathers(PMod pmod){
    std::set<Person*> x;
    auto if_valid = [&x](Person* parent){
        if(parent != nullptr){
            auto grandfather = parent->father();
            if(grandfather != nullptr){
                x.insert(grandfather);
            }
        }
    };
    if(pmod == PMod::MATERNAL){
        if_valid(mMother);
    }
    else if(pmod == PMod::PATERNAL){
        if_valid(mFather);
    }
    else{
        if_valid(mMother);
        if_valid(mFather);
    }
    return x;
}
std::set<Person*> Person::grandmothers(PMod pmod){
    std::set<Person*> x;
    auto if_valid = [&x](Person* parent){
        if(parent != nullptr){
            auto grandmother = parent->mother();
            if(grandmother != nullptr){
                x.insert(grandmother);
            }
        }
    };
    if(pmod == PMod::MATERNAL){
        if_valid(mMother);
    }
    else if(pmod == PMod::PATERNAL){
        if_valid(mFather);
    }
    else{
        if_valid(mMother);
        if_valid(mFather);
    }
    return x;
}
std::set<Person*> Person::grandparents(PMod pmod){
    std::set<Person*> x;
    auto if_valid = [&x](Person* parent){
        if(parent != nullptr){
            auto grandfather = parent->father();
            if(grandfather != nullptr){
                x.insert(grandfather);
            }
            auto grandmother = parent->mother();
            if(grandmother != nullptr){
                x.insert(grandmother);
            }
        }
    };
    if(pmod == PMod::MATERNAL){
        if_valid(mMother);
    }
    else if(pmod == PMod::PATERNAL){
        if_valid(mFather);
    }
    else{
        if_valid(mMother);
        if_valid(mFather);
    }
    return x;
}
std::set<Person*> Person::grandsons(){
    std::set<Person*> x;
    for(auto grandchild: grandchildren()){
        if(grandchild->gender() == Gender::MALE){
            x.insert(grandchild);
        }
    }
    return x;
}
std::set<Person*> Person::nephews(PMod pmod, SMod smod){
    std::set<Person*> x;
    for(auto sibling: siblings(pmod, smod)){
        for(auto nephew: sibling->children()){
            if(nephew->gender() == Gender::MALE){
                x.insert(nephew);
            }
        }
    }
    return x;
}
std::set<Person*> Person::nieces(PMod pmod, SMod smod){
    std::set<Person*> x;
    for(auto sibling: siblings(pmod, smod)){
        for(auto niece: sibling->children()){
            if(niece->gender() == Gender::FEMALE){
                x.insert(niece);
            }
        }
    }
    return x;
}
std::set<Person*> Person::parents(PMod pmod){
    std::set<Person*> x;
    if(pmod == PMod::MATERNAL){
        if(mMother != nullptr){
            x.insert(mMother);
        }
    }
    else if(pmod == PMod::PATERNAL){
        if(mFather != nullptr){
            x.insert(mFather);
        }
    }
    else{
        if(mMother != nullptr){
            x.insert(mMother);
        }
        if(mFather != nullptr){
            x.insert(mFather);
        }
    }
    return x;
}

std::set<Person*> Person::siblings(PMod pmod, SMod smod){
    std::set<Person*> x;
    if(smod == SMod::FULL){
        if((mMother == nullptr) || (mFather == nullptr)){
            return x;
        }
        for(auto m_sibling: mMother->children()){
            for(auto p_sibling: mFather->children()){
                if((m_sibling == p_sibling) && (m_sibling != this)){
                    x.insert(m_sibling);
                }
            }
        }
    }
    else if(smod == SMod::HALF){
        if(pmod == PMod::ANY){
            if((mMother == nullptr) || (mFather == nullptr)){
                if(mMother != nullptr){
                    for(auto m_sibling: mMother->children()){
                        if(m_sibling != this){
                            x.insert(m_sibling);
                        }
                    }
                }
                else if(mFather != nullptr){
                    for(auto p_sibling: mFather->children()){
                        if(p_sibling != this){
                            x.insert(p_sibling);
                        }
                    }
                }
            }
            else{
                for(auto m_sibling: mMother->children()){
                    for(auto p_sibling: mFather->children()){
                        if((m_sibling->mother() == mMother) && (p_sibling->mother() == mMother)
                        && (m_sibling->father() != p_sibling->father()) && (m_sibling != this)
                        && (p_sibling != this)){
                            x.insert(m_sibling);
                        }
                        else if((m_sibling->father() == mFather) && (p_sibling->father() == mFather)
                        && (m_sibling->mother() != p_sibling->mother()) && (m_sibling != this)
                        && (p_sibling != this)){
                            x.insert(p_sibling);
                        }
                    }
                }
            }
        }
        else if(pmod == PMod::MATERNAL){
            if(mMother != nullptr){
                for(auto m_sibling: mMother->children()){
                    if(mFather != nullptr){
                        for(auto p_sibling: mFather->children()){
                            if((m_sibling->mother() == mMother) && (p_sibling->mother() == mMother)
                            && (m_sibling->father() != p_sibling->father()) && (m_sibling != this)
                            && (p_sibling != this)){
                                x.insert(m_sibling);
                            }   
                        }
                    }

                    else{
                        if(m_sibling != this){
                            x.insert(m_sibling);
                        }
                    }
                }
            }
        }
        else if(pmod == PMod::PATERNAL){
            if(mFather != nullptr){
                for(auto p_sibling: mFather->children()){
                    if(mMother != nullptr){
                        for(auto m_sibling: mMother->children()){
                            if((m_sibling->father() == mFather) && (p_sibling->father() == mFather)
                            && (m_sibling->mother() != p_sibling->mother()) && (m_sibling != this)
                            && (p_sibling != this)){
                                x.insert(p_sibling);
                            }
                        }
                    }
                    else{
                        if(p_sibling != this){
                            x.insert(p_sibling);
                        }   
                    }
                }
            }
        }
    }
    else{
        if(pmod == PMod::MATERNAL){
            if(mMother != nullptr){
                for(auto m_sibling: mMother->children()){
                    if(m_sibling != this){
                        x.insert(m_sibling);
                    }
                }
            }
        }
        else if(pmod == PMod::PATERNAL){
            if(mFather != nullptr){
                for(auto p_sibling: mFather->children()){
                    if(p_sibling != this){
                        x.insert(p_sibling);
                    }
                }
            }
        }
        else{
            if(mMother != nullptr){
                for(auto m_sibling: mMother->children()){
                    if(m_sibling != this){
                        x.insert(m_sibling);
                    }
                }
            }
            if(mFather != nullptr){
                for(auto p_sibling: mFather->children()){
                    if(p_sibling != this){
                        x.insert(p_sibling);
                    }
                }
            }
        }
    }
    return x;
}

std::set<Person*> Person::sisters(PMod pmod, SMod smod){
    std::set<Person*> x;
    for(auto sister: siblings(pmod, smod)){
        if(sister->gender() == Gender::FEMALE){
            x.insert(sister);
        }
    }
    return x;
}
std::set<Person*> Person::sons(){
    std::set<Person*> x;
    for(auto child: mChildren){
        if(child->gender() == Gender::MALE){
            x.insert(child);
        }
    }
    return x;
}
std::set<Person*> Person::uncles(PMod pmod, SMod smod){
    std::set<Person*> x;
    if(smod == SMod::FULL){
        if(mMother != nullptr){
            for(auto brother: mMother->brothers(pmod, smod)){
                x.insert(brother);
            }
        }
        if(mFather != nullptr){
            for(auto brother: mFather->brothers(pmod, smod)){
                x.insert(brother);
            }
        }
    }
    else if(smod == SMod::HALF){
        if(pmod == PMod::MATERNAL){
            if(mMother != nullptr){
                for(auto brother: mMother->brothers(pmod = PMod::ANY, smod)){
                    x.insert(brother);
                }
                // for(auto brother: mMother->brothers(pmod = PMod::PATERNAL, smod)){
                //     x.insert(brother);
                // }
                
            }
        }
        else if(pmod == PMod::PATERNAL){
            if(mFather != nullptr){
                for(auto brother: mFather->brothers(pmod = PMod::ANY, smod)){
                    x.insert(brother);
                }
                // for(auto brother: mFather->brothers(pmod = PMod::MATERNAL, smod)){
                //     x.insert(brother);
                // }
            }
        }
        else{
            if(mMother != nullptr){
                // std::cout << "here" << '\n';
                for(auto brother: mMother->brothers(pmod = PMod::ANY, smod)){
                    x.insert(brother);
                }
                // for(auto brother: mMother->brothers(pmod = PMod::PATERNAL, smod)){
                //     x.insert(brother);
                // }
            }
            if(mFather != nullptr){
                // std::cout << "here2" << '\n';
                for(auto brother: mFather->brothers(pmod = PMod::ANY, smod)){
                    x.insert(brother);
                }
                // for(auto brother: mFather->brothers(pmod = PMod::MATERNAL, smod)){
                //     x.insert(brother);
                // }
            }
        }
    }
    
    else if(pmod == PMod::MATERNAL){
        if(mMother != nullptr){
            for(auto brother: mMother->brothers(pmod = PMod::ANY, smod)){
                x.insert(brother);
            }
            
            // for(auto brother: mMother->brothers(pmod = PMod::PATERNAL, smod)){
            //     x.insert(brother);
            // }
        }
    }
    else if(pmod == PMod::PATERNAL){
        if(mFather != nullptr){
            for(auto brother: mFather->brothers(pmod = PMod::ANY, smod)){
                x.insert(brother);
            }
            // for(auto brother: mFather->brothers(pmod = PMod::MATERNAL, smod)){
            //     x.insert(brother);
            // }
        }
    }
    else{
        if(mMother != nullptr){
            for(auto brother: mMother->brothers(pmod = PMod::ANY, smod)){
                x.insert(brother);
            }
            
            // for(auto brother: mMother->brothers(pmod = PMod::PATERNAL, smod)){
            //     x.insert(brother);
            // }
        }
        if(mFather != nullptr){
            for(auto brother: mFather->brothers(pmod = PMod::ANY, smod)){
                x.insert(brother);
            }
            // for(auto brother: mFather->brothers(pmod = PMod::MATERNAL, smod)){
            //     x.insert(brother);
            // }
        }
    }
    return x;
}
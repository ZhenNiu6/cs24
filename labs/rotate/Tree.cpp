#include "Tree.h"

// Tree Function Implementations

Tree::Tree() {
    root = nullptr;
    mLength = 0;
}

Tree::~Tree() {
    clear();
}

Node* Tree::return_root() {
    return root;
}

void Tree::clear_helper(Node* current) {
    if(current->left != nullptr) {
        clear_helper(current->left);
    }
    if(current->right != nullptr) {
        clear_helper(current->right);
    }
    delete current;
}

void Tree::clear() {
    if(root != nullptr) {
        clear_helper(root);
        root = nullptr;
        mLength = 0;
    }
}

size_t Tree::count() const {
    return mLength;
}

bool Tree::contains_helper(const string& s, Node* current) const {
    if(current == nullptr) {
        return false;
    }
    else if(s == current->content) {
        return true;
    }
    else {
        if(s < current->content) {
            if(current->left == nullptr) {
                return false;
            }
            else {
                return contains_helper(s, current->left);
            }
        }
        else {
            if(current->right == nullptr) {
                return false;
            }
            else {
                return contains_helper(s, current->right);
            }
        }
    }
}

bool Tree::contains(const std::string& s) const {
    return contains_helper(s, root);
}

void Tree::calculate_weight(Node* current) {
    if(current == nullptr) {
        return;
    }
    else {
        size_t result = 1;
        if(current->left == nullptr && current->right == nullptr) {
            current->weight = result;
            return;
        }
        else {
            if(current->left != nullptr) {
                calculate_weight(current->left);
                result += current->left->weight;
            }
            if(current->right != nullptr) {
                calculate_weight(current->right);
                result += current->right->weight;
            }
            current->weight = result;
        }
    }
}

void Tree::set_index(Node* current) {
    if(current->left != nullptr) {
        if(current->left->right != nullptr) {
            current->left->mIndex = current->mIndex - current->left->right->weight - 1;
        }
        else {
            current->left->mIndex = current->mIndex - 1;
        }
        set_index(current->left);
    }
    if(current->right != nullptr) {
        if(current->right->left != nullptr) {
            current->right->mIndex = current->mIndex + current->right->left->weight + 1;
        }
        else {
            current->right->mIndex = current->mIndex + 1;
        }
        set_index(current->right);
    }
}

size_t Tree::find_helper(const string& s, Node* current) const {
    if(current == nullptr) {
        return 0;
    }
    else if(s == current->content) {
        if(current->left != nullptr) {
            if(contains_helper(s, current->left)) {
                return find_helper(s, current->left);
            }
            else {
                return current->mIndex;
            }
        }
        else {
            return current->mIndex;
        }
    }
    else if(s < current->content) {
        if(current->left != nullptr) {
            return find_helper(s, current->left);
        }
        else {
            return SIZE_MAX;
        }
    }
    else {
        if(current->right != nullptr) {
            return find_helper(s, current->right);
        }
        else {
            return SIZE_MAX;
        }
    }
}

size_t Tree::find(const std::string& s) const {
    if(mLength == 0) {
        return SIZE_MAX;
    }
    else {
        return find_helper(s, root);
    }
}

void Tree::compare_Node(Node* container, Node* current) {
    if(container->content <= current->content) {
        if(current->left != nullptr) {
            compare_Node(container, current->left);
        }
        else {
            current->left = container;
            return;
        }
    }
    else {
        if(current->right != nullptr) {
            compare_Node(container, current->right);
        }
        else {
            current->right = container;
            return;
        }
    }
}

void Tree::insert(const std::string& s) {
    Node* container = new Node(s);
    if(root == nullptr) { 
        root = container;
    }
    else{
        compare_Node(container, root);
    }
    mLength += 1;
    calculate_weight(root);
    rotate(root);
    calculate_weight(root);
    if(root->left != nullptr) {
        root->mIndex = root->left->weight;
    }
    set_index(root);
}

string Tree::lookup_helper(Node* current, size_t index) const {
    if(current->mIndex == index) {
        return current->content;
    }
    else if(index < current->mIndex) {
        if(current->left != nullptr) {
            return lookup_helper(current->left, index);
        }
        else {
            return current->content;
        }
    }
    else {
        if(current->right != nullptr) {
            return lookup_helper(current->right, index);
        }
        else {
            return current->content;
        }
    }
}

string Tree::lookup(size_t index) const {
    string result = "";
    if(index >= mLength) {
        throw std::out_of_range("Invalid index.");
    }
    else {
        result = lookup_helper(root, index);
    }
    return result;
}

void Tree::print_Tree(Node* start) const {
    if(start->left == nullptr && start->right == nullptr) {
        cout << start->content;
    }
    else {
        cout << "(";
        if(start->left != nullptr) {
            print_Tree(start->left);
        }
        else {
            cout << "-";
        }
        cout << " " << start->content << " "; 
        if(start->right != nullptr) {
            print_Tree(start->right);
        }
        else {
            cout << "-";
        }
        cout << ")";
    }
}

void Tree::print() const {
    if(root == nullptr) {
        cout << '-' << '\n';
    }
    else {
        print_Tree(root);
        cout << '\n';
    }
}

Node* Tree::return_node(size_t index, Node* current) {
    if(current->mIndex == index) {
        return current;
    }
    else if(index < current->mIndex) {
        if(current->left != nullptr) {
            return return_node(index, current->left);
        }
        else {
            return current;
        }
    }
    else {
        if(current->right != nullptr) {
            return return_node(index, current->right);
        }
        else {
            return current;
        }
    }
}

void Tree::remove_zero(size_t index, Node* current) {
    if(index == mLength - 1) {
        Node* parent = return_node(index - 1, root);
        delete current;
        parent->right = nullptr;
    }
    else {
        Node* before = return_node(index - 1, root);
        Node* after = return_node(index + 1, root);
        if(before->right == current) {
            delete current;
            before->right = nullptr;
        }
        else {
            delete current;
            after->left = nullptr;
        }
        return;
    }
}

void Tree::remove_one(size_t index, Node* current) {
    if(current->left != nullptr) {
        current->content = current->left->content;
        delete current->left;
        current->left = nullptr;
    }
    else {
        current->content = current->right->content;
        delete current->right;
        current->right = nullptr;
    }
}

void Tree::remove_two(size_t index, Node* current) {
    if(current->right->left == nullptr) {
        current->content = current->right->content;
        if(current->right->right == nullptr) {
            delete current->right;
            current->right = nullptr;
        }
        else {
            current->right->content = current->right->right->content;
            delete current->right->right;
            current->right->right = nullptr;
        }
    }
    else {
        Node* next = return_node(index + 1, root);
        current->content = next->content;
        if(next->right == nullptr) {
            delete next;
            Node* next_next = return_node(index + 2, root);
            next_next->left = nullptr;
        }
        else {
            next->content = next->right->content;
            next->right = next->right->right;
            delete next->right;
        }
    }
}

void Tree::remove_helper(size_t index) {
    Node* current = return_node(index, root);
    if(current->left == nullptr && current->right == nullptr) {
        remove_zero(index, current);
    }
    else if(current->left != nullptr && current->right != nullptr) {
        remove_two(index, current);
    }
    else {
        remove_one(index, current);
    }
}

void Tree::remove(size_t index) {
    if(index >= mLength) {
        throw std::out_of_range("Invalid index.");
    }
    else if(index == 0 && mLength == 1) {
        clear();
        root = nullptr;
        return;
    }
    else {
        remove_helper(index);
    }
    mLength -= 1;
    calculate_weight(root);
    rotate(root);
    calculate_weight(root);
    if(root->left != nullptr) {
        root->mIndex = root->left->weight;
    }
    set_index(root);
}

void Tree::left_rotation(Node*& current) {
    if(current->right != nullptr) {
        Node* current_temp = current;
        Node* current_right_temp = current->right;
        Node* current_right_left_temp = current->right->left;
        current = current_right_temp;
        current->left = current_temp;
        current->left->right = current_right_left_temp;
    }
}

void Tree::right_rotation(Node*& current) {
    if(current->left != nullptr) {
        Node* current_temp = current;
        Node* current_left_temp = current->left;
        Node* current_left_right_temp = current->left->right;
        current = current_left_temp;
        current->right = current_temp;
        current->right->left = current_left_right_temp;
    }
}

void Tree::rotate(Node*& current) {
    if(current->left == nullptr && current->right == nullptr) {
        return;
    }
    else {
        int left_weight = 0;
        int right_weight = 0;
        int left_left_weight = 0;
        int left_right_weight = 0;
        int right_left_weight = 0;
        int right_right_weight = 0;
        if(current->left != nullptr) {
            left_weight = current->left->weight;
            if(current->left->left != nullptr) {
                left_left_weight = current->left->left->weight;
            }
            if(current->left->right != nullptr) {
                left_right_weight = current->left->right->weight;
            }
        }
        if(current->right != nullptr) {
            right_weight = current->right->weight;
            if(current->right->left != nullptr) {
                right_left_weight = current->right->left->weight;
            }
            if(current->right->right != nullptr) {
                right_right_weight = current->right->right->weight;
            }
        }
        // if(current->content == "rho") {
        //     cout << abs(left_weight - (right_left_weight + right_right_weight + 1)) - abs(left_weight + right_left_weight + 1 - right_right_weight) << '\n';
        //     cout << abs(left_left_weight + left_right_weight + 1 - right_weight) - abs(left_left_weight - (left_right_weight + right_weight + 1)) << '\n';
        // }
        if(abs(left_weight - (right_left_weight + right_right_weight + 1)) > abs(left_weight + right_left_weight + 1 - right_right_weight)) {
            left_rotation(current);
            if(current->left != nullptr) {
                rotate(current->left);
            }
            if(current->right != nullptr) {
                rotate(current->right);
            }
        }
        else if(abs(left_left_weight + left_right_weight + 1 - right_weight) > abs(left_left_weight - (left_right_weight + right_weight + 1))) {
            right_rotation(current);
            if(current->left != nullptr) {
                rotate(current->left);
            }
            if(current->right != nullptr) {
                rotate(current->right);
            }
        }
        else {
            return;
        }
    }
}




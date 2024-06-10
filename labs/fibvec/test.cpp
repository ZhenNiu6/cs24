int main() {

    FibVec vector = FibVec();
    vector.insert(5, 0);
    vector.insert(4, 1);
    vector.insert(3, 2);
    vector.insert(2, 3);
    vector.remove(3);
    vector.remove(2);
    vector.remove(1);
    size_t con = vector.capacity();
    size_t len = vector.count();
    int result = vector.lookup(0);
    cout << "con: " << con << '\n';
    cout << "len: " << len << '\n';
    cout << result << '\n';

    return 0;

}
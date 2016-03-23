#include <iostream>
using namespace std;
const int MAX_SIZE(30);
class Stack {
private:
    int container[MAX_SIZE];
    int size;
public:
    Stack() {
        size = 0;
    }
    void push(int );
    void pop();
    int top();
};
void Stack::push(int a) {
    if(size < MAX_SIZE)
        container[size++] = a;
    else
        cout << "Stack full" << endl;
}
int Stack::top() {
    if(size == 0) {
        cout << "Stack empty" << endl;
        return -1;
    } else {
        cout << container[size-1] << endl;
        return container[size];
    }
}
void Stack::pop() {
    if(size <= 0) {
        cout << "Stack empty" << endl;
    } else
        size--;
}
int main() {
    Stack s;
    s.push(0);
    s.push(1);

    s.pop();
    s.top();
    return 0;
}
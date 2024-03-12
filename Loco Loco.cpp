#include <iostream>
using namespace std;

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
    };

    Node* topNode;
    int size;
    int capacity;

public:
    Stack() : topNode(nullptr), size(0), capacity(10) {}

    ~Stack() {
        clear();
    }

    Stack(const Stack& other) : topNode(nullptr), size(0), capacity(10) {
        Node* temp = other.topNode;
        while (temp != nullptr) {
            push(temp->data);
            temp = temp->next;
        }
    }

    void push(const T& value) {
        if (size == capacity) {
            resize();
        }
        Node* newNode = new Node{ value, topNode };
        topNode = newNode;
        size++;
    }

    void pop() {
        if (isEmpty()) {
            cout << "Stack is empty. Cannot pop.\n";
            return;
        }
        Node* temp = topNode;
        topNode = topNode->next;
        delete temp;
        size--;
    }

    const T& top() const {
        if (isEmpty()) {
            throw runtime_error("Stack is empty.");
        }
        return topNode->data;
    }

    bool isEmpty() const {
        return size == 0;
    }

    int getSize() const {
        return size;
    }

    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }

private:
    void resize() {
        capacity *= 2;

        T* tempArray = new T[size];
        Node* temp = topNode;
        int index = 0;
        while (temp != nullptr) {
            tempArray[index++] = temp->data;
            temp = temp->next;
        }
        clear();
        for (int i = index - 1; i >= 0; i--) {
            push(tempArray[i]);
        }
        delete[] tempArray;
    }
};

int main() {
    Stack<int> stack;
    stack.push(5);
    stack.push(10);
    stack.push(3);

    cout << "Top element of stack: " << stack.top() << endl;
    cout << "Stack size: " << stack.getSize() << endl;

    stack.pop();
    cout << "After pop, Top element of stack: " << stack.top() << endl;

    Stack<int> stack2 = stack;
    cout << "Top element of stack2: " << stack2.top() << endl;

}

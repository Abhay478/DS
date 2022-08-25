#include <iostream>


class node{
    public:
    int n;
    node * next;
    node(int val){n = val; next = 0;}
};

class Stack{
    public:
    node * head;
    void start();
    void push(int val);
    int pop();
    ~Stack(){
        node * current = head;
        while(head != nullptr){
            head = head->next;
            delete current;
            current = head;
        }
    }
};

void Stack::push(int val){
    node * cu = new node(val);
    cu->next = head;
    head = cu;
}

int Stack::pop()
{
    if(head == nullptr) return -1;
    node * out = head;
    head = head->next;
    int n = out->n;
    delete out;
    return n;
}

void Stack::start()
{
    std::cout << "Following are the acceptable commands: \n\n"
    "push <value> : pushes an element onto stack.\n"
    "pop : pops element off stack.\n"
    "empty : checks whether stack is empty.\n"
    "destroy : deletes stack and terminates program.\n\n";
    std::string cmd;
    while(true){
        std::cout << "Enter function name.\n\n>>> ";
        std::cin >> cmd;
        if(cmd == "push"){
            int val;
            std::cin >> val;
            push(val);
            std::cout << "Pushed" << std::endl;
        }
        else if(cmd == "pop"){
            int out = pop();
            if(out == -1)
                std::cout << "Empty." << std::endl;
            else std::cout << out << std::endl;
        }
        else if(cmd == "empty"){
            std::cout << (head == nullptr ? "yes" : "no") << std::endl;
        }
        else if(cmd == "destroy"){
            return;
        }
        else{
            std::cout << "Invalid command." << std::endl << std::endl;
        }
    }
}

int main()
{
    Stack * s = new Stack();

    s->start();
    delete s;
    return 0;
}
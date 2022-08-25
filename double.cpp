#include <iostream>

using namespace std;

class node{
    public:
    int n;
    node * next;
    node * prev;
    node(int val){n = val; next = nullptr; prev = nullptr;}
};

class Collection{
    node * head;
    public:
    void start();
    void insert(int val);
    void remove(int val);
    void display();
    void reverse();

    node * search(int val);
};

void Collection::insert(int val)
{
    if(!head){
        head = new node(val);
        return;
    }
    node * inc = new node(val);
    node * push = head;
    inc->next = push;
    push->prev = inc;
    head = inc;
}

void Collection::remove(int val)
{
    if(head == nullptr) return;
    node * current = head;
    if(current->n == val){
        head = current->next;
        delete current;
        return;
    }

    while(current != nullptr){
        if(current->n == val){
            current->prev->next = current->next;
            if(current->next) current->next->prev = current->prev;
            
            delete current;
            return;
        }
        current = current->next;
    }
    cout << "Not there." << endl;
    return;
}

node * Collection::search(int val)
{
    node * current = head;
    while(current != nullptr){
        if(current->n == val) return current;
        current = current->next;
    }
    return nullptr;
}

void Collection::display()
{
    node * current = head;
    while(current != nullptr){
        std::cout << current->n << std::endl;
        current = current->next;
    }
}

void Collection::start()
{
    string cmd;
    while(true){
        cout << "Enter command." << std::endl << std::endl << ">>> ";
        cin >> cmd;
        if(cmd == "add"){
            int val;
            cin >> val;
            insert(val);
            cout << "Added." << std::endl << std::endl;
        }
        else if(cmd == "del"){
            int val;
            std::cin >> val;
            remove(val);
            std::cout << "Deleted." << std::endl << std::endl;
        }
        else if(cmd == "rev"){
            reverse();
            std::cout << "Reversed" << std::endl << std::endl;
        }
        else if(cmd == "dis"){
            std::cout << std::endl;
            display();
            std::cout << std::endl;
        }
        else if(cmd == "destroy") return;
        else{
            std::cout << "Invalid command." << std::endl << std::endl;
        }
    }
}

void Collection::reverse()
{
    if(head == nullptr){
        std::cout << "Empty." << std::endl;
        return;
    }
    if(head->next == nullptr) return;
    node * current = head;
    head = head->next;
    node * ss = head->next;
    current->next = nullptr;

    while(ss != nullptr){
        head->next = current;
        current->prev = head;
        current = head;
        head = ss;
        ss = ss->next;
    }
    head->next = current;
    current->prev = head;
}



int main()
{
    Collection * c = new Collection();
    c->start();

    delete c;
    return 0;
}
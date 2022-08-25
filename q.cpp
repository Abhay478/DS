#include <iostream>
using namespace std;

class node{
    public:
    int n;
    node * next;
    node(int val){n = val; next = nullptr;}
    ~node(){
        
    }
};

class Queue{
    public:
    node * head;
    node * tail;
    void enq(int val);
    int deq();
    void start();
    ~Queue(){
        node * current = head;
        while (current != nullptr){
            head = head->next;
            delete current;
            current = head;
        }
    }
};

void Queue::enq(int n)
{
    node * in = new node(n);
    if(!tail){
        head = tail = in;
        cout << "Queue initialised." << endl;    
    }
    else {
        tail->next = in;
        tail = tail->next;
    }
}

int Queue::deq()
{
    if(head == nullptr) return -1;
    node * out = head;
    head = head->next;
    int n = out->n;
    delete out;
    return n;
}

void Queue::start()
{
    // head = tail = new node(-1);
    cout << "Following are the acceptable commands:\n\n"
    "enq <value> : Enqueues value.\n"
    "deq : Dequeues value and prints it.\n"
    "empty : Prints 'YES' if queue is empty, 'NO' otherwise.\n"
    "destroy : destroys queue and terminates program.\n" << endl;

    std::string cmd;
    while(true){
        std::cout << ">>> ";
        std::cin >> cmd;
        if(cmd == "enq"){
            int val;
            std::cin >> val;
            enq(val);
            std::cout << "Enqueued" << std::endl << std::endl;
        }
        else if(cmd == "deq"){
            int out = deq();
            if(out == -1)
                std::cout << "Empty." << std::endl << std::endl;
            else std::cout << out << std::endl << std::endl;
        }
        else if(cmd == "empty"){
            std::cout << (head == nullptr || tail == nullptr ? "YES" : "NO") << std::endl;
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
    Queue * q = new Queue();
    q->start();

    delete q;
    return 0;
}
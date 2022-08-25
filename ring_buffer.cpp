#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
using namespace std;


class Queue{
    public:
    int * data;
    int start;
    int end;

    int max;

    Queue(int n);
    bool isEmpty();
    bool isFull();
    void enq(int val);
    int deq();
    void cli();
    void disp();
    ~Queue();
};

Queue::Queue(int n){
    this->data = (int *)calloc(n, sizeof(int));
    this->end = 0;
    this->start = 0;
    this->max = n;
}

Queue::~Queue()
{
    free(data);
}

bool Queue::isEmpty()
{
    return (end == start);
}

bool Queue::isFull()
{
    if(end < start) return abs(start - end)%max == 1;
    else return abs(start - end)%max == max - 1;
}

void Queue::enq(int val)
{
    if(isFull()){
        printf("Full.\n\n");
        return;
    }
    data[end] = val;
    end = (end + 1) % max;
}

int Queue::deq()
{
    if(isEmpty()){
        printf("Empty.\n");
        return -1;
    }
    int out = data[start];
    start = (start + 1) % max;
    return out;
}

void Queue::disp(){
    for(int i = start; i != end; i = (i + 1)%max)
        cout << data[i] << endl;

}

void Queue::cli(){
    cout << "Following are the acceptable commands:\n\n"
    "enq <value> : Enqueues value.\n"
    "deq : Dequeues value and prints it.\n"
    "empty : Prints 'YES' if queue is empty, 'NO' otherwise.\n"
    "full : Prints 'YES' if queue is full, 'NO' otherwise.\n"
    "dis : Displays queue.\n"
    "destroy : destroys queue and terminates program.\n" << endl;

    std::string cmd;
    while(true){
        std::cout << "\n>>> ";
        std::cin >> cmd;
        if(cmd == "enq"){
            int val;
            std::cin >> val;
            enq(val);
            // std::cout << "Enqueued" << std::endl << std::endl;
        }
        else if(cmd == "deq"){
            int out = deq();
            if(out == -1)
                std::cout << "Empty." << std::endl;
            else std::cout << out << std::endl;
        }
        else if(cmd == "empty"){
            std::cout << (isEmpty() ? "YES" : "NO") << std::endl;
        }
        else if(cmd == "full"){
            std::cout << (isFull() ? "YES" : "NO") << std::endl;
        }
        else if(cmd == "dis"){
            disp();
        }
        else if(cmd == "destroy"){
            return;
        }
        else{
            std::cout << "Invalid command." << std::endl;
        }
    }
}

int main()
{
    Queue * q = new Queue(20);
    
    q->cli();

    delete q;

}
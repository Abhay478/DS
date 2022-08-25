#include <iostream>

using namespace std;

class node{
    string name;
    int age;
    char gender;// M or F
    string dept;

    public:
    node * next;
    node * prev;

    void show()
    {
        cout << "\nName: " << name <<
        "\nAge: " << age <<
        "\nGender: " << gender <<
        "\nDepartment: " << dept << endl;
    }

    node(){
        cout << "Enter name." << endl;
        cin >> name;
        cout << "Enter age." << endl;
        cin >> age;
        char g;
        cout << "Enter gender (M or F)." << endl;
        cin >> g;
        while(g != 'M' && g != 'F'){
            cout << "Entered gender is not supported. Please enter 'M' or 'F'." << endl;
            cin >> g;
        }
        gender = g;
        cout << "Enter department." << endl;
        cin >> dept;
        cout << endl;

        cout << "Your data has been processed." << endl;
    }
};

class Collection
{
    private:
    node * head;
    node * search(string nm);
    void insert();
    void remove(string nm);
    void get(string nm);
    void display();
    public:
    void start();

    ~Collection(){
        node * current = head;
        while(head != nullptr){
            head = head->next;
            delete current;
            current = head;
        }
    }
};

void Collection::insert()
{
    node * inc = new node();
    node * push = head;
    inc->next = push;
    if(head) push->prev = inc;
    head = inc;

    cout << "Inserted." << endl;
}

void Collection::remove(string nm){
    node * out = search(nm);
    if(!out){
        cout << "No such entry." << endl;
        return;
    }
    if(out == head){
        head = out->next;
        delete out;
        cout << "Head moved." << endl;
    }

    
}

// void Collection::remove(string nm)
// {
//     if(head == nullptr) {
//         cout << "List is empty." << endl;
//         return;
//     }
//     node ** current = &head;
    
//     while(*current && (*current)->name != nm){
//         current = &(*current)->next;
//     }
//     node * out = *current;
//     if(!out){
//         cout << "No such entry." << endl;
//         return;
//     }
//     *current = (*current)->next;
//     delete out;

//     cout << "Deleted." << endl;
// }

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
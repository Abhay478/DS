/*********
 * Doubly Linked List
 * for CS2233
 * Abhay Shankar K
 * cs21btech11001
*/

#include <iostream>
using namespace std;

class node{
    public:
    string name;
    int age;
    char gender;// M or F
    string dept;

    node * next;
    node * prev;

    void show()
    {
        cout << "--------------" << endl;
        cout << "Name: " << name <<
        "\nAge: " << age <<
        "\nGender: " << gender <<
        "\nDepartment: " << dept << endl;
    }

    node(){
        cout << "Enter name." << endl;
        cin >> name;
        cout << "Enter age." << endl;
        // cin >> age;
        while(!(cin >> age) || age < 0){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Age must be a positive integer." << endl;
        }
        
        // char g;
        cout << "Enter gender (M or F)." << endl;
        // cin >> g; 
        while(!(cin >> gender) || (gender != 'M' && gender != 'F')){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entered gender " << gender << " is not supported. Please enter 'M' or 'F'." << endl;
        }
        // gender = g;
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

//insert at start
void Collection::insert()
{
    node * inc = new node();
    node * push = head;
    inc->next = push;
    if(head) push->prev = inc;
    head = inc;

    cout << "Inserted." << endl;
}

//straightfowrward deletion
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
        return;
    }

    out->prev->next = out->next;
    out->next->prev = out->prev;
    delete out;
    cout << "Deleted." << endl;
}

//used in "search" and "get"
node * Collection::search(string nm)
{
    node * current = head;  
    while(current != nullptr){
        if(current->name == nm) return current;
        current = current->next;
    }
    return nullptr;
}

//full list
void Collection::display()
{
    if(head == nullptr)
    {
        cout << "List is empty." << endl;
        return;
    }
    node * current = head;
    while(current != nullptr){
        current->show();
        current = current->next;
    }
}

//UI
void Collection::start()
{
    std::cout << "Following are the acceptable commands:\n\n"
    "  add : Adds a node to the list after accepting data.\n"
 "  del <name> : Removes member with that name.\n"
 "  fetch <name> : Prints the data for <name>.\n"
 "  search <name> : Prints 'yes' if entry exists, 'no' otherwise."
 "  show : prints entire list.\n"
 "  exit : destroys list and terminates program.\n" << endl;
    string cmd;
    while(true){
        std::cout << "Enter command.\n\n" << ">>> ";
        std::cin >> cmd;
        if(cmd == "add"){
            insert();
        }
        else if(cmd == "search"){
            string nm;
            std::cin >> nm;
            node * out = search(nm);
            if(out) cout << "YES" << endl;
            else cout << "NO" << endl;
        }
        else if(cmd == "del"){
            string nm;
            std::cin >> nm;
            remove(nm);
            // std::cout << "Deleted." << std::endl << std::endl;
        }
        else if(cmd == "fetch"){
            string nm;
            std::cin >> nm;
            node * current = search(nm);
            if(!current) cout << "No such entry." << endl;
            else current->show();
        }
        else if(cmd == "show"){
            std::cout << std::endl;
            display();
            std::cout << std::endl;
        }
        else if(cmd == "exit") return;
        else{
            std::cout << '\'' << cmd << "' is an invalid command." << std::endl << std::endl;
        }
    }
}

int main()
{
    Collection * c = new Collection();
    c->start();

    delete c;
    return 0;
}
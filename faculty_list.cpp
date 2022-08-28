/*********
 * Singly Linked List
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

//insert at front
void Collection::insert()
{
    node * in = new node();
    node * push = head;
    in->next = push;
    head = in;

    cout << "Inserted." << endl;
}

//full list
void Collection::display()
{
    node * current = head;
    while(current != nullptr){
        current->show();
        current = current->next;
    }
}

//staraightforward deletion
void Collection::remove(string nm)
{
    if(head == nullptr) {
        cout << "List is empty." << endl;
        return;
    }
    node ** current = &head;
    
    while(*current && (*current)->name != nm){
        current = &(*current)->next;
    }
    node * out = *current;
    if(!out){

    }
    *current = (*current)->next;
    delete out;

    cout << "Deleted." << endl;
}

//used in "is" and "get".
node * Collection::search(string nm)
{
    node * current = head;
    while(current != nullptr){
        if(current->name == nm) return current;
        current = current->next;
    }
    return nullptr;
}

//UI
void Collection::start()
{
    std::cout << "Following are the acceptable commands:\n\n"
    "  add : Adds a node to the list after accepting data.\n"
 "  del <name> : Removes member with that name.\n"
 "  get <name> : Prints the data for <name>.\n"
 "  is <name> : Prints 'yes' if entry exists, 'no' otherwise."
 "  dis : prints entire list.\n"
 "  destroy : destroys list.\n";
    std::string cmd;
    while(true){
        std::cout << "Enter command." << std::endl << std::endl << ">>> ";
        std::cin >> cmd;
        if(cmd == "add"){
            insert();
        }
        else if(cmd == "is"){
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
        else if(cmd == "get"){
            string nm;
            std::cin >> nm;
            node * current = search(nm);
            if(!current)
                cout << "No such entry." << endl;
            
            else current->show();
        }
        else if(cmd == "dis"){
            std::cout << std::endl;
            display();
            std::cout << std::endl;
        }
        else if(cmd == "destroy") return;
        else{
            std::cout << cmd << " is an invalid command." << std::endl << std::endl;
        }
    }
}

int main()
{
    Collection * c = new Collection();
    c->start();

    delete c;
    
}
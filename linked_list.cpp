#include <iostream>


class node{
    public:
    int n;
    node * next;
    node(int val){n = val; next = nullptr;}
};

class Collection
{
    private:
    node * head;
    node * search(int val);
    void insert(int val);
    void remove(int val);
    void display();
    void reverse();
    int get(int a);
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

void Collection::insert(int val)
{
    node * inc = new node(val);
    node * push = head;
    inc->next = push;
    head = inc;
}

int Collection::get(int a){
    node * current = head;
    for(int i = 0; i < a && current != nullptr; i++){
        current = current->next;
    }
    if(current == nullptr) return -1;
    else return current->n;
}

void Collection::display()
{
    node * current = head;
    while(current != nullptr){
        std::cout << current->n << std::endl;
        current = current->next;
    }
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

    while(current->next != nullptr){
        if(current->next->n == val){
            node * out = current->next;
            current->next = out->next;
            delete out;
            return;
        }
        current = current->next;
    }
    std::cout << "Not there." << std::endl;
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
        current = head;
        head = ss;
        ss = ss->next;
    }
    head->next = current;
}

void Collection::start()
{
    std::cout << "Following are the acceptable commands:\n\n"
    "  add <value> : Adds a node to the list.\n"
 "  del <value> : Removes node with that value.\n"
 "  get <value> : Prints the node at <value>.\n"
 "  is <value> : Prints 'yes' if vaule exsts, 'no' otherwise."
 "  rev : reverses the list.\n"
 "  dis : prints entire list.\n"
 "  destroy : destroys list.\n";
    std::string cmd;
    while(true){
        std::cout << "Enter command." << std::endl << std::endl << ">>> ";
        std::cin >> cmd;
        if(cmd == "add"){
            int val;
            std::cin >> val;
            insert(val);
            std::cout << "Added." << std::endl << std::endl;
        }
        if(cmd == "is"){
            int val;
            std::cin >> val;
            node * out = search(val);
            if(out) cout << "YES" << endl;
            else cout << "NO" << endl;
        }
        else if(cmd == "del"){
            int val;
            std::cin >> val;
            remove(val);
            std::cout << "Deleted." << std::endl << std::endl;
        }
        else if(cmd == "get"){
            int val;
            std::cin >> val;
            int x = get(val);
            if(x != -1) std::cout << x << std::endl << std::endl;
            else std::cout << "Exceeded." << std::endl << std::endl;
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

/***********
 * The Collection::start function accepts the following commands from the terminal:
 *  add <value> : Adds a node to the list.
 *  del <value> : Removes node with that value.
 *  get <value> : Prints the node at <value>.
 *  rev : reverses the list.
 *  dis : prints entire list.
 *  destroy : destroys list.
*/

int main()
{
    Collection * c = new Collection();
    c->start();

    delete c;
    
}
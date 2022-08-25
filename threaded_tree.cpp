#include <iostream>
using namespace std;

class node{
    public:
    int n;
    node * left;
    node * right;

    bool lth, rth;
    node(int val){
        n = val;
        left = right = nullptr;
        lth = rth = true;
    }

    void left_attach(int val);
    void right_attach(int val);

    node * next();
    node * prev();
};

node * node::next()
{
    node * current = this;
    if(current->rth)
        current = current->right;
    else{
        current = current->right;
        while(!current->lth)
            current = current->left;
    }
    return current;
}

node * node::prev()
{
    node * current = this;
    if(current->lth) current = current->left;
    else{
        current = current->left;
        while(!current->rth) current = current->right;       
    }
    return current;
}

void node::left_attach(int val)
{
    lth = false;
    node * in = new node(val);
    in->left = left;
    left = in;
    in->right = this;
}

void node::right_attach(int val)
{
    rth = false;
    node * in = new node(val);

    in->right = right;
    right = in;
    in->left = this;
}

class Tree{
    public:
    node * root;

    void inorder();
    void preorder(){cout << "No." << endl;}
    void postorder(){cout << "No." << endl;}

    void insert(int val);
    void remove(int val);
    void remove_sub(node * req, node * p);
    node * search(int val) {return nullptr;};

    // Tree()
    // {
    //     root = new node(-1);
    // }

    void start();
};

void Tree::remove_sub(node * req, node * p)
{
    //leaf
    if(req->lth && req->rth){
        if(req == root){
            delete req;
            root = nullptr;
            return;
        }
        cout << "this" << endl;
        if(p->left == req) p->left = req->left;
        if(p->right == req) p->right = req->right;
        delete req;
        return;
    }

    //left subtree
    if(req->rth){
        if(req == root){
            root->prev()->right = root->left;
            root = root->left;
            delete req;
            return;
        }
        
        if(req == p->left) p->left = req->left;
        else p->right = req->left;

        req->prev()->right = p;

        delete req;
        return;
    }

    //right subtree
    if(req->lth){
        if(req == root){
            root->next()->left = root->right;
            root = root->right;
            delete req;
            return;
        }

        if(req == p->left) p->left = req->left;
        else p->right = req->left;

        req->next()->left = p;

        delete req;
        return;
    }

}

void Tree::insert(int val)
{
    if(root == nullptr) {
        root = new node(val);
        cout << "Tree initialised." << endl;
        return;
    }

    
    node * current = root;
    while(true)
    {
        if(val > current->n){
            if(current->right == nullptr){
                current->right_attach(val);
                cout << "New rightmost." << endl;
                break;;
            }
            if(current->rth) {current->right_attach(val); break;}
            current = current->right;
        }
        else if(val < current->n){
            if(current->left == nullptr){
                current->left_attach(val);
                cout << "New leftmost." << endl;
                break;;
            }
            if(current->lth) {current->left_attach(val); break;}
            current = current->left;
        }
        else if(val == current->n){
            cout << "Duplicated. Not inserted." << endl;
            break;
        }
    }

}

void Tree::inorder()
{
    node * current = root;
    if(current == nullptr){
        cout << "Empty." << endl;
        return;
    }
    while(current->left != nullptr){
        current = current->left;
    }

    while(current != nullptr){
        cout << current->n << endl;
        current = current->next();
    }

}

void Tree::remove(int val)
{
    if(root == nullptr){
        cout << "Tree is empty." << endl;
        return;
    }
    node * req = root, * p = nullptr;

    while(req != nullptr){
        
        if(req->n == val) break;

        else if(req->n > val) {p = req; req = req->lth ? nullptr : req->left;}

        else {p = req; req = req->rth ? nullptr : req->right;}
    }

    if(req == nullptr){
        cout << "No such entry." << endl;
        return;
    }
    
    if(req == root) cout << "Messing with root." << endl;

    if(req->lth || req->rth) remove_sub(req, p);
    
    else{
        node * current = req->next();
        req->n = current->n;
        if(current->rth) p = current->right;
        else p = current->next()->right;
    cout << "Here." << endl;
        remove_sub(current, p);
    }
}

void Tree::start()
{
    std::cout << "Following are the acceptable commands : \n\n"
    "add <value> : adds node to tree with given value.\n"
    "del <value> : deletes node containing given value.\n"
    "is <value> : prints 'yes' if vaule exsts, 'no' otherwise."
    "in : inorder traversal.\n"
    "pre : preorder traversal.\n"
    "post : postorder traversal.\n"
    "destroy : deletes tree and terminates program.\n\n";

    string cmd;
    while(true){
        cout << "Enter command.\n\n>>> ";
        cin >> cmd;
        if(cmd == "add"){
            int val;
            cin >> val;
            insert(val);
            // cout << "Added." << std::endl << std::endl;
        }
        else if(cmd == "del"){
            int val;
            std::cin >> val;
            remove(val);
            // std::cout << "Deleted." << std::endl << std::endl;
        }
        else if(cmd == "in"){
            std::cout << std::endl;
            inorder();
            std::cout << std::endl;
        }
        else if(cmd == "is"){
            int val;
            cin >> val;
            std::cout << std::endl;
            node * is = search(val);
            if(is) cout << "YES";
            else cout << "NO";
            std::cout << std::endl;
        }
        else if(cmd == "pre"){
            std::cout << std::endl;
            preorder();
            std::cout << std::endl;
        }
        else if(cmd == "post"){
            std::cout << std::endl;
            postorder();
            std::cout << std::endl;
        }
        else if(cmd == "destroy") return;
        else{
            std::cout << "Invalid command." << std::endl << std::endl;
        }
    }
}

int main()
{
    Tree * t = new Tree();

    t->start();
    delete t;

}
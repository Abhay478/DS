#include <iostream>
using namespace std;

class node{
    public:
    int n;
    node * left;
    node * right;
    node(int val){n = val; left = nullptr; right = nullptr;}
};

class Tree{
    public:
    node * root;

    void insert(node * root, int val);
    void remove(int val);
    node * search(node * root, int val);

    void inorder(node * root);
    void preorder(node * root);
    void postorder(node * root);

    ~Tree();
    void start();
};

void Tree::insert(node * root, int val)
{
    if(!root){
        this->root = new node(val);
        cout << "Tree has been initialized." << endl;
        return;
    }

    node * current = root;

    while(current){
        if(val < current->n){
            if(!current->left) {
                current->left = new node(val);
                // current->left->parent = current;
                return;
            }
            else{
                current = current->left;
            }
        }
        else if(val > current->n){
            if(!current->right) {
                current->right = new node(val);
                // current->right->parent = current;
                return;
            }
            else{
                current = current->right;
            }
        }
        else {cout << "Duplicate value not inserted." << endl; return;}
    }
}

node * Tree::search(node * root, int val)
{
    node * current = root;
    while(current != nullptr){
        if(current->n == val) return current;

        else if(current->n > val) current = current->left;

        else current = current->right;
    }

    return current;
}

void Tree::remove(int val)
{
    if(root == nullptr){
        cout << "Tree is empty." << endl;
        return;
    }

    node * req = root, * prev;

    //searching
    while(req != nullptr){
        if(req->n == val) break;
        else if(req->n > val) {prev = req; req = req->left;}
        else {prev = req; req = req->right;}
    }

    //null check
    if(req == nullptr){
        cout << "No such entry." << endl;
        return;
    }
    if(req == root) cout << "Root reassigned." << endl;

    node * t = req->right;

    //left subtree
    if(t == nullptr){
        //root
        if(req == root){
            root = root->left;
            delete req;

            return;
        }

        //leaf
        if(!req->left){
            if(prev->left == req) prev->left = nullptr;
            if(prev->right == req) prev->right = nullptr;
            delete req;
            return;
        }

        //general
        if(req == prev->left) prev->left = req->left;
        else prev->right = req->left;
        delete req;
        return;
    }

    //right node is successor
    if(t->left == nullptr){
        req->n = t->n;
        req->right = t->right;
        delete t;
        return;
    }

    //general

    //successor
    while(t->left->left != nullptr) t = t->left;
    node * u = t->left;
    t->left = u->right;

    //key step
    req->n = u->n;
    delete u;
}

void Tree::inorder(node * root)
{
    if(!root) return;
    inorder(root->left);
    std::cout << root->n << endl;
    inorder(root->right);
}

void Tree::preorder(node * root)
{
    if(!root) return;

    std::cout << root->n << endl;
    preorder(root->left);
    preorder(root->right);
}

void Tree::postorder(node * root)
{
    if(!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->n << endl;
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
            insert(this->root, val);
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
            inorder(this->root);
            std::cout << std::endl;
        }
        else if(cmd == "is"){
            int val;
            cin >> val;
            std::cout << std::endl;
            node * is = search(this->root, val);
            if(is) cout << "YES";
            else cout << "NO";
            std::cout << std::endl;
        }
        else if(cmd == "pre"){
            std::cout << std::endl;
            preorder(this->root);
            std::cout << std::endl;
        }
        else if(cmd == "post"){
            std::cout << std::endl;
            postorder(this->root);
            std::cout << std::endl;
        }
        else if(cmd == "destroy") return;
        else{
            std::cout << "Invalid command." << std::endl << std::endl;
        }
    }
}

Tree::~Tree()
{
    if(root->left != nullptr){
        Tree * left = new Tree();
        left->root = root->left;
        delete left;
    }

    if(root->right != nullptr){
        Tree * right = new Tree();
        right->root = root->right;
        delete right;
    }

    // cout << root->n << endl;
    delete root;
}

int main()
{
    Tree * t = new Tree();
    t->start();

    delete t;
    return 0;
}
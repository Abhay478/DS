#include <iostream>
using namespace std;

class node{
    public:
    int n;
    node * left;
    node * right;
    node * parent;
    node(int val){n = val; left = nullptr; right = nullptr; parent = nullptr;}
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
                current->left->parent = current;
                return;
            }
            else{
                current = current->left;
            }
        }
        else if(val > current->n){
            if(!current->right) {
                current->right = new node(val);
                current->right->parent = current;
                return;
            }
            else{
                current = current->right;
            }
        }
        else return;
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

// void Tree::remove(int val)
// {
//     cout << "Before." << endl;
//     node * req = search(root, val);
//     cout << "Here." << endl;
//     if(!req){
//         cout << "No such entry." << endl;
//         return;
//     
//     node * t = req->right;
//     if(!t){
//         cout << "Not t" << endl;
//         if(!req->left){
//             delete req;
//             return;
//         }
//         if(req == root){
//             this->root = this->root->left;
//             delete req;
//             cout << "Root reassigned." << endl;
//             return;
//         }
//         req->n = req->left->n;
//         node * out = req->left = req->left->left;
//         req->left = req->left->left;
//         delete out;
//         return;
//     }
//     if(!t->left){
//         cout << "Not t.left" << endl;
//         req->n = t->n;
//         req->right = nullptr;
//         delete t;
//         return;
//     }
//     while(t->left->left != nullptr) t = t->left;
//     node * suc = t->left;
//     // if(req == this->root){
//     //     this->root->n = suc->n;
//     // }
//     t->left = suc->right;
//     req->n = suc->n;
//     delete suc;
// }

void Tree::remove(int val)
{
    if(!root){
        cout << "Tree is empty." << endl;
        return;
    }
    // cout << "Here." << endl;
    node * req = search(root, val);


    if(req == nullptr){
        cout << "No such entry." << endl;
        return;
    }

    node * t = req->right;

    if(!t){
        // cout << "Not t" << endl;
        if(req == root){
            cout << "Root reassigned." << endl;
            this->root = this->root->left;
            if(root) root->parent = nullptr;
            delete req;

            return;
        }

        //parent is necessary for this exact step.
        if(!req->left){
            // cout << "this" << endl;
            if(req->parent->left == req) req->parent->left = nullptr;
            if(req->parent->right == req) req->parent->right = nullptr;
            delete req;
            return;
        }

        
        // req->n = req->left->n;
        // node * out = req->left;
        // req->left = out->left;
        // req->left->parent = req;

        req->left->parent = req->parent;

        if(req == req->parent->left) req->parent->left = req->left;
        else req->parent->right = req->left;
        delete req;
        return;
    }
    if(!t->left){
        // cout << "Not t.left" << endl;
        req->n = t->n;
        req->right = nullptr;
        delete t;
        return;
    }

    while(t->left) t = t->left;
    t->parent->left = t->right;
    if(t->right) t->right->parent = t->parent;

    req->n = t->n;
    delete t;
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
    std::cout << "add <value> : adds node to tree with given value.\n"
    "del <value> : deletes node containing given value.\n"
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
    if(this->root->left){
        Tree * left = new Tree();
        left->root = this->root->left;
        delete left;
    }

    if(this->root->right){
        Tree * right = new Tree();
        right->root = this->root->right;
        delete right;
    }

    delete this->root;
}

int main()
{
    Tree * t = new Tree();
    t->start();

    delete t;
    return 0;
}
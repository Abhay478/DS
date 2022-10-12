#include <iostream>
using namespace std;

class node{
    public:
    int n;
    node * left;
    node * right;
    node * p;

    bool c;

    node(int val, node * nil){
        n = val;
        c = true;
        left = nil;
        right = nil;
    }
};

class Tree{
    public:
    node * root;
    node * nil;

    void rrot(node ** z);
    void lrot(node ** z);

    void insert(int val);
    void cleanup(node * z);

    node * search(int val);
    void inorder(node * root);
    void preorder(node * root);
    void postorder(node * root);

    Tree()
    {
        nil = new node(-1, nullptr);
        root = nil;
    }

    void start();
};

/*
void Tree::lrot(node * z)
{
    node * x = z;
    node * y = x->right;
    // node * a = x->left;
    node * b = y->left;
    // node * c = y->right;

    if(!z->p) root = y;
    else if(z == z->p->left) z->p->left = y;
    else z->p->right = y;
    x->right = b;
    y->left = x;

    if(b) b->p = x;
    y->p = x->p;
    x->p = y;

}

void Tree::rrot(node * z)
{
    node * y = z;
    node * x = y->left;

    // node * a = x->left;
    node * b = x->right;
    // node * c = y->right;

    if(!z->p) root = x;
    else if(z == z->p->left) z->p->left = x;
    else z->p->right = x;
    y->left = b;
    x->right = y;

    if(b) b->p = y;
    x->p = y->p;
    y->p = x;


}
*/

void Tree::lrot(node ** z)
{
    node * x = *z;
    node * y = x->right;
    if(x == root) root = y;
    node * b = y->left;

    *z = y;
    y->left = x;
    x->right = b;

    y->p = x->p;
    x->p = y;
    if(b != nil) b->p = x;
    if(y == root)
        nil->left = nil->right = y;
    

}

void Tree::rrot(node ** z)
{
    node * y = *z;
    node * x = y->left;
    if(y == root) root = x;
    node * b = x->right;

    *z = x;
    x->right = y;
    y->left = b;

    x->p = y->p;
    y->p = x;
    if(b != nil) b->p = y;
    if(x == root) nil->left = nil->right = x;
}

void Tree::cleanup(node * z)
{
    node * y;

    while(z->p->c){ // z is never root (look in insert()), and so z.p not nil.
        
        //it is sufficient to reset the colour of root, if indeed the bh difference has been passed till the root's child.
        if(z->p == root){
            z->p->c = false;
            break;
        }
        
        //z.p.p is not nil, as z.p is not root.
        if(z->p == z->p->p->left){
            y = z->p->p->right;
            if(y->c){
                z->p->c = false;
                y->c = false; //its okay if y is nil.
                z->p->p->c = true;
                cout << "Here.";
                z = z->p->p;
                if(z == root || z == nil) break; //makes sure.
            }
            else {if(z == z->p->right){
                z = z->p;
                lrot(&z);
                z = z->left;
            }
            z->p->c = false;
            z->p->p->c = true;
            node * w = z->p->p;
            rrot(&w);}
        }
        else{
            y = z->p->p->left;
            if(y->c){
                z->p->c = false;
                y->c = false;
                z->p->p->c = true;
                z = z->p->p;
                if(z == root) break;
            }
            else if(z == z->p->left){
                z = z->p;
                rrot(&z);
                z = z->right;
            }
            z->p->c = false;
            z->p->p->c = true;
            rrot(&(z->p->p));
        }
    }

    root->c = false;
    nil->c = false;
}

void Tree::insert(int val)
{
    if(root == nil){
        root = new node(val, nil);
        root->c = false;
        nil->left = nil->right = root;
        root->p = nil;
        cout << "Init" << endl;
        return;
    }
    cout << "Break." << endl;
    node * x = root;
    node * y = nil;
    node * z = new node(val, nil);

    while(x != nil){
        y = x;
        if(z->n == x->n){
            cout << "Dupe." << endl;
            return;
        }
        if(z->n < x->n){
            x = x->left;
        } else x = x->right;

        // cout << "Loop";
    }
    z->p = y;
    // if(y == nil) {root = z; nil->left = nil->right = z;}
    if(z->n < y->n) y->left = z;
    else y->right = z;
    
    cout << "Fix." << endl;
    // root->p = nil;
    cleanup(z);
}

void Tree::inorder(node * root)
{
    if(root->left != nil) inorder(root->left);
    cout << root->n << ": " << (root->c?"Red":"Black") << endl;
    if(root->right != nil) inorder(root->right);
}

void Tree::preorder(node * root)
{
    cout << root->n << ": " << (root->c?"Red":"Black") << endl;
    if(root->left != nil) preorder(root->left);
    if(root->right != nil) preorder(root->right);
}

void Tree::postorder(node * root)
{
    if(root->left != nil) postorder(root->left);
    if(root->right != nil) postorder(root->right);
    cout << root->n << ": " << (root->c?"Red":"Black") << endl;
}

node * Tree::search(int val)
{
    node * c = root;
    while(c != nil){
        if(val == c->n) return c;
        if(val > c->n) c = c->right;
        else c = c->left;
    }

    return nullptr;
}

void Tree::start()
{
    std::cout << "Following are the acceptable commands : \n\n"
    "add <value> : adds node to tree with given value.\n"
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
        else if(cmd == "in"){
            std::cout << std::endl;
            inorder(this->root);
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


int main()
{
    Tree * t = new Tree();
    t->start();

    delete t;
}
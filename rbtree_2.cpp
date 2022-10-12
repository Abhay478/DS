#include <iostream>
using namespace std;
#define RED true
#define BLACK false


class node{
    public:
    int n;
    node * l;
    node * r;
    node * p;
    bool c;

    node(int val, node * nil){
        this->n = val;
        l = r = nil;
        c = RED;
    }
};

class Tree{
    public:
    node * root;
    node * nil;
    void rrot(node * z);
    void lrot(node * z);

    void insert(int val);
    // void cleanup(node * z);

    node * search(int val);
    void inorder(node * root);
    void start();
    void depth(node * q, int d);
    Tree()
    {
        nil = new node(-1, nullptr);
        root = nullptr;
    }

    /*~Tree()
    {
        Tree * l = nullptr, * r = nullptr;

        if(root->n == -1){
            if(nil) delete nil;
            delete root;
            return;
        }

        l = new Tree(root->l);
        
        r = new Tree(root->r);
        
        cout << root->n << ": " << (root->c ? "Red":"Black") << endl;
        cout << "n";
        delete nil;
        cout << "a";
        delete root;

        if(l) {cout << "l"; delete l;}
        if(r) {cout << "r"; delete r;}
    }
*/
};
//let pointers point to the same node
/*
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
*/
void Tree::lrot(node * z)
{
    node * p = z->p;
    node * c = z->l;
    node * g = p->p;
    z->p = g;
    if(g) 
        if(p == g->r) g->r = z;
        else g->l = z; 
    else root = z;
    p->p = z;
    p->r = c;
    c->p = p;
    z->l = p;
    root->c = BLACK;

}

void Tree::rrot(node * z)
{
    node * p = z->p;
    node * c = z->r;
    node * g = p->p;
    z->p = g;
    if(g)
        if(p == g->r) g->r = z;
        else g->l = z; 
    else root = z;
    p->p = z;
    p->l = c;
    c->p = p;
    z->r = p;
    root->c = BLACK;
}

void Tree::inorder(node * root)
{
    if(root == nullptr){
        cout << "Empty." << endl;
        return;
    }
    if(root->l == nullptr || root->r == nullptr){
        cout << "NULL at " << root->n << endl;
        return;
    }
    if(root->l != nil) inorder(root->l);
    cout << root->n << ": " << (root->c ? "Red":"Black") << endl;
    if(root->r != nil) inorder(root->r);
}

void Tree::insert(int val)
{
    node * p = root;
    node * u, * g;
    node * n = new node(val, nil);
    if(root == nullptr){
        root = n;
        n->p = nullptr;
        n->c = BLACK;
        cout << "Init." << endl;
        return;
        cout << "NOP";
    }
    while(true){
        if(val == p->n){
            cout << "Dupe." << endl;
            return;
        }
        if(val < p->n){
            if(p->l == nil){
                n->p = p;
                p->l = n;
                break;
            } else p = p->l;
        }
        else{
            if(p->r == nil){
                n->p = p;
                p->r = n;
                break;
            } else p = p->r;
        }
    }
    cout << "Break" << endl;


    do{
        g = p->p;

        if(p->c == BLACK) return;
        if(g == nullptr) break; 
        if(p == g->l) u = g->r;
        else u = g->l;
        if(u == nil || u->c == BLACK) break;

        p->c = BLACK;
        u->c = BLACK;
        g->c = RED;
        n = g;
        p = n->p;
        

    } while(p != nullptr);

    if(n == root){
        n->c = BLACK; 
        return;
    }

    if(p == root){
        p->c = BLACK;
        return;
    }

    if(u == nil || u->c == BLACK){
        if(p == g->l && n == p->r){
            lrot(n);
            node * t = n;
            n = p;
            p = t;
        }

        if(p == g->r && n == p->l){
            rrot(n);
            node * t = n;
            n = p;
            p = t;
        }
        
        if(n == p->l) rrot(p);            
        else lrot(p);
        p->c = BLACK;
        g->c = RED;
    }
}

node * Tree::search(int val)
{
    node * x = root;
    while(x != nil){
        if(x->n == val) return x;
        if(x->n > val) x = x->l;
        else x = x->r;
    }
    return nullptr;

}

void Tree::start()
{
    std::cout << "Following are the acceptable commands : \n\n"
    "add <value> : adds node to tree with given value.\n"
    "is <value> : prints 'yes' if vaule exists, 'no' otherwise.\n"
    "in : inorder traversal.\n"
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
        /*
        else if(cmd == "pre"){
            std::cout << std::endl;
            preorder(this->root);
            std::cout << std::endl;
        }
        else if(cmd == "post"){
            std::cout << std::endl;
            postorder(this->root);
            std::cout << std::endl;
        }*/
        
        else if(cmd == "destroy") return;
        else{
            std::cout << "Invalid command." << std::endl << std::endl;
        }
    }
}

void Tree::depth(node * q, int d)
{
    int k = d + 1;
    if(q == nil) return;
    while(d--)
        cout << "    ";
    
    
    cout << q->n << ": " << (q->c ? "Red":"Black") << endl;
    depth(q->l, k);
    depth(q->r, k);
}

int main()
{
    Tree * t = new Tree();
    t->start();

    t->depth(t->root, 0);

    delete t;
    return 0;
}
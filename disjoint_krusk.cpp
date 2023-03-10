/*******
 * Kruskal's algorithm
 * for CS2233
 * by Abhay Shankar K
 * cs21btech11001
*/


#include <iostream>
#include <vector>
using namespace std;

#define parent(i) ((i - 1) / 2)
#define left(i) (2*i + 1)
#define right(i) (2*i + 2)

class Edge{
    public:
    int v1, v2, w;

    void operator = (const Edge e){
        v1 = e.v1;
        v2 = e.v2;
        w = e.w;
    }

    void print(){
        cout << v1 << " " << v2 << " " << w << endl;
    }
};

void siftdown(vector<Edge> &a, int start, int end)
{
    int r = start;
    int lc = left(r);
    while((lc = left(r)) <= end){
        int s = r;
        if(a[s].w < a[lc].w) s = lc;
        if(lc + 1 <= end && a[lc + 1].w > a[s].w) s = lc + 1;
        if(s == r) return;
        else{
            Edge t = a[r];
            a[r] = a[s];
            a[s] = t;
            r = s;
        }
    }
}

void heapify(vector<Edge> &a)
{
    int l = a.size();
    
    for(int s = parent(l - 1); s >= 0; s--)
        siftdown(a, s, l - 1);

}

void sort(vector<Edge> &a)
{
    // for(auto i : a) cout << i << " ";
    heapify(a);
    // for(auto i : a) cout << i << " ";
    int e = a.size() - 1;
    while(e > 0){
        Edge t = a[0];
        a[0] = a[e];
        a[e] = t;

        e--;
        siftdown(a, 0, e);
    }
}

class Tree{
    public:
    vector<int> v;
    vector<Edge> e;
    Tree * next;
    Tree * prev;

    void merge(Tree * tr){
        for(auto i : tr->v) v.push_back(i);

        for(auto i : tr->e) e.push_back(i);
    }

    Tree(int n){
        v.push_back(n);
        next = nullptr;
        prev = nullptr;
    }

    bool find(int u){
        for(auto i : v)
            if(i == u) return true;
        
        return false;
    }
    
    int weight(){
        int out = 0;
        for(auto edge : e)
            out += edge.w;
        
        return out;
    }
};

class Forest{
    public:
    Tree * head; // disjoint set
    
    Forest(int V){
        head = new Tree(1);
        Tree * current = head;
        for(int i = 2; i <= V; i++){
            current->next = new Tree(i);
            current->next->prev = current;
            current = current->next; 
        }

        //we now have V trees each with one node.
    }

    Tree * find(int u)
    {
        Tree * current = head;
        while(!current->find(u)) current = current->next;
        return current;
    }

    void add(Edge e){
        Tree * l = find(e.v1);
        Tree * r = find(e.v2);
        if(l == r) //edge repeats
            return;
        
        if(r == head) head = r->next;
        // we know edge connects two trees
        //delete r from list
        if(r->prev) r->prev->next = r->next;
        if(r->next) r->next->prev = r->prev;

        // add new edge to l
        l->e.push_back(e);
        // add edges and vertices of r to l
        l->merge(r);

        delete r;

    }

    void print(){
        Tree * current = head;
        while(current){
            cout << "Vertices: " << current->v.size() << endl;
            cout << "Edges: " << current->e.size() << endl;
            cout << "Weight: " << current->weight() << endl;

            sort(current->e);
            for(auto edge : current->e){
                edge.print();
            }

            cout << endl << endl;
            current = current->next;
        }
    }

};

class Graph{
    public:
    int V;
    vector<Edge> e;
    Graph(int V, vector<Edge> e){
        this->V = V;
        this->e = e;
    }
    Forest * kruskal()
    {
        Forest * out = new Forest(V);
        for(auto edge : e){
            out->add(edge);
        }
        return out;
    }
};

int main()
{
    cout << "Enter number of vertices" << endl;
    int V;
    cin >> V;

    cout << "Enter number of edges." << endl;
    int E;
    cin >> E;

    vector<Edge> e;
    // Edge e[E];
    cout << "Enter edges : vertex-1 vertex-2 weight" << endl;
    for(int i = 0; i < E; i++){
        Edge x;
        cin >> x.v1 >> x.v2 >> x.w;
        e.push_back(x);
        // e[i] = x;
    }

    sort(e);
    // vector<Edge> e2 = sort(e);

    Graph * G = new Graph(V, e);
    Forest * f = G->kruskal();
    f->print();
}
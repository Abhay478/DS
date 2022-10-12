// #include <iostream>
// #include <vector>
// using namespace std;
// void sort(vector<int> a)
// {
//     int l = a.size();
//     for(int i = l; i > 0; i--){
//         int p = i;
//         while(a[p] > a[p / 2] && p > 1){
//             int t = a[p];
//             a[p] = a[p / 2];
//             a[p/2] = t;
//             p = p / 2;
//         }
//     }
//     a.erase(a.begin());
//     while(!a.empty()){
//         int out = a[0];
//         int p = 0;
//         a[p] = a.at(a.size() - 1);
//         a.pop_back();
//         int l = 1, r = 2;
//     if(l >= a.size()) {cout << out << endl; return;}
//     if(r >= a.size()) r = l;
//     int min = a.at(l) > a.at(r) ? l : r;
//     // cout << "Stuff :" << a[p] << " " << a[min] << endl;
//     while(a[p] < a[min]){
//         int temp = a.at(min);
//         a[min] = a.at(p);
//         a[p] = temp;
//         // for(auto x : a)
//         // cout << x << " ";
//         // cout << endl;
//         p = min;
//         l = 2*p + 1;
//         r = 2*p + 2;
//         if(l >= a.size()) {
//             // cout << "breaking." << endl; 
//             break;
//         }
//         if(r >= a.size()) {
//             // cout << "Set." << endl; 
//             r = l;
//         }
//         min = a.at(l) > a.at(r) ? l : r;
//     }
//     cout << out << endl;
//     }
// }
// void sort2(vector<int> a)
// {
//     int l = a.size();
//     l /= 2;
//     for(int i = l; i > 0; i--){
//         int p = i;
//         int ch = a[2*p] > a[2*p + 1] ? 2*p : 2*p + 1;
//         while(a[p] < a[ch] && ch <= l){
//             int t = a[p];
//             a[p] = a[ch];
//             a[ch] = t;
//             p = ch;
//             ch = (a[2*p] > a[2*p + 1]) ? 2*p : 2*p + 1;
//         }
//     }
//     for(auto j : a){
//         cout << j << endl;
//     }
// }
// int main()
// {
//     vector<int> a;
//     a.push_back(0);
//     int x;
//     while(cin >> x && x != -1){
//         a.push_back(x);
//     }
//     sort(a);
// }

#include <iostream>
#include <vector>
using namespace std;
void sift(vector<int> a, int start, int end)
{
    int r = start;
    while(2*r + 1 <= end){
        int lc = 2*r + 1;
        int s = r;
        if(a[s] < a[lc]) s = lc;
        if(lc < end && a[s] < a[lc + 1]) s = lc + 1;
        if(s == r) return;
        else{
            int t = a[r];
            a[r] = a[s];
            a[s] = t;
            r = s;
        }
    }
}

void heapify(vector<int> a)
{
    int l = a.size();
    for(int s = l / 2 - l%2; s >= 0; s--)
        sift(a, s, l - 1);
    
}

int main()
{
    vector<int> a = {5, 1, 2, 6, 4, 3};
    heapify(a);

    for(auto i : a) cout << i << " ";
}
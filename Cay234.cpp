#include <iostream>
using namespace std;

struct Node{
    int keys[3];
    int count;
};

int main(){
    Node node;
    node.count=0;

    node.keys[node.count++]=30;
    node.keys[node.count++]=40;
    node.keys[node.count++]=50;

    cout<<"2-3-4 Tree node: ";
    for(int i=0;i<node.count;i++)
        cout<<node.keys[i]<<" ";
}

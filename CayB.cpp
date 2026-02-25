#include <iostream>
using namespace std;

struct Node{
    int key;
    Node *left,*right;
};

Node* newNode(int key){
    Node* n=new Node();
    n->key=key;
    n->left=n->right=NULL;
    return n;
}

Node* insert(Node* root,int key){
    if(!root) return newNode(key);
    if(key < root->key) root->left=insert(root->left,key);
    else root->right=insert(root->right,key);
    return root;
}

void inorder(Node* root){
    if(root){
        inorder(root->left);
        cout<<root->key<<" ";
        inorder(root->right);
    }
}

int main(){
    Node* root=NULL;
    root=insert(root,30);
    root=insert(root,40);
    root=insert(root,10);

    cout<<"BTree (demo): ";
    inorder(root);
}

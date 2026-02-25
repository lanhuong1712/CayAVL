#include <iostream>
using namespace std;

enum Color{RED,BLACK};

struct Node{
    int data;
    Color color;
    Node *left,*right,*parent;
};

Node* root=NULL;

Node* newNode(int data){
    Node* n=new Node();
    n->data=data;
    n->color=RED;
    n->left=n->right=n->parent=NULL;
    return n;
}

void rotateLeft(Node*& root,Node*& x){
    Node* y=x->right;
    x->right=y->left;
    if(y->left) y->left->parent=x;
    y->parent=x->parent;

    if(!x->parent) root=y;
    else if(x==x->parent->left) x->parent->left=y;
    else x->parent->right=y;

    y->left=x;
    x->parent=y;
}

void rotateRight(Node*& root,Node*& x){
    Node* y=x->left;
    x->left=y->right;
    if(y->right) y->right->parent=x;
    y->parent=x->parent;

    if(!x->parent) root=y;
    else if(x==x->parent->left) x->parent->left=y;
    else x->parent->right=y;

    y->right=x;
    x->parent=y;
}

Node* BSTInsert(Node* root,Node* pt){
    if(!root) return pt;

    if(pt->data < root->data){
        root->left=BSTInsert(root->left,pt);
        root->left->parent=root;
    }else{
        root->right=BSTInsert(root->right,pt);
        root->right->parent=root;
    }
    return root;
}

void insert(int data){
    Node* pt=newNode(data);
    root=BSTInsert(root,pt);
    root->color=BLACK;   // b?n rút g?n
}

void inorder(Node* root){
    if(root){
        inorder(root->left);
        cout<<root->data<<" ";
        inorder(root->right);
    }
}

int main(){
    insert(20);
    insert(30);
    insert(10);

    cout<<"RedBlack: ";
    inorder(root);
}

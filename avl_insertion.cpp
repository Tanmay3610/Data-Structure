#include<bits/stdc++.h>
using namespace std;

typedef struct Tree{
    struct Tree *left;
    struct Tree *right;
    int data;
    int height;
}Tree;

int height(Tree *node){
    if(node == NULL)
        return 0;
    return node->height;
}

int checkBalance(Tree* node){
    if(node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

Tree* newNode(int data){
    Tree* Node = (Tree*)malloc(sizeof(Tree));
    Node->data = data;
    Node->left = NULL;
    Node->right = NULL;
    Node->height = 1;
    return Node;
}

Tree* leftRotate(Tree* node){
    Tree* x = node->right;
    Tree* temp = x->left;
    x->left = node;
    node->right = temp;
    node->height = 1 + max(height(node->right), height(node->left));
    x->height = 1 + max(height(x->right), height(x->left));
    return x;
}

Tree* rightRotate(Tree* node){
    Tree* x = node->left;
    Tree* temp = x->right;
    x->right = node;
    node->left = temp;
    node->height = 1 + max(height(node->left), height(node->right));
    x->height = 1 + max(height(x->right), height(x->left));
    return x;
}

void printTree(Tree* root){
    if(root == NULL)
        return;
    printTree(root->left);
    cout<<root->data<<" ";
    printTree(root->right);
}

Tree* avl_tree(Tree* root, int data){  
    if(root == NULL){
        return (newNode(data));
    }
    
    if(data > root->data){
            root->right = avl_tree(root->right, data);
    }
    
    else if(data < root->data){
            root->left = avl_tree(root->left, data);
    }
    
    else
        return root;
    
    root->height = 1 + max(height(root->right), height(root->left));
    int balance = checkBalance(root);
    if (balance < -1 && data > root->right->data){
        return leftRotate(root);
    }
    if(balance > 1 && data < root->left->data){
        return rightRotate(root);
    }
    if(balance < -1 && data < root->right->data){
        root->right = rightRotate(root->right);
        return (leftRotate(root));
    }
    if(balance > 1 && data > root->right->data){
        root->left = leftRotate(root->left);
        return (rightRotate(root));
    }
    return root;
}

int main(){
    int array[] = {1,2,3,4,5,6,7,8,9};
    Tree* root = NULL;
    int size = sizeof(array)/sizeof(array[0]);
    for(int i = 0; i<size; i++)
        root = avl_tree(root, array[i]);
    printTree(root);
    return 0;
}

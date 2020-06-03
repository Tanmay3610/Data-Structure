#include<bits/stdc++.h>
using namespace std;

typedef struct Tree{
    struct Tree* left;
    struct Tree* right;
    int data;
    int height;
}Tree;

Tree* newNode(int data){
    Tree *node = (Tree*)malloc(sizeof(Tree));
    node->data = data;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int height(Tree* node){
    if(node == NULL)
        return 0;
    return node->height;
}

int getBalanceFactor(Tree* root){
    if(root == NULL)
        return 0;
    return height(root->left) - height(root->right);
}

Tree* rightRotate(Tree* node){
    Tree* x = node->left;
    Tree* temp = x->right;
    node->left = temp;
    x->right = node;
    x->height = 1 + max(height(x->left), height(x->left));
    node->height = 1 + max(height(node->left), height(node->right));
    return x;
}

Tree* leftRotate(Tree* node){
    Tree* x = node->right;
    Tree* temp = x->left;
    x->left = node;
    node->right = temp;
    node->height = 1 + max(height(node->left), height(node->right));
    x->height = 1 + max(height(x->right), height(x->left));
    return x;
}

Tree* insert(int key, Tree* root){
    if(root == NULL)
        return newNode(key);
    if(key > root->data){
        root->right = insert(key, root->right);
    }
    else if(key < root->data){
        root->left = insert(key, root->left);
    }
    else return root;

    root->height = 1 + max(height(root->right), height(root->left));
    int balance = getBalanceFactor(root);
    if(balance > 1 && key < root->data){
        return rightRotate(root);
    }
    if(balance < -1 && key > root->data){
        return leftRotate(root);
    }
    if(balance > 1 && key > root->data){
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if(balance < -1 && key < root->data){
        root->right = rightRotate(root->right);
    }    
    return root;
}

void printTree(Tree* root){
    if(root == NULL)
        return;
    printTree(root->left);
    cout<<root->data<<" ";
    printTree(root->right);
}

Tree* getInorderSuccesor(Tree* node){
    if(node->left == NULL)
        return node;
    getInorderSuccesor(node->left);
}

Tree* deleteKey(int key, Tree* root){
    if(root == NULL)
        return root;
    if(key > root->data){
        cout<<"Check1....";
        root->right = deleteKey(key, root->right);
    }        
    if(key < root->data){
        cout<<"check....left"<<endl;
        root->left = deleteKey(key, root->left);
    }        
    else{
        if(root -> left == NULL){
            Tree* temp = root->right;
            free(root);
            return temp;
        }
        else if(root->right == NULL){
            Tree* temp = root->left;
            free(root);
            return temp;
        }
        else{
            Tree* temp = getInorderSuccesor(root->right);
            root->data = temp->data;
            root->right = deleteKey(temp->data, root->right);
        }
    }
    if(root == NULL)
        return root;
    
    root->height = 1 + max(height(root->right), height(root->left));
    int balance = getBalanceFactor(root);
    if(balance > 1 && getBalanceFactor(root->left) >= 0)
        return rightRotate(root);
    if(balance < -1 && getBalanceFactor(root->right) <= 0)
        return leftRotate(root);
    if(balance > 1 && getBalanceFactor(root->left) < 0){
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if(balance < -1 && getBalanceFactor(root->right) > 0){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

int main(){
    int array[] = {1,2,3,4,5,6,7,8,9};
    int size = sizeof(array)/sizeof(array[0]);
    Tree* root = NULL;
    for(int i = 0; i<size; i++)
        root = insert(array[i], root);
    printTree(root);
    root = deleteKey(2, root);
    cout<<endl;
    printTree(root);
    return 0;
}

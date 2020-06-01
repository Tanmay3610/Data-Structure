#include<bits/stdc++.h>
using namespace std;

typedef struct Tree{
    struct Tree* Right;
    struct Tree* Left;
    int data;
}Tree;

Tree* create_bst(Tree* root, int data){
    Tree* newNode = (Tree*)malloc(sizeof(Tree));
    newNode->data = data;
    newNode->Right = NULL;
    newNode->Left = NULL;
    if(root == NULL){
        root = newNode;
    }
    else if (data <= root->data){
        root->Left = create_bst(root->Left, data);
    }
    else{
        root->Right = create_bst(root->Right, data);
    }
    return root;    
}

void print_tree(Tree* root){
    if(root == NULL)
        return;
    cout<<(root->data)<<" ";
    print_tree(root->Left);
    print_tree(root->Right);
}

int main(){
    int tree_data[] = {30, 40, 10, 50, 20, 5, 35}; //set of keys
    int length = sizeof(tree_data)/sizeof(tree_data[0]);
    Tree* root = NULL;
    for(int i = 0; i<length; i++)
        root = create_bst(root , tree_data[i]);
    print_tree(root);
}

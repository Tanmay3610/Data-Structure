#include<bits/stdc++.h>
using namespace std;

vector <int> inOrder;
int ptr = 0;
typedef struct Tree{
    struct Tree* left;
    struct Tree* right;
    int data;
}Tree;

Tree* create_tree(){
    int data;
    cin>>data;
    if(data == 0)
        return NULL;
    Tree* newNode = (Tree*)malloc(sizeof(Tree));
    newNode->data = data;
    cout<<"Enter the left child"<<endl;
    newNode->left = create_tree();
    cout<<"Enter the right child"<<endl;
    newNode->right = create_tree();
    return newNode;
}

void saveinOrder(Tree* root){
    if(root == NULL)
        return;
    saveinOrder(root->left);
    inOrder.push_back(root->data);
    saveinOrder(root->right);
}

void tree2bst(Tree* root){
    if(root == NULL)
        return;
    tree2bst(root->left);
    root->data = inOrder[ptr];
    ptr = ptr + 1;
    tree2bst(root->right);

}

void sortinOrder(){
    for(int i = 0; i<inOrder.size() - 1; i++){
        for(int j = 0; j<inOrder.size() - i - 1; j++){
            if(inOrder[j] > inOrder[j+1]){
                int temp = inOrder[j];
                inOrder[j] = inOrder[j+1];
                inOrder[j+1] = temp;
            }
        }
    }
}

void printTree(Tree* root){
    if(root == NULL)
        return;
    printTree(root->left);
    cout<<root->data<<" ";
    printTree(root->right);
}

int main(){
    Tree *root = create_tree();
    saveinOrder(root);
    sortinOrder();
    tree2bst(root);
    printTree(root);
    return 0;
}

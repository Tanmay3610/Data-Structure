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

//This is inorder printing of Tree
void print_tree(Tree* root){ 
    if(root == NULL)
        return;
    cout<<(root->data)<<" ";
    print_tree(root->Left);
    print_tree(root->Right);
}

Tree* getInorderSuccesor(Tree* root){
    if(root->Left == NULL)
        return root;
    getInorderSuccesor(root->Left);
}

Tree* delete_key(Tree* root, int key){
    if(root == NULL){
        cout<<"Can't find the key, Hence, cnat be deleted!";
        return root;
    }
    if(key > root->data)
        root->Right = delete_key(root->Right, key);
    else if(key < root->data)
        root->Left = delete_key(root->Left, key);
    else{
        if(root->Right == NULL && root->Left == NULL)
            free(root);
        else if(root->Right == NULL && root->Left != NULL){
            Tree* temp = root->Left;
            free(root);
            return temp;
        }
        else if(root->Right != NULL && root->Left == NULL){
            Tree* temp = root->Right;
            free(root);
            return temp;
        }
        else{
            Tree* temp = getInorderSuccesor(root->Right);
            root->data = temp->data;
            root->Right = delete_key(root->Right, temp->data);
        }
    }
    return root;    
}

int main(){
    int tree_data[] = {50, 40, 35, 30, 20, 10, 5}; 
    int length = sizeof(tree_data)/sizeof(tree_data[0]);
    Tree* root = NULL;
    for(int i = 0; i<length; i++)
        root = create_bst(root , tree_data[i]);
    cout<<"Tree before deletion"<<endl;
    print_tree(root);
    delete_key(root, 20);  
    cout<<endl;
    cout<<"Tree after deletion"<<endl;
    print_tree(root);
    return 0;
}

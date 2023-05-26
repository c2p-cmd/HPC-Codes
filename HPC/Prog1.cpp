//
//  Prog1.cpp
//  HPC - BFS
//
//

#include <stdio.h>
#include <iostream>
#include <queue>


class node
{
public:
    node *left, *right;
    int data;
};

class Breadthfs
{
public:
    node* insert(node* root, int data)
    {
        if (!root)
        {
            root=new node;
            root->left=NULL;
            root->right=NULL;
            root->data=data;
            return root;
        }
        
        std::queue<node *> q;
        q.push(root);
        
        while (!q.empty())
        {
            node *temp=q.front();
            q.pop();
            if(temp->left==NULL)
            {
                temp->left=new node;
                temp->left->left=NULL;
                temp->left->right=NULL;
                temp->left->data=data;
                return root;
            }
            else
            {
                q.push(temp->left);
            }
            
            if(temp->right==NULL)
            {
                temp->right=new node;
                temp->right->left=NULL;
                temp->right->right=NULL;
                temp->right->data=data;
                return root;
            }
            else
            {
                q.push(temp->right);
            }
            
        }
        return NULL;
    }
    
    void bfs(node* head)
    {
        std::queue<node*> q;
        q.push(head);
        
        long qSize;
        
        while (!q.empty())
        {
            qSize = q.size();
#pragma omp parallel for
            //creates parallel threads
            for (int i = 0; i < qSize; i++)
            {
                node* currNode;
#pragma omp critical
                {
                    currNode = q.front();
                    q.pop();
                    std::cout<<"\t"<<currNode->data;
                    
                }// prints parent node
#pragma omp critical
                {
                    if(currNode->left)// push parent's left node in queue
                        q.push(currNode->left);
                    if(currNode->right)
                        q.push(currNode->right);
                }// push parent's right node in queue
                
            }
            
        }
    }
};

int main()
{
    node *root=NULL;
    int data;
    char ans;
    Breadthfs *bfsPtr = new Breadthfs;
    
    do
    {
        std::cout << "\n enter data=>";
        std::cin >> data;
        
        root = bfsPtr->insert(root,data);
        
        std::cout << "do you want insert one more node?";
        std::cin >> ans;
        
    } while(ans == 'y' || ans == 'Y');
    
    bfsPtr->bfs(root);
    std::cout << "\nBye" << std::endl;
    
    return 0;
}

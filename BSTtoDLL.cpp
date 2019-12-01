/*  Convert a binary search tree into doubly linked list inplace.
	left pointer of tree will act as previous pointer of linked list and
	right pointer will act as next pointer of linked list.	

	time-complexity = O(n)
	space-complexity = O(1)

	Author - Akshay
	Date - 1st Dec, 2019

*/


#include <iostream>
using namespace std;


struct TreeNode
{
	int data;
	TreeNode *left;
	TreeNode *right;
};

//function to create a new node in BST
TreeNode *newNode(int data)
{
	TreeNode *new_node = (TreeNode *)malloc(sizeof(TreeNode));
	new_node->data = data;
	new_node->left = new_node->right = NULL;
	return new_node;
}

//Function to insert a node in BST with value key
TreeNode* insert(TreeNode* root, int key) 
{ 
    //if tree is empty just return the newly created node
    if (root == NULL) 
    	return newNode(key); 
  
    if (key < root->data) 
        root->left  = insert(root->left, key); 
    else if (key > root->data) 
        root->right = insert(root->right, key);    
  
    return root; 
} 

//function to traverse the tree in inorder(left,node,right) fashion.
void printInorder(TreeNode* root) 
{ 
    if (root == NULL) 
        return; 
  
    printInorder(root->left); 
    cout << root->data << " "; 
    printInorder(root->right); 
} 

 
TreeNode* left_rotate(TreeNode *temp)
{
	TreeNode *temp1 = temp->right;
	temp->right = temp1->left;
	temp1->left = temp;
	temp = temp1;
	return temp;
}

TreeNode* right_rotate(TreeNode *temp)
{
	TreeNode *temp1 = temp->left;
	temp->left = temp1->right;
	temp1->right = temp;
	temp = temp1;
	return temp;
}

//function to convert BST to doubly linked list. This function will return the head of the linked list
TreeNode *BST_to_DLL(TreeNode *root)
{
	TreeNode *temp_root = root;
	
	/*
		while left child has right child,rotate left till the left child has no right child. then point the left child's
		right back to the parent. Keep doing this till left subtree of root becomes a long list.
	*/
	while(temp_root->left)
	{
		TreeNode *temp = temp_root->left;
		while(temp->right)
		{
			temp = left_rotate(temp);
		}
		temp->right = temp_root;
		temp_root->left = temp;
		temp_root = temp_root->left;
	}
	//left most node of the root will become head of linked list
	TreeNode *head = temp_root;

	temp_root = root;
	/*
		while right child has left child,rotate right till the right child has no left child. then point the right child's
		left back to the parent. Keep doing this till right subtree of root becomes a long list.
	*/
	while(temp_root->right)
	{
		TreeNode *temp = temp_root->right;
		while(temp->left)
		{
			temp = right_rotate(temp);
		}
		temp->left = temp_root;
		temp_root->right = temp;
		temp_root = temp_root->right;
	}

	return head;
}

//function to print the doubly linked list
void print_list(TreeNode *head)
{
	TreeNode *temp = head;
	while(head)
	{
		if(head->left!=NULL)
			cout << head->data <<"->left = " << head->left->data << ",";
		else
		    cout << head->data <<"->left = NULL" << ",";
		if(head->right!=NULL)
			cout << head->data <<"->right = " << head->right->data << endl;
		else
		    cout << head->data <<"->right = NULL"<< endl;
		head = head->right;
		
	}
	cout << "---------------------------------\n";
	cout << "So final linked list:"<<endl;
	while(temp->right)
	{
	    cout << temp->data << "---";
	    temp = temp->right;
	}
	cout << temp->data<<endl;
	
}

int main()
{
	cout << "Enter no of nodes for BST : ";
	int no_of_nodes;
	while(1)
	{
	    cin >> no_of_nodes;
	    if(no_of_nodes <= 0)
	    {
	        cout << "No of nodes should be greater than 0, Enter again: ";
	        continue;
	    }
	    break;
	}

	cout << "---------------------------------\n";
	cout << "Enter values : ";
	TreeNode* root = NULL;
	for(int i=0;i<no_of_nodes;i++)
	{
		int val;
		cin >> val;
		if(!root)
			root = insert(root,val);
		else
			insert(root,val);
	}
    
    cout << "---------------------------------\n";
    
    cout << "Inorder Traversal of tree = ";
	printInorder(root);
	cout << endl;

	TreeNode *list_head = BST_to_DLL(root);
    
    cout << "---------------------------------\n";
	print_list(list_head);

}
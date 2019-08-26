#include <iostream>

struct node{
	int val;
	struct node* left_child;
	struct node* right_child;
};

node* initialise_BST_node(int val);
void print_BST(node* root);
void delete_BST(node* root);
void insert(node* root, int val);
void delete_node(node* root, int val, node* prev_node);

int main(){
	node* root = initialise_BST_node(5);
	insert(root, 3);
	insert(root, 10);
	insert(root, 4);
	insert(root, 8);
	insert(root, 14);
	insert(root, 1);
	print_BST(root);
	std::cout << std::endl;
	delete_node(root, 8, NULL);
	print_BST(root);
	std::cout << std::endl;
	delete_BST(root);
}

node* initialise_BST_node(int val){
	node* root = new node();
	root->val = val;
	root->left_child = NULL;
	root->right_child = NULL;
	return root;	
}

void print_BST(node* root){
	if (root->left_child != NULL)
		print_BST(root->left_child);
	std::cout << root->val << " ";
	if (root->right_child != NULL)
		print_BST(root->right_child);
}

void delete_BST(node* root){
	if (root->left_child != NULL)
		delete_BST(root->left_child);
	if (root->right_child != NULL)
		delete_BST(root->right_child);
	delete root;
}

void insert(node* root, int val){
	if (val == root->val)
		return;
	
	if (val < root->val){
		if (root->left_child != NULL)
			insert(root->left_child, val);
		else{
			node* new_node = initialise_BST_node(val);
			root->left_child = new_node;
		}
	}else{
		if (root->right_child != NULL)
			insert(root->right_child, val);
		else{
			node* new_node = initialise_BST_node(val);
			root->right_child = new_node;
		}
	}
}

void delete_node(node* root, int val, node* prev_node){
	if (root->left_child != NULL && val < root->val)
		delete_node(root->left_child, val, root);
	if (root->right_child != NULL && val > root->val)
		delete_node(root->right_child, val, root);

	if (root->val == val){
		node* replacing_node = NULL;
		if (root->left_child != NULL && root->left_child != NULL){
			replacing_node = root->right_child;
			while (replacing_node->left_child != NULL){
				replacing_node = replacing_node->left_child;
			}			
		}
		else if (root->left_child != NULL)
			replacing_node = root->left_child;	
		else if	(root->right_child != NULL)
			replacing_node = root->right_child;

		if (replacing_node != NULL){
			replacing_node->left_child = root->left_child;
			replacing_node->right_child = root->right_child;
		}

		if (prev_node != NULL){
			if (prev_node->left_child == root)
				prev_node->left_child = replacing_node;
			if (prev_node->right_child == root)
				prev_node->right_child = replacing_node;				
		}
		delete root;
	}
}

	
	


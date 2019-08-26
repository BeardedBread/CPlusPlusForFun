#include <iostream>

struct node{
	int val;
	node *next;
};

node* initiate_linked_list(int val);
void print_linked_list(node* head);
void push(node** head, int val);
int pop(node* head);
int search(node* head, int val);
void delete_linked_list(node* head);
node* recursive_reverse(node* head);

int main(){
	node *head = initiate_linked_list(1);
	print_linked_list(head);
	push(&head, 5);
	push(&head, 2);
	push(&head, 7);
	push(&head, 9);
	print_linked_list(head);
	head = recursive_reverse(head);
	print_linked_list(head);
	std::cout << search(head, 7) << std::endl;
	std::cout << search(head, 10) << std::endl;
	pop(head);
	print_linked_list(head);
	delete_linked_list(head);
}

node* initiate_linked_list(int val){
	node *head = new node();
	head->val = val;
	return head;
}

void print_linked_list(node* head){
	node *current_node = head;
	while (current_node != NULL){
		std::cout << current_node->val << " ";
		current_node = current_node->next;
	}
	std::cout << std::endl;
}

void push(node** head, int val){
	node *new_node = new node();
	new_node->val = val;
	new_node->next = *head;
	*head = new_node;
}

int pop(node* head){
	node *current_node = head;
	while (current_node->next->next != NULL){
		current_node = current_node->next;
	}
	int val = current_node->next->val;
	delete current_node->next;
	current_node->next = NULL;
	return val;
}

int search(node* head, int val){
	node *current_node = head;
	int index = 0;
	while (current_node != NULL){
		if (current_node->val == val)
			return index;
		current_node = current_node->next;
		++index;
	}
	return -1;
}

void delete_linked_list(node* head){
	node *current_node = head;
	node *next_node;
	while (current_node != NULL){
		next_node = current_node->next;
		delete current_node;
		current_node = next_node;
	}
}

node* recursive_reverse(node* head){
	node* current_node = head; // For clarity
	if (current_node->next != NULL){
		node* new_head = recursive_reverse(current_node->next);
		current_node->next->next = current_node;
		current_node->next = NULL;
		return new_head;
	}else{
		return current_node;
	}
	
}

/** This is the code for sorting linked list using mergesort
as a practice using C++. Also for practice using Vim :p
Feel free to modify.
**/

#include <iostream>
#include <stdlib.h>
#include <time.h>

struct node{
	int val;
	node *next;
};

int generate_random_number(int upper_bound);
node* initiate_linked_list(int val);
void print_linked_list(node* head);
void push(node** head, int val);
void delete_linked_list(node* head);
node* merge_sort(node* head);

int main(int argc, char** argv){
	int n;
	int upper_bound;
	// Input checking. Could've used a loop, but I'm not bothered :p
	if(argc == 3){
		char* endp;
		char* endp2;
		int val = strtol(argv[1], &endp, 10);
		int val2 = strtol(argv[2], &endp2, 10);
		if (!*endp && !*endp2){
			n = val;
			upper_bound = val2;
		}else{
			std::cout << "Usage: ./mergesort val1 val2"<< std::endl;
			std::cout << "val1 is the length of the array, int" << std::endl;
			std::cout << "val2 is the upper bound of the random number (exclusive), int" << std::endl;
			return 1;
		}
	}else{
		std::cout << "Usage: ./mergesort val1 val2"<< std::endl;
		std::cout << "val1 is the length of the array, int" << std::endl;
		std::cout << "val2 is the upper bound of the random number (exclusive), int" << std::endl;
		return 1;
	}

	srand (time(NULL));
	node* head = initiate_linked_list(generate_random_number(upper_bound));
	--n;

	for(int i=0;i<n;++i){
		push(&head, generate_random_number(upper_bound));
	}

	std::cout << "Before: "<<std::endl;
	print_linked_list(head);
	head = merge_sort(head);

	std::cout << "After: "<<std::endl;
	print_linked_list(head);
	delete_linked_list(head);
}


node* merge_sort(node* head){
	// Return if list is only one node
	if (head->next == NULL)
		return head;

	// Get to the half way of the list
	node *p1 = head, *p2 = head;
	while(p1->next != NULL && p1->next->next != NULL){
		p1 = p1->next->next;
		p2 = p2->next;
	}

	// Break into two lists
	p1 = p2->next;
	p2->next = NULL; 
	
	// Sort the two halves, recursively
	p1 = merge_sort(p1);
	//print_linked_list(p1);
	p2 = merge_sort(head);
	//print_linked_list(p2);
	
	node *newHead = NULL;
	node *current;
	node **smaller; // Address of pointer of smaller value
	// If either still have an element
	while(p1 != NULL || p2 != NULL){
		// Get whichever address of pointer to smaller value
		// Get the other if one is null
		if(p1 == NULL)
			smaller = &p2;
		else if(p2 == NULL)
			smaller = &p1;
		else{
			if(p1->val < p2->val)
				smaller = &p1;
			else
				smaller = &p2;
		}

		// If newHead is null (first element), make one
		// Otherwise append the current node
		// Require dereferencing the smaller variable
		if (newHead == NULL){
			newHead = *smaller;
		}else{
			current->next = *smaller;
		}
		// Make the current pointer at the appended node
		current = *smaller;
		// Shift the pointer of the smaller value to the next
		*smaller = (*smaller)->next;			
	}
	return newHead;
}

int generate_random_number(int upper_bound){
	return rand() % upper_bound;
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

void delete_linked_list(node* head){
	node *current_node = head;
	node *next_node;
	while (current_node != NULL){
		next_node = current_node->next;
		delete current_node;
		current_node = next_node;
	}
}


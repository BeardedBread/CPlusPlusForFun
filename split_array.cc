/**This is the code for search an index in a splitted sorted array
   Thought it was interesting. 
   If there are duplicate elements, it is not guarantee that the index return
   is the smallest index.**/

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

int generate_random_number(int upper_bound);
void print_array(int array[], int n);
int binary_search(int array[], int lo, int hi, int val);
int splitted_array_search(int split_array[], int lo, int hi, int val, int n);

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
			std::cout << "Usage: ./split_array val1 val2"<< std::endl;
			std::cout << "val1 is the length of the array, int" << std::endl;
			std::cout << "val2 is the upper bound of the random number (exclusive), int" << std::endl;
			return 1;
		}
	}else{
		std::cout << "Usage: ./split_array val1 val2"<< std::endl;
		std::cout << "val1 is the length of the array, int" << std::endl;
		std::cout << "val2 is the upper bound of the random number (exclusive), int" << std::endl;
		return 1;
	}
	// Randomisation
	srand (time(NULL));

	int array[n];
	for(int i=0;i<n;++i){
		array[i] = generate_random_number(upper_bound); 
	}
	// Sort it
	std::sort(array, array+n);
	std::cout << "Original" << std::endl;
	print_array(array, n);	
	// Split array, put as a separate array
	int split_ind = generate_random_number(n);
	std::cout << "Split point: " << array[split_ind] << std::endl;
	int split_array[n];
	for(int i=0;i<n-split_ind;++i){
		split_array[i] = array[split_ind+i];
	}
	for(int i=0;i<split_ind;++i){
		split_array[n-split_ind+i] = array[i];
	}
	std::cout << "After" << std::endl;
	print_array(split_array, n);

	int val;
	if (generate_random_number(2) == 1)	
		val = generate_random_number(upper_bound);
	else
		val = array[generate_random_number(n)];

	std::cout << "Finding " << val << "..."<<std::endl;
	int pos = splitted_array_search(split_array, 0, n-1, val, n);
	if (pos >=0)
		std::cout << val << " is at index " << pos << std::endl;
	else
		std::cout << "Value not found" << std::endl;

}

int generate_random_number(int upper_bound){
	return rand() % upper_bound;
}

void print_array(int array[], int n){
	for(int i=0;i<n;++i){
		std::cout << array[i] << " ";
	}
	std::cout<<std::endl;
}


int splitted_array_search(int split_array[], int lo, int hi, int val, int n){
	if(hi<lo)
		return -1;

	// Binary search if the values of hi > lo as the range specified is sorted
	if( split_array[lo] < split_array[hi])
		return binary_search(split_array, lo, hi, val);
	//std::cout << lo << " " << hi << std::endl;
	
	int mid = (lo+hi)/2;
	// Get lucky
	if (split_array[mid] == val)
		return mid;
	
	// Check which side the the mid and query val are at
	// false for left, true for right
	// This is exploiting the fact that the right side is smaller than the left
	bool mid_side, val_side;
	mid_side = split_array[mid] < split_array[0];
	val_side = val < split_array[0];

	// Recurse search, but reduce the range accordingly
	if(mid_side == val_side){
		if (split_array[mid]<val)
			return splitted_array_search(split_array, mid+1, hi, val, n);
		else
			return splitted_array_search(split_array, lo, mid-1, val, n);
	}else{
		if(mid_side)
			return splitted_array_search(split_array, lo, mid-1, val, n);
		else
			return splitted_array_search(split_array, mid+1, hi, val, n);
	}	
}

int binary_search(int array[], int lo, int hi, int val){
	// Just a normal binary search
	//std::cout << "Binary Searching..."<< std::endl;
	while(lo <= hi){
		//std::cout << lo << " " << hi << std::endl;
		int mid = (lo+hi)/2;
		if (array[mid] == val)
			return mid;
		if (array[mid]>val)
			hi = mid-1;
		else
			lo = mid+1;
	}
	return -1;
}

#ifndef PERMUTATION_H
#define PERMUTATION_H
#include<cstdlib>

class Permutation
{
    private:
        int max;
        int bound;
        int *array;

    public:
        Permutation(int);
        ~Permutation();
        int next();
};
//default constructor
//used to store max int number from 1 to max to an integer array.
//bound is used to record the number of remining items in the array.
Permutation::Permutation(int n) {
	max = n;
	bound = n;
	array = new int[n];
	for (int i = 0; i < max; i++) {
		array[i] = i+1;
	}
}

Permutation::~Permutation() {
	 
	delete[] array;
}
//next() function randomly select an item in the integer array and return this item
//store the last item to the selected item's original spot.
//decrease remaining items number by one(--bound);
int Permutation::next() {
	if (bound > 1) {
		int index = std::rand() % bound;
		int result = array[index];

		--bound;
		array[index] = array[bound];
		return result;

	}
	else {
		return array[0];
	}
    
}

#endif

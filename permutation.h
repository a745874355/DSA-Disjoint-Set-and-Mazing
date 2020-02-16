#ifndef PERMUTATION_H
#define PERMUTATION_H
#include<cstdlib>

class Permutation
{
private:
	int max;
	int *bound;
	int *array;

public:
	Permutation(int);
	~Permutation();
	int next();
	void reset();
};

Permutation::Permutation(int n) {
	max = n;
	bound = new int(n);
	array = new int[n];
	for (int i = 0; i < max; i++) {
		array[i] = i+1;
	}
	//test
//	std::cout << *bound << array[max-1] << std::endl;
}

Permutation::~Permutation() {
	delete bound;
	delete[] array;
}

int Permutation::next() {
	if (*bound > 1) {
		int index = std::rand() % (*bound);
	//	std::cout << "index: " << index << "\t";
		int result = array[index];

		--*bound;
		array[index] = array[*bound];
	//	std::cout << "result: " << result << "\t";
		return result;

	}
	else {
		return array[0];
	//	std::cout << "test *bound = 1" <<array[0];
	}
		
}

void Permutation::reset() {
	for (int i = 0; i < max; ++i) {
		array[i] = i;
	}

	*bound = max;
}
 
#endif

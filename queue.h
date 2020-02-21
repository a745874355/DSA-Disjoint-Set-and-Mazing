#ifndef QUEUE_H
#define QUEUE_H
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
	for (int i = 0; i < max; ++i) {
		array[i] = i;
	}
}

Permutation::~Permutation() {
	delete bound;
	delete[] array;
}

int Permutation::next() {
	if (*bound == 0) {
		return 0;
	}

	int index = std::rand() % (*bound);
	int result = array[index];

	--*bound;
	array[index] = array[*bound];

	return result;
}

void Permutation::reset() {
	for (int i = 0; i < max; ++i) {
		array[i] = i;
	}

	*bound = max;
}

#endif

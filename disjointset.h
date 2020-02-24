#include <iostream>
// we decide first element in the list is the rep.
class DisjointSet {
public:
	//Create DisjointSet with max
	DisjointSet(int max);
	
	//Create a set with object. 
	//if function returns true if the following condition are satisfied:
	//1. the object current not in the DisjointSet
	//2. the object is between 0(inclusive) - max(exclusive )
	bool makeSet(int object); //O(1) - constant
	
	//the funtion returns the represent of the set that containing object.
	//returns -1 if the object is not in the DisjointSet
	int findSet(int object) const; //O(1) - constant
	
	//the function union two set that rep1 in and rep in into one set.
	//the function returns true in any one of the following situations:
	//1. rep1 and rep2 are already in the same Set
	//2. the set that contains Rep1 and and the set contains Rep2 are unioned successfully.
	bool unionSets(int rep1, int rep2); //O(minimumof(obj2.list.size, obj1.list.size)) - this should be linear.
	
	
	~DisjointSet();//O(nodes.size + lists.size)

	DisjointSet(const DisjointSet& other); //O(max)
	DisjointSet& operator=(const DisjointSet& other); //O(max)
	DisjointSet(DisjointSet&& other); //O(1) - constant
	DisjointSet& operator=(DisjointSet&& other); //O(1) - constant
private:
	struct Node {
		int value = -1;
		Node* next = nullptr;
		Node* first = nullptr;
		Node* last = nullptr;
		size_t referedCount = 0;
		Node() {}
		Node(int v, Node* n, Node* f, Node* l, size_t r) {
			value = v;
			next = n;
			first = f;
			last = l;
			referedCount = r;
		}
	};
	Node** nodes = nullptr;
	int max = 0;
};

#include <iostream>
// we decide first element in the list is the rep.
class DisjointSet {
public:
	DisjointSet(int max); //O(max)
	bool makeSet(int object); //O(1) - constant
	int findSet(int object) const; //O(1) - constant
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
	Node** nodes;
	int max = 0;
};

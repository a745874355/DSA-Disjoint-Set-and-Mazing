#include "disjointset.h"

DisjointSet::DisjointSet(int max)
{
	//this->nodes = new LinkedList<int>::Node * [max]{nullptr}; //initialize to nullptr(0) - warning in matrix
	this->nodes = new Node * [max];
	for (size_t i = 0; i < max; i++)
	{
		nodes[i] = nullptr;
	}
	this->max = max;
	//lists = new LinkedList<LinkedList<int>*>;
}

bool DisjointSet::makeSet(int object) //O(1)
{
	if (object < 0 || object >= max || nodes[object]) return false;
	auto n = new Node();
	n->first = n;
	n->last = n;
	n->next = nullptr;
	n->referedCount = 1;
	n->value = object;
	nodes[object] = n;
	return true;
}

int DisjointSet::findSet(int object) const { //O(1)	
	if (nodes[object]) // if (nodes[object]), the obj already in the list;
	{
		return nodes[object]->first->value;
	}
	return -1;
}

bool DisjointSet::unionSets(int obj1, int obj2)	//O(minimumof(obj2.list.size, obj1.list.size)) - this should be linear.

{
	if (obj1 < 0 || obj1 >= max || obj2 < 0 || obj2 >= max) return false;
	if (obj1 == obj2) return true;
	if (!(nodes[obj1] && nodes[obj2])) return false; //if obj1 or obj2 not in the set
	auto n1 = nodes[obj1]->first;
	auto n2 = nodes[obj2]->first;
	if (n1 == n2) return true;
	if (n1->referedCount < n2->referedCount) //if list of n2 lager, link list of n1 to list of n2
	{
		auto n = n1;
		n1 = n2;
		n2 = n;
	}
	n1->last->next = n2;
	n1->last = n2->last;
	auto n = n2;
	while (n) {
		auto nn = n->next;
		n->first = n1;
		n->referedCount = 0;
		n1->referedCount++;
		n = nn;
	}
	return true;
}

DisjointSet::~DisjointSet()//O(max)
{
	if (this->nodes) {
		for (size_t i = 0; i < max; i++)
		{
			if (nodes[i])
			{
				delete nodes[i];
			}

		}
		delete[] this->nodes;
	}
}

DisjointSet::DisjointSet(const DisjointSet& other) //deep copy, O(max)
{
	*this = DisjointSet(other.max);
	for (size_t i = 0; i < max; i++)
	{
		if (other.nodes[i])
		{
			this->nodes[i] = new Node(
				other.nodes[i]->value,
				other.nodes[i]->next,
				other.nodes[i]->first,
				other.nodes[i]->last,
				other.nodes[i]->referedCount
				);
		}
	}
}

DisjointSet& DisjointSet::operator=(const DisjointSet& other) //deep copy same to copy constructor
{
	for (size_t i = 0; i < max; i++)
	{
		if (nodes[i])
		{
			delete nodes[i];
		}
	}
	this->max = other.max;
	*this = DisjointSet(other);
	return *this;
}

DisjointSet::DisjointSet(DisjointSet&& other) //move O(1)
{
	this->max = other.max;
	this->nodes = other.nodes;
	other.nodes = nullptr;
}

DisjointSet& DisjointSet::operator=(DisjointSet&& other) //move O(1)
{
	this->nodes = other.nodes;
	this->max = other.max;
	other.nodes = nullptr;
	return *this;
}
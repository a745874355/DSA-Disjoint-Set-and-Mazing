#include "disjointset.h"

DisjointSet::DisjointSet(int max)
{
	//this->nodes = new LinkedList<int>::Node * [max]{nullptr}; //initialize to nullptr(0) - warning in matrix
	this->nodes = new LinkedList<int>::Node * [max]; 
	for (size_t i = 0; i < max; i++)
	{
		nodes[i] = nullptr;
	}
	this->max = max;
	lists = new LinkedList<LinkedList<int>*>;
}

bool DisjointSet::makeSet(int object) //O(1)
{
	if (object < 0 || object >= max || nodes[object]) return false;
	auto list = new LinkedList<int>();
	nodes[object] = list->push_back(object);
	lists->push_back(list);
	return true;
}

int DisjointSet::findSet(int object) const{ //O(1)
	//if (lists->isEmpty()) return -1;
	//for (auto& list : *lists) {
	//	for (auto& e : list) {
	//		if (e == object)
	//		{
	//			return *list.begin();
	//		}
	//	}
	//}
	/*
	for (size_t i = 0; i < size; i++)
	{
		if (nodes[i]->data_ == object)
		{
			return *(nodes[i]->list_->begin());
		}
	}
	*/
	
	if (nodes[object]) // if nodes[object - 1] exsits, the obj already in the list;
	{
		//return *(*(nodes[object]->list_)->begin());
		return *((*(nodes[object]->list_)).begin());
	}
	return -1;
}

bool DisjointSet::unionSets(int obj1, int obj2)	//O(minimumof(obj2.list.size, obj1.list.size)) - this should be linear.

{
	if (obj1 < 0 || obj1 >= max || obj2 < 0 || obj2 >= max) return false;
	if (obj1 == obj2) return true;
	if (!(nodes[obj1] && nodes[obj2])) return false;
	auto set1 = findSet(obj1);
	auto set2 = findSet(obj2);
	if (set1 != -1 && set1 == set2) return true;
	LinkedList<int>* list1 = nullptr;
	LinkedList<int>* list2 = nullptr;
	/*for (auto i = lists->begin(); i != lists->end(); i++)
	{
		if (*(*i).begin() == set1)
		{
			if (list2)
			{
				break;
			}
			list1 = i.getNode();
		}
		if (*(*i).begin() == set2)
		{
			list2 = i.getNode();
			if (list1)
			{
				break;
			}
		}
	}*/
	list1 = nodes[obj1]->list_;
	list2 = nodes[obj2]->list_;
	//O(min(obj2.list.size, obj1.list.size)) - this should be linear.
	if (list1->size() > list2->size())
	{
		*list1 += *list2;  
		list2->clearListWithOutFreeMemory(); //the list still on the heap. we free it later.
	}
	else {
		*list2 += *list1;
		list1->clearListWithOutFreeMemory();
	}

	if (!(list1 && list2)) return false;
	return true;
}

DisjointSet::~DisjointSet()//O(nodes.size + lists.size)
{
	if (lists) {
		for (auto& n : *lists) {
			delete n;
		}
		delete lists;
	}
	delete[] nodes;
}

DisjointSet::DisjointSet(const DisjointSet& other) //deep copy, O(nodes.size + lists.size)
{
	*this = DisjointSet(other.max);
	for (auto& list : *(other.lists)) {
		auto nlist = new LinkedList<int>(); //create data list;
		for (auto& d : *list) {
		 	nodes[d] = nlist->push_back(d); //add data
		}
		lists->push_back(nlist); //push linkedlist
	}
}

DisjointSet& DisjointSet::operator=(const DisjointSet& other) //deep copy same to copy constructor
{
	this->max = other.max;
	delete lists;
	*this = DisjointSet(other);
	return *this;
}

DisjointSet::DisjointSet(DisjointSet&& other) //move O(1)
{
	this->max = other.max;
	this->lists = other.lists;
	this->nodes = other.nodes;
	other.lists = nullptr;	
	other.nodes = nullptr;
}

DisjointSet& DisjointSet::operator=(DisjointSet&& other) //move O(1)
{
	this->nodes = other.nodes;
	this->max = other.max;
	this->lists = other.lists;
	other.lists = nullptr;		
	other.nodes = nullptr;
	return *this;
}

void DisjointSet::printSet() const //debugging only
{
	for (auto& list : *lists) {
		std::cout << "{";
		for (auto& e : *list) {
			std::cout << e << " ";
		}
		std::cout << "}" << std::endl;
	}
}

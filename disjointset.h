#include <iostream>

template <typename T>
class LinkedList {
public:
	struct Node {
		LinkedList<T>* list_;
		T data_;
		Node* next_;
		Node* prev_;
		Node(const T& data = T{}, Node* next = nullptr, Node* prev = nullptr, LinkedList<T>* list = nullptr) {
			data_ = data;
			next_ = next;
			prev_ = prev;
			list_ = list;
		}
	};
	LinkedList() {
		front_ = nullptr;
		back_ = nullptr;
	}
	size_t size() const{
		return size_;
	}
	Node* push_front(const T& data);
	~LinkedList();
	Node* push_back(const T& data);
	bool isEmpty() const {
		return !(bool)front_;
	}
	void pop_front();
	void pop_back();
	void clearListWithOutFreeMemory() {
		front_ = nullptr;
		back_ = nullptr;
	}
	LinkedList<T>& operator+=(LinkedList<T>& rhs) {
		auto node = rhs.front_;
		while (node)
		{
			node->list_ = this;
			node = node->next_;
		}
		auto n = front_;
		if (back_) {
			n = back_;
		}
		rhs.front_->prev_ = n;
		n->next_ = rhs.front_;
		auto n2 = rhs.front_;
		if (rhs.back_)
		{
			n2 = rhs.back_;
		}
		this->back_ = rhs.back_;
		this->size_ += rhs.size_;
		rhs.size_ = 0;
		return *this;
	}









	class const_iterator {
	protected:
		friend class LinkedList<T>;
		const LinkedList* list;
		Node* data;
	public:
		const_iterator() {}
		const_iterator(Node* node) {
			this->data = node;
		}
		const_iterator(Node* node, const LinkedList* list) {
			data = node;
			this->list = list;
		}
		const_iterator operator++() {
			if (data)
			{
				this->data = data->next_;
			}
			return *this;
		}

		const_iterator operator++(int) {
			const_iterator it = const_iterator(*this);
			operator++();
			return it;
		}
		const_iterator operator--() {
			if (data)
			{
				this->data = data->prev_;
			}
			else {
				*this = const_iterator(list->back_);
			}
			return *this;
		}
		const_iterator operator--(int) {
			const_iterator it = const_iterator(*this);
			operator--();
			return it;
		}
		bool operator==(const_iterator rhs) {
			return this->data == rhs.data;
		}
		bool operator!=(const_iterator rhs) {
			return !operator==(rhs);
		}
		const T& operator*()const {
			return data->data_;
		}
	};
	class iterator :public const_iterator {
		LinkedList* list = nullptr;
	public:
		iterator() : const_iterator() {}
		iterator(Node* node) :const_iterator(node) {}
		iterator(Node* node, LinkedList* list) {
			this->list = list;
			const_iterator::data = node;
		}
		iterator operator++() {
			const_iterator::operator++();
			return *this;
		}
		iterator operator++(int) {
			iterator it = iterator(*this);
			operator++();
			return it;
		}
		iterator operator--() {
			if (const_iterator::data)
			{
				this->data = const_iterator::data->prev_;
			}
			else {
				*this = iterator(list->back_);
			}
			return *this;
		}
		iterator operator--(int) {
			iterator it = iterator(*this);
			operator--();
			return it;
		}
		Node* getNode() {
			return const_iterator::data;
		}
		T& operator*() {
			return const_iterator::data->data_;
		}
		const T& operator*()const {
			return const_iterator::operator*();
		}

	};
	const_iterator cbegin() const {
		return const_iterator(front_, this);
	}
	iterator begin() {
		return iterator(front_, this);
	}
	const_iterator cend() const {
		return const_iterator(nullptr, this);
	}
	iterator end() {
		return iterator(nullptr, this);
	}
	private:
		Node* front_;
		Node* back_;
		size_t size_;
};



template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::push_front(const T& data) {

	Node* nn = new Node(data, front_, nullptr, this);
	if (front_ != nullptr) {
		front_->prev_ = nn;
	}
	else {
		back_ = nn;
	}
	front_ = nn;
	size_++;
	return nn;
}



template <typename T>
void LinkedList<T>::pop_front() {
	if (front_ != nullptr) {
		Node* rm = front_;
		if (front_->next_ != nullptr, this) {
			front_ = front_->next_;
			front_->prev_ = nullptr;
		}
		else {
			front_ = nullptr;
			back_ = nullptr;
		}
		delete rm;
	}

}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::push_back(const T& data) {
	Node* n = new Node(data, nullptr, back_, this);
	if (back_)
	{
		back_->next_ = n;
	}
	else {
		front_ = n;
	}
	back_ = n;
	size_++;
	return n;
}


template <typename T>
void LinkedList<T>::pop_back() {
	if (back_)
	{
		Node* rm = back_;
		if (back_->prev_)
		{
			back_ = back_->prev_;
			back_->next_ = nullptr;
		}
		else {
			front_ = nullptr;
			back_ = nullptr;
		}
		delete rm;
		rm = nullptr;
	}

}


template <typename T>
LinkedList<T>::~LinkedList() {
	auto node = front_;
	while (node) {
		auto next = node->next_;
		delete node;
		node = next;
	}
	front_ = nullptr;
	back_ = nullptr;
}





// we decide first element in the list is the rep.
class DisjointSet {
public:
	DisjointSet(int max); //O(max)
	bool makeSet(int object); //O(1) - constant
	int findSet(int object) const; //O(1) - constant
	bool unionSets(int rep1, int rep2); //O(minimumof(obj2.list.size, obj1.list.size)) - this should be linear.
	~DisjointSet();//O(nodes.size + lists.size)

	DisjointSet(const DisjointSet& other); //O(nodes.size + lists.size)
	DisjointSet& operator=(const DisjointSet& other); //O(nodes.size + lists.size)
	DisjointSet(DisjointSet&& other); //O(1) - constant
	DisjointSet& operator=(DisjointSet&& other); //O(1) - constant
	void printSet() const;//debugging only
private:
	int max = 0;
	LinkedList<int>::Node** nodes;
	LinkedList<LinkedList<int>*>* lists;
};

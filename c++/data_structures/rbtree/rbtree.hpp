#ifndef RBTREE_HPP
#define RBTREE_HPP

template <typename T>
class RBTree {

private:
	struct Node;
	using pnode = Node*;

public:
	class iterator {
		friend class RBTree;
		pnode node;

	public:
		iterator();
		iterator(const iterator&);
		iterator& operator=(const iterator&);

		const T& operator*();
		bool operator==(const iterator&);
		bool operator!=(const iterator&);
		T* operator->();
		iterator& operator++();
		iterator  operator++(int);
	};

	RBTree() : root(nullptr) {}
	~RBTree() { clear(); }

	bool insert(const T&);
	bool remove(const T&);
	void clear();
	iterator begin();
	iterator end();

private:
	enum Color { RED, BLACK };

	struct Node {
		T* data;
		pnode parent;
		pnode left; pnode right;
		Color color;

		Node()
		    : data(nullptr), parent(nullptr),
		      left(nullptr), right(nullptr),
		      color(BLACK)
		{ }
		Node(const T& d)
		    : data(new T(d)), parent(nullptr),
		      left(nullptr), right(nullptr),
		      color(BLACK)
		{ }

		~Node() { delete data; delete left; delete right; }
	
	};

	pnode root;

	pnode grandparent(pnode);
	pnode uncle(pnode);
	pnode sibling(pnode);
	static pnode minimum(pnode);
	void remove_node(pnode);
	void transplant(pnode, pnode);

	void fix_insertion(pnode);
	void fix_deletion(pnode);

	void rotate_left(pnode);
	void rotate_right(pnode);
};


template <typename T>
bool RBTree<T>::insert(const T& value)
{
	// just simple insertion first
	pnode n = root;
	pnode p = nullptr;

	while (n) {
		p = n;
		if (value == *(n->data))
			return false;
		else if (value < *(n->data))
			n = n->left;
		else
			n = n->right;
	}

	pnode node = new Node(value);
	node->color = RED;

	if (!p) {
		root = node;
	}
	else if (value < *(p->data)) {
		p->left = node;
		node->parent = p;
	}
	else {
		p->right = node;
		node->parent = p;
	}

	fix_insertion(node);

	return true;
}

template <typename T>
bool RBTree<T>::remove(const T& val)
{
	pnode node = root;
	while (node) {
		if (val < *(node->data)) {
			node = node->left;
		}
		else if (val > *(node->data)) {
			node = node->right;
		}
		else {
			remove_node(node);
			return true;
		}
	}
	return false;
}

template <typename T>
void RBTree<T>::clear()
{
	while (root)
		remove_node(root);
}

template <typename T>
void RBTree<T>::remove_node(pnode to_delete)
{
	if (!to_delete)
		return;

	pnode to_move = nullptr,
	      to_fix = nullptr,
	      nil = nullptr; // fake node will be fed to fix_deletion()

	Color orig_color = to_delete->color;
	if (!to_delete->left) {
		to_fix = to_delete->right;
		if (!to_fix) {
			nil = new Node();
			to_fix = nil;
		}
		transplant(to_delete, to_fix);
	}
	else if (!to_delete->right) {
		to_fix = to_delete->left;
		if (!to_fix) {
			nil = new Node();
			to_fix = nil;
		}
		transplant(to_delete, to_fix);
	}
	else {
		to_move = minimum(to_delete->right);
		orig_color = to_move->color;
		to_fix = to_move->right;
		if (!to_fix) {
			nil = new Node();
			to_move->right = nil;
			nil->parent = to_move;
			to_fix = nil;
		}

		if(to_move->parent != to_delete) {
			transplant(to_move, to_fix);
			to_move->right = to_delete->right;
			to_move->right->parent = to_move;
		}

		transplant(to_delete, to_move);
		to_move->left = to_delete->left;
		to_move->left->parent = to_move;
		to_move->color = to_delete->color;
	}

	if (orig_color == BLACK)
		fix_deletion(to_fix);

	// clean up
	to_delete->left = to_delete->right = nullptr;
	delete to_delete;

	if (nil == root)
		root = nullptr;
	else if (nil) {
		if (nil == nil->parent->left)
			nil->parent->left = nullptr;
		else nil->parent->right = nullptr;
	}
	delete nil;
}

template <typename T>
void RBTree<T>::transplant(pnode n1, pnode n2)
{
	if (n1) {
		if (!n1->parent)
			root = n2;
		else if (n1 == n1->parent->left)
			n1->parent->left = n2;
		else
			n1->parent->right = n2;

		if (n2)
			n2->parent = n1->parent;
	}
}

template <typename T>
void RBTree<T>::fix_insertion(pnode to_fix)
{
	while (to_fix->parent && to_fix->parent->color == RED) {
		pnode p = to_fix->parent;
		pnode g = grandparent(to_fix);
		pnode u = uncle(to_fix);

		if(u && u->color == RED) {
			p->color = BLACK;
			u->color = BLACK;
			g->color = RED;
			to_fix = g;
		}
		else {
			if (to_fix == p->right && p == g->left) {
				rotate_left(p);
				to_fix = to_fix->left;
			}
			else if (to_fix == p->left && p == g->right) {
				rotate_right(p);
				to_fix = to_fix->right;
			}

			g = grandparent(to_fix);
			p = to_fix->parent;
			g->color = RED;
			p->color = BLACK;

			if (to_fix == p->left && p == g->left) {
				rotate_right(g);
				to_fix = g;
			}
			else if (to_fix == p->right && p == g->right) {
				rotate_left(g);
				to_fix = g;
			}
		}
	}
	root->color = BLACK;
}

template <typename T>
void RBTree<T>::fix_deletion(pnode to_fix)
{
	while (to_fix != root && to_fix->color == BLACK) {
		pnode s = sibling(to_fix);
		pnode p = to_fix->parent;
		if (s->color == RED) {
			s->color = BLACK;
			p->color = RED;
			if (to_fix == p->left)
				rotate_left(p);
			else
				rotate_right(p);
			s = sibling(to_fix);
		}

		if ((!s->left || s->left->color == BLACK)
			&& (!s->right || s->right->color == BLACK))
		{
			s->color = RED;
			to_fix = p;
		}
		else {
			if (to_fix == p->left
			    && (!s->right || s->right->color == BLACK))
			{
				s->left->color = BLACK;
				s->color = RED;
				rotate_right(s);
				s = sibling(to_fix);
			}
			if (to_fix == p->right
			    && (!s->left || s->left->color == BLACK))
			{
				s->right->color = BLACK;
				s->color = RED;
				rotate_left(s);
				s = sibling(to_fix);
			}
			s->color = p->color;
			p->color = BLACK;
			if (to_fix == p->left) {
				rotate_left(p);
				s->right->color = BLACK;
			}
			else {
				rotate_right(p);
				s->left->color = BLACK;
			}
			to_fix = root;
		}
	}

	to_fix->color = BLACK;
}

template <typename T>
void RBTree<T>::rotate_left(pnode node)
{
	pnode t = node->right;
	node->right = t->left;

	if (t->left)
		t->left->parent = node;
	t->left = node;
	t->parent = node->parent;

	if (!node->parent)
		root = t;
	else if (node == node->parent->left)
		node->parent->left = t;
	else
		node->parent->right = t;

	node->parent = t;
}

template <typename T>
void RBTree<T>::rotate_right(pnode node)
{
	pnode t = node->left;
	node->left = t->right;

	if (t->right)
		t->right->parent = node;
	t->right = node;
	t->parent = node->parent;

	if (!node->parent)
		root = t;
	else if (node == node->parent->left)
		node->parent->left = t;
	else
		node->parent->right = t;

	node->parent = t;
}

template <typename T>
typename RBTree<T>::pnode
RBTree<T>::grandparent(pnode node)
{
	if (node->parent)
		return node->parent->parent;
	return nullptr;
}

template <typename T>
typename RBTree<T>::pnode
RBTree<T>::uncle(pnode node)
{
	pnode g = grandparent(node);
	pnode p = node->parent;
	if (g)
		return sibling(p);

	return nullptr;
}

template <typename T>
typename RBTree<T>::pnode
RBTree<T>::sibling(pnode node)
{
	if (node->parent) {
		if (node == node->parent->left) {
			return node->parent->right;
		}
		return node->parent->left;
	}
	return nullptr;
}

template <typename T>
typename RBTree<T>::pnode
RBTree<T>::minimum(pnode node)
{
	while (node && node->left)
		node = node->left;
	return node;
}


/*
 * iterator implementation
 */
template <typename T>
RBTree<T>::iterator::iterator()
    : node(nullptr)
{ }

template <typename T>
RBTree<T>::iterator::iterator(const iterator& it)
    : node(it.node)
{ }

template <typename T>
typename RBTree<T>::iterator&
RBTree<T>::iterator::operator=(const iterator& it)
{
	node = it.node();
	return *this;
}

template <typename T>
const T& RBTree<T>::iterator::operator*()
{
	return *(node->data);
}

template <typename T>
bool RBTree<T>::iterator::operator==(const iterator& it)
{
	return node == it.node;
}

template <typename T>
bool RBTree<T>::iterator::operator!=(const iterator& it)
{
	return !operator==(it);
}

template <typename T>
T* RBTree<T>::iterator::operator->()
{
	return node->data;
}

template <typename T>
typename RBTree<T>::iterator&
RBTree<T>::iterator::operator++()
{
	if (node) {
		if (node->right) {
			node = minimum(node->right);
		}
		else {
			pnode p = node->parent;
			while (p && node == p->right) {
				node = p;
				p = node->parent;
			}
			node = p;
		}
	}
	return *this;
}

template <typename T>
typename RBTree<T>::iterator
RBTree<T>::iterator::operator++(int)
{
	iterator temp = *this;
	operator++();
	return temp;
}

template <typename T>
typename RBTree<T>::iterator
RBTree<T>::begin()
{
	iterator it;
	it.node = minimum(root);
	return it;
}
template <typename T>
typename RBTree<T>::iterator
RBTree<T>::end()
{
	return iterator();
}

#endif // RBTREE_HPP

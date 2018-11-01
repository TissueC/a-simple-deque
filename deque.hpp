#ifndef SJTU_DEQUE_HPP
#define SJTU_DEQUE_HPP

#include "exceptions.hpp"

#include <cstddef>

namespace sjtu { 

template<class T>
class deque {
private:

	struct node
	{
		T data;
		node *next;
		node *before;
	    //	node(const T &d):data(d),next(NULL),before(NULL){}
		node(const T &d, node* n = NULL, node* b = NULL) :data(d),next(n), before(b) {}
		node() :next(NULL), before(NULL) {}
	};


	
	size_t sz;
public:
	node *head;
	class const_iterator;
	class iterator {
	private:
		/**
		 * TODO add data members
		 *   just add whatever you want.
		 */

		
		//deque<T>* owner;
	public:
		bool is_real_head;
		node *current;
		deque<T>* owner;
		iterator(node *n=NULL,deque<T>* o=NULL,bool real=false)
			:current(n)
			,owner(o)
			,is_real_head(real){}

		~iterator(){}
		/**
		 * return a new iterator which pointer n-next elements
		 *   even if there are not enough elements, the behaviour is **undefined**.
		 * as well as operator-
		 */

		iterator operator+(const int &n) const {
			//TODO
			iterator ans=*this;
			if (n > 0)
			{
				for (int i = 0; i < n; i++)
					ans.current = ans.current->next;
				ans.is_real_head = false;
			}
			else if(n<0)
			{
				for (int i = 0; i < -n; i++)
					ans.current = ans.current->before;
				if (ans.current == ans.owner->head)
					ans.is_real_head = true;
			}
			return ans;
		}
		iterator operator-(const int &n) const {
			//TODO
			return *this + (-n);
		}
		// return th distance between two iterator,
		// if these two iterators points to different vectors, throw invaild_iterator.
		int operator-(const iterator &rhs) const {
			//TODO
			if (owner != rhs.owner) throw invalid_iterator();
			node *tmp1 = current;
			node *tmp2 = current;

			int ans = 0;
			if (rhs==owner->end())
			{
				if (*this ==owner-> begin()) return -int(owner->sz);
				else while (true)
				{
					if (tmp1 == rhs.current) return ans;
					tmp1 = tmp1->next;
					ans--;
				}
			}
			else if (rhs == owner->begin())
			{
				if (*this ==owner-> end()) return owner->sz;
				else while(true)
				{
					if (tmp2 == rhs.current) return ans;
					tmp2 = tmp2->before;
					ans++;
				}
			}
			else {
				bool flag1 = (tmp1 != owner->head->before)
					, flag2 = (tmp2 != owner->head);
				if (tmp1 == owner->head && !is_real_head) flag1 = false;
				if (tmp2 == owner->head && !is_real_head) flag2 = true;
				while (true)
				{
					if (tmp1 == rhs.current) { ans = -ans; break; }
					if (tmp2 == rhs.current)
					{
						if (tmp2 == owner->head&&ans == 0)
						{
							if (is_real_head == rhs.is_real_head)
								break;
						}
						else break;
					}
					if (flag1)tmp1 = tmp1->next;
					if (flag2)tmp2 = tmp2->before;
					ans++;
					flag1 = (tmp1 != owner->head->before);
					flag2 = (tmp2 != owner->head);
				}
			}
			return ans;
		}
		iterator &operator+=(const int &n) {
			//TODO
			if (n > 0)
			{
				for (int i = 0; i < n; i++)
					current = current->next;
				is_real_head =false;
			}
			else if (n < 0)
			{
				for (int i = 0; i < -n; i++)
					current = current->before;
				if (current == owner->head)
					is_real_head = true;
			}
			return *this;
		}
		iterator &operator-=(const int &n) {
			//TODO
			*this += (-n);
			return *this;
		}
		/**
		 * TODO iter++
		 */
		iterator operator++(int) {
			if (*this == owner->end()) throw invalid_iterator();
			iterator ans = *this;
			current = current->next;
			is_real_head = false;
			return ans;
		}
		/**
		 * TODO ++iter
		 */
		iterator& operator++() {
			if (*this == owner->end()) throw invalid_iterator();
			current = current->next;
			is_real_head = false;
			return *this;
		}
		/**
		 * TODO iter--
		 */
		iterator operator--(int) {
			if (*this == owner->begin()) throw invalid_iterator();
			iterator ans = *this;
			current = current->before;
			if (current == owner->head)
				is_real_head = true;
			return ans;
		}
		/**
		 * TODO --iter
		 */
		iterator& operator--() {
			if (*this == owner->begin()) throw invalid_iterator();
			current = current->before;
			if (current == owner->head)
				is_real_head = true;
			return *this;
		}
		/**
		 * TODO *it
		 */
		T& operator*() const {
			if (*this == owner->end())
				throw invalid_iterator();
			return current->data;

		}
		/**
		 * TODO it->field
		 */
		T* operator->() const noexcept {
			return &current->data;
		}
		/**
		 * a operator to check whether two iterators are same (pointing to the same memory).
		 */
		bool operator==(const iterator &rhs) const 
		{
			return current == rhs.current&&is_real_head==rhs.is_real_head;
		}
		bool operator==(const const_iterator &rhs) const 
		{
			return current == rhs.current&&is_real_head == rhs.is_real_head;
		}
		/**
		 * some other operator for iterator.
		 */
		bool operator!=(const iterator &rhs) const 
		{
			return current != rhs.current|| is_real_head != rhs.is_real_head;
		}
		bool operator!=(const const_iterator &rhs) const 
		{
			return current != rhs.current || is_real_head != rhs.is_real_head;
		}
	};
	class const_iterator {
		// it should has similar member method as iterator.
		//  and it should be able to construct from an iterator.
		private:
			// data members.
			bool is_real_head;
			node* current;
			const deque<T>* owner;
		public:
			const_iterator(node *n=NULL,const deque<T>* o=NULL,bool real=false)
				:current(n)
				,owner(o)
				,is_real_head(real){
				// TODO
			}
			const_iterator(const const_iterator &other) {
				// TODO
				current = other.current;
				owner = other.owner;
				is_real_head = other.is_real_head;
			}
			const_iterator(const iterator &other) {
				// TODO
				current = other.current;
				owner = other.owner;
				is_real_head = other.is_real_head;
			}

			const_iterator operator+(const int &n) const {
				//TODO
				const_iterator ans = *this;
				if (n > 0)
				{
					for (int i = 0; i < n; i++)
						ans.current = ans.current->next;
					ans.is_real_head = false;
				}
				else if (n<0)
				{
					for (int i = 0; i < -n; i++)
						ans.current = ans.current->before;
					if (ans.current == ans.owner->head)
						ans.is_real_head = true;
				}
				return ans;
			}
			const_iterator operator-(const int &n) const {
				//TODO
				return *this + (-n);
			}

			const_iterator &operator+=(const int &n) {
				//TODO
				if (n > 0)
				{
					for (int i = 0; i < n; i++)
						current = current->next;
					is_real_head = false;
				}
				else if (n < 0)
				{
					for (int i = 0; i < -n; i++)
						current = current->before;
					if (current == owner->head)
						is_real_head = true;
				}
				return *this;
			}
			const_iterator &operator-=(const int &n) {
				//TODO
				*this += (-n);
				return *this;
			}

			int operator-(const const_iterator &rhs) const {
				//TODO
				if (owner != rhs.owner) throw invalid_iterator();
				node *tmp1 = current;
				node *tmp2 = current;

				int ans = 0;
				if (rhs == owner->cend())
				{
					if (*this == owner->cbegin()) return -int(owner->sz);
					else while (true)
					{
						if (tmp1 == rhs.current) return ans;
						tmp1 = tmp1->next;
						ans--;
					}
				}
				else if (rhs == owner->cbegin())
				{
					if (*this == owner->cend()) return owner->sz;
					else while (true)
					{
						if (tmp2 == rhs.current) return ans;
						tmp2 = tmp2->before;
						ans++;
					}
				}
				else {
					bool flag1 = (tmp1 != owner->head->before)
						, flag2 = (tmp2 != owner->head);
					if (tmp1 == owner->head && !is_real_head) flag1 = false;
					if (tmp2 == owner->head && !is_real_head) flag2 = true;
					while (true)
					{
						if (tmp1 == rhs.current) { ans = -ans; break; }
						if (tmp2 == rhs.current)
						{
							if (tmp2 == owner->head&&ans == 0)
							{
								if (is_real_head == rhs.is_real_head)
									break;
							}
							else break;
						}
						if (flag1)tmp1 = tmp1->next;
						if (flag2)tmp2 = tmp2->before;
						ans++;
						flag1 = (tmp1 != owner->head->before);
						flag2 = (tmp2 != owner->head);
					}
				}
				return ans;
			}

			const_iterator operator++(int) {
				/*if (this->current == owner->head && !is_real_head)
					throw invalid_iterator();*/
				const_iterator ans = *this;
				current = current->next;
				is_real_head = false;
				return ans;
			}
			/**
			* TODO ++iter
			*/
			const_iterator& operator++() {
				/*if (this->current == owner->head&&!is_real_head)
					throw invalid_iterator();*/
				current = current->next;
				is_real_head = false;
				return *this;
			}
			/**
			* TODO iter--
			*/
			const_iterator operator--(int) {
				/*if (this->current == owner->head&&is_real_head)
					throw invalid_iterator();*/
				const_iterator ans = *this;
				current = current->before;
				if (current == owner->head)
					is_real_head = true;
				return ans;
			}
			/**
			* TODO --iter
			*/
			const_iterator& operator--() {
				/*if (this->current== owner->head&&is_real_head)
					throw invalid_iterator();*/
				current = current->before;
				if (current == owner->head)
					is_real_head = true;
				return *this;
			}

			const T& operator*() const {
				if (this->current == owner->head&&!is_real_head)
				{
					throw invalid_iterator();
				}
				return current->data;
			}

			T* operator->() const noexcept {
				return &current->data;
			}
			/**
			* a operator to check whether two iterators are same (pointing to the same memory).
			*/
			bool operator==(const iterator &rhs) const
			{
				return current == rhs.current&&is_real_head == rhs.is_real_head;
			}
			bool operator==(const const_iterator &rhs) const
			{
				return current == rhs.current&&is_real_head==rhs.is_real_head;
			}
			/**
			* some other operator for iterator.
			*/
			bool operator!=(const iterator &rhs) const
			{
				return current != rhs.current || is_real_head != rhs.is_real_head;
			}
			bool operator!=(const const_iterator &rhs) const
			{
				return current != rhs.current || is_real_head != rhs.is_real_head;
			}
			// And other methods in iterator.
			// And other methods in iterator.
			// And other methods in iterator.
	};
	/**
	 * TODO Constructors
	 */
	deque() :sz(0), head(NULL){}

	deque(const T &d) :sz(1)
	{
		node *n = new node(d);
		head n;
		head->next = n;
		head->before = n;
	}
	deque(const deque &other) 
	{
		head=NULL;
		if (other.sz == 0)
		{
			sz = 0;
			return;
		}
		node *tmp = other.head;
		node *p=head = new node(other.head->data);
		tmp = tmp->next;
		while (tmp != other.head)
		{
			node *q = new node(tmp->data);
			q->before = p;
			p->next = q;
			p = q;
			tmp = tmp->next;
		}
		p->next = head;
		head->before = p;
		sz = other.sz;
	}
	/**
	 * TODO Deconstructor
	 */
	~deque() 
	{
		if (sz == 0) return;
		node *tmp = head->next;
		node *del=NULL;
		while (tmp!=head)
		{
			del = tmp;
			tmp = tmp->next;
			if(del) delete del;
			del = NULL;
			sz--;
		}
		delete tmp;
		sz = 0;
	}
	/**
	 * TODO assignment operator
	 */
	deque &operator=(const deque &other) 
	{
		if (other.head ==head) return *this;
		this->clear();
		if (other.sz == 0) return *this;
		node *tmp = other.head;
		node *p = head= new node(tmp->data);
		tmp = tmp->next;
		while (tmp!=other.head)
		{
			node *q = new node(tmp->data);
			q->before = p;
			p->next = q;
			p = q;
			tmp = tmp->next;
		}
		p->next =head;
		head->before =p;
		sz = other.sz;
		return *this;
		
	}
	/**
	 * access specified element with bounds checking
	 * throw index_out_of_bound if out of bound.
	 */
	T & at(const size_t &pos) 
	{
		if (pos >= sz || pos<0) throw index_out_of_bound();
		node* tmp=head;
		if (pos < sz / 2)
			for (int i = 0; i < pos; i++)
				tmp = tmp->next;
		else
			for (int i = 0; i < sz-pos; i++)
				tmp = tmp->before;
		return tmp->data;
	}

	const T & at(const size_t &pos) const 
	{
		if (pos >= sz || pos<0) throw index_out_of_bound();
		node* tmp = head;
		if (pos < sz / 2)
			for (int i = 0; i < pos; i++)
				tmp = tmp->next;
		else
			for (int i = 0; i < sz - pos; i++)
				tmp = tmp->before;
		return tmp->data;
	}
	T & operator[](const size_t &pos) 
	{
		if (pos >= sz || pos<0) throw index_out_of_bound();
		node* tmp = head;
		if (pos < sz / 2)
			for (int i = 0; i < pos; i++)
				tmp = tmp->next;
		else
			for (int i = 0; i < sz - pos; i++)
				tmp = tmp->before;
		return tmp->data;
	}
	const T & operator[](const size_t &pos) const 
	{
		if (pos >= sz||pos<0) throw index_out_of_bound();
		node* tmp = head;
		if (pos < sz / 2)
			for (int i = 0; i < pos; i++)
				tmp = tmp->next;
		else
			for (int i = 0; i < sz - pos; i++)
				tmp = tmp->before;
		return tmp->data;
	}
	/**
	 * access the first element
	 * throw container_is_empty when the container is empty.
	 */
	const T & front() const 
	{
		if (empty()) throw container_is_empty();
		return head->data;
	}
	/**
	 * access the last element
	 * throw container_is_empty when the container is empty.
	 */
	const T & back() const 
	{
		if (empty()) throw container_is_empty();
		return head->before->data;
	}
	/**
	 * returns an iterator to the beginning.
	 */
	iterator begin() 
	{
		iterator iter(head, this);
		if (iter.owner->sz != 0) iter.is_real_head = true;
		return iter;
	}
	const_iterator cbegin() const 
	{

		if (sz == 0)
		{
			const_iterator iter(head, this,false); return iter;
		}
		else
		{
			const_iterator iter(head, this, true);return iter;
		}
		
	}
	/**
	 * returns an iterator to the end.
	 */
	iterator end() 
	{
		iterator iter(head, this,false);
		return iter;
	}
	const_iterator cend() const 
	{
		const_iterator iter(head, this,false);
		return iter;
	}
	/**
	 * checks whether the container is empty.
	 */
	bool empty() const 
	{
		return head == NULL;
	}
	/**
	 * returns the number of elements
	 */
	size_t size() const 
	{
		return sz;
	}
	/**
	 * clears the contents
	 */
	void clear() 
	{
		if (empty()) return;
		node* tmp = head->next;
		node *del=NULL;
		while (tmp!=head)
		{
			del = tmp;
			tmp = tmp->next;
			if(del) delete del;
			del = NULL;
		}
		delete head;
		head = NULL;
		sz = 0;
	}
	/**
	 * inserts elements at the specified locat on in the container.
	 * inserts value before pos
	 * returns an iterator pointing to the inserted value
	 *     throw if the iterator is invalid or it point to a wrong place.
	 */
	iterator insert(iterator pos, const T &value) 
	{
		if (pos.owner != this) throw invalid_iterator();
		if (sz == 0)
		{
			head= new node(value);
			head->next = head;
			head->before = head;
			iterator ans(head, this,true);
			sz++;
			return ans;
		}
		node *n = new node(value);
		
		pos.current->before->next = n;
		n->before = pos.current->before;
		n->next = pos.current;
		pos.current->before = n;

		iterator ans(n,this,false);
		if (pos.current == head&&pos.is_real_head)
		{
			head = n;
			pos.is_real_head = false;
			ans.is_real_head = true;
		}

		sz++;
		return ans;
	}
	/**
	 * removes specified element at pos.
	 * removes the element at pos.
	 * returns an iterator pointing to the following element, if pos pointing to the last element, end() will be returned.
	 * throw if the container is empty, the iterator is invalid or it points to a wrong place.
	 */
	iterator erase(iterator pos) 
	{
		if (empty()) throw container_is_empty();
		if (pos.owner != this) throw invalid_iterator();
		if (pos ==end()) throw invalid_iterator();
		node *del = pos.current;
		if (sz == 1)
		{
			delete del;
			head = NULL;
			sz = 0;
			return end();
		}
		iterator ans(pos.current->next, this);
		if (pos.owner->head == del)
		{
			pos.owner->head = del->next;
			ans.is_real_head = true;
		}
		
		del->before->next = del->next;
		del->next->before = del->before;
		if (del) delete del;
		del = NULL;
		sz--;
		//if (ans.current ==ans.owner->head) ans.is_real_head = false;
		return ans;
	}
	/**
	 * adds an element to the end
	 */
	void push_back(const T &value) 
	{
		if (empty())
		{
			head = new node(value);
			head->before = head;
			head->next = head;
			sz++;
			return;
		}

		node *n = new node(value);
		head->before->next = n;
		n->before = head->before;
		head->before = n;
		n->next = head;
		sz++;
	}
	/**
	 * removes the last element
	 *     throw when the container is empty.
	 */
	void pop_back() 
	{
		if (empty()) throw container_is_empty();
		if (sz == 1)
		{
			if(head) delete head;
			head = NULL;
			sz--;
			return;
		}
		node *del = head->before;
		//fuck the BUG
		//head->before = head->before->before;
		//head->before->before->next = head;

		head->before = head->before->before;
		head->before->next = head;

		if(del) delete del;
		del = NULL;
		sz--;
	}
	/**
	 * inserts an element to the beginning.
	 */
	void push_front(const T &value) 
	{
		if (empty())
		{
			head = new node(value);
			head->before = head;
			head->next = head;
			sz++;
			return;
		}

		node* n = new node(value);

		n->before = head->before;
		head->before->next = n;
		head->before = n;
		n->next = head;

		head = n;
		sz++;
	}
	/**
	 * removes the first element.
	 *     throw when the container is empty.
	 */
	void pop_front() 
	{
		if (empty())  throw container_is_empty();
		else if (sz == 1)
		{
			if(head) delete head;
			head=NULL;
			sz--;
			return;
		}
		node *tmp = head->next;
		head->next->before = head->before;
		head->before->next = head->next;
		if(head) delete head;
		head = tmp;
		sz--;
	}
};

}

#endif
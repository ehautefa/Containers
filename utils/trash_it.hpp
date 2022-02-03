	// /*******************	METHOD	*******************/		 
	// // template <class Container>
	// // 	back_insert_iterator<Container> back_inserter (Container& x);
	// // template<class InputIterator>
	// // 	typename iterator_traits<InputIterator>::difference_type distance (InputIterator first, InputIterator last);
	// // template <class Container>
	// // 	front_insert_iterator<Container> front_inserter (Container& x);
	// // template <class Container, class Iterator>
	// // 	insert_iterator<Container> inserter (Container& x, Iterator it);

	

	// template <class T>
	// struct iterator<input_iterator_tag, T> : public iterator_traits {

	// 	iterator( const iterator & src ) : _ptr(src._ptr) {}
	// 	iterator	&operator=(const iterator & rhs) {this->_ptr = this._ptr;return (*this);}
	// 	~iterator( void ) {}

	// 	bool 	operator==(const iterator & rhs) const { return (_ptr == rhs._ptr);}
	// 	bool 	operator!=(const iterator & rhs) const {return (_ptr != rhs._ptr);}

	// 	value_type	&operator*() {return (*_ptr);}
	// 	value_type	&operator->() {return (*_ptr);}

	// 	iterator	&operator++() {++_ptr;return *this;}
	// 	iterator	operator++( value_type ) { iterator tmp(*this); operator++(); return tmp;}

	// 	private:
	// 		pointer	_ptr;
	// };

	// template <class T>
	// struct iterator<forward_iterator_tag, T> : public iterator_traits {

	// 	iterator(pointer ptr) : _ptr(ptr) {}
	// 	iterator( const iterator & src ) : _ptr(src._ptr) {}
	// 	iterator	&operator=(const iterator & rhs) {this->_ptr = this._ptr;return (*this);}
	// 	~iterator( void ) {}

	// 	bool 	operator==(const iterator & rhs) const { return (_ptr == rhs._ptr);}
	// 	bool 	operator!=(const iterator & rhs) const {return (_ptr != rhs._ptr);}

	// 	value_type	&operator*() {return (*_ptr);}
	// 	value_type	&operator->() {return (*_ptr);}

	// 	value_type	operator=( value_type  t ) {*_ptr = t; return (*_ptr);}

	// 	iterator	&operator++() {++_ptr;return *this;}
	// 	iterator	operator++( value_type ) { iterator tmp(*this); operator++(); return tmp;}
		
	// 	private:
	// 		pointer	_ptr;
	// };

	// template <class T>
	// struct iterator<bidirectional_iterator_tag, T> : public iterator_traits {

	// 	iterator(pointer ptr) : _ptr(ptr) {}
	// 	iterator( const iterator & src ) : _ptr(src._ptr) {}
	// 	iterator	&operator=(const iterator & rhs) {this->_ptr = this._ptr;return (*this);}
	// 	~iterator( void ) {}

	// 	bool 	operator==(const iterator & rhs) const { return (_ptr == rhs._ptr);}
	// 	bool 	operator!=(const iterator & rhs) const {return (_ptr != rhs._ptr);}

	// 	value_type	&operator*() {return (*_ptr);}
	// 	value_type	&operator->() {return (*_ptr);}

	// 	value_type	operator=( value_type  t ) {*_ptr = t; return (*_ptr);}

	// 	iterator	&operator++() {++_ptr;return *this;}
	// 	iterator	operator++( value_type ) { iterator tmp(*this); operator++(); return tmp;}

	// 	iterator	&operator--() { --_ptr; return *this;}
	// 	iterator	operator--( value_type ) { iterator tmp(*this); operator--(); return tmp;	
	// 	private:
	// 		pointer	_ptr;
	// };
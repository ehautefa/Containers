                                              ▄▄                                    
  ▄▄█▀▀▀█▄█                     ██            ██                                    
▄██▀     ▀█                     ██                                                  
██▀       ▀ ▄██▀██▄▀████████▄ ██████ ▄█▀██▄ ▀███ ▀████████▄   ▄▄█▀██▀███▄███ ▄██▀███
██         ██▀   ▀██ ██    ██   ██  ██   ██   ██   ██    ██  ▄█▀   ██ ██▀ ▀▀ ██   ▀▀
██▄        ██     ██ ██    ██   ██   ▄█████   ██   ██    ██  ██▀▀▀▀▀▀ ██     ▀█████▄
▀██▄     ▄▀██▄   ▄██ ██    ██   ██  ██   ██   ██   ██    ██  ██▄    ▄ ██     █▄   ██
  ▀▀█████▀  ▀█████▀▄████  ████▄ ▀████████▀██▄████▄████  ████▄ ▀█████▀████▄   ██████▀
                                                                                    
#############		VECTOR			#############

The C++ Standard Library vector class is a class template for sequence containers. A vector stores elements of a given type in a linear arrangement, and allows fast random access to any element. A vector is the preferred container for a sequence when random-access performance is at a premium.

#############		ITERATOR		#############

Iterators are a generalization of pointers, abstracting from their requirements in a way that allows a C++ program to work with different data structures in a uniform manner. Iterators act as intermediaries between containers and generic algorithms. Instead of operating on specific data types, algorithms are defined to operate on a range specified by a type of iterator. Any data structure that satisfies the requirements of the iterator may then be operated on by the algorithm. There are five types or categories of iterator, each with its own set of requirements and resulting functionality:

Output: forward moving, may store but not retrieve values, provided by ostream and inserter.

Input: forward moving, may retrieve but not store values, provided by istream.

Forward: forward moving, may store and retrieve values.

Bidirectional: forward and backward moving, may store and retrieve values, provided by list, set, multiset, map, and multimap.

Random access: elements accessed in any order, may store and retrieve values, provided by vector, deque, string, and array.

#############		TO DO			#############


ITERATOR						❌
	member fcts			❌
	Non-member fcts		❌
	Overloads			❌
	iterators_traits	❌
	reverse_iterator	❌
VECTOR							❌
	member fcts			❌
	Non-member fcts		❌
	Overloads			❌			
MAP								❌
	member fcts			❌
	Non-member fcts		❌
	Overloads			❌
STACK							❌
	member fcts			❌
	Non-member fcts		❌
	Overloads			❌
enable_if						✅
is_integral						✅
equal/lexicographical compare	✅
std::pair						✅
std::make_pair					✅

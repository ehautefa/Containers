**The purpose of this project is to re-implement stack, vector and map from the C++98 Standard Template Library.**

## Vector

The C++ Standard Library vector class is a class template for sequence containers. A vector stores elements of a given type in a linear arrangement, and allows fast random access to any element. A vector is the preferred container for a sequence when random-access performance is at a premium.
My vectors occupy more space than static arrays, because more memory is allocated to handle future growth. This way my vector does not need to reallocate each time an element is inserted, but only when the additional memory is exhausted.

## Stack

A stack is basically a vector without any iterator with a LIFO data structure. The stack pushes and pops the element from the back of the underlying container, known as the top of the stack.
As default underlying containers, it use my vector class, but it is compatible with other containers, the STL ones included.

## Map

Map is a sorted associative container that contains key-value pairs with unique keys.
As self-balancing binary search tree, I choose to implement an AVL tree.
In an AVL tree, the heights of the two child subtrees of any node differ by at most one; if at any time they differ by more than one, rebalancing is done to restore this property.
It's Time complexity is in average and worst case for search, insert and delete : _O(log n)_

![AVL_Tree_Example](https://user-images.githubusercontent.com/78262213/210216046-99947c72-c888-4cc9-8b6d-0802d61374ff.gif)

_By Bruno Schalch - Own work, CC BY-SA 4.0, https://commons.wikimedia.org/w/index.php?curid=64250599_

## Iterator

Iterators are a generalization of pointers, abstracting from their requirements in a way that allows a C++ program to work with different data structures in a uniform manner. Iterators act as intermediaries between containers and generic algorithms. Instead of operating on specific data types, algorithms are defined to operate on a range specified by a type of iterator. Any data structure that satisfies the requirements of the iterator may then be operated on by the algorithm. There are five types or categories of iterator, each with its own set of requirements and resulting functionality:

Output: forward moving, may store but not retrieve values, provided by ostream and inserter.

Input: forward moving, may retrieve but not store values, provided by istream.

Forward: forward moving, may store and retrieve values.

Bidirectional: forward and backward moving, may store and retrieve values, provided by list, set, multiset, map, and multimap.

Random access: elements accessed in any order, may store and retrieve values, provided by vector, deque, string, and array.

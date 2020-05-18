#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <chrono>
#include <iostream>
#include <cmath>
#include <chrono>
#include <string>
#include <string.h>
#include <iterator>
#include <cstddef>
#include <cstring>
#include <utility>
#include <stdexcept>


template <typename T>
class Vector{

private:
	int veksize, maxsize, maximum = 100000000; //100 mil
	T* array;

	inline void alloc_new() {   // inline void - a hint to the compiler that the function's code should be generated inline at the place it is called, 
		maxsize = veksize * 2;			//rather than generated as a separate function to be branched to
		T* tarr = new T[maxsize];
		memcpy(tarr, array, veksize * sizeof(T));
		delete[] array;
		array = tarr;
	}

public:

	//Member Types

	typedef T value_type;
	typedef const T const_value_type;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef value_type& ref;	 //reference
	typedef value_type* ptr;	//pointer
	typedef T* iterator;
	typedef const T* const_iterator;
	typedef const_value_type* const_pointer;
	typedef const_value_type& const_reference;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	//Iteratoriai


	const_iterator cbegin() const {	return array;}

	const_iterator cend() const {return array + veksize;}

	reverse_iterator rbegin() { return reverse_iterator(array + veksize);}

	const_reverse_iterator crbegin() const {return reverse_iterator(array + veksize);}

	reverse_iterator rend() {return reverse_iterator(array);}

	const_reverse_iterator crend() const { return reverse_iterator(array); }

	ptr begin() { return (&array[0]); };

	ptr end() { return &array[veksize - 1]; };  //nes size yra vienu daugiau nei yra elementu? 

	//Element access

	value_type* data() noexcept {return array;}

	const_value_type* data() const noexcept { return array; }


	ref front() {return (array[0]);};

	ref back() {return (array[veksize - 1]);};

	value_type operator[](int i) {

		if (i < veksize)
			return array[i];
		throw std::out_of_range("out of range");
	};


	value_type at(int i) {

		if (i < veksize)
			return array[i];
		throw std::out_of_range("out of range");
	};


	//tiesiog konstruktorius 
	Vector(){
		maxsize = 10;
		array = new value_type[maxsize];
		veksize = 0;
	};


	Vector(value_type i){
		maxsize = i;
		array = new value_type[maxsize];
		veksize = 0;
	};

	Vector(const Vector& v){

		maxsize = v.maxsize;
		veksize = v.veksize;
		array = new value_type[maxsize];
		for (size_t i = 0; i < v.veksize; i++){

			array[i] = v.array[i];
		}
	};



	//destruktorius
	~Vector() {

		delete[] array;
	};



	int size() { return veksize; };
	int max_size() { return maximum; };
	int capacity() { return maxsize; }; 


	void push_back(value_type i){

		if (veksize + 1 > maxsize)
			alloc_new();
		array[veksize] = i;
		veksize++;
	};

	bool empty(){

		if (veksize == 0)
			return true;
		else
			return false;
	};

	void assign(int a, value_type b) {

		for (size_t i = 1; i <= a; i++)
		{
			if (veksize + 1 > maxsize)
				alloc_new();
			array[veksize] = b;
			veksize++;
		}
	};

	void shrink_to_fit(){

		maxsize = veksize;
		value_type* temp = new value_type[maxsize];
		for (int i = 0; i < veksize; i++)
			temp[i] = array[i];
		delete[] array;
		array = temp;
	};

	void clear(){

		veksize = 0;
		delete[] array;
		array = new value_type(maxsize);
	};

	void pop_back()
	{
		veksize = veksize - 1;
		value_type* tmp = new value_type[maxsize];
		for (int i = 0; i < veksize; i++)
			tmp[i] = array[i];
		delete[] array;
		array = tmp;
	};

	void erase(ptr it){

		ptr iit = &array[it - array];
		(*iit).~T();
		memmove(iit, iit + 1, (veksize - (it - array) - 1) * sizeof(T));
		--veksize;
	}

	void erase(ptr first, ptr last){

		value_type* temp = first;
		ptr f = &array[first - array];
		for (; first != last; ++first)
			(*first).~T();
		memmove(f, last, (veksize - (last - array)) * sizeof(T));
		veksize -= last - temp;
	}

	ptr insert(ptr it, const T& val){

		ptr iit = &array[it - array];
		if (veksize == max_size)
		{
			max_size <<= 2;
			alloc_new();
		}
		memmove(iit + 1, iit, (veksize - (it - array)) * sizeof(T));
		(*iit) = val;
		++veksize;
		return iit;
	}

	ptr insert(ptr it, T&& val){

		ptr iit = &array[it - array];
		if (veksize == maxsize)
		{
			maxsize <<= 2;
			alloc_new();
		}
		memmove(iit + 1, iit, (veksize - (it - array)) * sizeof(T));
		(*iit) = std::move(val);
		++veksize;
		return iit;
	}


	void reserve(int sz) {
		if (sz > maxsize) {
			maxsize = sz;
			alloc_new();
		}
	}


	void resize(int sz){

		if (sz > veksize)
		{
			if (sz > maxsize)
			{
				maxsize = sz;
				alloc_new();
			}
		}
		else
		{
			size_type i;
			for (i = veksize; i < sz; ++i)
				array[i].~T();
		}
		veksize = sz;
	}

	void resize(int sz, const T& c){

		if (sz > veksize)
		{
			if (sz > maxsize)
			{
				maxsize = sz;
				alloc_new();
			}
			size_type i;
			for (i = veksize; i < sz; ++i)
				array[i] = c;
		}
		else
		{
			size_type i;
			for (i = veksize; i < sz; ++i)
				array[i].~T();
		}
		veksize = sz;
	}

	void swap(Vector<T>& other){

		size_t tvsize = veksize,
			tmaxsize = maxsize;
		T* tarray = array;

		veksize = other.veksize;
		maxsize = other.maxsize;
		array = other.array;

		other.veksize = tvsize;
		other.maxsize = tmaxsize;
		other.array = tarray;
	}



	// Operatoriai
	bool operator==(const Vector<value_type>& vec) const
	{
		if (veksize != vec.veksize)
			return false;
		size_type i;
		for (i = 0; i < veksize; ++i)
			if (array[i] != vec.array[i])
				return false;
		return true;
	}

	bool operator!=(const Vector<value_type>& vec) const
	{
		if (veksize != vec.veksize)
			return true;
		size_type i;
		for (i = 0; i < veksize; ++i)
			if (array[i] != vec.array[i])
				return true;
		return false;
	}

	bool operator<(const Vector<value_type>& vec) const
	{
		size_type i, j, ub = veksize < vec.veksize ? veksize : vec.veksize;
		for (i = 0; i < ub; ++i)
			if (array[i] != vec.array[i])
				return array[i] < vec.array[i];
		return veksize < vec.veksize;
	}

	bool operator<=(const Vector<value_type>& vec) const
	{
		size_type i, j, ub = veksize < vec.veksize ? veksize : vec.veksize;
		for (i = 0; i < ub; ++i)
			if (array[i] != vec.array[i])
				return array[i] < vec.array[i];
		return veksize <= vec.veksize;
	}

	bool operator>(const Vector<value_type>& vec) const
	{
		size_type i, j, ub = veksize < vec.veksize ? veksize : vec.veksize;
		for (i = 0; i < ub; ++i)
			if (array[i] != vec.array[i])
				return array[i] > vec.array[i];
		return veksize > vec.veksize;
	}

	Vector& operator=(const Vector& v) {

		if (this != &v) {
			maxsize = v.maxsize;
			veksize = v.veksize;
			delete[] array;
			array = new value_type[maxsize];

			for (size_t i = 0; i < v.veksize; i++) {
				array[i] = v.array[i];
			}
		}
		return *this;
	}

	Vector& operator+=(value_type i) {

		this->push_back(i);
		return *this;
	}

	bool operator>=(const Vector<value_type>& vec) const
	{
		size_type i, j, ub = veksize < vec.veksize ? veksize : vec.veksize;
		for (i = 0; i < ub; ++i)
			if (array[i] != vec.array[i])
				return array[i] > vec.array[i];
		return veksize >= vec.veksize;
	}

};
#endif
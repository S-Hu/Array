/*
* C++ Programming, Assignment 2
* Array
* by S.Hu
*/
#pragma once
#ifndef ARRAY_H
#define ARRAY_H
#include<stdexcept>
#pragma warning(disable: 4290)//C++ exception specification ignored except to indicate a function is not __declspec(nothrow)

template<typename T>
class Array {
public:
	/* types */
	typedef T value_type;
	typedef unsigned int size_type;
	typedef int difference_type;
	typedef value_type &reference;
	typedef const value_type &const_reference;
	typedef value_type *pointer;
	typedef const value_type *const_pointer;

	/* Iterators */
	//const_iterator (base)
	class const_iterator {
	public:
		typedef std::random_access_iterator_tag iterator_category;
		typedef typename Array::value_type value_type;
		typedef typename Array::difference_type difference_type;
		typedef typename Array::const_pointer pointer;
		typedef typename Array::const_reference reference;

		const_iterator();
		const_iterator(value_type *ptr);

		reference operator*() const;
		pointer operator->() const;
		reference operator[](difference_type off) const;
		const_iterator operator+(difference_type dif) const;
		friend const_iterator operator+(difference_type dif, const_iterator myIter);
		const_iterator operator-(difference_type dif) const;
		difference_type operator-(const_iterator rightVal) const;
		const_iterator &operator++();
		const_iterator operator++(int);
		const_iterator &operator--();
		const_iterator operator--(int);
		const_iterator &operator+=(difference_type dif);
		const_iterator &operator-=(difference_type dif);
		bool operator==(const_iterator rightVal) const;
		bool operator!=(const_iterator rightVal) const;
		bool operator<(const_iterator rightVal) const;
		bool operator<=(const_iterator rightVal) const;
		bool operator>(const_iterator rightVal) const;
		bool operator>=(const_iterator rightVal) const;
	protected:
		value_type *Ptr;
		friend Array;
	};

	//iterator(继承自const_iterator)
	class iterator : public const_iterator {
	public:
		typedef typename Array::pointer pointer;
		typedef typename Array::reference reference;
		typedef typename Array::const_iterator iterBase;

		iterator();
		iterator(value_type *ptr);

		reference operator*() const;
		pointer operator->() const;
		reference operator[](difference_type off) const;
		iterator operator+(difference_type dif) const;
		friend iterator operator+(difference_type dif, iterator myIter);
		iterator operator-(difference_type dif) const;
		difference_type operator-(const_iterator rightVal) const;
		iterator &operator++();
		iterator operator++(int);
		iterator &operator--();
		iterator operator--(int);
		iterator &operator+=(difference_type dif);
		iterator &operator-=(difference_type dif);

		friend Array;
	};

	//常量反向迭代器
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
	//反向迭代器
	typedef std::reverse_iterator<iterator> reverse_iterator;

	/*
	--------------functions--------------
	*/

	/* constructors, destructor, assignment operators */
	explicit Array(size_type size = 0, const value_type &initVal = value_type());//从指定大小和初值构造
	Array(const Array &it);//复制构造
	Array(Array &&it);//转移构造
	Array(const_iterator first, const_iterator last);//从给定范围复制
	Array(std::initializer_list<value_type> initVals);//从初始化列表构造
	Array &operator=(const Array &it);//拷贝赋值
	Array &operator=(Array &&it);//转移赋值
	Array &operator=(std::initializer_list<value_type> Vals);//初始化列表赋值
	~Array();//析构

	/*容量相关函数*/
	void reserve(size_type n);//确保capacity()>=n
	void resize(size_type n, const value_type &initVal = value_type());//确保size()==n
	bool empty() const;//容器是否为空
	size_type size() const;//容器中元素个数
	size_type max_size() const;//系统允许最大元素个数
	size_type capacity() const;//容器中能够存储的元素个数，有capacity()>=size()

	/*迭代器相关函数*/
	iterator begin();//返回容器首迭代器
	iterator end();//返回容器尾迭代器
	reverse_iterator rbegin();//返回容器反向首迭代器
	reverse_iterator rend();//返回容器反向尾迭代器
	const_iterator begin()const;//返回容器首常量迭代器
	const_iterator end()const;//返回容器尾常量迭代器
	const_reverse_iterator rbegin()const;//返回容器常量反向首迭代器
	const_reverse_iterator rend()const;//返回容器常量反向尾迭代器
	const_iterator cbegin()const;//返回容器首常量迭代器
	const_iterator cend()const;//返回容器尾常量迭代器
	const_reverse_iterator crbegin()const;//返回容器常量反向首迭代器
	const_reverse_iterator crend()const;//返回容器常量反向尾迭代器

	/*数据读取相关函数*/
	reference front();//返回首元素引用
	reference back();//返回尾元素引用
	reference operator[](size_type pos);//返回下标为pos的元素的引用（无边界检查）
	reference at(size_type pos)throw(std::out_of_range);//返回下标为pos的元素的引用
	const_reference front()const;//返回首元素常引用
	const_reference back()const;//返回尾元素常引用
	const_reference operator[](size_type pos)const;//返回下标为pos的元素的常引用（无边界检查）
	const_reference at(size_type pos)const throw(std::out_of_range);//返回下标为pos的元素的引用

	/*数据修改相关函数*/
	void push_back(const value_type &Val); //向末尾添加元素
	void pop_back();//弹出尾元素
	void swap(Array<value_type> &it);//交换两个Array
	iterator insert(iterator pos, const size_type n, const value_type &Val = value_type())throw(std::out_of_range);//在插入点插入n个相同元素
	iterator insert(iterator pos, const value_type &Val = value_type())throw(std::out_of_range);//在插入点插入元素
	iterator insert(iterator pos, const_iterator first, const_iterator last)throw(std::out_of_range);//在插入点插入指定范围的元素
	iterator erase(iterator pos)throw(std::out_of_range);//删除指定元素，返回后一个元素的迭代器（或end()）
	iterator erase(iterator first, iterator last)throw(std::out_of_range, std::invalid_argument);//删除迭代器指定的一段元素，返回后一个元素的迭代器（或end()）
	void clear();//清空
	void assign(const_iterator first, const_iterator last)throw(std::invalid_argument);//复制范围赋值
	void assign(size_type n, const value_type &Val = value_type());//赋值，用指定元素序列覆盖容器内所有元素

	/*容器元素比较*/
	bool operator==(Array<value_type> rightVal);//容器元素是否相同
	bool operator!=(Array<value_type> rightVal);

private:
	pointer Start;//指向已用空间的头
	pointer Finish;//指向已用空间的尾
	pointer End;//指向可用空间的尾，有End>=Finish
};


/*
--------------const_iterator--------------
*/

template<typename T>
inline Array<T>::const_iterator::const_iterator() : Ptr(nullptr) {}
template<typename T>
inline Array<T>::const_iterator::const_iterator(value_type *ptr) : Ptr(ptr) {}
template<typename T>
inline typename Array<T>::const_iterator::reference Array<T>::const_iterator::operator*() const {
	return *Ptr;
}
template<typename T>
inline typename Array<T>::const_iterator::pointer Array<T>::const_iterator::operator->() const {
	return Ptr;
}
template<typename T>
inline typename Array<T>::const_iterator::reference Array<T>::const_iterator::operator[](difference_type off) const {
	return *(Ptr + off);
}
template<typename T>
inline typename Array<T>::const_iterator Array<T>::const_iterator::operator+(difference_type dif) const {
	return const_iterator(Ptr + dif);
}
template<typename T>
inline typename Array<T>::const_iterator operator+(int dif, typename Array<T>::const_iterator myIter) {
	return Array<T>::const_iterator(myIter.Ptr + dif);
}
template<typename T>
inline typename Array<T>::const_iterator Array<T>::const_iterator::operator-(difference_type dif) const {
	return const_iterator(Ptr - dif);
}
template<typename T>
inline int Array<T>::const_iterator::operator-(const_iterator rightVal) const {
	return Ptr - rightVal.Ptr;
}
template<typename T>
inline typename Array<T>::const_iterator &Array<T>::const_iterator::operator++() {
	++Ptr;
	return *this;
}
template<typename T>
inline typename Array<T>::const_iterator Array<T>::const_iterator::operator++(int) {
	auto tmp = *this;
	++Ptr;
	return tmp;
}
template<typename T>
inline typename Array<T>::const_iterator &Array<T>::const_iterator::operator--() {
	--Ptr;
	return *this;
}
template<typename T>
inline typename Array<T>::const_iterator Array<T>::const_iterator::operator--(int) {
	auto tmp = *this;
	--Ptr;
	return tmp;
}
template<typename T>
inline typename Array<T>::const_iterator &Array<T>::const_iterator::operator+=(difference_type dif) {
	Ptr += dif;
	return *this;
}
template<typename T>
inline typename Array<T>::const_iterator &Array<T>::const_iterator::operator-=(difference_type dif) {
	Ptr -= dif;
	return *this;
}
template<typename T>
inline bool Array<T>::const_iterator::operator==(const_iterator rightVal) const {
	return Ptr == rightVal.Ptr;
}
template<typename T>
inline bool Array<T>::const_iterator::operator!=(const_iterator rightVal) const {
	return Ptr != rightVal.Ptr;
}
template<typename T>
inline bool Array<T>::const_iterator::operator<(const_iterator rightVal) const {
	return Ptr < rightVal.Ptr;
}
template<typename T>
inline bool Array<T>::const_iterator::operator<=(const_iterator rightVal) const {
	return Ptr <= rightVal.Ptr;
}
template<typename T>
inline bool Array<T>::const_iterator::operator>(const_iterator rightVal) const {
	return Ptr > rightVal.Ptr;
}
template<typename T>
inline bool Array<T>::const_iterator::operator>=(const_iterator rightVal) const {
	return Ptr >= rightVal.Ptr;
}

/*
--------------iterator--------------
*/

template<typename T>
inline Array<T>::iterator::iterator() : iterBase(nullptr) {}
template<typename T>
inline Array<T>::iterator::iterator(value_type *ptr) : iterBase(ptr) {}
template<typename T>
inline typename Array<T>::iterator::reference Array<T>::iterator::operator*() const {
	return *Ptr;
}
template<typename T>
inline typename Array<T>::iterator::pointer Array<T>::iterator::operator->() const {
	return Ptr;
}
template<typename T>
inline typename Array<T>::iterator::reference Array<T>::iterator::operator[](difference_type off) const {
	return *(Ptr + off);
}
template<typename T>
inline typename Array<T>::iterator Array<T>::iterator::operator+(difference_type dif) const {
	return iterator(Ptr + dif);
}
template<typename T>
inline typename Array<T>::iterator operator+(int dif, typename Array<T>::iterator myIter) {
	return Array<T>::iterator(myIter.Ptr + dif);
}
template<typename T>
inline typename Array<T>::iterator Array<T>::iterator::operator-(difference_type dif) const {
	return iterator(Ptr - dif);
}
template<typename T>
inline int Array<T>::iterator::operator-(const_iterator rightVal) const {
	return Ptr - rightVal.Ptr;
}
template<typename T>
inline typename Array<T>::iterator &Array<T>::iterator::operator++() {
	++Ptr;
	return *this;
}
template<typename T>
inline typename Array<T>::iterator Array<T>::iterator::operator++(int) {
	auto tmp = *this;
	++Ptr;
	return tmp;
}
template<typename T>
inline typename Array<T>::iterator &Array<T>::iterator::operator--() {
	--Ptr;
	return *this;
}
template<typename T>
inline typename Array<T>::iterator Array<T>::iterator::operator--(int) {
	auto tmp = *this;
	--Ptr;
	return tmp;
}
template<typename T>
inline typename Array<T>::iterator &Array<T>::iterator::operator+=(difference_type dif) {
	Ptr += dif;
	return *this;
}
template<typename T>
inline typename Array<T>::iterator &Array<T>::iterator::operator-=(difference_type dif) {
	Ptr -= dif;
	return *this;
}

/*
--------------Array--------------
*/

#define iterator typename Array<T>::iterator
#define reverse_iterator typename Array<T>::reverse_iterator
#define const_iterator typename Array<T>::const_iterator
#define const_reverse_iterator typename Array<T>::const_reverse_iterator

/*构造、析构、赋值运算符相关函数*/
//从指定大小和初值构造
template<typename T>
Array<T>::Array(size_type size, const value_type &initVal) {
	Start = new value_type[size];
	End = Finish = Start + size;

	for (pointer iLoop = Start; iLoop != End; ++iLoop)
		*iLoop = initVal;
}
//复制构造
template<typename T>
Array<T>::Array(const Array &it) {
	const size_type targetSize = it.size();
	Start = new value_type[targetSize];
	End = Finish = Start + targetSize;

	for (size_type iLoop = 0; iLoop < targetSize; ++iLoop)
		Start[iLoop] = it[iLoop];
}

//转移构造
template<typename T>
Array<T>::Array(Array &&it) {
	Start = it.Start;
	End = it.End;
	Finish = it.Finish;
	it.Start = it.End = it.Finish = nullptr;
}

//从给定范围复制
template<typename T>
Array<T>::Array(const_iterator first, const_iterator last) {
	if (last < first) throw std::invalid_argument("interval invalid!");

	size_type n = last - first;
	Start = new value_type[n];
	End = Finish = Start + n;

	for (size_type iLoop = 0; iLoop < n; ++iLoop) Start[iLoop] = first[iLoop];
}
//从初始化列表构造
template<typename T>
Array<T>::Array(std::initializer_list<value_type> initVals) {
	size_type n = initVals.size();
	Start = new value_type[n];
	End = Finish = Start + n;

	for (size_type iLoop = 0; iLoop < n; ++iLoop) Start[iLoop] = *(initVals.begin() + iLoop);
}

//拷贝赋值
template<typename T>
inline Array<T> &Array<T>::operator=(const Array &it) {
	if (&it != this)  //非自赋值才执行操作
		assign(it.begin(), it.end());

	return *this;
}

//转移赋值
template<typename T>
inline Array<T> &Array<T>::operator=(Array &&it) {
	if (&it != this) {//非自赋值才执行操作
		Start = it.Start;
		End = it.End;
		Finish = it.Finish;
		it.Start = it.End = it.Finish = nullptr;
	}

	return *this;
}

//初始化列表赋值
template<typename T>
Array<T> &Array<T>::operator=(std::initializer_list<value_type> Vals) {
	size_type n = Vals.size();

	if (capacity() < n) {
		delete[]Start;
		Start = new value_type[n];
		End = Start + n;
	}

	Finish = Start + n;

	for (size_type iLoop = 0; iLoop < n; ++iLoop) Start[iLoop] = Vals.begin()[iLoop];

	return *this;
}

//析构
template<typename T>
inline Array<T>::~Array() {
	delete[]Start;
}

/*容量相关函数*/
//确保capacity()>=n
template<typename T>
void Array<T>::reserve(size_type n) {
	if (capacity() < n) {
		pointer tmp = new value_type[n];

		for (size_type iLoop = 0; iLoop < size(); ++iLoop)
			tmp[iLoop] = Start[iLoop];

		for (size_type iLoop = size(); iLoop < n; ++iLoop)
			tmp[iLoop] = value_type();

		delete[]Start;
		Finish = tmp + size();
		Start = tmp;
		End = Start + n;
	}
}
//确保size()==n
template<typename T>
void Array<T>::resize(size_type n, const value_type &initVal) {
	const size_type oldSize = size();

	if (oldSize == n)return;

	if (capacity() < n) {
		pointer tmp = new value_type[n];

		for (size_type iLoop = 0; iLoop < oldSize; ++iLoop)
			tmp[iLoop] = Start[iLoop];

		for (size_type iLoop = oldSize; iLoop < n; ++iLoop)
			tmp[iLoop] = initVal;

		delete[]Start;
		Start = tmp;
		End = Finish = Start + n;
	} else
		Finish = Start + n;
}
//容器是否为空
template<typename T>
inline bool Array<T>::empty() const {
	return Start == Finish;
}
//系统最大元素个数
template<typename T>
inline unsigned int Array<T>::max_size() const {
	return size_type(-1) / sizeof(value_type);
}
//容器中元素个数
template<typename T>
inline unsigned int Array<T>::size() const {
	return Finish - Start;
}
//容器中能够存储的元素个数，有capacity()>=size()
template<typename T>
inline unsigned int Array<T>::capacity() const {
	return End - Start;
}

/*迭代器相关函数*/
//返回容器首迭代器
template<typename T>
inline iterator Array<T>::begin() {
	return iterator(Start);
}
//返回容器尾迭代器
template<typename T>
inline iterator Array<T>::end() {
	return iterator(Finish);
}
template<typename T>
//返回容器反向首迭代器
inline reverse_iterator Array<T>::rbegin() {
	return reverse_iterator(end());
}
//返回容器反向尾迭代器
template<typename T>
inline reverse_iterator Array<T>::rend() {
	return reverse_iterator(begin());
}
//返回容器首常量迭代器
template<typename T>
inline  const_iterator Array<T>::begin() const {
	return const_iterator(Start);
}
//返回容器尾常量迭代器
template<typename T>
inline const_iterator Array<T>::end() const {
	return const_iterator(Finish);
}
//返回容器常量反向首迭代器
template<typename T>
inline const_reverse_iterator Array<T>::rbegin() const {
	return const_reverse_iterator(end());
}
//返回容器常量反向尾迭代器
template<typename T>
inline const_reverse_iterator Array<T>::rend() const {
	return const_reverse_iterator(begin());
}
//返回容器首常量迭代器
template<typename T>
inline  const_iterator Array<T>::cbegin() const {
	return begin();
}
//返回容器尾常量迭代器
template<typename T>
inline const_iterator Array<T>::cend() const {
	return end();
}
//返回容器常量反向首迭代器
template<typename T>
inline const_reverse_iterator Array<T>::crbegin() const {
	return rbegin();
}
//返回容器常量反向尾迭代器
template<typename T>
inline const_reverse_iterator Array<T>::crend() const {
	return rend();
}
/*数据读取相关函数*/
//返回首元素引用
template<typename T>
inline T &Array<T>::front() {
	return *Start;
}
//返回尾元素引用
template<typename T>
inline T &Array<T>::back() {
	return *(Finish - 1);
}
//返回下标为pos的元素的引用（无边界检查）
template<typename T>
inline T &Array<T>::operator[](size_type pos) {
	return Start[pos];
}
//返回下标为pos的元素的引用
template<typename T>
inline T &Array<T>::at(size_type pos) {
	if (pos >= size()) throw std::out_of_range("offset out of range!");

	return Start[pos];
}
//返回首元素常引用
template<typename T>
inline const T &Array<T>::front()const {
	return *Start;
}
//返回尾元素常引用
template<typename T>
inline const T &Array<T>::back()const {
	return *(Finish - 1);
}
//返回下标为pos的元素的常引用（无边界检查）
template<typename T>
inline const T &Array<T>::operator[](size_type pos)const {
	return Start[pos];
}
//返回下标为pos的元素的常引用
template<typename T>
inline const T &Array<T>::at(size_type pos)const {
	if (pos >= size()) throw std::out_of_range("offset out of range!");

	return Start[pos];
}

/*数据修改相关函数*/
//向末尾添加元素
template<typename T>
void Array<T>::push_back(const value_type &Val) {
	if (Finish == End) {//无可用空间
		if (End == Start)reserve(1);
		else reserve(3 * size() / 2);//容量是否为0
	}

	*Finish = Val;
	++Finish;
}
//弹出尾元素
template<typename T>
inline void Array<T>::pop_back() {
	if (Finish != Start) --Finish;
}

//交换两个Array
template<typename T>
inline void Array<T>::swap(Array<T> &it) {
	pointer tmp = Start;
	Start = it.Start;
	it.Start = tmp;
	tmp = Finish;
	Finish = it.Finish;
	it.Finish = tmp;
	tmp = End;
	End = it.End;
	it.End = tmp;
}
template<typename T>
inline void swap(Array<T> &leftVal, Array<T> &rightVal) {
	leftVal.swap(rightVal);
}

//在插入点插入n个相同元素
template<typename T>
iterator Array<T>::insert(iterator pos, const size_type n, const value_type &Val) {
	if (0 == n)return pos;

	if (pos.Ptr < Start || pos.Ptr > Finish) throw std::out_of_range("iterator out of range!");

	if (size_type(End - Finish) >= n) {//还有可用空间
		for (pointer iLoop = Finish; iLoop >= pos.Ptr; --iLoop)
			iLoop[n] = *iLoop;

		Finish += n;

		for (size_type iLoop = 0; iLoop < n; ++iLoop)
			pos[iLoop] = Val;

		return pos;
	} else { //无可用空间
		const size_type oldSize = size();
		const size_type targetCap = oldSize + (n > oldSize / 2 ? n : (oldSize / 2));
		const size_type position = pos.Ptr - Start;
		//重新分配空间，复制数据
		pointer tmp = new value_type[targetCap];

		for (size_type iLoop = 0; iLoop < position; ++iLoop)
			tmp[iLoop] = Start[iLoop];

		for (size_type iLoop = position; iLoop < position + n; ++iLoop)
			tmp[iLoop] = Val;

		for (size_type iLoop = position + n; iLoop < oldSize + n; ++iLoop)
			tmp[iLoop] = Start[iLoop - n];

		for (size_type iLoop = oldSize + n; iLoop < targetCap; ++iLoop)
			tmp[iLoop] = value_type();

		//撤销旧空间，修改指针
		delete[]Start;
		Start = tmp;
		Finish = Start + oldSize + n;
		End = Start + targetCap;
		return iterator(Start + position);
	}
}

//在插入点插入指定范围的元素
template<typename T>
iterator Array<T>::insert(iterator pos, const_iterator first, const_iterator last) {
	if (pos.Ptr < Start || pos.Ptr > Finish) throw std::out_of_range("iterator out of range!");

	if (last < first) throw std::invalid_argument("interval invalid!");

	const size_type n = last - first;

	if (0 == n)return pos;

	if (size_type(End - Finish) >= n) {//还有可用空间
		for (pointer iLoop = Finish; iLoop >= pos.Ptr; --iLoop)
			*(iLoop + 1) = *iLoop;

		Finish += n;

		for (size_type iLoop = 0; iLoop < n; ++iLoop)
			pos[iLoop] = first[iLoop]; //赋值

		return pos;
	} else { //无可用空间
		const size_type oldSize = size();
		const size_type targetCap = oldSize + (n > oldSize / 2 ? n : (oldSize / 2));
		const size_type position = pos.Ptr - Start;
		//重新分配空间，复制数据
		pointer tmp = new value_type[targetCap];

		for (size_type iLoop = 0; iLoop < position; ++iLoop)
			tmp[iLoop] = Start[iLoop];

		for (size_type iLoop = position; iLoop < position + n; ++iLoop)
			tmp[iLoop] = *(first++); //赋值

		for (size_type iLoop = position + n; iLoop < oldSize + n; ++iLoop)
			tmp[iLoop] = *(Start + iLoop - n);

		for (size_type iLoop = oldSize + n; iLoop < targetCap; ++iLoop)
			tmp[iLoop] = value_type();

		//撤销旧空间，修改指针
		delete[]Start;
		Start = tmp;
		Finish = Start + oldSize + n;
		End = Start + targetCap;
		return iterator(Start + position);
	}
}

//在插入点插入一个元素
template<typename T>
inline iterator Array<T>::insert(iterator pos, const value_type &Val) {
	return insert(pos, 1, Val);
}

//删除指定元素，返回后一个元素的迭代器（或end()）
template<typename T>
iterator Array<T>::erase(iterator pos) {
	if (pos.Ptr < Start || pos.Ptr > Finish) throw std::out_of_range("iterator out of range!");

	for (pointer iLoop = pos.Ptr; iLoop != Finish - 1; ++iLoop)
		*iLoop = *(iLoop + 1);

	--Finish;
	return pos;
}

//删除迭代器指定的一段元素，返回后一个元素的迭代器（或end()）
template<typename T>
iterator Array<T>::erase(iterator first, iterator last) {
	if (first.Ptr < Start || last.Ptr > Finish) throw std::out_of_range("iterator out of range!");

	const size_type n = last - first;

	if (n > size()) throw std::invalid_argument("interval invalid!");

	for (pointer iLoop = first.Ptr; iLoop != Finish - n; ++iLoop)
		*iLoop = *(iLoop + n);

	Finish -= n;
	return first;
}

//清空
template<typename T>
inline void Array<T>::clear() {
	Finish = Start;
}

//复制范围赋值
template<typename T>
void Array<T>::assign(const_iterator first, const_iterator last) {
	if (last.Ptr < first.Ptr) throw std::invalid_argument("interval invalid!");

	size_type n = last - first;

	if (capacity() < n) {
		delete[]Start;
		Start = new value_type[n];
		End = Start + n;
	}

	Finish = Start + n;

	for (size_type iLoop = 0; iLoop < n; ++iLoop) Start[iLoop] = first[iLoop];
}

//赋值，用指定元素序列覆盖容器内所有元素
template<typename T>
void Array<T>::assign(size_type n, const value_type &Val) {
	if (capacity() < n) {
		delete[]Start;
		Start = new value_type[n];
		End = Start + n;
	}

	for (Finish = Start; size() < n; ++Finish) *Finish = Val;
}

/*容器元素比较*/
template<typename T>
bool Array<T>::operator==(Array<value_type> rightVal) {
	if (size() != rightVal.size())return false;

	bool isEqu = true;

	for (size_type iLoop = 0; iLoop < size(); ++iLoop) {
		if (Start[iLoop] != rightVal[iLoop]) {
			isEqu = false;
			break;
		}
	}

	return isEqu;
}

template<typename T>
inline bool Array<T>::operator!=(Array<value_type> rightVal) {
	return !(*this == rightVal);
}

#undef iterator
#undef reverse_iterator
#undef const_iterator
#undef const_reverse_iterator

#endif /* ARRAY_H */
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

	//iterator(�̳���const_iterator)
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

	//�������������
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
	//���������
	typedef std::reverse_iterator<iterator> reverse_iterator;

	/*
	--------------functions--------------
	*/

	/* constructors, destructor, assignment operators */
	explicit Array(size_type size = 0, const value_type &initVal = value_type());//��ָ����С�ͳ�ֵ����
	Array(const Array &it);//���ƹ���
	Array(Array &&it);//ת�ƹ���
	Array(const_iterator first, const_iterator last);//�Ӹ�����Χ����
	Array(std::initializer_list<value_type> initVals);//�ӳ�ʼ���б���
	Array &operator=(const Array &it);//������ֵ
	Array &operator=(Array &&it);//ת�Ƹ�ֵ
	Array &operator=(std::initializer_list<value_type> Vals);//��ʼ���б�ֵ
	~Array();//����

	/*������غ���*/
	void reserve(size_type n);//ȷ��capacity()>=n
	void resize(size_type n, const value_type &initVal = value_type());//ȷ��size()==n
	bool empty() const;//�����Ƿ�Ϊ��
	size_type size() const;//������Ԫ�ظ���
	size_type max_size() const;//ϵͳ�������Ԫ�ظ���
	size_type capacity() const;//�������ܹ��洢��Ԫ�ظ�������capacity()>=size()

	/*��������غ���*/
	iterator begin();//���������׵�����
	iterator end();//��������β������
	reverse_iterator rbegin();//�������������׵�����
	reverse_iterator rend();//������������β������
	const_iterator begin()const;//���������׳���������
	const_iterator end()const;//��������β����������
	const_reverse_iterator rbegin()const;//�����������������׵�����
	const_reverse_iterator rend()const;//����������������β������
	const_iterator cbegin()const;//���������׳���������
	const_iterator cend()const;//��������β����������
	const_reverse_iterator crbegin()const;//�����������������׵�����
	const_reverse_iterator crend()const;//����������������β������

	/*���ݶ�ȡ��غ���*/
	reference front();//������Ԫ������
	reference back();//����βԪ������
	reference operator[](size_type pos);//�����±�Ϊpos��Ԫ�ص����ã��ޱ߽��飩
	reference at(size_type pos)throw(std::out_of_range);//�����±�Ϊpos��Ԫ�ص�����
	const_reference front()const;//������Ԫ�س�����
	const_reference back()const;//����βԪ�س�����
	const_reference operator[](size_type pos)const;//�����±�Ϊpos��Ԫ�صĳ����ã��ޱ߽��飩
	const_reference at(size_type pos)const throw(std::out_of_range);//�����±�Ϊpos��Ԫ�ص�����

	/*�����޸���غ���*/
	void push_back(const value_type &Val); //��ĩβ���Ԫ��
	void pop_back();//����βԪ��
	void swap(Array<value_type> &it);//��������Array
	iterator insert(iterator pos, const size_type n, const value_type &Val = value_type())throw(std::out_of_range);//�ڲ�������n����ͬԪ��
	iterator insert(iterator pos, const value_type &Val = value_type())throw(std::out_of_range);//�ڲ�������Ԫ��
	iterator insert(iterator pos, const_iterator first, const_iterator last)throw(std::out_of_range);//�ڲ�������ָ����Χ��Ԫ��
	iterator erase(iterator pos)throw(std::out_of_range);//ɾ��ָ��Ԫ�أ����غ�һ��Ԫ�صĵ���������end()��
	iterator erase(iterator first, iterator last)throw(std::out_of_range, std::invalid_argument);//ɾ��������ָ����һ��Ԫ�أ����غ�һ��Ԫ�صĵ���������end()��
	void clear();//���
	void assign(const_iterator first, const_iterator last)throw(std::invalid_argument);//���Ʒ�Χ��ֵ
	void assign(size_type n, const value_type &Val = value_type());//��ֵ����ָ��Ԫ�����и�������������Ԫ��

	/*����Ԫ�رȽ�*/
	bool operator==(Array<value_type> rightVal);//����Ԫ���Ƿ���ͬ
	bool operator!=(Array<value_type> rightVal);

private:
	pointer Start;//ָ�����ÿռ��ͷ
	pointer Finish;//ָ�����ÿռ��β
	pointer End;//ָ����ÿռ��β����End>=Finish
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

/*���졢��������ֵ�������غ���*/
//��ָ����С�ͳ�ֵ����
template<typename T>
Array<T>::Array(size_type size, const value_type &initVal) {
	Start = new value_type[size];
	End = Finish = Start + size;

	for (pointer iLoop = Start; iLoop != End; ++iLoop)
		*iLoop = initVal;
}
//���ƹ���
template<typename T>
Array<T>::Array(const Array &it) {
	const size_type targetSize = it.size();
	Start = new value_type[targetSize];
	End = Finish = Start + targetSize;

	for (size_type iLoop = 0; iLoop < targetSize; ++iLoop)
		Start[iLoop] = it[iLoop];
}

//ת�ƹ���
template<typename T>
Array<T>::Array(Array &&it) {
	Start = it.Start;
	End = it.End;
	Finish = it.Finish;
	it.Start = it.End = it.Finish = nullptr;
}

//�Ӹ�����Χ����
template<typename T>
Array<T>::Array(const_iterator first, const_iterator last) {
	if (last < first) throw std::invalid_argument("interval invalid!");

	size_type n = last - first;
	Start = new value_type[n];
	End = Finish = Start + n;

	for (size_type iLoop = 0; iLoop < n; ++iLoop) Start[iLoop] = first[iLoop];
}
//�ӳ�ʼ���б���
template<typename T>
Array<T>::Array(std::initializer_list<value_type> initVals) {
	size_type n = initVals.size();
	Start = new value_type[n];
	End = Finish = Start + n;

	for (size_type iLoop = 0; iLoop < n; ++iLoop) Start[iLoop] = *(initVals.begin() + iLoop);
}

//������ֵ
template<typename T>
inline Array<T> &Array<T>::operator=(const Array &it) {
	if (&it != this)  //���Ը�ֵ��ִ�в���
		assign(it.begin(), it.end());

	return *this;
}

//ת�Ƹ�ֵ
template<typename T>
inline Array<T> &Array<T>::operator=(Array &&it) {
	if (&it != this) {//���Ը�ֵ��ִ�в���
		Start = it.Start;
		End = it.End;
		Finish = it.Finish;
		it.Start = it.End = it.Finish = nullptr;
	}

	return *this;
}

//��ʼ���б�ֵ
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

//����
template<typename T>
inline Array<T>::~Array() {
	delete[]Start;
}

/*������غ���*/
//ȷ��capacity()>=n
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
//ȷ��size()==n
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
//�����Ƿ�Ϊ��
template<typename T>
inline bool Array<T>::empty() const {
	return Start == Finish;
}
//ϵͳ���Ԫ�ظ���
template<typename T>
inline unsigned int Array<T>::max_size() const {
	return size_type(-1) / sizeof(value_type);
}
//������Ԫ�ظ���
template<typename T>
inline unsigned int Array<T>::size() const {
	return Finish - Start;
}
//�������ܹ��洢��Ԫ�ظ�������capacity()>=size()
template<typename T>
inline unsigned int Array<T>::capacity() const {
	return End - Start;
}

/*��������غ���*/
//���������׵�����
template<typename T>
inline iterator Array<T>::begin() {
	return iterator(Start);
}
//��������β������
template<typename T>
inline iterator Array<T>::end() {
	return iterator(Finish);
}
template<typename T>
//�������������׵�����
inline reverse_iterator Array<T>::rbegin() {
	return reverse_iterator(end());
}
//������������β������
template<typename T>
inline reverse_iterator Array<T>::rend() {
	return reverse_iterator(begin());
}
//���������׳���������
template<typename T>
inline  const_iterator Array<T>::begin() const {
	return const_iterator(Start);
}
//��������β����������
template<typename T>
inline const_iterator Array<T>::end() const {
	return const_iterator(Finish);
}
//�����������������׵�����
template<typename T>
inline const_reverse_iterator Array<T>::rbegin() const {
	return const_reverse_iterator(end());
}
//����������������β������
template<typename T>
inline const_reverse_iterator Array<T>::rend() const {
	return const_reverse_iterator(begin());
}
//���������׳���������
template<typename T>
inline  const_iterator Array<T>::cbegin() const {
	return begin();
}
//��������β����������
template<typename T>
inline const_iterator Array<T>::cend() const {
	return end();
}
//�����������������׵�����
template<typename T>
inline const_reverse_iterator Array<T>::crbegin() const {
	return rbegin();
}
//����������������β������
template<typename T>
inline const_reverse_iterator Array<T>::crend() const {
	return rend();
}
/*���ݶ�ȡ��غ���*/
//������Ԫ������
template<typename T>
inline T &Array<T>::front() {
	return *Start;
}
//����βԪ������
template<typename T>
inline T &Array<T>::back() {
	return *(Finish - 1);
}
//�����±�Ϊpos��Ԫ�ص����ã��ޱ߽��飩
template<typename T>
inline T &Array<T>::operator[](size_type pos) {
	return Start[pos];
}
//�����±�Ϊpos��Ԫ�ص�����
template<typename T>
inline T &Array<T>::at(size_type pos) {
	if (pos >= size()) throw std::out_of_range("offset out of range!");

	return Start[pos];
}
//������Ԫ�س�����
template<typename T>
inline const T &Array<T>::front()const {
	return *Start;
}
//����βԪ�س�����
template<typename T>
inline const T &Array<T>::back()const {
	return *(Finish - 1);
}
//�����±�Ϊpos��Ԫ�صĳ����ã��ޱ߽��飩
template<typename T>
inline const T &Array<T>::operator[](size_type pos)const {
	return Start[pos];
}
//�����±�Ϊpos��Ԫ�صĳ�����
template<typename T>
inline const T &Array<T>::at(size_type pos)const {
	if (pos >= size()) throw std::out_of_range("offset out of range!");

	return Start[pos];
}

/*�����޸���غ���*/
//��ĩβ���Ԫ��
template<typename T>
void Array<T>::push_back(const value_type &Val) {
	if (Finish == End) {//�޿��ÿռ�
		if (End == Start)reserve(1);
		else reserve(3 * size() / 2);//�����Ƿ�Ϊ0
	}

	*Finish = Val;
	++Finish;
}
//����βԪ��
template<typename T>
inline void Array<T>::pop_back() {
	if (Finish != Start) --Finish;
}

//��������Array
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

//�ڲ�������n����ͬԪ��
template<typename T>
iterator Array<T>::insert(iterator pos, const size_type n, const value_type &Val) {
	if (0 == n)return pos;

	if (pos.Ptr < Start || pos.Ptr > Finish) throw std::out_of_range("iterator out of range!");

	if (size_type(End - Finish) >= n) {//���п��ÿռ�
		for (pointer iLoop = Finish; iLoop >= pos.Ptr; --iLoop)
			iLoop[n] = *iLoop;

		Finish += n;

		for (size_type iLoop = 0; iLoop < n; ++iLoop)
			pos[iLoop] = Val;

		return pos;
	} else { //�޿��ÿռ�
		const size_type oldSize = size();
		const size_type targetCap = oldSize + (n > oldSize / 2 ? n : (oldSize / 2));
		const size_type position = pos.Ptr - Start;
		//���·���ռ䣬��������
		pointer tmp = new value_type[targetCap];

		for (size_type iLoop = 0; iLoop < position; ++iLoop)
			tmp[iLoop] = Start[iLoop];

		for (size_type iLoop = position; iLoop < position + n; ++iLoop)
			tmp[iLoop] = Val;

		for (size_type iLoop = position + n; iLoop < oldSize + n; ++iLoop)
			tmp[iLoop] = Start[iLoop - n];

		for (size_type iLoop = oldSize + n; iLoop < targetCap; ++iLoop)
			tmp[iLoop] = value_type();

		//�����ɿռ䣬�޸�ָ��
		delete[]Start;
		Start = tmp;
		Finish = Start + oldSize + n;
		End = Start + targetCap;
		return iterator(Start + position);
	}
}

//�ڲ�������ָ����Χ��Ԫ��
template<typename T>
iterator Array<T>::insert(iterator pos, const_iterator first, const_iterator last) {
	if (pos.Ptr < Start || pos.Ptr > Finish) throw std::out_of_range("iterator out of range!");

	if (last < first) throw std::invalid_argument("interval invalid!");

	const size_type n = last - first;

	if (0 == n)return pos;

	if (size_type(End - Finish) >= n) {//���п��ÿռ�
		for (pointer iLoop = Finish; iLoop >= pos.Ptr; --iLoop)
			*(iLoop + 1) = *iLoop;

		Finish += n;

		for (size_type iLoop = 0; iLoop < n; ++iLoop)
			pos[iLoop] = first[iLoop]; //��ֵ

		return pos;
	} else { //�޿��ÿռ�
		const size_type oldSize = size();
		const size_type targetCap = oldSize + (n > oldSize / 2 ? n : (oldSize / 2));
		const size_type position = pos.Ptr - Start;
		//���·���ռ䣬��������
		pointer tmp = new value_type[targetCap];

		for (size_type iLoop = 0; iLoop < position; ++iLoop)
			tmp[iLoop] = Start[iLoop];

		for (size_type iLoop = position; iLoop < position + n; ++iLoop)
			tmp[iLoop] = *(first++); //��ֵ

		for (size_type iLoop = position + n; iLoop < oldSize + n; ++iLoop)
			tmp[iLoop] = *(Start + iLoop - n);

		for (size_type iLoop = oldSize + n; iLoop < targetCap; ++iLoop)
			tmp[iLoop] = value_type();

		//�����ɿռ䣬�޸�ָ��
		delete[]Start;
		Start = tmp;
		Finish = Start + oldSize + n;
		End = Start + targetCap;
		return iterator(Start + position);
	}
}

//�ڲ�������һ��Ԫ��
template<typename T>
inline iterator Array<T>::insert(iterator pos, const value_type &Val) {
	return insert(pos, 1, Val);
}

//ɾ��ָ��Ԫ�أ����غ�һ��Ԫ�صĵ���������end()��
template<typename T>
iterator Array<T>::erase(iterator pos) {
	if (pos.Ptr < Start || pos.Ptr > Finish) throw std::out_of_range("iterator out of range!");

	for (pointer iLoop = pos.Ptr; iLoop != Finish - 1; ++iLoop)
		*iLoop = *(iLoop + 1);

	--Finish;
	return pos;
}

//ɾ��������ָ����һ��Ԫ�أ����غ�һ��Ԫ�صĵ���������end()��
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

//���
template<typename T>
inline void Array<T>::clear() {
	Finish = Start;
}

//���Ʒ�Χ��ֵ
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

//��ֵ����ָ��Ԫ�����и�������������Ԫ��
template<typename T>
void Array<T>::assign(size_type n, const value_type &Val) {
	if (capacity() < n) {
		delete[]Start;
		Start = new value_type[n];
		End = Start + n;
	}

	for (Finish = Start; size() < n; ++Finish) *Finish = Val;
}

/*����Ԫ�رȽ�*/
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
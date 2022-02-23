#pragma once
#include<iostream>
#include<iterator>
#include<string>
using namespace std;
#define tab "\t"
using std::cin;
using std::cout;
using std::endl;

template<typename T>
class List
{

	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr);
		~Element();
		friend class List<T>;
	}*Head, * Tail;
	size_t size;



	class BaseIterator
	{
	protected:
		Element* Temp;
	public:
		BaseIterator(Element* Temp = nullptr);
		~BaseIterator();
		bool operator==(const BaseIterator& other)const;
		bool operator!=(const BaseIterator& other)const;
		const T& operator*()const;
		operator bool()const;

	};

public:

	class ConstIterator :public BaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr);
		~ConstIterator();

		ConstIterator& operator++();
		ConstIterator operator++(int);
		ConstIterator& operator--();
		ConstIterator operator--(int);


	};

	class ConstReverseIterator :public BaseIterator
	{
	public:

		ConstReverseIterator(Element* Temp = nullptr);
		~ConstReverseIterator();
		ConstReverseIterator& operator++();
		ConstReverseIterator operator++(int);
		ConstReverseIterator& operator--();
		ConstReverseIterator operator--(int);
		const int& operator*()const;

	};

	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr);
		~ReverseIterator();
		T& operator*();
	};


	class Iterator : public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr);
		~Iterator();
		T& operator*();

	};

	ConstIterator cbegin()const;
	ConstIterator cend()const;
	ReverseIterator rbegin();
	ReverseIterator rend();
	ConstReverseIterator crbegin()const;
	ConstReverseIterator crend()const;
	Iterator begin();
	Iterator end();

	List();
	List(unsigned int size);
	List(const initializer_list<T>& il);
	~List();


	//  Methods:

	void print()const;
	void revers_print()const;
	void push_front(T Data);
	void push_back(T Data);
	void insert(int index, T Data);
	void pop_front();
	void pop_back();
	void erase(int index);
};
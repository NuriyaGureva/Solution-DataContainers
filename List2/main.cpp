#include<iostream>
#include<iterator>
using namespace std;
#define tab "\t"
using std::cin;
using std::cout;
using std::endl;

	
class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
		
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) :
			Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << " EDestructor:\t" << this << endl;
		}
		friend class List;	
	}*Head,*Tail;
	size_t size;//size_t-unsigned int

public:
	class Iterator
	{
		Element* Temp;

	public:
		Iterator(Element* Temp = nullptr) :Temp(Temp)
		{
			cout << "ItConstructor:\t" << this << endl;
		}
		~Iterator()
		{
			cout << "ItDeconstructor:\t" << this << endl;
		}

		Iterator& operator++()
		{
			Temp = Temp->pNext;

			return *this;
		}
		Iterator operator++(int)
		{
			Iterator old = *this;
			Temp = Temp->pNext;
	         return old;			
		}
		Iterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		Iterator operator--(int)
		{
			Iterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		bool operator==(const Iterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const Iterator& other)const
		{
			return this->Temp != other.Temp;
		}
		int& operator*()
		{
			return Temp->Data;
		}
		const int& operator*()const
		{
			return Temp->Data;
		}

	};
	class ReversIterator
	{
		Element* Temp;
	public:
		ReversIterator(Element* Temp = nullptr) :Temp(Temp)
		{
			cout << "RltConstructor:\t" << this << endl;
		}
		~ReversIterator()
		{
			cout << "RltDeconstructor:\t" << this << endl;
		}
		ReversIterator& operator++()
		{
			Temp = Temp->pPrev;

			return *this;
		}
		ReversIterator operator++(int)
		{
			ReversIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ReversIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ReversIterator operator--(int)
		{
			ReversIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		bool operator==(const ReversIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ReversIterator& other)const
		{
			return this->Temp != other.Temp;
		}
		int& operator*()
		{
			return Temp->Data;
		}
		const int& operator*()const
		{
			return Temp->Data;
		}
		operator bool()const
		{
			return Temp;
		}

	};

	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	ReversIterator rbegin()
	{
		return Tail;
	}
	ReversIterator rend()
	{
		return nullptr;
	}
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << " LConsructor:\t" << this << endl;
	}
	List(unsigned int size) :List()
	{	
		for (int i = 0; i < size; i++)
		{
			push_front(0);
			push_back(0);
		}
	}
	List(const initializer_list<int>& il):List()
	{		
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); ++ it)
		{			
			push_back(*it);		
		}	

	}
	~List()
	{
		while (Head)pop_front();	
		while (Tail)pop_back();		
		cout << "LDestructor:\t" << this << endl;
	}
	//const int& operator[](int index)const
	//{
	//	Element* Temp = Head;
	//
	//	for (int i = 0; i < index; i++) Temp = Temp->pNext;
	//	return Temp->Data;
	//}
	//int& operator[](int index)
	//{
	//	Element* Temp = Head;
	//	for (int i = 0; i < index; i++) Temp = Temp->pNext;
	//	return Temp->Data;
	//}
	     //Adding elements:

		//          Methods:
	void print()const
	{
	   cout << "Количество элементов списка: " << size <<endl;
	   for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	}
	void revers_print()const
	{
		cout << "Количество элементов списка: " << size <<endl;
		for(Element* Temp=Tail; Temp; Temp=Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	}
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		   size++;
		   return;
		}
	Element* New = new Element(Data);
	New->pNext = Head;
	Head->pPrev = New;
	Head = New;
	//Head = Head->pPrev = new Element(Data, Head);
	size++;
	}
	void push_back(int Data)
	{	
	/*	if (Tail == nullptr)return push_front(Data);				
		Element* Temp = Tail;
		while (Temp->pNext)
		Temp = Temp->pNext;			
		Temp->pNext = new Element(Data);		
		size++;*/
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		Element* New = new Element(Data);
		New->pPrev = Tail;
		Tail->pNext=New; 
		Tail = New;	
		size++;

	}
	void insert(int index, int Data)
	{
	/*	if (index == 0 || Head == nullptr) return push_front(Data);
		if (index > size)return;		
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)
		Temp = Temp->pNext;	
		Temp->pNext = new Element(Data, Temp->pNext);
		size++;*/
		Element* Temp;
		if (index > size)return;
		if (index == 0)return push_front(Data);
		if (index == size)return push_back(Data);
		if (index<size/2)
		{
			Temp = Head;
			for (int i = 0; i < index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size- 1 - index; i++)Temp = Temp->pPrev;
		}
		Element* New = new Element(Data);
		New->pNext = Temp;
		New->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;
		size++;
	}
	
	void pop_front()
	{
		if (Head == nullptr && Tail==nullptr)return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			size--;
			return;
		}
	    Head = Head->pNext;	  
		delete Head-> pPrev;
		Head->pPrev = nullptr;		
		size--;
	}
	void pop_back()
	{
		/*if (Tail == nullptr)return;		
		Element* Temp = Tail;
		while (Temp->pNext->pNext)Temp = Temp->pNext;		
		delete Temp->pNext;		
		Temp->pNext = nullptr;
		size--;*/
		
		if (Head == Tail)return pop_front();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		Head = nullptr;
		size--;
	}
	void erase(int index)
	{
		if (index == 0 || Head == nullptr) return;
	
		Element* Temp = Head;
		Element* pPev = nullptr;
		for (int i = 0; i<index; i++)
		{
			Temp = Temp->pNext;
		}

		Element* Prev = Temp->pPrev;
		Element* Next = Temp->pNext;

		Prev->pNext = Next;
		Next->pPrev = Prev;

		delete Temp;
		size--;
	}
	
};

#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK

	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
		//list.push_back(rand() % 100);
	}
/*	list.print();
	list.revers_print();
	list.push_front(100);
	list.print();
	list.push_back(100);
	list.print();
	list.pop_back();
	list.print();
	list.pop_front();
	list.print();*/	

	int index;
	int value;
	cout << " Введите индекс добавляемого элемента:";
	cin >> index;
	cout << " Введите значение добавляемого элемента:";
	cin >> value;
	list.insert(index, value);
	list.print();
	//list.revers_print();
	cout << "Введите индекс удаляемого элемента:";
	cin >> index;
	list.erase(index);
	list.print();
	//list.revers_print();

#endif // BASE_CHECK

	//List list = { 3,5,8,13,21 };
	//list.print();
	//for (int i : list)
	//{
	//	cout << i << tab;
	//}
	//cout << endl;
	//for (List::ReversIterator it = list.rbegin(); it; ++it)
	//{
	//	cout << *it << tab;
	//}
	//cout << endl;
}
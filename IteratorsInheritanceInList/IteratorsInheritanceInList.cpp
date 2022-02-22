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
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr) :
			Data(Data), pNext(pNext), pPrev(pPrev)
		{
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

		}

		~Element()		
		{
#ifdef DEBUG
			cout << " EDestructor:\t" << this << endl;
#endif // DEBUG

		}
		friend class List<T>;
	}*Head, * Tail;
	size_t size;//size_t-unsigned int


	class BaseIterator
	{
	protected:
		Element* Temp;
	public:
	
		BaseIterator(Element* Temp=nullptr) :Temp(Temp)

		{
#ifdef  DEBUG
			cout << "BitConstructor:\t" << this << endl;
#endif //  DEBUG
	    }
		~BaseIterator()
		{
#ifdef DEBUG
			cout << " BitDestructor:\t" << this << endl;
#endif // DEBUG

		}
	/*	virtual BaseIterator& operator ++() = 0;		
		virtual BaseIterator& operator --() = 0;*/

		bool operator==(const BaseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const BaseIterator& other)const
		{
			return this->Temp != other.Temp;
		}

		const T& operator*()const
		{
			return Temp->Data;
		}
		operator bool()const
		{
			return Temp;
		}
	};

public:

	class ConstIterator:public BaseIterator
	{		
	public:

		ConstIterator(Element* Temp = nullptr) :BaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "CItConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~ConstIterator()
		{
#ifdef DEBUG
			cout << "CItDeconstructor:\t" << this << endl;
#endif // DEBUG

		}
		ConstIterator& operator++()
		{
			BaseIterator::Temp = BaseIterator:: Temp->pNext;

			return *this;
		}
		ConstIterator operator++(int)
		{
			ConstIterator old = *this;
			BaseIterator::Temp = BaseIterator::Temp->pNext;
			return old;
		}
		ConstIterator& operator--()
		{
			BaseIterator::Temp = BaseIterator::Temp->pPrev;
			return *this;
		}
		ConstIterator operator--(int)
		{
			ConstIterator old = *this;
			BaseIterator::Temp = BaseIterator::Temp->pPrev;
			return old;
		}
	
	};
	class ConstReverseIterator :public BaseIterator
	{	
	public:

		ConstReverseIterator(Element* Temp = nullptr) :BaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "CRltConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~ConstReverseIterator()
		{
#ifdef DEBUG
			cout << "CRltDeconstructor:\t" << this << endl;
#endif // DEBUG

		}
		ConstReverseIterator& operator++()
		{	
			BaseIterator::Temp = BaseIterator::Temp->pPrev;

			return *this;
		}
		ConstReverseIterator operator++(int)
		{
			ConstReverseIterator old = *this;
			BaseIterator::Temp = BaseIterator::Temp->pPrev;
			return old;
		}
		ConstReverseIterator& operator--()
		{
			BaseIterator::Temp = BaseIterator::Temp->pNext;
			return *this;
		}
		ConstReverseIterator operator--(int)
		{
			ConstReverseIterator old = *this;
			BaseIterator::Temp = BaseIterator::Temp->pNext;
			return old;
		}

		const int& operator*()const
		{
			return BaseIterator:: Temp->Data;
		}

	};
	class ReverseIterator:public ConstReverseIterator
	{
		
	public:
		ReverseIterator(Element* Temp = nullptr) :ConstReverseIterator(Temp)
		{
#ifdef DEBUG
			cout << "RltConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~ReverseIterator()
		{
#ifdef DEBUG
			cout << "RltDeconstructor:\t" << this << endl;
#endif // DEBUG

		}					
		T& operator*()
		{
			return BaseIterator ::Temp->Data;
		}
	};

	class Iterator : public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr) :ConstIterator(Temp)
		{
#ifdef DEBUG
			cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~Iterator()
		{
#ifdef DEBUG
			cout << "ItDeconstructor:\t" << this << endl;
#endif // DEBUG

		}	
	
		T& operator*()
		{
			return BaseIterator::Temp->Data;
		}		

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





template<typename T>
 typename List<T>::ConstIterator List<T>:: cbegin()const
{
	return Head;
}
template<typename T>
typename List<T>::ConstIterator List<T>::cend()const
{
	return nullptr;
}
template<typename T>
typename List<T>::ReverseIterator List<T>::rbegin()
{
	return Tail;
}
template<typename T>
typename List<T>::ReverseIterator List<T>::rend()
{
	return nullptr;
}
template<typename T>
typename List<T>::ConstReverseIterator List<T>::crbegin()const
{
	return Tail;
}
template<typename T>
typename List<T>::ConstReverseIterator List<T>::crend()const
{
	return nullptr;
}
template<typename T>
typename List<T>::Iterator List<T>::begin()
{
	return Head;
}
template<typename T>
typename List<T>::Iterator List<T>::end()
{
	return nullptr;
}

template<typename T>List<T>::List()
{
	Head = Tail = nullptr;
	size = 0;

#ifdef DEBUG
	cout << " LConsructor:\t" << this << endl;
#endif // DEBUG

}
template<typename T>List<T>::List(unsigned int size) :List()
{
	for (int i = 0; i < size; i++)
	{
		push_front(0);
		push_back(0);
	}
}
template<typename T>List<T>::List(const initializer_list<T>& il) :List()
{
	cout << typeid(il.begin()).name() << endl;
	for (T const* it = il.begin(); it != il.end(); ++it)
	{
		push_back(*it);
	}

}
template<typename T>List<T>::~List()
{
	while (Head)pop_front();
	while (Tail)pop_back();

#ifdef DEBUG
	cout << "LDestructor:\t" << this << endl;
#endif // DEBUG

}

//          Methods:
template<typename T>
  void List<T>::print()const
{
	cout << "Количество элементов списка: " << size << endl;
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
}
  template<typename T>
void List<T>::revers_print()const
{
	cout << "Количество элементов списка: " << size << endl;
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
}
template<typename T>
void List<T>::push_front(T Data)
{
	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = new Element(Data);
		size++;
		return;
	}

	Head = Head->pPrev = new Element(Data, Head);
	size++;
}
template<typename T>
void List<T>::push_back(T Data)
{

	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = new Element(Data);
		size++;
		return;
	}
	
	Tail = Tail->pNext = new Element(Data, nullptr, Tail);
	size++;

}
template<typename T>
void List<T>::insert(int index, T Data)
{
	
	Element* Temp;
	if (index > size)return;
	if (index == 0)return push_front(Data);
	if (index == size)return push_back(Data);
	if (index < size / 2)
	{
		Temp = Head;
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail;
		for (int i = 0; i < size - 1 - index; i++)Temp = Temp->pPrev;
	}
	
	Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
	size++;
}
template<typename T>
void List<T>::pop_front()
{
	if (Head == nullptr && Tail == nullptr)return;
	if (Head == Tail)
	{
		delete Head;
		Head = Tail = nullptr;
		size--;
		return;
	}
	Head = Head->pNext;
	delete Head->pPrev;
	Head->pPrev = nullptr;
	size--;
}
template<typename T>
void List<T>::pop_back()
{


	if (Head == Tail)return pop_front();
	Tail = Tail->pPrev;
	delete Tail->pNext;
	Tail->pNext = nullptr;
	Head = nullptr;
	size--;
}
template<typename T>
void List<T>::erase(int index)
{
	if (Head == nullptr || Tail == nullptr) return;
	if (index == 0)return pop_front();

	Element* Temp = Head;
	for (int i = 0; i < index; i++)
	{
		Temp = Temp->pNext;
	}

	Element* Prev = Temp->pPrev;
	Element* Next = Temp->pNext;

	Prev->pNext = Next;
	Next->pPrev = Prev;

	delete Temp;
	Temp = nullptr;
	size--;
}
 //#define BASE_CHECK
#define RANGE_BASED_FOR_LIST

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK

	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
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
	list.revers_print();
	//cout << "Введите индекс удаляемого элемента:";
	//cin >> index;
	//list.erase(index);
	//list.print();
	//list.revers_print();

#endif // BASE_CHECK

#ifdef RANGE_BASED_FOR_LIST
		
	List<int> list = { 3,5,8,13,21 };
	list.print();
	cout << endl;
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;

	/*for (List::ConstIterator it = list.cbegin(); it != list.cend(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;*/
	//for (List<int>::ReverseIterator it = list.rbegin(); it; ++it)
	//{
	//	cout << *it << tab;
	//}
	//cout << endl;

	for (List<int>::ConstReverseIterator it = list.crbegin(); it; ++it)
	{
		cout << *it << tab;
	}
	cout << endl;	
#endif // RANGE_BASED_FOR_LIST

	List<double> d_list = { 2.5,3.14,5.2,8.3 };
	for (double i : d_list)cout << i << tab;
	cout << endl;
for(List<double>::ReverseIterator it=d_list.rbegin();it;++it)
   {
	cout << *it << tab;
   }
   cout << endl;
   List<string>s_list = { "Have","a","nice","day" };
   for (std::string i : s_list)cout << i << tab; cout << endl;
   for (List<std::string>::ReverseIterator it = s_list.rbegin(); it != s_list.rend(); ++it)
   {
	   cout << *it << tab;
   }
   cout << endl;
}
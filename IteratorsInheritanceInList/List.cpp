#include"List.h"



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
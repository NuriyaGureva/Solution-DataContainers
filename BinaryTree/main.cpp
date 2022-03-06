#include<iostream>
using namespace std;

class Tree
{	
protected:
	class Element
	{	
		int Data;
		Element* pLeft;
		Element* pRight;	
		
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRighit = nullptr) :Data(Data), pLeft(pLeft), pRight(pRighit)
		{
			cout << " EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDecstructor:\t" << this << endl;
						
		}
		bool is_leaf()const
		{
			return pLeft == pRight;
		}
		friend class Tree;
		friend class  UnigueTree;
	}*Root;

public:
	
	Element* getRoot()
	{
		return Root;
	}
public:
	Tree()
	{
		
		this->Root = nullptr;
		cout << "TConstructor:\t" << this << endl;
	}
	Tree(const std::initializer_list<int>& il) :Tree()
	{
		for (int const* it = il.begin(); it != il.end(); it++)
		{
		insert(*it, Root);
		}
	}
	Tree(const Tree& other):Tree()
	{		
		copy( other.Root);
		cout << "CopyConstructor:\t" << this << endl;
	}
	Tree(Tree&& other):Tree()
	{		
		/*this->Root=other.Root;
		this->Root->pLeft = other.Root->pLeft;
		this->Root->pRight = other.Root->pRight;*/
		move(other.Root);
		cout << "MoveConstructor:\t" << this << endl;
		
	}
	~Tree()
	{
		clear();
		cout << "TDestructor:\t" << this << endl;		
		
	}

	Tree& operator=(Tree&& other)
	{
		if (this == &other)return *this;
		delete this->Root;	
		this->Root = other.Root->pLeft;
		this->Root = other.Root->pLeft;		
		other.Root = nullptr;
		cout << " MoveAssignment;\t" << this << endl;
		return *this;
	}
	void insert(int Data)
	{
		insert(Data, Root);
	}
	void erase(int Data)
	{
		erase(Data, Root);
	   
	}
	void clear()
	{
		clear(Root);
		Root = nullptr;
	}
	
	int minValue()const
	{
		return minValue(Root);
	}
	int maxValue()const
	{
		return maxValue(Root);
	}
	void print()const
	{
		print(Root);
		cout << endl;
	}
	int size()const
	{
		return size(Root);
	}
	int sum()const
	{
		return sum(Root);
	}
	double avg()const
	{
	  return avg(Root);
	}

private:

	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr) 
		{
			this->Root = new Element(Data);
			return;
		}
		if (Root == nullptr)return;
		if (Data < Root->Data )		
		{
			if (Root->pLeft == nullptr) Root->pLeft = new Element(Data);
		    else  insert(Data, Root->pLeft);					
			
		}
		if (Data > Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
	void erase(int Data, Element*& Root)
	{
		if (Root == nullptr) return;
		erase(Data, Root->pLeft);
		erase(Data, Root->pRight);

		if (Data == Root->Data)
		{
			if (Root->is_leaf())
			{
				delete Root;
				Root = nullptr;
			}
			else
			{
				if (size(Root->pLeft) > size(Root->pRight))
				{
					Root->Data = maxValue(Root->pLeft);
					erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else
				{
					Root->Data = minValue(Root->pRight);
					erase(minValue(Root->pRight), Root->pRight);
				}
			}
		}		
	}

	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << "\t";
		print(Root->pRight);
		
	}
	void clear(Element* Root)
	{
		if (Root == nullptr)return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete (Root);
	}
	void copy(Element* Root)
	{
		if (Root == nullptr)return;
		insert(Root->Data, this->Root);
		copy(Root->pLeft);
		copy(Root->pRight);
	
	}
	//void move(Element*Root)
	//{
	//	if (Root==nullptr)return;
	//	this->Root=Root;
	//	move(Root->pLeft);
	//	move(Root->pRight);
	//}
	int minValue(Element* Root)const
	{
		if (Root == nullptr)return 0;
	/*	if (Root->pLeft == nullptr)
		{
			return Root->Data;
		}
		else
		{
			return minValue(Root->pLeft);
		}
		return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);*/
		return Root->pLeft ? minValue(Root->pLeft):Root->Data;
    }
	int maxValue(Element* Root)const
	{
		if (Root == nullptr)return 0;
	/*	if (Root->pRight == nullptr)
		{
			return Root->Data;
		}
		else
		{
			return maxValue(Root->pRight);
		}*/
		return Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}
	int size(Element* Root)const
	{
		//if (Root == nullptr)return 0;
		//return size(Root->pLeft) + size(Root->pRight)+1;
		return Root == nullptr ?0 : size(Root->pLeft) + size(Root->pRight) + 1;
	}
	int sum(Element* Root)const
	{
		//if (Root ==nullptr)return 0;		
		//return Root->Data + sum(Root->pLeft) +sum(Root->pRight);
		return !Root ?0 : sum(Root->pLeft) + sum(Root->pRight)+ Root->Data;
	}
	double avg(Element*Root)const
	{	
		return sum(Root) / size(Root);
	}


};
class UnigueTree :public Tree
{
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)
		{
			this->Root = new Element(Data);
			return;
		}
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else if (Data > Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
public:
	void insert(int Data)
	{
		insert(Data, this->Root);
	}
};

//#define BASE_CHECK

void main()
{
	
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK	
	int n;
	cout << " Введите размер дерева:"; cin >> n;
	//UnigueTree tree;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	//tree.clear();

	cout << endl;
	cout << " Минимальное значение в дереве: " << tree.minValue() << endl;
	cout << " Максимальное значение в дереве: " << tree.maxValue() << endl;
	cout << " Количество элементов в дереве:" << tree.size() << endl;
	cout << " Сумма элементов дерева:" << tree.sum() << endl;
	cout << " Среднее арифметическое значение дерева:" << tree.avg() << endl;
	//tree.erase();
	//tree.print();
	

#endif // BASE_CHECK

	Tree tree = { 50,25,75,16,32,65,80,27,35};
	tree.print();
	/*Tree tree2 = tree;
	tree2.print();*/
	int value;
	cout << "Введите значение удаляемого элемента :"; cin>>value;
	tree.erase(value);
	tree.print();
  
		
	
}
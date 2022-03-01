#include<iostream>
using namespace std;

class Tree
{
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft=nullptr, Element* pRighit=nullptr) :Data(Data), pLeft(pLeft), pRight(pRighit)
		{
			cout << " EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDecstructor:\t" << this << endl;
		}
		friend class Tree;
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
	~Tree()
	{
		cout << "TDestuctor:\t" << this << endl;
	}

	void insert(int Data, Element* Root)
	{
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);	
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight= new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << " ¬ведите размер дерева:"; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100, tree.getRoot());
	}




}
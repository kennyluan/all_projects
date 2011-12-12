#pragma once

#include <limits>
#include <iostream>
#include <vector>

using namespace std;

class MyStack
{
public:
	void StackPush( int data );
    int  StackPop();
	bool StackIsEmpty();
	bool InitStack( int nLevel );
	MyStack( int nlevel = DEFAULT_STACK_SIZE );
	~MyStack();
	bool IsFull(){return nTop == ( DEFAULT_STACK_SIZE - 1 );}
	bool IsEmpty() { return nTop < 0; }
	void DumpStack() { while( !IsEmpty() ) { cout<<StackPop()<<endl; } }
private:
	enum { DEFAULT_STACK_SIZE = 100 };
	int nTop;
	int *pStackHead;
};

class SetofStack
{
private:
	vector< MyStack *> stackSet;
public:
	MyStack *GetLastStack();
	void Push(int data);
	int Pop();
};

class Tower
{
public:
	MyStack *pDisks;
	int nIndex;
	Tower( int nLevel, int Index );
	void MoveTopTo( Tower *pTower );
	void MoveDisks( int n, Tower *pDestination, Tower *pBuffer, Tower *pFrom );
};

void RunHanoi( int nLevel );
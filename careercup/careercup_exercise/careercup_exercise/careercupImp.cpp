#include "stdafx.h"

#include "careercup_exercise.h"

MyStack::MyStack( int nLevel )
{
	pStackHead = NULL;
	nTop = -1;
	if( !InitStack( nLevel ) )
	{
		exit(1);
	}
}

bool MyStack::InitStack( int nLevel )
{
	pStackHead = new int[nLevel];
	if( !pStackHead )
	{
		return false;
	}
	return true;
}

void MyStack::StackPush( int data )
{
	if( !IsFull() )
	{
		pStackHead[++nTop] = data;
	}
}

int MyStack::StackPop()
{
	if( !IsEmpty() )
	{
		return pStackHead[nTop--];
	}
	return std::numeric_limits<int>::max();
}

MyStack::~MyStack()
{
	delete []pStackHead;
	nTop = -1;
}

MyStack *SetofStack::GetLastStack()
{
	int nLastStack = stackSet.size();
	if( 0 == nLastStack )
	{
		return NULL;
	}
	else
	{
		return stackSet.at( nLastStack );
	}
}

void SetofStack::Push(int data)
{
	MyStack *pStack = GetLastStack();
	if( NULL != pStack && !pStack->IsFull () )
	{
		pStack->StackPush ( data );
	}
	else
	{
		pStack = new MyStack();
		pStack->StackPush ( data );
		stackSet.push_back( pStack );
	}
}

Tower::Tower(int nLevel, int Index)
{
	pDisks = new MyStack( nLevel );
	nIndex = Index;
}

void Tower::MoveTopTo(Tower *pTower)
{
	int nTop = pDisks->StackPop ();
	pTower->pDisks ->StackPush ( nTop );
	cout << "Moved "<< nTop << " From tower "<< nIndex << " To "<<pTower->nIndex <<endl;
}

void Tower::MoveDisks(int n, Tower *pDestination, Tower *pBuffer, Tower *pFrom)
{
	if( n > 0 )
	{
		MoveDisks( n - 1, pBuffer, pDestination, pFrom );
		pFrom->MoveTopTo( pDestination );
		MoveDisks( n - 1, pDestination, this, pBuffer );
	}
}


void RunHanoi( int nLevel )
{
	Tower *towers[3] = { NULL };
    int i;
	for( i = 0; i < 3; i++ )
	{
		towers[i] = new Tower( nLevel, i );
	}
	for( i = ( nLevel -1 ) ; i >= 0; i-- )
	{
		towers[0]->pDisks ->StackPush ( i );
	}
	towers[0]->MoveDisks ( nLevel, towers[2], towers[1], towers[0] );
}
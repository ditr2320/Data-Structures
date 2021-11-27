#include <iostream>
#include <fstream>
#include "MovieTree.hpp"

using namespace std;

LLMovieNode* getLLMovieNode(int r, std::string t, int y, float q)
{
	LLMovieNode* lmn =new LLMovieNode();
	lmn->ranking = r;
	lmn->title=t;
	lmn->year =y;
	lmn->rating =q;
	lmn->next =NULL;
	return lmn;
}

/* ------------------------------------------------------ */
MovieTree::MovieTree()
{
	root = NULL;
}

void _deconstructor(TreeNode* T)
{
	if(T == NULL)
	{
		return; 
	}
	if(T->head != NULL)
	{
		LLMovieNode* curr = T->head; 
		LLMovieNode* prev = NULL; 
		while(curr != NULL)
		{
			prev = curr; 
			curr = curr -> next; 
			delete prev; 
		}
	}
	_deconstructor(T->leftChild); 
	_deconstructor(T->rightChild); 
	delete T; 
	T = 0; 
}

MovieTree::~MovieTree()
{
	_deconstructor(root); 
}

/* ------------------------------------------------------ */
void inorderTraversalHelper(TreeNode * root) {
		if (root == NULL) {
			return;
		}
		inorderTraversalHelper(root->leftChild);
		cout << root->titleChar << " ";
		inorderTraversalHelper(root->rightChild);
}

void MovieTree::inorderTraversal() {
	inorderTraversalHelper(root);
	cout << endl;
}

/* ------------------------------------------------------ */
TreeNode* searchCharHelper(TreeNode* curr, char key)
{
    if (curr == NULL)
        return curr;
    else if(curr->titleChar == key)
        return curr;
    else if (curr->titleChar > key)
        return searchCharHelper(curr->leftChild, key);
    else
        return searchCharHelper(curr->rightChild, key);
}

TreeNode* MovieTree::searchCharNode(char key)
{
    return searchCharHelper(root, key);
}

/* ------------------------------------------------------ */


void _showMovieCollection(TreeNode* T)
{
	if(T == NULL)
	{
		return; 
	}
	LLMovieNode* crawler = T->head; 
	_showMovieCollection(T->leftChild); 
	if(crawler != NULL)
	{
		cout << "Movies starting with letter: " << T->titleChar << endl; 
	}
	while(crawler != NULL)
	{
	cout << " >> " << crawler->title << " " << crawler->rating << endl;
	crawler = crawler -> next; 
	}
	_showMovieCollection(T->rightChild); 
	return; 
}

void MovieTree::showMovieCollection()
{
	_showMovieCollection(root); 
	return; 
}


void _insertNode(TreeNode* &T, LLMovieNode* m)
{ 
  if(T == 0) //base case 
  {
    T = new TreeNode(); 
	T -> head = m; 
    T -> leftChild = NULL; 
    T -> rightChild = NULL; 
	T -> titleChar = m->title[0]; 
    return; 
  }
  if(m->title[0] < T -> titleChar)
  {
    _insertNode(T->leftChild, m); 
	T->leftChild->parent = T; 
  }
  else if(m->title[0] > T -> titleChar)
  {
    _insertNode(T->rightChild,m); 
	T->rightChild->parent = T; 
  }
  return; 
}

void _insertMovie(TreeNode* &T, LLMovieNode* m) 
{
	if(T == NULL) // empty tree 
	{
		T= new TreeNode(); 
		T->head = m; 
		T->leftChild = NULL; 
		T->rightChild = NULL; 
		T->parent = NULL; 
		T->titleChar = m->title[0]; 
		return; 
	}
	if(searchCharHelper(T, m->title[0]) == NULL) //Node with letter does not exist 
	{
		_insertNode(T, m); 
		return; 	
	}
	TreeNode* M = searchCharHelper(T, m->title[0]);
	LLMovieNode* curr = M->head; 
	LLMovieNode* prev = NULL; 
	while(curr!= NULL && (curr->title < m->title)) 
	{
		prev = curr; 
		curr = curr -> next; 
	}
	if(prev == NULL) //inserting as first 
	{
		m -> next = M-> head; 
		M-> head = m; 
	}
	else // inserting else where
	{
		prev -> next = m; 
		m -> next = curr; 
	}
}

void MovieTree::insertMovie(int ranking, string title, int year, float rating)
{
	LLMovieNode* m  = getLLMovieNode(ranking, title, year, rating); 
	_insertMovie(root, m); 
}


void _remove(TreeNode*T, string title)
{
	if(T == NULL) 
	{
		cout << "Movie not found."<< endl;
		return; 
	} 
	if(title[0] > T->titleChar)
	{
		_remove(T->rightChild,title); 
	}
	else if(title[0] < T-> titleChar)
	{
		_remove(T->leftChild,title); 
	}
	else if(title[0] == T->titleChar)
	{
		LLMovieNode* curr = T->head; 
		LLMovieNode* prev = NULL; 
		while(curr!= NULL && (curr->title != title)) 
		{
			prev = curr; 
			curr = curr -> next; 
		}
		if(curr == NULL)
		{
			cout << "Movie not found."<< endl;
		}
		if(prev == NULL) // deleting first 
		{
			T->head = curr-> next; 
			delete curr; 
		}
		else
		{
			prev -> next = curr -> next; 
			delete curr; 
		}
		
	}
}

void MovieTree:: removeMovieRecord(std::string title)
{
	_remove(root, title); 
}


void MovieTree::leftRotation(TreeNode* curr)
{  
	TreeNode* X = curr;
    TreeNode* Y = curr -> rightChild;
	X -> rightChild = Y -> leftChild;
	Y -> parent = X -> parent;
    if( Y -> leftChild != NULL)
    {
        Y -> leftChild->parent = X -> parent;
    }
    if(X -> parent == NULL)
    {
        root = Y;
    }
    else if (X == X -> parent -> rightChild)
    {
        X -> parent -> rightChild = Y;
    }
    else
    {
        X -> parent -> leftChild = Y;
    }
    Y -> leftChild = X;
    X -> parent = Y;
}
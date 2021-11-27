#include "MovieTree.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// Helper function: Create new node using provided args
MovieNode* getMovieNode(int rank, string t, int y, float r) {
    MovieNode* nn = new MovieNode;
    nn->title = t;
    nn->ranking = rank;
    nn->year = y;
    nn->rating = r;
    return nn;
}

MovieTree::MovieTree() {
  //write your code
  root = NULL; 
}

void deconstruct(MovieNode* M)
{
  if(M == NULL) return; 
  deconstruct(M -> left); 
  deconstruct(M -> right); 
  delete M; 
  M = 0; 
}

MovieTree::~MovieTree() {
  //write your code
  deconstruct(root); 
}

void print(MovieNode* M) 
{
  if(M == NULL)
  {
    return;    
  }
  print(M->left);
  cout << "Movie: " << M->title << " (" << M->rating << ")" << endl;
  print(M->right); 
  return;
}

void MovieTree::printMovieInventory() {
   //write your code
   if(root == NULL)
   {
     cout << "Tree is empty. Cannot print." << endl; 
     return; 
   }
   print(root); 
}

void insert(MovieNode* &M, int ranking, string title, int year, float rating)
{
  if(M == NULL)
  {
    M = new MovieNode(); 
    M -> ranking = ranking; 
    M -> title = title; 
    M -> year = year; 
    M -> rating = rating; 
    M -> right = 0; 
    M -> left = 0; 
    return; 
  }
  if((M->title).compare(title) > 0) 
  {
    insert(M->left, ranking, title, year, rating); 
  }
  else
  {
    insert(M->right, ranking,title,year,rating); 
  }
  return; 
}

void MovieTree::addMovieNode(int ranking, string title, int year, float rating) {
  //write your code
  insert(root, ranking, title, year, rating); 
}

MovieNode* search(string title, MovieNode* N)
{
  if(N == NULL) return 0; 
  if(N-> title == title) return N; 
  if(N->title.compare(title) > 0) 
  {
    return search(title,N->left); 
  }
  else
  {
    return search(title,N->right); 
  }
  return 0; 
}

void MovieTree::findMovie(string title) {
  //write your code
  MovieNode* S = search(title, root); 
  if(S == 0)
  {
    cout << "Movie not found." << endl; 
    return; 
  }
cout << "Movie Info:" << endl;
cout << "==================" << endl;
cout << "Ranking:" << S->ranking << endl; 
cout << "Title  :" << S->title << endl; 
cout << "Year   :" << S->year << endl; 
cout << "Rating :" << S->rating << endl;
}

void query(float rating, int year, MovieNode* M)
{
  if(M == NULL)
  {
    return; 
  }
  if(M->year > year && M->rating >= rating)
  {
    cout << M->title << " (" << M->year << ") " << M->rating << endl;
    query(rating, year,M->left); 
    query(rating, year,M->right); 
  }
  else
  {
    query(rating, year,M->left); 
    query(rating, year,M->right); 
  }
}

void MovieTree::queryMovies(float rating, int year) {
  //write your code
  if(root == NULL)
  {
    cout << "Tree is Empty. Cannot query Movies." << endl;
  }
  cout << "Movies that came out after " << year << " with rating at least " << rating << ":" << endl;
  query(rating,year,root); 
}

float sum(MovieNode* M)
{
  if(M == NULL)
  {
    return 0; 
  }
  return (M->rating + sum(M->left)+ sum(M->right)); 
}
float numMovies(MovieNode*M)
{
  int n = 1; 
  if(M == NULL)
  {
    return n; 
  }
  if(M-> right != NULL) n = n + numMovies(M->right); 
  if(M-> left != NULL) n = n + numMovies(M->left); 
  return n; 
}

void MovieTree::averageRating() {
  //write your code
  if(root == NULL)
  {
    cout << "Average rating:0.0" << endl;
    return; 
  }
  float summation = sum(root); 
  float totalNum = numMovies(root);  
  float average = summation/totalNum; 
  cout << "Average rating:" << average << endl;
}

void levelPrint(int level, MovieNode* M)
{
  if(M == NULL) 
  {
    return; 
  }
  if(level == 0)
  {
    cout << "Movie: " << M->title << " (" << M ->rating << ")" << endl;
  }
  level--; 
  levelPrint(level, M->left); 
  levelPrint(level, M->right); 
}

void MovieTree::printLevelNodes(int level) {
  //write your code
  levelPrint(level, root); 
}

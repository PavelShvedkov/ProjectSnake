#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <fstream>
#include "ctime"

typedef int(*Comparer)(int, int);
typedef bool(*Filter)(int);

class Array
{
public:
	Array(int);
	Array(const int*, int);
	Array(int[], int);
	Array(Array&);
	~Array();

	inline	int getLength()const;
	//int* getArray()const окнун
	//{
	//	return array;
	//}
	void setItem(int, int);
	int getItem(int);

	void display()const;
	void sort();
	void sort(Comparer);
	void mergeSort(Array&, Comparer);
	void quickSort(Array&,int,int,Comparer);
	void inverted();
	void randomFilling(int);
	void shuffle();
	void shift(int,bool);
	void writeBinFile(const char*);
	void readBinFile(const char*);
	void deleteRepits();
	void deleteElement(int);
	int counter(int, Comparer)const;
	void selection(Array&, Filter)const;
	void search(Array&, Filter);
	void screening(Filter);


	int& operator [](int);
	const int& operator [](int)const;
	Array& operator =(Array&);
	bool operator ==(Array&);
	bool operator !=(Array&);

private:
	int* array;
	int length;
	static void swap(int&, int&);
	inline void setLength(int);
};


#endif  ARRAY_H// !ARRAY_H
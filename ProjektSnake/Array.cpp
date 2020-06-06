#include "Array.h"
#include <ctime>

using namespace std;

Array::Array(int length)
{
	setLength(length);

	int n = getLength();

	array = new int[n];

	for (int i = 0; i < n; i++)
	{
		array[i] = 0;
	}
}
Array::Array(const int* source, int lenght)
{
	if (length < 0)
	{
		throw std::invalid_argument(" Length must be positive");
	}
	if (source == 0 && length != 0)
	{
		throw std::invalid_argument(" Cannot create an empty array of length greater than zero");
	}

	setLength(length);

	int n = getLength();

	array = new int[n];

	for (int i = 0; i < n; i++)
	{
		array[i] = source[i];
	}
}
Array::Array(int source[], int length)
{
	if (length < 0)
	{
		throw std::invalid_argument(" Length must be positive");
	}
	if (source == 0 && length != 0)
	{
		throw std::invalid_argument(" Cannot create an empty array of length greater than zero");
	}

	setLength(length);

	int n = getLength();

	array = new int[n];

	for (int i = 0; i < n; i++)
	{
		array[i] = source[i];
	}
}
Array::Array(Array& other)
{
	this->setLength(other.getLength());

	array = new int[getLength()];

	for (int i = 0; i < getLength(); i++)
	{
		array[i] = other[i];
	}
}
Array::~Array()
{
	delete[]array;
	setLength(0);
	//cout << " Memory is clean" << endl;
}

int Array::getLength() const
{
	return length;
}
void Array::setLength(int length)
{
	if (length < 0)
	{
		throw std::invalid_argument(" Length must be positive");
	}

	this->length = length;
}
void Array::setItem(int index, int value)
{
	if (index < 0 || index >= getLength())
	{
		throw std::out_of_range(" Out of range");
	}

	array[index] = value;
}
int Array::getItem(int index)
{
	if (index < 0 || index >= getLength())
	{
		throw std::out_of_range(" Out of range");
	}

	return array[index];
}

void Array::display() const
{
	for (int i = 0; i < getLength(); i++)
	{
		cout << array[i] << '\t';
	}
}
void Array::sort()
{
	bool isSorted = false;
	int i = 0;

	while (!isSorted)
	{
		isSorted = true;
		for (int j = getLength() - 1; j > i; j--)
		{
			if (array[j] < array[j - 1])
			{
				swap(array[j], array[j - 1]);
				isSorted = false;
			}
		}
		i++;
	}
}
void Array::sort(Comparer comparer)
{
	bool isSorted = false;
	int i = 0;

	while (!isSorted)
	{
		isSorted = true;
		for (int j = getLength() - 1; j > i; j--)
		{
			if (comparer(array[j], array[j - 1]) > 0)
			{
				swap(array[j], array[j - 1]);
				isSorted = false;
			}
		}
		i++;
	}
}
void Array::mergeSort(Array& key, Comparer comparator)
{
	int length = this->getLength();

	if (length != key.getLength())
	{
		throw std::invalid_argument(" Keys do not match array!");
	}

	int mid = length / 2, h = 1;

	if (length % 2 == 1)
	{
		mid++;
	}

	Array buffer = *this;
	Array sourcesBuffer(length);
	Array keysBuffer(length);
	int step;

	while (h < length)
	{
		step = h;
		int i = 0;
		int j = mid;
		int k = 0;
		while (step <= mid)
		{
			while ((i < step) && (j < length) && (j < (mid + step)))
			{
				if (comparator(key[i], key[j]) > 0)
				{
					keysBuffer[k] = key[i];
					sourcesBuffer[k] = buffer[i];
					i++;
					k++;
				}
				else
				{
					keysBuffer[k] = key[j];
					sourcesBuffer[k] = buffer[j];
					j++;
					k++;
				}
			}
			while (i < step)
			{
				keysBuffer[k] = key[i];
				sourcesBuffer[k] = buffer[i];
				i++;
				k++;
			}
			while ((j < (mid + step)) && (j < length))
			{
				keysBuffer[k] = key[j];
				sourcesBuffer[k] = buffer[j];
				j++;
				k++;
			}

			step = step + h;
		}

		h = h * 2;

		for (i = 0; i < length; i++)
		{
			key[i] = keysBuffer[i];
			buffer[i] = sourcesBuffer[i];
		}
	}

	*this = buffer;
}
void Array::quickSort(Array& key, int first, int last, Comparer comparator)
{
	if (this->getLength() != key.getLength())
	{
		throw std::invalid_argument(" Keys do not match array!");
	}

	Array buffer = *this;
	int f = first, l = last, mid = key[(f + l) / 2];

	do
	{
		while (comparator(key[f], mid) > 0)
		{
			++f;
		}
		while (comparator(mid, key[l]) > 0)
		{
			--l;
		}

		if (f <= l)
		{
			swap(key[f], key[l]);
			swap(buffer[f], buffer[l]);
			++f;
			--l;
		}
	} while (f < l);

	*this = buffer;

	if (first < l)
	{
		this->quickSort(key, first, l, comparator);
	}
	if (f < last)
	{
		this->quickSort(key, f, last, comparator);
	}
}
void Array::inverted()
{
	int n = getLength();

	for (int i = 0; i < getLength() / 2; i++, n--)
	{
		swap(array[i], array[n - 1]);
	}
}
void Array::randomFilling(int limit)
{
	srand(time(NULL));

	for (int i = 0; i < getLength(); i++)
	{
		setItem(i, (rand() % limit / 2) * pow(-1, rand() % 2));
	}
}
void Array::shuffle()
{
	int shuffles = getLength();

	for (int index1 = 0, index2 = 0, i = 0; i <= shuffles; i++)
	{
		index1 = ((rand() / rand()) % shuffles + ((rand() * 22) / 9)) % shuffles;
		index2 = ((rand() / rand()) % shuffles + ((rand() * 22) / 9)) % shuffles;
		swap(array[index1], array[index2]);
	}

}
void Array::shift(int steps, bool direction)
{
	int length = getLength();

	if (direction)
	{
		for (int i = 0; i < steps; i++)
		{
			int temp = this->array[length - 1];

			for (int j = length; j > 0; j--)
			{
				this->array[j] = this->array[j - 1];
			}

			this->array[0] = temp;
		}
	}
	else
	{
		for (int i = 0; i < steps; i++)
		{
			int temp = this->array[0];

			for (int j = 0; j < length; j++)
			{
				this->array[j] = this->array[j + 1];
			}

			this->array[length - 1] = temp;
		}
	}
}
void Array::writeBinFile(const char* path)
{
	ofstream out(path, ios::binary);
	int length = this->getLength();
	Array buffer = *this;

	if (!out.is_open())
	{
		cout << "Cannot open file to read!" << endl;
		system("pause");
		exit(1);
	}

	out.write((char*)&length, sizeof(int));

	for (int i = 0; i < length; ++i)
	{
		out.write((char*)&buffer[i], sizeof(int));
	}

	out.close();
}
void Array::readBinFile(const char* path)
{
	ifstream in(path, ios::binary);
	int lengthDest = 0;

	if (!in.is_open())
	{
		cout << "Cannot open file to read!" << endl;
		system("pause");
		exit(1);
	}

	in.read((char*)&lengthDest, sizeof(int));

	Array buffer(lengthDest);

	for (int i = 0; i < lengthDest; ++i)
	{
		in.read((char*)&buffer[i], sizeof(buffer[i]));
	}

	in.close();

	*this = buffer;
}
void Array::deleteRepits()
{
	for (int i = 0, k = 0; i < this->getLength(); ++i)
	{
		for (int j = i + 1; j < this->getLength(); ++j)
		{
			if (this->getItem(i) == this->getItem(j))
			{
				this->deleteElement(j);
			}
		}
	}
}
void Array::deleteElement(int index)
{
	int length = this->getLength();

	if (index >= length)
	{
		throw std::invalid_argument(" Index can't be more than source length !");
	}

	if (index < 0)
	{
		throw std::invalid_argument(" Index can't be less than zero length !");
	}

	Array buffer(length - 1);

	for (int i = 0, j = 0; i < length; ++i)
	{
		if (i == index)
		{
			continue;
		}

		buffer[j] = this->getItem(i);
		++j;
	}

	*this = buffer;

	system("cls");
}

int Array::counter(int pattern, Comparer comparer) const
{
	int counter = 0;

	for (int i = 0; i < getLength(); i++)
	{
		if (comparer(array[i], pattern))
		{
			counter++;
		}
	}
	return counter;
}
void Array::selection(Array& destination, Filter filter) const
{
	int length = getLength(), newLength = 0;
	Array buffer(length);

	for (int i = 0; i < length; i++)
	{
		if (filter(array[i]))
		{
			buffer[newLength] = array[i];
			++newLength;
		}
	}

	Array buffer2(newLength);

	for (int i = 0; i < newLength; ++i)
	{
		buffer2[i] = buffer[i];
	}

	destination = buffer2;
}
void Array::search(Array& indexArray, Filter filter)
{
	int length = getLength(), newLength = 0;
	Array buffer(length);

	for (int i = 0; i < length; i++)
	{
		if (filter(array[i]))
		{
			buffer[newLength] = i;
			++newLength;
		}
	}

	Array buffer2(newLength);

	for (int i = 0; i < newLength; ++i)
	{
		buffer2[i] = buffer[i];
	}

	indexArray = buffer2;
}
void Array::screening(Filter filter)
{
	int sourceLength = this->getLength(), newLength = 0;
	Array buffer(sourceLength);

	for (int i = 0, j = 0; i < sourceLength; ++i)
	{
		if (!filter(this->getItem(i)))
		{
			buffer[newLength] = this->getItem(i);
			++newLength;
		}
	}

	Array buffer2(newLength);

	for (int i = 0; i < newLength; i++)
	{
		buffer2[i] = buffer[i];
	}

	*this = buffer2;

	system("cls");
}


void Array::swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}


int& Array::operator[](const int index)
{
	if (index < 0 || index >= getLength())
	{
		throw std::out_of_range(" Out of range");
	}

	return array[index];
}
const int& Array::operator[](int index)const
{
	if (index < 0 || index >= getLength())
	{
		throw std::out_of_range(" Out of range");
	}

	return array[index];
}
bool Array::operator==(Array& rho)
{
	if (this->getLength() != rho.getLength())
	{
		return false;
	}

	for (int i = 0; i < this->getLength(); i++)
	{
		if (this->array[i] != rho[i])
		{
			return false;
		}
	}

	return true;
}
bool Array::operator !=(Array& rho)
{
	return !(*this == rho);
}

Array& Array:: operator=(Array& rho)
{
	int newLength = rho.getLength();

	this->setLength(newLength);

	if (this->array != nullptr)
	{
		delete[] this->array;
	}

	this->array = new int[newLength];

	for (int i = 0; i < newLength; i++)
	{
		this->setItem(i, rho.getItem(i));
	}

	return *this;
}




//void readTxtFile(const char* path, Array& destination)
//{
//	ifstream in(path);
//	int sizeObj = sizeof(Array);
//	int sizeMaxElement = 100;
//
//	if (!in.is_open())
//	{
//		cout << "Cannot open file to read!" << endl;
//		system("pause");
//		exit(1);
//	}
//
//	char* buffer = new char[sizeMaxElement] {0};
//	int buff = 0;
//	for (int i = 0; i < sizeMaxElement; i++)
//	{
//		buffer[i] = 0;
//	}
//	while (!in.eof())
//	{
//
//	}
//	//in.destination, sizeObj);
//
//	in.close();
//}//------
//void stringToArray(char* source, Array& destination)
//{
//	int sourceLength = strlen(source), newLength = 0, bufferNumber = 0;
//	char* buffer1 = new char[sourceLength];
//	char* buffer2 = new char[sourceLength];
//	char* space = strchr(source, ' ');
//	Array bufferArray(sourceLength);
//
//	strcpy(buffer2, source);
//
//	for (int i = 0; space; ++i, ++newLength)
//	{
//		space = strchr(buffer2, ' ');
//
//		if (!space)
//		{
//			strcpy(buffer1, buffer2);
//		}
//		else
//		{
//			strncpy(buffer1, buffer2, space - buffer2);
//			strcpy(buffer2, space + 1);
//		}
//
//		bufferNumber = atoi(buffer1);
//		bufferArray[i] = bufferNumber;
//
//		delete[]buffer1;
//		buffer1 = new char[sourceLength];
//	}
//
//	Array bufferArray2(newLength);
//
//	for (int i = 0; i < newLength; ++i)
//	{
//		bufferArray2[i] = bufferArray[i];
//	}
//
//	destination = bufferArray2;
//
//	delete[]buffer1;
//	//delete[]buffer2;
//	delete space;
//}


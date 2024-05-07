#include "Matrix.h"
#include <exception>
#include <cstring>
#include <iostream>
using namespace std;


Matrix::Matrix(int nrLines, int nrCols) {
	  
	columnAmount = nrCols;
	elemCapacity = 100;
	elemAmount = 0;
	elements = new TElem[elemCapacity];
	columns = new int[elemCapacity];

	rowAmount = nrLines;
	rows = new int[rowAmount + 1];

	for (int i = 0; i <= rowAmount; i++)
	{
		rows[i] = 0;
	}
}


int Matrix::nrLines() const {
	// Complexity:
	// O(1)
	return rowAmount;
}


int Matrix::nrColumns() const {
	// Complexity:
	// O(1)
	return columnAmount;
}


TElem Matrix::element(int i, int j) const {

	// Complexity:
	// 
	// O(n)
	// Average: Theta(n)
	// Worst: Theta(n)
	// Best: Theta(1) if the list is empty or if it is the first element on the row

	// check if index is valid
	if (i < 0 || i >= rowAmount || j < 0 || j >= columnAmount)
		throw exception("index out of range");


	// don't bother if there are no elements in matrix
	if (elemAmount == 0)
		return NULL_TELEM;


	// iterate through elements on this row
	for (int k = rows[i]; k < rows[i + 1]; k++)
		if (columns[k] == j)
			return elements[k];

	return NULL_TELEM;
}

TElem Matrix::modify(int i, int j, TElem e) {

	// Complexity:
	// 
	// O(n)
	// Average: Theta(n)
	// Worst: Theta(n)
	// Best: Theta(1) if the list is empty, or if the current row is empty and it falls into any of the cases from line 130 to 139

	// check if index is valid
	if (i < 0 || i >= rowAmount || j < 0 || j >= columnAmount)
		throw exception("index out of range");

	TElem returnValue = NULL_TELEM;

	// next row that isn't empty
	// -1 means unknown
	// -2 means i is the last non-empty row in the sequence
	// any positive number means that is the next row
	int nextRow = -1;

	// if row isn't empty
	if (rows[i] != elemAmount)
	{
		int next = i + 1;
		if (rows[i + 1] == elemAmount && nextRow != -2)
		{
			// look for next non-empty row
			for (int k = next; k < rowAmount; k++)
				if (rows[k] != elemAmount)
				{
					next = k;
					break;
				}

			if (next != i + 1)
				nextRow = next;
			else
				nextRow = -2;
		}

		// check if element already exists
		for (int k = rows[i]; k < rows[next]; k++)
		{
			if (columns[k] == j)
			{
				returnValue = elements[k];
				if (e == NULL_TELEM)
					remove(k);
				else
					elements[k] = e;

				return returnValue;
			}
		}
	}


	// if it hasn't returned, position is empty right now
	if (e != NULL_TELEM)
	{
		int index = 0;
		// if adding to the first row, always insert at the start of the array
		if (i == 0)
			index = 0;
		// if adding to the last row or the last non-empty row, insert at the end of the array 
		else if (i == rowAmount - 1 || nextRow == -2)
			index = elemAmount;
		// if the next row isn't empty, insert just before it
		else if (rows[i + 1] != elemAmount)
			index = rows[i + 1];
		// if a non-empty row has been found after i, insert just before that
		else if (nextRow >= 0)
			index = rows[nextRow];
		// if none of those are true,look for next non-empty row
		else
		{
			for (int k = i+1; k < rowAmount; k++)
				if (rows[k] != elemAmount)
				{
					index = rows[k];
					break;
				}

			// means all rows after it are empty
			if (index == 0)
				index = elemAmount;
		}

		// if index is below 0, it means it should be placed at the start of the array
		if (index < 0)
			index = 0;

		// insert into array
		insert(e, j, index);
		
		// if row was previously empty, update it
		if (rows[i] == elemAmount || index == 0)
			rows[i] = index;
	}

	return returnValue;

	
}

void Matrix::resize()
{
	// Complexity:
	// 
	// O(n)
	// Average: Theta(n)
	// Worst: Theta(n)
	// Best: Theta(n)

	// resize up
	if (elemAmount > elemCapacity / 2)
		elemCapacity *= 2;

	// resize down
	else if (elemAmount < elemCapacity / 4)
		elemCapacity /= 2;
	
	// if no need for resize, don't resize
	else return;

	// keep old elems
	TElem* oldElems = elements;
	int* oldColumns = columns;

	// create new vectors
	elements = new TElem[elemCapacity];
	columns = new int[elemCapacity];

	// about 3x faster than for loop in testing
	// only for primitive types though
	memcpy(elements, oldElems, elemAmount * sizeof(TElem));
	memcpy(columns, oldColumns, elemAmount * sizeof(int));

	delete oldElems;
	delete oldColumns;
}

void Matrix::insert(TElem elem, int column, int index)
{
	// Complexity:
	// 
	// O(n)
	// Average: Theta(n)
	// Worst: Theta(n)
	// Best: Theta(n)

	// push the elements in front forward
	memcpy(elements + index + 1, elements + index, (elemAmount - index) * sizeof(TElem));
	memcpy(columns + index + 1, columns + index, (elemAmount - index) * sizeof(int));


	// update row indexes
	for (int i = 0; i <= rowAmount; i++)
		if (rows[i] >= index || rows[i] == elemAmount)
			rows[i]++;

	// increase element amount
	elemAmount++;

	// set element
	elements[index] = elem;
	columns[index] = column;

	resize();
}

void Matrix::remove(int index)
{
	// Complexity:
	// 
	// O(n)
	// Average: Theta(n)
	// Worst: Theta(n)
	// Best: Theta(n)

	// push the elements back by 1
	memcpy(elements + index, elements + index + 1, (elemAmount - index) * sizeof(TElem));
	memcpy(columns + index, columns + index + 1, (elemAmount - index) * sizeof(int));


	// update row indexes
	for (int i = 0; i <= rowAmount; i++)
		if (rows[i] > index || rows[i] == elemAmount)
			rows[i]--;

	// increase element amount
	elemAmount--;

	// resize if needed
	resize();
}

TElem* Matrix::getRow(int row)
{
	// Complexity:
	// 
	// O(n)
	// Average: Theta(n)
	// Worst: Theta(n)
	// Best: Theta(n)

	TElem* returnValue = new TElem[nrColumns()];
	
	for (int i = 0; i < nrColumns(); i++)
		returnValue[i] = element(row, i);

	return returnValue;
}

TElem* Matrix::getColumn(int column)
{
	// Complexity:
	// 
	// O(n)
	// Average: Theta(n)
	// Worst: Theta(n)
	// Best: Theta(n)

	TElem* returnValue = new TElem[nrLines()];

	for (int i = 0; i < nrLines(); i++)
		returnValue[i] = element(i, column);

	return returnValue;
}

Matrix* Matrix::multiply(Matrix& other)
{

	// not very efficient, if i had more time i'd've implemented a better method

	// Complexity:
	// 
	// n = this.nrLines();
	// m = other.nrColumns();
	// p = this.nrColumns();
	//
	// O(n*m*p)
	// Average: Theta(n*m*p)
	// Worst: Theta(n*m*p)
	// Best: Theta(n*m*p)

	// Wikipedia: For matrix multiplication, the number of columns in the first matrix must be equal to the number of rows in the second matrix.
	if (nrColumns() != other.nrLines())
		throw exception("Matrices cannot be multiplied");

	// The resulting matrix, known as the matrix product, has the number of rows of the first and the number of columns of the second matrix.
	Matrix* result = new Matrix(nrLines(), other.nrColumns());

	for (int i = 0; i < nrLines(); i++)
	{
		TElem* row = getRow(i);
		for (int j = 0; j < other.nrColumns(); j++)
		{
			TElem* column = other.getColumn(j);
			TElem sum = NULL_TELEM;
			for (int k = 0; k < nrColumns(); k++)
				sum+=row[k]*column[k];
			result->modify(i, j, sum);
		}
	}

	return result;
}

void Matrix::print()
{
	for (int i = 0; i < nrLines(); i++)
	{
		for (int j = 0; j < nrColumns(); j++)
		{
			cout << element(i, j) << " ";
		}
		cout << endl;
	}
}

Matrix::~Matrix() {
	delete elements;
	delete columns;
	delete rows;
}



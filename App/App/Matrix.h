#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

class Matrix {

private:
	
	// elements and columns
	TElem* elements;
	int* columns;


	// same length and capacity
	int elemAmount;
	int elemCapacity;

	int columnAmount;

	// rows don't change length so they don't need capacity, length is rowAmount+1
	int* rows;
	int rowAmount;

	// resize up or down
	void resize();

	// insert element at index
	void insert(TElem elem, int column, int index);

	// remove element at index
	void remove(int index);
	

public:

	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

	// returns an array with all elements in a row, length nrColumns()
	TElem* getRow(int row);

	// returns an array with all elements in a column, length nrRows()
	TElem* getColumn(int column);

	// prints the matrix
	void print();

	// multiplies two matrices
	// tests in ShortTest
	Matrix* multiply(Matrix& other);
	
	// destructor
	~Matrix();

};

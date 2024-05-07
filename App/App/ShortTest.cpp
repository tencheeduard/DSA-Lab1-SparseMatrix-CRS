#include <assert.h>
#include "Matrix.h"
#include <iostream>

using namespace std;

void testAll() { 
	Matrix m(4, 4);
	assert(m.nrLines() == 4);
	assert(m.nrColumns() == 4);	
	m.modify(1, 1, 5);
	assert(m.element(1, 1) == 5);
	m.modify(1, 1, 6);
	assert(m.element(1, 2) == NULL_TELEM);


	// TEST FOR MULTIPLICATION

	/*
	
	a = [1 2 3]  b = [10 11]
	    [4 5 6]      [20 21]
					 [30 31]

	result = [140 146]
			 [320 335]
	
	*/

	Matrix a(2, 3);
	Matrix b(3, 2);

	a.modify(0, 0, 1);
	a.modify(0, 1, 2);
	a.modify(0, 2, 3);
	a.modify(1, 0, 4);
	a.modify(1, 1, 5);
	a.modify(1, 2, 6);

	b.modify(0, 0, 10);
	b.modify(0, 1, 11);
	b.modify(1, 0, 20);
	b.modify(1, 1, 21);
	b.modify(2, 0, 30);
	b.modify(2, 1, 31);

	Matrix* r = a.multiply(b);

	assert(r->element(0, 0) == 140);
	assert(r->element(0, 1) == 146);
	assert(r->element(1, 0) == 320);
	assert(r->element(1, 1) == 335);

	delete r;
}
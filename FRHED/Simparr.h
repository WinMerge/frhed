/*
Frhed - Free hex editor
Copyright (C) 2000 Raihan Kibria

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License, version 2, as published by
the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with this program; see the file COPYING.  If not, write to the Free
Software Foundation, 59 Temple Place - Suite 330, Boston, MA
02111-1307, USA.

Last change: 2017-06-24 by Jochen Neubeck
*/
/** 
 * @file  Simparr.h
 *
 * @brief Declaration file for SimpleArray and SimpleString classes.
 *
 */
#ifndef simplearr_h
#define simplearr_h

/**
 * A simple array class template.
 * This template offers basic array class methods.
 * @note This class is limited in 32-bit space for item count.
 */
template<typename Type, int mGrowBy = 1>
class SimpleArray : public Vector<Type, mGrowBy>
{
public:
	SimpleArray() { }
	bool InsertAtGrow(size_t index, Type val, size_t number = 1)
	{
		if (index > mSize)
			return false;
		return Vector::insert(index, val, number);
	}
	bool InsertAtGrow(size_t index, Type const *ptr, size_t number)
	{
		if (index > mSize)
			return false;
		return Vector::insert(index, ptr, number);
	}
	bool RemoveAt(size_t index, size_t number = 1)
	{
		if (index >= mSize || number <= 0)
			return false;
		Vector::remove(index, number);
		return true;
	}
	void Adopt(Type *data, size_t size, size_t capacity)
	{
		delete [] mData;
		mData = data;
		mCapacity = capacity;
		mSize = size;
	}
	bool Replace(size_t index, size_t length, Type const *ptr, size_t number)
	{
		if (length <= 0 || index + length > mSize)
			return false;
		return replace(index, length, ptr, number);
	}
private:
	SimpleArray(const SimpleArray &); // disallow copy construction
	SimpleArray &operator=(const SimpleArray &); // disallow assignment
};

#endif // simplearr_h

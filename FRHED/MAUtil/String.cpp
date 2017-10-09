/* Copyright (C) 2009 Mobile Sorcery AB

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

This is an edited version of code obtained from:
https://github.com/MoSync/MoSync/blob/master/libs/MAUtil

Last change: 2017-06-27 by Jochen Neubeck
*/

#include "precomp.h"
#include "String.h"

namespace MAUtil {

#if defined(MAUTIL_VECTOR_DEBUGGING)
	int nV = 0;
#endif

	template<class Tchar> StringData<Tchar>::StringData(int len, const Tchar* text)
		: RefCounted(1)
	{
		if (!resize(len + 1))
			return;
		mData[--mSize] = 0;
		if (text != NULL)
			memcpy(mData, text, mSize * sizeof(Tchar));
	}

#ifdef HAVE_EMPTY_STRING
	const BasicString* BasicString<Tchar>::EMPTY_STRING = NULL;
#endif

	template<class Tchar> static StringData<Tchar>* getEmptyData();

	static StringData<char> ed_char(0);
	template<>
	StringData<char>* getEmptyData<char>()
	{
		ed_char.addRef();
		return &ed_char;
	}

	static StringData<wchar_t> ed_wchar(0);
	template<>
	StringData<wchar_t>* getEmptyData<wchar_t>()
	{
		ed_wchar.addRef();
		return &ed_wchar;
	}

	template<class Tchar> BasicString<Tchar>::BasicString() {
		sd = getEmptyData<Tchar>();
	}

	template<class Tchar> BasicString<Tchar>::BasicString(int aCapacity) {
		sd = new StringData<Tchar>(aCapacity);
		resize(0);
	}

	template<class Tchar> void BasicString<Tchar>::allocStringData(const Tchar* text, int len) {
		if(len < 0) {
			maPanic(0, "BasicString(const Tchar* text, int len), passed a negative length.");
		}

		if(text == NULL || *text == 0 || len == 0) {
			sd = getEmptyData<Tchar>();
		} else {
			sd = new StringData<Tchar>(len, text);
			MAASSERT(sd);
		}		
	}

	template<class Tchar> BasicString<Tchar>::BasicString(const Tchar* text, int len) {
		if(text == NULL) maPanic(0, "BasicString(const Tchar* text, int len), passed a NULL pointer.");
		allocStringData(text, len);
	}

	template<class Tchar> BasicString<Tchar>::BasicString(const Tchar* text) {
		if(text == NULL) maPanic(0, "BasicString(const Tchar* text), passed a NULL pointer.");
		allocStringData(text, tstrlen(text));
	}

	template<class Tchar> BasicString<Tchar>::BasicString(const BasicString& s) {
		sd = s.sd;
		sd->addRef();
	}

	template<class Tchar> const Tchar* BasicString<Tchar>::c_str() const {
		return sd->pointer();
	}

	template<class Tchar> BasicString<Tchar>& BasicString<Tchar>::operator=(const BasicString& s) {
		StringData<Tchar>* old = sd;
		sd = s.sd;
		sd->addRef();
		old->release();
		return *this;
	}

	template<class Tchar> bool BasicString<Tchar>::operator==(const BasicString& other) const {
		return sd == other.sd ||
			length() == other.length() && tstrcmp(c_str(), other.c_str()) == 0;
	}

	template<class Tchar> bool BasicString<Tchar>::operator!=(const BasicString& other) const {
		return !((*this)==other);
	}

	template<class Tchar> bool BasicString<Tchar>::operator<(const BasicString& other) const {
		return tstrcmp(c_str(), other.c_str()) < 0;
	}


	template<class Tchar> bool BasicString<Tchar>::operator>(const BasicString& other) const {
		return tstrcmp(c_str(), other.c_str()) > 0;
	}


	template<class Tchar> bool BasicString<Tchar>::operator<=(const BasicString& other) const {
		return tstrcmp(c_str(), other.c_str()) <= 0;
	}

	template<class Tchar> bool BasicString<Tchar>::operator>=(const BasicString& other) const {
		return tstrcmp(c_str(), other.c_str()) >= 0;
	}

	template<class Tchar> Tchar& BasicString<Tchar>::operator[](int index) {
		//if memory is shared, do copy on write

		if(sd->getRefCount() > 1) {
			StringData<Tchar>* newSd = new StringData<Tchar>(sd->size(), sd->pointer());
			MAASSERT(newSd);
			sd->release();
			sd = newSd;
		}

		return sd->pointer()[index];
	}

#ifndef NEW_OPERATORS
	template<class Tchar>
	BasicString<Tchar> BasicString<Tchar>::operator+(const BasicString<Tchar>& other) const {
		BasicString<Tchar> s = *this;
		s += other;
		return s;
	}

	template<class Tchar> void BasicString<Tchar>::append(const Tchar* other, int len) {
		//order of operations is important here.
		int oldLen = length();
		int otherLen = len;
		int newLen = oldLen + otherLen;
		if(sd->getRefCount() > 1) {
			StringData<Tchar>* newSd = new StringData<Tchar>(newLen);
			memcpy(newSd->pointer(), sd->pointer(), oldLen * sizeof(Tchar));
			sd->release();
			sd = newSd;
		} else {
			sd->reserve(newLen + 1);
		}
		memcpy(sd->pointer() + oldLen, other, otherLen * sizeof(Tchar));
		pointer()[newLen] = 0;
		sd->resize(newLen);		
	}

	template<class Tchar>
	BasicString<Tchar>& BasicString<Tchar>::operator+=(const BasicString<Tchar>& other) {
		append(other.c_str(), other.length());
		return *this;
	}

	template<class Tchar> BasicString<Tchar> BasicString<Tchar>::operator+(Tchar c) const {
		BasicString s = *this;
		s += c;
		return s;
	}

	template<class Tchar> BasicString<Tchar>& BasicString<Tchar>::operator+=(Tchar c) {
		append(&c, 1);
		return *this;
	}
#endif	//NEW_OPERATORS

	template<class Tchar>
	int BasicString<Tchar>::find(BasicString<Tchar> const &s, int offset) const {
		if (s.length() + offset <= length()) {
			if (s.length() == 0)
				return offset;	// Empty string is always found
			Tchar const *str = c_str() + offset;
			Tchar const *search = s.c_str();
			Tchar const *const end = c_str() + length() - s.length();
			Tchar const *const search_end = s.c_str() + s.length() - 1;
			do if (*str == *search) {
				Tchar const *i = str;
				Tchar const *j = search;
				do if (j == search_end) {
					return static_cast<int>(str - sd->pointer());
				} while (*++i == *++j);
			} while (str++ != end);
		}
		return npos;
	}

	template<class Tchar> int BasicString<Tchar>::findLastOf(const Tchar findThis) const {
		for(int i = this->length(); i >= 0; i--) {
			if((*this)[i] == findThis) return i;
		}
		return npos;
	}

	template<class Tchar>
	int BasicString<Tchar>::findFirstOf(const Tchar findThis, int position) const {
		for(int i = position; i < this->length(); i++) {
			if((*this)[i] == findThis) return i;
		}
		return npos;
	}

	template<class Tchar>
	int BasicString<Tchar>::findFirstNotOf(const Tchar findNotThis, int position) const {
		for(int i = position; i < this->length(); i++) {
			if((*this)[i] != findNotThis) return i;
		}
		return npos;
	}

	template<class Tchar>
	void BasicString<Tchar>::insert(int position, const BasicString<Tchar>& other) {
		int otherLen = other.length();
		int newLen = this->length() + otherLen;
		this->resize(newLen);
		int endpos = position + otherLen;
		for(int i = newLen-1; i >= endpos; i--) {
			(*sd)[i] = (*sd)[i-otherLen];
		}
		for(int i = 0; i < otherLen; i++) {
			(*sd)[position++] = other[i];
		}
	}

	//TODO: cleanup
	template<class Tchar> void BasicString<Tchar>::insert(int position, Tchar c) {
		int otherLen = 1;
		int newLen = this->length() + otherLen;
		this->resize(newLen);
		int endpos = position + otherLen;
		for(int i = newLen-1; i >= endpos; i--) {
			(*sd)[i] = (*sd)[i-otherLen];
		}
		for(int i = 0; i < otherLen; i++) {
			(*sd)[position++] = c;
		}
	}

	template<class Tchar> void BasicString<Tchar>::remove(int position, int number) {
		if(sd->getRefCount() > 1) {
			ASSERT_MSG(position >= 0 && position < this->length(), "invalid position");
			ASSERT_MSG(number > 0 && (position + number) <= this->length(), "invalid number");
			int newLen = size() - number;
			StringData<Tchar>* temp = new StringData<Tchar>(newLen);
			if(position > 0) {
				memcpy(temp->pointer(), sd->pointer(), position * sizeof(Tchar));
			}
			if(position < newLen) {
				memcpy(temp->pointer() + position, sd->pointer() + (position + number),
					(newLen - position) * sizeof(Tchar));
			}
			sd->release();
			sd = temp;
		} else {
			sd->remove(position, number);
			sd->reserve(sd->size() + 1);
		}
		(*sd)[sd->size()] = 0;
	}

	template<class Tchar>
	BasicString<Tchar> BasicString<Tchar>::substr(int startIndex, int len) const {
		ASSERT_MSG(startIndex >= 0 && startIndex <= this->length(), "invalid index");
		if(len == npos)
			len = length() - startIndex;
		ASSERT_MSG(len >= 0 && startIndex + len <= length(), "invalid length");

		return BasicString(c_str() + startIndex, len);
	}

	template<class Tchar> const Tchar& BasicString<Tchar>::operator[](int index) const {
		return sd->pointer()[index];
	}

	template<class Tchar> int BasicString<Tchar>::size() const {
		return sd->size();
	}

	template<class Tchar> int BasicString<Tchar>::length() const {
		return sd->size();
	}

	template<class Tchar> int BasicString<Tchar>::capacity() const {
		return sd->capacity() - 1;
	}

	template<class Tchar> BasicString<Tchar>::~BasicString() {
		sd->release();
	}

	template<class Tchar> void BasicString<Tchar>::resize(int newLen) {
		reserve(newLen);
		sd->resize(newLen);
		(*sd)[newLen] = 0;
	}

	template<class Tchar> void BasicString<Tchar>::reserve(int newLen) {
		if(sd->getRefCount() > 1) {
			if(newLen < sd->capacity())
				newLen = sd->capacity();
			StringData<Tchar>* temp = new StringData<Tchar>(newLen);
			temp->resize(sd->size());
			memcpy(temp->pointer(), sd->pointer(), (sd->size() + 1) * sizeof(Tchar));
			sd->release();
			sd = temp;
		} else {
			sd->reserve(newLen+1);
			(*sd)[sd->size()] = 0;
		}
	}

	template<class Tchar> void BasicString<Tchar>::clear() {
		if(sd) {
			sd->release();
		}
		sd = getEmptyData<Tchar>();
	}

#ifdef HAVE_EMPTY_STRING
	template<class Tchar> const BasicString& BasicString<Tchar>::emptyString() {
		return *EMPTY_STRING;
	}
#endif

	template<class Tchar> void BasicString<Tchar>::setData(StringData<Tchar>* data) {
		sd->release();
		sd = data;
	}

	template<class Tchar> Tchar* BasicString<Tchar>::pointer() {
		return sd->pointer();
	}

	//explicit instantiation
	template class BasicString<char>;
	template class BasicString<wchar_t>;
	template class StringData<char>;
	template class StringData<wchar_t>;
}

template<> int tstrlen<char>(const char* str) { return static_cast<int>(strlen(str)); }
template<> int tstrcmp<char>(const char* a, const char* b) { return strcmp(a, b); }

template<class Tchar> int tstrlen(const Tchar* str) { return static_cast<int>(wcslen(str)); }
template<class Tchar> int tstrcmp(const Tchar* a, const Tchar* b) { return wcscmp(a, b); }

//explicit instantiation (needed to link with these functions in MAPIP.)
template int tstrlen<wchar_t>(const wchar_t*);
template int tstrcmp<wchar_t>(const wchar_t*, const wchar_t*);

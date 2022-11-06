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

Last change: 2017-06-21 by Jochen Neubeck
*/
/** 
 * @file  BinTrans.h
 *
 * @brief Text to binary converter class declaration.
 *
 */
#ifndef BinTrans_h
#define BinTrans_h

size_t create_bc_translation(BYTE** ppd, const char* src, size_t srclen, int charset, int binarymode);

/**
 * @brief A class translating between text export and binary data.
 */
class Text2BinTranslator : public String
{
public:
	int bCompareBin(Text2BinTranslator& tr2, int charmode, int binmode);
	Text2BinTranslator(const char* ps);
	static int iIsBytecode(const char* src, size_t len);
	static size_t iBytes2BytecodeDestLen(const BYTE* src, size_t srclen);
	static size_t iLengthOfTransToBin(const char* src, size_t srclen);
	static size_t iCreateBcTranslation(BYTE* dest, const char* src, size_t srclen, int charmode, int binmode);
	static int iTranslateOneBytecode(BYTE* dest, const char* src, size_t srclen, int binmode);
	static size_t iFindBytePos(const char* src, char c);
	static size_t iTranslateBytesToBC(char* pd, const BYTE* src, size_t srclen);

private:
	size_t GetTrans2Bin(Vector<BYTE>& sa, int charmode, int binmode);
};

#endif // BinTrans_h

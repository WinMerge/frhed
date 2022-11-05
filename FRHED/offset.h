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

Last change: 2013-02-24 by Jochen Neubeck
*/
/** 
 * @file  Offset.h
 *
 * @brief Definition of the offset helper functions.
 *
 */
#ifndef _OFFSET_H_
#define _OFFSET_H_

bool offset_parse(LPCTSTR str, int &offset);
bool offset_parse64(LPCTSTR str, INT64 &offset);
bool offset_parse_size_t(LPCTSTR str, size_t &offset);
bool offset_parse_ssize_t(LPCTSTR str, SSIZE_T &offset);

#endif _OFFSET_H_

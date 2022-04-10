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

Last change: 2013-02-26 by Jochen Neubeck
*/
/**
 * @file  LangArray.cpp
 *
 * @brief Implementation for translated text array class.
 *
 */
#include "precomp.h"
#include "LangArray.h"
#include "VersionData.h"

static const UINT ModifyableMenuFlags = MF_POPUP | MF_BITMAP | MF_DISABLED | MF_GRAYED | MF_MENUBARBREAK | MF_MENUBREAK;

const LANGID LangArray::DefLangId = MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US);

/**
 * @brief Remove prefix from the string.
 * @param [in] text String from which to jump over prefix.
 * @param [in] prefix Prefix string to jump over.
 * @return String without the prefix.
 * @note Function returns pointer to original string,
 *  it does not allocate a new string.
 */
static char *EatPrefix(char *text, const char *prefix)
{
	if (size_t len = strlen(prefix))
		if (_memicmp(text, prefix, len) == 0)
			return text + len;
	return 0;
}

LangArray::StringData *LangArray::StringData::Create(const char *ps, size_t length)
{
	size_t cb = FIELD_OFFSET(StringData, data) + length + 1;
	StringData *psd = reinterpret_cast<StringData *>(new char[cb]);
	psd->refcount = 0;
	memcpy(psd->data, ps, length);
	psd->data[length] = '\0';
	return psd;
}

char *LangArray::StringData::Share()
{
	++refcount;
	return data;
}

void LangArray::StringData::Unshare(char *data)
{
	data -= FIELD_OFFSET(StringData, data);
	if (--reinterpret_cast<StringData *>(data)->refcount == 0)
		delete [] data;
}

LangArray::LangArray()
: m_hLangDll(0)
, m_codepage(0)
, m_langid(0)
{
}

LangArray::~LangArray()
{
	ClearAll();
}

void LangArray::ExpandToSize()
{
	while (mSize < mCapacity)
		mData[mSize++] = NULL;
}

void LangArray::ClearAll()
{
	while (mSize)
		if (char *data = mData[--mSize])
			StringData::Unshare(data);
	Vector::clear();
}

/**
 * @brief Convert C style \\nnn, \\r, \\n, \\t etc into their indicated characters.
 * @param [in] codepage Codepage to use in conversion.
 * @param [in,out] s String to convert.
 */
static size_t unslash(unsigned codepage, char *s)
{
	char *p = s;
	char *q = p;
	char c;
	do
	{
		char *r = q + 1;
		switch (c = *q)
		{
		case '\\':
			switch (c = *r++)
			{
			case 'a':
				c = '\a';
				break;
			case 'b':
				c = '\b';
				break;
			case 'f':
				c = '\f';
				break;
			case 'n':
				c = '\n';
				break;
			case 'r':
				c = '\r';
				break;
			case 't':
				c = '\t';
				break;
			case 'v':
				c = '\v';
				break;
			case 'x':
				*p = (char)strtol(r, &q, 16);
				break;
			default:
				*p = (char)strtol(r - 1, &q, 8);
				break;
			}
			if (q >= r)
				break;
			// fall through
		default:
			*p = c;
			if ((c & 0x80) && IsDBCSLeadByteEx(codepage, c))
				*++p = *r++;
			q = r;
		}
		++p;
	} while (c != '\0');
	return p - s - 1;
}

BOOL LangArray::Load(HINSTANCE hMainInstance, LANGID langid, LPCTSTR langdir)
{
	if (m_langid == langid)
		return TRUE;
	m_langid = langid;
	ClearAll();
	char buf[1024];
	String *ps = 0;
	String msgid;
	Vector<int> lines;
	int unresolved = 0;
	int mismatched = 0;
	FILE *f = 0;
	switch (langid)
	{
	case 0:
	case DefLangId:
		break;
	default:
		TCHAR path[MAX_PATH];
		GetModuleFileName(hMainInstance, path, MAX_PATH);
		PathRemoveFileSpec(path);
		PathAppend(path, langdir);
		PathAppend(path, _T("heksedit.lng"));
		if (m_hLangDll == 0)
		{
			m_hLangDll = LoadLibrary(path);
			if (m_hLangDll == 0)
				break;
		}
		const CVersionData *pvdMain = CVersionData::Load(hMainInstance);
		if (pvdMain == 0)
			break;
		const CVersionData *pvdLang = CVersionData::Load(m_hLangDll);
		if (pvdLang == 0)
			break;
		if (memcmp(pvdMain->Data(), pvdLang->Data(), FIELD_OFFSET(VS_FIXEDFILEINFO, dwProductVersionMS)))
			break;
		HRSRC potfile = FindResource(m_hLangDll, _T("en-US.pot"), RT_RCDATA);
		if (potfile == 0)
			break;
		size_t size = SizeofResource(m_hLangDll, potfile);
		const char *data = (const char *)LoadResource(m_hLangDll, potfile);
		while (const char *eol = (const char *)memchr(data, '\n', size))
		{
			size_t len = eol - data;
			if (len >= sizeof buf)
			{
				assert(FALSE);
				break;
			}
			memcpy(buf, data, len);
			buf[len++] = '\0';
			data += len;
			size -= len;
			if (char *p = EatPrefix(buf, "#:"))
			{
				if (char *q = strchr(p, ':'))
				{
					int line = strtol(q + 1, &q, 10);
					lines.add(line);
					++unresolved;
				}
			}
			else if (EatPrefix(buf, "msgid "))
			{
				ps = &msgid;
			}
			if (ps)
			{
				char *p = strchr(buf, '"');
				char *q = strrchr(buf, '"');
				if (q > p)
				{
					*q = '\0';
					ps->append(p + 1, q - p - 1);
				}
				else
				{
					ps = 0;
					if (int i = lines.size())
					{
						StringData *psd = StringData::Create(msgid.c_str(), msgid.length());
						do
						{
							int line = lines[--i];
							if (mSize <= line)
							{
								reserve(line + 1);
								ExpandToSize();
							}
							mData[line] = psd->Share();
						} while (i);
					}
					lines.clear();
					msgid.clear();
				}
			}
		}
		PathRemoveFileSpec(path);
		LPTSTR name = PathAddBackslash(path);
		// Look for a .po file that matches the given langid.
		// Possible cases in order of precedence:
		// (1) Country specific translation for given country, e.g. de-CH.po
		// (2) Country specific translation to serve as default, e.g. de-DE.po
		// (3) Country inspecific translation, e.g. de.po
		do
		{
			if (int i = LangCodeMajor(langid, name))
			{
				int j = LangCodeMinor(langid, name + i);
				name[--i] = '-';
				do
				{
					_tcscpy(name + i + j, _T(".po"));
					f = _tfopen(path, _T("r"));
					if (j == 0 || SUBLANGID(langid) != SUBLANG_DEFAULT)
						break;
					j = 0;
				} while (f == 0);
			}
			if (SUBLANGID(langid) == SUBLANG_DEFAULT)
				break;
			langid = MAKELANGID(PRIMARYLANGID(langid), SUBLANG_DEFAULT);
		} while (f == 0);
	}
	if (f == 0)
	{
		if (m_hLangDll)
			FreeLibrary(m_hLangDll);
		m_hLangDll = 0;
		return FALSE;
	}
	ps = 0;
	msgid.clear();
	lines.clear();
	String msgstr;
	String format;
	String directive;
	while (fgets(buf, sizeof buf, f))
	{
		if (char *p = EatPrefix(buf, "#:"))
		{
			if (char *q = strchr(p, ':'))
			{
				int line = strtol(q + 1, &q, 10);
				if (line == 367)
					line = line;
				lines.add(line);
				--unresolved;
			}
		}
		else if (char *p = EatPrefix(buf, "#,"))
		{
			StrTrimA(p, " \t\r\n");
			format = p;
		}
		else if (char *p = EatPrefix(buf, "#."))
		{
			StrTrimA(p, " \t\r\n");
			directive = p;
		}
		else if (EatPrefix(buf, "msgid "))
		{
			ps = &msgid;
		}
		else if (EatPrefix(buf, "msgstr "))
		{
			ps = &msgstr;
		}
		if (ps)
		{
			char *p = strchr(buf, '"');
			char *q = strrchr(buf, '"');
			if (q > p)
			{
				*q = '\0';
				ps->append(p + 1, q - p - 1);
			}
			else
			{
				ps = 0;
				if (msgstr.length() == 0)
					msgstr.append(msgid.c_str(), msgid.length());
				msgstr.resize(unslash(m_codepage, msgstr.pointer()));
				if (int i = lines.size())
				{
					StringData *psd = StringData::Create(msgstr.c_str(), msgstr.length());
					do
					{
						int line = lines[--i];
						if (mSize <= line)
						{
							reserve(line + 1);
							ExpandToSize();
						}
						char *data = mData[line];
						if (data && strcmp(data, msgid.c_str()) == 0)
						{
							StringData::Unshare(data);
							mData[line] = psd->Share();
						}
						else
						{
							++mismatched;
						}
					} while (i);
				}
				lines.clear();
				if (strcmp(directive.c_str(), "Codepage") == 0)
				{
					m_codepage = strtol(msgstr.c_str(), &p, 10);
					directive.clear();
				}
				msgid.clear();
				msgstr.clear();
			}
		}
	}
	fclose(f);
	if (unresolved || mismatched)
	{
		ClearAll();
		if (m_hLangDll)
			FreeLibrary(m_hLangDll);
		m_hLangDll = 0;
		return FALSE;
	}
	return TRUE;
}

PTSTR LangArray::TranslateString(int line)
{
#ifdef UNICODE
	BSTR ws = 0;
	if (line > 0 && line < mSize)
	{
		if (char *s = mData[line])
		{
			if (UINT len = static_cast<UINT>(strlen(s)))
			{
				ws = SysAllocStringLen(0, len);
				len = MultiByteToWideChar(m_codepage, 0, s, -1, ws, len + 1);
				SysReAllocStringLen(&ws, ws, len - 1);
			}
		}
	}
	return ws;
#else
	PTSTR t = 0;
	if (line > 0 && line < mSize)
	{
		if (char *s = mData[line])
		{
			if (UINT len = static_cast<UINT>(strlen(s)))
			{
				unsigned codepage = GetACP();
				if (m_codepage != codepage)
				{
					// Attempt to convert to UI codepage
					BSTR ws = SysAllocStringLen(0, len);
					len = MultiByteToWideChar(m_codepage, 0, s, -1, ws, len + 1);
					if (len)
					{
						SysReAllocStringLen(&ws, ws, len - 1);
						len = WideCharToMultiByte(codepage, 0, ws, -1, 0, 0, 0, 0);
						if (len)
						{
							t = (PTSTR)SysAllocStringByteLen(0, len - 1);
							WideCharToMultiByte(codepage, 0, ws, -1, t, len, 0, 0);
						}
					}
					SysFreeString(ws);
				}
				else
				{
					t = (PTSTR)SysAllocStringByteLen(s, len);
				}
			}
		}
	}
	return t;
#endif
}

void LangArray::TranslateDialog(HWND h)
{
	UINT gw = GW_CHILD;
	do
	{
		TCHAR text[80];
		::GetWindowText(h, text, RTL_NUMBER_OF(text));
		int line = 0;
		if (PTSTR p = _tcschr(text, _T(':')))
			line = _ttoi(p + 1);
		if (PTSTR t = TranslateString(line))
		{
			::SetWindowText(h, t);
			::SysFreeString((BSTR)t);
		}
		h = ::GetWindow(h, gw);
		gw = GW_HWNDNEXT;
	} while (h);
}

void LangArray::TranslateMenu(HMENU h)
{
	if (h)
	{
		int i = GetMenuItemCount(h);
		while (i > 0)
		{
			--i;
			UINT state = GetMenuState(h, i, MF_BYPOSITION);
			UINT id;
			if (state & MF_POPUP)
			{
				id = reinterpret_cast<UINT>(GetSubMenu(h, i));
				TranslateMenu(reinterpret_cast<HMENU>(id));
			}
			else
			{
				id = GetMenuItemID(h, i);
			}
			TCHAR text[80];
			if (GetMenuString(h, i, text, RTL_NUMBER_OF(text), MF_BYPOSITION))
			{
				int line = 0;
				if (PTSTR p = _tcschr(text, _T(':')))
					line = _ttoi(p + 1);
				if (PTSTR t = TranslateString(line))
				{
					::ModifyMenu(h, i, state & ModifyableMenuFlags | MF_BYPOSITION, id, t);
					::SysFreeString((BSTR)t);
				}
			}
		}
	}
}

HMENU LangArray::LoadMenu(HINSTANCE hMainInstance, LPTSTR idr)
{
	HMENU h = ::LoadMenu(m_hLangDll ? m_hLangDll : hMainInstance, idr);
	if (m_hLangDll)
		TranslateMenu(h);
	return h;
}

int LangArray::LangCodeMajor(LANGID langid, LPTSTR name)
{
	return GetLocaleInfo(langid, LOCALE_SISO639LANGNAME, name, 4);
}

int LangArray::LangCodeMinor(LANGID langid, LPTSTR name)
{
	static const TCHAR cyrl[] = _T("Cyrl");
	static const TCHAR latn[] = _T("Latn");
	switch (langid)
	{
	case MAKELANGID(LANG_AZERI, SUBLANG_AZERI_LATIN):
	case MAKELANGID(LANG_SERBIAN, SUBLANG_SERBIAN_LATIN):
	case MAKELANGID(LANG_UZBEK, SUBLANG_UZBEK_LATIN):
		memcpy(name, latn, sizeof latn);
		return RTL_NUMBER_OF(latn);
	case MAKELANGID(LANG_AZERI, SUBLANG_AZERI_CYRILLIC):
	case MAKELANGID(LANG_SERBIAN, SUBLANG_SERBIAN_CYRILLIC):
	case MAKELANGID(LANG_UZBEK, SUBLANG_UZBEK_CYRILLIC):
		memcpy(name, cyrl, sizeof cyrl);
		return RTL_NUMBER_OF(cyrl);
	}
	return GetLocaleInfo(langid, LOCALE_SISO3166CTRYNAME, name, 4);
}

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
 * @file  ViewSettingsDlg.cpp
 *
 * @brief Implementation of the View settings -dialog.
 *
 */
#include "precomp.h"
#include "resource.h"
#include "hexwnd.h"
#include "hexwdlg.h"
#include "LangArray.h"
#include "StringTable.h"
#include "Constants.h"
#include "AnsiConvert.h"

HComboBox *ViewSettingsDlg::pCbLang;

/**
 * @brief Available and installed languages enumerator.
 * This method enumerates all available locales. Then it checks if there is a
 * matching language file available. If the language file is available the
 * language is added to the Viewsettings dialog.
 * @param [in] lpLocaleString Locale identifier string.
 * @return TRUE to continue enumeration, FALSE otherwise.
 */
BOOL ViewSettingsDlg::EnumLocalesProc(LPTSTR lpLocaleString)
{
	TCHAR path[MAX_PATH];
	GetModuleFileName(hMainInstance, path, MAX_PATH);
	PathRemoveFileSpec(path);
	PathAppend(path, static_cast<W2T>(LangFileSubFolder));
	LPTSTR name = PathAddBackslash(path);
	LCID lcid = 0;
	if (_stscanf(lpLocaleString, _T("%x"), &lcid) == 1)
	{
		LANGID langid = (LANGID)lcid;
		if (int i = GetLocaleInfo(langid, LOCALE_SISO639LANGNAME, name, 4))
		{
			int j = GetLocaleInfo(langid, LOCALE_SISO3166CTRYNAME, name + i, 4);
			name[--i] = '-';
			BOOL f = langid == LangArray::DefLangId;
			while (f == 0)
			{
				_tcscpy(name + i + j, _T(".po"));
				f = PathFileExists(path);
				if (j == 0 || SUBLANGID(langid) != SUBLANG_DEFAULT)
					break;
				j = 0;
			}
			if (f)
			{
				WCHAR buffer[256];
				DWORD_PTR itemData = MAKELONG(langid, f);
				int length = FormatLangId(buffer, LOWORD(itemData), true);
				int k = pCbLang->AddString(buffer);
				pCbLang->SetItemData(k, itemData);
				if (langid == (langArray.m_langid ? langArray.m_langid : LangArray::DefLangId))
					pCbLang->SetCurSel(k);
			}
		}
	}
	return TRUE;
}

int ViewSettingsDlg::FormatLangId(LPWSTR bufW, LANGID langid, bool verbose)
{
#ifdef UNICODE
	int i = LangArray::LangCodeMajor(langid, bufW);
#else
	CHAR bufA[256];
	int i = LangArray::LangCodeMajor(langid, bufA);
#endif
	if (i)
	{
#ifdef UNICODE
		bufW[i - 1] = '-';
		i += LangArray::LangCodeMinor(langid, bufW + i);
		if (verbose)
		{
			bufW[i - 1] = ' '; bufW[i++] = '-'; bufW[i++] = ' ';
			i += GetLocaleInfoW(langid, LOCALE_SNATIVELANGNAME|LOCALE_USE_CP_ACP, bufW + i, 40);
			bufW[i - 1] = ' '; bufW[i++] = '-'; bufW[i++] = ' ';
			i += GetLocaleInfoW(langid, LOCALE_SNATIVECTRYNAME|LOCALE_USE_CP_ACP, bufW + i, 40);
			bufW[i - 1] = ' '; bufW[i++] = '-'; bufW[i++] = ' ';
			i += GetLocaleInfoW(langid, LOCALE_SENGLANGUAGE, bufW + i, 40);
			bufW[i - 1] = ' '; bufW[i++] = '-'; bufW[i++] = ' ';
			i += GetLocaleInfoW(langid, LOCALE_SENGCOUNTRY, bufW + i, 40);
		}
#else
		bufA[i - 1] = '-';
		i += LangArray::LangCodeMinor(langid, bufA + i);
		if (verbose)
		{
			bufA[i - 1] = ' '; bufA[i++] = '-'; bufA[i++] = ' ';
			i += GetLocaleInfoA(langid, LOCALE_SNATIVELANGNAME|LOCALE_USE_CP_ACP, bufA + i, 40);
			bufA[i - 1] = ' '; bufA[i++] = '-'; bufA[i++] = ' ';
			i += GetLocaleInfoA(langid, LOCALE_SNATIVECTRYNAME|LOCALE_USE_CP_ACP, bufA + i, 40);
			bufA[i - 1] = ' '; bufA[i++] = '-'; bufA[i++] = ' ';
			i += GetLocaleInfoA(langid, LOCALE_SENGLANGUAGE, bufA + i, 40);
			bufA[i - 1] = ' '; bufA[i++] = '-'; bufA[i++] = ' ';
			i += GetLocaleInfoA(langid, LOCALE_SENGCOUNTRY, bufA + i, 40);
		}
		MultiByteToWideChar(CP_ACP, 0, bufA, i, bufW, i);
#endif
		--i;
	}
	else
	{
		i = swprintf(bufW, L"%04x", langid);
	}
	return i;
}

/**
 * @brief Initialize the dialog controls.
 * This function initializes dialog controls from current option values. Not
 * reading from registry since there are values calculated runtime (min.
 * offset length).
 * @param [in] hDlg Handle to the dialog.
 * @return TRUE.
 */
BOOL ViewSettingsDlg::OnInitDialog(HWindow *pDlg)
{
	pDlg->SetDlgItemInt(IDC_SETTINGS_BYTESPERLINE, iBytesPerLine);
	pDlg->SetDlgItemInt(IDC_SETTINGS_OFFSETLEN, iMinOffsetLen);
	UINT checked = iAutomaticBPL == 0 ? BST_UNCHECKED : BST_CHECKED;
	pDlg->CheckDlgButton(IDC_SETTINGS_ADJUST_BYTELINE, checked);
	pDlg->CheckDlgButton(bUnsignedView ? IDC_SETTINGS_CARETUNSIGN :
			IDC_SETTINGS_CARETSIGN, BST_CHECKED);
	checked = bOpenReadOnly == 0 ? BST_UNCHECKED : BST_CHECKED;
	pDlg->CheckDlgButton(IDC_SETTINGS_OPENRO, checked);
	checked = bAutoOffsetLen == 0 ? BST_UNCHECKED : BST_CHECKED;
	pDlg->CheckDlgButton(IDC_SETTINGS_ADJOFFSET, checked);
	pDlg->SetDlgItemText(IDC_SETTINGS_EDITOR, TexteditorName);
	pCbLang = static_cast<HComboBox *>(pDlg->GetDlgItem(IDC_SETTINGS_LANGUAGE));
	// Populate the dropdown list.
	EnumSystemLocales(EnumLocalesProc, LCID_SUPPORTED);
	return TRUE;
}

/**
 * @brief Save the settings in dialog controls to registry.
 * @param [in] hDlg Handle to the dialog.
 * @return TRUE.
 */
BOOL ViewSettingsDlg::Apply(HWindow *pDlg)
{
	iBytesPerLine = pDlg->GetDlgItemInt(IDC_SETTINGS_BYTESPERLINE, 0);
	if (iBytesPerLine < 1)
		iBytesPerLine = 1;
	iMinOffsetLen = pDlg->GetDlgItemInt(IDC_SETTINGS_OFFSETLEN, 0);
	if (iMinOffsetLen < 1)
		iMinOffsetLen = 1;
	// Get the text editor path and name.
	pDlg->GetDlgItemText(IDC_SETTINGS_EDITOR, TexteditorName, RTL_NUMBER_OF(TexteditorName));
	
	UINT res = pDlg->IsDlgButtonChecked(IDC_SETTINGS_ADJUST_BYTELINE);
	if (res == BST_CHECKED)
		iAutomaticBPL = 1;
	else
		iAutomaticBPL = 0;

	res = pDlg->IsDlgButtonChecked(IDC_SETTINGS_ADJOFFSET);
	if (res == BST_CHECKED)
		bAutoOffsetLen = 1;
	else
		bAutoOffsetLen = 0;

	res = pDlg->IsDlgButtonChecked(IDC_SETTINGS_CARETUNSIGN);
	if (res == BST_CHECKED)
		bUnsignedView = true;
	else if (res == BST_UNCHECKED)
		bUnsignedView = false;

	bOpenReadOnly = pDlg->IsDlgButtonChecked(IDC_SETTINGS_OPENRO);
	int i = pCbLang->GetCurSel();
	if (i != -1)
	{
		DWORD_PTR itemData = pCbLang->GetItemData(i);
		load_lang((LANGID)itemData);
	}
	save_ini_data();
	resize_window();
	return TRUE;
}

/**
 * @brief Show the file selection dialog to select text editor executable.
 * @param [in] hDlg Handle to the view settings dialog.
 */
void ViewSettingsDlg::SelectEditor(HWindow *pDlg)
{
	TCHAR szFileName[MAX_PATH];
	szFileName[0] = '\0';
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof ofn);
	ofn.lStructSize = sizeof ofn;
	ofn.hwndOwner = pwnd->m_hWnd;
	ofn.lpstrFilter = GetLangString(IDS_OPEN_ALL_FILES);
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_HIDEREADONLY | OFN_CREATEPROMPT;
	if (GetOpenFileName(&ofn))
	{
		_tcsncpy(TexteditorName, szFileName, MAX_PATH);
		pDlg->SetDlgItemText(IDC_SETTINGS_EDITOR, TexteditorName);
	}
}

/**
 * @brief Handle dialog messages.
 * @param [in] hDlg Handle to the dialog.
 * @param [in] iMsg The message.
 * @param [in] wParam The command in the message.
 * @param [in] lParam The optional parameter for the command.
 * @return TRUE if the message was handled, FALSE otherwise.
 */
INT_PTR ViewSettingsDlg::DlgProc(HWindow *pDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_INITDIALOG:
		return OnInitDialog(pDlg);
	case WM_COMMAND:
		switch (wParam)
		{
		case IDC_SETTINGS_EDITORSELECT:
			SelectEditor(pDlg);
			return TRUE;
		case IDOK:
			if (Apply(pDlg))
			{
			case IDCANCEL:
				pDlg->EndDialog(wParam);
			}
			return TRUE;
		}
		break;

	case WM_HELP:
		OnHelp(pDlg);
		break;
	}
	return FALSE;
}

/*=============================================================================
 * This is a part of the YeaSoft Software Development Kit.
 * Copyright (C) 2001 YEAsoft Int'l.
 * All rights reserved.
 *=============================================================================
 * Copyright (c) 2001 YEAsoft Int'l (Leo Moll, Andrea Pennelli).
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from the
 * use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software in
 *    a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *=============================================================================
 * FILENAME		:	Collection.cpp
 * PURPOSE		:	Implementation of better collection classes
 * SCOPE		:	YeaSoft MFC GUI Library
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/
#include "StdAfx.h"

#include <yCollection.h>

/*=============================================================================
 * THE LIST CLASSES
 *============================================================================*/
IMPLEMENT_DYNAMIC(CPtrListOk,CPtrList)

BOOL CPtrListOk::AddHead (void * newElement, POSITION *pPos /* = NULL */)
{
	try {
		POSITION pos = CPtrList::AddHead (newElement);
		if ( pPos ) {
			*pPos = pos;
		}
		return TRUE;
	}
	catch ( CMemoryException *pEx ) {
		TRACE(_T("CPtrList::AddHead failed.\n"));
		pEx->Delete ();
	}
	return FALSE;
}

BOOL CPtrListOk::AddTail (void * newElement, POSITION *pPos /* = NULL */)
{
	try {
		POSITION pos = CPtrList::AddTail (newElement);
		if ( pPos ) {
			*pPos = pos;
		}
		return TRUE;
	}
	catch ( CMemoryException *pEx ) {
		TRACE(_T("CPtrList::AddTail failed.\n"));
		pEx->Delete ();
	}
	return FALSE;
}

BOOL CPtrListOk::AddHead (CPtrList * pNewList)
{
	try {
		CPtrList::AddHead (pNewList);
		return TRUE;
	}
	catch ( CMemoryException *pEx ) {
		TRACE(_T("CPtrList::AddHead failed.\n"));
		pEx->Delete ();
	}
	return FALSE;
}

BOOL CPtrListOk::AddTail (CPtrList * pNewList)
{
	try {
		CPtrList::AddTail (pNewList);
		return TRUE;
	}
	catch ( CMemoryException *pEx ) {
		TRACE(_T("CPtrList::AddTail failed.\n"));
		pEx->Delete ();
	}
	return FALSE;
}

BOOL CPtrListOk::InsertBefore (POSITION position, void * newElement, POSITION *pPos /* = NULL */)
{
	try {
		POSITION pos = CPtrList::InsertBefore (position, newElement);
		if ( pPos ) {
			*pPos = pos;
		}
		return TRUE;
	}
	catch ( CMemoryException *pEx ) {
		TRACE(_T("CPtrList::InsertBefore failed.\n"));
		pEx->Delete ();
	}
	return FALSE;
}

BOOL CPtrListOk::InsertAfter (POSITION position, void * newElement, POSITION *pPos /* = NULL */)
{
	try {
		POSITION pos = CPtrList::InsertAfter (position, newElement);
		if ( pPos ) {
			*pPos = pos;
		}
		return TRUE;
	}
	catch ( CMemoryException *pEx ) {
		TRACE(_T("CPtrList::InsertAfter failed.\n"));
		pEx->Delete ();
	}
	return FALSE;
}

IMPLEMENT_SERIAL(CObListOk,CObList,0)

BOOL CObListOk::AddHead (CObject * newElement, POSITION *pPos /* = NULL */)
{
	try {
		POSITION pos = CObList::AddHead (newElement);
		if ( pPos ) {
			*pPos = pos;
		}
		return TRUE;
	}
	catch ( CMemoryException *pEx ) {
		TRACE(_T("CObList::AddHead failed.\n"));
		pEx->Delete ();
	}
	return FALSE;
}

BOOL CObListOk::AddTail (CObject * newElement, POSITION *pPos /* = NULL */)
{
	try {
		POSITION pos = CObList::AddTail (newElement);
		if ( pPos ) {
			*pPos = pos;
		}
		return TRUE;
	}
	catch ( CMemoryException *pEx ) {
		TRACE(_T("CObList::AddTail failed.\n"));
		pEx->Delete ();
	}
	return FALSE;
}

BOOL CObListOk::AddHead (CObList * pNewList)
{
	try {
		CObList::AddHead (pNewList);
		return TRUE;
	}
	catch ( CMemoryException *pEx ) {
		TRACE(_T("CObList::AddHead failed.\n"));
		pEx->Delete ();
	}
	return FALSE;
}

BOOL CObListOk::AddTail (CObList * pNewList)
{
	try {
		CObList::AddTail (pNewList);
		return TRUE;
	}
	catch ( CMemoryException *pEx ) {
		TRACE(_T("CObList::AddTail failed.\n"));
		pEx->Delete ();
	}
	return FALSE;
}

BOOL CObListOk::InsertBefore (POSITION position, CObject * newElement, POSITION *pPos /* = NULL */)
{
	try {
		POSITION pos = CObList::InsertBefore (position, newElement);
		if ( pPos ) {
			*pPos = pos;
		}
		return TRUE;
	}
	catch ( CMemoryException *pEx ) {
		TRACE(_T("CObList::InsertBefore failed.\n"));
		pEx->Delete ();
	}
	return FALSE;
}

BOOL CObListOk::InsertAfter (POSITION position, CObject * newElement, POSITION *pPos /* = NULL */)
{
	try {
		POSITION pos = CObList::InsertAfter (position, newElement);
		if ( pPos ) {
			*pPos = pos;
		}
		return TRUE;
	}
	catch ( CMemoryException *pEx ) {
		TRACE(_T("CObList::InsertAfter failed.\n"));
		pEx->Delete ();
	}
	return FALSE;
}

CObListOk::~CObListOk ()
{
}

IMPLEMENT_SERIAL(CStringListOk,CStringList,0)

BOOL CStringListOk::AddHead (LPCTSTR newElement, POSITION *pPos /* = NULL */)
{
	try {
		POSITION pos = CStringList::AddHead (newElement);
		if ( pPos ) {
			*pPos = pos;
		}
		return TRUE;
	}
	catch ( CMemoryException *pEx ) {
		TRACE(_T("CStringList::AddHead failed.\n"));
		pEx->Delete ();
	}
	return FALSE;
}

BOOL CStringListOk::AddTail (LPCTSTR newElement, POSITION *pPos /* = NULL */)
{
	try {
		POSITION pos = CStringList::AddTail (newElement);
		if ( pPos ) {
			*pPos = pos;
		}
		return TRUE;
	}
	catch ( CMemoryException *pEx ) {
		TRACE(_T("CStringList::AddTail failed.\n"));
		pEx->Delete ();
	}
	return FALSE;
}

BOOL CStringListOk::AddHead (const CString& newElement, POSITION *pPos /* = NULL */)
{
	try {
		POSITION pos = CStringList::AddHead (newElement);
		if ( pPos ) {
			*pPos = pos;
		}
		return TRUE;
	}
	catch ( CMemoryException *pEx ) {
		TRACE(_T("CStringList::AddHead failed.\n"));
		pEx->Delete ();
	}
	return FALSE;
}

BOOL CStringListOk::AddTail (const CString& newElement, POSITION *pPos /* = NULL */)
{
	try {
		POSITION pos = CStringList::AddTail (newElement);
		if ( pPos ) {
			*pPos = pos;
		}
		return TRUE;
	}
	catch ( CMemoryException *pEx ) {
		TRACE(_T("CStringList::AddTail failed.\n"));
		pEx->Delete ();
	}
	return FALSE;
}

BOOL CStringListOk::AddHead (CStringList* pNewList)
{
	try {
		CStringList::AddHead (pNewList);
		return TRUE;
	}
	catch ( CMemoryException *pEx ) {
		TRACE(_T("CStringList::AddHead failed.\n"));
		pEx->Delete ();
	}
	return FALSE;
}

BOOL CStringListOk::AddTail (CStringList* pNewList)
{
	try {
		CStringList::AddTail (pNewList);
		return TRUE;
	}
	catch ( CMemoryException *pEx ) {
		TRACE(_T("CStringList::AddTail failed.\n"));
		pEx->Delete ();
	}
	return FALSE;
}

BOOL CStringListOk::InsertBefore (POSITION position, LPCTSTR newElement, POSITION *pPos /* = NULL */)
{
	try {
		POSITION pos = CStringList::InsertBefore (position, newElement);
		if ( pPos ) {
			*pPos = pos;
		}
		return TRUE;
	}
	catch ( CMemoryException *pEx ) {
		TRACE(_T("CStringList::InsertBefore failed.\n"));
		pEx->Delete ();
	}
	return FALSE;
}

BOOL CStringListOk::InsertAfter (POSITION position, LPCTSTR newElement, POSITION *pPos /* = NULL */)
{
	try {
		POSITION pos = CStringList::InsertAfter (position, newElement);
		if ( pPos ) {
			*pPos = pos;
		}
		return TRUE;
	}
	catch ( CMemoryException *pEx ) {
		TRACE(_T("CStringList::InsertAfter failed.\n"));
		pEx->Delete ();
	}
	return FALSE;
}

BOOL CStringListOk::InsertBefore (POSITION position, const CString& newElement, POSITION *pPos /* = NULL */)
{
	try {
		POSITION pos = CStringList::InsertBefore (position, newElement);
		if ( pPos ) {
			*pPos = pos;
		}
		return TRUE;
	}
	catch ( CMemoryException *pEx ) {
		TRACE(_T("CStringList::InsertBefore failed.\n"));
		pEx->Delete ();
	}
	return FALSE;
}

BOOL CStringListOk::InsertAfter (POSITION position, const CString& newElement, POSITION *pPos /* = NULL */)
{
	try {
		POSITION pos = CStringList::InsertAfter (position, newElement);
		if ( pPos ) {
			*pPos = pos;
		}
		return TRUE;
	}
	catch ( CMemoryException *pEx ) {
		TRACE(_T("CStringList::InsertAfter failed.\n"));
		pEx->Delete ();
	}
	return FALSE;
}

CStringListOk::~CStringListOk ()
{
}

/*=============================================================================
 * THE BASE CLASSES OF INFISCRIPT SIB OBJECTS
 *============================================================================*/
IMPLEMENT_DYNAMIC(CPtrArrayOk,CPtrArray)

CPtrArrayOk::CPtrArrayOk ()
{
}

BOOL CPtrArrayOk::SetSize (int nNewSize, int nGrowBy)
{
	try {
		CPtrArray::SetSize (nNewSize, nGrowBy);
	}
	catch ( CMemoryException *pEx ) {
		TRACE(_T("CPtrArrayOk::SetSize failed.\n"));
		pEx->Delete ();
		return FALSE;
	}
	return TRUE;
}

void * CPtrArrayOk::GetAt (int nIndex) const
{
	ASSERT((nIndex >= 0) && (nIndex < m_nSize));
	if ( (nIndex < 0) || (nIndex >= m_nSize) ) {
		return NULL;
	}
	return (void *) CPtrArray::GetAt (nIndex);
}

BOOL CPtrArrayOk::SetAt (int nIndex, void* newElement)
{
	ASSERT((nIndex >= 0) && (nIndex < m_nSize));
	if ( (nIndex >= 0) && (nIndex < m_nSize) ) {
		CPtrArray::SetAt (nIndex, newElement);
		return TRUE;
	}
	return FALSE;
}

int CPtrArrayOk::Find (void * pElement) const
{
	ASSERT(pElement);
	for ( int i = 0; i < m_nSize; i++ ) {
		void *pPtr = GetAt (i);
		if ( pPtr == pElement ) {
			return i;
		}
	}
	return -1;
}

BOOL CPtrArrayOk::SetAtGrow (int nIndex, void* newElement)
{
	ASSERT(nIndex >= 0);
	if ( nIndex >= 0 ) {
		try {
			CPtrArray::SetAtGrow (nIndex, newElement);
			return TRUE;
		}
		catch ( CMemoryException *pEx ) {
			TRACE(_T("CPtrArrayOk::SetAtGrow failed.\n"));
			pEx->Delete ();
		}
	}
	return FALSE;
}

int CPtrArrayOk::Append (const CPtrArrayOk& src)
{
	try {
		int nOldSize = CPtrArray::Append (src);
		return nOldSize;
	}
	catch ( CMemoryException *pEx ) {
		TRACE(_T("CPtrArrayOk::Append failed.\n"));
		pEx->Delete ();
	}
	return -1;
}

BOOL CPtrArrayOk::Copy (const CPtrArrayOk& src)
{
	try {
		CPtrArray::Copy (src);
		return TRUE;
	}
	catch ( CMemoryException *pEx ) {
		TRACE(_T("CPtrArrayOk::Copy failed.\n"));
		pEx->Delete ();
	}
	return FALSE;
}

BOOL CPtrArrayOk::InsertAt (int nIndex, void* newElement, int nCount)
{
	ASSERT(nIndex >= 0);    // will expand to meet need
	ASSERT(nCount > 0);     // zero or negative size not allowed

	try {
		CPtrArray::InsertAt (nIndex, newElement, nCount);
		return TRUE;
	}
	catch ( CMemoryException *pEx ) {
		TRACE(_T("CPtrArrayOk::InsertAt failed.\n"));
		pEx->Delete ();
	}
	return FALSE;
}

BOOL CPtrArrayOk::InsertAt (int nStartIndex, CPtrArrayOk* pNewArray)
{
	ASSERT(pNewArray != NULL);
	ASSERT(nStartIndex >= 0);
	if ( pNewArray && (nStartIndex >= 0) ) {
		try {
			CPtrArray::InsertAt (nStartIndex, pNewArray);
			return TRUE;
		}
		catch ( CMemoryException *pEx ) {
			TRACE(_T("CPtrArrayOk::InsertAt failed.\n"));
			pEx->Delete ();
		}
	}
	return FALSE;
}

BOOL CPtrArrayOk::RemoveAt (int nIndex, int nCount)
{
	ASSERT(nIndex >= 0);
	ASSERT(nCount >= 0);
	ASSERT(nIndex + nCount <= m_nSize);

	if ( (nIndex >= 0) && ((nIndex + nCount) <= m_nSize) ) {
		CPtrArray::RemoveAt (nIndex, nCount);
		return TRUE;
	}
	return FALSE;
}

BOOL CPtrArrayOk::Remove (void* pElement)
{
	int nIndex = Find (pElement);
	if ( nIndex != -1 ) {
		return RemoveAt (nIndex);
	}
	return FALSE;
}

IMPLEMENT_SERIAL(CObArrayOk,CObArray,0)

CObArrayOk::CObArrayOk ()
{
}

BOOL CObArrayOk::SetSize (int nNewSize, int nGrowBy)
{
	try {
		CObArray::SetSize (nNewSize, nGrowBy);
	}
	catch ( CMemoryException *pEx ) {
		TRACE(_T("CObArrayOk::SetSize failed.\n"));
		pEx->Delete ();
		return FALSE;
	}
	return TRUE;
}

CObject * CObArrayOk::GetAt (int nIndex) const
{
	ASSERT((nIndex >= 0) && (nIndex < m_nSize));
	if ( (nIndex < 0) || (nIndex >= m_nSize) ) {
		return NULL;
	}
	return (CObject *) CObArray::GetAt (nIndex);
}

BOOL CObArrayOk::SetAt (int nIndex, CObject* newElement)
{
	ASSERT((nIndex >= 0) && (nIndex < m_nSize));
	if ( (nIndex >= 0) && (nIndex < m_nSize) ) {
		CObArray::SetAt (nIndex, newElement);
		return TRUE;
	}
	return FALSE;
}

int CObArrayOk::Find (CObject* pElement) const
{
	ASSERT(pElement);
	for ( int i = 0; i < m_nSize; i++ ) {
		CObject *pObject = GetAt (i);
		if ( pObject == pElement ) {
			return i;
		}
	}
	return -1;
}

BOOL CObArrayOk::SetAtGrow (int nIndex, CObject* newElement)
{
	ASSERT(nIndex >= 0);
	if ( nIndex >= 0 ) {
		try {
			CObArray::SetAtGrow (nIndex, newElement);
			return TRUE;
		}
		catch ( CMemoryException *pEx ) {
			TRACE(_T("CObArrayOk::SetAtGrow failed.\n"));
			pEx->Delete ();
		}
	}
	return FALSE;
}

int CObArrayOk::Append (const CObArrayOk& src)
{
	try {
		int nOldSize = CObArray::Append (src);
		return nOldSize;
	}
	catch ( CMemoryException *pEx ) {
		TRACE(_T("CObArrayOk::Append failed.\n"));
		pEx->Delete ();
	}
	return -1;
}

BOOL CObArrayOk::Copy (const CObArrayOk& src)
{
	try {
		CObArray::Copy (src);
		return TRUE;
	}
	catch ( CMemoryException *pEx ) {
		TRACE(_T("CObArrayOk::Copy failed.\n"));
		pEx->Delete ();
	}
	return FALSE;
}

BOOL CObArrayOk::InsertAt (int nIndex, CObject* newElement, int nCount)
{
	ASSERT(nIndex >= 0);    // will expand to meet need
	ASSERT(nCount > 0);     // zero or negative size not allowed

	try {
		CObArray::InsertAt (nIndex, newElement, nCount);
		return TRUE;
	}
	catch ( CMemoryException *pEx ) {
		TRACE(_T("CObArrayOk::InsertAt failed.\n"));
		pEx->Delete ();
	}
	return FALSE;
}

BOOL CObArrayOk::InsertAt (int nStartIndex, CObArrayOk* pNewArray)
{
	ASSERT(pNewArray != NULL);
	ASSERT(nStartIndex >= 0);
	if ( pNewArray && (nStartIndex >= 0) ) {
		try {
			CObArray::InsertAt (nStartIndex, pNewArray);
			return TRUE;
		}
		catch ( CMemoryException *pEx ) {
			TRACE(_T("CObArrayOk::InsertAt failed.\n"));
			pEx->Delete ();
		}
	}
	return FALSE;
}

BOOL CObArrayOk::RemoveAt (int nIndex, int nCount)
{
	ASSERT(nIndex >= 0);
	ASSERT(nCount >= 0);
	ASSERT(nIndex + nCount <= m_nSize);

	if ( (nIndex >= 0) && ((nIndex + nCount) <= m_nSize) ) {
		CObArray::RemoveAt (nIndex, nCount);
		return TRUE;
	}
	return FALSE;
}

BOOL CObArrayOk::Remove (CObject* pElement)
{
	int nIndex = Find (pElement);
	if ( nIndex != -1 ) {
		return RemoveAt (nIndex);
	}
	return FALSE;
}

/*=============================================================================
 * THE MAP CLASSES
 *============================================================================*/
CMapPtrToPtrOk::CMapPtrToPtrOk (int nBlockSize /* = 10 */) : CMapPtrToPtr (nBlockSize)
{
}

BOOL CMapPtrToPtrOk::SetAt (void* key, void* newValue)
{
	try {
		CMapPtrToPtr::SetAt (key, newValue);
		return TRUE;
	}
	catch ( CMemoryException *pEx ) {
		pEx->Delete ();
		return FALSE;
	}
}

inline UINT CMapPtrToPtrOk::HashKey(void* key) const
{
	// default identity hash - works for most primitive values
	return ((UINT)(void*)(DWORD)key) >> 4;
}


CMapStringToPtrOk::CMapStringToPtrOk (int nBlockSize /* = 10 */) : CMapStringToPtr (nBlockSize)
{
}

BOOL CMapStringToPtrOk::SetAt (LPCTSTR key, void* newValue)
{
	try {
		CMapStringToPtr::SetAt (key, newValue);
		return TRUE;
	}
	catch ( CMemoryException *pEx ) {
		pEx->Delete ();
		return FALSE;
	}
}

inline UINT CMapStringToPtrOk::HashKey(LPCTSTR key) const
{
	UINT nHash = 0;
	while ( *key ) {
		nHash = (nHash << 5) + nHash + *key++;
	}
	return nHash;
}

//
// EoF
////////
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
 * FILENAME		:	yMfcUtil.h
 * PURPOSE		:	Definition of better collection classes
 * SCOPE		:	YeaSoft MFC GUI Library
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/
#ifndef __yCollection_h__
#define __yCollection_h__

/*=============================================================================
 * RELATED INCLUDES
 *============================================================================*/
#ifndef __AFXTEMPL_H__
#include <afxtempl.h>
#endif

/*=============================================================================
 * DLL LINKAGE STUFF
 *============================================================================*/
#ifndef YEAUTIL_EXT_CLASS
#define YEAUTIL_EXT_CLASS __declspec(dllimport)
#endif

/*=============================================================================
 * THE LIST CLASSES
 *============================================================================*/
class YEAUTIL_EXT_CLASS CPtrListOk : protected CPtrList
{
// Construction
public:
	CPtrListOk					(int nBlockSize = 10) : CPtrList (nBlockSize) { }

// Attributes (head and tail)
public:
	// count of elements
	int							GetCount				() const { return CPtrList::GetCount (); }
	BOOL						IsEmpty					() const { return CPtrList::IsEmpty (); }

	// peek at head or tail
	void *&						GetHead					() { return CPtrList::GetHead (); }
	void *						GetHead					() const { return CPtrList::GetHead (); }
	void *&						GetTail					() { return CPtrList::GetTail (); }
	void *						GetTail					() const { return CPtrList::GetTail (); }

// Operations
public:
	// get head or tail (and remove it) - don't call on empty list!
	void *						RemoveHead				() { return CPtrList::RemoveHead (); }
	void *						RemoveTail				() { return CPtrList::RemoveTail (); }

	// add before head or after tail
	BOOL						AddHead					(void * newElement, POSITION *pPos = NULL);
	BOOL						AddTail					(void * newElement, POSITION *pPos = NULL);


	// add another list of elements before head or after tail
	BOOL						AddHead					(CPtrList * pNewList);
	BOOL						AddTail					(CPtrList * pNewList);

	// remove all elements
	void						RemoveAll				() { CPtrList::RemoveAll (); }

	// iteration
	POSITION					GetHeadPosition			() const { return CPtrList::GetHeadPosition (); }
	POSITION					GetTailPosition			() const { return CPtrList::GetTailPosition (); }
	void *&						GetNext					(POSITION& rPosition) { return CPtrList::GetNext (rPosition); } // return *Position++
	void *						GetNext					(POSITION& rPosition) const { return CPtrList::GetNext (rPosition); } // return *Position++
	void *&						GetPrev					(POSITION& rPosition) { return CPtrList::GetPrev (rPosition); } // return *Position--
	void *						GetPrev					(POSITION& rPosition) const { return CPtrList::GetPrev (rPosition); } // return *Position--

	// getting/modifying an element at a given position
	void *&						GetAt					(POSITION position) { return CPtrList::GetAt (position); }
	void *						GetAt					(POSITION position) const { return CPtrList::GetAt (position); }
	void						SetAt					(POSITION pos, void * newElement) { CPtrList::SetAt (pos, newElement); }

	void						RemoveAt				(POSITION position) { CPtrList::RemoveAt (position); }

	// inserting before or after a given position
	BOOL						InsertBefore			(POSITION position, void * newElement, POSITION *pPos = NULL);
	BOOL						InsertAfter				(POSITION position, void * newElement, POSITION *pPos = NULL);


	// helper functions (note: O(n) speed)
	POSITION					Find					(void * searchValue, POSITION startAfter = NULL) const { return CPtrList::Find (searchValue, startAfter); }
								// defaults to starting at the HEAD
								// return NULL if not found
	POSITION					FindIndex				(int nIndex) const { return CPtrList::FindIndex (nIndex); }
								// get the 'nIndex'th element (may return NULL)

// Implementation
public:
#ifdef _DEBUG
	void						Dump					(CDumpContext &dc) const { CPtrList::Dump (dc); }
	void						AssertValid				() const { CPtrList::AssertValid (); }
#endif

	DECLARE_DYNAMIC(CPtrListOk)
};

class YEAUTIL_EXT_CLASS CObListOk : protected CObList
{
// Construction
public:
	CObListOk					(int nBlockSize = 10) : CObList (nBlockSize) { }

// Attributes (head and tail)
public:
	// count of elements
	int							GetCount				() const { return CObList::GetCount (); }
	BOOL						IsEmpty					() const { return CObList::IsEmpty (); }

	// peek at head or tail
	CObject *&					GetHead					() { return CObList::GetHead (); }
	CObject *					GetHead					() const { return CObList::GetHead (); }
	CObject *&					GetTail					() { return CObList::GetTail (); }
	CObject *					GetTail					() const { return CObList::GetTail (); }

// Operations
public:
	// get head or tail (and remove it) - don't call on empty list!
	CObject *					RemoveHead				() { return CObList::RemoveHead (); }
	CObject *					RemoveTail				() { return CObList::RemoveTail (); }

	// add before head or after tail
	BOOL						AddHead					(CObject * newElement, POSITION *pPos = NULL);
	BOOL						AddTail					(CObject * newElement, POSITION *pPos = NULL);


	// add another list of elements before head or after tail
	BOOL						AddHead					(CObList * pNewList);
	BOOL						AddTail					(CObList * pNewList);

	// remove all elements
	void						RemoveAll				() { CObList::RemoveAll (); }

	// iteration
	POSITION					GetHeadPosition			() const { return CObList::GetHeadPosition (); }
	POSITION					GetTailPosition			() const { return CObList::GetTailPosition (); }
	CObject *&					GetNext					(POSITION& rPosition) { return CObList::GetNext (rPosition); } // return *Position++
	CObject *					GetNext					(POSITION& rPosition) const { return CObList::GetNext (rPosition); } // return *Position++
	CObject *&					GetPrev					(POSITION& rPosition) { return CObList::GetPrev (rPosition); } // return *Position--
	CObject *					GetPrev					(POSITION& rPosition) const { return CObList::GetPrev (rPosition); } // return *Position--

	// getting/modifying an element at a given position
	CObject *&					GetAt					(POSITION position) { return CObList::GetAt (position); }
	CObject *					GetAt					(POSITION position) const { return CObList::GetAt (position); }
	void						SetAt					(POSITION pos, CObject * newElement) { CObList::SetAt (pos, newElement); }

	void						RemoveAt				(POSITION position) { CObList::RemoveAt (position); }

	// inserting before or after a given position
	BOOL						InsertBefore			(POSITION position, CObject * newElement, POSITION *pPos = NULL);
	BOOL						InsertAfter				(POSITION position, CObject * newElement, POSITION *pPos = NULL);


	// helper functions (note: O(n) speed)
	POSITION					Find					(CObject * searchValue, POSITION startAfter = NULL) const { return CObList::Find (searchValue, startAfter); }
								// defaults to starting at the HEAD
								// return NULL if not found
	POSITION					FindIndex				(int nIndex) const { return CObList::FindIndex (nIndex); }
								// get the 'nIndex'th element (may return NULL)

// Implementation
public:
	~CObListOk					();

	void						Serialize				(CArchive &ar) { CObList::Serialize (ar); }

#ifdef _DEBUG
	void						Dump					(CDumpContext &dc) const { CObList::Dump (dc); }
	void						AssertValid				() const { CObList::AssertValid (); }
#endif

	DECLARE_SERIAL(CObListOk)
};

class YEAUTIL_EXT_CLASS CStringListOk : protected CStringList
{
// Construction
public:
	CStringListOk				(int nBlockSize = 10) : CStringList (nBlockSize) { }

// Attributes (head and tail)
public:
	// count of elements
	int							GetCount				() const { return CStringList::GetCount (); }
	BOOL						IsEmpty					() const { return CStringList::IsEmpty (); }

	// peek at head or tail
	CString &					GetHead					() { return CStringList::GetHead (); }
	CString						GetHead					() const { return CStringList::GetHead (); }
	CString &					GetTail					() { return CStringList::GetTail (); }
	CString						GetTail					() const { return CStringList::GetTail (); }

// Operations
	// get head or tail (and remove it) - don't call on empty list!
	CString						RemoveHead				() { return CStringList::RemoveHead (); }
	CString						RemoveTail				() { return CStringList::RemoveTail (); }

	// add before head or after tail
	BOOL						AddHead					(LPCTSTR newElement, POSITION *pPos = NULL);
	BOOL						AddTail					(LPCTSTR newElement, POSITION *pPos = NULL);

	BOOL						AddHead					(const CString& newElement, POSITION *pPos = NULL);
	BOOL						AddTail					(const CString& newElement, POSITION *pPos = NULL);

	// add another list of elements before head or after tail
	BOOL						AddHead					(CStringList* pNewList);
	BOOL						AddTail					(CStringList* pNewList);

	// remove all elements
	void						RemoveAll				() { CStringList::RemoveAll (); }

	// iteration
	POSITION					GetHeadPosition			() const { return CStringList::GetHeadPosition (); }
	POSITION					GetTailPosition			() const { return CStringList::GetTailPosition (); }
	CString &					GetNext					(POSITION& rPosition) { return CStringList::GetNext (rPosition); } // return *Position++
	CString						GetNext					(POSITION& rPosition) const { return CStringList::GetNext (rPosition); } // return *Position++
	CString &					GetPrev					(POSITION& rPosition) { return CStringList::GetPrev (rPosition); } // return *Position--
	CString						GetPrev					(POSITION& rPosition) const { return CStringList::GetPrev (rPosition); } // return *Position--

	// getting/modifying an element at a given position
	CString &					GetAt					(POSITION position) { return CStringList::GetAt (position); }
	CString						GetAt					(POSITION position) const { return CStringList::GetAt (position); }
	void						SetAt					(POSITION pos, LPCTSTR newElement) { CStringList::SetAt (pos, newElement); }
	void						SetAt					(POSITION pos, const CString& newElement) { CStringList::SetAt (pos, newElement); }

	void						RemoveAt				(POSITION position) { CStringList::RemoveAt (position); }

	// inserting before or after a given position
	BOOL						InsertBefore			(POSITION position, LPCTSTR newElement, POSITION *pPos = NULL);
	BOOL						InsertAfter				(POSITION position, LPCTSTR newElement, POSITION *pPos = NULL);

	BOOL						InsertBefore			(POSITION position, const CString& newElement, POSITION *pPos = NULL);
	BOOL						InsertAfter				(POSITION position, const CString& newElement, POSITION *pPos = NULL);


	// helper functions (note: O(n) speed)
	POSITION					Find					(LPCTSTR searchValue, POSITION startAfter = NULL) const { return CStringList::Find (searchValue, startAfter); }
						// defaults to starting at the HEAD
						// return NULL if not found
	POSITION					FindIndex				(int nIndex) const { return CStringList::FindIndex (nIndex); }
						// get the 'nIndex'th element (may return NULL)


public:
	~CStringListOk				();

	void						Serialize				(CArchive &ar) { CStringList::Serialize (ar); }

	DECLARE_SERIAL(CStringListOk)
};

/*=============================================================================
 * THE ARRAY CLASSES
 *============================================================================*/
class YEAUTIL_EXT_CLASS CPtrArrayOk : protected CPtrArray
{
public:
	// construction
	CPtrArrayOk					();

public:
	// attributes
	int							GetSize					() const { return CPtrArray::GetSize (); }
	int							GetUpperBound			() const { return CPtrArray::GetUpperBound (); }
	BOOL						SetSize					(int nNewSize, int nGrowBy = -1);

public:
	// operations

	// Clean up
	void						FreeExtra				() { CPtrArray::FreeExtra (); }
	void						RemoveAll				() { CPtrArray::RemoveAll (); }

	// Accessing elements
	void *						GetAt					(int nIndex) const;
	BOOL						SetAt					(int nIndex, void * newElement);

	void *&						ElementAt				(int nIndex) { return (void *&) CPtrArray::ElementAt (nIndex); }

	// Searching
	int							Find					(void * pElement) const;

	// Direct Access to the element data (may return NULL)
	const void **				GetData					() const { return (const void **) CPtrArray::GetData (); }
	void **						GetData					() { return (void **) CPtrArray::GetData (); }

	// Potentially growing the array
	BOOL						SetAtGrow				(int nIndex, void* newElement);
	BOOL						Add						(void* newElement) { return SetAtGrow (m_nSize, newElement); }
	int							Append					(const CPtrArrayOk & src);
	BOOL						Copy					(const CPtrArrayOk & src);

	// overloaded operator helpers
	void *						operator[]				(int nIndex) const { return GetAt (nIndex); }
	void *&						operator[]				(int nIndex) { return ElementAt (nIndex); }

	// Operations that move elements around
	BOOL						InsertAt				(int nIndex, void* newElement, int nCount = 1);
	BOOL						InsertAt				(int nStartIndex, CPtrArrayOk * pNewArray);
	BOOL						RemoveAt				(int nIndex, int nCount = 1);
	BOOL						Remove					(void* pElement);

public:
	// overrides
	void						Serialize				(CArchive &ar) { CPtrArray::Serialize (ar); }
#ifdef _DEBUG
	void						Dump					(CDumpContext &dc) const { CPtrArray::Dump (dc); }
	void						AssertValid				() const  { CPtrArray::AssertValid (); }
#endif

	DECLARE_DYNAMIC				(CPtrArrayOk)
};

class YEAUTIL_EXT_CLASS CObArrayOk : protected CObArray
{
public:
	// construction
	CObArrayOk					();

public:
	// attributes
	int							GetSize					() const { return CObArray::GetSize (); }
	int							GetUpperBound			() const { return CObArray::GetUpperBound (); }
	BOOL						SetSize					(int nNewSize, int nGrowBy = -1);

public:
	// operations

	// Clean up
	void						FreeExtra				() { CObArray::FreeExtra (); }
	void						RemoveAll				() { CObArray::RemoveAll (); }

	// Accessing elements
	CObject *					GetAt					(int nIndex) const;
	BOOL						SetAt					(int nIndex, CObject* newElement);

	CObject *&					ElementAt				(int nIndex) { return (CObject *&) CObArray::ElementAt (nIndex); }

	// Searching
	int							Find					(CObject* pElement) const;

	// Direct Access to the element data (may return NULL)
	const CObject **			GetData					() const { return (const CObject **) CObArray::GetData (); }
	CObject **					GetData					() { return (CObject **) CObArray::GetData (); }

	// Potentially growing the array
	BOOL						SetAtGrow				(int nIndex, CObject* newElement);
	BOOL						Add						(CObject* newElement) { return SetAtGrow (m_nSize, newElement); }
	int							Append					(const CObArrayOk& src);
	BOOL						Copy					(const CObArrayOk& src);

	// overloaded operator helpers
	CObject *					operator[]				(int nIndex) const { return GetAt (nIndex); }
	CObject *&					operator[]				(int nIndex) { return ElementAt (nIndex); }

	// Operations that move elements around
	BOOL						InsertAt				(int nIndex, CObject* newElement, int nCount = 1);
	BOOL						InsertAt				(int nStartIndex, CObArrayOk* pNewArray);
	BOOL						RemoveAt				(int nIndex, int nCount = 1);
	BOOL						Remove					(CObject* pElement);

public:
	// overrides
	void						Serialize				(CArchive &ar) { CObArray::Serialize (ar); }
#ifdef _DEBUG
	void						Dump					(CDumpContext &dc) const { CObArray::Dump (dc); }
	void						AssertValid				() const  { CObArray::AssertValid (); }
#endif

	DECLARE_SERIAL				(CObArrayOk)
};

/*=============================================================================
 * THE MAP CLASSES
 *============================================================================*/
class YEAUTIL_EXT_CLASS CMapPtrToPtrOk : protected CMapPtrToPtr
{
public:
	// construction
	CMapPtrToPtrOk				(int nBlockSize = 10);

public:
	// attributes
	// number of elements
	int							GetCount				() const { return CMapPtrToPtr::GetCount (); }
	BOOL						IsEmpty					() const { return CMapPtrToPtr::IsEmpty (); }

	// Lookup
	BOOL						Lookup					(void* key, void*& rValue) const { return CMapPtrToPtr::Lookup (key, rValue); }

public:
	// operations
	// Lookup and add if not there
	// NO ERROR CHECKING POSSIBLE - REMOVE! - Use Lookup and SetAt!
	// void*&						operator[]				(void* key);

	// add a new (key, value) pair
	BOOL						SetAt					(void* key, void* newValue);

	// removing existing (key, ?) pair
	BOOL						RemoveKey				(void* key) { return CMapPtrToPtr::RemoveKey (key); }
	void						RemoveAll				() { CMapPtrToPtr::RemoveAll (); }

	// iterating all (key, value) pairs
	POSITION					GetStartPosition		() const { return CMapPtrToPtr::GetStartPosition (); }
	void						GetNextAssoc			(POSITION& rNextPosition, void*& rKey, void*& rValue) const { CMapPtrToPtr::GetNextAssoc (rNextPosition, rKey, rValue); }

	// advanced features for derived classes
	UINT						GetHashTableSize		() const { return CMapPtrToPtr::GetHashTableSize (); }
	void						InitHashTable			(UINT hashSize, BOOL bAllocNow = TRUE) { CMapPtrToPtr::InitHashTable (hashSize, bAllocNow); }

// Overridables: special non-virtual (see map implementation for details)
	// Routine used to user-provided hash keys
	UINT						HashKey					(void* key) const;
};

class YEAUTIL_EXT_CLASS CMapStringToPtrOk : protected CMapStringToPtr
{
public:
	// construction
	CMapStringToPtrOk			(int nBlockSize = 10);

public:
	// attributes
	int							GetCount				() const { return CMapStringToPtr::GetCount (); }
	BOOL						IsEmpty					() const { return CMapStringToPtr::IsEmpty (); }

	// Lookup
	BOOL						Lookup					(LPCTSTR key, void*& rValue) const { return CMapStringToPtr::Lookup (key, rValue); }
	BOOL						LookupKey				(LPCTSTR key, LPCTSTR& rKey) const { return CMapStringToPtr::LookupKey (key, rKey); }

public:
	// operations
	// Lookup and add if not there
	// NO ERROR CHECKING POSSIBLE - REMOVE! - Use Lookup and SetAt!
	//void *&						operator[]				(LPCTSTR key);

	// add a new (key, value) pair
	BOOL						SetAt					(LPCTSTR key, void* newValue);

	// removing existing (key, ?) pair
	BOOL						RemoveKey				(LPCTSTR key) { return CMapStringToPtr::RemoveKey (key); }
	void						RemoveAll				() { CMapStringToPtr::RemoveAll (); }

	// iterating all (key, value) pairs
	POSITION					GetStartPosition		() const { return CMapStringToPtr::GetStartPosition (); }
	void						GetNextAssoc			(POSITION& rNextPosition, CString& rKey, void*& rValue) const { CMapStringToPtr::GetNextAssoc (rNextPosition, rKey, rValue); }

	// advanced features for derived classes
	UINT						GetHashTableSize		() const { return CMapStringToPtr::GetHashTableSize (); }
	void						InitHashTable			(UINT hashSize, BOOL bAllocNow = TRUE) { CMapStringToPtr::InitHashTable (hashSize, bAllocNow); }

// Overridables: special non-virtual (see map implementation for details)
	// Routine used to user-provided hash keys
	UINT						HashKey					(LPCTSTR key) const;
};

/*=============================================================================
 * USEFUL TEMPLATES
 *============================================================================*/
template<class BASE_CLASS, class TYPE>
class CTypedPtrListOk : public _CTypedPtrList<BASE_CLASS, TYPE>
{
public:
	CTypedPtrListOk				(int nBlockSize = 10) : _CTypedPtrList<BASE_CLASS, TYPE>(nBlockSize) { }

	// add before head or after tail
	BOOL						AddHead					(TYPE newElement, POSITION *pPos = NULL) { return BASE_CLASS::AddHead (newElement, pPos); }
	BOOL						AddTail					(TYPE newElement, POSITION *pPos = NULL) { return BASE_CLASS::AddTail (newElement, pPos); }

	// add another list of elements before head or after tail
	BOOL						AddHead					(CTypedPtrList<BASE_CLASS, TYPE>* pNewList) { return BASE_CLASS::AddHead(pNewList); }
	BOOL						AddTail					(CTypedPtrList<BASE_CLASS, TYPE>* pNewList) { return BASE_CLASS::AddTail(pNewList); }
};

template<class BASE_CLASS, class TYPE>
class CTypedPtrArrayOk : public BASE_CLASS
{
public:
	// Accessing elements
	TYPE						GetAt					(int nIndex) const { return (TYPE) BASE_CLASS::GetAt (nIndex); }
	TYPE &						ElementAt				(int nIndex) { return (TYPE &) BASE_CLASS::ElementAt (nIndex); }
	BOOL						SetAt					(int nIndex, TYPE ptr) { return BASE_CLASS::SetAt (nIndex, ptr); }

	// Searching
	int							Find					(TYPE ptr) const { return BASE_CLASS::Find (ptr); }
	int							Find					(DWORD dwSlpID, TYPE *pFoundItem = NULL) const { return BASE_CLASS::Find (dwSlpID, pFoundItem); }
	int							Find					(LPCTSTR pszIdentifier, TYPE *pFoundItem = NULL) const { return BASE_CLASS::Find (pszIdentifier, pFoundItem); }

	// Potentially growing the array
	BOOL						SetAtGrow				(int nIndex, TYPE newElement) { return BASE_CLASS::SetAtGrow (nIndex, newElement); }
	BOOL						Add						(TYPE newElement) { return BASE_CLASS::Add (newElement); }
	int							Append					(const CTypedPtrArrayOk<BASE_CLASS, TYPE>& src) { return BASE_CLASS::Append (src); }
	BOOL						Copy					(const CTypedPtrArrayOk<BASE_CLASS, TYPE>& src) { return BASE_CLASS::Copy (src); }

	// Operations that move elements around
	BOOL						InsertAt				(int nIndex, TYPE newElement, int nCount = 1) { return BASE_CLASS::InsertAt (nIndex, newElement, nCount); }
	BOOL						InsertAt				(int nStartIndex, CTypedPtrArrayOk<BASE_CLASS, TYPE>* pNewArray) { return BASE_CLASS::InsertAt(nStartIndex, pNewArray); }
	BOOL						Remove					(TYPE ptr) { return BASE_CLASS::Remove (ptr); }

	// overloaded operator helpers
	TYPE						operator[]				(int nIndex) const { return (TYPE) BASE_CLASS::operator[] (nIndex); }
	TYPE &						operator[]				(int nIndex) { return (TYPE &) BASE_CLASS::operator[] (nIndex); }
};

template<class TYPE>
class CMapStringToTypedPtr : public CMapStringToPtrOk
{
public:
	// Lookup
	BOOL						Lookup					(LPCTSTR key, TYPE & rValue) const { return CMapStringToPtrOk::Lookup (key, (void *&) rValue); }

	// add a new (key, value) pair
	BOOL						SetAt					(LPCTSTR key, TYPE newValue) { return CMapStringToPtrOk::SetAt (key, (void *) newValue); }

	// iterating all (key, value) pairs
	void						GetNextAssoc			(POSITION& rNextPosition, CString& rKey, TYPE & rValue) const { CMapStringToPtrOk::GetNextAssoc (rNextPosition, rKey, (void *&) rValue); }
};

template<class KEYTYPE, class TYPE>
class CMapIntValToTypedPtr : public CMapPtrToPtrOk
{
public:
	// Lookup
	BOOL						Lookup					(KEYTYPE key, TYPE & rValue) const { return CMapPtrToPtrOk::Lookup ((void *) key, (void *&) rValue); }

public:
	// add a new (key, value) pair
	BOOL						SetAt					(KEYTYPE key, TYPE newValue) { return CMapPtrToPtrOk::SetAt ((void *) key, (void *) newValue); }

	// removing existing (key, ?) pair
	BOOL						RemoveKey				(KEYTYPE key) { return CMapPtrToPtrOk::RemoveKey ((void *) key); }

	// iterating all (key, value) pairs
	void						GetNextAssoc			(POSITION& rNextPosition, KEYTYPE & rKey, TYPE & rValue) const { CMapPtrToPtrOk::GetNextAssoc ((void *&) rNextPosition, rKey, (void *&) rValue); }

// Overridables: special non-virtual (see map implementation for details)
	// Routine used to user-provided hash keys
	UINT						HashKey					(KEYTYPE key) const { return CMapPtrToPtrOk::HashKey ((void *) key); }
};


// template class for an array of specific allocated objects
template<class BASE_CLASS, class TYPE, class CREATIONTYPE>
class CTypedAllocatedPtrArray : public BASE_CLASS
{
public:
	// Assignment and destruction
	const CTypedAllocatedPtrArray<BASE_CLASS, TYPE, CREATIONTYPE> &operator= (const CTypedAllocatedPtrArray<BASE_CLASS, TYPE, CREATIONTYPE> &valueSrc) { Assign (valueSrc); return *this; }
	BOOL						Assign					(const CTypedAllocatedPtrArray<BASE_CLASS, TYPE, CREATIONTYPE> &valueSrc);
	void						RemoveAll				();

	// Accessing elements
	TYPE						GetAt					(int nIndex) const { return (TYPE) BASE_CLASS::GetAt (nIndex); }
	TYPE &						ElementAt				(int nIndex) { return (TYPE &) BASE_CLASS::ElementAt (nIndex); }
	BOOL						SetAt					(int nIndex, TYPE ptr) { return BASE_CLASS::SetAt (nIndex, ptr); }

	// Searching
	int							Find					(TYPE ptr) const { return BASE_CLASS::Find (ptr); }
	int							Find					(DWORD dwSlpID, TYPE *pFoundItem = NULL) const { return BASE_CLASS::Find (dwSlpID, pFoundItem); }
	int							Find					(LPCTSTR pszIdentifier, TYPE *pFoundItem = NULL) const { return BASE_CLASS::Find (pszIdentifier, pFoundItem); }

	// Potentially growing the array
	BOOL						SetAtGrow				(int nIndex, TYPE newElement) { return BASE_CLASS::SetAtGrow (nIndex, newElement); }
	BOOL						Add						(TYPE newElement) { return BASE_CLASS::Add (newElement); }
	int							Append					(const CTypedPtrArrayOk<BASE_CLASS, TYPE>& src) { return BASE_CLASS::Append (src); }
	BOOL						Copy					(const CTypedPtrArrayOk<BASE_CLASS, TYPE>& src) { return BASE_CLASS::Copy (src); }

	// Operations that move elements around
	BOOL						InsertAt				(int nIndex, TYPE newElement, int nCount = 1) { return BASE_CLASS::InsertAt (nIndex, newElement, nCount); }
	BOOL						InsertAt				(int nStartIndex, CTypedPtrArrayOk<BASE_CLASS, TYPE>* pNewArray) { return BASE_CLASS::InsertAt(nStartIndex, pNewArray); }
	BOOL						Remove					(TYPE ptr) { return BASE_CLASS::Remove (ptr); }

	// overloaded operator helpers
	TYPE						operator[]				(int nIndex) const { return (TYPE) BASE_CLASS::operator[] (nIndex); }
	TYPE &						operator[]				(int nIndex) { return (TYPE &) BASE_CLASS::operator[] (nIndex); }
};

template<class BASE_CLASS, class TYPE, class CREATIONTYPE>
BOOL CTypedAllocatedPtrArray<BASE_CLASS, TYPE, CREATIONTYPE>::Assign (const CTypedAllocatedPtrArray<BASE_CLASS, TYPE, CREATIONTYPE> &valueSrc)
{
	RemoveAll ();

	BOOL	bOK		= TRUE;
	int		iCount	= valueSrc.GetSize ();

	for ( int i = 0; i < iCount; i++ ) {
		TYPE pOldObject = valueSrc.GetAt (i);
		if ( pOldObject ) {
			TYPE pNewObject = new CREATIONTYPE;
			if ( (pNewObject != NULL) && pNewObject->Assign (*pOldObject) ) {
				if ( SetAtGrow (i, pNewObject) ) {
					bOK &= TRUE;
				}
				else {
					delete pNewObject;
					TRACE(_T("Serious Memory Problem\n"));
					ASSERT(FALSE);
					bOK &= FALSE;
				}
			}
			else {
				bOK &= FALSE;
			}
		}
	}
	return bOK != FALSE;
}

template<class BASE_CLASS, class TYPE, class CREATIONTYPE>
void CTypedAllocatedPtrArray<BASE_CLASS, TYPE, CREATIONTYPE>::RemoveAll ()
{
	int iCount = GetSize ();

	for ( int i = 0; i < iCount; i++ ) {
		delete GetAt (i);
	}

	BASE_CLASS::RemoveAll ();
}

template<class TYPE>
class CMapStringToAllocatedPtr : public CMapStringToPtrOk
{
public:
	// Lookup
	BOOL						Lookup					(LPCTSTR key, TYPE & rValue) const { return CMapStringToPtrOk::Lookup (key, (void *&) rValue); }

	// add a new (key, value) pair
	BOOL						SetAt					(LPCTSTR key, TYPE newValue) { return CMapStringToPtrOk::SetAt (key, (void *) newValue); }

	// iterating all (key, value) pairs
	void						GetNextAssoc			(POSITION& rNextPosition, CString& rKey, TYPE & rValue) const { CMapStringToPtrOk::GetNextAssoc (rNextPosition, rKey, (void *&) rValue); }

	void						RemoveAll				();
};

template<class TYPE>
void CMapStringToAllocatedPtr<TYPE>::RemoveAll ()
{
	for ( POSITION pos = GetStartPosition (); pos; /*TUNIX*/ ) {
		TYPE	pFound = NULL;
		CString csFound;
		GetNextAssoc (pos, csFound, pFound);
		if ( pFound ) {
			delete pFound;
		}
	}
	CMapStringToPtrOk::RemoveAll ();
}

#endif //__yCollection_h__
//
// EoF
////////
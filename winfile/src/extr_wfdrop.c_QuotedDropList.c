#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_13__ {int member_3; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_12__ {TYPE_1__* lpVtbl; } ;
struct TYPE_11__ {int /*<<< orphan*/  hGlobal; } ;
struct TYPE_10__ {scalar_t__ (* GetData ) (TYPE_3__*,TYPE_4__*,TYPE_2__*) ;} ;
typedef  TYPE_2__ STGMEDIUM ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  TYPE_3__ IDataObject ;
typedef  int /*<<< orphan*/  HDROP ;
typedef  TYPE_4__ FORMATETC ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CF_HDROP ; 
 void* CHAR_DQUOTE ; 
 int /*<<< orphan*/  CHAR_NULL ; 
 int /*<<< orphan*/  CHAR_SPACE ; 
 int /*<<< orphan*/  DVASPECT_CONTENT ; 
 int DragQueryFile (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  LMEM_FIXED ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ReleaseStgMedium (TYPE_2__*) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TYMED_HGLOBAL ; 
 scalar_t__ stub1 (TYPE_3__*,TYPE_4__*,TYPE_2__*) ; 

LPWSTR QuotedDropList(IDataObject *pDataObject)
{
	HDROP hdrop;
	DWORD cFiles, iFile, cchFiles;
	LPWSTR szFiles = NULL, pch;
	FORMATETC fmtetc = { CF_HDROP, 0, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
	STGMEDIUM stgmed;

	if (pDataObject->lpVtbl->GetData(pDataObject, &fmtetc, &stgmed) == S_OK)
	{
		// Yippie! the data is there, so go get it!
		hdrop = stgmed.hGlobal;

		cFiles = DragQueryFile(hdrop, 0xffffffff, NULL, 0);
		cchFiles = 0;
		for (iFile = 0; iFile < cFiles; iFile++)
			cchFiles += DragQueryFile(hdrop, iFile, NULL, 0) + 1 + 2;

		pch = szFiles = (LPWSTR)LocalAlloc(LMEM_FIXED, cchFiles * sizeof(WCHAR));
		for (iFile = 0; iFile < cFiles; iFile++)
		{
			DWORD cchFile;

			*pch++ = CHAR_DQUOTE;
			
			cchFile = DragQueryFile(hdrop, iFile, pch, cchFiles);
			pch += cchFile;
			*pch++ = CHAR_DQUOTE;

			if (iFile+1 < cFiles)
				*pch++ = CHAR_SPACE;
			else
				*pch = CHAR_NULL;
				
			cchFiles -= cchFile + 1 + 2;
		}

		// release the data using the COM API
		ReleaseStgMedium(&stgmed);
	}

	return szFiles;
}
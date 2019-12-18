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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_13__ {int member_3; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_12__ {TYPE_1__* lpVtbl; } ;
struct TYPE_11__ {int /*<<< orphan*/ * hGlobal; } ;
struct TYPE_10__ {scalar_t__ (* GetData ) (TYPE_3__*,TYPE_4__*,TYPE_2__*) ;} ;
typedef  TYPE_2__ STGMEDIUM ;
typedef  int* LPDWORD ;
typedef  TYPE_3__ IDataObject ;
typedef  TYPE_4__ FORMATETC ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CFSTR_PREFERREDDROPEFFECT ; 
 int DROPEFFECT_COPY ; 
 int DROPEFFECT_MOVE ; 
 int /*<<< orphan*/  DVASPECT_CONTENT ; 
 int* GlobalLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OleGetClipboard (TYPE_3__**) ; 
 int /*<<< orphan*/  RegisterClipboardFormat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseStgMedium (TYPE_2__*) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TYMED_HGLOBAL ; 
 scalar_t__ stub1 (TYPE_3__*,TYPE_4__*,TYPE_2__*) ; 

DWORD 
ReadMoveStatus()
{
	IDataObject *pDataObj;
	FORMATETC fmtetcDrop = { 0, 0, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
	UINT uFormatEffect = RegisterClipboardFormat(CFSTR_PREFERREDDROPEFFECT);
	FORMATETC fmtetcEffect = { uFormatEffect, 0, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
	STGMEDIUM stgmed;
	DWORD dwEffect = DROPEFFECT_COPY;

	OleGetClipboard(&pDataObj);		// pDataObj == NULL if error

	if (pDataObj != NULL && pDataObj->lpVtbl->GetData(pDataObj, &fmtetcEffect, &stgmed) == S_OK && stgmed.hGlobal != NULL)
	{
		LPDWORD lpEffect = GlobalLock(stgmed.hGlobal);
		if (*lpEffect & DROPEFFECT_COPY) dwEffect = DROPEFFECT_COPY;
		if (*lpEffect & DROPEFFECT_MOVE) dwEffect = DROPEFFECT_MOVE;
		GlobalUnlock(stgmed.hGlobal);
		ReleaseStgMedium(&stgmed);
	}

	return dwEffect;
}
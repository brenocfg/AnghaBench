#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* lpVtbl; } ;
struct TYPE_10__ {TYPE_1__ ido; } ;
typedef  TYPE_3__ WF_IDataObject ;
struct TYPE_11__ {int member_3; unsigned short cfFormat; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_2; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_9__ {scalar_t__ (* QueryGetData ) (int /*<<< orphan*/ ,TYPE_4__*) ;} ;
typedef  int /*<<< orphan*/  LPDATAOBJECT ;
typedef  TYPE_4__ FORMATETC ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CFSTR_FILEDESCRIPTOR ; 
 int /*<<< orphan*/  CF_HDROP ; 
 int /*<<< orphan*/  DVASPECT_CONTENT ; 
 unsigned short RegisterClipboardFormat (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TYMED_HGLOBAL ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static BOOL QueryDataObject(WF_IDataObject *pDataObject)
{
	FORMATETC fmtetc = { CF_HDROP, 0, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
    unsigned short cp_format_descriptor = RegisterClipboardFormat(CFSTR_FILEDESCRIPTOR);
    FORMATETC descriptor_format = {0, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL};
	descriptor_format.cfFormat = cp_format_descriptor;

	// does the data object support CF_HDROP using a HGLOBAL?
	return pDataObject->ido.lpVtbl->QueryGetData((LPDATAOBJECT)pDataObject, &fmtetc) == S_OK || 
			pDataObject->ido.lpVtbl->QueryGetData((LPDATAOBJECT)pDataObject, &descriptor_format) == S_OK;
}
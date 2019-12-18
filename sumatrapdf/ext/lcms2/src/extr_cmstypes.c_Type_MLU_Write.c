#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct _cms_typehandler_struct {int dummy; } ;
typedef  size_t cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsUInt16Number ;
struct TYPE_4__ {size_t UsedEntries; int PoolUsed; scalar_t__ MemPool; TYPE_1__* Entries; } ;
typedef  TYPE_2__ cmsMLU ;
typedef  int /*<<< orphan*/  cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
typedef  int /*<<< orphan*/  _cmsTagBase ;
struct TYPE_3__ {size_t Len; size_t StrW; int /*<<< orphan*/  Country; int /*<<< orphan*/  Language; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _cmsWriteUInt16Number (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cmsWriteUInt32Number (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  _cmsWriteWCharArray (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (size_t) ; 

__attribute__((used)) static
cmsBool  Type_MLU_Write(cmsContext ContextID, struct _cms_typehandler_struct* self, cmsIOHANDLER* io, void* Ptr, cmsUInt32Number nItems)
{
    cmsMLU* mlu =(cmsMLU*) Ptr;
    cmsUInt32Number HeaderSize;
    cmsUInt32Number  Len, Offset;
    cmsUInt32Number i;

    if (Ptr == NULL) {

          // Empty placeholder
          if (!_cmsWriteUInt32Number(ContextID, io, 0)) return FALSE;
          if (!_cmsWriteUInt32Number(ContextID, io, 12)) return FALSE;
          return TRUE;
    }

    if (!_cmsWriteUInt32Number(ContextID, io, mlu ->UsedEntries)) return FALSE;
    if (!_cmsWriteUInt32Number(ContextID, io, 12)) return FALSE;

    HeaderSize = 12 * mlu ->UsedEntries + sizeof(_cmsTagBase);

    for (i=0; i < mlu ->UsedEntries; i++) {

        Len    =  mlu ->Entries[i].Len;
        Offset =  mlu ->Entries[i].StrW;

        Len    = (Len * sizeof(cmsUInt16Number)) / sizeof(wchar_t);
        Offset = (Offset * sizeof(cmsUInt16Number)) / sizeof(wchar_t) + HeaderSize + 8;

        if (!_cmsWriteUInt16Number(ContextID, io, mlu ->Entries[i].Language)) return FALSE;
        if (!_cmsWriteUInt16Number(ContextID, io, mlu ->Entries[i].Country))  return FALSE;
        if (!_cmsWriteUInt32Number(ContextID, io, Len)) return FALSE;
        if (!_cmsWriteUInt32Number(ContextID, io, Offset)) return FALSE;
    }

    if (!_cmsWriteWCharArray(ContextID, io, mlu ->PoolUsed / sizeof(wchar_t), (wchar_t*)  mlu ->MemPool)) return FALSE;

    return TRUE;

    cmsUNUSED_PARAMETER(nItems);
    cmsUNUSED_PARAMETER(self);
}
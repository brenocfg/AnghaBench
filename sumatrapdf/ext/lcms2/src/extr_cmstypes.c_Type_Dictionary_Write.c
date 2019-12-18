#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct _cms_typehandler_struct {int dummy; } ;
typedef  int cmsUInt32Number ;
struct TYPE_20__ {int (* Tell ) (int /*<<< orphan*/ ,TYPE_1__*) ;int /*<<< orphan*/  (* Seek ) (int /*<<< orphan*/ ,TYPE_1__*,int) ;} ;
typedef  TYPE_1__ cmsIOHANDLER ;
typedef  int /*<<< orphan*/ * cmsHANDLE ;
struct TYPE_21__ {int /*<<< orphan*/ * DisplayValue; int /*<<< orphan*/ * DisplayName; int /*<<< orphan*/  Value; int /*<<< orphan*/  Name; } ;
typedef  TYPE_2__ cmsDICTentry ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  scalar_t__ cmsBool ;
typedef  int /*<<< orphan*/  _cmsTagBase ;
struct TYPE_22__ {int /*<<< orphan*/  DisplayValue; int /*<<< orphan*/  DisplayName; int /*<<< orphan*/  Value; int /*<<< orphan*/  Name; } ;
typedef  TYPE_3__ _cmsDICarray ;

/* Variables and functions */
 int /*<<< orphan*/  AllocArray (int /*<<< orphan*/ ,TYPE_3__*,int,int) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FreeArray (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WriteOffsetArray (int /*<<< orphan*/ ,TYPE_1__*,TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  WriteOneMLUC (int /*<<< orphan*/ ,struct _cms_typehandler_struct*,TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WriteOneWChar (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _cmsWriteUInt32Number (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 TYPE_2__* cmsDictGetEntryList (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* cmsDictNextEntry (int /*<<< orphan*/ ,TYPE_2__ const*) ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (int) ; 
 int stub1 (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int stub2 (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int stub3 (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,TYPE_1__*,int) ; 

__attribute__((used)) static
cmsBool Type_Dictionary_Write(cmsContext ContextID, struct _cms_typehandler_struct* self, cmsIOHANDLER* io, void* Ptr, cmsUInt32Number nItems)
{
    cmsHANDLE hDict = (cmsHANDLE) Ptr;
    const cmsDICTentry* p;
    cmsBool AnyName, AnyValue;
    cmsUInt32Number i, Count, Length;
    cmsUInt32Number DirectoryPos, CurrentPos, BaseOffset;
   _cmsDICarray a;

    if (hDict == NULL) return FALSE;

    BaseOffset = io ->Tell(ContextID, io) - sizeof(_cmsTagBase);

    // Let's inspect the dictionary
    Count = 0; AnyName = FALSE; AnyValue = FALSE;
    for (p = cmsDictGetEntryList(ContextID, hDict); p != NULL; p = cmsDictNextEntry(ContextID, p)) {

        if (p ->DisplayName != NULL) AnyName = TRUE;
        if (p ->DisplayValue != NULL) AnyValue = TRUE;
        Count++;
    }

    Length = 16;
    if (AnyName)  Length += 8;
    if (AnyValue) Length += 8;

    if (!_cmsWriteUInt32Number(ContextID, io, Count)) return FALSE;
    if (!_cmsWriteUInt32Number(ContextID, io, Length)) return FALSE;

    // Keep starting position of offsets table
    DirectoryPos = io ->Tell(ContextID, io);

    // Allocate offsets array
    if (!AllocArray(ContextID, &a, Count, Length)) goto Error;

    // Write a fake directory to be filled latter on
    if (!WriteOffsetArray(ContextID, io, &a, Count, Length)) goto Error;

    // Write each element. Keep track of the size as well.
    p = cmsDictGetEntryList(ContextID, hDict);
    for (i=0; i < Count; i++) {

        if (!WriteOneWChar(ContextID, io, &a.Name, i,  p ->Name, BaseOffset)) goto Error;
        if (!WriteOneWChar(ContextID, io, &a.Value, i, p ->Value, BaseOffset)) goto Error;

        if (p ->DisplayName != NULL) {
            if (!WriteOneMLUC(ContextID, self, io, &a.DisplayName, i, p ->DisplayName, BaseOffset)) goto Error;
        }

        if (p ->DisplayValue != NULL) {
            if (!WriteOneMLUC(ContextID, self, io, &a.DisplayValue, i, p ->DisplayValue, BaseOffset)) goto Error;
        }

       p = cmsDictNextEntry(ContextID, p);
    }

    // Write the directory
    CurrentPos = io ->Tell(ContextID, io);
    if (!io ->Seek(ContextID, io, DirectoryPos)) goto Error;

    if (!WriteOffsetArray(ContextID, io, &a, Count, Length)) goto Error;

    if (!io ->Seek(ContextID, io, CurrentPos)) goto Error;

    FreeArray(ContextID, &a);
    return TRUE;

Error:
    FreeArray(ContextID, &a);
    return FALSE;

    cmsUNUSED_PARAMETER(nItems);
}
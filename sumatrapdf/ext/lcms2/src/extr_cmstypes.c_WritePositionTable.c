#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct _cms_typehandler_struct {int dummy; } ;
typedef  size_t cmsUInt32Number ;
struct TYPE_12__ {size_t (* Tell ) (int /*<<< orphan*/ ,TYPE_1__*) ;int /*<<< orphan*/  (* Seek ) (int /*<<< orphan*/ ,TYPE_1__*,size_t) ;} ;
typedef  TYPE_1__ cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
typedef  int /*<<< orphan*/  (* PositionTableEntryFn ) (int /*<<< orphan*/ ,struct _cms_typehandler_struct*,TYPE_1__*,void*,size_t,size_t) ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _cmsCalloc (int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  _cmsFree (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  _cmsWriteUInt32Number (int /*<<< orphan*/ ,TYPE_1__*,size_t) ; 
 size_t stub1 (int /*<<< orphan*/ ,TYPE_1__*) ; 
 size_t stub2 (int /*<<< orphan*/ ,TYPE_1__*) ; 
 size_t stub3 (int /*<<< orphan*/ ,TYPE_1__*) ; 
 size_t stub4 (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,TYPE_1__*,size_t) ; 

__attribute__((used)) static
cmsBool WritePositionTable(cmsContext ContextID, struct _cms_typehandler_struct* self,
                               cmsIOHANDLER* io,
                               cmsUInt32Number SizeOfTag,
                               cmsUInt32Number Count,
                               cmsUInt32Number BaseOffset,
                               void *Cargo,
                               PositionTableEntryFn ElementFn)
{
    cmsUInt32Number i;
    cmsUInt32Number DirectoryPos, CurrentPos, Before;
    cmsUInt32Number *ElementOffsets = NULL, *ElementSizes = NULL;

     // Create table
    ElementOffsets = (cmsUInt32Number *) _cmsCalloc(ContextID, Count, sizeof(cmsUInt32Number));
    if (ElementOffsets == NULL) goto Error;

    ElementSizes = (cmsUInt32Number *) _cmsCalloc(ContextID, Count, sizeof(cmsUInt32Number));
    if (ElementSizes == NULL) goto Error;

    // Keep starting position of curve offsets
    DirectoryPos = io ->Tell(ContextID, io);

    // Write a fake directory to be filled latter on
    for (i=0; i < Count; i++) {

        if (!_cmsWriteUInt32Number(ContextID, io, 0)) goto Error;  // Offset
        if (!_cmsWriteUInt32Number(ContextID, io, 0)) goto Error;  // size
    }

    // Write each element. Keep track of the size as well.
    for (i=0; i < Count; i++) {

        Before = io ->Tell(ContextID, io);
        ElementOffsets[i] = Before - BaseOffset;

        // Callback to write...
        if (!ElementFn(ContextID, self, io, Cargo, i, SizeOfTag)) goto Error;

        // Now the size
        ElementSizes[i] = io ->Tell(ContextID, io) - Before;
    }

    // Write the directory
    CurrentPos = io ->Tell(ContextID, io);
    if (!io ->Seek(ContextID, io, DirectoryPos)) goto Error;

    for (i=0; i <  Count; i++) {
        if (!_cmsWriteUInt32Number(ContextID, io, ElementOffsets[i])) goto Error;
        if (!_cmsWriteUInt32Number(ContextID, io, ElementSizes[i])) goto Error;
    }

    if (!io ->Seek(ContextID, io, CurrentPos)) goto Error;

    if (ElementOffsets != NULL) _cmsFree(ContextID, ElementOffsets);
    if (ElementSizes != NULL) _cmsFree(ContextID, ElementSizes);
    return TRUE;

Error:
    if (ElementOffsets != NULL) _cmsFree(ContextID, ElementOffsets);
    if (ElementSizes != NULL) _cmsFree(ContextID, ElementSizes);
    return FALSE;
}
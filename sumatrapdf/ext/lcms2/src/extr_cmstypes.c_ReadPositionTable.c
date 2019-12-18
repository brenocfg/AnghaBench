#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct _cms_typehandler_struct {int dummy; } ;
typedef  int cmsUInt32Number ;
struct TYPE_8__ {int (* Tell ) (int /*<<< orphan*/ ,TYPE_1__*) ;int ReportedSize; int /*<<< orphan*/  (* Seek ) (int /*<<< orphan*/ ,TYPE_1__*,int) ;} ;
typedef  TYPE_1__ cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
typedef  int /*<<< orphan*/  (* PositionTableEntryFn ) (int /*<<< orphan*/ ,struct _cms_typehandler_struct*,TYPE_1__*,void*,int,int) ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _cmsCalloc (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  _cmsFree (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  _cmsReadUInt32Number (int /*<<< orphan*/ ,TYPE_1__*,int*) ; 
 int stub1 (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,TYPE_1__*,int) ; 

__attribute__((used)) static
cmsBool ReadPositionTable(cmsContext ContextID, struct _cms_typehandler_struct* self,
                              cmsIOHANDLER* io,
                              cmsUInt32Number Count,
                              cmsUInt32Number BaseOffset,
                              void *Cargo,
                              PositionTableEntryFn ElementFn)
{
    cmsUInt32Number i;
    cmsUInt32Number *ElementOffsets = NULL, *ElementSizes = NULL;
    cmsUInt32Number currentPosition;

    currentPosition = io->Tell(ContextID, io);

    // Verify there is enough space left to read at least two cmsUInt32Number items for Count items.
    if (((io->ReportedSize - currentPosition) / (2 * sizeof(cmsUInt32Number))) < Count)
        return FALSE;

    // Let's take the offsets to each element
    ElementOffsets = (cmsUInt32Number *) _cmsCalloc(ContextID, Count, sizeof(cmsUInt32Number));
    if (ElementOffsets == NULL) goto Error;

    ElementSizes = (cmsUInt32Number *) _cmsCalloc(ContextID, Count, sizeof(cmsUInt32Number));
    if (ElementSizes == NULL) goto Error;

    for (i=0; i < Count; i++) {

        if (!_cmsReadUInt32Number(ContextID, io, &ElementOffsets[i])) goto Error;
        if (!_cmsReadUInt32Number(ContextID, io, &ElementSizes[i])) goto Error;

        ElementOffsets[i] += BaseOffset;
    }

    // Seek to each element and read it
    for (i=0; i < Count; i++) {

        if (!io -> Seek(ContextID, io, ElementOffsets[i])) goto Error;

        // This is the reader callback
        if (!ElementFn(ContextID, self, io, Cargo, i, ElementSizes[i])) goto Error;
    }

    // Success
    if (ElementOffsets != NULL) _cmsFree(ContextID, ElementOffsets);
    if (ElementSizes != NULL) _cmsFree(ContextID, ElementSizes);
    return TRUE;

Error:
    if (ElementOffsets != NULL) _cmsFree(ContextID, ElementOffsets);
    if (ElementSizes != NULL) _cmsFree(ContextID, ElementSizes);
    return FALSE;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct _cms_typehandler_struct {int dummy; } ;
typedef  scalar_t__ cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsUInt16Number ;
typedef  void cmsNAMEDCOLORLIST ;
struct TYPE_6__ {int (* Read ) (int /*<<< orphan*/ ,TYPE_1__*,char*,int,int) ;} ;
typedef  TYPE_1__ cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 int /*<<< orphan*/  _cmsReadUInt16Array (int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _cmsReadUInt32Number (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__*) ; 
 void* cmsAllocNamedColorList (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  cmsAppendNamedColor (int /*<<< orphan*/ ,void*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsERROR_RANGE ; 
 int /*<<< orphan*/  cmsFreeNamedColorList (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ cmsMAXCHANNELS ; 
 int /*<<< orphan*/  cmsSignalError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (scalar_t__) ; 
 int stub1 (int /*<<< orphan*/ ,TYPE_1__*,char*,int,int) ; 

__attribute__((used)) static
void *Type_ColorantTable_Read(cmsContext ContextID, struct _cms_typehandler_struct* self, cmsIOHANDLER* io, cmsUInt32Number* nItems, cmsUInt32Number SizeOfTag)
{
    cmsUInt32Number i, Count;
    cmsNAMEDCOLORLIST* List;
    char Name[34];
    cmsUInt16Number PCS[3];
    cmsUNUSED_PARAMETER(self);


    if (!_cmsReadUInt32Number(ContextID, io, &Count)) return NULL;

    if (Count > cmsMAXCHANNELS) {
        cmsSignalError(ContextID, cmsERROR_RANGE, "Too many colorants '%d'", Count);
        return NULL;
    }

    List = cmsAllocNamedColorList(ContextID, Count, 0, "", "");
    for (i=0; i < Count; i++) {

        if (io ->Read(ContextID, io,Name, 32, 1) != 1) goto Error;
        Name[32] = 0;

        if (!_cmsReadUInt16Array(ContextID, io, 3, PCS)) goto Error;

        if (!cmsAppendNamedColor(ContextID, List, Name, PCS, NULL)) goto Error;

    }

    *nItems = 1;
    return List;

Error:
    *nItems = 0;
    cmsFreeNamedColorList(ContextID, List);
    return NULL;

    cmsUNUSED_PARAMETER(SizeOfTag);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct _cms_typehandler_struct {int dummy; } ;
typedef  scalar_t__ cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsUInt16Number ;
struct TYPE_11__ {scalar_t__ ColorantCount; scalar_t__ Suffix; scalar_t__ Prefix; } ;
typedef  TYPE_1__ cmsNAMEDCOLORLIST ;
struct TYPE_12__ {int /*<<< orphan*/  (* Write ) (int /*<<< orphan*/ ,TYPE_2__*,int,char*) ;} ;
typedef  TYPE_2__ cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _cmsWriteUInt16Array (int /*<<< orphan*/ ,TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _cmsWriteUInt32Number (int /*<<< orphan*/ ,TYPE_2__*,scalar_t__) ; 
 int cmsMAXCHANNELS ; 
 int cmsMAX_PATH ; 
 scalar_t__ cmsNamedColorCount (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  cmsNamedColorInfo (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (scalar_t__) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*,int,char*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,TYPE_2__*,int,char*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,TYPE_2__*,int,char*) ; 

__attribute__((used)) static
cmsBool Type_NamedColor_Write(cmsContext ContextID, struct _cms_typehandler_struct* self, cmsIOHANDLER* io, void* Ptr, cmsUInt32Number nItems)
{
    cmsNAMEDCOLORLIST* NamedColorList = (cmsNAMEDCOLORLIST*) Ptr;
    char                prefix[33];     // Prefix for each color name
    char                suffix[33];     // Suffix for each color name
    cmsUInt32Number     i, nColors;

    nColors = cmsNamedColorCount(ContextID, NamedColorList);

    if (!_cmsWriteUInt32Number(ContextID, io, 0)) return FALSE;
    if (!_cmsWriteUInt32Number(ContextID, io, nColors)) return FALSE;
    if (!_cmsWriteUInt32Number(ContextID, io, NamedColorList ->ColorantCount)) return FALSE;

    strncpy(prefix, (const char*) NamedColorList->Prefix, 32);
    strncpy(suffix, (const char*) NamedColorList->Suffix, 32);

    suffix[32] = prefix[32] = 0;

    if (!io ->Write(ContextID, io, 32, prefix)) return FALSE;
    if (!io ->Write(ContextID, io, 32, suffix)) return FALSE;

    for (i=0; i < nColors; i++) {

       cmsUInt16Number PCS[3];
       cmsUInt16Number Colorant[cmsMAXCHANNELS];
       char Root[cmsMAX_PATH];

        if (!cmsNamedColorInfo(ContextID, NamedColorList, i, Root, NULL, NULL, PCS, Colorant)) return 0;
        Root[32] = 0;
        if (!io ->Write(ContextID, io, 32 , Root)) return FALSE;
        if (!_cmsWriteUInt16Array(ContextID, io, 3, PCS)) return FALSE;
        if (!_cmsWriteUInt16Array(ContextID, io, NamedColorList ->ColorantCount, Colorant)) return FALSE;
    }

    return TRUE;

    cmsUNUSED_PARAMETER(nItems);
    cmsUNUSED_PARAMETER(self);
}
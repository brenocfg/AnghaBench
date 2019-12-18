#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct _cms_typehandler_struct {int dummy; } ;
typedef  int /*<<< orphan*/  cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsMLU ;
typedef  int /*<<< orphan*/  cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WriteCountAndSting (int /*<<< orphan*/ ,struct _cms_typehandler_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
cmsBool  Type_CrdInfo_Write(cmsContext ContextID, struct _cms_typehandler_struct* self, cmsIOHANDLER* io, void* Ptr, cmsUInt32Number nItems)
{

    cmsMLU* mlu = (cmsMLU*) Ptr;

    if (!WriteCountAndSting(ContextID, self, io, mlu, "nm")) goto Error;
    if (!WriteCountAndSting(ContextID, self, io, mlu, "#0")) goto Error;
    if (!WriteCountAndSting(ContextID, self, io, mlu, "#1")) goto Error;
    if (!WriteCountAndSting(ContextID, self, io, mlu, "#2")) goto Error;
    if (!WriteCountAndSting(ContextID, self, io, mlu, "#3")) goto Error;

    return TRUE;

Error:
    return FALSE;

    cmsUNUSED_PARAMETER(nItems);
}
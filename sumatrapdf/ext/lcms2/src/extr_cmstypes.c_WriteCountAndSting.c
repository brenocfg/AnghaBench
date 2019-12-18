#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct _cms_typehandler_struct {int dummy; } ;
typedef  scalar_t__ cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsMLU ;
struct TYPE_5__ {int /*<<< orphan*/  (* Write ) (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__,char*) ;} ;
typedef  TYPE_1__ cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _cmsFree (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ _cmsMalloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  _cmsWriteUInt32Number (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__) ; 
 scalar_t__ cmsMLUgetASCII (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char const*,char*,scalar_t__) ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (struct _cms_typehandler_struct*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__,char*) ; 

__attribute__((used)) static
cmsBool  WriteCountAndSting(cmsContext ContextID, struct _cms_typehandler_struct* self, cmsIOHANDLER* io, cmsMLU* mlu, const char* Section)
{
 cmsUInt32Number TextSize;
 char* Text;
 cmsUNUSED_PARAMETER(self);

    TextSize = cmsMLUgetASCII(ContextID, mlu, "PS", Section, NULL, 0);
    Text     = (char*) _cmsMalloc(ContextID, TextSize);

    if (!_cmsWriteUInt32Number(ContextID, io, TextSize)) return FALSE;

    if (cmsMLUgetASCII(ContextID, mlu, "PS", Section, Text, TextSize) == 0) return FALSE;

    if (!io ->Write(ContextID, io, TextSize, Text)) return FALSE;
    _cmsFree(ContextID, Text);

    return TRUE;
}
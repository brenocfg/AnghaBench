#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct _cms_typehandler_struct {int dummy; } ;
typedef  scalar_t__ cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsMLU ;
struct TYPE_4__ {int /*<<< orphan*/  (* Write ) (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__,char*) ;} ;
typedef  TYPE_1__ cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  _cmsFree (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ _cmsMalloc (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ cmsMLUgetASCII (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  cmsNoCountry ; 
 int /*<<< orphan*/  cmsNoLanguage ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__,char*) ; 

__attribute__((used)) static
cmsBool Type_Text_Write(cmsContext ContextID, struct _cms_typehandler_struct* self, cmsIOHANDLER* io, void* Ptr, cmsUInt32Number nItems)
{
    cmsMLU* mlu = (cmsMLU*) Ptr;
    cmsUInt32Number size;
    cmsBool  rc;
    char* Text;
    cmsUNUSED_PARAMETER(self);

    // Get the size of the string. Note there is an extra "\0" at the end
    size = cmsMLUgetASCII(ContextID, mlu, cmsNoLanguage, cmsNoCountry, NULL, 0);
    if (size == 0) return FALSE;       // Cannot be zero!

    // Create memory
    Text = (char*) _cmsMalloc(ContextID, size);
    if (Text == NULL) return FALSE;

    cmsMLUgetASCII(ContextID, mlu, cmsNoLanguage, cmsNoCountry, Text, size);

    // Write it, including separator
    rc = io ->Write(ContextID, io, size, Text);

    _cmsFree(ContextID, Text);
    return rc;

    cmsUNUSED_PARAMETER(nItems);
}
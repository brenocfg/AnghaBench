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
typedef  int cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsMLU ;
typedef  int /*<<< orphan*/  cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 int /*<<< orphan*/  ReadCountAndSting (int /*<<< orphan*/ ,struct _cms_typehandler_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,char*) ; 
 int /*<<< orphan*/ * cmsMLUalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cmsMLUfree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
void *Type_CrdInfo_Read(cmsContext ContextID, struct _cms_typehandler_struct* self, cmsIOHANDLER* io, cmsUInt32Number* nItems, cmsUInt32Number SizeOfTag)
{
    cmsMLU* mlu = cmsMLUalloc(ContextID, 5);

    *nItems = 0;
    if (!ReadCountAndSting(ContextID, self, io, mlu, &SizeOfTag, "nm")) goto Error;
    if (!ReadCountAndSting(ContextID, self, io, mlu, &SizeOfTag, "#0")) goto Error;
    if (!ReadCountAndSting(ContextID, self, io, mlu, &SizeOfTag, "#1")) goto Error;
    if (!ReadCountAndSting(ContextID, self, io, mlu, &SizeOfTag, "#2")) goto Error;
    if (!ReadCountAndSting(ContextID, self, io, mlu, &SizeOfTag, "#3")) goto Error;

    *nItems = 1;
    return (void*) mlu;

Error:
    cmsMLUfree(ContextID, mlu);
    return NULL;

}
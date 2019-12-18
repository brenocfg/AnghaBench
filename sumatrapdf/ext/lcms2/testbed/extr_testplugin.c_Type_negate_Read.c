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
typedef  int cmsUInt16Number ;
typedef  int /*<<< orphan*/  cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 void* StageAllocNegate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cmsReadUInt16Number (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static
void *Type_negate_Read(cmsContext ContextID, struct _cms_typehandler_struct* self,
 			    cmsIOHANDLER* io,
                cmsUInt32Number* nItems,
                cmsUInt32Number SizeOfTag)
{
    cmsUInt16Number   Chans;
    if (!_cmsReadUInt16Number(ContextID, io, &Chans)) return NULL;
    if (Chans != 3) return NULL;

    *nItems = 1;
    return StageAllocNegate(ContextID);
}
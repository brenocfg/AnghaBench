#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct _cms_typehandler_struct {int dummy; } ;
typedef  size_t cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsMLU ;
struct TYPE_8__ {size_t (* Tell ) (int /*<<< orphan*/ ,TYPE_1__*) ;} ;
typedef  TYPE_1__ cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
struct TYPE_9__ {size_t* Sizes; size_t* Offsets; } ;
typedef  TYPE_2__ _cmsDICelem ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  Type_MLU_Write (int /*<<< orphan*/ ,struct _cms_typehandler_struct*,TYPE_1__*,void*,int) ; 
 size_t stub1 (int /*<<< orphan*/ ,TYPE_1__*) ; 
 size_t stub2 (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static
cmsBool WriteOneMLUC(cmsContext ContextID, struct _cms_typehandler_struct* self, cmsIOHANDLER* io,  _cmsDICelem* e, cmsUInt32Number i, const cmsMLU* mlu, cmsUInt32Number BaseOffset)
{
    cmsUInt32Number Before;

     // Special case for undefined strings (see ICC Votable
     // Proposal Submission, Dictionary Type and Metadata TAG Definition)
     if (mlu == NULL) {
        e ->Sizes[i] = 0;
        e ->Offsets[i] = 0;
        return TRUE;
    }

    Before = io ->Tell(ContextID, io);
    e ->Offsets[i] = Before - BaseOffset;

    if (!Type_MLU_Write(ContextID, self, io, (void*) mlu, 1)) return FALSE;

    e ->Sizes[i] = io ->Tell(ContextID, io) - Before;
    return TRUE;
}
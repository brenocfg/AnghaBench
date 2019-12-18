#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct _cms_typehandler_struct {int dummy; } ;
typedef  size_t cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsMLU ;
struct TYPE_7__ {int /*<<< orphan*/  (* Seek ) (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__) ;} ;
typedef  TYPE_1__ cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
struct TYPE_8__ {scalar_t__* Offsets; int /*<<< orphan*/ * Sizes; } ;
typedef  TYPE_2__ _cmsDICelem ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ Type_MLU_Read (int /*<<< orphan*/ ,struct _cms_typehandler_struct*,TYPE_1__*,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static
cmsBool ReadOneMLUC(cmsContext ContextID, struct _cms_typehandler_struct* self, cmsIOHANDLER* io,  _cmsDICelem* e, cmsUInt32Number i, cmsMLU** mlu)
{
    cmsUInt32Number nItems = 0;

    // A way to get null MLUCs
    if (e -> Offsets[i] == 0 || e ->Sizes[i] == 0) {

        *mlu = NULL;
        return TRUE;
    }

    if (!io -> Seek(ContextID, io, e -> Offsets[i])) return FALSE;

    *mlu = (cmsMLU*) Type_MLU_Read(ContextID, self, io, &nItems, e ->Sizes[i]);
    return *mlu != NULL;
}
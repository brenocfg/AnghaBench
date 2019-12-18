#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct _cms_typehandler_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  Desc; void* Ucr; void* Bg; } ;
typedef  TYPE_1__ cmsUcrBg ;
typedef  struct _cms_typehandler_struct* cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 scalar_t__ _cmsMallocZero (int /*<<< orphan*/ ,int) ; 
 void* cmsDupToneCurve (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  cmsMLUdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (struct _cms_typehandler_struct*) ; 

__attribute__((used)) static
void* Type_UcrBg_Dup(cmsContext ContextID, struct _cms_typehandler_struct* self, const void *Ptr, cmsUInt32Number n)
{
    cmsUcrBg* Src = (cmsUcrBg*) Ptr;
    cmsUcrBg* NewUcrBg = (cmsUcrBg*) _cmsMallocZero(ContextID, sizeof(cmsUcrBg));
    cmsUNUSED_PARAMETER(self);

    if (NewUcrBg == NULL) return NULL;

    NewUcrBg ->Bg   = cmsDupToneCurve(ContextID, Src ->Bg);
    NewUcrBg ->Ucr  = cmsDupToneCurve(ContextID, Src ->Ucr);
    NewUcrBg ->Desc = cmsMLUdup(ContextID, Src ->Desc);

    return (void*) NewUcrBg;

    cmsUNUSED_PARAMETER(n);
}
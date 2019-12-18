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
typedef  struct _cms_typehandler_struct* cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsToneCurve ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 scalar_t__ _cmsCalloc (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * cmsDupToneCurve (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (struct _cms_typehandler_struct*) ; 

__attribute__((used)) static
void* Type_vcgt_Dup(cmsContext ContextID, struct _cms_typehandler_struct* self, const void *Ptr, cmsUInt32Number n)
{
    cmsToneCurve** OldCurves =  (cmsToneCurve**) Ptr;
    cmsToneCurve** NewCurves;
    cmsUNUSED_PARAMETER(self);

    NewCurves = ( cmsToneCurve**) _cmsCalloc(ContextID, 3, sizeof(cmsToneCurve*));
    if (NewCurves == NULL) return NULL;

    NewCurves[0] = cmsDupToneCurve(ContextID, OldCurves[0]);
    NewCurves[1] = cmsDupToneCurve(ContextID, OldCurves[1]);
    NewCurves[2] = cmsDupToneCurve(ContextID, OldCurves[2]);

    return (void*) NewCurves;

    cmsUNUSED_PARAMETER(n);
}
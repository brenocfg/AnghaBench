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
struct TYPE_2__ {scalar_t__ Desc; scalar_t__ Bg; scalar_t__ Ucr; } ;
typedef  TYPE_1__ cmsUcrBg ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 int /*<<< orphan*/  _cmsFree (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  cmsFreeToneCurve (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  cmsMLUfree (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (struct _cms_typehandler_struct*) ; 

__attribute__((used)) static
void Type_UcrBg_Free(cmsContext ContextID, struct _cms_typehandler_struct* self, void *Ptr)
{
   cmsUcrBg* Src = (cmsUcrBg*) Ptr;
   cmsUNUSED_PARAMETER(self);

   if (Src ->Ucr) cmsFreeToneCurve(ContextID, Src ->Ucr);
   if (Src ->Bg)  cmsFreeToneCurve(ContextID, Src ->Bg);
   if (Src ->Desc) cmsMLUfree(ContextID, Src ->Desc);

   _cmsFree(ContextID, Ptr);
}
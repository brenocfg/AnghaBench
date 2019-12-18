#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cmsUInt16Number ;
typedef  int /*<<< orphan*/  cmsContext ;
struct TYPE_4__ {TYPE_1__* cmyk2cmyk; int /*<<< orphan*/  KTone; } ;
struct TYPE_3__ {int /*<<< orphan*/  Data; int /*<<< orphan*/  (* Eval16Fn ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ GrayOnlyParams ;

/* Variables and functions */
 int TRUE ; 
 int /*<<< orphan*/  cmsEvalToneCurve16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int BlackPreservingGrayOnlySampler(cmsContext ContextID, register const cmsUInt16Number In[], register cmsUInt16Number Out[], register void* Cargo)
{
    GrayOnlyParams* bp = (GrayOnlyParams*) Cargo;

    // If going across black only, keep black only
    if (In[0] == 0 && In[1] == 0 && In[2] == 0) {

        // TAC does not apply because it is black ink!
        Out[0] = Out[1] = Out[2] = 0;
        Out[3] = cmsEvalToneCurve16(ContextID, bp->KTone, In[3]);
        return TRUE;
    }

    // Keep normal transform for other colors
    bp ->cmyk2cmyk ->Eval16Fn(ContextID, In, Out, bp ->cmyk2cmyk->Data);
    return TRUE;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* Next; } ;
typedef  TYPE_1__ cmsStage ;
struct TYPE_8__ {TYPE_1__* Elements; } ;
typedef  TYPE_2__ cmsPipeline ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int cmsBool ;
struct TYPE_9__ {int nTypes; scalar_t__* MpeTypes; } ;
typedef  TYPE_3__ cmsAllowedLUT ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ cmsStageType (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static
cmsBool CheckOne(cmsContext ContextID, const cmsAllowedLUT* Tab, const cmsPipeline* Lut)
{
    cmsStage* mpe;
    int n;

    for (n=0, mpe = Lut ->Elements; mpe != NULL; mpe = mpe ->Next, n++) {

        if (n > Tab ->nTypes) return FALSE;
        if (cmsStageType(ContextID, mpe) != Tab ->MpeTypes[n]) return FALSE;
    }

    return (n == Tab ->nTypes);
}
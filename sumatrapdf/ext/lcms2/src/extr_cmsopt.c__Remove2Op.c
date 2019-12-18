#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ cmsStageSignature ;
struct TYPE_5__ {scalar_t__ Implements; struct TYPE_5__* Next; } ;
typedef  TYPE_1__ cmsStage ;
struct TYPE_6__ {TYPE_1__* Elements; } ;
typedef  TYPE_2__ cmsPipeline ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _RemoveElement (int /*<<< orphan*/ ,TYPE_1__**) ; 

__attribute__((used)) static
cmsBool _Remove2Op(cmsContext ContextID, cmsPipeline* Lut, cmsStageSignature Op1, cmsStageSignature Op2)
{
    cmsStage** pt1;
    cmsStage** pt2;
    cmsBool AnyOpt = FALSE;

    pt1 = &Lut ->Elements;
    if (*pt1 == NULL) return AnyOpt;

    while (*pt1 != NULL) {

        pt2 = &((*pt1) -> Next);
        if (*pt2 == NULL) return AnyOpt;

        if ((*pt1) ->Implements == Op1 && (*pt2) ->Implements == Op2) {
            _RemoveElement(ContextID, pt2);
            _RemoveElement(ContextID, pt1);
            AnyOpt = TRUE;
        }
        else
            pt1 = &((*pt1) -> Next);
    }

    return AnyOpt;
}
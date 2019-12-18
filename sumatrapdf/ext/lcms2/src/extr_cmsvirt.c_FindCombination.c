#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ cmsUInt32Number ;
typedef  scalar_t__ cmsTagSignature ;
typedef  int /*<<< orphan*/  cmsPipeline ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int cmsBool ;
struct TYPE_5__ {int IsV4; scalar_t__ RequiredTag; } ;
typedef  TYPE_1__ cmsAllowedLUT ;

/* Variables and functions */
 TYPE_1__* AllowedLUTTypes ; 
 scalar_t__ CheckOne (int /*<<< orphan*/ ,TYPE_1__ const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ SIZE_OF_ALLOWED_LUT ; 

__attribute__((used)) static
const cmsAllowedLUT* FindCombination(cmsContext ContextID, const cmsPipeline* Lut, cmsBool IsV4, cmsTagSignature DestinationTag)
{
    cmsUInt32Number n;

    for (n=0; n < SIZE_OF_ALLOWED_LUT; n++) {

        const cmsAllowedLUT* Tab = AllowedLUTTypes + n;

        if (IsV4 ^ Tab -> IsV4) continue;
        if ((Tab ->RequiredTag != 0) && (Tab ->RequiredTag != DestinationTag)) continue;

        if (CheckOne(ContextID, Tab, Lut)) return Tab;
    }

    return NULL;
}
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
typedef  int /*<<< orphan*/  cmsTagTypeSignature ;
struct TYPE_2__ {scalar_t__ SaveAs8Bits; } ;
typedef  TYPE_1__ cmsPipeline ;
typedef  double cmsFloat64Number ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 int /*<<< orphan*/  cmsSigLut16Type ; 
 int /*<<< orphan*/  cmsSigLut8Type ; 
 int /*<<< orphan*/  cmsSigLutBtoAType ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
cmsTagTypeSignature DecideLUTtypeB2A(cmsContext ContextID, cmsFloat64Number ICCVersion, const void *Data)
{
    cmsPipeline* Lut = (cmsPipeline*) Data;
    cmsUNUSED_PARAMETER(ContextID);

    if (ICCVersion < 4.0) {
        if (Lut ->SaveAs8Bits) return cmsSigLut8Type;
        return cmsSigLut16Type;
    }
    else {
         return cmsSigLutBtoAType;
    }
}
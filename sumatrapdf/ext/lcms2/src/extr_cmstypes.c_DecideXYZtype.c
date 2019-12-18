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
typedef  int /*<<< orphan*/  cmsTagTypeSignature ;
typedef  void const* cmsFloat64Number ;
typedef  void const* cmsContext ;

/* Variables and functions */
 int /*<<< orphan*/  cmsSigXYZType ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (void const*) ; 

__attribute__((used)) static
cmsTagTypeSignature DecideXYZtype(cmsContext ContextID, cmsFloat64Number ICCVersion, const void *Data)
{
    return cmsSigXYZType;

    cmsUNUSED_PARAMETER(ICCVersion);
    cmsUNUSED_PARAMETER(Data);
    cmsUNUSED_PARAMETER(ContextID);
}
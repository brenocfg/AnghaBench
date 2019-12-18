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
typedef  int /*<<< orphan*/  cmsUInt16Number ;
typedef  void* cmsContext ;
typedef  int /*<<< orphan*/  cmsCIELab ;

/* Variables and functions */
 int /*<<< orphan*/  Lab2ITU (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int TRUE ; 
 int /*<<< orphan*/  UTILS_UNUSED_PARAMETER (void*) ; 
 int /*<<< orphan*/  cmsDesaturateLab (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  cmsLabEncoded2Float (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static
int PCS2ITU(cmsContext ContextID, register const cmsUInt16Number In[], register cmsUInt16Number Out[], register void*  Cargo)
{
    cmsCIELab Lab;

    cmsLabEncoded2Float(NULL, &Lab, In);
    cmsDesaturateLab(NULL, &Lab, 85, -85, 125, -75);    // This function does the necessary gamut remapping
    Lab2ITU(&Lab, Out);
    return TRUE;

    UTILS_UNUSED_PARAMETER(Cargo);
    UTILS_UNUSED_PARAMETER(ContextID);
}
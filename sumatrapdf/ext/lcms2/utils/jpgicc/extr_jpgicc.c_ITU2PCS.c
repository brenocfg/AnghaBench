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
 int /*<<< orphan*/  ITU2Lab (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int TRUE ; 
 int /*<<< orphan*/  UTILS_UNUSED_PARAMETER (void*) ; 
 int /*<<< orphan*/  cmsFloat2LabEncoded (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
int ITU2PCS(cmsContext ContextID, register const cmsUInt16Number In[], register cmsUInt16Number Out[], register void*  Cargo)
{
    cmsCIELab Lab;

    ITU2Lab(In, &Lab);
    cmsFloat2LabEncoded(NULL, Out, &Lab);
    return TRUE;

    UTILS_UNUSED_PARAMETER(Cargo);
    UTILS_UNUSED_PARAMETER(ContextID);
}
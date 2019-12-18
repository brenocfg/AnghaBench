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
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 scalar_t__ InputColorant ; 
 scalar_t__ OutputColorant ; 
 int /*<<< orphan*/  cmsDeleteTransform (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  cmsFreeNamedColorList (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ hTrans ; 
 scalar_t__ hTransLab ; 
 scalar_t__ hTransXYZ ; 

__attribute__((used)) static
void CloseTransforms(cmsContext ContextID)
{
    if (InputColorant) cmsFreeNamedColorList(ContextID, InputColorant);
    if (OutputColorant) cmsFreeNamedColorList(ContextID, OutputColorant);

    if (hTrans) cmsDeleteTransform(ContextID, hTrans);
    if (hTransLab) cmsDeleteTransform(ContextID, hTransLab);
    if (hTransXYZ) cmsDeleteTransform(ContextID, hTransXYZ);

}
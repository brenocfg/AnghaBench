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
typedef  int cmsUInt16Number ;
typedef  int /*<<< orphan*/  cmsFloat64Number ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 int Verbose ; 
 int /*<<< orphan*/  cmsDoTransform (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int*,int) ; 
 scalar_t__ hTransLab ; 
 scalar_t__ hTransXYZ ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int,int,int) ; 

__attribute__((used)) static
void PrintPCSEncoded(cmsContext ContextID, cmsFloat64Number Input[])
{
    if (Verbose > 1 && hTransXYZ && hTransLab) {

        cmsUInt16Number XYZ[3], Lab[3];

        if (hTransXYZ) cmsDoTransform(ContextID, hTransXYZ, Input, XYZ, 1);
        if (hTransLab) cmsDoTransform(ContextID, hTransLab, Input, Lab, 1);

        printf("[PCS] Lab=(0x%04X,0x%04X,0x%04X) XYZ=(0x%04X,0x%04X,0x%04X)\n", Lab[0], Lab[1], Lab[2],
            XYZ[0], XYZ[1], XYZ[2]);

    }
}
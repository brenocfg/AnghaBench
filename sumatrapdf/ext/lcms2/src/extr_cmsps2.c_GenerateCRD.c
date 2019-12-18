#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int cmsUInt32Number ;
struct TYPE_7__ {int UsedSpace; } ;
typedef  TYPE_1__ cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 int /*<<< orphan*/  EmitHeader (int /*<<< orphan*/ ,TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteNamedColorCRD (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  WriteOutputLUT (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  _cmsIOPrintf (int /*<<< orphan*/ ,TYPE_1__*,char*) ; 
 int cmsFLAGS_NODEFAULTRESOURCEDEF ; 
 scalar_t__ cmsGetDeviceClass (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cmsSigNamedColorClass ; 

__attribute__((used)) static
cmsUInt32Number  GenerateCRD(cmsContext ContextID,
                             cmsHPROFILE hProfile,
                             cmsUInt32Number Intent, cmsUInt32Number dwFlags,
                             cmsIOHANDLER* mem)
{
    cmsUInt32Number dwBytesUsed;

    if (!(dwFlags & cmsFLAGS_NODEFAULTRESOURCEDEF)) {

        EmitHeader(ContextID, mem, "Color Rendering Dictionary (CRD)", hProfile);
    }


    // Is a named color profile?
    if (cmsGetDeviceClass(ContextID, hProfile) == cmsSigNamedColorClass) {

        if (!WriteNamedColorCRD(ContextID, mem, hProfile, Intent, dwFlags)) {
            return 0;
        }
    }
    else {

        // CRD are always implemented as LUT

        if (!WriteOutputLUT(ContextID, mem, hProfile, Intent, dwFlags)) {
            return 0;
        }
    }

    if (!(dwFlags & cmsFLAGS_NODEFAULTRESOURCEDEF)) {

        _cmsIOPrintf(ContextID, mem, "%%%%EndResource\n");
        _cmsIOPrintf(ContextID, mem, "\n%% CRD End\n");
    }

    // Done, keep memory usage
    dwBytesUsed = mem ->UsedSpace;

    // Finally, return used byte count
    return dwBytesUsed;
}
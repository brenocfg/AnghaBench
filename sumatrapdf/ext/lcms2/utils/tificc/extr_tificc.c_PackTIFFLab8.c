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
struct _cmstransform_struct {int dummy; } ;
typedef  unsigned char cmsUInt8Number ;
typedef  struct _cmstransform_struct* cmsUInt32Number ;
typedef  scalar_t__ cmsUInt16Number ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 int FromLabV4ToLabV2 (scalar_t__) ; 
 int /*<<< orphan*/  UTILS_UNUSED_PARAMETER (struct _cmstransform_struct*) ; 

__attribute__((used)) static
unsigned char* PackTIFFLab8(cmsContext ContextID, struct _cmstransform_struct* CMMcargo,
                            register cmsUInt16Number wOut[],
                            register cmsUInt8Number* output,
                            register cmsUInt32Number Stride)
{
    int a, b;

    *output++ = (cmsUInt8Number) (FromLabV4ToLabV2(wOut[0] + 0x0080) >> 8);

    a = (FromLabV4ToLabV2(wOut[1]) + 0x0080) >> 8;
    b = (FromLabV4ToLabV2(wOut[2]) + 0x0080) >> 8;

    *output++ = (cmsUInt8Number) ((a < 128) ? (a + 128) : (a - 128));
    *output++ = (cmsUInt8Number) ((b < 128) ? (b + 128) : (b - 128));

    return output;

    UTILS_UNUSED_PARAMETER(Stride);
    UTILS_UNUSED_PARAMETER(CMMcargo);
}
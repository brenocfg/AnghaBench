#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int cmsUInt32Number ;
typedef  scalar_t__ cmsFormatterDirection ;
struct TYPE_3__ {int /*<<< orphan*/  Fmt16; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ cmsFormatter ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 int CMS_PACK_FLAGS_FLOAT ; 
 int /*<<< orphan*/  PackTIFFLab16 ; 
 int /*<<< orphan*/  PackTIFFLab8 ; 
 int T_BYTES (int) ; 
 int /*<<< orphan*/  UnrollTIFFLab16 ; 
 int /*<<< orphan*/  UnrollTIFFLab8 ; 
 scalar_t__ cmsFormatterInput ; 

__attribute__((used)) static
cmsFormatter TiffFormatterFactory(cmsContext ContextID, cmsUInt32Number Type,
                                  cmsFormatterDirection Dir,
                                  cmsUInt32Number dwFlags)
{
    cmsFormatter Result = { NULL };
    int bps           = T_BYTES(Type);
    int IsTiffSpecial = (Type >> 23) & 1;

    if (IsTiffSpecial && !(dwFlags & CMS_PACK_FLAGS_FLOAT))
    {
        if (Dir == cmsFormatterInput)
        {
            Result.Fmt16 = (bps == 1) ? UnrollTIFFLab8 : UnrollTIFFLab16;
        }
        else
            Result.Fmt16 = (bps == 1) ? PackTIFFLab8 : PackTIFFLab16;
    }

    return Result;
}
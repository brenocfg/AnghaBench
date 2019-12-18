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
typedef  scalar_t__ cmsUInt32Number ;
typedef  scalar_t__ cmsFormatterDirection ;
struct TYPE_3__ {int /*<<< orphan*/  Fmt16; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ cmsFormatter ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 scalar_t__ CMS_PACK_FLAGS_FLOAT ; 
 scalar_t__ TYPE_RGB_565 ; 
 scalar_t__ cmsFormatterInput ; 
 int /*<<< orphan*/  my_Unroll565 ; 

cmsFormatter my_FormatterFactory(cmsContext ContextID, cmsUInt32Number Type,
                                  cmsFormatterDirection Dir,
                                  cmsUInt32Number dwFlags)
{
    cmsFormatter Result = { NULL };

    if ((Type == TYPE_RGB_565) &&
        !(dwFlags & CMS_PACK_FLAGS_FLOAT) &&
        (Dir == cmsFormatterInput)) {
            Result.Fmt16 = my_Unroll565;
    }
    return Result;
}
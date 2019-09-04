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
typedef  enum complex_fixup { ____Placeholder_complex_fixup } complex_fixup ;

/* Variables and functions */
#define  COMPLEX_FIXUP_NV12 132 
#define  COMPLEX_FIXUP_P8 131 
#define  COMPLEX_FIXUP_UYVY 130 
#define  COMPLEX_FIXUP_YUY2 129 
#define  COMPLEX_FIXUP_YV12 128 
 int /*<<< orphan*/  FIXME (char*,int) ; 

__attribute__((used)) static const char *debug_complex_fixup(enum complex_fixup fixup)
{
    switch(fixup)
    {
#define WINED3D_TO_STR(x) case x: return #x
        WINED3D_TO_STR(COMPLEX_FIXUP_YUY2);
        WINED3D_TO_STR(COMPLEX_FIXUP_UYVY);
        WINED3D_TO_STR(COMPLEX_FIXUP_YV12);
        WINED3D_TO_STR(COMPLEX_FIXUP_NV12);
        WINED3D_TO_STR(COMPLEX_FIXUP_P8);
#undef WINED3D_TO_STR
        default:
            FIXME("Unrecognized complex fixup %#x\n", fixup);
            return "unrecognized";
    }
}
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
typedef  enum fixup_channel_source { ____Placeholder_fixup_channel_source } fixup_channel_source ;

/* Variables and functions */
#define  CHANNEL_SOURCE_COMPLEX0 135 
#define  CHANNEL_SOURCE_COMPLEX1 134 
#define  CHANNEL_SOURCE_ONE 133 
#define  CHANNEL_SOURCE_W 132 
#define  CHANNEL_SOURCE_X 131 
#define  CHANNEL_SOURCE_Y 130 
#define  CHANNEL_SOURCE_Z 129 
#define  CHANNEL_SOURCE_ZERO 128 
 int /*<<< orphan*/  FIXME (char*,int) ; 

__attribute__((used)) static const char *debug_fixup_channel_source(enum fixup_channel_source source)
{
    switch(source)
    {
#define WINED3D_TO_STR(x) case x: return #x
        WINED3D_TO_STR(CHANNEL_SOURCE_ZERO);
        WINED3D_TO_STR(CHANNEL_SOURCE_ONE);
        WINED3D_TO_STR(CHANNEL_SOURCE_X);
        WINED3D_TO_STR(CHANNEL_SOURCE_Y);
        WINED3D_TO_STR(CHANNEL_SOURCE_Z);
        WINED3D_TO_STR(CHANNEL_SOURCE_W);
        WINED3D_TO_STR(CHANNEL_SOURCE_COMPLEX0);
        WINED3D_TO_STR(CHANNEL_SOURCE_COMPLEX1);
#undef WINED3D_TO_STR
        default:
            FIXME("Unrecognized fixup_channel_source %#x\n", source);
            return "unrecognized";
    }
}
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
#define  CHANNEL_SOURCE_ONE 133 
#define  CHANNEL_SOURCE_W 132 
#define  CHANNEL_SOURCE_X 131 
#define  CHANNEL_SOURCE_Y 130 
#define  CHANNEL_SOURCE_Z 129 
#define  CHANNEL_SOURCE_ZERO 128 
 int /*<<< orphan*/  FIXME (char*,int) ; 

__attribute__((used)) static const char *shader_arb_get_fixup_swizzle(enum fixup_channel_source channel_source)
{
    switch(channel_source)
    {
        case CHANNEL_SOURCE_ZERO: return "0";
        case CHANNEL_SOURCE_ONE: return "1";
        case CHANNEL_SOURCE_X: return "x";
        case CHANNEL_SOURCE_Y: return "y";
        case CHANNEL_SOURCE_Z: return "z";
        case CHANNEL_SOURCE_W: return "w";
        default:
            FIXME("Unhandled channel source %#x\n", channel_source);
            return "undefined";
    }
}
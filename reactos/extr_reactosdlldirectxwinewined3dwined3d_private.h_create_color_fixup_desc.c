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
struct color_fixup_desc {int member_0; int member_1; int member_2; int member_3; int member_4; int member_5; int member_6; int member_7; } ;
typedef  enum fixup_channel_source { ____Placeholder_fixup_channel_source } fixup_channel_source ;

/* Variables and functions */

__attribute__((used)) static inline struct color_fixup_desc create_color_fixup_desc(
        int sign0, enum fixup_channel_source src0, int sign1, enum fixup_channel_source src1,
        int sign2, enum fixup_channel_source src2, int sign3, enum fixup_channel_source src3)
{
    struct color_fixup_desc fixup =
    {
        sign0, src0,
        sign1, src1,
        sign2, src2,
        sign3, src3,
    };
    return fixup;
}
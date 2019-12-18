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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  AAC_PROFILE_MAIN ; 
#define  AOT_AAC_LC 136 
#define  AOT_AAC_LTP 135 
#define  AOT_AAC_MAIN 134 
#define  AOT_AAC_PS 133 
#define  AOT_AAC_SBR 132 
#define  AOT_AAC_SC 131 
#define  AOT_AAC_SSR 130 
#define  AOT_ER_AAC_ELD 129 
#define  AOT_ER_AAC_LD 128 
 int /*<<< orphan*/  static_assert (int,char*) ; 

__attribute__((used)) static int AOTtoAACProfile(uint8_t i_object_type)
{
    switch(i_object_type)
    {
        case AOT_AAC_MAIN:
        case AOT_AAC_LC:
        case AOT_AAC_SSR:
        case AOT_AAC_LTP:
        case AOT_AAC_SBR:
        case AOT_AAC_SC:
        case AOT_ER_AAC_LD:
        case AOT_AAC_PS:
        case AOT_ER_AAC_ELD:
            {
            static_assert(AOT_AAC_MAIN == AAC_PROFILE_MAIN + 1,
                          "invalid profile to object mapping");
            return i_object_type - 1;
            }
        default:
            return -1;
    }
}
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
 char const** ISO13818_1_other_descs ; 
 char const** ISO13818_1_streamstypes_descs ; 

__attribute__((used)) static const char *ISO13818_1_Get_StreamType_Description(uint8_t i_type)
{
    if( i_type <= 0x23 )
        return ISO13818_1_streamstypes_descs[i_type];
    else if (i_type >= 0x0F && i_type < 0x7F)
        return ISO13818_1_streamstypes_descs[0];
    else if( i_type == 0x7F )
        return ISO13818_1_streamstypes_descs[0x1A];
    else
        return ISO13818_1_other_descs[1];
}
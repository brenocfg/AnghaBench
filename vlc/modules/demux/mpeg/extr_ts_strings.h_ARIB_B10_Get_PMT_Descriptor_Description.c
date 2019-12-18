#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_2__ {int id; char const* psz_desc; } ;

/* Variables and functions */
 TYPE_1__* ARIB_B10_PMT_Descriptors_descs ; 

__attribute__((used)) static const char *ARIB_B10_Get_PMT_Descriptor_Description(uint8_t i_desc)
{
    for(uint8_t i=0; i<5; i++)
        if(ARIB_B10_PMT_Descriptors_descs[i].id == i_desc)
            return ARIB_B10_PMT_Descriptors_descs[i].psz_desc;
    return NULL;
}
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
 char const** rgpsz_ATSC_A53_service_types ; 

__attribute__((used)) static const char * ATSC_A53_get_service_type( uint8_t i_type )
{
    if( i_type == 0 || i_type > 5 )
        return NULL;
    return rgpsz_ATSC_A53_service_types[i_type - 1];
}
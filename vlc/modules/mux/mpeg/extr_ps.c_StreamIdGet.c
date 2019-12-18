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

/* Variables and functions */

__attribute__((used)) static int StreamIdGet( bool *id, int i_id_min, int i_id_max )
{
    int i;

    for( i = 0; i <= i_id_max - i_id_min; i++ )
    {
        if( id[i] )
        {
            id[i] = false;

            return i_id_min + i;
        }
    }
    return -1;
}
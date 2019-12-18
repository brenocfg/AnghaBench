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
typedef  int /*<<< orphan*/  val ;

/* Variables and functions */
 scalar_t__ byte_swapped ; 
 int /*<<< orphan*/  put_data (unsigned short*,int) ; 

void put_word( unsigned short val )
{
    if (byte_swapped) val = (val << 8) | (val >> 8);
    put_data( &val, sizeof(val) );
}
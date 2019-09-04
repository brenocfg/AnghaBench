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
 int /*<<< orphan*/  put_data (unsigned int*,int) ; 

void put_dword( unsigned int val )
{
    if (byte_swapped)
        val = ((val << 24) | ((val << 8) & 0x00ff0000) | ((val >> 8) & 0x0000ff00) | (val >> 24));
    put_data( &val, sizeof(val) );
}
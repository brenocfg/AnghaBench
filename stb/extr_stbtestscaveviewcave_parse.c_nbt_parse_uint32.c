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
typedef  unsigned char uint32 ;

/* Variables and functions */

__attribute__((used)) static uint32 nbt_parse_uint32(unsigned char *buffer)
{
   return (buffer[0] << 24) + (buffer[1]<<16) + (buffer[2]<<8) + buffer[3];
}
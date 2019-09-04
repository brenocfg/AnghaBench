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

unsigned int stb_hashlen(char *str, int len)
{
   unsigned int hash = 0;
   while (len-- > 0 && *str)
      hash = (hash << 7) + (hash >> 25) + *str++;
   return hash + (hash >> 16);
}
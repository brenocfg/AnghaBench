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

__attribute__((used)) static void nbt_get_string_data(unsigned char *data, char *buffer, size_t bufsize)
{
   int len = data[0]*256 + data[1];
   int i;
   for (i=0; i < len && i+1 < (int) bufsize; ++i)
      buffer[i] = (char) data[i+2];
   buffer[i] = 0;
}
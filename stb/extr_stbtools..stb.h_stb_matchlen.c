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
typedef  size_t stb_uint ;
typedef  scalar_t__ stb_uchar ;

/* Variables and functions */

__attribute__((used)) static unsigned int stb_matchlen(stb_uchar *m1, stb_uchar *m2, stb_uint maxlen)
{
   stb_uint i;
   for (i=0; i < maxlen; ++i)
      if (m1[i] != m2[i]) return i;
   return i;
}
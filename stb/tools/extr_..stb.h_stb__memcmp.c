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
 int memcmp (char*,char*,int /*<<< orphan*/ ) ; 
 int stb__memcmpoffset ; 
 int /*<<< orphan*/  stb__memcmpsize ; 

int stb__memcmp(const void *a, const void *b)
{
   return memcmp((char *) a + stb__memcmpoffset, (char *) b + stb__memcmpoffset, stb__memcmpsize);
}
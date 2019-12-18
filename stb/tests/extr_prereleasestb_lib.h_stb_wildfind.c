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
 int stb__wildmatch_raw (char*,char*,int,int /*<<< orphan*/ ) ; 

int stb_wildfind(char *expr, char *candidate)
{
   return stb__wildmatch_raw(expr, candidate, 1,0);
}
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
typedef  int /*<<< orphan*/  stb_cfg ;

/* Variables and functions */
 int /*<<< orphan*/  stb_cfg_read (int /*<<< orphan*/ *,char*,char*,int) ; 

int stb_cfg_read_string(stb_cfg *z, char *key, char *value, int len)
{
   if (!stb_cfg_read(z, key, value, len)) return 0;
   value[len-1] = 0;
   return 1;
}
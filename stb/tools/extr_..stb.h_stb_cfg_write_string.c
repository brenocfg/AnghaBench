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
 int /*<<< orphan*/  stb_cfg_write (int /*<<< orphan*/ *,char*,char*,int) ; 
 scalar_t__ strlen (char*) ; 

void stb_cfg_write_string(stb_cfg *z, char *key, char *value)
{
   stb_cfg_write(z, key, value, (int) strlen(value)+1);
}
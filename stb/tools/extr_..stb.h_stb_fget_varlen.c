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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 unsigned int stb_fget_varlenu (int /*<<< orphan*/ *) ; 

int     stb_fget_varlen(FILE *f)
{
   unsigned int z = stb_fget_varlenu(f);
   return (z & 1) ? ~(z>>1) : (z>>1);
}
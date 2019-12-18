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
typedef  int /*<<< orphan*/  stb_sdict ;

/* Variables and functions */
 int /*<<< orphan*/ * stb_sdict_create () ; 

stb_sdict * stb_sdict_new(void)
{
   stb_sdict *d = stb_sdict_create();
   if (d == NULL) return NULL;
   return d;
}